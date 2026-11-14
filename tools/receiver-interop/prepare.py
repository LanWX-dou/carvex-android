"""Stage original DiPlay receiver code for optional JVM interoperability tests.

No receiver source is distributed or compiled into production variants. Run the
printed Gradle command after preparing; its init script affects only test sources.
Source/extracted-body hashes are retained in build/receiver-interop/manifest.json.
"""
import argparse
import hashlib
import json
import re
import shutil
import subprocess
from pathlib import Path

ANDROID = Path(__file__).resolve().parents[2]
TEMPLATES = Path(__file__).resolve().parent
OUT = ANDROID / 'build/receiver-interop'
PREFIX = 'shared/src/main/java/com/shilapi/xcertplay/'
WHOLE = (
    'iap2/wire/Iap2Wire.kt', 'iap2/wire/Iap2WireCodec.kt',
    'iap2/wire/Iap2CsmFramer.kt', 'iap2/catalog/Iap2Endpoint.kt',
    'iap2/body/Iap2BodyReader.kt', 'iap2/body/Iap2BodyBuilder.kt',
    'iap2/message/Iap2Messages.kt', 'media/CarPlayPlaybackStatus.kt',
    'iap2/message/Iap2LaneGuidance.kt', 'hud/NavigationOutputWorker.kt',
    'transport/Iap2FileTransferReceiver.kt',
    'hud/BydHudRouteState.kt', 'hud/BydManeuverCodes.kt', 'airplay/AirPlayHid.kt',
)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def git(repo, *args):
    return subprocess.check_output(['git', '-C', str(repo), *args], text=True).strip()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('receiver', type=Path, help='clean DiPlay source checkout')
    args = parser.parse_args()
    receiver = args.receiver.resolve(strict=True)
    if git(receiver, 'status', '--porcelain', '--untracked-files=normal'):
        raise ValueError('Receiver checkout must be clean; record a source commit first')
    commit = git(receiver, 'rev-parse', 'HEAD')
    sources = {}
    slices = {}
    staged = {}

    def read(relative):
        data = (receiver / relative).read_bytes()
        sources[relative] = digest(data)
        return data

    def stage(module, relative, data):
        dest = OUT / module / 'receiver' / relative
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(data)
        staged[dest.relative_to(OUT).as_posix()] = digest(data)

    protocol = 'protocol-carplay'
    for relative in WHOLE:
        data = read(PREFIX + relative)
        stage(protocol, relative, data)
        if relative == 'airplay/AirPlayHid.kt':
            stage('host-carlife-mixing', relative, data)

    worker_test = 'shared/src/test/java/com/shilapi/xcertplay/hud/NavigationOutputWorkerTest.kt'
    stage(protocol, 'hud/NavigationOutputWorkerTest.kt', read(worker_test))

    # Only imports are reduced. Model and parser bodies are copied exactly.
    call_source = read(PREFIX + 'hud/BydCarPlayCall.kt')
    begin = call_source.index(b'data class CarPlayCallCard(')
    boundary = re.search(rb'/\*\*\r?\n \* Optional, needs ADB over network:', call_source[begin:])
    if boundary is None:
        raise ValueError('Missing original call-parser end boundary')
    end = begin + boundary.start()
    call_slice = call_source[begin:end]
    slices['hud/CarPlayCallState.kt'] = digest(call_slice)
    stage(protocol, 'hud/CarPlayCallState.kt',
          b'package com.shilapi.xcertplay.hud\n'
          b'import com.shilapi.xcertplay.iap2.body.Iap2BodyReader\n'
          b'import com.shilapi.xcertplay.iap2.wire.Iap2Frame\n' + call_slice)

    # Execute the actual declaration function, without its Android-facing callers.
    info = read(PREFIX + 'airplay/AirPlayInfoPlist.kt')
    begin = info.index(b'    private fun audioFormats(')
    end = info.index(b'    /**', begin)
    audio_slice = info[begin:end]
    slices['airplay/ReceiverAudioFormats.kt'] = digest(audio_slice)
    buffered = read(PREFIX + 'airplay/BufferedAudioStream.kt')
    match = re.search(rb'const val STREAM_TYPE = (\d+)\b', buffered)
    if match is None:
        raise ValueError('Missing buffered stream constant')
    stage(protocol, 'airplay/ReceiverAudioFormats.kt',
          b'package com.shilapi.xcertplay.airplay\n'
          b'internal object ReceiverAudioFormats {\n' +
          audio_slice.replace(b'private fun audioFormats(', b'fun audioFormats(', 1) + b'}\n'
          b'internal object BufferedAudioStream { const val STREAM_TYPE = ' + match[1] + b' }\n')

    for module, name in ((protocol, 'ReceiverProtocolContractTest.kt'),
                         ('host-carlife-mixing', 'ReceiverCallKeyContractTest.kt')):
        target = OUT / module / 'contracts' / name
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(TEMPLATES / name, target)
        staged[target.relative_to(OUT).as_posix()] = digest(target.read_bytes())

    manifest = {
        'schema': 2, 'receiver_commit': commit, 'source_sha256': sources,
        'staged_sha256': staged,
        'unchanged_body_slice_sha256': slices,
        'contract_template_sha256': {name: digest((TEMPLATES / name).read_bytes()) for name in
                                    ('ReceiverProtocolContractTest.kt', 'ReceiverCallKeyContractTest.kt')},
        'sender_commit': git(ANDROID, 'rev-parse', 'HEAD'),
        'validation_scope': 'JVM contracts, not vehicle acceptance or Apple sender equivalence',
    }
    OUT.mkdir(parents=True, exist_ok=True)
    # Avoid interpolating user source paths into executable Groovy/shell text.
    # All roots below are derived from this project's own fixed build directory.
    init = '''gradle.beforeProject { p ->
    if (p.path in [':protocol-carplay', ':host-carlife-mixing']) {
        p.plugins.withId('com.android.library') {
            def root = new File(p.rootProject.projectDir, 'build/receiver-interop/' + p.name)
            def tests = p.extensions.getByName('android').sourceSets.getByName('test')
            tests.kotlin.srcDir(new File(root, 'receiver'))
            tests.kotlin.srcDir(new File(root, 'contracts'))
        }
    }
}
'''
    (OUT / 'receiver-tests.init.gradle').write_text(init, encoding='utf-8')
    staged['receiver-tests.init.gradle'] = digest((OUT / 'receiver-tests.init.gradle').read_bytes())
    (OUT / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    print(f'Prepared receiver {commit}; {len(sources)} source hashes, {len(slices)} body hashes')
    print('Manifest: build/receiver-interop/manifest.json')
    print(r'.\gradlew.bat :protocol-carplay:testDebugUnitTest '
          r':host-carlife-mixing:testDebugUnitTest --offline --console=plain '
          r'--no-configuration-cache -I build/receiver-interop/receiver-tests.init.gradle')


if __name__ == '__main__':
    main()

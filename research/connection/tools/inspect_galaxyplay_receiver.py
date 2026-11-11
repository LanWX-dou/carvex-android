"""Verify the supplied GalaxyPlay APK against reviewed receiver DEX locations.

This reads original bytes, resolves method ownership, and checks instruction
hashes. It does not run vendor code or prove Apple semantics or vehicle results.
The APK and complete vendor disassembly remain outside the repository.
"""
import argparse
import hashlib
import json
import struct
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
EVIDENCE = ROOT / 'research/connection/evidence/galaxyplay-0.1.212-receiver.json'
APK_SHA256 = 'f106680faa27be5a9dfc4a9a9b9cb59239e4512c5f3b73b64cebfec47bb023e6'
PREFIX = 'Lcom/shilapi/xcertplay/'
METHODS = {
    'classes2.dex': {
        'hud/CarPlayNavigationInput.accept': 0x023cb4,
        'hud/CarPlayNavigationInput.updateRoute': 0x0249f0,
        'hud/CarPlayNavigationInput.updateManeuver': 0x024858,
        'hud/CarPlayNavigationInput.snapshot': 0x024070,
        'hud/CarPlayNavigationInput.reset': 0x024810,
        'hud/BydNavigationOutputs.onFrame$shared': 0x01a184,
        'hud/ClusterSongState.accept': 0x02584c,
        'hud/BydClusterSong.onFrame': 0x014564,
        'hud/CarPlayCallState.accept': 0x021b70,
        'hud/BydCarPlayCall.onFrame': 0x011e3c,
    },
    'classes3.dex': {
        'transport/Iap2WiredControlClient$Companion.subscriptions': 0x028ef8,
        'transport/Iap2IdentificationClient$Companion.identificationInformation': 0x01e3fc,
        'transport/Iap2IdentificationClient$Companion.identificationInformation$lambda$7$lambda$6': 0x01e914,
    },
    'classes5.dex': {
        'orchestration/CarPlayController.onRouteFrame': 0x04b370,
        'orchestration/CarPlayController.artworkTransferHandler$lambda$62': 0x046990,
        'airplay/AirPlaySession.handleStreams': 0x02409c,
        'airplay/AudioStreamCodec.fromFormatBits': 0x027cec,
        'airplay/CarPlayMediaEngine.onAudio': 0x02e9cc,
        'airplay/CarPlayMediaEngine.microphoneConfig': 0x02e608,
        'airplay/CarPlayMediaEngine.dataStreamKey': 0x02e464,
    },
    'classes6.dex': {
        'media/CarPlayPlaybackStatus.acceptUpdate': 0x01f8d8,
        'media/CarPlayPlaybackStatus.updatedStatus': 0x01f83c,
        'media/AndroidMediaSink.onMicrophoneStarted': 0x01228c,
        'media/MicrophoneUplink.start': 0x026c40,
        'media/MicrophoneUplink.capture': 0x027a24,
    },
    'classes11.dex': {
        'iap2/message/Iap2ControlMessages.subscriptions': 0x002774,
        'iap2/message/Iap2ControlMessages.subscriptions$lambda$5$lambda$2': 0x002930,
        'iap2/message/Iap2ControlMessages.subscriptions$lambda$5$lambda$4': 0x0029ec,
    },
}
ANDROID_FILES = (
    'protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/AirSession.kt',
    'protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/NowPlayingUpdate.kt',
    'protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/NowPlayingArtwork.kt',
    'protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/PhoneSubscriptions.kt',
    'protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/CallMicrophonePlan.kt',
    'protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/CarPlayAudioPlan.kt',
    'protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/NavigationPublisher.kt',
    'bridge/src/main/java/io/github/iamr0s/carvex/session/SessionController.kt',
    'bridge/src/main/java/io/github/iamr0s/carvex/session/HostNavigationRelay.kt',
    'host-carlife-mixing/src/main/java/io/github/iamr0s/carvex/host/vendor/CarWithNavigation.kt',
    'protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/NavigationGuidance.kt',
    'protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/RuntimeIap.kt',
)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def uleb(data, offset):
    value = 0
    for shift in range(0, 35, 7):
        byte = data[offset]
        offset += 1
        value |= (byte & 127) << shift
        if not byte & 128:
            return value, offset
    raise ValueError('invalid ULEB128')


def dex_methods(data):
    """Resolve class_data -> method_id -> declaring type/name/prototype."""
    def table(header):
        return struct.unpack_from('<II', data, header)

    string_count, string_table = table(0x38)
    strings = []
    for index in range(string_count):
        offset = struct.unpack_from('<I', data, string_table + 4 * index)[0]
        _, start = uleb(data, offset)
        end = data.index(b'\0', start)
        # Metadata strings can contain modified UTF-8; reviewed method identifiers
        # are ASCII, so replacement decoding does not affect their ownership.
        strings.append(data[start:end].decode('utf-8', errors='replace'))
    type_count, type_table = table(0x40)
    types = [strings[struct.unpack_from('<I', data, type_table + i * 4)[0]]
             for i in range(type_count)]
    _, prototype_table = table(0x48)
    _, method_table = table(0x58)
    class_count, class_table = table(0x60)
    result = {}
    for index in range(class_count):
        class_index = struct.unpack_from('<I', data, class_table + index * 32)[0]
        offset = struct.unpack_from('<I', data, class_table + index * 32 + 24)[0]
        if not offset:
            continue
        counts = []
        for _ in range(4):
            count, offset = uleb(data, offset)
            counts.append(count)
        for _ in range(counts[0] + counts[1]):
            _, offset = uleb(data, offset)
            _, offset = uleb(data, offset)
        for count in counts[2:]:
            method_index = 0
            for _ in range(count):
                delta, offset = uleb(data, offset)
                method_index += delta
                _, offset = uleb(data, offset)
                code_offset, offset = uleb(data, offset)
                if not code_offset:
                    continue
                owner, prototype, name = struct.unpack_from('<HHI', data, method_table + 8 * method_index)
                if owner != class_index:
                    raise ValueError('method owner differs from class_data')
                _, return_type, parameters = struct.unpack_from('<III', data, prototype_table + 12 * prototype)
                args = []
                if parameters:
                    length = struct.unpack_from('<I', data, parameters)[0]
                    args = [types[struct.unpack_from('<H', data, parameters + 4 + i * 2)[0]]
                            for i in range(length)]
                result[code_offset] = (types[owner], strings[name], '(' + ''.join(args) + ')' + types[return_type])
    return result


def inspect(path):
    apk = path.read_bytes()
    if digest(apk) != APK_SHA256:
        raise ValueError('APK differs from the reviewed GalaxyPlay build')
    result = {
        'schema': 1, 'date': '2026-11-11',
        'scope': 'Receiver byte identity and method locations; no runtime or Apple-equivalence claim',
        'apk_sha256': APK_SHA256, 'apk_bytes': len(apk),
        'manifest_identity_review': {'tool': 'Android SDK 36.0.0 aapt dump badging',
                                     'package': 'com.shilapi.galaxyplay',
                                     'version_name': '0.1.212', 'version_code': 240},
        'dex': {},
    }
    with zipfile.ZipFile(path) as archive:
        result['manifest_sha256'] = digest(archive.read('AndroidManifest.xml'))
        result['dex_count'] = sum(name.endswith('.dex') for name in archive.namelist())
        for name, methods in METHODS.items():
            data = archive.read(name)
            if not data.startswith(b'dex\n'):
                raise ValueError('invalid DEX magic')
            owners = dex_methods(data)
            entry = {'sha256': digest(data), 'bytes': len(data), 'methods': {}}
            for label, offset in methods.items():
                owner, method = label.rsplit('.', 1)
                resolved = owners.get(offset)
                if resolved is None or resolved[:2] != (PREFIX + owner + ';', method):
                    raise ValueError(f'{name}:{label}: code_item ownership mismatch at {offset:#x}: {resolved}')
                registers, inputs, outputs, tries, debug, units = struct.unpack_from('<HHHHII', data, offset)
                begin = offset + 16
                instructions = data[begin:begin + 2 * units]
                if not units or len(instructions) != units * 2:
                    raise ValueError('invalid code_item bounds')
                entry['methods'][label] = {
                    'descriptor': resolved[0], 'method': resolved[1], 'prototype': resolved[2],
                    'code_item': hex(offset), 'insns_offset': hex(begin), 'code_units': units,
                    'registers': registers, 'inputs': inputs, 'outputs': outputs,
                    'insns_sha256': digest(instructions),
                }
            result['dex'][name] = entry
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('apk', type=Path)
    parser.add_argument('--write', action='store_true', help='generate only the evidence JSON')
    parser.add_argument('--check-android', action='store_true', help='check reviewed sender source hashes')
    args = parser.parse_args()
    observed = inspect(args.apk)
    if args.write:
        observed['android_source_review'] = {
            'scope': 'Current working files; identity only, not behavior tests',
            'files': {relative: digest((ROOT / 'android' / relative).read_bytes()) for relative in ANDROID_FILES},
        }
        EVIDENCE.write_text(json.dumps(observed, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    else:
        expected = json.loads(EVIDENCE.read_text(encoding='utf-8'))
        android = expected.pop('android_source_review')
        if observed != expected:
            raise ValueError('recorded APK identity, method ownership or instruction hashes differ')
        if args.check_android:
            for relative, sha256 in android['files'].items():
                if digest((ROOT / 'android' / relative).read_bytes()) != sha256:
                    raise ValueError(f'sender source changed: {relative}; reassess the audit')
    count = sum(len(entry['methods']) for entry in observed['dex'].values())
    print(f'PASS: APK identity, {len(observed["dex"])} reviewed DEX files, {count} method owners and instruction hashes')
    if args.check_android:
        print('PASS: reviewed Android sender source hashes')
    print('No receiver runtime, call audio, instrument display or Apple-equivalence test was performed.')


if __name__ == '__main__':
    main()

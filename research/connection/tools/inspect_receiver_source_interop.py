"""Verify DiPlay source hashes and GalaxyPlay 0.1.212 original call-key code.

This binds the receiver reference to input bytes. It does not execute a vehicle
session or replace the independent Apple sender evidence.
"""
import argparse
import hashlib
import json
import re
import struct
import subprocess
import zipfile
from pathlib import Path

from inspect_galaxyplay_receiver import dex_methods

EVIDENCE = Path(__file__).resolve().parents[1] / 'evidence/receiver-source-interop-20261111.json'
APK_SHA256 = 'f106680faa27be5a9dfc4a9a9b9cb59239e4512c5f3b73b64cebfec47bb023e6'
PREFIX = 'shared/src/main/java/com/shilapi/xcertplay/'
SOURCE_FILES = (
    'iap2/wire/Iap2Wire.kt', 'iap2/wire/Iap2WireCodec.kt', 'iap2/wire/Iap2CsmFramer.kt',
    'iap2/catalog/Iap2Endpoint.kt', 'iap2/body/Iap2BodyReader.kt',
    'iap2/body/Iap2BodyBuilder.kt', 'iap2/message/Iap2Messages.kt',
    'media/CarPlayPlaybackStatus.kt', 'hud/BydHudRouteState.kt',
    'hud/BydManeuverCodes.kt', 'airplay/AirPlayHid.kt', 'hud/BydCarPlayCall.kt',
    'airplay/AirPlayInfoPlist.kt', 'airplay/BufferedAudioStream.kt',
    'orchestration/CarPlayController.kt', 'airplay/CarPlayMediaEngine.kt',
    'airplay/AirPlaySession.kt', 'transport/Iap2IdentificationClient.kt',
    'transport/Iap2WirelessControlClient.kt', 'airplay/AirPlayIapTunnelStream.kt',
    'glance/CarPlayGlance.kt', 'iap2/message/Iap2LaneGuidance.kt',
)
METHODS = (
    (0x01cc1c, 'airplay/AirPlayHid', '<clinit>', '()V'),
    (0x01c5a4, 'airplay/AirPlayHid', 'descriptor', '([I)[B'),
    (0x01cbb0, 'airplay/AirPlayHid', 'telephonyHidDevice', '(Ljava/lang/String;)Ljava/util/Map;'),
    (0x01c7a8, 'airplay/AirPlayHid', 'telephonyReport', '(I)[B'),
    (0x025cd4, 'airplay/AirPlaySession', 'sendTelephony', '(I)V'),
    (0x0439e8, 'orchestration/CarPlayController', 'answerCall', '()Z'),
    (0x043cec, 'orchestration/CarPlayController', 'endCall', '()Z'),
)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def inspect(receiver, apk):
    commit = subprocess.check_output(['git', '-C', str(receiver), 'rev-parse', 'HEAD'], text=True).strip()
    if subprocess.check_output(['git', '-C', str(receiver), 'status', '--porcelain', '--untracked-files=normal'], text=True).strip():
        raise ValueError('Receiver checkout must be clean')
    sources = {PREFIX + name: digest((receiver / PREFIX / name).read_bytes()) for name in SOURCE_FILES}
    # Same unchanged slices executed by the optional Android contract tests.
    calls = (receiver / PREFIX / 'hud/BydCarPlayCall.kt').read_bytes()
    begin = calls.index(b'data class CarPlayCallCard(')
    boundary = re.search(rb'/\*\*\r?\n \* Optional, needs ADB over network:', calls[begin:])
    if boundary is None:
        raise ValueError('Missing original call-parser end boundary')
    call_slice = calls[begin:begin + boundary.start()]
    info = (receiver / PREFIX / 'airplay/AirPlayInfoPlist.kt').read_bytes()
    begin = info.index(b'    private fun audioFormats(')
    audio_slice = info[begin:info.index(b'    /**', begin)]
    slices = {'hud/CarPlayCallState.kt': digest(call_slice),
              'airplay/ReceiverAudioFormats.kt': digest(audio_slice)}
    apk_bytes = apk.read_bytes()
    if digest(apk_bytes) != APK_SHA256:
        raise ValueError('APK differs from reviewed GalaxyPlay 0.1.212')
    with zipfile.ZipFile(apk) as archive:
        dex = archive.read('classes5.dex')
    owners = dex_methods(dex)
    records = []
    for offset, owner, method, prototype in METHODS:
        expected = ('Lcom/shilapi/xcertplay/' + owner + ';', method, prototype)
        if owners.get(offset) != expected:
            raise ValueError(f'Unexpected DEX method ownership at {offset:06x}')
        units = struct.unpack_from('<I', dex, offset + 12)[0]
        instructions = dex[offset + 16:offset + 16 + units * 2]
        if len(instructions) != units * 2:
            raise ValueError('Truncated DEX code item')
        if method in ('answerCall', 'endCall'):
            selector = 1 if method == 'answerCall' else 3
            if instructions[:2] != bytes((0x12, selector << 4)):
                raise ValueError(f'{method} selector differs from original const/4')
        records.append({'code_item': f'0x{offset:06x}', 'owner': expected[0],
                        'method': method, 'prototype': prototype, 'code_units': units,
                        'instructions_sha256': digest(instructions)})

    # Original fill-array-data payload referenced by AirPlayHid.<clinit> at unit 0x154.
    payload = 0x01cc1c + 16 + 2 * 0x244
    marker, width, count = struct.unpack_from('<HHI', dex, payload)
    if (marker, width, count) != (0x0300, 4, 57):
        raise ValueError('Unexpected original telephony descriptor array payload')
    descriptor = bytes(struct.unpack_from('<57I', dex, payload + 8))
    source = (receiver / PREFIX / 'airplay/AirPlayHid.kt').read_text(encoding='utf-8')
    declaration = source.split('private val telephonyDescriptor = descriptor(', 1)[1].split('\n    )', 1)[0]
    source_descriptor = bytes(int(number, 16) for number in re.findall(r'0x[0-9a-fA-F]+', declaration))
    if descriptor != source_descriptor:
        raise ValueError('DiPlay telephony descriptor differs from original GalaxyPlay array')
    return {
        'schema': 1, 'date': '2026-11-11', 'receiver_commit': commit, 'source_sha256': sources,
        'unchanged_body_slice_sha256': slices,
        'galaxyplay_apk_sha256': APK_SHA256, 'galaxyplay_classes5_sha256': digest(dex),
        'galaxyplay_call_key_methods': records,
        'telephony_descriptor': {'array_payload_offset': f'0x{payload:06x}',
                                'hex': descriptor.hex(), 'sha256': digest(descriptor),
                                'source_and_apk_equal': True},
        'scope': 'Original receiver input identity and local call-key fact; no vehicle or Apple equivalence claim',
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('receiver', type=Path)
    parser.add_argument('apk', type=Path)
    parser.add_argument('--record', action='store_true', help='write reviewed evidence record')
    args = parser.parse_args()
    result = inspect(args.receiver.resolve(strict=True), args.apk.resolve(strict=True))
    if args.record:
        EVIDENCE.write_text(json.dumps(result, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
    elif result != json.loads(EVIDENCE.read_text(encoding='utf-8')):
        raise ValueError('Source/APK inputs differ from recorded evidence')
    print(f'PASS: {len(result["source_sha256"])} source hashes, 7 DEX owners/instruction hashes, '
          'identical original/source telephony descriptor; selectors answer=1 end=3')


if __name__ == '__main__':
    main()

"""Read the supplied CarWith APK and verify the recorded DEX byte locations.

Hashes locate the reviewed instructions; this is not a runtime or semantic test.
The APK and full vendor disassembly are deliberately excluded from the repository.
"""
import argparse
import hashlib
import json
import struct
import zipfile
from pathlib import Path

EVIDENCE = Path(__file__).resolve().parents[1] / 'evidence/carwith-4.0.14-host.json'
APK_SHA256 = 'c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e'
METHODS = {
    'classes.dex': {
        'h1.a.a([BI)': 0x48ef6c,
        'h1.a.c([B)': 0x48ee00,
        'PhoneAudioCast.B([B)': 0x4328e0,
        'VoIPService$IPhoneAudioCastStub.readAssistantRecorderData([B)': 0x4384d0,
        'PhoneAudioCast.z([B)': 0x432dc4,
        'VoIPService$IPhoneAudioCastStub.onAudioData([B)': 0x438558,
        'VoIPService$IPhoneAudioCastStub.startToRecord()': 0x438884,
        'h1.d.b([B)': 0x48f254,
        'h1.d.f([B)': 0x48f2ec,
    },
    'classes2.dex': {
        'LauncherDataBusClient.C()': 0x16fb48,
        'LauncherDataBusClient.E(...)': 0x16fc3c,
        'LauncherDataBusClient.F(...)': 0x16ffc4,
        'LauncherDataBusClient.w(String,String)': 0x16f3f0,
        'LauncherDataBusClient.u(Intent,Intent)': 0x16f8e4,
        'map.wms.i$x.g(boolean)': 0x1c5c20,
    },
    'classes4.dex': {
        'DataBusService$DataBusServiceStub.readAssistantRecorderData([B)': 0x10f738,
        'NavigationInfo.i()': 0x11c40c,
        'NavigationInfo.<init>(boolean,byte[],String,...)': 0x11c4d0,
        'databus.b$b.run()': 0x10979c,
    },
    'classes5.dex': {
        'UCarMapInfo.fromBundle(Bundle)': 0x1bf334,
        'be.f.d([BII)': 0x1b1fc8,
    },
    'classes6.dex': {
        'CarlifeAudioListener.onReceiveAudioStream([BIII)': 0x0adf90,
        'carlife.j.r(Intent)': 0x0a88bc,
        'carlife.j.G(Intent)': 0x0a8a60,
        'bh.d.<init>(Context)': 0x0a4cd8,
        'bh.d$c.b([BIIII)': 0x0a4c04,
        'carlife.j.A([BIIII)': 0x0a9488,
    },
}


def digest(data):
    return hashlib.sha256(data).hexdigest()


def dex_string(data, index):
    count, table = struct.unpack_from('<II', data, 0x38)
    if index >= count:
        raise ValueError('string index outside DEX table')
    offset = struct.unpack_from('<I', data, table + 4 * index)[0]
    start = offset
    while data[start] & 128:
        start += 1
    start += 1
    end = data.index(b'\0', start)
    return {'index': hex(index), 'data_offset': hex(offset),
            'value': data[start:end].decode('utf-8')}


def inspect(path):
    apk = path.read_bytes()
    if digest(apk) != APK_SHA256:
        raise ValueError('APK differs from the reviewed CarWith build')
    result = {'schema': 1, 'apk_sha256': APK_SHA256, 'apk_bytes': len(apk),
              'package': 'com.miui.carlink', 'version_code': 104000014,
              'version_name': '4.0.14-20260801',
              'scope': 'DEX byte identity and locations; no runtime or Apple-equivalence claim',
              'dex': {}}
    with zipfile.ZipFile(path) as archive:
        for name, methods in METHODS.items():
            data = archive.read(name)
            if not data.startswith(b'dex\n'):
                raise ValueError('invalid DEX magic')
            entry = {'sha256': digest(data), 'bytes': len(data), 'methods': {}}
            for label, offset in methods.items():
                registers, inputs, outputs, tries, debug, units = struct.unpack_from('<HHHHII', data, offset)
                begin = offset + 16
                instructions = data[begin:begin + 2 * units]
                if len(instructions) != units * 2 or not units:
                    raise ValueError('invalid code item bounds')
                entry['methods'][label] = {'code_item': hex(offset),
                    'insns_offset': hex(begin), 'code_units': units,
                    'registers': registers, 'inputs': inputs, 'outputs': outputs,
                    'insns_sha256': digest(instructions)}
            if name == 'classes2.dex':
                entry['distance_strings'] = [dex_string(data, i) for i in (0xc845, 0xc8e0, 0xc8cc)]
            result['dex'][name] = entry
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('apk', type=Path)
    parser.add_argument('--write', action='store_true', help='write only the evidence JSON')
    args = parser.parse_args()
    observed = inspect(args.apk)
    if args.write:
        EVIDENCE.write_text(json.dumps(observed, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    else:
        expected = json.loads(EVIDENCE.read_text(encoding='utf-8'))
        if observed != expected:
            raise ValueError('recorded DEX byte locations or hashes differ')
    method_count = sum(len(value['methods']) for value in observed['dex'].values())
    print(f'PASS: APK identity, {len(observed["dex"])} DEX files, {method_count} code items, and 3 original distance strings')
    print('No Android runtime, modem injection, or vehicle behavior was tested.')


if __name__ == '__main__':
    main()

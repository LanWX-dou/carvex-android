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
        'common.utils.p.a(Bitmap,float)': 0x44e174,
        'common.utils.p.b(Bitmap,Bitmap)': 0x44e254,
        'common.utils.c1.o()': 0x45668c,
        'common.utils.c1.l()': 0x456634,
        'e2.a.<init>()': 0x476570,
        'e2.a.u()': 0x47660c,
        'e2.a.o()': 0x4761c4,
        'e2.a.p()': 0x4761dc,
        'e2.d.b()': 0x476bfc,
        'e2.d.c()': 0x476c98,
        'o1.a.c()': 0x519cd8,
        'o1.a.d()': 0x519d28,
        'o1.a.g(boolean)': 0x519e64,
        'i1.a.h(int)': 0x495648,
        'i1.a.j(int,int)': 0x4956dc,
        'i1.a.q(int)': 0x495838,
        'i1.a.s(int)': 0x49597c,
        'h1.j$d.a()': 0x490714,
        'PhoneAudioCast.q(boolean)': 0x432b24,
    },
    'classes2.dex': {
        'LauncherDataBusClient.C()': 0x16fb48,
        'LauncherDataBusClient.E(...)': 0x16fc3c,
        'LauncherDataBusClient.F(...)': 0x16ffc4,
        'LauncherDataBusClient.w(String,String)': 0x16f3f0,
        'LauncherDataBusClient.u(Intent,Intent)': 0x16f8e4,
        'map.wms.i$x.g(boolean)': 0x1c5c20,
        'f5.d.i(oa.c,boolean)': 0x334a3c,
        'f5.d.n(String)': 0x334e8c,
        'f5.d.q(MusicInfo,oa.c)': 0x3350a8,
        'f5.d.m()': 0x334dac,
        'f5.d.j(MusicInfo,MusicInfo)': 0x3348a4,
        'f5.d.k(MusicInfo,MusicInfo)': 0x33491c,
        'f5.d.r()': 0x3351c8,
        'f5.d.s(oa.c,MusicInfo)': 0x335218,
        'HomeActivity$f.b()': 0x1a538c,
        'HomeActivity$f.c()': 0x1a5340,
        'HomeActivity.M1()': 0x1a6758,
        'HomeActivity.onDestroy()': 0x1a7200,
    },
    'classes4.dex': {
        'DataBusService$DataBusServiceStub.readAssistantRecorderData([B)': 0x10f738,
        'NavigationInfo.i()': 0x11c40c,
        'NavigationInfo.<init>(boolean,byte[],String,...)': 0x11c4d0,
        'databus.b$b.run()': 0x10979c,
        'oa.c.D()': 0x19ae44,
        'oa.c.r()': 0x19a9a0,
        'oa.c.N()': 0x19af4c,
        'za.c.a(MediaMetadataCompat)': 0x1bb444,
        'za.c.e(MediaMetadataCompat)': 0x1bb524,
        'databus.MusicInfo.<init>(String,String,String,String,long,...)': 0x11c0fc,
        'databus.MusicInfo.d()': 0x11bd10,
        'databus.MusicInfo.q()': 0x11bec0,
        'oa.c.F0()': 0x19c0d8,
        'oa.c.H()': 0x19a848,
        'oa.c.g(oa.c,Bitmap)': 0x19b540,
        'oa.c$c.a(ra.b)': 0x1996bc,
        'oa.c.s(MediaMetadataCompat)': 0x19b7b0,
        'oa.c.d0()': 0x19aa24,
        'oa.c.t()': 0x19b820,
        'ra.d.c(ra.a)': 0x1a5b08,
        'ra.d.d(ra.a)': 0x1a5bf0,
        'ra.d.e(ra.a)': 0x1a5c64,
        'ra.d.f()': 0x1a5cdc,
        'qa.b.C(String,Uri,Bitmap,Bitmap)': 0x1a20b4,
    },
    'classes5.dex': {
        'UCarMapInfo.fromBundle(Bundle)': 0x1bf334,
        'be.f.d([BII)': 0x1b1fc8,
        'be.h.b(int)': 0x1b2620,
        'be.g.d([BII)': 0x1b20bc,
    },
    'classes6.dex': {
        'CarlifeAudioListener.onReceiveAudioStream([BIII)': 0x0adf90,
        'carlife.j.r(Intent)': 0x0a88bc,
        'carlife.j.G(Intent)': 0x0a8a60,
        'bh.d.<init>(Context)': 0x0a4cd8,
        'bh.d$c.b([BIIII)': 0x0a4c04,
        'carlife.j.A([BIIII)': 0x0a9488,
        'CarlifeHw.onKeyEvent(KeyEvent)': 0x0a98e8,
        'carlife.j.q(Intent)': 0x0a7fd0,
        'carlife.j.x(int)': 0x0a93a8,
        'bh.d$c.a(int,int)': 0x0a4be4,
        'bh.d$c.notifyAudioState(int)': 0x0a4ba4,
    },
    'classes7.dex': {
        'voiceassistant.a.m(String)': 0x0e682c,
        'VoiceService.processIntentInternal(Intent)': 0x0ead0c,
        'VoiceService.stopEngine(boolean,boolean,int)': 0x0eaeb4,
        'VoiceService.onCreate()': 0x0eac1c,
        'execute.j.d(xh.a)': 0x0f3fa4,
        'execute.j.a(boolean,int)': 0x0f3ad4,
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


def voice_key_switch(data):
    """Read the reviewed onKeyEvent packed switch directly, in DEX code units."""
    base = METHODS['classes6.dex']['CarlifeHw.onKeyEvent(KeyEvent)'] + 16
    units = struct.unpack_from('<I', data, base - 4)[0]
    switch = 0x44
    opcode, register, relative = struct.unpack_from('<BBi', data, base + switch * 2)
    if opcode != 0x2b:
        raise ValueError('expected packed-switch instruction')
    table = switch + relative
    if not 0 <= table <= units - 4:
        raise ValueError('packed-switch payload outside code item')
    kind, count, first = struct.unpack_from('<HHi', data, base + table * 2)
    if kind != 0x100 or table + 4 + count * 2 > units:
        raise ValueError('invalid packed-switch payload')
    branches = {}
    for index in range(count):
        delta = struct.unpack_from('<i', data, base + table * 2 + 8 + index * 4)[0]
        target = switch + delta
        if not 0 <= target < units:
            raise ValueError('packed-switch branch outside code item')
        branches[str(first + index)] = hex(base + target * 2)
    if branches.get('8107') != '0xa9a50' or branches.get('8108') != '0xa9a40':
        raise ValueError('voice key targets differ from reviewed branches')
    return {'instruction_offset': hex(base + switch * 2),
            'register': register, 'payload_offset': hex(base + table * 2),
            'branch_file_offsets': branches}


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
            if name == 'classes6.dex':
                entry['voice_key_switch'] = voice_key_switch(data)
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
    print(f'PASS: APK identity, {len(observed["dex"])} DEX files, {method_count} code items, 3 original distance strings, and voice key switch targets')
    print('No Android runtime, modem injection, or vehicle behavior was tested.')


if __name__ == '__main__':
    main()

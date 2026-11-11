"""Verify reviewed navigation bytes from original Apple images and CarWith APK.

No vendor execution or vehicle test. The record pins method owners, slices,
enum tables and reviewed icon identities; semantic reasoning is in the audit.
Uses only the Python standard library, with no dependency on local dumps.
"""
import argparse
import hashlib
import json
import struct
import zipfile
from pathlib import Path

from inspect_galaxyplay_receiver import dex_methods

ROOT = Path(__file__).resolve().parents[3]
RECORD = ROOT / 'research/connection/evidence/navigation-numeric-core-20261111.json'
APPLE = {
    'accessoryd': (
        'research/protocol/iap2_input_business_lifecycle/source/firmware/accessoryd',
        '2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe',
        [(0x100003b28, 0x100003d60), (0x100003d60, 0x100003dc8),
         (0x100004428, 0x1000044b0), (0x1000c5008, 0x1000c504c),
         (0x1000c5704, 0x1000c5d64), (0x1000de30c, 0x1000de4a8),
         (0x100018f98, 0x100018fcc), (0x1000027f4, 0x100002eb0),
         (0x1001777c0, 0x100177d80), (0x100003b18, 0x100003b28),
         (0x100012120, 0x100012138), (0x1000153bc, 0x1000153cc),
         (0x100004650, 0x1000046d0), (0x1000046d0, 0x100004734)]),
    'CarPlay': (
        'firmware/extracted/24A446/binaries/CarPlay/CarPlay',
        '4dc1ad040452a76d1f33c291532eedf71bf509663c9e86a41c53f5d2c352afa5',
        [(0x247b00444, 0x247b004ec), (0x247b3a190, 0x247b3a220)]),
}
CARWITH_SHA = 'c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e'
METHODS = {
    0x16fc3c: ('Lcom/carwith/launcher/LauncherDataBusClient;', 'E'),
    0x16f3f0: ('Lcom/carwith/launcher/LauncherDataBusClient;', 'w'),
    0x1aedb4: ('Lcom/carwith/launcher/map/l;', 'd'),
    0x1af2fc: ('Lcom/carwith/launcher/map/l;', '<clinit>'),
    0x1aeacc: ('Lcom/carwith/launcher/map/l$a;', '<init>'),
    0x1aea9c: ('Lcom/carwith/launcher/map/l$a;', 'a'),
    0x1aeab4: ('Lcom/carwith/launcher/map/l$a;', 'b'),
}
# Resource table mapping reviewed with aapt2 against the pinned resources.arsc.
# No PNG bytes or full vendor dump are distributed.
ICONS = {
    'hud_gaode_car_2': 'res/uty.png', 'hud_gaode_car_3': 'res/bNv.png',
    'hud_gaode_car_4': 'res/xr7.png', 'hud_gaode_car_5': 'res/jb5.png',
    'hud_gaode_car_6': 'res/rjB.png', 'hud_gaode_car_7': 'res/Lub.png',
    'hud_gaode_car_8': 'res/_rj.png', 'hud_gaode_car_9': 'res/PQH.png',
    'hud_gaode_car_10': 'res/Vhp.png', 'hud_gaode_car_11': 'res/yrL.png',
    'hud_gaode_car_12': 'res/owr.png', 'hud_gaode_car_13': 'res/MLl.png',
    'hud_gaode_car_18': 'res/Jr_.png', 'hud_gaode_car_19': 'res/j-9.png',
    'hud_baidu_car_1': 'res/KFZ.png', 'hud_baidu_car_2': 'res/ENC.png',
    'hud_baidu_car_7': 'res/MDm.png', 'hud_baidu_car_12': 'res/VBq.png',
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


class Image:
    def __init__(self, path, expected):
        self.data = path.read_bytes()
        if sha(self.data) != expected or struct.unpack_from('<I', self.data)[0] != 0xfeedfacf:
            raise ValueError(f'original image identity mismatch: {path}')
        self.segments = []
        offset = 32
        for _ in range(struct.unpack_from('<I', self.data, 16)[0]):
            command, size = struct.unpack_from('<II', self.data, offset)
            if command == 0x19:
                self.segments.append(struct.unpack_from('<QQQQ', self.data, offset + 24))
            offset += size

    def read(self, address, length):
        for vm, _, offset, size in self.segments:
            if vm <= address and address + length <= vm + size:
                return self.data[offset + address - vm:offset + address - vm + length]
        raise ValueError(f'unmapped address {address:#x} size {length}')

    def chained_pointer(self, raw):
        # These reviewed dyld CFString slots contain non-auth rebase pointers.
        # Validate the decoded target against the original image's file segments.
        if raw >> 63 or (raw >> 62) & 1:
            raise ValueError('unexpected authenticated or bound pointer')
        target = 0x180000000 + (raw & 0xfffffffff)
        self.read(target, 1)
        return target

    def enum_table(self, start, count):
        result = {}
        for index in range(count):
            slot = start + 8 * index
            raw, = struct.unpack('<Q', self.read(slot, 8))
            cf = self.chained_pointer(raw)
            values = struct.unpack('<QQQQ', self.read(cf, 32))
            target = self.chained_pointer(values[2])
            if not 0 < values[3] < 128:
                raise ValueError('unexpected CFString length')
            text = self.read(target, values[3]).decode('ascii')
            result[str(index)] = {'slot': hex(slot), 'raw': hex(raw),
                                  'cfstring': hex(cf), 'text_address': hex(target), 'text': text}
        return result

    def call_target(self, address):
        instruction, = struct.unpack('<I', self.read(address, 4))
        if instruction >> 26 != 0b100101:
            raise ValueError(f'expected original BL at {address:#x}')
        displacement = instruction & 0x3ffffff
        if displacement & 0x2000000:
            displacement -= 0x4000000
        return address + 4 * displacement

    def route_u32_path(self, parameter, start, expected_key_target, key_slot):
        # Reviewed six-instruction sender path: select key, lookup snapshot value,
        # move it to x3, select parameter ID, append through the same U32 helper.
        for address, register in ((start, 0), (start + 16, 2)):
            instruction, = struct.unpack('<I', self.read(address, 4))
            if instruction != 0x52800000 | (parameter << 5) | register:
                raise ValueError(f'original p{parameter} MOVZ differs at {address:#x}')
        expected_calls = {start + 4: 0x100003b18, start + 8: 0x100012120,
                          start + 12: 0x1000153bc, start + 20: 0x100004650}
        calls = {address: self.call_target(address) for address in expected_calls}
        if calls != expected_calls:
            raise ValueError(f'original p{parameter} encoder call targets differ')
        relative, = struct.unpack('<i', self.read(0x100003d60 + (parameter - 1) * 4, 4))
        if 0x100003b5c + relative != expected_key_target:
            raise ValueError(f'original p{parameter} key jump differs')
        return {'parameter': parameter, 'encoder_start': hex(start), 'payload_bytes': 4,
                'encoder_sha256': sha(self.read(start, 24)),
                'call_targets': {hex(address): hex(target) for address, target in calls.items()},
                'key_jump_target': hex(expected_key_target), 'key_slot': hex(key_slot),
                'key_branch_sha256': sha(self.read(expected_key_target, 12))}


def inspect(apk):
    result = {'schema': 2, 'date': '2026-11-11',
              'scope': 'Original byte identity; no universal meter/order or vehicle claim',
              'apple': {}, 'carwith': {}}
    for label, (path, digest, slices) in APPLE.items():
        image = Image(ROOT / path, digest)
        entry = {'path': path, 'sha256': digest, 'slices': {
            hex(start): {'end': hex(end), 'bytes': end - start,
                         'sha256': sha(image.read(start, end - start))}
            for start, end in slices}}
        if label == 'CarPlay':
            entry['guidance_states'] = image.enum_table(0x2690da898, 7)
            entry['maneuver_types'] = image.enum_table(0x2690da6a8, 54)
        else:
            entry['route_key_jump_targets'] = {
                str(i + 1): hex(0x100003b5c + struct.unpack('<i', image.read(0x100003d60 + i * 4, 4))[0])
                for i in range(26)}
            entry['maneuver_key_jump_targets'] = {
                str(i + 1): hex(0x1000de340 + struct.unpack('<i', image.read(0x100018f98 + i * 4, 4))[0])
                for i in range(13)}
            entry['route_u32_paths'] = {
                'distance_remaining': image.route_u32_path(7, 0x100002b94, 0x100003c4c, 0x10023dc10),
                'distance_to_maneuver': image.route_u32_path(10, 0x100002bfc, 0x100003bb0, 0x10023dc28),
            }
        result['apple'][label] = entry
    if sha(apk.read_bytes()) != CARWITH_SHA:
        raise ValueError('CarWith original APK identity mismatch')
    with zipfile.ZipFile(apk) as archive:
        data = archive.read('classes2.dex')
        owners = dex_methods(data)
        methods = {}
        for offset, expected in METHODS.items():
            resolved = owners.get(offset)
            if resolved is None or resolved[:2] != expected:
                raise ValueError(f'CarWith method ownership mismatch: {offset:#x}: {resolved}')
            units, = struct.unpack_from('<I', data, offset + 12)
            code = data[offset + 16:offset + 16 + 2 * units]
            if not units or len(code) != 2 * units:
                raise ValueError('invalid instruction bounds')
            methods[hex(offset)] = {'owner': resolved[0], 'method': resolved[1],
                                    'prototype': resolved[2], 'code_units': units,
                                    'insns_sha256': sha(code)}
        result['carwith'] = {
            'version': '4.0.14-20260801', 'apk_sha256': CARWITH_SHA,
            'classes2_sha256': sha(data), 'methods': methods,
            'resources_arsc_sha256': sha(archive.read('resources.arsc')),
            'reviewed_icons': {name: {'entry': path, 'sha256': sha(archive.read(path))}
                               for name, path in ICONS.items()}}
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('carwith_apk', type=Path)
    parser.add_argument('--write', action='store_true')
    args = parser.parse_args()
    observed = inspect(args.carwith_apk)
    if args.write:
        RECORD.write_text(json.dumps(observed, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    elif observed != json.loads(RECORD.read_text(encoding='utf-8')):
        raise ValueError('reviewed navigation byte record differs')
    print('PASS: 2 Apple images, 7 guidance states, 54 maneuver types, key jump tables, p7/p10 U32 paths;')
    print('PASS: CarWith APK, 7 method owners/instruction hashes and 18 reviewed icon hashes.')
    print('No vendor execution, universal unit/order or vehicle validation.')


if __name__ == '__main__':
    main()

"""Recheck original navigation field investigation bytes without vendor execution.

Pins APK/DEX method ownership and instruction hashes, Apple symbols and reviewed
slices. This is a byte identity check; source roles, shared-cache text semantics,
route overview, lanes and vehicle acceptance remain separate OPEN requirements.
"""
import argparse
import json
import struct
import zipfile
from pathlib import Path

from inspect_galaxyplay_receiver import dex_methods
from inspect_navigation_numeric_core import APPLE, Image, sha

ROOT = Path(__file__).resolve().parents[3]
RECORD = ROOT / 'research/connection/evidence/galaxyplay-navigation-fields-20261112.json'
INPUTS = {
    'carwith': ('c897a45d92c84f06e670fc4edd323824093a093f67d8e7d7b058fee2a737d06c', {
        'classes.dex': {0x46ef90: ('Le2/d$a;', 'invokeMethod')},
        'classes2.dex': {
            0x1bb4b0: ('Lcom/carwith/launcher/map/m$a;', 'a'),
            0x17abdc: ('Lcom/carwith/launcher/LauncherDataBusClient;', 'F'),
            0x17af64: ('Lcom/carwith/launcher/LauncherDataBusClient;', 'G')},
        'classes4.dex': {
            0x122648: ('Lcom/miui/carlink/databus/p2cdatastructure/NavigationInfo;', '<init>'),
            0x122584: ('Lcom/miui/carlink/databus/p2cdatastructure/NavigationInfo;', 'i')},
        'classes6.dex': {
            0xa65c4: ('Lcom/xiaomi/ucar/carlife/CarlifeConnService$CarLifeCastManagerImpl;', 'invokeMethod'),
            0xa751c: ('Lcom/xiaomi/ucar/carlife/k;', 'r'),
            0xa7e14: ('Lcom/xiaomi/ucar/carlife/k;', 's')},
    }),
    'amap': ('768d62ee138771c0f1d1a08c68151a0e41f66bda2ada1c559e07ebb09b65857c', {
        'classes4.dex': {0x5ab8c0: ('Lmv;', 'notifyOngoingCard'), 0x3f6e04: ('Lew6;', 'e')},
        'classes8.dex': {0x35eed8: ('Lgv6;', 'a')},
    }),
    'galaxyplay': ('f106680faa27be5a9dfc4a9a9b9cb59239e4512c5f3b73b64cebfec47bb023e6', {
        'classes2.dex': {address: ('Lcom/shilapi/xcertplay/hud/CarPlayNavigationInput;', name)
                         for address, name in [(0x245e4, 'text'), (0x24810, 'reset'),
                                               (0x24858, 'updateManeuver'), (0x249f0, 'updateRoute')]},
    }),
}
CAR_KIT = 'firmware/extracted/24A446/binaries/CarKitNavigation/CarKitNavigation'
CAR_KIT_SHA = 'df991f16ab607f32f090612463e8f1a18c96c3f14407dace74053b645f3f2e47'
SYMBOLS = {
    '-[ACCNavigationAccessoryComponent(CarPlay) CP_variantFittingCurrentRoadName:]': 0x22b03d15c,
    '+[ACCNavigationAccessoryComponent(CarPlay) CP_variant:fittingMaxLength:]': 0x22b03d3d8,
    '-[ACCNavigationAccessoryComponent(CarPlay) CP_variantFittingPostManeuverRoadName:]': 0x22b03ffa8,
    '-[NSString(ACCNavigation) stringByEllipsingPastMaxLength:]': 0x22b040144,
}
ACCESSORY_SLICES = [
    (0x1000041bc, 0x100004428), (0x1000c5704, 0x1000c5d64),
    (0x1000dd220, 0x1000dd514), (0x100003b28, 0x100003dc8),
    (0x1000de30c, 0x1000de4a8), (0x100018f98, 0x100018fcc),
    (0x1000de8b8, 0x1000de958), (0x1000dec88, 0x1000ded58),
]


def symbols(data):
    result = {}
    position = 32
    for _ in range(struct.unpack_from('<I', data, 16)[0]):
        command, size = struct.unpack_from('<II', data, position)
        if command == 2:
            symoff, count, stroff, _ = struct.unpack_from('<IIII', data, position + 8)
            for index in range(count):
                strx, _, _, _, value = struct.unpack_from('<IBBHQ', data, symoff + index * 16)
                start = stroff + strx
                name = data[start:data.index(b'\0', start)].decode('utf8')
                if name in SYMBOLS:
                    result[name] = value
        position += size
    if result != SYMBOLS:
        raise ValueError('original CarKitNavigation symbol/address mismatch')
    return result


def slices(image, ranges):
    return {hex(start): {'end': hex(end), 'bytes': end - start,
                         'sha256': sha(image.read(start, end - start))} for start, end in ranges}


def inspect(paths):
    result = {'schema': 1, 'date': '2026-11-12',
              'scope': 'Local byte identity; no display unit, source role or vehicle claim', 'apks': {}}
    for label, path in paths.items():
        digest, entries = INPUTS[label]
        if sha(path.read_bytes()) != digest:
            raise ValueError(f'{label} original APK identity mismatch')
        dexes = {}
        with zipfile.ZipFile(path) as archive:
            for name, methods in entries.items():
                data = archive.read(name)
                owners = dex_methods(data)
                checked = {}
                for address, expected in methods.items():
                    resolved = owners.get(address)
                    if resolved is None or resolved[:2] != expected:
                        raise ValueError(f'{label}/{name} ownership mismatch at {address:#x}')
                    units, = struct.unpack_from('<I', data, address + 12)
                    code = data[address + 16:address + 16 + 2 * units]
                    if not units or len(code) != 2 * units:
                        raise ValueError('invalid original DEX instruction bounds')
                    checked[hex(address)] = {'owner': resolved[0], 'method': resolved[1],
                                            'prototype': resolved[2], 'code_units': units,
                                            'insns_sha256': sha(code)}
                dexes[name] = {'sha256': sha(data), 'methods': checked}
        result['apks'][label] = {'sha256': digest, 'dexes': dexes}
    path, digest, _ = APPLE['accessoryd']
    result['accessoryd'] = {'path': path, 'sha256': digest,
                            'slices': slices(Image(ROOT / path, digest), ACCESSORY_SLICES)}
    kit = Image(ROOT / CAR_KIT, CAR_KIT_SHA)
    result['CarKitNavigation'] = {
        'path': CAR_KIT, 'sha256': CAR_KIT_SHA,
        'symbols': {name: hex(address) for name, address in symbols(kit.data).items()},
        'slices': slices(kit, [(0x22b03d15c, 0x22b03d3d8), (0x22b03d3d8, 0x22b03d594),
                               (0x22b03ffa8, 0x22b040018), (0x22b040144, 0x22b040280)]),
    }
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for label in INPUTS:
        parser.add_argument(label + '_apk', type=Path)
    parser.add_argument('--write', action='store_true')
    args = parser.parse_args()
    result = inspect({label: getattr(args, label + '_apk') for label in INPUTS})
    if args.write:
        RECORD.write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf8')
    elif result != json.loads(RECORD.read_text(encoding='utf8')):
        raise ValueError('reviewed navigation field byte record differs')
    print('PASS: 3 original APKs, 16 DEX method owners/instruction hashes; 2 Apple images, 4 symbols, 12 slices.')
    print('No vendor execution, shared-cache semantic closure or vehicle validation.')


if __name__ == '__main__':
    main()

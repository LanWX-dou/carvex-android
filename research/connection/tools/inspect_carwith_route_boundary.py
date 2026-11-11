"""Pin the supplied Amap/CarWith navigation IPC boundary to original DEX bytes.

Full APKs, disassembly and device logs remain local. These checks verify source
identity and the reviewed null-title/query instructions, not vehicle behavior.
"""
import argparse
import hashlib
import json
import struct
import zipfile
from pathlib import Path

from inspect_galaxyplay_receiver import dex_methods, uleb

RECORD = Path(__file__).resolve().parents[1] / 'evidence/carwith-amap-route-boundary-20261111.json'
SOURCES = {
    'amap': {
        'sha256': '768d62ee138771c0f1d1a08c68151a0e41f66bda2ada1c559e07ebb09b65857c',
        'identity': {'package': 'com.autonavi.minimap', 'version_name': '17.02.0.2010', 'version_code': 170200},
        'methods': {
            'classes4.dex': {
                0x27c038: ('Lcom/amap/bundle/drive/carprojection/module/AjxModuleCarProjection;', 'getIAjxModuleCar'),
                0x27d8e0: ('Lcom/amap/bundle/drive/carprojection/module/AjxModuleCarProjection;', 'notifyOngoingCard'),
                0x5ab8c0: ('Lmv;', 'notifyOngoingCard'),
                0x3f6d08: ('Lew6;', 'd'),
            },
            'classes8.dex': {
                0x35eed8: ('Lgv6;', 'a'),
                0x2d5614: ('Lcom/ucar/map/connect/UCarMapConnector;', 'f'),
                0x482204: ('Lcom/ucar/map/IUCarMapService$Stub$Proxy;', 'showNavInfo'),
            },
        },
    },
    'carwith': {
        'sha256': 'c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e',
        'identity': {'package': 'com.miui.carlink', 'version_name': '4.0.14-20260801'},
        'methods': {
            'classes2.dex': {
                0x1af960: ('Lcom/carwith/launcher/map/m$a;', 'a'),
                0x16fc3c: ('Lcom/carwith/launcher/LauncherDataBusClient;', 'E'),
                0x16ffc4: ('Lcom/carwith/launcher/LauncherDataBusClient;', 'F'),
                0x170050: ('Lcom/carwith/launcher/LauncherDataBusClient;', 'G'),
            },
            'classes4.dex': {
                0x10f6bc: ('Lcom/miui/carlink/databus/DataBusService$DataBusServiceStub;', 'sendNavigationInfoToCar'),
                0x10efc0: ('Lcom/miui/carlink/databus/ControlChannel;', 'sendNavigationInfo'),
                0x11c4d0: ('Lcom/miui/carlink/databus/p2cdatastructure/NavigationInfo;', '<init>'),
            },
            'classes5.dex': {
                0x1bf334: ('Lcom/ucar/map/UCarMapInfo;', 'fromBundle'),
                0x1c06f0: ('Lcom/ucar/map/service/mapservice/IUCarMapServiceStub;', 'showNavInfo'),
                0x1c02b0: ('Lcom/ucar/map/service/mapservice/IUCarMapServiceStub;', 'getValue'),
            },
            'classes8.dex': {
                0x1594b8: ('Lnet/easyconn/carman/bridge/BMapBridge;', '<init>'),
                0x1593dc: ('Lnet/easyconn/carman/bridge/BMapBridge;', 'getNavigationInfo'),
            },
        },
    },
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def dex_string(data, index):
    count, table = struct.unpack_from('<II', data, 0x38)
    if not 0 <= index < count:
        raise ValueError('string index outside DEX table')
    offset, = struct.unpack_from('<I', data, table + 4 * index)
    _, start = uleb(data, offset)
    return data[start:data.index(b'\0', start)].decode('utf-8', errors='replace')


def reviewed_boundaries(label, name, data):
    if label == 'amap' and name == 'classes8.dex':
        # Original gv6.a: both keys use v2, set to null at code unit 0x30.
        if data[0x35ef48:0x35ef4a] != bytes.fromhex('1202'):
            raise ValueError('TITLE_1 null register changed')
        for address, key in ((0x35ef42, 'ucar.map.bundle.TITLE_1'),
                             (0x35ef50, 'ucar.map.bundle.TITLE_2')):
            if data[address:address+2] != bytes.fromhex('1b01'):
                raise ValueError('expected const-string/jumbo into v1')
            index, = struct.unpack_from('<I', data, address+2)
            if dex_string(data, index) != key:
                raise ValueError('reviewed navigation title key changed')
        call = bytes.fromhex('6e30 7605 1002')
        if data[0x35ef4a:0x35ef50] != call or data[0x35ef56:0x35ef5c] != call:
            raise ValueError('null title putString calls changed')
    if label == 'carwith' and name == 'classes5.dex':
        if data[0x1c02c0:0x1c02c4] != bytes.fromhex('1200 1100'):
            raise ValueError('reviewed getValue no longer returns null')


def inspect(path, label):
    spec = SOURCES[label]
    raw = path.read_bytes()
    if sha(raw) != spec['sha256']:
        raise ValueError(f'{label} APK differs from reviewed input')
    result = {'apk_sha256': sha(raw), 'bytes': len(raw),
              'manifest_identity_review': spec['identity'], 'dex': {}}
    with zipfile.ZipFile(path) as z:
        result['manifest_sha256'] = sha(z.read('AndroidManifest.xml'))
        result['dex_count'] = sum(n.endswith('.dex') for n in z.namelist())
        for name, methods in spec['methods'].items():
            data = z.read(name)
            owners = dex_methods(data)
            reviewed_boundaries(label, name, data)
            entry = {'sha256': sha(data), 'bytes': len(data), 'methods': {}}
            for address, expected in methods.items():
                actual = owners.get(address)
                if actual is None or actual[:2] != expected:
                    raise ValueError(f'{label} {name} {address:#x}: method ownership differs: {actual}')
                registers, inputs, outputs, tries, debug, units = struct.unpack_from('<HHHHII', data, address)
                instructions = data[address+16:address+16+units*2]
                if not units or len(instructions) != units*2:
                    raise ValueError('invalid instruction bounds')
                entry['methods'][hex(address)] = {
                    'descriptor': actual[0], 'method': actual[1], 'prototype': actual[2],
                    'code_units': units, 'registers': registers, 'inputs': inputs,
                    'outputs': outputs, 'insns_sha256': sha(instructions),
                }
            result['dex'][name] = entry
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--amap', type=Path, required=True)
    parser.add_argument('--carwith', type=Path, required=True)
    parser.add_argument('--write', action='store_true')
    args = parser.parse_args()
    observed = {
        'schema': 1, 'date': '2026-11-11',
        'scope': 'Original producer/IPC byte boundaries; no route-distance fix or runtime claim',
        'amap': inspect(args.amap, 'amap'), 'carwith': inspect(args.carwith, 'carwith'),
        'instruction_checks': {'amap_ucar_titles_explicit_null': True,
                               'carwith_ucar_get_value_returns_null': True},
    }
    if args.write:
        RECORD.write_text(json.dumps(observed, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
    elif observed != json.loads(RECORD.read_text(encoding='utf-8')):
        raise ValueError('recorded method identity or instruction hashes differ')
    count = sum(len(dex['methods']) for label in ('amap', 'carwith') for dex in observed[label]['dex'].values())
    print(f'PASS: 2 APK identities, {count} method owners/instruction hashes, explicit null titles and null query')
    print('No application, device log or vehicle execution was performed.')


if __name__ == '__main__':
    main()

"""Verify local MiAuto navigation signatures against original ICCOA/CarWith DEX.

Reads the external checkout and APKs without executing vendor code. Full SDKs,
APKs and disassembly remain local; the record contains reviewed metadata only.
"""
import argparse
import hashlib
import json
import struct
import subprocess
import zipfile
from pathlib import Path

from inspect_carwith_route_boundary import inspect as inspect_route_boundary
from inspect_galaxyplay_receiver import dex_methods, uleb

RECORD = Path(__file__).resolve().parents[1] / 'evidence/miauto-carwith-navigation-20261111.json'
MIAUTO_HEAD = '8ee36108ab74a58cbb0ef5c305e813a5f2fd8f41'
NAV = 'Lcom/ucar/vehiclesdk/UCarCommon$NavigationInfo;'
FIELDS = {
    'ISNAVIGATING_FIELD_NUMBER': 1, 'DIRECTIONICON_FIELD_NUMBER': 2,
    'DISTANCE_FIELD_NUMBER': 3, 'DISTANCEUNIT_FIELD_NUMBER': 4,
    'OPERATION_FIELD_NUMBER': 5, 'WHERE_FIELD_NUMBER': 6,
    'TITLE1_FIELD_NUMBER': 7, 'TITLE2_FIELD_NUMBER': 8, 'ID_FIELD_NUMBER': 9,
}
APKS = {
    'carwith': {
        'sha256': 'c7888ec5018b4e279ed3d3395b8c855d2a3571f06ae26b96849a61ad6dbef00e',
        'dex': 'classes4.dex',
        'proto': 'Lcom/miui/carlink/databus/proto/UCarProto$NotifyNavigationInfo;',
        'schema_instruction': 0x1441d0,
        'message_id_instruction': 0x16bd00,
        'methods': {
            0x10efc0: ('Lcom/miui/carlink/databus/ControlChannel;', 'sendNavigationInfo'),
            0x10f6bc: ('Lcom/miui/carlink/databus/DataBusService$DataBusServiceStub;', 'sendNavigationInfoToCar'),
            0x144120: ('Lcom/miui/carlink/databus/proto/UCarProto$NotifyNavigationInfo;', 'dynamicMethod'),
            0x16bcdc: ('Lda/j;', 'B'),
        },
    },
    'factory': {
        'sha256': '043866ed5e719fd1617ef57f4060c0fd7030e02df70433c5f5d0f518bf1946af',
        'dex': 'classes3.dex',
        'proto': 'Lcom/ucar/databus/proto/UCarProto$NotifyNavigationInfo;',
        'schema_instruction': 0x1e9f06,
        'message_id_instruction': 0x220224,
        'methods': {
            0x1e9e18: ('Lcom/ucar/databus/proto/UCarProto$NotifyNavigationInfo;', 'dynamicMethod'),
            0x220214: ('Lcom/ucar/vehiclesdk/t2;', 'H'),
            0x218954: ('Lcom/ucar/vehiclesdk/l0;', 'r'),
            0x2185a0: ('Lcom/ucar/vehiclesdk/l0;', 'l'),
            0x1fc088: (NAV, '<init>'),
            0x1f3bf8: ('Lcom/ucar/vehiclesdk/UCarAdapter$d;', 'a'),
            0x1f7038: ('Lcom/ucar/vehiclesdk/UCarAdapter;', 'a'),
            0x1f821c: ('Lcom/ucar/vehiclesdk/UCarAdapter;', 'b'),
            0x1f32f0: ('Lcom/ucar/vehiclesdk/UCarAdapter$$ExternalSyntheticLambda3;', 'run'),
            0x1f69a8: ('Lcom/ucar/vehiclesdk/UCarAdapter;', '$r8$lambda$F9vZXGRn2fRuRpHxFkA5MCyET2Y'),
            0x1f798c: ('Lcom/ucar/vehiclesdk/UCarAdapter;', 'a'),
        },
    },
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def dex_tables(data):
    count, table = struct.unpack_from('<II', data, 0x38)
    strings = []
    for i in range(count):
        offset, = struct.unpack_from('<I', data, table + i * 4)
        _, offset = uleb(data, offset)
        raw = data[offset:data.index(b'\0', offset)]
        strings.append(raw.replace(b'\xc0\x80', b'\0').decode('utf-8', errors='surrogatepass'))
    count, table = struct.unpack_from('<II', data, 0x40)
    types = [strings[struct.unpack_from('<I', data, table + i * 4)[0]] for i in range(count)]
    return strings, types


def dex_fields(data, descriptor, strings, types):
    count, table = struct.unpack_from('<II', data, 0x60)
    field_table, = struct.unpack_from('<I', data, 0x54)
    matches = [table + i * 32 for i in range(count)
               if types[struct.unpack_from('<I', data, table + i * 32)[0]] == descriptor]
    if len(matches) != 1:
        raise ValueError('expected one class definition for ' + descriptor)
    offset, values_offset = struct.unpack_from('<II', data, matches[0] + 24)
    counts = []
    for _ in range(4):
        value, offset = uleb(data, offset)
        counts.append(value)
    values = []
    if values_offset:
        size, values_offset = uleb(data, values_offset)
        for _ in range(size):
            tag = data[values_offset]
            values_offset += 1
            kind, width = tag & 31, (tag >> 5) + 1
            if kind == 0x1e:  # VALUE_NULL
                values.append(None)
            elif kind == 4:  # VALUE_INT
                values.append(int.from_bytes(data[values_offset:values_offset+width], 'little', signed=True))
                values_offset += width
            else:
                raise ValueError('unexpected reviewed static value type')
    result = {'static': {}, 'instance': {}}
    for group, size in zip(result, counts[:2]):
        index = 0
        for i in range(size):
            delta, offset = uleb(data, offset)
            index += delta
            flags, offset = uleb(data, offset)
            owner, field_type, name = struct.unpack_from('<HHI', data, field_table + index * 8)
            if types[owner] != descriptor:
                raise ValueError('field ownership changed')
            result[group][strings[name]] = {'type': types[field_type], 'access_flags': flags}
            if group == 'static':
                result[group][strings[name]]['value'] = values[i] if i < len(values) else None
    return result


def class_methods(data):
    """Read signature-only class metadata; do not load/execute the stub classes."""
    if data[:4] != b'\xca\xfe\xba\xbe':
        raise ValueError('not a JVM class')
    offset = 8

    def take(fmt):
        nonlocal offset
        value = struct.unpack_from('>' + fmt, data, offset)
        offset += struct.calcsize('>' + fmt)
        return value

    size, = take('H')
    pool = [None] * size
    index = 1
    while index < size:
        tag, = take('B')
        if tag == 1:
            length, = take('H')
            pool[index] = data[offset:offset+length].decode('utf-8', errors='replace')
            offset += length
        else:
            widths = {3: 4, 4: 4, 5: 8, 6: 8, 7: 2, 8: 2, 9: 4, 10: 4, 11: 4,
                      12: 4, 15: 3, 16: 2, 17: 4, 18: 4, 19: 2, 20: 2}
            if tag not in widths:
                raise ValueError('unsupported constant pool entry')
            offset += widths[tag]
            if tag in (5, 6):
                index += 1
        index += 1
    take('HHH')  # access, this, super
    count, = take('H')
    offset += count * 2
    result = {}
    for category in ('fields', 'methods'):
        count, = take('H')
        rows = []
        for _ in range(count):
            flags, name, descriptor, attributes = take('HHHH')
            names = []
            for _ in range(attributes):
                attribute, length = take('HI')
                names.append(pool[attribute])
                offset += length
            rows.append({'name': pool[name], 'descriptor': pool[descriptor], 'access_flags': flags,
                         'has_constant_value': 'ConstantValue' in names})
        result[category] = rows
    return result


def inspect_miauto(root):
    head = subprocess.run(['git', '-C', str(root), 'rev-parse', 'HEAD'], check=True,
                          capture_output=True, text=True).stdout.strip()
    if head != MIAUTO_HEAD:
        raise ValueError('MiAuto commit differs from reviewed checkout')
    files = ('app/src/main/java/com/miauto/app/IccoaManager.java',
             'app/src/main/java/com/andrerinas/openheadunit/connection/IcocaBridge.kt',
             'app/libs/README.md', 'app/stubs/icar-sdk-stubs.jar')
    result = {'commit': head, 'files': {name: sha((root / name).read_bytes()) for name in files}}
    result['runtime_dex_present'] = (root / 'app/libs/icar-sdk.dex').is_file()
    result['stub_classes'] = {}
    with zipfile.ZipFile(root / 'app/stubs/icar-sdk-stubs.jar') as archive:
        for name in ('com/ucar/vehiclesdk/UCarCommon$NavigationInfo.class',
                     'com/ucar/vehiclesdk/IPhoneDataListener.class',
                     'com/ucar/databus/proto/UCarProto$NotifyNavigationInfo.class'):
            result['stub_classes'][name] = class_methods(archive.read(name))
    proto_fields = result['stub_classes']['com/ucar/databus/proto/UCarProto$NotifyNavigationInfo.class']['fields']
    if any(row['has_constant_value'] or row['access_flags'] & 0x10 for row in proto_fields):
        raise ValueError('stub field stripping differs; re-review numeric constants')
    return result


def inspect_apk(path, label):
    spec = APKS[label]
    raw = path.read_bytes()
    if sha(raw) != spec['sha256']:
        raise ValueError(label + ' APK identity differs')
    with zipfile.ZipFile(path) as archive:
        data = archive.read(spec['dex'])
    strings, types = dex_tables(data)
    contract = dex_fields(data, spec['proto'], strings, types)
    numbers = {name: row['value'] for name, row in contract['static'].items() if name.endswith('_FIELD_NUMBER')}
    if numbers != FIELDS:
        raise ValueError('navigation field numbers differ')
    address = spec['schema_instruction']
    if data[address] != 0x1a:
        raise ValueError('reviewed schema constant instruction changed')
    index, = struct.unpack_from('<H', data, address + 2)
    schema = [ord(c) for c in strings[index]]
    address = spec['message_id_instruction']
    if data[address:address+4] != bytes.fromhex('1301 0b00' if label == 'carwith' else '1300 0b00'):
        raise ValueError('navigation message ID changed')
    owners = dex_methods(data)
    methods = {}
    for address, expected in spec['methods'].items():
        actual = owners.get(address)
        if actual is None or actual[:2] != expected:
            raise ValueError(f'{label} {address:#x}: ownership differs: {actual}')
        units, = struct.unpack_from('<I', data, address + 12)
        methods[hex(address)] = {'owner': actual[0], 'name': actual[1], 'prototype': actual[2],
                                 'code_units': units, 'insns_sha256': sha(data[address+16:address+16+units*2])}
    if label == 'factory':
        # l0.r packed switch: message IDs 6..11; ID 11 jumps to l0.l at code unit 0x4a.
        signature, size, first = struct.unpack_from('<HHi', data, 0x218a88)
        targets = list(struct.unpack_from('<' + 'i' * size, data, 0x218a90))
        if (signature, size, first, 0x31 + targets[5]) != (0x100, 6, 6, 0x4a):
            raise ValueError('receiver navigation dispatch changed')
    return {'apk_sha256': sha(raw), 'dex_name': spec['dex'], 'dex_sha256': sha(data),
            'message_id': 11, 'fields': contract, 'proto_schema_codepoints': schema, 'methods': methods}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--miauto', type=Path, required=True)
    parser.add_argument('--carwith', type=Path, required=True)
    parser.add_argument('--factory', type=Path, required=True)
    parser.add_argument('--write', action='store_true')
    args = parser.parse_args()
    result = {'schema': 1, 'date': '2026-11-11',
              'scope': 'MiAuto source/stub signatures, original CarWith producer and separate factory SDK receiver',
              'miauto': inspect_miauto(args.miauto), 'carwith': inspect_apk(args.carwith, 'carwith'),
              'factory': inspect_apk(args.factory, 'factory')}
    if result['carwith']['proto_schema_codepoints'] != result['factory']['proto_schema_codepoints']:
        raise ValueError('producer and receiver protobuf schemas differ')
    # Also retain the previously reviewed producer boundary checks.
    result['carwith_ucar_boundary'] = inspect_route_boundary(args.carwith, 'carwith')
    if args.write:
        RECORD.write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    elif result != json.loads(RECORD.read_text(encoding='utf-8')):
        raise ValueError('source or byte evidence differs from reviewed record')
    print('PASS: MiAuto source/stub signatures; identical 9-field original schemas; message 11 producer/receiver dispatch')
    print('Static verification only; full-route distance source and vehicle fix remain unverified.')


if __name__ == '__main__':
    main()

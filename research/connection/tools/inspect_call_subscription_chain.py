"""Pin original Apple call subscription tables, handler slices and mode branches.

Byte checks do not establish an Android per-call metadata or cellular PCM source.
"""
import argparse
import json
import struct

from inspect_navigation_numeric_core import ROOT, Image, sha

RECORD = ROOT / 'research/connection/evidence/call-subscription-chain-20261111.json'
IMAGE = 'research/protocol/iap2_input_business_lifecycle/source/firmware/accessoryd'
DIGEST = '2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe'
SLICES = [
    (0x10011e6e4, 0x10011eb34), (0x10011ec18, 0x10011ece4),
    (0x10011ece4, 0x10011f020), (0x10011f020, 0x10011f0e0),
    (0x1001208f8, 0x10012114c), (0x1000186a8, 0x1000186dc),
]


def inspect():
    image = Image(ROOT / IMAGE, DIGEST)
    result = {'schema': 1, 'date': '2026-11-11', 'path': IMAGE, 'sha256': DIGEST,
              'scope': 'Original byte identity, declarations and mode branches; no provider or vehicle test',
              'slices': {hex(start): {'end': hex(end), 'sha256': sha(image.read(start, end-start))}
                         for start, end in SLICES},
              'required_groups': {}}
    for label, address, ids in [
        ('call', 0x1001b3158, [0x4154, 0x4155, 0x4156]),
        ('communications', 0x1001b317c, [0x4157, 0x4158, 0x4159]),
    ]:
        entries = [struct.unpack('<III', image.read(address + 12*i, 12)) for i in range(3)]
        if entries != [(ids[0], 0, 1), (ids[1], 1, 1), (ids[2], 0, 0)]:
            raise ValueError(f'unexpected original required message table: {label}: {entries}')
        result['required_groups'][label] = {'address': hex(address), 'entries': entries}
    legacy = struct.unpack('<6I', image.read(0x1001b3248, 24))
    if legacy != (3, 3, 1, 1, 2, 1):
        raise ValueError('legacy status table differs')
    result['legacy_status_table'] = {'address': '0x1001b3248', 'values_for_1_to_6': legacy}
    result['call_parameter_jump_targets'] = {
        str(i): hex(0x100120c34 + struct.unpack('<i', image.read(0x1000186a8 + i*4, 4))[0])
        for i in range(13)}
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--write', action='store_true')
    args = parser.parse_args()
    observed = inspect()
    # Normalize tuples to the JSON representation for exact comparison.
    observed = json.loads(json.dumps(observed))
    if args.write:
        RECORD.write_text(json.dumps(observed, indent=2) + '\n', encoding='utf-8')
    elif observed != json.loads(RECORD.read_text(encoding='utf-8')):
        raise ValueError('call subscription byte record differs')
    print('PASS: original accessoryd, 2 required message groups, 6 slices, legacy table and parameter jump targets')
    print('No Android per-call provider, cellular downlink or vehicle validation.')


if __name__ == '__main__':
    main()

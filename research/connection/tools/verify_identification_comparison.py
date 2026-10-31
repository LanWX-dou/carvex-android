"""Read-only chapter80 integrity verifier; run under WSL with Capstone.

Checks original bytes, function boundaries, table decoding and reviewed input
snapshots. Does not execute Apple code, infer semantics or test a vehicle.
"""
import bisect
import hashlib
import json
import struct
import sys
from pathlib import Path

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(DOC.parent / 'firmware/tools/ipsw-research'))
from firmware_image import Image
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN


def path(value):
    value = value.replace('\\', '/')
    if sys.platform != 'win32' and len(value) > 2 and value[1] == ':':
        value = '/mnt/' + value[0].lower() + value[2:]
    return Path(value)


def sha(value):
    return hashlib.sha256(value).hexdigest()


def main():
    ev = json.loads((DOC / 'evidence/identification-three-way-audit.json').read_text(encoding='utf-8'))
    im = Image(path(ev['firmware']['path']))
    assert sha(im.data) == ev['firmware']['sha256'], 'firmware changed'
    decoder = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    instruction_count = 0
    for row in ev['functions']:
        at, end = int(row['address'], 0), int(row['end'], 0)
        assert at in im.starts and im.starts[bisect.bisect_right(im.starts, at)] == end
        raw = im.read(at, end - at)
        assert sha(raw) == row['sha256'], row['address']
        for cache in row['cache_matches']:
            assert path(cache).read_bytes() == raw, cache
        decoded = [f'{i.address:#x}: {i.bytes.hex()} {i.mnemonic} {i.op_str}' for i in decoder.disasm(raw, at)]
        assert decoded == row['assembly'], row['address']
        instruction_count += len(decoded)
    spans = 0
    def check_span(row):
        nonlocal spans
        raw = im.read(int(row['address'], 0), row['length'])
        assert sha(raw) == row['sha256'] and raw.hex() == row['raw_hex']
        spans += 1
        return raw
    for group in ev['tables']['groups']:
        raw = check_span(group['raw'])
        for n, message in enumerate(group['messages']):
            mid = struct.unpack_from('<H', raw, n * 12)[0]
            direction = struct.unpack_from('<I', raw, n * 12 + 4)[0]
            assert f'0x{mid:04x}' == message['message_id']
            assert direction == message['direction']
            assert raw[n * 12 + 8] == message['required']
            assert (7 if direction == 1 else 6) == message['declaration_field']
    for row in ev['tables']['entries']:
        entry = check_span(row['entry'])
        check_span(row['descriptor'])
        check_span(row['vtable'])
        assert struct.unpack_from('<I', entry)[0] == row['feature_id']
        assert im.ptr(int(row['entry']['address'], 0) + 8) == int(row['descriptor']['address'], 0)
        vt = int(row['vtable']['address'], 0)
        assert im.ptr(int(row['descriptor']['address'], 0)) == vt
        for offset, key in [(16, 'start_from_device'), (24, 'validator')]:
            assert im.ptr(vt + offset) == (int(row[key], 0) if row[key] else 0)
    for row in ev['snapshots']:
        assert sha(path(row['path']).read_bytes()) == row['sha256'], row['path']
    assert len(ev['probe']['observations']) == 18 and ev['probe']['exit_code'] == 0
    print(json.dumps(dict(ok=True, functions=len(ev['functions']),
        instructions=instruction_count, table_spans=spans, snapshots=len(ev['snapshots']),
        recorded_probe_observations=18, probe_rerun=False,
        firmware_executed=False, vehicle_tested=False,
        limit='Integrity only; probe observations include known gaps, not Apple equivalence.'), indent=2))


if __name__ == '__main__':
    main()

"""Read-only chapter81 integrity verifier; run under WSL with Capstone.

Checks original function boundaries/bytes, message tables, current source hashes
and existing JUnit reports. Does not execute tests or Apple firmware itself.
"""
import bisect
import hashlib
import json
import struct
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(DOC.parent / 'firmware/tools/ipsw-research'))
from firmware_image import Image
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN


def local_path(value):
    value = value.replace('\\', '/')
    if sys.platform != 'win32' and len(value) > 2 and value[1] == ':':
        value = '/mnt/' + value[0].lower() + value[2:]
    return Path(value)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    evidence = json.loads((DOC / 'evidence/identification-components-message-batch.json').read_text(encoding='utf-8'))
    image = Image(local_path(evidence['firmware']['path']))
    assert sha(image.data) == evidence['firmware']['sha256'], 'firmware changed'
    decoder = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
    instructions = 0
    for row in evidence['functions']:
        start, end = int(row['address'], 0), int(row['end'], 0)
        assert start in image.starts and image.starts[bisect.bisect_right(image.starts, start)] == end
        raw = image.read(start, end - start)
        assert sha(raw) == row['sha256'], row['address']
        for cache in row['cache_matches']:
            assert local_path(cache).read_bytes() == raw, cache
        decoded = [f'{i.address:#x}: {i.bytes.hex()} {i.mnemonic} {i.op_str}' for i in decoder.disasm(raw, start)]
        assert decoded == row['assembly'], row['address']
        instructions += len(decoded)
    spans = 0

    def span(row):
        nonlocal spans
        raw = image.read(int(row['address'], 0), row['length'])
        assert sha(raw) == row['sha256'] and raw.hex() == row['raw_hex']
        spans += 1
        return raw

    for group in evidence['tables']['groups']:
        raw = span(group['raw'])
        for index, message in enumerate(group['messages']):
            assert f'0x{struct.unpack_from("<H", raw, index * 12)[0]:04x}' == message['message_id']
            direction = struct.unpack_from('<I', raw, index * 12 + 4)[0]
            assert direction == message['direction']
            assert raw[index * 12 + 8] == message['required']
            assert (7 if direction == 1 else 6) == message['declaration_field']
    for row in evidence['tables']['entries']:
        entry = span(row['entry'])
        span(row['descriptor'])
        span(row['vtable'])
        assert struct.unpack_from('<I', entry)[0] == row['feature_id']
        assert image.ptr(int(row['entry']['address'], 0) + 8) == int(row['descriptor']['address'], 0)
        vtable = int(row['vtable']['address'], 0)
        assert image.ptr(int(row['descriptor']['address'], 0)) == vtable
        for offset, key in [(16, 'start_from_device'), (24, 'validator')]:
            assert image.ptr(vtable + offset) == (int(row[key], 0) if row[key] else 0)
    for row in evidence['source_snapshots']:
        assert sha(local_path(row['path']).read_bytes()) == row['sha256'], row['path']
    results = []
    for module in evidence['tests']['full']:
        root = local_path('D:/carvex-research/android') / module['module'] / 'build/test-results/testDebugUnitTest'
        actual = {}
        for path in root.glob('TEST-*.xml'):
            suite = ET.parse(path).getroot()
            actual[suite.attrib['name']] = {key: int(suite.attrib[key]) for key in ('tests', 'failures', 'errors', 'skipped')}
        expected = {row['suite']: {key: row[key] for key in ('tests', 'failures', 'errors', 'skipped')} for row in module['suites']}
        assert actual == expected, module['module'] + ' reports differ; run full suite, not only targeted tests'
        assert all(row['failures'] == row['errors'] == row['skipped'] == 0 for row in actual.values())
        results.append(dict(module=module['module'], suites=len(actual), tests=sum(row['tests'] for row in actual.values())))
    print(json.dumps(dict(ok=True, functions=len(evidence['functions']), instructions=instructions,
        table_spans=spans, source_snapshots=len(evidence['source_snapshots']), junit=results,
        tests_executed_by_verifier=False, firmware_executed=False, vehicle_tested=False), indent=2))


if __name__ == '__main__':
    main()

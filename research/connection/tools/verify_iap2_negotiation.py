"""Read-only integrity check for chapter78; run with python3 -B under WSL.

Does not execute firmware or implementations, or prove semantic correctness.
--check-implementations also checks historical source/tool snapshots against now.
"""
import argparse
import bisect
import json
import sys
from pathlib import Path

sys.dont_write_bytecode = True
from inspect_iap2_handoff import DOC, Image, MD, sha


def current_path(value):
    value = value.replace('\\', '/')
    if len(value) > 2 and value[1:3] == ':/':
        return Path('/mnt') / value[0].lower() / value[3:]
    return Path(value)


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--check-implementations', action='store_true')
    args = p.parse_args()
    evidence = json.loads((DOC / 'evidence/iap2-syn-negotiation-audit.json').read_text(encoding='utf-8'))
    assert sha((DOC / evidence['inspection_tool']).read_bytes()) == evidence['inspection_tool_sha256']
    source = evidence['source']
    im = Image(current_path(source['path']))
    assert sha(im.data) == source['sha256'], 'firmware source changed'
    cached = anchors = 0
    for row in evidence['functions']:
        at, end = int(row['address'], 0), int(row['end'], 0)
        assert at in im.starts and im.starts[bisect.bisect_right(im.starts, at)] == end, row['address']
        raw = im.read(at, end-at)
        assert sha(raw) == row['sha256'], row['address']
        for path in row['cache_matches']:
            assert current_path(path).read_bytes() == raw, path
        cached += bool(row['cache_matches'])
        assembly = {f'{i.address:#x}: {i.bytes.hex()} {i.mnemonic} {i.op_str}' for i in MD.disasm(raw, at)}
        for line in row['reviewed_instructions']:
            assert line in assembly, line
            anchors += 1
    for row in evidence['constants']:
        assert im.read(int(row['address'], 0), len(bytes.fromhex(row['raw']))).hex() == row['raw']
    records = 0
    for state in evidence['device_state_table']:
        at = int(evidence['state_table_base'], 0) + state['state'] * 16
        raw = im.read(at, 16)
        assert raw.hex() == state['entry_hex']
        assert raw[8] == len(state['events'])
        table = im.ptr(at)
        for i, row in enumerate(state['events']):
            slot = table + i * 16
            raw = im.read(slot, 16)
            action = im.ptr(slot)
            assert hex(slot) == row['address'] and raw.hex() == row['raw_hex']
            assert row['handler'] == (hex(action) if action else None)
            assert (raw[8], raw[9]) == (row['next_state'], row['event'])
            records += 1
    assert len(evidence['functions']) == 20 and records == 93
    probes = evidence['implementation_probes']['rows']
    assert len(probes) == 16 and len({r['id'] for r in probes}) == 16
    for row in probes:
        assert row['phone']['generation'] == int(row['phone']['result'] == 'completed')
    result = dict(ok=True, functions=20, cached_functions=cached, instruction_anchors=anchors,
                  states=8, table_records=records, stored_probe_rows=16)
    if args.check_implementations:
        for row in evidence['implementation_sources'] + evidence['research_tools']:
            assert sha(current_path(row['path']).read_bytes()) == row['sha256'], row['path']
        for row in evidence['implementation_probes']['compiled_inputs']:
            assert sha(current_path(row['Path']).read_bytes()) == row['Hash'].lower(), row['Path']
        result['implementation_sources'] = len(evidence['implementation_sources'])
        result['research_tools'] = len(evidence['research_tools'])
    result['limit'] = 'Integrity only; stored probes are not rerun; no firmware execution, complete branch coverage or vehicle validation.'
    print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()

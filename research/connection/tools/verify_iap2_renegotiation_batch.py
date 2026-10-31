"""Chapter79 read-only source/evidence integrity check; no build or device I/O.

--check-tests compares saved JUnit XML to this batch. Later legitimate source
edits/test runs can invalidate the historical snapshot without being a defect.
This does not rerun tests or validate protocol semantics/headunit compatibility.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import xml.etree.ElementTree as ET

DOC = Path(__file__).resolve().parents[1]


def resolve(value):
    value = value.replace('\\', '/')
    if os.name != 'nt' and len(value) > 2 and value[1:3] == ':/':
        return Path('/mnt') / value[0].lower() / value[3:]
    return Path(value)


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--check-tests', action='store_true')
    args = p.parse_args()
    evidence = json.loads((DOC / 'evidence/iap2-renegotiation-batch.json').read_text(encoding='utf-8'))
    for row in evidence['snapshots']:
        assert digest(resolve(row['path'])) == row['sha256'], row['path']
    assert digest(Path(__file__)) == evidence['verification_tool_sha256']
    result = dict(ok=True, source_and_reference_snapshots=len(evidence['snapshots']))
    if args.check_tests:
        totals = dict(xml_suites=0, tests=0, failures=0, errors=0, skipped=0)
        for row in evidence['full_module']['xml']:
            path = resolve(row['path'])
            assert digest(path) == row['sha256'], row['name']
            suite = ET.parse(path).getroot()
            assert suite.attrib['name'] == row['name']
            totals['xml_suites'] += 1
            for key in ('tests', 'failures', 'errors', 'skipped'):
                number = int(suite.attrib.get(key, 0))
                assert number == row[key], (row['name'], key)
                totals[key] += number
        assert totals == evidence['full_module']['totals'], totals
        result['saved_test_results'] = totals
    result['limit'] = 'Integrity only; tests not rerun; no native execution or headunit validation.'
    print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()

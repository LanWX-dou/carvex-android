"""Read-only verification of chapter 77 byte/hash evidence (run under WSL).

Does not execute firmware, build Android, write caches, or verify protocol semantics.
--check-android additionally compares the current two phone files and JUnit XML
against this batch's snapshot; later legitimate edits/test runs may change them.
"""
import argparse
import bisect
import json
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

sys.dont_write_bytecode = True
from inspect_iap2_handoff import DOC, Image, sha


def current_path(value):
    if len(value) > 2 and value[1:3] == ':/':
        return Path('/mnt') / value[0].lower() / value[3:]
    return Path(value)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check-android', action='store_true')
    args = parser.parse_args()
    evidence = json.loads((DOC / 'evidence/iap2-extension-wait-boundary.json').read_text(encoding='utf-8'))
    assert sha((DOC / evidence['tool']).read_bytes()) == evidence['tool_sha256'], 'inspection tool changed'
    source, = evidence['sources']
    im = Image(Path(source['path']))
    assert sha(im.data) == source['sha256'], 'firmware source changed'
    count = cached = 0
    for row in evidence['functions']:
        at, end = int(row['address'], 0), int(row['end'], 0)
        assert at in im.starts and im.starts[bisect.bisect_right(im.starts, at)] == end, row['address']
        raw = im.read(at, end-at)
        assert sha(raw) == row['sha256'], row['address']
        for path in row['cache_matches']:
            assert Path(path).read_bytes() == raw, path
        cached += bool(row['cache_matches'])
        count += 1
    assert count == evidence['function_scope']['total']
    result = {'ok': True, 'sources': 1, 'functions': count, 'cached_functions': cached}
    if args.check_android:
        android = evidence['android_change']
        for kind in ('production', 'test'):
            assert sha(current_path(android[kind+'_file']).read_bytes()) == android[kind+'_sha256'], kind
        repo = current_path(android['production_file'].split('/protocol-carplay/')[0])
        xmls = sorted((repo / 'protocol-carplay/build/test-results/testDebugUnitTest').glob('TEST-*.xml'))
        totals = dict(xml_suites=len(xmls), count=0, failures=0, errors=0, skipped=0)
        for path in xmls:
            suite = ET.parse(path).getroot()
            for target, source_key in [('count', 'tests'), ('failures', 'failures'), ('errors', 'errors'), ('skipped', 'skipped')]:
                totals[target] += int(suite.attrib.get(source_key, 0))
        assert totals == android['full_module_tests'], totals
        result['android_files'] = 2
        result['test_results'] = totals
    result['limit'] = 'Integrity only; not semantic verification, native execution, full branch coverage or headunit validation.'
    print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()

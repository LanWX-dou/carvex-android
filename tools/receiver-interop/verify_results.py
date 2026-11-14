"""Check JUnit results contain every receiver contract with no failure or skip.

Run after a successful Gradle invocation with receiver-tests.init.gradle. This
checks existing reports, including valid Gradle cache results; it does not run
Gradle or independently prove report freshness or vehicle interoperability.
"""
import argparse
import hashlib
import json
import re
import xml.etree.ElementTree as ET
from pathlib import Path

ANDROID = Path(__file__).resolve().parents[2]
TEMPLATES = Path(__file__).resolve().parent
CONTRACTS = {
    'protocol-carplay': ('ReceiverProtocolContractTest.kt',
                        'io.github.iamr0s.carvex.carplay.core.ReceiverProtocolContractTest'),
    'host-carlife-mixing': ('ReceiverCallKeyContractTest.kt',
                          'io.github.iamr0s.carvex.host.ReceiverCallKeyContractTest'),
}


def digest(data):
    return hashlib.sha256(data).hexdigest()


def inspect(full):
    manifest = json.loads((ANDROID / 'build/receiver-interop/manifest.json').read_text(encoding='utf-8'))
    staged_root = (ANDROID / 'build/receiver-interop').resolve()
    if manifest.get('schema') != 2 or not manifest.get('staged_sha256'):
        raise ValueError('Receiver manifest predates staged input hashing; prepare and run tests again')
    for relative, expected_hash in manifest['staged_sha256'].items():
        path = (staged_root / relative).resolve()
        if not path.is_relative_to(staged_root) or digest(path.read_bytes()) != expected_hash:
            raise ValueError(f'Staged receiver input changed; prepare and run tests again: {relative}')
    paths = {module: f'{module}/build/test-results/testDebugUnitTest' for module in CONTRACTS}
    if full:
        paths.update({module: f'{module}/build/test-results/testDebugUnitTest'
                      for module in ('core', 'bridge', 'host-api')})
        paths['pcm-core'] = 'pcm-core/build/test-results/test'
        paths.update({f'app/{brand}': f'app/build/test-results/test{brand.title()}DebugUnitTest'
                      for brand in ('xiaomi', 'oppo', 'vivo', 'samsung', 'honor')})
    summary = {}
    hashes = {}
    for module, relative in paths.items():
        files = sorted((ANDROID / relative).glob('TEST-*.xml'))
        if not files:
            raise ValueError(f'No JUnit reports for {module}')
        totals = dict(tests=0, failures=0, errors=0, skipped=0)
        found = set()
        for report in files:
            data = report.read_bytes()
            suite = ET.fromstring(data)
            cases = suite.findall('testcase')
            if len(cases) != int(suite.attrib['tests']):
                raise ValueError(f'Incomplete JUnit report: {report.name}')
            for key in totals:
                totals[key] += int(suite.attrib.get(key, 0))
            if any(case.find(tag) is not None for case in cases for tag in ('failure', 'error', 'skipped')):
                raise ValueError(f'Failed or skipped test in {report.name}')
            if module in CONTRACTS:
                found.update(case.attrib['name'] for case in cases
                             if case.attrib.get('classname') == CONTRACTS[module][1])
            hashes[report.relative_to(ANDROID).as_posix()] = digest(data)
        if not totals['tests'] or any(totals[key] for key in ('failures', 'errors', 'skipped')):
            raise ValueError(f'{module} has failed, empty or skipped tests: {totals}')
        if module in CONTRACTS:
            template_name, _ = CONTRACTS[module]
            template = (TEMPLATES / template_name).read_bytes()
            staged = ANDROID / 'build/receiver-interop' / module / 'contracts' / template_name
            if staged.read_bytes() != template or manifest['contract_template_sha256'][template_name] != digest(template):
                raise ValueError(f'Contract template changed; prepare and run tests again: {template_name}')
            expected = set(re.findall(r'@Test\s+fun\s+(\w+)\s*\(', template.decode('utf-8')))
            if not expected or found != expected:
                raise ValueError(f'Receiver contracts missing or changed in {module}: expected={sorted(expected)} found={sorted(found)}')
            totals['receiver_contracts'] = len(found)
            if module == 'protocol-carplay':
                worker_source = 'shared/src/test/java/com/shilapi/xcertplay/hud/NavigationOutputWorkerTest.kt'
                worker_staged = ANDROID / 'build/receiver-interop/protocol-carplay/receiver/hud/NavigationOutputWorkerTest.kt'
                worker_bytes = worker_staged.read_bytes()
                if digest(worker_bytes) != manifest['source_sha256'][worker_source]:
                    raise ValueError('Receiver worker test changed; prepare and run tests again')
                worker_report = ANDROID / relative / 'TEST-com.shilapi.xcertplay.hud.NavigationOutputWorkerTest.xml'
                worker_cases = ET.fromstring(worker_report.read_bytes()).findall('testcase')
                worker_expected = set(re.findall(r'@Test\s+fun\s+`([^`]+)`\s*\(', worker_bytes.decode('utf-8')))
                if not worker_expected or {case.attrib['name'] for case in worker_cases} != worker_expected:
                    raise ValueError('Receiver worker tests missing or changed')
                totals['receiver_worker_tests'] = len(worker_cases)
        summary[module] = totals
    result = {
        'schema': 2, 'receiver_commit': manifest['receiver_commit'],
        'sender_commit_at_prepare': manifest['sender_commit'],
        'source_sha256': manifest['source_sha256'],
        'staged_sha256': manifest['staged_sha256'],
        'unchanged_body_slice_sha256': manifest['unchanged_body_slice_sha256'],
        'contract_template_sha256': manifest['contract_template_sha256'],
        'sender_source_sha256': {relative: digest((ANDROID / relative).read_bytes()) for relative in (
            'protocol-carplay/src/main/java/io/github/iamr0s/carvex/carplay/core/NavigationPublisher.kt',
            'host-carlife-mixing/src/main/java/io/github/iamr0s/carvex/host/MixingKeys.kt',
        )},
        'junit_summary': summary, 'junit_xml_sha256': hashes,
        'scope': 'Existing JUnit report verification after Gradle success; no vehicle or report freshness claim',
    }
    if full:
        lint = ANDROID / 'app/build/reports/lint-results-xiaomiRelease.xml'
        data = lint.read_bytes()
        issues = ET.fromstring(data).findall('issue')
        errors = [item for item in issues if item.attrib.get('severity') in ('Error', 'Fatal')]
        if errors:
            raise ValueError('Xiaomi Release lint has errors')
        result['xiaomi_release_lint'] = {
            'errors': 0, 'warnings': sum(item.attrib.get('severity') == 'Warning' for item in issues),
            'xml_sha256': digest(data),
        }
        isolation = {}
        for module in CONTRACTS:
            for variant in ('debug', 'release'):
                relative = f'{module}/build/intermediates/built_in_kotlinc/{variant}/compile{variant.title()}Kotlin/classes'
                classes = sorted((ANDROID / relative).rglob('*.class'))
                if not classes:
                    raise ValueError(f'Missing production Kotlin classes: {module}/{variant}')
                if any('com/shilapi/' in path.as_posix() or path.name.startswith('ReceiverProtocolContractTest')
                       or path.name.startswith('ReceiverCallKeyContractTest') for path in classes):
                    raise ValueError(f'Receiver code entered production classes: {module}/{variant}')
                isolation[f'{module}/{variant}'] = {'classes': len(classes), 'receiver_classes': 0}
        result['production_kotlin_isolation'] = isolation
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--full', action='store_true', help='also check core/bridge/host-api/PCM, five app flavors and Release lint')
    parser.add_argument('--output', type=Path, help='write verification summary JSON')
    args = parser.parse_args()
    result = inspect(args.full)
    if args.output:
        args.output.write_text(json.dumps(result, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
    for module, summary in result['junit_summary'].items():
        print(f'PASS {module}: {summary}')
    if args.full:
        print(f'PASS Xiaomi Release lint: {result["xiaomi_release_lint"]}')
        print(f'PASS production Kotlin isolation: {result["production_kotlin_isolation"]}')
    print('PASS: all receiver contracts present; zero test failures/errors/skips')


if __name__ == '__main__':
    main()

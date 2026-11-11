"""Verify hash-bound APK navigation paths and export allowlisted device-log metadata.

No vendor code is executed. No private road, lyrics, keys or device identities
are exported. DEX instruction identity is separate from runtime acceptance.
"""
import argparse
import hashlib
import json
import re
import struct
import zipfile
from pathlib import Path

from inspect_galaxyplay_receiver import dex_methods

ROOT = Path(__file__).resolve().parents[3]
EVIDENCE = ROOT / 'research/connection/evidence/cluster-navigation-flow-20261111.json'
APKS = {
    'galaxyplay': ('f106680faa27be5a9dfc4a9a9b9cb59239e4512c5f3b73b64cebfec47bb023e6', {
        'classes4.dex': {
            'Lcom/shilapi/xcertplay/GalaxyHudMediaText;.select': 0x0f7348,
            'Lcom/shilapi/xcertplay/GalaxyHudMediaText;.media': 0x0f7524,
            'Lcom/shilapi/xcertplay/GalaxyMediaKeys;.attach': 0x0fc5a8,
            'Lcom/shilapi/xcertplay/GalaxyMediaKeys;.attach$lambda$5': 0x0fbd6c,
            'Lcom/shilapi/xcertplay/GalaxyMediaKeys;.attach$lambda$7': 0x0fbddc,
            'Lcom/shilapi/xcertplay/GalaxyMediaKeys;.attach$lambda$9': 0x0fbe7c,
            'Lcom/shilapi/xcertplay/GalaxyMediaKeys;.onConnection': 0x0fc9dc,
            'Lcom/shilapi/xcertplay/GalaxyMediaKeys;.onMediaAudioChanged': 0x0fcbf8,
            'Lcom/shilapi/xcertplay/GalaxyMediaKeys;.startNavigation': 0x0fd170,
            'Lcom/shilapi/xcertplay/GalaxyMediaKeys;.startNavigation$lambda$34': 0x0fba60,
            'Lcom/shilapi/xcertplay/GalaxyMediaKeys$startNavigation$3;.run': 0x0fb290,
            'Lcom/shilapi/xcertplay/L7NavigationSession;.update': 0x16a6dc,
            'Lcom/shilapi/xcertplay/L7NavigationSession;.publish': 0x16a49c,
            'Lcom/shilapi/xcertplay/GalaxyOemNavigation;.guidance': 0x1086a4,
            'Lcom/shilapi/xcertplay/GalaxyOemNavigation;.register': 0x1087e8,
            'Lcom/shilapi/xcertplay/GalaxyOemNavigation;.flush': 0x1083d0,
            'Lcom/shilapi/xcertplay/GalaxyNavigationSdk;.register': 0x1054b4,
            'Lcom/shilapi/xcertplay/GalaxyNavigationSdk;.register$lambda$4': 0x1057a0,
            'Lcom/shilapi/xcertplay/GalaxyNavigationSdk;.respond': 0x105b30,
            'Lcom/shilapi/xcertplay/GalaxyNavigationSdk$register$callback$1$1$1;.guidance': 0x105330,
            'Lcom/shilapi/xcertplay/GalaxyNavigationSdk$register$callback$1$1$1;.status': 0x1053e8,
            'Lcom/shilapi/xcertplay/GalaxyNavigationContract;.<init>': 0x1034d0,
            'Lcom/shilapi/xcertplay/GalaxyNavigationContract;.model': 0x102f44,
            'Lcom/shilapi/xcertplay/GalaxyNavigationContract;.number': 0x102cdc,
            'Lcom/shilapi/xcertplay/GalaxyNavigationIcons;.fromCarPlay': 0x103f04,
        },
        'classes5.dex': {
            'Lcom/shilapi/xcertplay/orchestration/CarPlayController;.hasActiveSession': 0x043d7c,
        },
    }),
    'factory': ('043866ed5e719fd1617ef57f4060c0fd7030e02df70433c5f5d0f518bf1946af', {
        'classes.dex': {
            'Lcom/geely/carlinkservice/listener/PhoneDataListener;.onMusicInfoReceived': 0x47daa4,
            'Lcom/geely/carlinkservice/listener/PhoneDataListener;.onNavigationInfoReceived': 0x47db48,
            'Lcom/geely/handler/MediaCtrlMgr;.startCarlinkMusic': 0x487058,
            'Lcom/geely/handler/NavCtrMgr;.cancelNavi': 0x48850c,
            'Lcom/ecarx/eas/framework/sdk/navi/MapAPI;.registerMapClient': 0x3b715c,
            'Lcom/ecarx/eas/framework/sdk/navi/MapAPI;.unregisterMapClient': 0x3b7188,
            'Lcom/ecarx/eas/framework/sdk/navi/MapAPIProxy;.registerMapClient': 0x3b6f58,
            'Lcom/ecarx/eas/framework/sdk/navi/EASMapAPI;.registerMapClient': 0x3b56a8,
            'Lcom/ecarx/eas/mapsdk/model/response/GuidingInfoModel;.setNextTurnDistance': 0x3d1828,
            'Lcom/ecarx/eas/mapsdk/model/response/GuidingInfoModel;.setRemainDistance': 0x3d1888,
            'Lcom/ecarx/eas/mapsdk/model/response/GuidingInfoModel;.setRemainTime': 0x3d1900,
            'Lcom/ecarx/eas/mapsdk/model/response/GuidingInfoModel;.setTurnIconId': 0x3d19c0,
            'Lcom/ecarx/eas/mapsdk/model/response/GuidingInfoModel;.writeToParcel': 0x3d2208,
        },
        'classes3.dex': {
            'Lcom/ucar/vehiclesdk/UCarAdapter;.a': 0x1f798c,
            'Lcom/ucarsink/sink/natives/SinkNative;.<clinit>': 0x226d40,
        },
    }),
}

# Parameter IDs and reviewed scalar names, never the field's position in a packet.
NAVIGATION_SCALARS = {
    '5201': {'0': 'component', '1': 'guidanceState', '7': 'distanceRemaining',
             '10': 'distanceToManeuver', '13': 'maneuverIndex'},
    '5202': {'0': 'component', '1': 'index', '3': 'type'},
}


def digest(data):
    return hashlib.sha256(data).hexdigest()


def inspect_apk(path, expected_hash, targets):
    data = path.read_bytes()
    if digest(data) != expected_hash:
        raise ValueError('APK differs from the reviewed build')
    result = {'sha256': expected_hash, 'bytes': len(data), 'dex': {}}
    with zipfile.ZipFile(path) as archive:
        result['manifest_sha256'] = digest(archive.read('AndroidManifest.xml'))
        result['dex_count'] = sum(name.endswith('.dex') for name in archive.namelist())
        result['native_libraries'] = {
            name: {'bytes': len(raw), 'sha256': digest(raw)}
            for name in archive.namelist() if name.startswith('lib/') and name.endswith('.so')
            for raw in [archive.read(name)]
        }
        for name, methods in targets.items():
            data = archive.read(name)
            owners = dex_methods(data)
            entry = {'sha256': digest(data), 'methods': {}}
            for label, offset in methods.items():
                owner, method = label.rsplit('.', 1)
                resolved = owners.get(offset)
                if resolved is None or resolved[:2] != (owner, method):
                    raise ValueError(f'{name}:{label}: code_item ownership mismatch: {resolved}')
                units = struct.unpack_from('<I', data, offset + 12)[0]
                begin = offset + 16
                instructions = data[begin:begin + units * 2]
                if not units or len(instructions) != units * 2:
                    raise ValueError('invalid instruction bounds')
                entry['methods'][label] = {'code_item': hex(offset), 'prototype': resolved[2],
                                          'code_units': units, 'insns_sha256': digest(instructions)}
            result['dex'][name] = entry
    return result


def inspect_log(path):
    data = path.read_bytes()
    lines = data.decode('utf-8-sig').splitlines()
    version = re.search(r'^Version: (\d+) \(([^)]+)\).*?(debug|release)', '\n'.join(lines), re.M)
    result = {'sha256': digest(data), 'bytes': len(data), 'line_count': len(lines),
              'build': {'version_code': int(version[1]), 'version_name': version[2], 'type': version[3]}
              if version else None, 'sessions': {}}
    packets = {}
    for line_number, line in enumerate(lines, 1):
        prefix = re.match(r'^(\d{4}-\d{2}-\d{2}T[\d:.]+Z) \[([a-f0-9]+)\] (.*)$', line)
        if prefix is None:
            continue
        time, session, body = prefix.groups()
        entry = result['sessions'].setdefault(session, {'normalized': [], 'navigation_packets': [],
            'music_transport_completions': [], 'runtime_navigation_starts': []})
        base = {'line': line_number, 'utc': time}
        if 'navigation event=normalized ' in body:
            # Explicit numeric and enum whitelist; never copy the full log line.
            fields = re.search(r'source=(xiaomi) binding=(\d+) route=(\d+) revision=(\d+) lifecycle=(ACTIVE|ENDED|INVALIDATED|UNKNOWN|REROUTING)', body)
            if fields:
                entry['normalized'].append(base | {'source': fields[1], 'binding': int(fields[2]),
                    'route': int(fields[3]), 'revision': int(fields[4]), 'lifecycle': fields[5]})
        if 'debug navigation event=subscription id=5200 ' in body:
            match = re.search(r'accepted=(true|false) link=(\d+) subscription=(\d+) components=\[([\d, ]*)\] options=(\d+)(?:\s|$)', body)
            if match and match[1] == 'true':
                entry['runtime_navigation_starts'].append(base | {
                    'link': int(match[2]), 'subscription': int(match[3]),
                    'components': [int(item.strip()) for item in match[4].split(',') if item.strip()],
                    'options': int(match[5])})
        if 'debug navigation event=wire direction=tx ' in body:
            match = re.search(r'id=(5201|5202) source=runtime tx=(\d+) fields=(\d+)', body)
            if match:
                packet = base | {'id': match[1], 'tx': int(match[2]),
                                 'field_count': int(match[3]), 'fields': {}}
                entry['navigation_packets'].append(packet)
                packets[(session, match[1], int(match[2]))] = packet
        if 'debug navigation event=field direction=tx ' in body:
            match = re.search(r'id=(5201|5202) source=runtime tx=(\d+) field=(\d+) index=\d+ name=(\w+) value=(\d+)(?:\s|$)', body)
            if match and NAVIGATION_SCALARS[match[1]].get(match[3]) == match[4]:
                packet = packets.get((session, match[1], int(match[2])))
                if packet:
                    packet['fields'][match[3]] = int(match[5])
        if 'debug navigation event=transport direction=tx ' in body:
            match = re.search(r'id=(5201|5202) tx=(\d+) completed=(true|false)', body)
            if match and (packet := packets.get((session, match[1], int(match[2])))):
                packet['transport_completed'] = match[3] == 'true'
        if 'debug music event=transport direction=tx id=5001 ' in body and 'completed=true' in body:
            entry['music_transport_completions'].append(base)
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--galaxyplay', type=Path, required=True)
    parser.add_argument('--factory', type=Path, required=True)
    parser.add_argument('--log', type=Path, required=True)
    parser.add_argument('--write', action='store_true')
    args = parser.parse_args()
    observed = {'schema': 2, 'date': '2026-11-11',
                'scope': 'Original APK byte identity and sanitized sender log; no vehicle acceptance claim',
                'apks': {name: inspect_apk(getattr(args, name), *config) for name, config in APKS.items()},
                'device_log': inspect_log(args.log)}
    if args.write:
        EVIDENCE.write_text(json.dumps(observed, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    elif observed != json.loads(EVIDENCE.read_text(encoding='utf-8')):
        raise ValueError('APK identities, method bytes or sanitized log differ from recorded evidence')
    count = sum(len(dex['methods']) for apk in observed['apks'].values() for dex in apk['dex'].values())
    print(f'PASS: two APK identities, {count} method owners/instruction hashes, sanitized device log')
    print('Static byte checks and sender transport completion do not prove instrument rendering.')


if __name__ == '__main__':
    main()

"""Verify the reviewed CarWith 4.0.23 navigation producer from its original APK.

Only method identities, original instruction hashes and reviewed PNG hashes are
exported. No vendor code is executed; semantic review is recorded in the spec.
"""
import argparse
import hashlib
import json
import struct
import zipfile
from pathlib import Path

from inspect_galaxyplay_receiver import dex_methods
from inspect_navigation_numeric_core import ICONS

ROOT = Path(__file__).resolve().parents[3]
RECORD = ROOT / 'research/connection/evidence/carwith-navigation-upgrade-20261112.json'
REFERENCE = ROOT / 'research/connection/evidence/navigation-numeric-core-20261111.json'
APK_SHA = 'c897a45d92c84f06e670fc4edd323824093a093f67d8e7d7b058fee2a737d06c'
LAUNCHER = 'Lcom/carwith/launcher/LauncherDataBusClient;'
MAP = 'Lcom/carwith/launcher/map/l;'
METHODS = {
    0x1d3c14: ('Lcom/carwith/launcher/map/wms/j$b0;', 'g', '(Z)V'),
    0x17aae8: (LAUNCHER, 'D', '()V'),
    0x17abdc: (LAUNCHER, 'F', '(ZLjava/lang/String;Landroid/graphics/drawable/Icon;' + 'Ljava/lang/String;' * 6 + ')V'),
    0x17a338: (LAUNCHER, 'x', '(Ljava/lang/String;Ljava/lang/String;)I'),
    0x1ba904: (MAP, 'd', '(Landroid/graphics/Bitmap;Ljava/lang/String;)I'),
    0x1bae4c: (MAP, '<clinit>', '()V'),
    0x1ba61c: ('Lcom/carwith/launcher/map/l$a;', '<init>', '(II)V'),
    0x1ba5ec: ('Lcom/carwith/launcher/map/l$a;', 'a', '()I'),
    0x1ba604: ('Lcom/carwith/launcher/map/l$a;', 'b', '()I'),
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def inspect(apk):
    data = apk.read_bytes()
    if sha(data) != APK_SHA:
        raise ValueError('APK differs from the reviewed CarWith 4.0.23 build')
    reference = json.loads(REFERENCE.read_text(encoding='utf-8'))['carwith']['reviewed_icons']
    result = {'schema': 1, 'date': '2026-11-12',
              'scope': 'Original producer bytes and template identity; no vehicle acceptance',
              'version': '4.0.23-20261016', 'apk_sha256': APK_SHA, 'apk_bytes': len(data),
              'manifest_identity_review': {'tool': 'Android SDK 36.0.0 aapt dump badging',
                  'package': 'com.miui.carlink', 'version_code': 104000023},
              'methods': {}, 'reviewed_icons': {}}
    with zipfile.ZipFile(apk) as archive:
        dex = archive.read('classes2.dex')
        owners = dex_methods(dex)
        result['classes2_sha256'] = sha(dex)
        result['manifest_sha256'] = sha(archive.read('AndroidManifest.xml'))
        result['resources_arsc_sha256'] = sha(archive.read('resources.arsc'))
        for offset, expected in METHODS.items():
            if owners.get(offset) != expected:
                raise ValueError(f'Method ownership or prototype differs at {offset:#x}')
            registers, inputs, outputs, tries, _, units = struct.unpack_from('<HHHHII', dex, offset)
            code = dex[offset + 16:offset + 16 + units * 2]
            if not units or len(code) != units * 2:
                raise ValueError('Invalid code item bounds')
            result['methods'][hex(offset)] = {'owner': expected[0], 'method': expected[1],
                'prototype': expected[2], 'registers': registers, 'inputs': inputs,
                'outputs': outputs, 'tries': tries, 'code_units': units, 'insns_sha256': sha(code)}
        # aapt2 confirmed these resource entries for both original APKs. Their
        # bytes must equal the already reviewed 4.0.14 arrow templates.
        for name, entry in ICONS.items():
            digest = sha(archive.read(entry))
            if digest != reference[name]['sha256']:
                raise ValueError(f'Reviewed arrow template changed: {name}')
            result['reviewed_icons'][name] = {'entry': entry, 'sha256': digest}
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('apk', type=Path)
    parser.add_argument('--write', action='store_true')
    args = parser.parse_args()
    observed = inspect(args.apk)
    if args.write:
        RECORD.write_text(json.dumps(observed, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
    elif observed != json.loads(RECORD.read_text(encoding='utf-8')):
        raise ValueError('Recorded producer identities or original instruction hashes differ')
    print('PASS: CarWith 4.0.23 APK, 9 method owners/prototypes/instruction hashes, 18 unchanged arrow templates')
    print('No vendor execution or vehicle display validation.')


if __name__ == '__main__':
    main()

"""Recover user-requested navigation fields and image bytes from exported logs.

No vendor code or serialized objects are executed. Partial/corrupt captures remain
visible in the manifest and return a nonzero status instead of producing guessed bytes.
"""
import argparse
import base64
import hashlib
import json
import re
from pathlib import Path

EVENT = re.compile(r'navigation event=raw-(begin|field|end) source=(\S+) binding=(\d+) capture=(\d+) payload=')


def extract(log, output):
    captures = {}
    with log.open(encoding='utf-8-sig') as stream:
        for line_number, line in enumerate(stream, 1):
            match = EVENT.search(line)
            if not match:
                continue
            event, source, binding, capture = match.groups()
            session = re.search(r'\[([^]]*)\]', line[:match.start()])
            key = (session[1] if session else '', source, int(binding), int(capture))
            record = captures.setdefault(key, {'fields': {}, 'errors': []})
            try:
                # The host event adapter appends " 0"; decode only the JSON object.
                payload, _ = json.JSONDecoder().raw_decode(line[match.end():].lstrip())
                if event != 'field':
                    record[event] = payload
                    continue
                path = tuple(payload['path'])
                field = record['fields'].setdefault(path, {'meta': payload, 'parts': {}})
                for name in ('type', 'encoding', 'parts', 'bytes', 'sha256'):
                    if field['meta'].get(name) != payload.get(name):
                        raise ValueError('inconsistent field metadata')
                part = payload['part']
                if not isinstance(part, int) or not 1 <= part <= payload['parts']:
                    raise ValueError('invalid part number')
                previous = field['parts'].get(part)
                if previous is not None and previous != payload['value']:
                    raise ValueError('conflicting repeated chunk')
                field['parts'][part] = payload['value']
            except (ValueError, TypeError, KeyError) as error:
                record['errors'].append({'line': line_number, 'error': str(error)})
    if not captures:
        raise ValueError('No navigation raw captures found; log 8 predates this feature')
    output.mkdir(parents=True, exist_ok=True)
    manifest = {'captures': [], 'complete': True}
    files = 0
    for key, capture in captures.items():
        session, source, binding, number = key
        result = {'session': session, 'source': source, 'binding': binding, 'capture': number,
                  'begin': capture.get('begin'), 'end': capture.get('end'),
                  'fields': [], 'errors': list(capture['errors'])}
        for path, field in capture['fields'].items():
            meta = field['meta']
            recovered = {name: value for name, value in meta.items() if name not in ('value', 'part', 'preview')}
            try:
                if len(field['parts']) != meta['parts']:
                    raise ValueError('missing chunks')
                value = ''.join(field['parts'][i] for i in range(1, meta['parts'] + 1))
                encoding = meta['encoding']
                if encoding == 'base64' or encoding.endswith('-base64'):
                    data = base64.b64decode(value, validate=True)
                    if len(data) != meta['bytes'] or hashlib.sha256(data).hexdigest() != meta['sha256']:
                        raise ValueError('byte length or SHA256 mismatch')
                    if encoding == 'utf16be-base64':
                        recovered['value'] = data.decode('utf-16-be', errors='surrogatepass')
                    else:
                        suffix = '.bin'
                        if encoding == 'png-base64' or data.startswith(b'\x89PNG\r\n\x1a\n'):
                            suffix = '.png'
                        elif data.startswith(b'\xff\xd8\xff'):
                            suffix = '.jpg'
                        elif encoding == 'parcel-base64':
                            suffix = '.parcel'
                        elif encoding == 'serialized-base64':
                            suffix = '.ser'
                        files += 1
                        # Source keys never become filesystem paths.
                        name = f'field-{files:05d}{suffix}'
                        (output / name).write_bytes(data)
                        recovered['file'] = name
                else:
                    recovered['value'] = value
                recovered['complete'] = encoding != 'error'
                if encoding == 'error':
                    raise ValueError('source value could not be captured: ' + value)
            except (ValueError, UnicodeError, KeyError) as error:
                recovered['complete'] = False
                recovered['error'] = str(error)
            result['fields'].append(recovered)
        end = capture.get('end')
        if not capture.get('begin') or not end:
            result['errors'].append({'error': 'missing begin/end record'})
        elif end['fields'] != len(capture['fields']) or end['chunks'] != sum(len(f['parts']) for f in capture['fields'].values()):
            result['errors'].append({'error': 'capture field/chunk count mismatch'})
        result['complete'] = not result['errors'] and all(f['complete'] for f in result['fields'])
        manifest['complete'] &= result['complete']
        manifest['captures'].append(result)
    (output / 'navigation-raw.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n',
                                               encoding='utf-8', errors='backslashreplace')
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('log', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    try:
        manifest = extract(args.log, args.output)
    except ValueError as error:
        parser.exit(2, str(error) + '\n')
    print(f"Recovered {len(manifest['captures'])} navigation captures: {args.output / 'navigation-raw.json'}")
    if not manifest['complete']:
        parser.exit(2, 'Some captures are incomplete; see manifest errors.\n')


if __name__ == '__main__':
    main()

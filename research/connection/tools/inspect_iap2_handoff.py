"""Read-only 24A446 handoff inspection; JSON to stdout, no cache writes.

Selectors decoded from original shared-cache stubs. Direct call references and
symbol names do not prove dynamic dispatch or cross-process execution.
"""
import argparse
import bisect
import hashlib
import json
import re
import struct
import sys
from pathlib import Path

sys.dont_write_bytecode = True
DOC = Path(__file__).resolve().parents[1]
FW = DOC.parent / 'firmware'
sys.path.insert(0, str(FW / 'tools/ipsw-research'))
from firmware_image import Image
from firmware_cache import Cache
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN

ROOT = FW / 'extracted/24A446/components/24A446__iPhone18,1/root'
SOURCES = {
    'accessoryd': ROOT / 'System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd',
    'bluetoothd': ROOT / 'usr/sbin/bluetoothd',
    'CoreAccessories': FW / 'extracted/24A446/binaries/CoreAccessories/CoreAccessories',
}
MD = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)

def sha(data): return hashlib.sha256(data).hexdigest()

def imports(im):
    off=32; sections=[]; symtab=indirect=None
    for _ in range(struct.unpack_from('<I',im.data,16)[0]):
        cmd,size=struct.unpack_from('<II',im.data,off)
        if cmd==2: symtab=struct.unpack_from('<IIII',im.data,off+8)
        elif cmd==11: indirect=struct.unpack_from('<II',im.data,off+56)
        elif cmd==25:
            for i in range(struct.unpack_from('<I',im.data,off+64)[0]):
                at=off+72+i*80
                flags,first,stride=struct.unpack_from('<III',im.data,at+64)
                if flags&255 in (6,7,8):
                    addr,length=struct.unpack_from('<QQ',im.data,at+32)
                    sections.append((addr,length,first,stride if flags&255==8 else 8))
        off+=size
    result={}
    if symtab and indirect:
        syms,count,strings,strlen=symtab
        for addr,length,first,stride in sections:
            for at in range(addr,addr+length,stride):
                index=first+(at-addr)//stride
                if index>=indirect[1]: continue
                symbol=struct.unpack_from('<I',im.data,indirect[0]+4*index)[0]
                if symbol>=count: continue
                no=struct.unpack_from('<I',im.data,syms+symbol*16)[0]
                end=im.data.index(b'\0',strings+no,strings+strlen)
                result[at]={'symbol':im.data[strings+no:end].decode(),'indirect_index':index}
    return result

def local_selector(im,at):
    ins=list(MD.disasm(im.read(at,12),at))
    if len(ins)<2 or ins[0].mnemonic!='adrp' or not ins[0].op_str.startswith('x1, #'): return None
    m=re.fullmatch(r'x1, \[x1, #(0x[0-9a-f]+)\]',ins[1].op_str)
    if ins[1].mnemonic!='ldr' or not m:return None
    slot=int(ins[0].op_str.split('#')[1],0)+int(m.group(1),0)
    ptr=im.ptr(slot)
    return {'stub':hex(at),'selector_slot':hex(slot),'string_address':hex(ptr),'selector':im.cstr(ptr)}

def verify_evidence(cache):
    evidence=json.loads((DOC/'evidence/iap2-xpc-handoff-hid.json').read_text(encoding='utf-8'))
    assert evidence['tool_sha256']==sha(Path(__file__).read_bytes()), 'tool hash changed'
    counts={'sources':0,'functions':0,'cached_functions':0,'original_cache_functions':0}
    for component in evidence['components']:
        im=Image(SOURCES[component['component']])
        assert sha(im.data)==component['source_sha256'], component['component']
        counts['sources']+=1
        for row in component['functions']:
            at,end=int(row['address'],0),int(row['end'],0)
            assert at in im.starts and im.starts[bisect.bisect_right(im.starts,at)]==end
            raw=im.read(at,end-at)
            assert sha(raw)==row['sha256'], row['address']
            for path in row['cache_matches']:
                assert Path(path).read_bytes()==raw, path
            if row['cache_matches']: counts['cached_functions']+=1
            if row.get('original_cache_matches'):
                assert cache.read(at,len(raw))==raw, row['address']
                counts['original_cache_functions']+=1
            counts['functions']+=1
    return {'ok':True,**counts,'limit':'Byte/hash verification only; not protocol semantics, full branch coverage, firmware execution or headunit validation.'}

def selector(cache, at):
    raw = cache.read(at, 12)
    instructions = list(MD.disasm(raw, at))
    if len(instructions) != 3: return None
    a, b, c = instructions
    if a.mnemonic != 'adrp' or not a.op_str.startswith('x1, #'): return None
    if b.mnemonic != 'add' or not b.op_str.startswith('x1, x1, #'): return None
    target = int(a.op_str.split('#')[1], 0) + int(b.op_str.split('#')[1], 0)
    name = cache.cstr(target)
    return {'stub': hex(at), 'stub_hex': raw.hex(), 'string_address': hex(target), 'selector': name}

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('mode', choices=['function','symbols','selectors','pointers','slice','imports','strings','cfstrings','verify'])
    p.add_argument('--component', choices=list(SOURCES), default='accessoryd')
    p.add_argument('--address', action='append', default=[])
    p.add_argument('--regex', default='createEndpoint|publishConnection|serverConnection|ACCTransport')
    p.add_argument('--count', type=int, default=16)
    args = p.parse_args()
    im = Image(SOURCES[args.component])
    imported=imports(im)
    cache = Cache(FW / 'extracted/24A446/dyld')
    out = {'component':args.component, 'source':str(im.path), 'source_sha256':sha(im.data),
           'tool_sha256':sha(Path(__file__).read_bytes()), 'firmware_executed':False, 'records':[]}
    try:
        if args.mode=='verify': out['verification']=verify_evidence(cache)
        if args.mode == 'symbols':
            out['records'] = [{'address':hex(at),'names':names} for at,names in im.symbols.items()
                              if any(re.search(args.regex,n,re.I) for n in names)]
        for at in map(lambda s:int(s,0), args.address):
            if args.mode == 'imports':
                out['records'].append({'address':hex(at),**imported.get(at,{})})
            elif args.mode in ('strings','cfstrings'):
                reader=cache if args.component=='CoreAccessories' else im
                ptr=reader.ptr(at+16) if args.mode=='cfstrings' else at
                out['records'].append({'address':hex(at),'string_address':hex(ptr),'string':reader.cstr(ptr)})
            elif args.mode == 'selectors':
                out['records'].append(selector(cache,at))
            elif args.mode == 'pointers':
                for slot in range(at, at+args.count*8, 8):
                    reader=cache if args.component=='CoreAccessories' else im
                    raw=reader.read(slot,8)
                    row={'slot':hex(slot),'raw':raw.hex()}
                    try:
                        ptr=reader.ptr(slot)
                        row.update(target=hex(ptr),symbols=im.symbols.get(ptr,[]))
                        try: row['string']=reader.cstr(ptr)
                        except (ValueError,UnicodeError): pass
                    except ValueError as e:
                        row['error']=str(e)
                        if str(e)=='external bind' and slot in imported: row.update(imported[slot])
                    out['records'].append(row)
            elif args.mode in ('function','slice'):
                if args.mode == 'function':
                    assert at in im.starts, f'not function start {at:#x}'
                    idx=bisect.bisect_right(im.starts,at)
                    end=im.starts[idx]
                else: end=at+args.count*4
                raw=im.read(at,end-at)
                row={'address':hex(at),'end':hex(end),'sha256':sha(raw), 'symbols':sorted(set(n for n in im.symbols.get(at,[]) if n))}
                if args.component=='CoreAccessories':
                    row['original_cache_matches']=raw==cache.read(at,len(raw))
                    assert row['original_cache_matches']
                row['cache_matches']=[]
                if args.mode=='function':
                    for f in (FW/'analysis/decompiler-cache/24A446'/args.component).glob(f'*/functions/f_{at:x}.bin'):
                        assert f.read_bytes()==raw
                        row['cache_matches'].append(str(f))
                row['assembly']=[]
                row['selector_calls']=[]
                row['named_calls']=[]
                for ins in MD.disasm(raw,at):
                    row['assembly'].append(f'{ins.address:#x}: {ins.bytes.hex()} {ins.mnemonic} {ins.op_str}')
                    if ins.mnemonic in ('b','bl') and ins.op_str.startswith('#0x'):
                        target=int(ins.op_str[1:],0)
                        names=imported.get(target) or {'symbols':sorted(set(n for n in im.symbols.get(target,[]) if n and not n.startswith('_OUTLINED_FUNCTION_') and '.cold.' not in n))}
                        if names.get('symbol') or names.get('symbols'): row['named_calls'].append({'site':hex(ins.address),'target':hex(target),**names})
                        if args.component!='CoreAccessories':
                            try:
                                resolved=local_selector(im,target)
                                if resolved:row['selector_calls'].append({'site':hex(ins.address),**resolved})
                            except (ValueError,UnicodeError):pass
                    if ins.mnemonic in ('b','bl') and ins.op_str.startswith('#0x208'):
                        try:
                            resolved=selector(cache,int(ins.op_str[1:],0))
                            if resolved: row['selector_calls'].append({'site':hex(ins.address),**resolved})
                        except (ValueError,UnicodeError): pass
                out['records'].append(row)
    finally: cache.close()
    print(json.dumps(out, ensure_ascii=False, indent=2))

if __name__=='__main__': main()

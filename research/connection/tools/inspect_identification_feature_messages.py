"""Read-only 24A446 Identification audit; emit JSON, never modify input images.

Run with Python 3 and Capstone installed. Cache text is navigation only;
complete cached machine-code slices must match the mapped original image.
"""
from pathlib import Path
import hashlib
import json
import struct
import sys
import capstone

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'firmware/tools/ipsw-research'))
from firmware_image import Image

IMAGE = ROOT / 'firmware/extracted/24A446/components/24A446__iPhone18,1/root/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd'
CACHE = ROOT / 'firmware/analysis/decompiler-cache/24A446/accessoryd/18405d82c74429b84ed4/functions'
PHONE = ROOT.parent / 'iamr0s/carplay-xiaomi-carlife'
BASE = PHONE / 'protocol-carplay/src/main/java/io/github/iamr0s/carvex'
FUNCTIONS = [
    0x10013aed0, 0x10006782c, 0x10013bcc8, 0x10013bbdc,
    0x10013bb68, 0x10004e29c, 0x100050c2c, 0x100050af4,
    0x10004efe8, 0x10004eec8, 0x10013b6d4, 0x10013adf0,
    0x10004ecec, 0x10004edcc, 0x1000b331c, 0x100170d80,
    0x10013ec58, 0x100170cb8, 0x100170bb0, 0x10016e004,
    0x10016d3ac, 0x100005138, 0x100051054, 0x100050dcc,
    0x10013b540, 0x10004dd50, 0x10013c0ec, 0x10013ea10,
    0x10011da74, 0x10011d8dc, 0x100001b04, 0x1000031f8,
    0x10002b140,
]
NAMES = {
    0:'AccAuthentication', 1:'Identification', 18:'Test', 8:'DeviceNotifications',
    14:'NowPlaying', 2:'AppLaunch', 16:'Power', 11:'HID', 22:'WiFiSharing',
    10:'ExternalAccessory', 19:'USBHostMode', 13:'MediaLibrary', 3:'AssistiveTouch',
    21:'VoiceOver', 9:'DigitalAudio', 6:'Communications', 20:'Vehicle', 4:'BLEPairing',
    12:'Location', 5:'BTConnectionStatus', 23:'DestinationSharing', 15:'OOBBTPairing',
    17:'Navigation', 7:'DeviceAuthentication', 24:'AppLinks', 25:'OOBBTPairing2',
    26:'CarPlayConnectionRequest', 27:'DigitalCarKey_Info', 28:'DigitalCarKey_Matching',
}

def path(value):
    return str(value).replace('\\', '/').replace('/mnt/d/', 'D:/')

def sha(data):
    return hashlib.sha256(data).hexdigest()

def main():
    image = Image(IMAGE)
    decoder = capstone.Cs(capstone.CS_ARCH_ARM64, capstone.CS_MODE_LITTLE_ENDIAN)
    def ptr(at):
        raw = image.u64(at)
        if not raw:
            return 0
        if raw >> 62 & 1:
            raise ValueError(f'bind, not a local rebase: {at:#x}')
        value = image.base + (raw & 0xffffffffff)
        image.read(value, 1)
        return value
    def span(at, count):
        raw = image.read(at, count)
        offset = next(off + at - a for a,b,off,_ in image.segments if a <= at and at+count <= b)
        return dict(address=hex(at), length=count, source_file_offset=offset, sha256=sha(raw), raw_hex=raw.hex())
    functions = []
    for address in FUNCTIONS:
        cache = CACHE / f'f_{address:x}.bin'
        raw = cache.read_bytes()
        record = span(address, len(raw))
        del record['raw_hex']
        record.update(symbols=image.symbols.get(address, []), raw_matches_source=raw == image.read(address, len(raw)), cache_raw_path=path(cache), assembly_path=path(cache.with_suffix('.s')))
        assert record['raw_matches_source'], hex(address)
        decoded=list(decoder.disasm(image.read(address,len(raw)),address))
        assert sum(item.size for item in decoded)==len(raw), hex(address)
        record['decoded_instruction_count']=len(decoded)
        record['control_transfers']=[dict(address=hex(item.address),raw_hex=item.bytes.hex(),mnemonic=item.mnemonic,operands=item.op_str) for item in decoded if item.mnemonic.startswith(('b.','cb','tb','bl','br','ret','csel','cset','ccmp')) or item.mnemonic=='b']
        functions.append(record)
    entries=[]
    for index in range(29):
        address=0x10021b550 + 16*index
        feature=struct.unpack('<I', image.read(address,4))[0]
        descriptor=ptr(address+8)
        vtable=ptr(descriptor)
        validator=ptr(vtable+0x18) if vtable else 0
        starter=ptr(vtable+0x10) if vtable else 0
        entries.append(dict(index=index,feature_id=feature,name=NAMES[feature],entry=span(address,16),descriptor=span(descriptor,0x23),vtable=span(vtable,0x20) if vtable else None,validator=hex(validator) if validator else None,start_from_device=hex(starter) if starter else None,start_without_identification_flag=image.read(descriptor+0x22,1)[0],validator_body_audited=feature in (22,26)))
    groups=[]
    for name, address in [('CarPlayConnectionRequest',0x1001b3fc8), ('DeviceWiFiCredentialsSharing',0x1001b40a8), ('AccessoryWiFiCredentialsSharing',0x1001b40c0)]:
        messages=[]
        for index in range(2):
            raw=image.read(address+12*index,12)
            message=struct.unpack_from('<H',raw)[0]
            direction=struct.unpack_from('<I',raw,4)[0]
            messages.append(dict(message_id=f'0x{message:04x}',direction=direction,required=raw[8],declaration_field=7 if direction==1 else 6))
        groups.append(dict(name=name,raw=span(address,24),messages=messages))
    source_paths = [BASE/'carplay/Bootstrap.kt', BASE/'carplay/core/Wire.kt', BASE/'sessioncore/IapIdentifyInfo.kt', BASE/'sessioncore/PeerNegotiationController.kt', PHONE/'core/src/main/java/io/github/iamr0s/carvex/sessioncore/Connection.kt']
    sources=[dict(path=path(p),sha256=sha(p.read_bytes())) for p in source_paths]
    return dict(schema_version=1,created_date='2026-10-29',baseline='iPhone18,1 / iOS 27.0.1 / 24A446',status='PARTIAL',runtime_observed=False,original_code_executed_this_round=False,full_feature_coverage=False,source=dict(path=path(IMAGE),sha256=sha(image.data)),method='Mapped LC_SEGMENT_64 bytes; compared complete cached machine code and decoded original bytes with Capstone. Re-read 29 original feature entries/descriptors/vtables and 3 message arrays. Never execute original code. Pointer decoding only for checked local non-bind rebases.',decoder_version=capstone.__version__,tools=[dict(path=path(ROOT/'firmware/tools/ipsw-research/firmware_image.py'),sha256=sha((ROOT/'firmware/tools/ipsw-research/firmware_image.py').read_bytes()))],functions=functions,feature_registration=dict(base='0x10021b550',count=29,entry_size=16,validator_offset_in_vtable=24,start_offset_in_vtable=16,entries=entries),message_groups=groups,current_source_snapshot=sources)

if __name__ == '__main__':
    result = main()
    result['tools'].append(dict(path=path(Path(__file__).resolve()),sha256=sha(Path(__file__).read_bytes())))
    if '--summary' in sys.argv:
        result = dict(source=result['source'],functions=len(result['functions']),all_raw_match=all(item['raw_matches_source'] for item in result['functions']),feature_entries=len(result['feature_registration']['entries']),message_groups=len(result['message_groups']),decoder_version=result['decoder_version'],tools=result['tools'])
    print(json.dumps(result,ensure_ascii=False,indent=2))

# Toyota ACK-only / NO_SYN producer trace (2026-10-31)

## Status

- ACK constructor and call chain: **CONFIRMED from the original Toyota binaries**
- Detection interpreted as a 512-byte packet by a stale iAP2 device: **STRONG STATIC EVIDENCE**
- Stale device survives because the cleanup path cannot complete: **PARTIAL / OPEN**
- Production CarVeX protocol workaround justified by this round: **NO**
- Toyota field result for the current CarVeX build: **REPORTED PASS**

The user subsequently reported that the current CarVeX build on Toyota can:

- connect reliably;
- disconnect and reconnect after the session;
- display lyrics while media is playing.

This is field evidence that the now-playing initialization repair has covered the
observed primary failure on the tested Toyota unit. It does not prove every
historical ACK-only state impossible, but it removes the need to ship an
unproven ACK, SYN, timeout, or Toyota-specific workaround.

The field report does not include an APK hash, cycle count, or a synchronized
Toyota-side thread trace. Those details remain useful for regression tracking,
not for blocking this result.

This note supersedes the earlier address list that incorrectly named `0x40a270`
as an `iap2Disconnect` caller. `0x40a270` is `KnobUpdate`. The real common
teardown function is `FUN_0040a380`.

## Firmware inputs

Toyota:

- `libiAP2.so`
- SHA-256: `f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f`
- Ghidra image base in the analysis project: `0x100000`

Toyota:

- `AppleCarPlay`
- SHA-256: `bb8a5b0d9fa57eafa8a9358341db3c9661d210ec778620e52e8d3b9fa4fd9f5e`

iPhone baseline:

- `/System/Library/PrivateFrameworks/CoreAccessories.framework/Support/accessoryd`
- extracted from iPhone 24A446
- SHA-256: `2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe`

Windows-native Ghidra project:

- `analysis/toyota-ack-producer-20261031/windows-project/toyota-ack-win`

The earlier root-owned Ghidra project remains untouched.

## Confirmed ACK producer

For `libiAP2.so`, Ghidra virtual addresses are file offset `+ 0x100000`.

```text
CIpodDevice::procThread
  -> CIpodDevice::packetProc
  -> CIpodIap2::packetProc                 VA 0x138370 / file 0x38370
  -> FUN_00137d60                          VA 0x137d60 / file 0x37d60
  -> CIpodIap2::sendAckPacket              VA 0x128cb0 / file 0x28cb0
  -> CIpodIap2::createLinkPacket           VA 0x1282f0 / file 0x282f0
  -> CIpodIap2::write
  -> CIpodDevice::send
  -> Bluetooth send callback
```

`CIpodIap2::sendAckPacket` calls:

```text
createLinkPacket(control = 0x40,
                 seq     = this[0x10],
                 ack     = this[0x11],
                 session = 0,
                 payload = empty)
```

`FUN_00137d60` selects this path under either of these conditions:

- session is non-zero; it first stores inbound byte 5 into `this[0x11]`, sends
  an ACK, then dispatches the CSM
- session is zero and total length is not 9; it stores inbound byte 5 into
  `this[0x11]` and sends an ACK

For a session-zero, total-length-9 pure ACK (`control=0x40`), it does not reply.
For the bare RST form (`control=0x10`), it enters the RST branch.

`CIpodDevice::procThread` holds the device queue mutex at `device+0xe0` while it
calls `packetProc`. `CIpodDevice::packetAdd` uses the same mutex.

## Detection misparse by a stale CIpodDevice

Toyota Bluetooth input enters:

```text
CIpodLib::ipod_BT_spp_data_pro       VA 0x13d7b0 / file 0x3d7b0
  -> CIpodList::getDevice(handle)
  -> CIpodDevice::ipod_BT_spp_data_pro
                                      VA 0x11fc90 / file 0x1fc90
```

The device input function has two branches:

```text
if device[0xac] == 0 and first six bytes == FF 55 02 00 EE 10:
    accept Detection
    device[0xa8] = 2
    device[0xac] = 1
    sem_post(device+0x88)
else:
    length = packet[2] << 8 | packet[3]
    copy `length` bytes without checking FF 5A
    copy `length` bytes without checking the actual socket-read length
    packetAdd(length-sized packet)
```

Therefore, if the same `CIpodDevice` still has `device[0xac] == 1`, a repeated
Detection is not recognized as Detection:

```text
input:              FF 55 02 00 EE 10
derived length:     0x0200 = 512
derived packet[5]:  0x10
```

The stale object enqueues a nominal 512-byte session-zero packet. Once
`packetProc` reaches this packet:

```text
session  = packet[5] = 0
length   = 512 != 9
this[0x11] = packet[5] = 0x10
sendAckPacket()
```

The resulting shape is exactly:

```text
control = 0x40
seq     = current value of CIpodIap2[0x10]
ack     = 0x10
session = 0
payload = empty
```

The field logs contain:

```text
iAP frame RX 40/109/16/0/0
```

`IapLink.frameLine` formats a frame as `flags/seq/ack/session/payloadSize`.
Thus the failed frames are `seq=109, ack=16`, not `seq=1`. The earlier
`seq=1` statement is withdrawn.

`seq=109` is consistent with retained iAP2 state, but the logs alone do not
prove which object instance produced that value. The `ack=0x10` is directly
explained by Detection byte 5 and the stale-object branch above.

## Why a stale object is possible

### Connect does not replace an existing path

`CIpodLib::connect` at VA `0x13c820` / file `0x3c820` first calls
`CIpodList::isDeviceExist(path)`. If true, it logs:

```text
iAP2 Device has already exist.
```

It returns 0 without creating a new `CIpodDevice` and without resetting
`device[0xac]`.

### Bluetooth handle and disconnect callback

`CIpodDevice::openDevice` assigns Bluetooth a fixed handle:

```text
device+0x30 = 3
device+0x08 = 0xff
```

`0xff` is therefore handle 255, not a `-1` sentinel.

`CIpodLib::ipod_bt_spp_state_change` at VA `0x13d738` / file `0x3d738`:

```text
old = getbtSppConnStatus()
setbtSppConnStatus(new)
if old == 3 and new != 3:
    CIpodEvent::sendEvent(event=0, handle=0xff, status=0)
```

The AppleCarPlay observer object is populated in `FUN_0040b260`:

```text
observer = 0x425a50
observer[0x00] = FUN_0040cfa0
```

`CIpodEvent::sendEvent` case 0 invokes observer slot 0 with `(handle,status)`.
Bluetooth handle 255 matches AppleCarPlay global Bluetooth handle
`DAT_004258c0 == 0xff`, so `FUN_0040cfa0(255,0)` enters the teardown branch.

It clears the AppleCarPlay BT globals and calls `iap2Disconnect(255)`.

`iap2Disconnect` calls `CIpodLib::disconnect`. That function at VA `0x13c9a0`
first acquires the global `CIpodSync` lock, then checks the device, pops it from
`CIpodList`, and sets the caller handle to `-1`.

`CIpodList::pop` calls `CIpodDevice::destroy`, which:

- calls protocol deinit
- sets the device exiting flag
- closes the handle
- joins process, receive, and native threads
- deletes the protocol object

The receive thread also sends event 0 with the device handle on read/select
failure, so a normal EOF has another path into the same AppleCarPlay teardown.

### Remaining OPEN condition

The cleanup entry exists. The unresolved point is why it does not finish before
the next RFCOMM connection.

The strongest current candidate remains a blocked global lock:

```text
now-playing callback
  -> device queue lock held
  -> getPlayingTrackTitle holds CIpodSync
  -> waits on initialization completed by the same blocked notification path

next RFCOMM state change / disconnect / connect
  -> needs CIpodSync
  -> cannot pop or create CIpodDevice
```

Earlier local Toyota-binary analysis established the title self-wait and the
global-lock relationship. It is not yet bound to the field APK/binary and is not
proved by a field thread stack, so this remains **OPEN**.

`CIpodDevice::destroy` also calls `pthread_join` on the current receive thread
when invoked synchronously from that thread's event callback. A self-join
normally returns `EDEADLK`; the return value is ignored. This is not currently
assigned as the root cause.

## iPhone 24A446 Detection baseline

`iAP2LinkDeviceActionSendDetect @ 0x10002fac8`:

- writes a `0x1d` action marker
- calls `iAP2LinkResetSeqAck(link,0,1)`
- calls `iAP2LinkSendDetectCB`

The fixed source buffer at `0x1001b3378` is:

```text
ff 55 02 00 ee 10
```

The following halfword at `0x1001b3380` is `0x0006`, so exactly six bytes are
sent. `iAP2PacketCheckDetect @ 0x100102e20` validates the same six bytes.

CarVeX uses the same six bytes in:

```text
protocol-carplay/.../core/Wire.kt
```

The iPhone baseline does not justify changing the Detection bytes or adding
Toyota-specific Detection variants.

## Relation to current CarVeX behavior

The field order shows:

1. New RFCOMM connection.
2. The first classified frame is `40/109/16/0/0`.
3. CarVeX correctly ignores this as a pre-SYN ACK.
4. No peer SYN follows.
5. CarVeX terminates with `NO_SYN`.

Current relevant behavior:

- `Wire.kt` sends the firmware-matching Detection bytes.
- `IapLink.kt` has absolute first-byte and pre-SYN deadlines.
- `IapLink.kt` does not feed a pre-SYN pure ACK into committed sequence state.

These behaviors are not contradicted by the firmware evidence in this round.
No production code should be changed merely to accept, answer, or synthesize
the stale ACK.

## Next evidence work

These items are historical root-cause work. They no longer gate the current
production path because the tested Toyota build now connects, reconnects, and
displays lyrics.

1. Retain the complete passing field log with the exact APK hash and repeated
   connect/disconnect cycle count.
2. Obtain a field thread stack or synchronized logs showing whether
   `CIpodSync` is held if the ACK-only state ever returns.
3. Bind the field Toyota build to the local `sourceVersion`/binary before
   treating the now-playing self-wait as proven on that unit.
4. Use a bounded model driven by the original instruction branches to validate:
   - fresh device plus Detection
   - stale `device[0xac]==1` plus Detection
   - queue mutex held versus free
5. Trace all writes to `CIpodIap2[0x10]` and determine whether 109 belongs to the
   retained Bluetooth object or another handoff-generation object.
6. Only after those points close, decide whether CarVeX needs a session-epoch,
   cleanup-timeout, or transport-recreation change. Any such change must first
   be justified by an iPhone 24A446 branch or a Toyota receive-side condition,
   not by this ACK observation alone.

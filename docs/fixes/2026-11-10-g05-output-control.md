# G05: declare only the prepared output control transport

24A446 AirPlaySender SHA256:
304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f.

Original instructions 0x2519be158..0x2519be19c branch raw102 to the output
control transport, while other supported playback types initialize its port to
zero. 0x2519be3fc..0x2519be5c8 creates/prepares that transport and retrieves its
port. 0x2519be8ac..0x2519be8d8 writes controlPort and spf together only when the
port is positive. Input dataPort has an independent positive-port condition at
0x2519be8f4..0x2519be91c.

Android previously always allocated a second UDP socket and advertised its port
and spf for all playback routes. Runtime now creates retransmission/control only
for raw102. Raw100/raw101 omit both fields, including duplex speech: a real
microphone socket still supplies input/dataPort without fabricating output
control. Nullable control sockets are closed safely on reserve/setup failure.
Packetization and raw102 retransmission behavior are retained.

Latency is still OPEN, with a more precise data-flow boundary: GetLatencyInfo
0x2519bbf0c returns formatInfo+0x78; 0x251ade724..0x251ade730 copies the three
latency fields into that slot. 0x251ade434..0x251ade474 obtains its first field
from the local formats policy, while receiver input/output micros contribute to
two sample-count fields. SETUP 0x2519be85c reads the first field. Directly using
receiverLatencyMicros/1000 for SETUP would therefore be incorrect. Constructor
policy binding and runtime capture time mapping remain unclosed; this repair
does not change the existing latency value or claim complete G05 support.

Validation: three additional regressions (all three routes/codecs, duplex input,
raw102 control), protocol 1107 tests and Xiaomi Debug Kotlin compilation passed.
No phone or vehicle validation.

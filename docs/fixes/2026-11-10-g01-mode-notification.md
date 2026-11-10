# G01: rejected resource transactions must not publish a state

The local changeModes handler returns HTTP 200 / business status 1 when a
resource request is unsupported or the host rejects the screen change. It does
not commit a state and supplies no params. Previously eventReplied treated this
transport success as permission to enqueue modesChanged with null params.

ResourceModeNotification now requires business status 0 and a state dictionary.
The accepted transaction retains its complete screen/audio/appStates snapshot;
failed requests generate no state notification. This is a correction to the
local transaction boundary, not a newly inferred Apple arbitration algorithm.

24A446 AirPlaySender (SHA256
304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f):
0x251afb178..0x251afb204 parses the complete resource request, and
0x2519b97ec..0x2519b9810 separately commits a complete mode struct. The resource
parser 0x251afb2e0..0x251afb5d0 validates priorities 100/500 and constraints
100/500/1000; these values alone do not prove arbitration or app-state ownership.

G01 remains PARTIAL: priorities/constraints, local temporary borrowing history,
and Speech/PhoneCall/TurnByTurn production and arbitration remain OPEN. The
original receiver/delegate policy consumer has not been closed; no ignored
constraint handling or fabricated app-state ownership was added.

Validation: five new regressions cover binary-plist success, business rejection,
missing/malformed status and invalid state; protocol tests (1104 total) and
Xiaomi Debug Kotlin compilation passed. No device or vehicle validation.

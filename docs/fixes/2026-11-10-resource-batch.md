# Combined resource requests

24A446 AirPlaySender, SHA256
`304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f`:
`0x251afb178..0x251afb204` loops over the resources array, placing resource 1
at request offset 8 and resource 2 at offset 32. The parser at `0x251afb304`
rejects duplicate entries in strict mode. The former Android `singleOrNull`
restriction rejected simultaneous screen and audio changes.

The existing supported transfer subset now accepts both resources in either
order. Validation builds a proposed state without side effects. AirSession
obtains screen acceptance before committing either owner, then updates its
main-audio send gate when resource 2 was included. The post-reply modesChanged
notification retains the complete resulting state.

This is a bounded parser/dispatch correction, not full resource arbitration.
Constraint fields and nonempty appStates still remain unsupported; parsing
their enum values alone does not establish their arbitration behavior.

Validation: protocol unit tests and Xiaomi Kotlin compilation. New cases cover
both orders, duplicate/unknown resources, invalid second transfers, and combined
borrow/return without partial mutation. No phone or vehicle validation.

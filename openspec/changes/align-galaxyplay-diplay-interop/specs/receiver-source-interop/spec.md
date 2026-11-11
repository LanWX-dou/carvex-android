## ADDED Requirements

### Requirement: Execute source-bound receiver contracts

The optional verifier SHALL execute the supplied receiver Kotlin parsers against
CarVeX output, preserve original parser bodies, and record all input hashes.
It MUST NOT add receiver code to production variants or write to the source repo.

#### Scenario: Receiver source is available

- **WHEN** a clean DiPlay checkout is supplied to the verifier
- **THEN** sender metadata/navigation bytes and receiver subscription/HID values
  are tested using that checkout's code, with its commit and hashes recorded

#### Scenario: Required source is unavailable or changed structurally

- **WHEN** an expected receiver source file or extraction boundary is missing
- **THEN** the verifier fails explicitly without substituting a simulated parser

### Requirement: Bound navigation definitions by receiver capacity

The sender SHALL respect the minimum positive maneuver storage capacity of every
selected component, reuse valid U16 indices, and define a maneuver before referencing it.

#### Scenario: Long route on an eight-slot receiver

- **WHEN** more than eight maneuvers are published without ending the route
- **THEN** the receiver retains at most eight distinct maneuver indices while
  its current arrow and distance correspond to the latest batch

#### Scenario: Single-slot receiver

- **WHEN** a maneuver definition is published to a component with capacity one
- **THEN** a reset precedes the definition and reference so an existing arrow
  cannot be paired with the new maneuver's old distance

### Requirement: Preserve call-control semantics

The adapter SHALL translate Telephony Hook Switch to the verified host answer
operation and Drop to end/reject. It MUST NOT translate unsupported Flash to answer.

#### Scenario: GalaxyPlay or DiPlay answers a ringing call

- **WHEN** the receiver emits selector one from its telephony HID descriptor
- **THEN** descriptor decoding produces usage 0x20 and the adapter requests
  the host's CALL action, rather than opening the phone UI

### Requirement: Separate compatibility evidence from field acceptance

Validation SHALL distinguish receiver-source tests, original APK facts, sender
firmware evidence and real vehicle outcomes. Missing full phone metadata,
cellular PCM sources and unverified navigation field roles MUST remain OPEN.

#### Scenario: Local tests pass but no vehicle session is available

- **WHEN** the verifier and affected module tests pass
- **THEN** the result is reported as local contract validation and no complete
  vehicle interoperability or full duplex call claim is made

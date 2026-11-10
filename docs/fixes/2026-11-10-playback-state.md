# Playback state for steering wheel controls

The device log contains three Consumer Play presses, all delivered to the host,
and 332 Now Playing deltas with no playback status. The old host adapter has no
verified player-state input. An audio lane stopping during navigation or speech
cannot be used as proof that the music app is paused.

Observe Android MediaController playback state after explicit notification-access
authorization. Match the host title and, when provided, artist to exactly one
active media session. Unrelated or ambiguous sessions, unavailable permission,
buffering and unknown states do not manufacture a PLAYING/PAUSED update. The
observer releases its listeners with the projection session and handles access
being granted after connection. No notification contents are inspected.

Publish known player states through the existing 5001 encoder and subscription
filter. Explicit Play/Pause HID usages keep their existing semantics. Confirmed
player state also supersedes audio-lane and sent-key guesses for the local toggle.

Protocol encoding is unchanged: accessoryd 24A446 playback handler 0x1001465c4,
existing NowPlayingUpdate group 1 / attribute 0 and initialization helpers
0x10008f588 / 0x10008f978. This is an Android backend addition, not a claim that
Android MediaSession authorization or metadata matching reproduces iOS internals.
The relevant original handler assembly was reviewed during this change.

Validation: platform-android, core, bridge and protocol-carplay unit suites;
Xiaomi debug Kotlin compilation and main manifest merge. Focused cases cover
unique/ambiguous/unmatched players and player-state precedence over audio focus
or a successfully sent key. Device/vehicle validation is still required; no APK
was packaged or installed. Notification access must be enabled in Settings before
this state source can correct the vehicle's Play/Pause decision.

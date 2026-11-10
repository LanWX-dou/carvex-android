# Use observed playback state for steering-wheel toggles

This is an Android host-routing correction, not a new Apple wire mapping. The
existing HID path remains governed by input-business-lifecycle spec R-1.6/R-1.7:
original `0x6802` report transport does not establish a player's state. Apple
WWDC 2016 session 722 (1414–1422 seconds) describes media controls; it does not
justify inferring playback from audio focus or treating key delivery as success.

Previously a toggle flipped a local Boolean before channel admission and before
host delivery. Unknown state was seeded by audio lane activity and explicit keys.
Now only MediaPlaybackMonitor's matched player report selects host Play/Pause.
Selection runs when the queued usage is dispatched. Unknown state retains the
existing Android KEYCODE_MEDIA_PLAY_PAUSE route. A rejected or unconfirmed press
does not alter the next action. This cannot guarantee that the system route targets
the intended player without a matching session; device testing is still needed.

Validation: core/bridge tests, protocol tests and Xiaomi Kotlin compilation.
Cases cover unknown/revoked state, repeated selection without player confirmation,
and player changes while a press waits. Hold/seek semantics remain a separate gap.
No phone or vehicle validation.

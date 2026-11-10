package io.github.iamr0s.carvex.sessioncore

/**
 * State only for the stateless HID Consumer Play/Pause usage.
 *
 * CarWith exposes separate Play and Pause keys. Only a matched player's reported
 * state can select between them. Unknown state retains the native toggle meaning.
 * Queue admission or key delivery does not prove that playback changed.
 */
class MediaPlaybackToggle {
    private var reported: Boolean? = null

    @Synchronized fun playbackState(active: Boolean?) {
        reported = active
    }

    @Synchronized fun choose(play: Int, pause: Int): Int? = when (reported) {
        true -> pause
        false -> play
        null -> null
    }
}

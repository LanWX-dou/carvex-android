package io.github.iamr0s.carvex.session

import io.github.iamr0s.carvex.platform.MediaSessionSelection
import io.github.iamr0s.carvex.carplay.core.NowPlayingUpdate

/** CarWith's HUD can put a lyric in song and the complete song-artist label in artist.
 * Compare the complete label; splitting it would corrupt names containing hyphens.
 * MediaSessionSelection combines this with ordinary matching and rejects ambiguity. */
internal object CarLifeMusicPresentation {
    /** Only an independently matched full label permits replacing presentation text. */
    fun normalize(track: NowPlayingUpdate.Track, candidate: MediaSessionSelection.Item?): NowPlayingUpdate.Track {
        if (candidate == null || !matches(MediaSessionSelection.Item(track.title, track.artist), candidate)) return track
        val title = NowPlayingUpdate.textOrNull(candidate.title) ?: return track
        val artist = NowPlayingUpdate.textOrNull(candidate.artist) ?: return track
        return track.copy(title = title, artist = artist)
    }

    fun matches(target: MediaSessionSelection.Item, candidate: MediaSessionSelection.Item): Boolean {
        if (target.title.isNullOrBlank()) return false
        val label = target.artist?.trim()?.takeIf { it.isNotEmpty() } ?: return false
        val title = candidate.title?.trim()?.takeIf { it.isNotEmpty() } ?: return false
        val artist = candidate.artist?.trim()?.takeIf { it.isNotEmpty() } ?: return false
        return label == "$title-$artist"
    }
}

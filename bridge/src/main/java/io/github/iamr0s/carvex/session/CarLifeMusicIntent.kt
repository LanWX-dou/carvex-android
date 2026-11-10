package io.github.iamr0s.carvex.session

import android.content.Intent
import io.github.iamr0s.carvex.carplay.core.NowPlayingUpdate
import org.json.JSONObject

/**
 * Normalizes the vehicle-music Intent without treating private field names
 * as an iAP2 schema. Only fields with a known Now Playing analogue are
 * copied. Artwork is handled by CarLifeArtworkLoader; player state comes from
 * the matched Android media session rather than guessed private Intent values.
 */
internal object CarLifeMusicIntent {
    private const val ACTION = "carlife_vehicle_music_info"
    private const val PROGRESS_ACTION = "carlife_vehicle_music_progress"

    fun parse(intent: Intent): NowPlayingUpdate.Track? {
        val json = intent.getStringExtra("params")?.let { raw ->
            runCatching { JSONObject(raw) }.getOrNull()
        }
        val extras = intent.extras?.let { bundle ->
            bundle.keySet().associateWith { key -> bundle.get(key) }
        }.orEmpty()
        return parsePayload(intent.action, extras, json)
    }

    internal fun parsePayload(action: String?, values: Map<String, Any?>,
                              json: JSONObject? = null): NowPlayingUpdate.Track? {
        if (action != ACTION && action != PROGRESS_ACTION) return null
        fun string(vararg names: String): String? {
            for (name in names) {
                val direct = values[name]
                if (direct is String) return direct
                val nested = json?.takeIf { it.has(name) && !it.isNull(name) }?.optString(name)
                if (nested != null) return nested
            }
            return null
        }
        fun number(vararg names: String): Long? {
            for (name in names) {
                val value = when (val direct = values[name]) {
                    is Number -> direct.toLong()
                    is String -> direct.toLongOrNull()
                    else -> null
                } ?: json?.optLong(name, Long.MIN_VALUE)?.takeUnless { it == Long.MIN_VALUE }
                if (value != null) return value
            }
            return null
        }
        val title = string("song", "title", "MediaSongName", "song_name")
        val artist = string("artist", "MediaArtistName", "artist_name")
        val album = string("album", "MediaAlbumName", "album_name")
        val app = string("source", "app", "MediaAPPName", "MediaAppName")
        val duration = number("duration", "duration_ms", "MediaSongDuration")
            ?.takeIf { it in 1..0xffffffffL }
        val elapsed = number("curTime", "progress", "progress_ms", "MediaSongPlayTime")
            ?.takeIf { it in 0..0xffffffffL }
        // The progress broadcast is a delta, including a legitimate zero after seeking.
        // Units follow the existing host adapter's millisecond contract; state is unknown.
        if (action == PROGRESS_ACTION) return if (duration == null && elapsed == null) null
            else NowPlayingUpdate.Track(durationMs = duration, elapsedMs = elapsed)
        if (title == null && artist == null && album == null && app == null && duration == null && elapsed == null) {
            return null
        }
        return NowPlayingUpdate.Track(
            title = NowPlayingUpdate.textOrNull(title),
            artist = NowPlayingUpdate.textOrNull(artist),
            album = NowPlayingUpdate.textOrNull(album),
            durationMs = duration,
            elapsedMs = elapsed,
            appName = NowPlayingUpdate.textOrNull(app),
        )
    }

}

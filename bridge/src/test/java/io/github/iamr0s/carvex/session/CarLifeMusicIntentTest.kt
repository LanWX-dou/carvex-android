package io.github.iamr0s.carvex.session

import org.junit.Assert.assertEquals
import org.junit.Assert.assertNull
import org.junit.Test

class CarLifeMusicIntentTest {
    @Test fun parsesDirectMusicFieldsAndKeepsWireRanges() {
        val track = CarLifeMusicIntent.parsePayload("carlife_vehicle_music_info", mapOf(
            "song" to "Song", "artist" to "Artist", "album" to "Album",
            "duration" to 180000L, "progress" to 1200L), null)
        assertEquals("Song", track?.title)
        assertEquals("Artist", track?.artist)
        assertEquals("Album", track?.album)
        assertEquals(180000L, track?.durationMs)
        assertEquals(1200L, track?.elapsedMs)
    }

    @Test fun parsesDashboardAliasesAndDoesNotInventState() {
        val track = CarLifeMusicIntent.parsePayload("carlife_vehicle_music_info",
            mapOf("MediaSongName" to "dashboard song", "MediaPlayStatus" to 1), null)
        assertEquals("dashboard song", track?.title)
        assertNull(track?.status)
    }

    @Test fun rejectsWrongActionAndReportsArtworkAsUnimplemented() {
        assertNull(CarLifeMusicIntent.parsePayload("other", mapOf("song" to "ignored"), null))
    }

    @Test fun progressBroadcastUsesCurTimeIncludingSeekToZero() {
        val track = CarLifeMusicIntent.parsePayload("carlife_vehicle_music_progress",
            mapOf("curTime" to 0L, "duration" to 180000L, "song" to "not metadata"))!!
        assertEquals(0L, track.elapsedMs)
        assertEquals(180000L, track.durationMs)
        assertNull(track.title)
        assertNull(track.status)
    }

    @Test fun progressRejectsOutOfRangeInsteadOfWrapping() {
        assertNull(CarLifeMusicIntent.parsePayload("carlife_vehicle_music_progress",
            mapOf("curTime" to -1L, "duration" to 0x100000000L)))
        assertEquals(0xffffffffL, CarLifeMusicIntent.parsePayload("carlife_vehicle_music_progress",
            mapOf("curTime" to "4294967295"))?.elapsedMs)
    }
}

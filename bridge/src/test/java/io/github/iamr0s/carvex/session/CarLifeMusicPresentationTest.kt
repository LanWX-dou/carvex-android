package io.github.iamr0s.carvex.session

import io.github.iamr0s.carvex.platform.MediaSessionSelection
import io.github.iamr0s.carvex.carplay.core.NowPlayingUpdate
import io.github.iamr0s.carvex.carplay.core.NowPlayingArtwork
import org.junit.Assert.*
import org.junit.Test

class CarLifeMusicPresentationTest {
    private fun item(title: String?, artist: String? = null) = MediaSessionSelection.Item(title, artist)
    private fun select(target: MediaSessionSelection.Item, vararg candidates: MediaSessionSelection.Item) =
        MediaSessionSelection.index(target, candidates.toList(), CarLifeMusicPresentation::matches)

    @Test fun lyricAndCompleteLabelSelectTheActualTrack() {
        assertEquals(1, select(item("A lyric line", "Song-Artist"),
            item("Podcast", "Host"), item("Song", "Artist")))
        assertEquals(0, select(item("Next lyric line", "Song-Artist"), item("Song", "Artist")))
    }

    @Test fun ordinaryMetadataStillMatches() {
        assertEquals(0, select(item("Song", "Artist"), item("Song", "Artist")))
        assertEquals(0, select(item("Song"), item("Song", "Artist")))
    }

    @Test fun namesContainingHyphensAreComparedWithoutSplitting() {
        assertEquals(0, select(item("Lyric", "Song-Part-Artist-Name"), item("Song-Part", "Artist-Name")))
        assertNull(select(item("Lyric", "Song-Part-Artist-Name"),
            item("Song-Part", "Artist-Name"), item("Song", "Part-Artist-Name")))
    }

    @Test fun partialArtistAndSubstringDoNotIdentifyPlayer() {
        assertNull(select(item("Lyric", "Artist"), item("Song", "Artist")))
        assertNull(select(item("Lyric", "Song-Artist-extra"), item("Song", "Artist")))
        assertNull(select(item("Lyric", "Other-Artist"), item("Song", "Artist")))
    }

    @Test fun duplicateTracksAndCrossPathMatchesStayUnknown() {
        assertNull(select(item("Lyric", "Song-Artist"), item("Song", "Artist"), item("Song", "Artist")))
        assertNull(select(item("Lyric", "Song-Artist"), item("Lyric", "Song-Artist"), item("Song", "Artist")))
    }

    @Test fun missingMetadataDoesNotTurnIntoAnAlias() {
        assertNull(select(item(null, "Song-Artist"), item("Song", "Artist")))
        assertNull(select(item("Lyric", "Song-"), item("Song", null)))
        assertNull(select(item("Lyric", "-Artist"), item(null, "Artist")))
        assertNull(select(item("Lyric", null), item("Song", "Artist")))
    }

    @Test fun unrelatedIntentAndProgressCannotSupplyMusicPresentation() {
        assertNull(CarLifeMusicIntent.parsePayload("other", mapOf("song" to "Lyric", "artist" to "Song-Artist")))
        val progress = CarLifeMusicIntent.parsePayload("carlife_vehicle_music_progress",
            mapOf("curTime" to 10, "song" to "Lyric", "artist" to "Song-Artist"))!!
        assertNull(select(item(progress.title, progress.artist), item("Song", "Artist")))
    }

    private fun normalize(track: NowPlayingUpdate.Track, vararg candidates: MediaSessionSelection.Item): NowPlayingUpdate.Track {
        val index = select(item(track.title, track.artist), *candidates)
        return CarLifeMusicPresentation.normalize(track, index?.let { candidates[it] })
    }

    @Test fun successiveLyricsUseRealMetadataAndPreserveOtherHostFields() {
        val track = NowPlayingUpdate.Track(title = "Lyric", artist = "Song-Part-Artist-Name",
            album = "Album", durationMs = 293000, elapsedMs = 1234)
        val expected = track.copy(title = "Song-Part", artist = "Artist-Name")
        assertEquals(expected, normalize(track, item("Song-Part", "Artist-Name")))
        assertEquals(expected, normalize(track.copy(title = "Next lyric"), item("Song-Part", "Artist-Name")))
    }

    @Test fun missingAmbiguousOrUnrelatedSessionsPreserveHostMetadata() {
        val track = NowPlayingUpdate.Track(title = "Lyric", artist = "Song-Artist")
        assertEquals(track, normalize(track))
        assertEquals(track, normalize(track, item("Other", "Artist")))
        assertEquals(track, normalize(track, item("Song", "Artist"), item("Song", "Artist")))
        assertEquals(track, normalize(track, item("Lyric", "Song-Artist"), item("Song", "Artist")))
        assertEquals(track, CarLifeMusicPresentation.normalize(track, item("Other", "Artist")))
    }

    @Test fun ordinaryAndPartialUpdatesAreNotRewritten() {
        val ordinary = NowPlayingUpdate.Track(title = "Song", artist = "Artist")
        assertEquals(ordinary, normalize(ordinary, item("Song", "Artist")))
        val partial = NowPlayingUpdate.Track(elapsedMs = 0)
        assertEquals(partial, normalize(partial, item("Song", "Artist")))
    }

    @Test fun invalidRealMetadataCannotBypassWireTextValidation() {
        val track = NowPlayingUpdate.Track(title = "Lyric", artist = "Song\u0000-Artist")
        assertEquals(track, normalize(track, item("Song\u0000", "Artist")))
    }

    @Test fun lyricRefreshFailureKeepsCoverAndRealTrackChangeStillClearsIt() {
        val references = mutableListOf<List<Pair<Int, ByteArray>>>()
        val publisher = NowPlayingArtwork({ 2 to 4096 }, { fields, _, _ -> references.add(fields); true },
            { _, _, _ -> true })
        publisher.linkReady(true)
        publisher.subscribe(true)
        val images = mutableListOf<ByteArray>()
        val state = HostArtworkState { images.add(it); publisher.update(it) }
        fun track(title: String, label: String = "Song-Artist", realTitle: String = "Song") =
            normalize(NowPlayingUpdate.Track(title = title, artist = label), item(realTitle, "Artist"))
        val first = track("First lyric")
        val initial = requireNotNull(state.begin(first.title, first.artist, true, listOf("cover")))
        state.complete(initial, byteArrayOf(1, 2))
        val next = track("Second lyric")
        assertNull(state.begin(next.title, next.artist, true, listOf("cover")))
        val failed = requireNotNull(state.begin(next.title, next.artist, true, listOf("refresh")))
        state.complete(failed, null)
        assertEquals(1, images.size)
        assertEquals(1, references.size)
        val changed = track("New lyric", "New-Artist", "New")
        assertNull(state.begin(changed.title, changed.artist, false, emptyList()))
        assertEquals(2, images.size)
        assertTrue(images.last().isEmpty())
    }
}

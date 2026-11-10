package io.github.iamr0s.carvex.session

import io.github.iamr0s.carvex.platform.MediaSessionSelection
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
}

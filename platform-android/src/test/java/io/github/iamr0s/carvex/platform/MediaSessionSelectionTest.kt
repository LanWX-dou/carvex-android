package io.github.iamr0s.carvex.platform

import org.junit.Assert.*
import org.junit.Test

class MediaSessionSelectionTest {
    private fun item(title: String?, artist: String? = null) = MediaSessionSelection.Item(title, artist)
    @Test fun onlyMatchingPlayerSuppliesState() {
        assertEquals(1, MediaSessionSelection.index(item("Song", "Artist"),
            listOf(item("Podcast", "Host"), item("Song", "Artist"))))
    }
    @Test fun identicalTitlesNeedArtistAndAmbiguityStaysUnknown() {
        val players = listOf(item("Song", "A"), item("Song", "B"))
        assertNull(MediaSessionSelection.index(item("Song"), players))
        assertEquals(1, MediaSessionSelection.index(item("Song", "B"), players))
        assertNull(MediaSessionSelection.index(item("Song", "C"), players))
    }
    @Test fun noHostTrackOrNoMatchingPlayerDoesNotInventStopped() {
        assertNull(MediaSessionSelection.index(item(null), listOf(item("Song"))))
        assertNull(MediaSessionSelection.index(item("Song"), emptyList()))
    }
}

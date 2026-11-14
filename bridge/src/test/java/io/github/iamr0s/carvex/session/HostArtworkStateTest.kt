package io.github.iamr0s.carvex.session

import io.github.iamr0s.carvex.carplay.core.NowPlayingArtwork
import org.junit.Assert.*
import org.junit.Test

class HostArtworkStateTest {
    private class Harness {
        val delivered = mutableListOf<ByteArray>()
        val state = HostArtworkState { delivered.add(it) }
        fun load(title: String, artist: String? = "Artist", source: String = "source",
                 image: ByteArray = byteArrayOf(1, 2)): HostArtworkState.Request {
            val request = requireNotNull(state.begin(title, artist, true, listOf(source)))
            state.complete(request, image)
            return request
        }
    }

    @Test fun metadataWithReplacementImageNeverPublishesAnIntermediateEmptyImage() {
        val h = Harness()
        h.load("Old")
        val request = requireNotNull(h.state.begin("New", "Artist", true, listOf("new-source")))
        assertEquals(1, h.delivered.size)
        h.state.complete(request, byteArrayOf(3, 4))
        assertEquals(2, h.delivered.size)
        assertTrue(h.delivered.all { it.isNotEmpty() })
        assertArrayEquals(byteArrayOf(3, 4), h.delivered.last())
    }

    @Test fun repeatedAlbumImageAcrossMetadataChangesRetainsOneFileReference() {
        val references = mutableListOf<List<Pair<Int, ByteArray>>>()
        val publisher = NowPlayingArtwork({ 2 to 4096 }, { fields, _, _ ->
            references.add(fields); true
        }, { _, _, _ -> true })
        publisher.linkReady(true)
        publisher.subscribe(true)
        val state = HostArtworkState(publisher::update)
        repeat(5) { index ->
            val request = requireNotNull(state.begin("Song $index", "Artist $index", true,
                listOf("source $index")))
            state.complete(request, byteArrayOf(1, 2))
        }
        assertEquals(1, references.size)
    }

    @Test fun newTrackWithoutArtworkClearsButPartialMetadataPreservesCurrentImage() {
        val h = Harness()
        h.load("Old")
        assertNull(h.state.begin(null, null, false, emptyList()))
        assertEquals(1, h.delivered.size)
        assertNull(h.state.begin("Old", null, false, emptyList()))
        assertEquals(1, h.delivered.size)
        assertNull(h.state.begin("New", "Artist", false, emptyList()))
        assertEquals(2, h.delivered.size)
        assertEquals(0, h.delivered.last().size)
    }

    @Test fun emptyArtworkSourceClearsAndRevokesPendingDecode() {
        val h = Harness()
        h.load("Old")
        val pending = requireNotNull(h.state.begin("New", "Artist", true, listOf("pending")))
        assertNull(h.state.begin("New", "Artist", true, emptyList()))
        h.state.complete(pending, byteArrayOf(9))
        assertEquals(2, h.delivered.size)
        assertEquals(0, h.delivered.last().size)
    }

    @Test fun failedReplacementClearsPreviousTracksImageEvenAfterAnotherSourceUpdate() {
        val h = Harness()
        h.load("Old")
        val first = requireNotNull(h.state.begin("New", "Artist", true, listOf("first")))
        val second = requireNotNull(h.state.begin("New", "Artist", true, listOf("second")))
        h.state.complete(first, byteArrayOf(7))
        assertEquals(1, h.delivered.size)
        h.state.complete(second, null)
        assertEquals(2, h.delivered.size)
        assertEquals(0, h.delivered.last().size)
    }

    @Test fun failedImageRefreshForSameTrackKeepsItsExistingImage() {
        val h = Harness()
        h.load("Song")
        val request = requireNotNull(h.state.begin("Song", "Artist", true, listOf("unavailable")))
        h.state.complete(request, null)
        assertEquals(1, h.delivered.size)
    }

    @Test fun failedReplacementCanRecoverOnALaterIdenticalHostUpdate() {
        val h = Harness()
        h.load("Old")
        val failed = requireNotNull(h.state.begin("New", "Artist", true, listOf("source")))
        assertNull(h.state.begin("New", "Artist", true, listOf("source")))
        h.state.complete(failed, null)
        assertEquals(0, h.delivered.last().size)

        val retry = requireNotNull(h.state.begin("New", "Artist", true, listOf("source")))
        assertTrue(retry.generation > failed.generation)
        h.state.complete(failed, byteArrayOf(9))
        assertEquals(2, h.delivered.size)
        h.state.complete(retry, byteArrayOf(3, 4))
        assertArrayEquals(byteArrayOf(3, 4), h.delivered.last())
        assertNull(h.state.begin("New", "Artist", true, listOf("source")))
    }

    @Test fun failedRefreshRetriesWithoutClearingOrRepublishingTheSameImage() {
        val h = Harness()
        h.load("Song")
        val failed = requireNotNull(h.state.begin("Song", "Artist", true, listOf("refresh")))
        h.state.complete(failed, null)
        val retry = requireNotNull(h.state.begin("Song", "Artist", true, listOf("refresh")))
        assertEquals(1, h.delivered.size)
        h.state.complete(retry, byteArrayOf(1, 2))
        assertEquals(1, h.delivered.size)
        assertNull(h.state.begin("Song", "Artist", true, listOf("refresh")))
    }

    @Test fun staleFailureCannotInvalidateANewerSuccessfulSource() {
        val h = Harness()
        val old = requireNotNull(h.state.begin("Old", "Artist", true, listOf("old")))
        h.load("New", source = "new")
        h.state.complete(old, null)
        assertNull(h.state.begin("New", "Artist", true, listOf("new")))
        assertEquals(1, h.delivered.size)
        h.state.close()
        assertNull(h.state.begin("New", "Artist", true, listOf("new")))
    }

    @Test fun metadataOnlyTrackChangeAndCloseRejectLateDecodes() {
        val h = Harness()
        val old = requireNotNull(h.state.begin("Old", "Artist", true, listOf("source")))
        assertTrue(h.state.track("New", "Artist"))
        h.state.complete(old, byteArrayOf(8))
        assertEquals(1, h.delivered.size)
        assertEquals(0, h.delivered.single().size)
        val pending = requireNotNull(h.state.begin("New", "Artist", true, listOf("source")))
        h.state.close()
        h.state.complete(pending, byteArrayOf(9))
        assertNull(h.state.begin("Other", "Artist", true, listOf("source")))
        assertEquals(1, h.delivered.size)
    }

    @Test fun identicalSourceKeepsItsInFlightRequestAndImagesAreCopied() {
        val h = Harness()
        val request = requireNotNull(h.state.begin("Song", "Artist", true, listOf("source")))
        assertNull(h.state.begin("Song", null, true, listOf("source")))
        val image = byteArrayOf(1, 2)
        h.state.complete(request, image)
        image[0] = 8
        h.delivered.single()[0] = 9
        val refresh = requireNotNull(h.state.begin("Song", "Artist", true, listOf("refresh")))
        h.state.complete(refresh, byteArrayOf(1, 2))
        assertEquals(1, h.delivered.size)
    }
}

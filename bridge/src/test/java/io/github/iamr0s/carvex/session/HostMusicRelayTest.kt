package io.github.iamr0s.carvex.session

import io.github.iamr0s.carvex.carplay.core.*
import org.junit.Assert.*
import org.junit.Test

class HostMusicRelayTest {
    private val selection = IapFields(listOf(
        0 to IapWire.fields(listOf(1 to byteArrayOf(), 6 to byteArrayOf())),
        1 to IapWire.fields(listOf(1 to byteArrayOf()))))

    @Test fun progressBeforeAirSessionPreservesSongForFirstSubscription() {
        val relay = HostMusicRelay()
        relay.update(NowPlayingUpdate.Track(title="Song", album="Album"))
        relay.update(CarLifeMusicIntent.parsePayload("carlife_vehicle_music_progress",
            mapOf("curTime" to 1234L, "duration" to 180000L))!!)
        val sent = mutableListOf<List<Pair<Int,ByteArray>>>()
        val publisher = NowPlayingPublisher { sent.add(it); true }
        relay.attach { track, replace -> publisher.update(track, replace) }
        publisher.linkReady(true)
        assertTrue(publisher.command(0x5000, selection))
        assertEquals(2, sent.size) // Protocol defaults, then the complete real snapshot.
        val media = IapWire.parseFieldList(sent.last().first{it.first==0}.second)
        assertArrayEquals(IapWire.cstring("Song"), media.ordered.first{it.first==1}.second)
        assertArrayEquals(IapWire.cstring("Album"), media.ordered.first{it.first==6}.second)
        val playback = IapWire.parseFieldList(sent.last().first{it.first==1}.second)
        assertArrayEquals(IapWire.be32(1234), playback.ordered.first{it.first==1}.second)
    }

    @Test fun progressAndSongCallbacksDeliverTheirOwnDeltasInOrder() {
        val relay = HostMusicRelay()
        val sent = mutableListOf<Pair<NowPlayingUpdate.Track,Boolean>>()
        relay.attach { track, replace -> sent.add(track to replace) }
        relay.update(NowPlayingUpdate.Track(title="Old"), true)
        relay.update(NowPlayingUpdate.Track(elapsedMs=100))
        relay.update(NowPlayingUpdate.Track(title="New"), true)
        relay.update(NowPlayingUpdate.Track(elapsedMs=0))
        assertEquals(listOf("Old",null,"New",null), sent.map{it.first.title})
        assertEquals(listOf(true,false,true,false), sent.map{it.second})
        var replay: NowPlayingUpdate.Track? = null
        relay.attach { track, _ -> replay=track }
        assertEquals("New", replay?.title)
        assertEquals(0L, replay?.elapsedMs)
        assertNull(replay?.status)
    }

    @Test fun partialAlbumUpdateSurvivesLaterProgressAndResubscription() {
        val relay=HostMusicRelay()
        relay.update(NowPlayingUpdate.Track(title="Song"), true)
        relay.update(NowPlayingUpdate.Track(album="Album"))
        relay.update(NowPlayingUpdate.Track(elapsedMs=42))
        var snapshot:NowPlayingUpdate.Track?=null
        relay.attach{track,_->snapshot=track}
        assertEquals("Song",snapshot?.title)
        assertEquals("Album",snapshot?.album)
        assertEquals(42L,snapshot?.elapsedMs)
    }
}

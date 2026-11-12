package io.github.iamr0s.carvex.carplay.core

import org.junit.Assert.*
import org.junit.Test

class NowPlayingSetInfoTest {
    private val subscribe=IapFields(listOf(1 to IapWire.fields(listOf(1 to byteArrayOf(),2 to byteArrayOf()))))
    @Test fun rawU32AndOnlyFfffffffAutoWindowArePreserved() {
        val parsed=NowPlayingUpdate.parseSetInfo(IapFields(listOf(0 to IapWire.be32(0),
            1 to IapWire.be32(0xffffffffL),2 to IapWire.be32(0x80000000L),99 to byteArrayOf(1))))!!
        assertEquals(0L,parsed.elapsedValue);assertEquals(0xffffffffL,parsed.queueIndex)
        assertEquals(0x80000000L,parsed.queueWindowStart);assertFalse(parsed.autoWindow)
        assertTrue(NowPlayingUpdate.parseSetInfo(IapFields(listOf(2 to IapWire.be32(0xffffffffL))))!!.autoWindow)
        assertNull(NowPlayingUpdate.parseSetInfo(IapFields(listOf(0 to IapWire.be32(42),1 to byteArrayOf(0)))))
    }
    @Test fun absentProviderNeverWritesRequestedValuesIntoObservedSnapshot() {
        val sent=mutableListOf<List<Pair<Int,ByteArray>>>()
        val logs=mutableListOf<String>()
        val publisher=NowPlayingPublisher({fields->sent+=fields;true},logs::add)
        publisher.linkReady(true);publisher.command(0x5000,subscribe)
        publisher.update(NowPlayingUpdate.Track(elapsedMs=10,queueIndex=2))
        val before=sent.size
        assertFalse(publisher.setInfo(IapFields(listOf(0 to IapWire.be32(100),1 to IapWire.be32(7)))))
        assertEquals(before,sent.size)
        publisher.command(0x5000,subscribe)
        val playback=IapWire.parseFieldList(sent.last().single().second)
        assertArrayEquals(IapWire.be32(10),playback[1]);assertArrayEquals(IapWire.be32(2),playback[2])
        assertTrue(logs.any{it.contains("parsed=true")&&it.contains("no-player-provider")})
    }
    @Test fun platformRequestAcceptanceHasNo5001SideEffectAndWindowGateIsIndependent() {
        val requests=mutableListOf<NowPlayingUpdate.SetInfo>()
        var sent=0
        val publisher=NowPlayingPublisher({_,_->sent++;true},{},{requests+=it;true})
        publisher.linkReady(true) // No START: elapsed/index can still reach an actual provider.
        assertTrue(publisher.setInfo(IapFields(listOf(0 to IapWire.be32(42),2 to IapWire.be32(7)))))
        assertEquals(NowPlayingUpdate.SetInfo(elapsedValue=42),requests.single())
        assertEquals(0,sent)
        assertFalse(publisher.setInfo(IapFields(listOf(2 to IapWire.be32(7)))))
        assertEquals(1,requests.size)
        publisher.command(0x5000,IapFields(listOf(1 to IapWire.fields(listOf(0x11 to IapWire.be32(0))))))
        assertTrue(publisher.setInfo(IapFields(listOf(2 to IapWire.be32(0xffffffffL)))))
        assertTrue(requests.last().autoWindow)
        publisher.command(0x5002,IapFields(emptyList()))
        assertFalse(publisher.setInfo(IapFields(listOf(2 to IapWire.be32(0)))))
        assertEquals(0,sent)
    }
    @Test fun malformedRequestIsAtomicAndProviderRejectionIsNotObservedExecution() {
        var calls=0
        val publisher=NowPlayingPublisher({_,_->fail("request must not emit a snapshot");true},{},{calls++;false})
        publisher.linkReady(true)
        assertFalse(publisher.setInfo(IapFields(listOf(0 to IapWire.be32(42),1 to byteArrayOf()))))
        assertEquals(0,calls)
        assertFalse(publisher.setInfo(IapFields(listOf(1 to IapWire.be32(1)))))
        assertEquals(1,calls)
        assertTrue(publisher.setInfo(IapFields(listOf(99 to byteArrayOf()))))
        assertEquals(1,calls)
        publisher.close()
        assertFalse(publisher.setInfo(IapFields(listOf(1 to IapWire.be32(1)))))
        assertEquals(1,calls)
    }
}

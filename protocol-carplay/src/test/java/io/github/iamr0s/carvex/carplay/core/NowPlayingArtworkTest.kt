package io.github.iamr0s.carvex.carplay.core

import org.junit.Assert.*
import org.junit.Test

class NowPlayingArtworkTest {
    private class Harness(version:Int=1,mtu:Int=16) {
        data class Packet(val bytes:ByteArray,val valid:()->Boolean,val ack:(Throwable?)->Unit)
        var time=0L
        var supported=true
        val references=mutableListOf<Pair<Int,(Throwable?)->Unit>>()
        val referenceGuards=mutableListOf<()->Boolean>()
        val packets=mutableListOf<Packet>()
        val logs=mutableListOf<String>()
        val publisher=NowPlayingArtwork({if(supported)version to mtu else null}, {fields,valid,ack->
            val id=IapWire.parseFieldList(fields.single().second).ordered.single().second.single().toInt() and 255
            references.add(id to ack);referenceGuards+=valid;true
        },{data,valid,ack->packets.add(Packet(data,valid,ack));true},logs::add,{time})
        fun ready(){publisher.linkReady(true);publisher.subscribe(true)}
        fun reply(op:Int,id:Int=references.last().first){publisher.receive(byteArrayOf(id.toByte(),op.toByte()))}
        fun start(bytes:ByteArray){ready();publisher.update(bytes);references.last().second(null)}
    }
    @Test fun firmwareSetupAndFirstLastHeadersMatchGoldenBytes() {
        assertArrayEquals(byteArrayOf(0x80.toByte(),4,0,0,0,0,0,0,0,3),ArtworkFileWire.setup(128,3,1))
        assertArrayEquals(byteArrayOf(0x80.toByte(),4,0,0,0,0,0,0,0,3,0,2),ArtworkFileWire.setup(128,3,2))
        assertArrayEquals(byteArrayOf(0x80.toByte(),0xc0.toByte(),1,2,3),ArtworkFileWire.chunk(128,byteArrayOf(1,2,3),0,12))
        assertArrayEquals(byteArrayOf(0x80.toByte(),0xc0.toByte()),ArtworkFileWire.chunk(128,byteArrayOf(),0,12))
    }
    @Test fun waitsForReferenceAckAndReceiverStartThenPreservesAllBytesAcrossMtu() {
        val h=Harness();val data=ByteArray(40){it.toByte()}
        h.publisher.update(data);assertTrue(h.references.isEmpty())
        h.ready();assertEquals(1,h.references.size);assertTrue(h.packets.isEmpty())
        h.references.single().second(null)
        h.packets.single().ack(null);assertEquals(1,h.packets.size)
        h.reply(1)
        for(index in 1..3)h.packets[index].ack(null)
        val payloads=h.packets.drop(1).map{it.bytes}
        assertEquals(listOf(0x80,0,0x40),payloads.map{it[1].toInt() and 255})
        assertArrayEquals(data,payloads.flatMap{it.drop(2)}.toByteArray())
        assertFalse(h.logs.any{it.contains("result=accepted")})
        h.reply(5);assertTrue(h.logs.any{it.contains("result=accepted")})
    }
    @Test fun receiverStartBeforeSetupAckDoesNotDuplicateFirstPacket() {
        val h=Harness();h.start(byteArrayOf(1,2,3));h.reply(1)
        assertEquals(1,h.packets.size)
        h.packets[0].ack(null);assertEquals(2,h.packets.size)
        h.reply(1);assertEquals(2,h.packets.size)
        h.reply(5);h.packets[1].ack(null)
        assertEquals(2,h.packets.size)
    }
    @Test fun replacingSongRevokesOldQueuedDataAndLateCallbacks() {
        val h=Harness();h.start(ByteArray(40));h.packets[0].ack(null);h.reply(1)
        val oldId=h.references[0].first;val oldPacket=h.packets[1]
        h.publisher.update(byteArrayOf(7,8))
        assertFalse(h.referenceGuards.first()());assertTrue(h.referenceGuards.last()())
        assertFalse(oldPacket.valid());assertNotEquals(oldId,h.references.last().first)
        oldPacket.ack(null);h.reply(5,oldId)
        assertFalse(h.logs.any{it.contains("result=accepted")})
        assertEquals(3,h.packets.size) // Setup, old data and cancellation only.
    }
    @Test fun unsubscribeAndNewLinkRejectOldCallbacksAndRequireNewSubscription() {
        val h=Harness();h.start(byteArrayOf(1));val oldAck=h.references[0].second
        h.publisher.subscribe(false);assertFalse(h.packets[0].valid())
        assertFalse(h.referenceGuards.first()())
        val cancelled=h.packets.last()
        h.publisher.linkReady(false);h.publisher.linkReady(true)
        assertFalse(cancelled.valid())
        oldAck(null);h.reply(1)
        assertEquals(1,h.references.size)
        h.publisher.subscribe(true);assertEquals(2,h.references.size)
    }
    @Test fun pauseResumeAndCancelAreFileControlsNotLinkAcknowledgements() {
        val h=Harness();h.start(ByteArray(40));h.packets[0].ack(null);h.reply(1)
        h.reply(3);h.packets[1].ack(null)
        assertEquals(3,h.packets.size);assertEquals(3,h.packets.last().bytes[1].toInt())
        h.reply(1);assertEquals(4,h.packets.size)
        h.reply(2);assertFalse(h.packets[3].valid())
        assertEquals(2,h.packets.last().bytes[1].toInt())
    }
    @Test fun missingFileSessionOversizeAndTimeoutStayBounded() {
        val h=Harness();h.supported=false;h.ready();h.publisher.update(byteArrayOf(1))
        assertTrue(h.references.isEmpty())
        assertThrows(IllegalArgumentException::class.java){h.publisher.update(ByteArray(ArtworkFileWire.MAX_BYTES+1))}
        h.supported=true;h.publisher.subscribe(true);h.references[0].second(null)
        h.time=31_000_000_000L;h.publisher.expire()
        assertFalse(h.packets[0].valid());assertTrue(h.logs.any{it.contains("timeout")})
    }
    @Test fun repeatedSameArtworkDoesNotRetransmitAndEmptyImageClearsIt() {
        val h=Harness(2);h.start(byteArrayOf(1))
        h.publisher.update(byteArrayOf(1));assertEquals(1,h.references.size)
        h.publisher.update(byteArrayOf());assertEquals(2,h.references.size)
        h.references.last().second(null);h.packets.last().ack(null);h.reply(1)
        assertEquals(2,h.packets.last().bytes.size)
        assertEquals(0xc0,h.packets.last().bytes[1].toInt() and 255)
    }
    @Test fun artworkOnlySubscriptionAndStopDriveFilePublisher() {
        val sent=mutableListOf<Boolean>()
        val publisher=NowPlayingPublisher{true}
        publisher.artworkSelectionChanged={sent.add(it)}
        publisher.linkReady(true)
        assertTrue(publisher.command(0x5000,IapFields(listOf(0 to IapWire.fields(listOf(26 to byteArrayOf()))))))
        assertTrue(sent.last())
        publisher.command(0x5002,IapFields(emptyList()));assertFalse(sent.last())
    }
    @Test fun failedReplacementSubscriptionRevokesPreviousArtworkButMalformedStartDoesNot() {
        val selected=mutableListOf<Boolean>()
        val publisher=NowPlayingPublisher{false}
        publisher.artworkSelectionChanged={selected.add(it)}
        publisher.linkReady(true)
        publisher.command(0x5000,IapFields(listOf(0 to IapWire.fields(listOf(26 to byteArrayOf())))))
        assertTrue(selected.last())
        assertFalse(publisher.command(0x5000,IapFields(listOf(0 to IapWire.fields(listOf(26 to byteArrayOf(1)))))))
        assertTrue(selected.last())
        assertFalse(publisher.command(0x5000,IapFields(listOf(0 to IapWire.fields(listOf(1 to byteArrayOf()))))))
        assertFalse(selected.last())
    }
    @Test fun guardsDoNotAcquireArtworkMonitorAndClosedOwnerCannotRestart() {
        val h=Harness();h.start(byteArrayOf(1))
        val executor=java.util.concurrent.Executors.newSingleThreadExecutor()
        try {
            synchronized(h.publisher){
                assertTrue(executor.submit<Boolean>{h.referenceGuards.first()()&&h.packets.first().valid()}
                    .get(1,java.util.concurrent.TimeUnit.SECONDS))
            }
            h.publisher.close();h.publisher.close();h.ready();h.publisher.update(byteArrayOf(2))
            assertFalse(h.referenceGuards.first()());assertFalse(h.packets.first().valid())
            assertEquals(1,h.references.size)
            h.references.first().second(null)
            assertEquals(1,h.packets.size)
        } finally {executor.shutdownNow()}
    }
}

package io.github.iamr0s.carvex.carplay.core

import io.github.iamr0s.carvex.sessioncore.AcceptedIdentification
import io.github.iamr0s.carvex.sessioncore.IdentifyInfo
import org.junit.Assert.*
import org.junit.Test
import java.io.ByteArrayInputStream
import java.io.ByteArrayOutputStream
import java.util.concurrent.*

/** Real ordered writer with synthetic peers: local revocation, not vehicle behavior. */
class NowPlayingGuardedTransportTest {
    private val titleSelection=IapFields(listOf(0 to IapWire.fields(listOf(1 to byteArrayOf()))))
    private val artistSelection=IapFields(listOf(0 to IapWire.fields(listOf(12 to byteArrayOf()))))

    private class Peer(packetSize:Int=2048):AutoCloseable {
        val output=LinkedBlockingQueue<IapWire.Frame>()
        val ready=CountDownLatch(1)
        val states=CopyOnWriteArrayList<RuntimeIapState>()
        val failures=LinkedBlockingQueue<Throwable>()
        val runtime=RuntimeIap({bytes->output.offer(IapWire.read(ByteArrayInputStream(bytes)))},{},{state->
            states+=state
            if(state==RuntimeIapState.CONTROL_READY)ready.countDown()
        },negotiate={link->AcceptedIdentification(link.generation,link.linkEpoch,IdentifyInfo())})
        val publisher=NowPlayingPublisher({fields,valid->
            runtime.sendGuarded(0x5001,fields,valid){it?.let(failures::offer)}
        },{})
        init {
            val syn=byteArrayOf(1,1)+IapWire.be16(packetSize)+IapWire.be16(1000)+
                IapWire.be16(73)+byteArrayOf(1,1,10,0,1)
            assertTrue(runtime.accept(IapWire.packet(IapWire.Frame(0x80,30,0,0,syn))))
            ack(next().seq)
            assertTrue(ready.await(2,TimeUnit.SECONDS))
            publisher.linkReady(true)
        }
        fun next():IapWire.Frame=requireNotNull(output.poll(2,TimeUnit.SECONDS)){"missing output"}
        fun ack(seq:Int){assertTrue(runtime.accept(IapWire.packet(IapWire.Frame(0x40,30,seq,0,byteArrayOf()))))}
        fun finish(){publisher.linkReady(false)}
        override fun close(){finish();runtime.close()}
    }

    private fun cancellation(revoke:(NowPlayingPublisher)->Unit,expectFreshInitial:Boolean=false) {
        Peer().use { peer->
            assertTrue(peer.publisher.command(0x5000,titleSelection))
            peer.ack(peer.next().seq)
            assertTrue(peer.runtime.send(0x5702,emptyList()))
            val held=peer.next() // Withhold ACK to hold the serial writer.
            assertTrue(peer.publisher.update(NowPlayingUpdate.Track(title="old")))
            revoke(peer.publisher)
            val done=CompletableFuture<Throwable?>()
            assertTrue(peer.runtime.send(0x5702,emptyList()){done.complete(it)})
            peer.ack(held.seq)
            var previous=held.seq
            if(expectFreshInitial){
                val fresh=peer.next()
                assertEquals((previous+1) and 255,fresh.seq)
                assertEquals(0x5001,IapWire.u16(fresh.payload,4))
                val body=IapWire.parseFieldList(fresh.payload.copyOfRange(6,fresh.payload.size))
                assertEquals(listOf(12),IapWire.parseFieldList(body[0]!!).ordered.map{it.first})
                peer.ack(fresh.seq);previous=fresh.seq
            }
            val sentinel=peer.next()
            assertEquals((previous+1) and 255,sentinel.seq)
            assertEquals(0x5702,IapWire.u16(sentinel.payload,4))
            peer.ack(sentinel.seq)
            assertNull(done.get(2,TimeUnit.SECONDS))
            assertTrue(peer.failures.poll(2,TimeUnit.SECONDS) is StaleIapSendException)
            assertFalse(peer.states.contains(RuntimeIapState.DEGRADED))
        }
    }

    @Test(timeout=8000) fun stopRevokesQueuedMusicBeforeSequenceAllocation()=cancellation({
        assertTrue(it.command(0x5002,IapFields(emptyList())))
    })
    @Test(timeout=8000) fun replacementRevokesOldSelectionAndKeepsNewInitialization()=cancellation({
        assertTrue(it.command(0x5000,artistSelection))
    },true)
    @Test(timeout=8000) fun linkInvalidationRevokesQueuedMusic()=cancellation({it.linkReady(false)})
    @Test(timeout=8000) fun aNewLinkNeedsItsOwnStart()=cancellation({it.linkReady(false);it.linkReady(true)})
    @Test(timeout=8000) fun closeRevokesQueuedMusicAndCannotBeReopened()=cancellation({
        it.close();it.close();it.linkReady(true)
        assertFalse(it.command(0x5000,titleSelection))
        assertFalse(it.update(NowPlayingUpdate.Track(title="late")))
    })

    @Test(timeout=8000) fun malformedStartDoesNotRevokeValidQueuedMusic() {
        Peer().use { peer->
            assertTrue(peer.publisher.command(0x5000,titleSelection));peer.ack(peer.next().seq)
            assertTrue(peer.runtime.send(0x5702,emptyList()));val held=peer.next()
            assertTrue(peer.publisher.update(NowPlayingUpdate.Track(title="kept")))
            assertFalse(peer.publisher.command(0x5000,IapFields(listOf(0 to IapWire.fields(
                listOf(1 to byteArrayOf(7)))))))
            peer.ack(held.seq)
            val music=peer.next();assertEquals((held.seq+1) and 255,music.seq)
            assertEquals(0x5001,IapWire.u16(music.payload,4))
            peer.ack(music.seq)
            val done=CompletableFuture<Throwable?>()
            assertTrue(peer.runtime.send(0x5702,emptyList()){done.complete(it)})
            peer.ack(peer.next().seq);assertNull(done.get(2,TimeUnit.SECONDS))
            assertTrue(peer.failures.isEmpty())
        }
    }

    @Test(timeout=8000) fun committedMusicFragmentsCompleteAfterStop() {
        Peer(128).use { peer->
            assertTrue(peer.publisher.command(0x5000,titleSelection));peer.ack(peer.next().seq)
            val track=NowPlayingUpdate.Track(title="x".repeat(400))
            val expected=IapWire.csm(0x5001,NowPlayingUpdate.fields(track,NowPlayingUpdate.selection(titleSelection)!!))
            assertTrue(peer.publisher.update(track))
            val bytes=ByteArrayOutputStream()
            var previous=-1
            while(bytes.size()<expected.size){
                val frame=peer.next()
                if(previous>=0)assertEquals((previous+1) and 255,frame.seq)
                previous=frame.seq;bytes.write(frame.payload)
                peer.publisher.command(0x5002,IapFields(emptyList()))
                peer.ack(frame.seq)
            }
            assertArrayEquals(expected,bytes.toByteArray())
            val done=CompletableFuture<Throwable?>()
            peer.runtime.send(0x5702,emptyList()){done.complete(it)}
            peer.ack(peer.next().seq);assertNull(done.get(2,TimeUnit.SECONDS))
            assertTrue(peer.failures.isEmpty())
            assertFalse(peer.states.contains(RuntimeIapState.DEGRADED))
        }
    }
}

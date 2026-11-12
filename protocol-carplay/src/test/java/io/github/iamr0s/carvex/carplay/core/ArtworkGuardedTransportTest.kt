package io.github.iamr0s.carvex.carplay.core

import io.github.iamr0s.carvex.sessioncore.AcceptedIdentification
import io.github.iamr0s.carvex.sessioncore.IdentifyInfo
import org.junit.Assert.*
import org.junit.Test
import java.io.ByteArrayInputStream
import java.util.concurrent.*
import java.util.concurrent.atomic.AtomicBoolean

class ArtworkGuardedTransportTest {
    private class Peer:AutoCloseable {
        val output=LinkedBlockingQueue<IapWire.Frame>()
        val ready=CountDownLatch(1)
        val states=CopyOnWriteArrayList<RuntimeIapState>()
        val runtime=RuntimeIap({bytes->output.offer(IapWire.read(ByteArrayInputStream(bytes)))},{},{state->
            states+=state;if(state==RuntimeIapState.CONTROL_READY)ready.countDown()
        },negotiate={link->AcceptedIdentification(link.generation,link.linkEpoch,IdentifyInfo())})
        init {
            val syn=byteArrayOf(1,1)+IapWire.be16(2048)+IapWire.be16(1000)+IapWire.be16(73)+
                byteArrayOf(1,1,10,0,1,11,1,1)
            assertTrue(runtime.accept(IapWire.packet(IapWire.Frame(0x80,30,0,0,syn))))
            ack(next().seq);assertTrue(ready.await(2,TimeUnit.SECONDS))
            assertNotNull(runtime.fileSession())
        }
        fun next():IapWire.Frame=requireNotNull(output.poll(2,TimeUnit.SECONDS)){"missing output"}
        fun ack(seq:Int){assertTrue(runtime.accept(IapWire.packet(IapWire.Frame(0x40,30,seq,0,byteArrayOf()))))}
        override fun close(){runtime.close()}
    }

    @Test(timeout=8000) fun staleFileWorkHasNoSequenceAndDoesNotDegradeRuntime() {
        Peer().use { peer->
            peer.runtime.send(0x5702,emptyList());val held=peer.next()
            val valid=AtomicBoolean(true)
            val cancelled=CompletableFuture<Throwable?>()
            assertTrue(peer.runtime.sendFile(ArtworkFileWire.setup(128,1,1),{valid.get()}){cancelled.complete(it)})
            valid.set(false)
            val done=CompletableFuture<Throwable?>()
            peer.runtime.send(0x5702,emptyList()){done.complete(it)}
            peer.ack(held.seq)
            assertTrue(cancelled.get(2,TimeUnit.SECONDS) is StaleIapSendException)
            val next=peer.next();assertEquals((held.seq+1) and 255,next.seq)
            assertEquals(10,next.session);assertEquals(0x5702,IapWire.u16(next.payload,4))
            peer.ack(next.seq);assertNull(done.get(2,TimeUnit.SECONDS))
            assertFalse(peer.states.contains(RuntimeIapState.DEGRADED))
        }
    }

    @Test(timeout=8000) fun oldArtworkReferenceCannotCommitAfterReplacement() {
        Peer().use { peer->
            val completions=LinkedBlockingQueue<Throwable>()
            val art=NowPlayingArtwork({peer.runtime.fileSession()},{fields,valid,complete->
                peer.runtime.sendGuarded(0x5001,fields,valid){error->error?.let(completions::offer);complete(error)}
            },{bytes,valid,complete->peer.runtime.sendFile(bytes,valid,complete)})
            try {
                peer.runtime.send(0x5702,emptyList());val held=peer.next()
                art.linkReady(true);art.subscribe(true);art.update(byteArrayOf(1));art.update(byteArrayOf(2))
                val done=CompletableFuture<Throwable?>()
                peer.runtime.send(0x5702,emptyList()){done.complete(it)}
                peer.ack(held.seq)
                val cancel=peer.next();assertEquals((held.seq+1) and 255,cancel.seq)
                assertEquals(11,cancel.session);assertArrayEquals(byteArrayOf(128.toByte(),2),cancel.payload)
                peer.ack(cancel.seq)
                val reference=peer.next();assertEquals((cancel.seq+1) and 255,reference.seq)
                assertEquals(10,reference.session)
                val group=IapWire.parseFieldList(reference.payload.copyOfRange(6,reference.payload.size))[0]!!
                assertArrayEquals(byteArrayOf(129.toByte()),IapWire.parseFieldList(group)[26])
                peer.ack(reference.seq)
                val sentinel=peer.next();assertEquals(0x5702,IapWire.u16(sentinel.payload,4))
                peer.ack(sentinel.seq);assertNull(done.get(2,TimeUnit.SECONDS))
                assertTrue(completions.poll(2,TimeUnit.SECONDS) is StaleIapSendException)
                // Only the new reference's completion can enqueue SETUP.
                val setup=peer.next();assertEquals(11,setup.session)
                assertArrayEquals(ArtworkFileWire.setup(129,1,1),setup.payload);peer.ack(setup.seq)
                assertFalse(peer.states.contains(RuntimeIapState.DEGRADED))
            } finally {art.close()}
        }
    }
}

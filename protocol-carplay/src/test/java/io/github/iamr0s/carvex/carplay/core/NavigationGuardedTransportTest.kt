package io.github.iamr0s.carvex.carplay.core

import io.github.iamr0s.carvex.sessioncore.AcceptedIdentification
import io.github.iamr0s.carvex.sessioncore.IdentifyInfo
import org.junit.Assert.*
import org.junit.Test
import java.io.ByteArrayInputStream
import java.util.concurrent.*
import java.util.concurrent.atomic.AtomicBoolean

/** Synthetic peers verify local revocation and reliability, not Apple field semantics. */
class NavigationGuardedTransportTest {
    private class Peer(packetSize: Int = 2048) : AutoCloseable {
        val output = LinkedBlockingQueue<IapWire.Frame>()
        val ready = CountDownLatch(1)
        val degraded = CountDownLatch(1)
        val reject = AtomicBoolean()
        val states = CopyOnWriteArrayList<RuntimeIapState>()
        val runtime = RuntimeIap({ bytes ->
            val frame = IapWire.read(ByteArrayInputStream(bytes))
            if (reject.get() && frame.payload.isNotEmpty()) false else { output.offer(frame); true }
        }, {}, { state ->
            states += state
            if (state == RuntimeIapState.CONTROL_READY) ready.countDown()
            if (state == RuntimeIapState.DEGRADED) degraded.countDown()
        }, negotiate = { link -> AcceptedIdentification(link.generation, link.linkEpoch, IdentifyInfo()) })
        init {
            val syn = byteArrayOf(1, 1) + IapWire.be16(packetSize) + IapWire.be16(1000) +
                IapWire.be16(73) + byteArrayOf(1, 1, 10, 0, 1)
            assertTrue(runtime.accept(IapWire.packet(IapWire.Frame(0x80, 30, 0, 0, syn))))
            val response = next()
            ack(response.seq)
            assertTrue(ready.await(2, TimeUnit.SECONDS))
        }
        fun next(): IapWire.Frame = requireNotNull(output.poll(2, TimeUnit.SECONDS)) { "missing peer output" }
        fun ack(seq: Int) { assertTrue(runtime.accept(IapWire.packet(IapWire.Frame(0x40, 30, seq, 0, byteArrayOf())))) }
        override fun close() { runtime.close() }
    }

    @Test(timeout = 8000) fun staleQueuedMessageConsumesNoSequenceAndDoesNotDegradeLink() {
        Peer().use { peer ->
            assertTrue(peer.runtime.send(0x5702, emptyList()))
            val first = peer.next() // Hold its ACK to keep the ordered sender busy.
            val valid = AtomicBoolean(true)
            val cancelled = CompletableFuture<Throwable?>()
            assertTrue(peer.runtime.sendGuarded(0x5201, listOf(1 to byteArrayOf(1)), { valid.get() }) { cancelled.complete(it) })
            val done = CompletableFuture<Throwable?>()
            assertTrue(peer.runtime.send(0x5702, emptyList()) { done.complete(it) })
            valid.set(false)
            peer.ack(first.seq)
            assertTrue(cancelled.get(2, TimeUnit.SECONDS) is StaleIapSendException)
            val next = peer.next()
            assertEquals((first.seq + 1) and 255, next.seq)
            assertEquals(0x5702, IapWire.u16(next.payload, 4))
            peer.ack(next.seq)
            assertNull(done.get(2, TimeUnit.SECONDS))
            assertFalse(peer.states.contains(RuntimeIapState.DEGRADED))
            assertEquals(RuntimeIapState.CONTROL_READY, peer.states.last())
        }
    }

    @Test(timeout = 8000) fun committedFragmentedCsmFinishesAfterLocalRevocation() {
        Peer(128).use { peer ->
            val valid = AtomicBoolean(true)
            val done = CompletableFuture<Throwable?>()
            val fields = listOf(3 to IapWire.cstring("x".repeat(400)))
            val expected = IapWire.csm(0x5201, fields)
            assertTrue(peer.runtime.sendGuarded(0x5201, fields, { valid.get() }) { done.complete(it) })
            val chunks = java.io.ByteArrayOutputStream()
            var lastSeq = -1
            while (chunks.size() < expected.size) {
                val frame = peer.next()
                if (lastSeq >= 0) assertEquals((lastSeq + 1) and 255, frame.seq)
                lastSeq = frame.seq
                chunks.write(frame.payload)
                valid.set(false) // The CSM has already committed; do not cut its later fragments.
                peer.ack(frame.seq)
            }
            assertArrayEquals(expected, chunks.toByteArray())
            assertNull(done.get(2, TimeUnit.SECONDS))
            assertFalse(peer.states.contains(RuntimeIapState.DEGRADED))
        }
    }

    @Test(timeout = 8000) fun realTransportRejectionStillDegradesGuardedSend() {
        Peer().use { peer ->
            val done = CompletableFuture<Throwable?>()
            peer.reject.set(true)
            assertTrue(peer.runtime.sendGuarded(0x5201, listOf(1 to byteArrayOf(1)), { true }) { done.complete(it) })
            assertTrue(peer.degraded.await(2, TimeUnit.SECONDS))
            assertNotNull(done.get(2, TimeUnit.SECONDS))
            assertEquals(RuntimeIapState.DEGRADED, peer.states.last())
        }
    }
}

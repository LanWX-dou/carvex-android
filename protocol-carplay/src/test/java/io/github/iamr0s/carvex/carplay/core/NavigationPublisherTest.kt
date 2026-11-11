package io.github.iamr0s.carvex.carplay.core

import io.github.iamr0s.carvex.protocol.api.*
import io.github.iamr0s.carvex.sessioncore.RawParameter
import org.junit.Assert.*
import org.junit.Test
import java.util.concurrent.atomic.AtomicReference

class NavigationPublisherTest {
    private val sends = setOf(0x5200, 0x5203)
    private val receives = setOf(0x5201, 0x5202)
    private fun start(id: Int) = IapFields(listOf(0 to IapWire.be16(id)))
    private fun snapshot(revision: Long = 1, lifecycle: NavigationLifecycle = NavigationLifecycle.ACTIVE) =
        NavigationSnapshot("synthetic-host", 1, 1, revision, lifecycle,
            NavigationRoute(currentRoad = "synthetic-road", distanceRemainingMeters = 200))

    private data class Queued(val id: Int, val fields: List<Pair<Int, ByteArray>>,
                              val valid: () -> Boolean, val complete: (Throwable?) -> Unit)
    private class Fixture(encode: (NavigationSnapshot, NavigationGuidance.Start, NavigationDisplayCapabilities) -> NavigationPlan) {
        val source = AtomicReference<NavigationSnapshot?>()
        val queued = mutableListOf<Queued>()
        val logs = mutableListOf<String>()
        var rejectId: Int? = null
        val publisher = NavigationPublisher({ id, fields, valid, complete ->
            if (id == rejectId) false else { queued += Queued(id, fields, valid, complete); true }
        }, { logs += it }, encode)
        init { publisher.attachNavigation { source.get() } }
    }

    /** Synthetic encoding exercises delivery plumbing only; no Apple semantic assertion. */
    private fun synthetic(snapshot: NavigationSnapshot, start: NavigationGuidance.Start,
                          display: NavigationDisplayCapabilities): NavigationPlan = NavigationPlan(listOf(
        NavigationPacket(0x5201, start.components.map { 0 to IapWire.be16(it) } +
            listOf(3 to IapWire.cstring(requireNotNull(snapshot.route.currentRoad)),
                7 to IapWire.be32(requireNotNull(snapshot.route.distanceRemainingMeters))) +
            if (start.mask and 1 != 0) listOf(19 to IapWire.cstring("synthetic-source")) else emptyList(), "test-fixture")))
    private fun fixture() = Fixture(::synthetic)

    @Test fun waitsForRealRuntimeSubscriptionAndReadsCurrentSupplier() {
        NavigationGuidance.start(start(99)) // Global bootstrap state cannot authorize this publisher.
        val f = fixture(); f.source.set(snapshot())
        assertFalse(f.publisher.navigationChanged())
        assertFalse(f.publisher.command(0x5200, start(42)))
        f.publisher.linkReady(true, sends, receives)
        assertTrue(f.publisher.command(0x5200, start(42)))
        assertEquals(1, f.queued.size)
        assertArrayEquals(IapWire.be16(42), f.queued.single().fields.first().second)
        assertTrue(f.queued.single().valid())
    }

    @Test fun stopRevokesQueuedWorkAndStartReencodesCurrentSnapshot() {
        val f = fixture(); f.source.set(snapshot())
        f.publisher.linkReady(true, sends, receives)
        f.publisher.command(0x5200, start(42))
        val old = f.queued.single()
        assertTrue(f.publisher.command(0x5203, IapFields(emptyList())))
        assertFalse(old.valid())
        f.source.set(snapshot(2).copy(route = NavigationRoute("new-road", distanceRemainingMeters = 0)))
        assertFalse(f.publisher.navigationChanged())
        f.publisher.command(0x5200, start(43))
        val fresh = f.queued.last()
        assertArrayEquals(IapWire.be16(43), fresh.fields.first().second)
        assertArrayEquals(IapWire.be32(0), fresh.fields.first { it.first == 7 }.second)
        assertTrue(fresh.valid())
    }

    @Test fun badCommandsPreserveSubscriptionAndExistingQueueTokens() {
        val f = fixture(); f.source.set(snapshot())
        f.publisher.linkReady(true, sends, receives); f.publisher.command(0x5200, start(42))
        val old = f.queued.single()
        assertFalse(f.publisher.command(0x5200, IapFields(listOf(1 to byteArrayOf(1)))))
        assertFalse(f.publisher.command(0x5200, IapFields(listOf(1 to byteArrayOf(), 1 to byteArrayOf()))))
        assertFalse(f.publisher.command(0x5203, IapFields(listOf(0 to byteArrayOf(1)))))
        assertTrue(old.valid())
        assertTrue(f.publisher.navigationChanged())
        assertArrayEquals(IapWire.be16(42), f.queued.last().fields.first().second)
    }

    @Test fun requiredCapabilitiesAndEmptyComponentProfileAreGated() {
        val f = fixture(); f.source.set(snapshot())
        for (missing in listOf(0x5200, 0x5203, 0x5201, 0x5202)) {
            f.publisher.linkReady(true, sends - missing, receives - missing)
            assertFalse(f.publisher.command(0x5200, start(42)))
        }
        f.publisher.linkReady(true, sends, receives)
        assertTrue(f.publisher.command(0x5200, IapFields(emptyList())))
        assertTrue(f.queued.isEmpty())
        assertTrue(f.logs.any { it.contains("empty-components-profile-unverified") })
    }

    @Test fun resubscriptionRevokesOldOptionsAndReencodesNewComponents() {
        val f = fixture(); f.source.set(snapshot())
        f.publisher.linkReady(true, sends, receives); f.publisher.command(0x5200, start(42))
        val old = f.queued.single()
        f.publisher.command(0x5200, IapFields(start(43).ordered + listOf(1 to byteArrayOf())))
        assertFalse(old.valid())
        assertArrayEquals(IapWire.be16(43), f.queued.last().fields.first().second)
        assertTrue(f.queued.last().fields.any { it.first == 19 })
    }

    @Test fun reconnectAndDetachRevokeOldWorkAndCannotInheritSubscription() {
        val f = fixture(); f.source.set(snapshot())
        f.publisher.linkReady(true, sends, receives); f.publisher.command(0x5200, start(42))
        val old = f.queued.single()
        f.publisher.linkReady(false); assertFalse(old.valid())
        f.publisher.linkReady(true, sends, receives)
        assertFalse(f.publisher.navigationChanged())
        f.publisher.command(0x5200, start(43))
        val next = f.queued.last()
        f.publisher.detachNavigation(); assertFalse(next.valid())
        val other = fixture(); other.publisher.linkReady(true, sends, receives)
        assertTrue(other.publisher.command(0x5200, start(43)))
        assertTrue(other.queued.isEmpty())
    }

    @Test fun snapshotReplacementRevokesWorkBeforeNotification() {
        val f = fixture(); f.source.set(snapshot())
        f.publisher.linkReady(true, sends, receives); f.publisher.command(0x5200, start(42))
        val old = f.queued.single()
        f.source.set(snapshot(2, NavigationLifecycle.ENDED))
        assertFalse(old.valid())
        f.source.set(null)
        assertFalse(old.valid())
    }

    @Test fun productionEncoderRequiresSourceEvidenceEvenForTerminals() {
        val f = Fixture(NavigationWireEncoding::plan)
        f.publisher.linkReady(true, sends, receives + 0x5204)
        for (state in listOf(snapshot(), snapshot(2, NavigationLifecycle.ENDED),
            snapshot(3, NavigationLifecycle.INVALIDATED), snapshot(4).copy(unverifiedFields = setOf("turn")))) {
            f.source.set(state)
            assertTrue(f.publisher.command(0x5200, start(42)))
            assertFalse(f.publisher.navigationChanged())
        }
        assertTrue(f.queued.isEmpty())
        assertTrue(f.logs.any { it.contains("host-lifecycle-unverified") })
    }

    @Test fun laneCapabilityIsIndependentAndUndeclaredBatchIsNotPartlyQueued() {
        val f = Fixture { _, selection, _ -> NavigationPlan(listOf(NavigationPacket(0x5204,
            selection.components.map { 0 to IapWire.be16(it) } + listOf(1 to IapWire.be16(0)), "test-fixture"))) }
        f.source.set(snapshot()); f.publisher.linkReady(true, sends, receives)
        assertTrue(f.publisher.command(0x5200, start(42)))
        assertTrue(f.queued.isEmpty())
        f.publisher.linkReady(true, sends, receives + 0x5204)
        f.publisher.command(0x5200, start(42))
        assertEquals(listOf(0x5204), f.queued.map { it.id })
    }

    @Test fun batchUsesOneSnapshotAndQueueFailureRevokesUnsentPartsWithoutRetry() {
        val seen = mutableListOf<NavigationSnapshot>()
        val f = Fixture { state, selection, display ->
            seen += state
            NavigationPlan(synthetic(state, selection, display).packets + NavigationPacket(0x5202,
                selection.components.map { 0 to IapWire.be16(it) } + listOf(1 to IapWire.be16(0)), "test-fixture"))
        }
        val state = snapshot(); f.source.set(state); f.rejectId = 0x5202
        f.publisher.linkReady(true, sends, receives); f.publisher.command(0x5200, start(42))
        assertSame(state, seen.single())
        assertEquals(1, f.queued.size)
        assertFalse(f.queued.single().valid())
        assertTrue(f.logs.any { it.contains("queue-rejected") && it.contains("submitted=1/2") })
        f.rejectId = null
        assertTrue(f.publisher.navigationChanged()) // A real update, not an automatic retry.
        assertEquals(3, f.queued.size)
        f.queued[1].complete(java.io.IOException("synthetic transport failure"))
        assertFalse(f.queued[2].valid())
        assertEquals(3, f.queued.size)
    }

    @Test fun malformedBatchIsValidatedBeforeAnySubmission() {
        val f = Fixture { _, selection, _ -> NavigationPlan(listOf(
            NavigationPacket(0x5201, selection.components.map { 0 to IapWire.be16(it) } + listOf(7 to IapWire.be32(1)), "test"),
            NavigationPacket(0x5202, selection.components.map { 0 to IapWire.be16(it) } + listOf(1 to byteArrayOf(1)), "test"))) }
        f.source.set(snapshot()); f.publisher.linkReady(true, sends, receives)
        assertThrows(IllegalArgumentException::class.java) { f.publisher.command(0x5200, start(42)) }
        assertTrue(f.queued.isEmpty())
    }

    @Test fun acceptedDisplayFieldsAreCopiedAndClearedWithLink() {
        val seen = mutableListOf<List<RawParameter>>()
        val f = Fixture { _, _, display -> seen += display.parameters(); NavigationPlan(blocked = "test") }
        f.source.set(snapshot()); f.publisher.linkReady(true, sends, receives)
        val raw = byteArrayOf(1, 2)
        f.publisher.identification(listOf(RawParameter(26, raw))); raw.fill(9)
        f.publisher.command(0x5200, start(42))
        assertArrayEquals(byteArrayOf(1, 2), seen.single().single().value)
        seen.single().single().value.fill(8)
        f.publisher.navigationChanged()
        assertArrayEquals(byteArrayOf(1, 2), seen.last().single().value)
        f.publisher.linkReady(false); f.publisher.linkReady(true, sends, receives)
        f.publisher.command(0x5200, start(42))
        assertTrue(seen.last().isEmpty())
    }
}

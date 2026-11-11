package io.github.iamr0s.carvex.carplay.core

import io.github.iamr0s.carvex.protocol.api.*
import io.github.iamr0s.carvex.sessioncore.RawParameter
import org.junit.Assert.*
import org.junit.Test
import java.util.concurrent.atomic.AtomicReference

class NavigationWireEncodingTest {
    private val start = NavigationGuidance.Start(listOf(42), 3)
    private fun component(id: Int = 42, capacity: Int = 8) = RawParameter(30,
        IapWire.fields(listOf(0 to IapWire.be16(id), 1 to IapWire.cstring("RouteGuidance"),
            2 to IapWire.be16(64), 4 to IapWire.be16(64), 6 to IapWire.be16(capacity))))
    private val display = NavigationDisplayCapabilities(listOf(component()))
    private fun snapshot(turn: NavigationTurn? = NavigationTurn.RIGHT, distance: Long? = 200) =
        NavigationSnapshot("xiaomi", 1, 1, 2, NavigationLifecycle.ACTIVE,
            maneuver = NavigationManeuver("hint", distanceMeters = distance, turn = turn),
            evidence = mapOf("lifecycle" to "H01:classes2:16fc3c", "maneuver" to "H01:HUD-maneuver"),
            unverifiedFields = setOf("road_name-role"), maneuverGeneration = 1)
    private fun fields(packet: NavigationPacket) = IapWire.parseFieldList(IapWire.fields(packet.fields))
    private fun state(packet: NavigationPacket) = fields(packet)[1]!!.single().toInt()

    @Test fun definitionPrecedesReferenceAndDistanceGoesToManeuverParameter() {
        val plan = NavigationWireEncoding.plan(snapshot(), start, display)
        assertNull(plan.blocked)
        assertEquals(listOf(0x5202, 0x5201), plan.packets.map { it.id })
        val definition = fields(plan.packets[0]); val route = fields(plan.packets[1])
        assertArrayEquals(definition[1], route[13])
        assertArrayEquals(byteArrayOf(2), definition[3]) // Apple RightTurn, vendor right is 3.
        assertArrayEquals(byteArrayOf(1), route[1])
        assertArrayEquals(IapWire.be32(200), route[10])
        assertNull(route[7]); assertNull(route[14]) // No fabricated whole-route distance/count.
        assertNull(route[3]); assertNull(definition[4]) // Unclassified road hint is not a road field.
        assertNull(definition[8]) // The host has no driving-side source.
    }

    @Test fun explicitAppleTypesAreUsedInsteadOfLocalEnumOrdinals() {
        for ((turn, value) in mapOf(NavigationTurn.STRAIGHT to 3, NavigationTurn.LEFT to 1,
            NavigationTurn.RIGHT to 2, NavigationTurn.U_TURN to 4, NavigationTurn.SHARP_LEFT to 47,
            NavigationTurn.SHARP_RIGHT to 48, NavigationTurn.SLIGHT_LEFT to 49, NavigationTurn.SLIGHT_RIGHT to 50)) {
            val packet = NavigationWireEncoding.plan(snapshot(turn), start, display).packets.first()
            assertArrayEquals(byteArrayOf(value.toByte()), fields(packet)[3])
        }
    }

    @Test fun unknownTurnAndUnknownDistanceClearOldReceiverValues() {
        val unknown = NavigationWireEncoding.plan(snapshot(null), start, display)
        assertEquals(listOf(0x5201, 0x5201), unknown.packets.map { it.id })
        assertEquals(listOf(0, 1), unknown.packets.map(::state))
        assertTrue(unknown.packets.all { fields(it)[13] == null && fields(it)[10] == null })
        for (distance in listOf(null, 0L, -1L, 0x100000000L)) {
            val plan = NavigationWireEncoding.plan(snapshot(distance = distance), start, display)
            assertEquals(listOf(0x5201, 0x5202, 0x5201), plan.packets.map { it.id })
            assertEquals(0, state(plan.packets.first()))
            assertNull(fields(plan.packets.last())[10])
        }
    }

    @Test fun terminalIsNotActiveRetainsSubscriptionAndDoesNotClaimArrival() {
        for (lifecycle in listOf(NavigationLifecycle.ENDED, NavigationLifecycle.INVALIDATED)) {
            val plan = NavigationWireEncoding.plan(snapshot().copy(lifecycle = lifecycle,
                maneuver = null, endReason = NavigationEndReason.UNKNOWN), start, display)
            assertEquals(listOf(0x5201), plan.packets.map { it.id })
            assertEquals(0, state(plan.packets.single()))
            assertNull(fields(plan.packets.single())[13])
        }
    }

    @Test fun componentCapacityIsExplicitAndMalformedOrDuplicateDeclarationsFailClosed() {
        val absent = NavigationDisplayCapabilities(emptyList())
        assertNotNull(NavigationWireEncoding.plan(snapshot(), start, absent).blocked)
        for (parameters in listOf(listOf(component(capacity = 0)), listOf(component(id = 43)),
            listOf(component(), component()), listOf(RawParameter(30, byteArrayOf(0, 9, 0, 0))),
            listOf(RawParameter(30, IapWire.fields(listOf(0 to IapWire.be16(42),
                6 to IapWire.be16(8), 6 to IapWire.be16(8))))))) {
            assertFalse(NavigationDisplayCapabilities(parameters).supportsManeuver(42))
        }
        val multi = NavigationGuidance.Start(listOf(42, 43), 0)
        assertNotNull(NavigationWireEncoding.plan(snapshot(), multi, display).blocked)
        val both = NavigationDisplayCapabilities(listOf(component(), component(43, 1)))
        assertNull(NavigationWireEncoding.plan(snapshot(), multi, both).blocked)
        assertNull(NavigationWireEncoding.plan(snapshot().copy(lifecycle = NavigationLifecycle.ENDED), start, absent).blocked)
    }

    @Test fun resubscriptionAndEndReencodeCurrentStateAndRevokeOldPackets() {
        val source = AtomicReference<NavigationSnapshot?>(snapshot())
        val queued = mutableListOf<Pair<NavigationPacket, () -> Boolean>>()
        val publisher = NavigationPublisher({ id, fields, valid, _ ->
            queued += NavigationPacket(id, fields, "test-capture") to valid; true
        })
        publisher.attachNavigation { source.get() }
        assertFalse(publisher.navigationChanged())
        publisher.identification(listOf(component(), component(43, 1)))
        publisher.linkReady(true, setOf(0x5200, 0x5203), setOf(0x5201, 0x5202))
        publisher.command(0x5200, IapFields(listOf(0 to IapWire.be16(42))))
        assertEquals(listOf(0x5202, 0x5201), queued.map { it.first.id })
        val old = queued.toList()
        publisher.command(0x5200, IapFields(listOf(0 to IapWire.be16(43))))
        assertTrue(old.none { it.second() })
        assertArrayEquals(IapWire.be16(43), fields(queued.last().first)[0])
        source.set(snapshot().copy(revision = 3, lifecycle = NavigationLifecycle.ENDED, maneuver = null))
        publisher.navigationChanged()
        assertEquals(0, state(queued.last().first))
        assertTrue(queued.last().second())
        val size = queued.size
        publisher.command(0x5203, IapFields(emptyList()))
        assertFalse(publisher.navigationChanged()); assertEquals(size, queued.size)
        publisher.command(0x5200, IapFields(listOf(0 to IapWire.be16(43))))
        assertEquals(0, state(queued.last().first)) // Ended route cannot revive on START.
    }

    @Test fun maneuverReplacementAndDistanceOnlyUpdatesKeepReferencesConsistent() {
        val first = NavigationWireEncoding.plan(snapshot(), start, display)
        val distance = NavigationWireEncoding.plan(snapshot(distance = 100).copy(revision = 3), start, display)
        assertArrayEquals(fields(first.packets.last())[13], fields(distance.packets.last())[13])
        val changed = NavigationWireEncoding.plan(snapshot(NavigationTurn.LEFT).copy(maneuverGeneration = 2), start, display)
        assertArrayEquals(IapWire.be16(2), fields(changed.packets.first())[1])
        assertArrayEquals(IapWire.be16(2), fields(changed.packets.last())[13])
    }
}

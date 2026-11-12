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
            maneuverGeneration = 1)
    private fun fields(packet: NavigationPacket) = IapWire.parseFieldList(IapWire.fields(packet.fields))
    private fun state(packet: NavigationPacket) = fields(packet)[1]!!.single().toInt()
    private fun withRoute(distance: Long?, evidence: String? = "fixture:verified-route") = snapshot().let {
        it.copy(route = NavigationRoute(distanceRemainingMeters = distance),
            evidence = it.evidence + listOfNotNull(evidence?.let { value -> "distanceRemainingMeters" to value }).toMap())
    }

    @Test fun verifiedRouteDistanceUsesItsOwnUnsignedParameterIncludingExplicitZero() {
        for (distance in listOf(19000L, 0L, 1L, 0xffffffffL)) {
            val plan = NavigationWireEncoding.plan(withRoute(distance), start, display)
            assertNull(plan.blocked)
            assertEquals(listOf(0x5202, 0x5201), plan.packets.map { it.id })
            val route = fields(plan.packets.last())
            assertArrayEquals(IapWire.be32(distance), route[7])
            assertArrayEquals(IapWire.be32(200), route[10])
            assertArrayEquals(fields(plan.packets.first())[1], route[13])
        }
    }

    @Test fun missingInvalidOrUnverifiedRouteDistanceClearsInsteadOfPublishingAFallback() {
        val unknown = listOf(withRoute(null), withRoute(-1), withRoute(0x100000000L),
            withRoute(Long.MAX_VALUE), withRoute(19000, null), withRoute(19000, " "))
        for (snapshot in unknown) {
            val plan = NavigationWireEncoding.plan(snapshot, start, display)
            assertNull(plan.blocked)
            assertEquals(listOf(0x5201, 0x5202, 0x5201), plan.packets.map { it.id })
            assertEquals(0, state(plan.packets.first()))
            assertTrue(plan.packets.all { fields(it)[7] == null })
            assertArrayEquals(IapWire.be32(200), fields(plan.packets.last())[10])
        }
        assertNotNull(NavigationWireEncoding.plan(withRoute(19000).copy(evidence =
            mapOf("distanceRemainingMeters" to "fixture:route")), start, display).blocked)
    }

    @Test fun routeDistanceSurvivesUnknownManeuverAndReroutingButIsOmittedOnTermination() {
        val known = withRoute(19000)
        for (lifecycle in listOf(NavigationLifecycle.ACTIVE, NavigationLifecycle.REROUTING)) {
            val plan = NavigationWireEncoding.plan(known.copy(lifecycle = lifecycle,
                maneuver = null), start, display)
            assertEquals(listOf(0x5201, 0x5201), plan.packets.map { it.id })
            assertEquals(0, state(plan.packets.first()))
            assertNull(fields(plan.packets.first())[7])
            assertEquals(if (lifecycle == NavigationLifecycle.ACTIVE) 1 else 5, state(plan.packets.last()))
            assertArrayEquals(IapWire.be32(19000), fields(plan.packets.last())[7])
            assertNull(fields(plan.packets.last())[10])
            assertNull(fields(plan.packets.last())[13])
        }
        for (lifecycle in listOf(NavigationLifecycle.ENDED, NavigationLifecycle.INVALIDATED)) {
            val packet = NavigationWireEncoding.plan(known.copy(lifecycle = lifecycle), start, display).packets.single()
            assertEquals(0, state(packet))
            assertNull(fields(packet)[7])
        }
    }

    @Test fun routeDistanceKeepsCapabilitySubscriptionAndStaleSnapshotGuards() {
        val source = AtomicReference<NavigationSnapshot?>(withRoute(19000))
        val queued = mutableListOf<Pair<NavigationPacket, () -> Boolean>>()
        val publisher = NavigationPublisher({ id, fields, valid, _ ->
            queued += NavigationPacket(id, fields, "test-capture") to valid; true
        })
        publisher.attachNavigation { source.get() }
        publisher.identification(listOf(component(), component(43)))
        publisher.linkReady(true, setOf(0x5200, 0x5203), setOf(0x5201, 0x5202))
        assertFalse(publisher.navigationChanged())
        assertTrue(queued.isEmpty())
        publisher.command(0x5200, IapFields(listOf(0 to IapWire.be16(42))))
        assertArrayEquals(IapWire.be32(19000), fields(queued.last().first)[7])
        val old = queued.toList()
        publisher.command(0x5200, IapFields(listOf(0 to IapWire.be16(43))))
        assertTrue(old.none { it.second() })
        assertArrayEquals(IapWire.be16(43), fields(queued.last().first)[0])
        assertArrayEquals(IapWire.be32(19000), fields(queued.last().first)[7])
        val known = queued.toList()
        source.set(snapshot().copy(routeEpoch = 2, revision = 3))
        val begin = queued.size
        assertTrue(publisher.navigationChanged())
        assertTrue(known.none { it.second() })
        val cleared = queued.drop(begin)
        assertEquals(listOf(0x5201, 0x5202, 0x5201), cleared.map { it.first.id })
        assertEquals(0, state(cleared.first().first))
        assertTrue(cleared.all { fields(it.first)[7] == null })
        publisher.command(0x5203, IapFields(emptyList()))
        assertTrue(cleared.none { it.second() })
        assertFalse(publisher.navigationChanged())
        publisher.command(0x5200, IapFields(listOf(0 to IapWire.be16(43))))
        assertNull(fields(queued.last().first)[7])
        publisher.linkReady(false)
        assertTrue(queued.none { it.second() })
    }

    @Test fun definitionPrecedesReferenceAndDistanceGoesToManeuverParameter() {
        val plan = NavigationWireEncoding.plan(snapshot(), start, display)
        assertNull(plan.blocked)
        assertEquals(listOf(0x5201, 0x5202, 0x5201), plan.packets.map { it.id })
        assertEquals(0, state(plan.packets.first())) // Clear a previous whole-route value.
        val definition = fields(plan.packets[1]); val route = fields(plan.packets[2])
        assertArrayEquals(definition[1], route[13])
        assertArrayEquals(byteArrayOf(2), definition[3]) // Apple RightTurn, vendor right is 3.
        assertArrayEquals(byteArrayOf(1), route[1])
        assertArrayEquals(IapWire.be32(200), route[10])
        assertNull(route[7]); assertNull(route[14]) // No fabricated whole-route distance/count.
        assertNull(route[3]) // No current-road source.
        assertArrayEquals(byteArrayOf(0), definition[4]) // Explicitly clear a missing after-road.
        assertNull(definition[8]) // The host has no driving-side source.
    }

    @Test fun explicitAppleTypesAreUsedInsteadOfLocalEnumOrdinals() {
        for ((turn, value) in mapOf(NavigationTurn.STRAIGHT to 3, NavigationTurn.LEFT to 1,
            NavigationTurn.RIGHT to 2, NavigationTurn.U_TURN to 4, NavigationTurn.SHARP_LEFT to 47,
            NavigationTurn.SHARP_RIGHT to 48, NavigationTurn.SLIGHT_LEFT to 49, NavigationTurn.SLIGHT_RIGHT to 50)) {
            val packet = NavigationWireEncoding.plan(snapshot(turn), start, display).packets.single { it.id == 0x5202 }
            assertArrayEquals(byteArrayOf(value.toByte()), fields(packet)[3])
        }
    }

    @Test fun afterRoadIsSentAsUtf8WithTheManeuverDefinitionBeforeItsReference() {
        val road = "测试转向后道路🚘"
        val initial = snapshot()
        val plan = NavigationWireEncoding.plan(initial.copy(
            maneuver = initial.maneuver!!.copy(afterRoad = road)), start, display)
        assertNull(plan.blocked)
        val definition = plan.packets.single { it.id == 0x5202 }
        val text = requireNotNull(fields(definition)[4])
        assertEquals(0, text.last().toInt())
        assertEquals(road, String(text, 0, text.size - 1, Charsets.UTF_8))
        assertNull(fields(definition)[2]) // A road name is not an instruction.
        assertTrue(plan.packets.filter { it.id == 0x5201 }.all { fields(it)[3] == null })
        assertArrayEquals(fields(definition)[1], fields(plan.packets.last())[13])
        assertArrayEquals(IapWire.be32(200), fields(plan.packets.last())[10])
    }

    @Test fun reusedDefinitionUpdatesOrClearsItsAfterRoadAndRejectsMalformedText() {
        val initial = snapshot()
        val cached = mutableMapOf<Int, ByteArray>()
        for (road in listOf("测试道路甲", "测试道路乙", null, "", "broken\u0000road", "\uD800", "x".repeat(4097))) {
            val plan = NavigationWireEncoding.plan(initial.copy(
                maneuver = initial.maneuver!!.copy(afterRoad = road)), start, display)
            val definition = fields(plan.packets.single { it.id == 0x5202 })
            cached.putAll(definition.ordered.toMap()) // The receiver merges existing slots.
            assertArrayEquals(IapWire.be16(1), cached[1])
            val expected = if (road in listOf("测试道路甲", "测试道路乙")) road!! else ""
            assertArrayEquals(IapWire.cstring(expected), cached[4])
            assertArrayEquals(IapWire.be32(200), fields(plan.packets.last())[10])
        }
    }

    @Test fun unknownTurnAndEndedRouteKeepTheirResetBehaviorWithAnAfterRoad() {
        val initial = snapshot()
        val unknown = initial.copy(maneuver = initial.maneuver!!.copy(afterRoad = "测试道路", turn = null))
        val plan = NavigationWireEncoding.plan(unknown, start, display)
        assertEquals(listOf(0x5201, 0x5201), plan.packets.map { it.id })
        assertEquals(listOf(0, 1), plan.packets.map(::state))
        assertTrue(plan.packets.all { fields(it)[13] == null })
        val ended = NavigationWireEncoding.plan(initial.copy(lifecycle = NavigationLifecycle.ENDED,
            maneuver = requireNotNull(initial.maneuver).copy(afterRoad = "测试道路")), start, display)
        assertEquals(listOf(0x5201), ended.packets.map { it.id })
        assertEquals(0, state(ended.packets.single()))
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
        assertEquals(listOf(0x5201, 0x5202, 0x5201), queued.map { it.first.id })
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
        assertArrayEquals(IapWire.be16(2), fields(changed.packets.single { it.id == 0x5202 })[1])
        assertArrayEquals(IapWire.be16(2), fields(changed.packets.last())[13])
    }

    @Test fun maneuverSlotsRespectMinimumSelectedStorageCapacity() {
        val selected = NavigationGuidance.Start(listOf(42, 43), 3)
        val capabilities = NavigationDisplayCapabilities(listOf(component(42, 8), component(43, 3)))
        assertEquals(8, capabilities.maneuverCapacity(42))
        assertEquals(3, capabilities.maneuverCapacity(43))
        val indices = (1L..100L).map { generation ->
            val plan = NavigationWireEncoding.plan(withRoute(19000).copy(maneuverGeneration = generation), selected, capabilities)
            assertEquals(listOf(0x5202, 0x5201), plan.packets.map { it.id })
            val index = fields(plan.packets.single { it.id == 0x5202 })[1]!!
            assertArrayEquals(index, fields(plan.packets.last())[13])
            IapWire.u16(index, 0)
        }.toSet()
        assertEquals(setOf(0, 1, 2), indices)
        val large = NavigationWireEncoding.plan(withRoute(19000).copy(maneuverGeneration = Long.MAX_VALUE), start,
            NavigationDisplayCapabilities(listOf(component(capacity = 65535))))
        assertTrue(IapWire.u16(fields(large.packets.single { it.id == 0x5202 })[1]!!, 0) in 0 until 65535)
    }

    @Test fun aSingleStorageSlotIsClearedBeforeItsDefinitionCanChangeTheArrow() {
        val plan = NavigationWireEncoding.plan(withRoute(19000), start,
            NavigationDisplayCapabilities(listOf(component(capacity = 1))))
        assertEquals(listOf(0x5201, 0x5202, 0x5201), plan.packets.map { it.id })
        assertEquals(0, state(plan.packets.first()))
        assertArrayEquals(IapWire.be16(0), fields(plan.packets[1])[1])
        assertArrayEquals(IapWire.be16(0), fields(plan.packets.last())[13])
        assertArrayEquals(IapWire.be32(200), fields(plan.packets.last())[10])
        assertArrayEquals(IapWire.be32(19000), fields(plan.packets.last())[7])
        assertNotNull(NavigationWireEncoding.plan(snapshot(), NavigationGuidance.Start(emptyList(), 3), display).blocked)
    }
}

package io.github.iamr0s.carvex.session

import io.github.iamr0s.carvex.protocol.api.*
import io.github.iamr0s.carvex.sessioncore.*
import org.junit.Assert.*
import org.junit.Test

class HostNavigationRelayTest {
    private val source = HostNavigationSource("test-host", 1)
    private fun event(change: HostNavigationChange, delta: HostNavigationDelta = HostNavigationDelta(),
                      route: String? = null, sequence: Long? = null, binding: Long = 1) =
        HostNavigationEvent(source.copy(bindingEpoch = binding), change, "test-source-evidence", delta, route, sequence)
    private fun <T> value(value: T) = HostNavigationField.Value(value, "test-field-evidence")

    @Test fun diagnosticsSeparateRepeatedGuidanceDistanceChangesAndTerminalBoundaries() {
        val logs = mutableListOf<String>()
        HostNavigationRelay(logs::add).use { relay ->
            relay.update(event(HostNavigationChange.STARTED))
            fun hint(distance: Long) = event(HostNavigationChange.UPDATED, HostNavigationDelta(
                maneuver = value(HostNavigationManeuver("private road identity", "private instruction",
                    distanceMeters = distance, turn = HostNavigationTurn.LEFT))))
            relay.update(hint(245))
            assertTrue(logs.last().contains("guidanceChanged=true"))
            assertTrue(logs.last().contains("turn=LEFT maneuverDistance=245 routeDistance=absent"))
            val generation = requireNotNull(relay.snapshot()).maneuverGeneration
            relay.update(hint(245))
            assertTrue(logs.last().contains("guidanceChanged=false"))
            relay.update(hint(200))
            assertTrue(logs.last().contains("guidanceChanged=true"))
            assertTrue(logs.last().contains("maneuverDistance=200"))
            assertEquals(generation, relay.snapshot()?.maneuverGeneration)
            relay.update(event(HostNavigationChange.ENDED))
            assertTrue(logs.last().contains("lifecycle=ENDED guidanceChanged=true"))
            assertTrue(logs.last().contains("turn=absent maneuverDistance=absent"))
            val ended = relay.snapshot()
            assertFalse(relay.update(hint(245)))
            assertTrue(logs.last().contains("reason=no-active-route"))
            assertSame(ended, relay.snapshot())
            assertFalse(logs.any { it.contains("private road") || it.contains("private instruction") })
        }
    }

    @Test fun absentRetainsValuesExplicitClearRemovesAndZeroIsValid() {
        HostNavigationRelay().use { relay ->
            assertTrue(relay.update(event(HostNavigationChange.STARTED,
                HostNavigationDelta(currentRoad = value("road"), distanceRemainingMeters = value(20L)))))
            assertTrue(relay.update(event(HostNavigationChange.UPDATED,
                HostNavigationDelta(distanceRemainingMeters = value(0L)))))
            assertEquals("road", relay.snapshot()?.route?.currentRoad)
            assertEquals(0L, relay.snapshot()?.route?.distanceRemainingMeters)
            assertEquals(NavigationLifecycle.ACTIVE, relay.snapshot()?.lifecycle)
            relay.update(event(HostNavigationChange.UPDATED, HostNavigationDelta(currentRoad = HostNavigationField.Clear)))
            assertNull(relay.snapshot()?.route?.currentRoad)
            assertFalse(requireNotNull(relay.snapshot()).evidence.containsKey("currentRoad"))
        }
        assertThrows(IllegalArgumentException::class.java) {
            HostNavigationDelta(distanceRemainingMeters = value(-1L))
        }
    }

    @Test fun maneuverReplacementClearsLanesAndInputsAreCopied() {
        val directions = mutableListOf(HostNavigationTurn.LEFT)
        val lanes = mutableListOf(HostNavigationLane(directions, true))
        val uncertainty = mutableSetOf("test-unknown")
        HostNavigationRelay().use { relay ->
            relay.update(event(HostNavigationChange.STARTED, HostNavigationDelta(
                maneuver = value(HostNavigationManeuver("m1")), lanes = value(HostNavigationLanes("m1", lanes))))
                .copy(unverifiedFields = uncertainty))
            directions.clear(); lanes.clear(); uncertainty.clear()
            assertEquals(listOf(NavigationTurn.LEFT), relay.snapshot()?.lanes?.lanes?.single()?.directions)
            assertEquals(setOf("test-unknown"), relay.snapshot()?.unverifiedFields)
            relay.update(event(HostNavigationChange.UPDATED, HostNavigationDelta(maneuver = value(HostNavigationManeuver("m2")))))
            assertNull(relay.snapshot()?.lanes)
            assertEquals(setOf("test-unknown"), relay.snapshot()?.unverifiedFields)
        }
    }

    @Test fun doubleEndIsIdempotentAndLateHudCannotReactivate() {
        HostNavigationRelay().use { relay ->
            assertFalse(relay.update(event(HostNavigationChange.UPDATED)))
            relay.update(event(HostNavigationChange.STARTED, HostNavigationDelta(currentRoad = value("road"))))
            relay.update(event(HostNavigationChange.ENDED))
            val ended = relay.snapshot()
            assertNull(ended?.route?.currentRoad)
            assertEquals(NavigationEndReason.UNKNOWN, ended?.endReason)
            assertFalse(relay.update(event(HostNavigationChange.ENDED)))
            assertFalse(relay.update(event(HostNavigationChange.UPDATED)))
            assertFalse(relay.update(event(HostNavigationChange.REROUTING)))
            assertSame(ended, relay.snapshot())
            relay.update(event(HostNavigationChange.STARTED))
            assertEquals(requireNotNull(ended).routeEpoch + 1, relay.snapshot()?.routeEpoch)
        }
    }

    @Test fun maneuverGenerationIsStableForDistancesAndChangesAcrossHintsAndRoutes() {
        HostNavigationRelay().use { relay ->
            relay.update(event(HostNavigationChange.STARTED))
            fun hint(id: String, distance: Long?, turn: HostNavigationTurn?) = event(HostNavigationChange.UPDATED,
                HostNavigationDelta(maneuver = value(HostNavigationManeuver(id, distanceMeters = distance, turn = turn))))
            relay.update(hint("right-road", 200, HostNavigationTurn.RIGHT))
            val first = requireNotNull(relay.snapshot())
            assertTrue(first.maneuverGeneration > 0)
            assertEquals(NavigationTurn.RIGHT, first.maneuver?.turn)
            relay.update(hint("right-road", 100, HostNavigationTurn.RIGHT))
            assertEquals(first.maneuverGeneration, relay.snapshot()?.maneuverGeneration)
            relay.update(hint("unknown", null, null))
            assertNull(relay.snapshot()?.maneuver?.turn)
            assertNull(relay.snapshot()?.maneuver?.distanceMeters)
            assertTrue(requireNotNull(relay.snapshot()).maneuverGeneration > first.maneuverGeneration)
            relay.update(event(HostNavigationChange.ENDED))
            relay.update(event(HostNavigationChange.STARTED))
            relay.update(hint("right-road", 300, HostNavigationTurn.RIGHT))
            assertTrue(requireNotNull(relay.snapshot()).maneuverGeneration > first.maneuverGeneration)
        }
    }

    @Test fun newRouteResetsRouteLocalSequenceAndRejectsRetiredRoute() {
        HostNavigationRelay().use { relay ->
            relay.update(event(HostNavigationChange.STARTED, HostNavigationDelta(destination = value("old")), "r1", 100))
            assertTrue(relay.update(event(HostNavigationChange.STARTED, route = "r2", sequence = 1)))
            assertNull(relay.snapshot()?.route?.destination)
            assertFalse(relay.update(event(HostNavigationChange.UPDATED, route = "r1", sequence = 101)))
            assertFalse(relay.update(event(HostNavigationChange.STARTED, route = "r1", sequence = 102)))
            assertFalse(relay.update(event(HostNavigationChange.UPDATED, route = "r2", sequence = 1)))
            assertTrue(relay.update(event(HostNavigationChange.UPDATED, route = "r2", sequence = 2)))
        }
    }

    @Test fun invalidatedBindingRequiresNewBindingAndRejectsLocalLateWork() {
        HostNavigationRelay().use { relay ->
            relay.update(event(HostNavigationChange.STARTED))
            relay.update(event(HostNavigationChange.SOURCE_INVALIDATED))
            assertFalse(relay.update(event(HostNavigationChange.STARTED)))
            assertTrue(relay.update(event(HostNavigationChange.STARTED, binding = 2)))
            assertFalse(relay.update(event(HostNavigationChange.UPDATED, binding = 1)))
            assertFalse(relay.update(event(HostNavigationChange.ENDED, binding = 1)))
            assertEquals(2L, relay.snapshot()?.bindingEpoch)
            assertEquals(NavigationLifecycle.ACTIVE, relay.snapshot()?.lifecycle)
        }
    }

    private class Sink : NavigationSink {
        var source: (() -> NavigationSnapshot?)? = null
        var changes = 0
        override fun attachNavigation(source: () -> NavigationSnapshot?) { this.source = source }
        override fun navigationChanged(): Boolean { changes++; return true }
        override fun detachNavigation() { source = null }
    }

    @Test fun stopAndReattachReadCurrentSnapshotAndCloseRevokesSupplier() {
        val relay = HostNavigationRelay()
        val first = Sink(); relay.attach(first)
        relay.update(event(HostNavigationChange.STARTED))
        val supplier = requireNotNull(first.source)
        assertSame(relay.snapshot(), supplier())
        relay.detach()
        assertNull(first.source)
        relay.update(event(HostNavigationChange.UPDATED, HostNavigationDelta(currentRoad = value("new"))))
        val next = Sink(); relay.attach(next)
        assertEquals("new", next.source?.invoke()?.route?.currentRoad)
        relay.close()
        assertNull(next.source)
        assertNull(supplier())
        assertFalse(relay.update(event(HostNavigationChange.STARTED)))
    }
}

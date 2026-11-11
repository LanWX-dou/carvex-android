package io.github.iamr0s.carvex.host.vendor

import io.github.iamr0s.carvex.sessioncore.*
import org.junit.Assert.*
import org.junit.Test

class CarWithNavigationTest {
    private val source = HostNavigationSource("xiaomi", 1, "4.0.14-20260801")
    private fun decode(action: String, values: Map<String, Any?>) = CarWithNavigation.decode(action, values, source)

    @Test fun strictBooleanLifecycleAndIntegerHudEnd() {
        assertEquals(HostNavigationChange.STARTED, decode("mix_notify_start_navi", mapOf("isNavi" to true))?.change)
        assertEquals(HostNavigationChange.ENDED, decode("mix_notify_start_navi", mapOf("isNavi" to false))?.change)
        assertEquals(HostNavigationChange.ENDED, decode("carlife_show_hud_info", mapOf("action" to 3))?.change)
        for (wrong in listOf("false", 0, 0L, null))
            assertNull(decode("mix_notify_start_navi", mapOf("isNavi" to wrong)))
        for (wrong in listOf("3", 3L, 3.0, false, null, 0, 99))
            assertNull(decode("carlife_show_hud_info", mapOf("action" to wrong)))
    }

    @Test fun firstHudCannotStartAndZeroDoesNotMeanArrivalOrRouteDistance() {
        val event = requireNotNull(decode("carlife_show_hud_info", mapOf("action" to 1,
            "remain_distance" to 0, "total_distance" to 2000, "road_name" to "turn road", "navi_turn" to 7)))
        assertEquals(HostNavigationChange.UPDATED, event.change)
        assertEquals(HostNavigationEndReason.UNKNOWN, event.endReason)
        assertEquals(0L, event.observation?.distanceHintMeters)
        assertEquals(2000L, event.observation?.referenceDistanceMeters)
        assertEquals(HostNavigationField.Absent, event.delta.currentRoad)
        assertEquals(HostNavigationField.Absent, event.delta.distanceRemainingMeters)
        val maneuver = (event.delta.maneuver as HostNavigationField.Value).value
        assertEquals(HostNavigationTurn.LEFT, maneuver.turn)
        assertNull(maneuver.distanceMeters)
        assertEquals(HostNavigationField.Absent, event.delta.lanes)
        assertTrue(event.unverifiedFields.isNotEmpty())
    }

    @Test fun badHudFieldsRemainUnknownAndMutableIconIsNotRetained() {
        val icon = byteArrayOf(1, 2, 3)
        val event = requireNotNull(decode("carlife_show_hud_info", mapOf("action" to 2,
            "remain_distance" to "12", "total_distance" to -1, "road_name" to 12,
            "navi_turn" to "left", "turn_icon_data" to icon)))
        icon.fill(9)
        assertNull(event.observation?.distanceHintMeters)
        assertNull(event.observation?.referenceDistanceMeters)
        assertNull(event.observation?.roadHint)
        assertNull(event.observation?.turnHint)
        assertEquals(3, event.observation?.iconBytes)
    }

    @Test fun evidenceDoesNotAutomaticallyApplyToAnotherVersionOrBrand() {
        for (version in listOf(null, "4.0.14", "4.0.15-20260801"))
            assertNull(CarWithNavigation.decode("mix_notify_start_navi", mapOf("isNavi" to true), source.copy(version = version)))
        assertNull(VendorHostConfig("oppo", "OPPO", "pkg", "service").navigationDecoder)
        assertNull(decode("unrecognized", emptyMap()))
    }

    @Test fun reviewedIconGroupsBecomeTurnsWithoutCopyingVendorEnums() {
        val expected = mapOf(2 to HostNavigationTurn.SLIGHT_RIGHT, 3 to HostNavigationTurn.RIGHT,
            4 to HostNavigationTurn.SLIGHT_LEFT, 5 to HostNavigationTurn.U_TURN,
            7 to HostNavigationTurn.LEFT, 8 to HostNavigationTurn.LEFT)
        for ((raw, turn) in expected) {
            val event = requireNotNull(decode("carlife_show_hud_info", mapOf("action" to 2,
                "remain_distance" to 125, "total_distance" to 500, "navi_turn" to raw)))
            val maneuver = (event.delta.maneuver as HostNavigationField.Value).value
            assertEquals(turn, maneuver.turn)
            assertEquals(125L, maneuver.distanceMeters)
            assertEquals(HostNavigationField.Absent, event.delta.distanceRemainingMeters)
        }
        for (raw in listOf(0, 1, 9, 11, 23, 24, 99)) {
            val event = requireNotNull(decode("carlife_show_hud_info", mapOf("action" to 2, "navi_turn" to raw)))
            assertNull((event.delta.maneuver as HostNavigationField.Value).value.turn)
        }
    }

    @Test fun invalidAndAmbiguousDistancesCannotKeepAnOldValidValue() {
        for (raw in listOf(0, -1, Int.MAX_VALUE, "200", 200L, null)) {
            val event = requireNotNull(decode("carlife_show_hud_info", mapOf("action" to 2,
                "remain_distance" to raw, "navi_turn" to 3)))
            assertNull((event.delta.maneuver as HostNavigationField.Value).value.distanceMeters)
            assertEquals(HostNavigationEndReason.UNKNOWN, event.endReason)
        }
    }
}

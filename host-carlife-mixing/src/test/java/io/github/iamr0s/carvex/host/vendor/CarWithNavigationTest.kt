package io.github.iamr0s.carvex.host.vendor

import io.github.iamr0s.carvex.sessioncore.*
import org.junit.Assert.*
import org.junit.Test

class CarWithNavigationTest {
    private val source = HostNavigationSource("xiaomi", 1, "4.0.14-20260801")
    private fun decode(action: String, values: Map<String, Any?>) = CarWithNavigation.decode(action, values, source)

    @Test fun upgradedHostAcceptsStartChangingManeuversAndBothEndNotifications() {
        val upgraded = source.copy(version = "4.0.23-20261016")
        fun current(action: String, values: Map<String, Any?>) =
            requireNotNull(CarWithNavigation.decode(action, values, upgraded))
        val start = current("mix_notify_start_navi", mapOf("isNavi" to true))
        assertEquals(HostNavigationChange.STARTED, start.change)
        assertEquals("H02:classes2:1d3c14", start.evidence)
        // Raw numeric shapes from log 7; road text is a synthetic fixture.
        for ((raw, distance, expected) in listOf(Triple(3, 128, HostNavigationTurn.RIGHT),
            Triple(3, 127, HostNavigationTurn.RIGHT), Triple(2, 2700, HostNavigationTurn.SLIGHT_RIGHT))) {
            val event = current("carlife_show_hud_info", mapOf("action" to 2,
                "navi_turn" to raw, "remain_distance" to distance,
                "total_distance" to 3700, "road_name" to "test road"))
            assertEquals(HostNavigationChange.UPDATED, event.change)
            assertEquals("H02:classes2:17abdc", event.evidence)
            val field = event.delta.maneuver as HostNavigationField.Value
            assertEquals(expected, field.value.turn)
            assertEquals(distance.toLong(), field.value.distanceMeters)
            assertEquals("test road", field.value.afterRoad)
            assertFalse(event.unverifiedFields.contains("road_name-role"))
            assertEquals("H02:classes2:17abdc/17a338/1ba904/1bae4c:HUD-maneuver", field.evidence)
            assertEquals(HostNavigationField.Absent, event.delta.currentRoad)
            assertEquals(3700L, (event.delta.distanceRemainingMeters as HostNavigationField.Value).value)
            assertEquals(HostNavigationField.Absent, event.delta.timeRemainingSeconds)
            assertEquals(HostNavigationField.Absent, event.delta.lanes)
        }
        for ((action, values) in listOf("mix_notify_start_navi" to mapOf("isNavi" to false),
            "carlife_show_hud_info" to mapOf("action" to 3))) {
            val end = current(action, values)
            assertEquals(HostNavigationChange.ENDED, end.change)
            assertEquals("H02:classes2:17aae8", end.evidence)
        }
    }

    @Test fun upgradedHostRetainsStrictTypesAndReportsUnsupportedVersions() {
        val upgraded = source.copy(version = "4.0.23-20261016")
        for (wrong in listOf("true", 1, 1L, null))
            assertNull(CarWithNavigation.decode("mix_notify_start_navi", mapOf("isNavi" to wrong), upgraded))
        for (wrong in listOf("2", 2L, false, null))
            assertNull(CarWithNavigation.decode("carlife_show_hud_info", mapOf("action" to wrong), upgraded))
        for (distance in listOf(0, -1, Int.MAX_VALUE, 127L, "127", null)) {
            val event = requireNotNull(CarWithNavigation.decode("carlife_show_hud_info",
                mapOf("action" to 2, "navi_turn" to 3, "remain_distance" to distance), upgraded))
            assertNull((event.delta.maneuver as HostNavigationField.Value).value.distanceMeters)
        }
        val unknown = source.copy(version = "4.0.24-20261016")
        val values = mapOf("isNavi" to true)
        assertNull(CarWithNavigation.decode("mix_notify_start_navi", values, unknown))
        assertTrue(CarWithNavigation.diagnostic("mix_notify_start_navi", values, unknown, null)
            .contains("reason=unsupported-version"))
        assertTrue(CarWithNavigation.diagnostic("mix_notify_start_navi", mapOf("isNavi" to "true"), upgraded, null)
            .contains("reason=invalid-action-or-type"))
    }

    @Test fun confirmedRoadNameBelongsToTheManeuverForBothReviewedVersions() {
        val road = "测试转向后道路🚘"
        for (version in listOf("4.0.14-20260801", "4.0.23-20261016")) {
            for (action in listOf(1, 2)) {
                val event = requireNotNull(CarWithNavigation.decode("carlife_show_hud_info",
                    mapOf("action" to action, "navi_turn" to 3, "remain_distance" to 101,
                        "road_name" to road), source.copy(version = version)))
                val maneuver = (event.delta.maneuver as HostNavigationField.Value).value
                assertEquals(road, maneuver.afterRoad)
                assertNull(maneuver.description)
                assertEquals(HostNavigationField.Absent, event.delta.currentRoad)
                assertFalse(event.unverifiedFields.contains("road_name-role"))
            }
        }
    }

    @Test fun absentBlankOrWrongTypeRoadCannotReuseThePreviousHint() {
        for (road in listOf(null, "", " \t", 42, true)) {
            val event = requireNotNull(decode("carlife_show_hud_info",
                mapOf("action" to 2, "navi_turn" to 3, "remain_distance" to 101, "road_name" to road)))
            val maneuver = (event.delta.maneuver as HostNavigationField.Value).value
            assertNull(maneuver.afterRoad)
            assertEquals(HostNavigationField.Absent, event.delta.currentRoad)
        }
        val missing = requireNotNull(decode("carlife_show_hud_info", mapOf("action" to 2, "navi_turn" to 3)))
        assertNull((missing.delta.maneuver as HostNavigationField.Value).value.afterRoad)
        assertEquals(HostNavigationChange.ENDED,
            decode("carlife_show_hud_info", mapOf("action" to 3, "road_name" to "old road"))?.change)
    }

    @Test fun sourceDiagnosticDistinguishesRawChangesWithoutPrivatePayloads() {
        val icon = byteArrayOf(1, 2, 3)
        val values = mapOf("action" to 2, "navi_turn" to 7, "remain_distance" to 245,
            "total_distance" to 1000, "road_name" to "private test road", "turn_icon_data" to icon)
        fun trace(data: Map<String, Any?>) = CarWithNavigation.diagnostic("carlife_show_hud_info",
            data, source, decode("carlife_show_hud_info", data))
        val first = trace(values)
        assertTrue(first.contains("binding=1 version=4.0.14-20260801"))
        assertTrue(first.contains("decoded=UPDATED"))
        assertTrue(first.contains("turn=int:7 distance=int:245 reference=int:1000"))
        assertTrue(first.contains("roadChars=17"))
        assertTrue(first.contains("iconBytes=3"))
        assertFalse(first.contains("private test road"))
        assertEquals(first, trace(values))
        val roadDigest = Regex("roadSha256=([a-f0-9]{64})").find(first)?.groupValues?.get(1)
        val iconDigest = Regex("iconSha256=([a-f0-9]{64})").find(first)?.groupValues?.get(1)
        assertNotNull(roadDigest)
        assertNotNull(iconDigest)
        assertFalse(trace(values + ("road_name" to "another test road")).contains("roadSha256=$roadDigest"))
        icon.fill(9)
        assertFalse(trace(values).contains("iconSha256=$iconDigest"))
        assertTrue(trace(values + ("action" to "2")).contains("decoded=rejected"))
        assertTrue(trace(values + ("action" to "2")).contains("hudAction=text"))
        assertTrue(trace(values + ("remain_distance" to 245L)).contains("distance=long:245"))
        assertTrue(trace(values + ("remain_distance" to "private input")).contains("distance=text"))
        assertFalse(trace(values + ("remain_distance" to "private input")).contains("private input"))
    }

    @Test fun strictBooleanLifecycleAndIntegerHudEnd() {
        assertEquals(HostNavigationChange.STARTED, decode("mix_notify_start_navi", mapOf("isNavi" to true))?.change)
        assertEquals(HostNavigationChange.ENDED, decode("mix_notify_start_navi", mapOf("isNavi" to false))?.change)
        assertEquals(HostNavigationChange.ENDED, decode("carlife_show_hud_info", mapOf("action" to 3))?.change)
        for (wrong in listOf("false", 0, 0L, null))
            assertNull(decode("mix_notify_start_navi", mapOf("isNavi" to wrong)))
        for (wrong in listOf("3", 3L, 3.0, false, null, 0, 99))
            assertNull(decode("carlife_show_hud_info", mapOf("action" to wrong)))
    }

    @Test fun firstHudCannotStartAndZeroManeuverDistanceDoesNotMeanArrival() {
        val event = requireNotNull(decode("carlife_show_hud_info", mapOf("action" to 1,
            "remain_distance" to 0, "total_distance" to 2000, "road_name" to "turn road", "navi_turn" to 7)))
        assertEquals(HostNavigationChange.UPDATED, event.change)
        assertEquals(HostNavigationEndReason.UNKNOWN, event.endReason)
        assertEquals(0L, event.observation?.distanceHintMeters)
        assertEquals(2000L, event.observation?.referenceDistanceMeters)
        assertEquals(HostNavigationField.Absent, event.delta.currentRoad)
        assertEquals(2000L, (event.delta.distanceRemainingMeters as HostNavigationField.Value).value)
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
            assertEquals(500L, (event.delta.distanceRemainingMeters as HostNavigationField.Value).value)
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

    @Test fun userRequestedTotalDistanceTrialIsIndependentOfManeuverDistanceForBothVersions() {
        for (version in listOf("4.0.14-20260801", "4.0.23-20261016")) {
            for ((kind, remaining, total) in listOf(Triple(1, 6400, 6400), Triple(2, 4000, 6400),
                Triple(2, 92, 6400), Triple(2, 0, 0))) {
                val event = requireNotNull(CarWithNavigation.decode("carlife_show_hud_info",
                    mapOf("action" to kind, "navi_turn" to 3,
                        "remain_distance" to remaining, "total_distance" to total), source.copy(version = version)))
                val route = event.delta.distanceRemainingMeters as HostNavigationField.Value
                assertEquals(total.toLong(), route.value)
                assertTrue(route.evidence.contains("total_distance-route:user-test-20261112"))
                assertTrue(event.unverifiedFields.contains("total_distance-route-role-user-test"))
                val maneuver = (event.delta.maneuver as HostNavigationField.Value).value
                assertEquals(remaining.toLong().takeIf { it > 0 }, maneuver.distanceMeters)
                assertEquals(HostNavigationField.Absent, event.delta.timeRemainingSeconds)
                assertEquals(HostNavigationField.Absent, event.delta.arrivalEpochSeconds)
            }
        }
    }

    @Test fun invalidOrMissingTrialDistanceClearsWithoutUsingManeuverDistance() {
        for (total in listOf(null, -1, Int.MAX_VALUE, "6400", 6400L, true)) {
            val event = requireNotNull(decode("carlife_show_hud_info", mapOf("action" to 2,
                "navi_turn" to 3, "remain_distance" to 92, "total_distance" to total)))
            assertEquals(HostNavigationField.Clear, event.delta.distanceRemainingMeters)
            assertEquals(92L, (event.delta.maneuver as HostNavigationField.Value).value.distanceMeters)
        }
        val missing = requireNotNull(decode("carlife_show_hud_info", mapOf("action" to 2,
            "navi_turn" to 3, "remain_distance" to 92)))
        assertEquals(HostNavigationField.Clear, missing.delta.distanceRemainingMeters)
        for (action in listOf("mix_notify_start_navi", "carlife_show_hud_info")) {
            val end = requireNotNull(decode(action, mapOf("isNavi" to false, "action" to 3,
                "total_distance" to 6400)))
            assertEquals(HostNavigationChange.ENDED, end.change)
            assertEquals(HostNavigationField.Absent, end.delta.distanceRemainingMeters)
        }
    }
}

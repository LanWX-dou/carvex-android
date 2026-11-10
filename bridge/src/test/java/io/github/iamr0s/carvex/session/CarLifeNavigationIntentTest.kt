package io.github.iamr0s.carvex.session

import org.junit.Assert.*
import org.junit.Test

class CarLifeNavigationIntentTest {
    @Test fun booleanFalseEndsNavigation() {
        assertTrue(CarLifeNavigationIntent.ended("mix_notify_start_navi",mapOf("isNavi" to false)))
        assertFalse(CarLifeNavigationIntent.ended("mix_notify_start_navi",mapOf("isNavi" to true)))
    }

    @Test fun hudEndIsNotAZeroDistanceUpdate() {
        assertTrue(CarLifeNavigationIntent.ended("carlife_show_hud_info",mapOf(
            "action" to 3,"navi_turn" to 0,"remain_distance" to 0,"road_name" to null)))
        for(action in 1..2)assertFalse(CarLifeNavigationIntent.ended("carlife_show_hud_info",
            mapOf("action" to action,"remain_distance" to 0)))
    }

    @Test fun absentOrMistypedLifecycleCannotDiscardRoute() {
        for(value in listOf(null,0,"false",3))assertFalse(CarLifeNavigationIntent.ended(
            "mix_notify_start_navi",mapOf("isNavi" to value)))
        for(value in listOf(null,3L,"3",false))assertFalse(CarLifeNavigationIntent.ended(
            "carlife_show_hud_info",mapOf("action" to value)))
        assertFalse(CarLifeNavigationIntent.ended("mix_notify_start_navi",emptyMap()))
        assertFalse(CarLifeNavigationIntent.ended("carlife_show_hud_info",emptyMap()))
    }

    @Test fun unrelatedActionsDoNotEndNavigation() {
        for(action in listOf(null,"carlife_change_theme","other"))assertFalse(
            CarLifeNavigationIntent.ended(action,mapOf("isNavi" to false,"action" to 3)))
    }
}

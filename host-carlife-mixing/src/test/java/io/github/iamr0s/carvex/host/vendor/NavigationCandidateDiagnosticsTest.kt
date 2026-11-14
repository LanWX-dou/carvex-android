package io.github.iamr0s.carvex.host.vendor

import com.ucar.map.UCarMapInfo
import io.github.iamr0s.carvex.sessioncore.HostNavigationSource
import org.junit.Assert.*
import org.junit.Test

class NavigationCandidateDiagnosticsTest {
    private val source = HostNavigationSource("xiaomi", 7, "4.0.23-20261016")
    private fun capture(values: Map<String, Any?>, action: String = "carlife_show_hud_info",
                        expand: (Any) -> Any? = { null }): List<String> = mutableListOf<String>().also { lines ->
        NavigationRawDiagnostics(lines::add, expand).record(action, values, source)
    }

    @Test fun missingRouteCandidatesAndPresentZeroRemainDistinctWithoutChangingNavigation() {
        val values = mapOf("action" to 2, "remain_distance" to 44, "total_distance" to 44,
            "destinationRemainingDistance" to 0L, "destinationRemainingTime" to null)
        val before = CarWithNavigation.decode("carlife_show_hud_info", values, source)
        val lines = capture(values)
        val summary = lines.single { "event=raw-candidate-summary" in it }
        assertTrue(lines.any { "\"candidate\":\"destinationRemainingDistance\"" in it && "\"value\":\"0\"" in it })
        assertTrue(summary.contains("\"state\":\"null\""))
        assertTrue(summary.contains("\"notObserved\":[\"TITLE_1\",\"TITLE_2\""))
        assertEquals(before, CarWithNavigation.decode("carlife_show_hud_info", values, source))
        assertTrue(lines.last().contains("event=raw-end"))
    }

    @Test fun nativeTitlesNestedModelsCallbackArraysAndArrivalKeepTheirOriginalPathsAndTypes() {
        val values = mapOf("native" to mapOf("ucar.map.bundle.TITLE_1" to "19 公里 / 31 分钟",
            "title2" to "预计 12:45 到达"), "navigationInfo" to mapOf("remainDistance" to 19000,
            "remainTime" to 1860L), "onViaListRemainInfoUpdate" to arrayOf(intArrayOf(9000, 19000), intArrayOf(900, 1860)),
            "arriveTime" to 1794631500000L, "arriveTimeZone" to "Asia/Shanghai",
            "roadRemainingDistance" to -1, "roadRemainingTime" to "unknown")
        val lines = capture(values)
        assertTrue(NavigationCandidateDiagnostics.hasCandidate(mapOf("nested" to values)))
        assertTrue(lines.any { "\"candidate\":\"TITLE_1\"" in it && "\"preview\":\"19 公里 / 31 分钟\"" in it })
        assertTrue(lines.any { "\"candidate\":\"remainTime\"" in it && "java.lang.Long" in it && "\"unit\":\"unverified\"" in it })
        assertTrue(lines.any { "\"onViaListRemainInfoUpdate\",\"1\",\"1\"]" in it && "\"value\":\"1860\"" in it })
        assertTrue(lines.any { "\"candidate\":\"roadRemainingDistance\"" in it && "\"value\":\"-1\"" in it })
        val callback = capture(mapOf("arguments" to intArrayOf(19000, 1860)), "sdk.onRemainInfoUpdate")
        assertTrue(NavigationRawDiagnostics.isNavigationAction("sdk.onRemainInfoUpdate"))
        assertTrue(callback.single { "event=raw-candidate-summary" in it }.contains("\"state\":\"action-only\""))
        assertTrue(callback.any { "\"arguments\",\"0\"]" in it && "\"value\":\"19000\"" in it })
    }

    @Test fun knownDeliveredObjectsAreExpandedEvenWhenRawSerializationOrOneGetterFails() {
        assertTrue(NavigationCandidateDiagnostics.hasCandidate(mapOf("native" to UCarMapInfo("剩余 19 公里"))))
        val lines = capture(mapOf("native" to UCarMapInfo("剩余 19 公里", failSecond = true))) {
            throw UnsupportedOperationException("fixture parcel unavailable")
        }
        assertTrue(lines.any { "\"candidate\":\"TITLE_1\"" in it && "\"preview\":\"剩余 19 公里\"" in it })
        assertTrue(lines.any { "\"candidate\":\"TITLE_2\"" in it && "\"encoding\":\"error\"" in it && "java.lang.IllegalStateException" in it })
        assertTrue(lines.any { "\"<raw>\"]" in it && "java.lang.UnsupportedOperationException" in it })
        val unknown = object { fun getTitle1(): String = error("must not be invoked") }
        assertNull(NavigationCandidateDiagnostics.readObject(unknown))
    }

    @Test fun aJsonDiagnosticViewPreservesOriginalTextAndDoesNotBecomeNavigationInput() {
        val json = "{\"destinationRemainingDistance\":19000,\"destinationRemainingTime\":1860}"
        val values = mapOf("action" to 2, "params" to json)
        val before = CarWithNavigation.decode("carlife_show_hud_info", values, source)
        val lines = capture(values) { value ->
            if (value == json) mapOf("destinationRemainingDistance" to 19000, "destinationRemainingTime" to 1860) else null
        }
        assertTrue(lines.any { "\"params\"]" in it && "\"encoding\":\"utf16be-base64\"" in it })
        assertTrue(lines.any { "\"params\",\"<json>\",\"destinationRemainingDistance\"]" in it && "\"value\":\"19000\"" in it })
        assertEquals(before, CarWithNavigation.decode("carlife_show_hud_info", values, source))
        assertTrue(NavigationCandidateDiagnostics.hasCandidate(values) { value ->
            if (value == json) mapOf("remainTime" to 1860) else null
        })
        // A text-returning adapter must not recursively expand the same JSON forever.
        assertEquals(1, capture(values) { if (it == json) json else null }
            .count { "\"params\"]" in it && "event=raw-field" in it })
    }

    @Test fun observerReportsUnattachedUpstreamsAndCyclesOrBrokenSinksRemainHarmless() {
        val lines = mutableListOf<String>()
        NavigationRawDiagnostics(lines::add).observer(source)
        val observer = lines.single()
        assertTrue(observer.contains("binding=7"))
        assertTrue(observer.contains("\"nativeMapBundle\":\"not-attached\""))
        assertTrue(observer.contains("\"easyconnNaviCallbacks\":\"not-registered\""))
        val cycle = mutableMapOf<String, Any?>()
        cycle["self"] = cycle
        assertFalse(NavigationCandidateDiagnostics.hasCandidate(cycle))
        assertFalse(NavigationRawDiagnostics.isNavigationAction("carlife_vehicle_music_progress"))
        NavigationRawDiagnostics({ throw IllegalStateException("sink") }).also {
            it.observer(source)
            it.record("carlife_show_hud_info", cycle, source)
        }
    }
}

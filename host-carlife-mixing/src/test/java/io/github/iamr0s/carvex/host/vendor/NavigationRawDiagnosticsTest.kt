package io.github.iamr0s.carvex.host.vendor

import io.github.iamr0s.carvex.sessioncore.HostNavigationSource
import org.junit.Assert.*
import org.junit.Test
import java.util.Base64

class NavigationRawDiagnosticsTest {
    private val source = HostNavigationSource("xiaomi", 1, "4.0.23-20261016")
    private fun capture(values: Map<String, Any?>): List<String> = mutableListOf<String>().also { lines ->
        NavigationRawDiagnostics(lines::add).record("carlife_show_hud_info", values, source)
    }

    @Test fun unknownFieldsNestedLanesAndWrongTypesAreRecordedWithoutChangingDecode() {
        val values = mapOf("action" to 2, "navi_turn" to 3, "remain_distance" to 117,
            "total_distance" to 19000L, "total_time" to "31 分钟",
            "lanes" to listOf(mapOf("recommended" to true, "angles" to intArrayOf(0, 90))),
            "extra_unknown" to null)
        val before = CarWithNavigation.decode("carlife_show_hud_info", values, source)
        val lines = capture(values)
        assertEquals(before, CarWithNavigation.decode("carlife_show_hud_info", values, source))
        assertTrue(lines.first().contains("\"extra_unknown\""))
        assertTrue(lines.any { "\"path\":[\"extras\",\"total_distance\"]" in it && "java.lang.Long" in it && "\"value\":\"19000\"" in it })
        assertTrue(lines.any { "\"path\":[\"extras\",\"lanes\",\"0\",\"angles\",\"1\"]" in it && "\"value\":\"90\"" in it })
        assertTrue(lines.any { "\"recommended\"]" in it && "\"value\":\"true\"" in it })
        assertTrue(lines.any { "\"total_time\"]" in it && "\"preview\":\"31 分钟\"" in it })
        assertTrue(lines.last().contains("event=raw-end"))
    }

    @Test fun iconChunksReconstructEveryByteIncludingAnEmptyArray() {
        val bytes = ByteArray(13301) { (it % 251).toByte() }
        val lines = capture(mapOf("turn_icon_data" to bytes, "empty" to byteArrayOf()))
        val chunks = lines.filter { "event=raw-field" in it && "\"turn_icon_data\"]" in it }
        assertTrue(chunks.size > 1)
        assertTrue(chunks.all { "\"bytes\":13301" in it && "\"sha256\":\"" in it })
        val encoded = chunks.joinToString("") { Regex("\\\"value\\\":\\\"([^\\\"]*)\\\"").find(it)!!.groupValues[1].replace("\\u003d", "=") }
        assertArrayEquals(bytes, Base64.getDecoder().decode(encoded))
        assertTrue(lines.any { "\"empty\"]" in it && "\"value\":\"\"" in it && "\"bytes\":0" in it })
    }

    @Test fun fullTextSurvivesChunkingAndEscapesLineBreaksAndSurrogates() {
        val text = "道路\n\"路口\"\\方向🚙".repeat(600) + '\ud800'
        val lines = capture(mapOf("road_name" to text))
        val chunks = lines.filter { "event=raw-field" in it && "\"road_name\"]" in it }
        assertTrue(chunks.size > 1)
        assertTrue(lines.none { '\n' in it || '\r' in it })
        assertTrue(chunks.first().contains("\\u"))
        val encoded = chunks.joinToString("") { Regex("\\\"value\\\":\\\"([^\\\"]*)\\\"").find(it)!!.groupValues[1].replace("\\u003d", "=") }
        val bytes = Base64.getDecoder().decode(encoded)
        val recovered = (bytes.indices step 2).map { (((bytes[it].toInt() and 255) shl 8) or (bytes[it + 1].toInt() and 255)).toChar() }.joinToString("")
        assertEquals(text, recovered)
    }

    @Test fun cyclesExpansionFailuresAndSinkFailuresCannotBreakNavigationCapture() {
        val cycle = mutableMapOf<String, Any?>()
        cycle["self"] = cycle
        assertTrue(capture(cycle).any { "\"encoding\":\"reference\"" in it })
        val lines = mutableListOf<String>()
        val diagnostics = NavigationRawDiagnostics(lines::add) { throw IllegalArgumentException("fixture") }
        diagnostics.record("unknown_navi", mapOf("opaque" to Any(), "after" to 42), source)
        assertTrue(lines.any { "\"encoding\":\"error\"" in it })
        assertTrue(lines.any { "\"value\":\"42\"" in it })
        NavigationRawDiagnostics({ throw IllegalStateException("sink") }).record("carlife_show_hud_info", cycle, source)
    }

    @Test fun capturesHaveDistinctIdsAndOtherNavigationActionsAreRecognized() {
        val lines = mutableListOf<String>()
        val diagnostics = NavigationRawDiagnostics(lines::add)
        diagnostics.record("mix_notify_start_navi", emptyMap(), source)
        diagnostics.record("carlife_show_hud_info", emptyMap(), source)
        assertTrue(lines.any { "capture=1" in it && "event=raw-end" in it })
        assertTrue(lines.any { "capture=2" in it && "event=raw-end" in it })
        for (action in listOf("carlife_show_hud_info", "mix_notify_start_navi", "new_lane_info", "map_route_update"))
            assertTrue(NavigationRawDiagnostics.isNavigationAction(action))
        assertFalse(NavigationRawDiagnostics.isNavigationAction("carlife_vehicle_music_progress"))
    }
}

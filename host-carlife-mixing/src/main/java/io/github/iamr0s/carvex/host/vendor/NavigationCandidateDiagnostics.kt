package io.github.iamr0s.carvex.host.vendor

import java.lang.reflect.InvocationTargetException

/** Observation only: these names do not grant route semantics or activate an upstream SDK. */
internal object NavigationCandidateDiagnostics {
    data class Candidate(val name: String, val keys: Set<String>, val unit: String = "unverified")

    val fields = listOf(
        Candidate("destinationRemainingDistance", setOf("destinationRemainingDistance"), "meters-user-trial"),
        Candidate("destinationRemainingTime", setOf("destinationRemainingTime"), "seconds-user-trial"),
        Candidate("TITLE_1", setOf("ucar.map.bundle.TITLE_1", "TITLE_1", "title1")),
        Candidate("TITLE_2", setOf("ucar.map.bundle.TITLE_2", "TITLE_2", "title2")),
        Candidate("remainDistance", setOf("remainDistance")),
        Candidate("remainTime", setOf("remainTime")),
        Candidate("remainDistanceStr", setOf("remainDistanceStr")),
        Candidate("remainTimeStr", setOf("remainTimeStr")),
        Candidate("arriveTime", setOf("arriveTime")),
        Candidate("arriveTimeZone", setOf("arriveTimeZone"), "timezone-id-candidate"),
        Candidate("roadRemainingDistance", setOf("roadRemainingDistance")),
        Candidate("roadRemainingTime", setOf("roadRemainingTime")),
        Candidate("remain_distance", setOf("remain_distance"), "maneuver-meters"),
        Candidate("total_distance", setOf("total_distance"), "maneuver-reference-meters"),
        Candidate("remain_time", setOf("remain_time")),
        Candidate("total_time", setOf("total_time")),
        Candidate("onRemainInfoUpdate", setOf("onRemainInfoUpdate")),
        Candidate("onViaListRemainInfoUpdate", setOf("onViaListRemainInfoUpdate")),
        Candidate("onRemainDistanceUpdate", setOf("onRemainDistanceUpdate")),
        Candidate("onRemainTimeUpdate", setOf("onRemainTimeUpdate")),
    )
    private val byKey = fields.flatMap { field -> field.keys.map { it to field } }.toMap()
    private val callbacks = fields.filter { it.name.startsWith("on") }

    fun field(key: String?): Candidate? = byKey[key]
    fun callbackAction(action: String?): Candidate? = callbacks.firstOrNull {
        action?.substringAfterLast('.')?.equals(it.name, ignoreCase = true) == true
    }

    /** Look only in supplied containers; never probe the host process or invoke unknown getters. */
    fun hasCandidate(values: Map<String, Any?>, expand: (Any) -> Any? = { null }): Boolean {
        val pending = java.util.ArrayDeque<Any>()
        val visited = java.util.IdentityHashMap<Any, Boolean>()
        pending.add(values)
        var inspected = 0
        while (pending.isNotEmpty() && inspected++ < 128) {
            val current = pending.removeFirst()
            if (visited.put(current, true) != null) continue
            if (objectFields(current.javaClass.name) != null) return true
            fun add(value: Any?) { if (value != null) pending.addLast(value) }
            when (current) {
                is Map<*, *> -> {
                    if (current.keys.any { it is String && field(it) != null }) return true
                    current.values.forEach(::add)
                }
                is Iterable<*> -> current.take(128).forEach(::add)
                is Array<*> -> current.take(128).forEach(::add)
                else -> {
                    val container = current.javaClass.name in setOf("android.os.Bundle", "org.json.JSONObject", "org.json.JSONArray")
                    val json = current is String && current.length <= 65536 &&
                        current.trimStart().firstOrNull() in listOf('{', '[')
                    if (container || json) try { add(expand(current)) } catch (_: Exception) { }
                }
            }
        }
        return false
    }

    private fun objectFields(className: String): List<String>? = when (className) {
        "com.ucar.map.UCarMapInfo" -> listOf("title1", "title2")
        "net.easyconn.carman.bridge.BMapBridge\$NavigationInfo" -> listOf("remainDistance", "remainTime")
        "net.easyconn.carman.bridge.BMapBridge\$BikeNaviInfo" ->
            listOf("remainDistance", "remainTime", "remainDistanceStr", "remainTimeStr")
        "net.easyconn.carman.sdk_communication.P2C.ECP_P2C_PHONE_HUDINFO\$HUDINFO" ->
            listOf("destinationRemainingDistance", "destinationRemainingTime", "roadRemainingDistance", "roadRemainingTime")
        else -> null
    }

    /** Read audited getters only on an object actually delivered to this callback. */
    fun readObject(value: Any): Map<String, Any?>? {
        val names = objectFields(value.javaClass.name) ?: return null
        return names.associateWith { name ->
            try {
                val getter = "get" + name.replaceFirstChar { it.uppercaseChar() }
                value.javaClass.getMethod(getter).invoke(value)
            } catch (error: Exception) {
                val cause = if (error is InvocationTargetException) error.targetException else error
                NavigationRawDiagnostics.Failure(cause.javaClass.name)
            }
        }
    }
}

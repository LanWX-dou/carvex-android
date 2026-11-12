package io.github.iamr0s.carvex.host.vendor

import io.github.iamr0s.carvex.sessioncore.*
import java.security.MessageDigest

/** CarWith 4.0.14 classes2: lifecycle 1c5c20/16fb48, HUD 16fc3c,
 * meter conversion 16f3f0 and icon classifier 1aedb4/1af2fc.
 * Road hints and cached reference distances are not route overview fields. */
internal object CarWithNavigation {
    private data class Evidence(val start: String, val end: String, val hud: String, val maneuver: String)

    // Each supported version has its own original APK audit. The 4.0.23 classifier
    // groups and all 18 reviewed template PNGs match 4.0.14; method offsets changed.
    private val reviewedVersions = mapOf(
        "4.0.14-20260801" to Evidence("H01:classes2:1c5c20", "H01:classes2:16fb48",
            "H01:classes2:16fc3c", "H01:classes2:16fc3c/16f3f0/1aedb4/1af2fc:HUD-maneuver"),
        "4.0.23-20261016" to Evidence("H02:classes2:1d3c14", "H02:classes2:17aae8",
            "H02:classes2:17abdc", "H02:classes2:17abdc/17a338/1ba904/1bae4c:HUD-maneuver"),
    )

    fun recognizes(action: String?) = action == "mix_notify_start_navi" || action == "carlife_show_hud_info"

    /** Trace the producer before normalization, including rejected types, without road/icon payloads. */
    fun diagnostic(action: String?, values: Map<String, Any?>, source: HostNavigationSource,
                   event: HostNavigationEvent?): String {
        fun scalar(key: String): String = when (val value = values[key]) {
            null -> "absent"
            is Int -> "int:$value"
            is Boolean -> "bool:$value"
            is Long -> "long:$value"
            is String -> "text"
            is ByteArray -> "bytes"
            else -> "other"
        }
        fun digest(bytes: ByteArray) = MessageDigest.getInstance("SHA-256").digest(bytes)
            .joinToString("") { "%02x".format(it.toInt() and 0xff) }
        val road = values["road_name"] as? String
        val icon = values["turn_icon_data"] as? ByteArray
        return "navigation event=source source=${source.id} binding=${source.bindingEpoch} " +
            "version=${source.version ?: "unknown"} action=$action decoded=${event?.change ?: "rejected"} " +
            "reason=${when {
                source.version !in reviewedVersions -> "unsupported-version"
                event == null -> "invalid-action-or-type"
                else -> "none"
            }} " +
            "isNavi=${scalar("isNavi")} hudAction=${scalar("action")} turn=${scalar("navi_turn")} " +
            "distance=${scalar("remain_distance")} reference=${scalar("total_distance")} " +
            "roadType=${scalar("road_name")} roadChars=${road?.length ?: 0} " +
            "roadSha256=${road?.let { digest(it.toByteArray(Charsets.UTF_8)) } ?: "absent"} " +
            "iconType=${scalar("turn_icon_data")} iconBytes=${icon?.size ?: 0} " +
            "iconSha256=${icon?.let(::digest) ?: "absent"}"
    }

    fun decode(action: String?, values: Map<String, Any?>, source: HostNavigationSource): HostNavigationEvent? {
        // The inspected producer is version-bound. Other versions need their own evidence.
        val evidence = reviewedVersions[source.version] ?: return null
        return when (action) {
            "mix_notify_start_navi" -> (values["isNavi"] as? Boolean)?.let { active ->
                HostNavigationEvent(source,
                    if (active) HostNavigationChange.STARTED else HostNavigationChange.ENDED,
                    if (active) evidence.start else evidence.end)
            }
            "carlife_show_hud_info" -> {
                val kind = values["action"] as? Int ?: return null
                when (kind) {
                    3 -> HostNavigationEvent(source, HostNavigationChange.ENDED, evidence.end)
                    1, 2 -> HostNavigationEvent(source, HostNavigationChange.UPDATED, evidence.hud,
                        delta = HostNavigationDelta(maneuver = HostNavigationField.Value(
                            HostNavigationManeuver(
                                // A local identity for the current HUD hint, not a vendor/wire index.
                                id = "hud:${values["navi_turn"] as? Int}:${values["road_name"] as? String}",
                                distanceMeters = (values["remain_distance"] as? Int)?.toLong()
                                    ?.takeIf { it in 1 until Int.MAX_VALUE.toLong() },
                                turn = turn(values["navi_turn"] as? Int)),
                            evidence.maneuver)),
                        observation = HostNavigationObservation(
                            roadHint = values["road_name"] as? String,
                            distanceHintMeters = (values["remain_distance"] as? Int)?.toLong()?.takeIf { it >= 0 },
                            referenceDistanceMeters = (values["total_distance"] as? Int)?.toLong()?.takeIf { it >= 0 },
                            turnHint = values["navi_turn"] as? Int,
                            action = kind,
                            iconBytes = (values["turn_icon_data"] as? ByteArray)?.size),
                        unverifiedFields = buildSet {
                            add("road_name-role")
                            if (turn(values["navi_turn"] as? Int) == null) add("navi_turn-enum")
                            if ((values["remain_distance"] as? Int)?.let { it > 0 && it < Int.MAX_VALUE } != true)
                                add("remain_distance-validity")
                        })
                    else -> null
                }
            }
            else -> null
        }
    }

    /** Classifier return values are grouped by the actual APK template pixels, not OPERATION.
     * Informational/roundabout/arrival/fork icons remain unknown until separately mapped. */
    private fun turn(value: Int?): HostNavigationTurn? = when (value) {
        2 -> HostNavigationTurn.SLIGHT_RIGHT
        3 -> HostNavigationTurn.RIGHT
        4 -> HostNavigationTurn.SLIGHT_LEFT
        5 -> HostNavigationTurn.U_TURN
        7, 8 -> HostNavigationTurn.LEFT
        else -> null
    }
}

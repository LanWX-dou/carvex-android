package io.github.iamr0s.carvex.host.vendor

import io.github.iamr0s.carvex.sessioncore.*

/** CarWith 4.0.14 classes2: lifecycle 1c5c20/16fb48, HUD 16fc3c,
 * meter conversion 16f3f0 and icon classifier 1aedb4/1af2fc.
 * Road hints and cached reference distances are not route overview fields. */
internal object CarWithNavigation {
    fun recognizes(action: String?) = action == "mix_notify_start_navi" || action == "carlife_show_hud_info"

    fun decode(action: String?, values: Map<String, Any?>, source: HostNavigationSource): HostNavigationEvent? {
        // The inspected producer is version-bound. Other versions need their own evidence.
        if (source.version != "4.0.14-20260801") return null
        return when (action) {
            "mix_notify_start_navi" -> (values["isNavi"] as? Boolean)?.let { active ->
                HostNavigationEvent(source,
                    if (active) HostNavigationChange.STARTED else HostNavigationChange.ENDED,
                    "H01:classes2:${if (active) "1c5c20" else "16fb48"}")
            }
            "carlife_show_hud_info" -> {
                val kind = values["action"] as? Int ?: return null
                when (kind) {
                    3 -> HostNavigationEvent(source, HostNavigationChange.ENDED, "H01:classes2:16fb48")
                    1, 2 -> HostNavigationEvent(source, HostNavigationChange.UPDATED, "H01:classes2:16fc3c",
                        delta = HostNavigationDelta(maneuver = HostNavigationField.Value(
                            HostNavigationManeuver(
                                // A local identity for the current HUD hint, not a vendor/wire index.
                                id = "hud:${values["navi_turn"] as? Int}:${values["road_name"] as? String}",
                                distanceMeters = (values["remain_distance"] as? Int)?.toLong()
                                    ?.takeIf { it in 1 until Int.MAX_VALUE.toLong() },
                                turn = turn(values["navi_turn"] as? Int)),
                            "H01:classes2:16fc3c/16f3f0/1aedb4/1af2fc:HUD-maneuver")),
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

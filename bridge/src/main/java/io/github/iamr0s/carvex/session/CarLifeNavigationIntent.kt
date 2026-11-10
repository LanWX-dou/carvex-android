package io.github.iamr0s.carvex.session

import android.content.Intent

/** CarWith 4.0.14 classes2.dex 0x16fb48 sends both end notifications.
 * Their values describe host lifecycle, not the unrelated iAP guidance-state enum. */
internal object CarLifeNavigationIntent {
    fun ended(intent: Intent): Boolean {
        val values = intent.extras?.let { bundle ->
            bundle.keySet().associateWith { bundle.get(it) }
        }.orEmpty()
        return ended(intent.action, values)
    }

    internal fun ended(action: String?, values: Map<String, Any?>): Boolean = when (action) {
        "mix_notify_start_navi" -> values["isNavi"] == false
        "carlife_show_hud_info" -> values["action"] == 3
        else -> false
    }
}

package io.github.iamr0s.carvex.carplay.core

import io.github.iamr0s.carvex.sessioncore.DebugLogValue

/** Observes existing wire fields without changing parsing, subscriptions or sent bytes. */
object BusinessDiagnostics {
    fun domain(id: Int): String? = when (id) {
        in 0x5000..0x5003 -> "music"
        0x5200, 0x5201, 0x5202, 0x5203, 0x5204 -> "navigation"
        in 0x4150..0x4159 -> "call"
        else -> null
    }

    fun fields(id: Int, direction: String, fields: List<Pair<Int, ByteArray>>, context: String = ""): List<String> {
        val domain = domain(id) ?: return emptyList()
        val prefix = "debug $domain"
        val scope = "direction=$direction id=${id.toString(16)} $context".trimEnd()
        return buildList {
            var remainingChildren = 128
            add("$prefix event=wire $scope fields=${fields.size}")
            fields.take(64).forEachIndexed { index, (field, bytes) ->
                if (id == 0x5000 || id == 0x5001) {
                    val children = runCatching { IapWire.parseFieldList(bytes).ordered }.getOrNull()
                    if (children == null) {
                        add("$prefix event=field $scope field=$field index=$index malformed-group bytes=${bytes.size}")
                    } else {
                        val selected = children.take(minOf(64, remainingChildren))
                        remainingChildren -= selected.size
                        selected.forEachIndexed { childIndex, (child, value) ->
                            val name = musicName(field, child)
                            val rendered = if (id == 0x5000) {
                                if (field == 1 && child == 0x11) scalar(value, 4) else "marker bytes=${value.size}"
                            } else musicValue(field, child, value)
                            add("$prefix event=field $scope field=$field.$child index=$index.$childIndex name=$name value=$rendered")
                        }
                        if (selected.size < children.size)
                            add("$prefix event=field $scope field=$field.truncated index=$index remaining=${children.size-selected.size}")
                    }
                } else {
                    val (name, rendered) = when (domain) {
                        "navigation" -> navigationValue(id, field, bytes)
                        "call" -> callValue(id, field, bytes)
                        else -> (when(field){0->"elapsedMs";1->"queueIndex";2->"queueStart";else->"parameter"}) to scalar(bytes, 4)
                    }
                    add("$prefix event=field $scope field=$field index=$index name=$name value=$rendered")
                }
            }
            if (fields.size > 64) add("$prefix event=field $scope field=truncated remaining=${fields.size - 64}")
        }
    }

    private fun musicName(group: Int, id: Int): String = when (group to id) {
        0 to 0 -> "persistentId"; 0 to 1 -> "title"; 0 to 4 -> "durationMs"
        0 to 6 -> "album"; 0 to 12 -> "artist"; 0 to 0x1a -> "artworkTransfer"
        1 to 0 -> "playbackStatus"; 1 to 1 -> "elapsedMs"; 1 to 2 -> "queueIndex"
        1 to 3 -> "queueCount"; 1 to 7 -> "appName"; 1 to 0x10 -> "appBundleId"
        1 to 0x11 -> "queueStart"; else -> "attribute"
    }

    private fun musicValue(group: Int, id: Int, bytes: ByteArray): String = when {
        group == 0 && id in setOf(1, 6, 12, 0x10, 0x12) || group == 1 && id in setOf(7, 8, 10, 0x10) -> text(bytes)
        group == 1 && id == 0 -> scalar(bytes, 1) + " status=" + (bytes.singleOrNull()?.toInt()?.and(255)?.let { raw ->
            NowPlayingUpdate.PlaybackStatus.entries.firstOrNull { it.wire == raw }?.name
        } ?: "unknown")
        bytes.size in setOf(1, 2, 4, 8) -> scalar(bytes, bytes.size)
        else -> "bytes=${bytes.size}"
    }

    private fun navigationValue(message: Int, id: Int, bytes: ByteArray): Pair<String, String> {
        if (message == 0x5200 || message == 0x5203)
            return if (id == 0) "component" to scalar(bytes, 2) else "option" to "marker bytes=${bytes.size}"
        val names = when (message) {
            0x5201 -> mapOf(0 to "component", 1 to "guidanceState", 2 to "maneuverState", 3 to "currentRoad", 4 to "destination",
                7 to "distanceRemaining", 10 to "distanceToManeuver", 13 to "maneuverIndex", 14 to "maneuverCount", 15 to "beingShown")
            0x5202 -> mapOf(0 to "component", 1 to "index", 2 to "description", 3 to "type", 4 to "afterRoad", 5 to "distance")
            else -> mapOf(0 to "component", 1 to "index", 2 to "laneGroup", 3 to "instruction")
        }
        val textFields = when (message) { 0x5201 -> setOf(3, 4, 8, 11, 19); 0x5202 -> setOf(2, 4, 6, 13); else -> setOf(3) }
        val rendered = when {
            id in textFields -> text(bytes)
            message == 0x5204 && id == 2 || message == 0x5201 && id == 23 -> "group bytes=${bytes.size}"
            bytes.size in setOf(1, 2, 4, 8) -> scalar(bytes, bytes.size)
            else -> "bytes=${bytes.size}"
        }
        return (names[id] ?: "parameter") to rendered
    }

    private fun callValue(message: Int, id: Int, bytes: ByteArray): Pair<String, String> {
        if (message in setOf(0x4154, 0x4156, 0x4157, 0x4159)) return "subscription" to "marker bytes=${bytes.size}"
        // Contact data and call identifiers are intentionally not decoded for diagnostics.
        if (message == 0x4155 && id in setOf(2, 3, 8, 9, 10, 11, 12) ||
            message == 0x4158 && (id in 0..3 || id in 5..0x11))
            return "state" to if (bytes.size in setOf(1, 2, 4, 8)) scalar(bytes, bytes.size) else "bytes=${bytes.size}"
        return "private" to "redacted bytes=${bytes.size}"
    }

    private fun text(bytes: ByteArray): String = if (bytes.isEmpty() || bytes.last() != 0.toByte())
        "invalid-text bytes=${bytes.size}" else DebugLogValue.text(bytes.copyOf(bytes.size - 1).toString(Charsets.UTF_8))

    private fun scalar(bytes: ByteArray, size: Int): String {
        if (bytes.size != size) return "invalid-width expected=$size bytes=${bytes.size}"
        var value = 0uL
        for (byte in bytes) value = (value shl 8) or (byte.toInt() and 255).toULong()
        return value.toString()
    }
}

package io.github.iamr0s.carvex.sessioncore

import java.security.MessageDigest

/** Bounded, single-line diagnostic values. Callers select fields; never dump an entire Intent. */
object DebugLogValue {
    fun text(value: String?): String {
        if (value == null) return "unknown"
        val escaped = buildString {
            value.take(96).forEach { c ->
                append(when (c) {
                    '\\' -> "\\\\"
                    '"' -> "\\\""
                    '\n' -> "\\n"
                    '\r' -> "\\r"
                    '\t' -> "\\t"
                    else -> if (c.isISOControl() || c.isSurrogate()) "\\u%04x".format(c.code) else c.toString()
                })
            }
        }
        return "\"${escaped.take(192)}${if (value.length > 96 || escaped.length > 192) "…" else ""}\" chars=${value.length} sha256=${digest(value.toByteArray(Charsets.UTF_8))}"
    }

    fun bytes(value: ByteArray): String = "bytes=${value.size} sha256=${digest(value)}"

    fun value(value: Any?): String = when (value) {
        null -> "unknown"
        is String -> text(value)
        is Number, is Boolean -> value.toString()
        is ByteArray -> bytes(value)
        else -> "type=${value.javaClass.simpleName}" // Bitmap/Parcelable contents stay out of logs.
    }

    private fun digest(bytes: ByteArray): String = MessageDigest.getInstance("SHA-256")
        .digest(bytes).take(8).joinToString("") { "%02x".format(it.toInt() and 255) }
}

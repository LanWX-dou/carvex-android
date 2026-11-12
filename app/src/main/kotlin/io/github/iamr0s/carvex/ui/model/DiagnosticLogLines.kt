package io.github.iamr0s.carvex.ui.model

/** Parse visible rows on demand without rebuilding the complete history on every new entry. */
internal fun diagnosticLogLines(raw: List<String>): List<LogLine> = object : AbstractList<LogLine>() {
    override val size: Int get() = raw.size

    override fun get(index: Int): LogLine {
        val line = raw[index]
        val message = line.substringAfter("] ", line)
        val level = when {
            message.startsWith("ERROR", true) || message.contains("failed", true) -> "ERROR"
            message.startsWith("WARN", true) || message.contains("warning", true) -> "WARN"
            else -> "INFO"
        }
        return LogLine(line.substringBefore(" [").takeLast(12), level, message)
    }
}

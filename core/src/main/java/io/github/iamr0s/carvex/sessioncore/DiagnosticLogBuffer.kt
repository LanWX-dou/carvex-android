package io.github.iamr0s.carvex.sessioncore

/** Append without copying the entire history for each live audio/video log entry. */
internal class DiagnosticLogBuffer(initial: List<String> = emptyList()) {
    private val entries = ArrayList(initial)

    fun append(line: String): List<String> = synchronized(entries) {
        entries.add(line)
        snapshot()
    }

    /** Each published list keeps its original length while the buffer continues to grow. */
    fun snapshot(): List<String> = synchronized(entries) {
        val length = entries.size
        object : AbstractList<String>() {
            override val size: Int = length
            override fun get(index: Int): String {
                if (index !in 0 until size) throw IndexOutOfBoundsException("index=$index size=$size")
                return synchronized(entries) { entries[index] }
            }
        }
    }
}

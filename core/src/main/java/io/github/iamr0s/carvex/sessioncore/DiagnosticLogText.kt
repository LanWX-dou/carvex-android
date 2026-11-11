package io.github.iamr0s.carvex.sessioncore

import java.io.File
import java.time.Instant

/** Read and export the complete diagnostic history until the user clears it. */
internal object DiagnosticLogText {
    /** Stream UTF-8 decoding from the beginning, without a file-size or line-count cutoff. */
    fun readDisk(file: File): List<String> {
        if (!file.exists()) return emptyList()
        return file.bufferedReader(Charsets.UTF_8).use { input ->
            input.lineSequence().filter { it.isNotEmpty() }.toList()
        }
    }

    /** A pending clear must not reintroduce the previous disk generation. */
    fun merge(generation: Long, diskGeneration: Long, disk: List<String>,
              evidence: List<String>, recent: List<String>): List<String> {
        val persisted = if (generation == diskGeneration) disk else emptyList()
        return (persisted + evidence + recent).distinct().sortedBy {
            runCatching { Instant.parse(it.substringBefore(" [")) }.getOrDefault(Instant.MIN)
        }
    }
}

package io.github.iamr0s.carvex.sessioncore

import java.io.OutputStream

/** A fixed view of the complete history; writing never copies or encodes the whole log. */
internal class DiagnosticLogExport(private val header: String, private val lines: List<String>) {
    /** The caller owns the stream. Flush before reporting success, and propagate write failures. */
    fun writeTo(output: OutputStream, checkActive: () -> Unit = {}) {
        val writer = output.bufferedWriter(Charsets.UTF_8)
        checkActive()
        writer.write(header)
        for (index in lines.indices) {
            checkActive()
            if (index != 0) writer.write("\n")
            writer.write(lines[index])
        }
        checkActive()
        writer.flush()
    }
}

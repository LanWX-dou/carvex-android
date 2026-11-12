package io.github.iamr0s.carvex.ui

import io.github.iamr0s.carvex.ui.model.diagnosticLogLines
import org.junit.Assert.*
import org.junit.Test

class DiagnosticLogLinesTest {
    @Test fun pageKeepsOldMiddleAndNewestRowsBeyondFormerLimits() {
        val raw = (0 until 3000).map { "2026-11-11T12:34:56.789Z [session] row=$it" }
        val rows = diagnosticLogLines(raw)
        assertEquals(3000, rows.size)
        assertEquals("row=0", rows.first().message)
        assertEquals("row=100", rows[100].message)
        assertEquals("row=2999", rows.last().message)
    }

    @Test fun pageParsesOnlyRequestedRowsAndKeepsLongMessages() {
        val message = "WARN " + "导航".repeat(1000) + " tail-marker"
        var reads = 0
        val raw = object : AbstractList<String>() {
            override val size = 10000
            override fun get(index: Int): String {
                reads++
                return "2026-11-11T12:34:56.789Z [session] $message"
            }
        }
        val rows = diagnosticLogLines(raw)
        assertEquals(0, reads)
        assertEquals(10000, rows.size)
        assertEquals(message, rows[9999].message)
        assertEquals(1, reads)
        assertEquals("WARN", rows[0].level)
    }
}

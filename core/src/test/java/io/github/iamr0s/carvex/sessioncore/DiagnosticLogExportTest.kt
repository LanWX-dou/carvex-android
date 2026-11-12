package io.github.iamr0s.carvex.sessioncore

import kotlinx.coroutines.CancellationException
import kotlinx.coroutines.runBlocking
import org.junit.Assert.*
import org.junit.Test
import java.io.ByteArrayOutputStream
import java.io.IOException
import java.io.OutputStream
import java.security.DigestOutputStream
import java.security.MessageDigest

class DiagnosticLogExportTest {
    private class CountingOutput : OutputStream() {
        var bytes = 0L
        var largestWrite = 0
        var flushed = false
        var closed = false
        override fun write(value: Int) { bytes++ }
        override fun write(data: ByteArray, offset: Int, length: Int) {
            bytes += length
            largestWrite = maxOf(largestWrite, length)
        }
        override fun flush() { flushed = true }
        override fun close() { closed = true }
    }

    @Test(timeout = 30000) fun streamsOneHundredThousandUtf8RowsWithBoundedWrites() {
        val header = "CarVeX diagnostics\n--- Complete raw log ---\n"
        val message = "导航🚘".repeat(128) + " tail-marker"
        fun line(index: Int) = "2026-11-12T12:34:56.789Z [session] row=$index $message"
        val output = CountingOutput()
        var reads = 0
        val history = object : AbstractList<String>() {
            override val size = 100_000
            override fun get(index: Int): String {
                assertEquals(reads++, index)
                if (index >= 10_000) assertTrue("must write before reading all rows", output.bytes > 0)
                return line(index)
            }
        }
        val actual = MessageDigest.getInstance("SHA-256")
        DiagnosticLogExport(header, history).writeTo(DigestOutputStream(output, actual))

        val expected = MessageDigest.getInstance("SHA-256")
        expected.update(header.toByteArray(Charsets.UTF_8))
        repeat(history.size) { index ->
            if (index != 0) expected.update('\n'.code.toByte())
            expected.update(line(index).toByteArray(Charsets.UTF_8))
        }
        assertArrayEquals(expected.digest(), actual.digest())
        assertEquals(100_000, reads)
        assertTrue(output.bytes > 100_000_000L)
        assertTrue("UTF-8 encoder must use bounded byte buffers", output.largestWrite <= 8192)
        assertTrue(output.flushed)
        assertFalse(output.closed)
    }

    @Test fun completeLongLineAndDuplicateRecordsArePreserved() {
        val line = "导航🚘".repeat(50_000) + " tail-marker"
        val output = ByteArrayOutputStream()
        DiagnosticLogExport("header\n", listOf(line, line)).writeTo(output)
        assertEquals("header\n$line\n$line", output.toString(Charsets.UTF_8.name()))
    }

    @Test fun snapshotSurvivesAppendsAndClearWithoutIncludingLaterRows() {
        var history = DiagnosticLogBuffer(listOf("old-0", "old-1"))
        val export = DiagnosticLogExport("header\n", history.snapshot())
        history.append("later-row")
        history = DiagnosticLogBuffer(listOf("new-generation"))
        val output = ByteArrayOutputStream()
        export.writeTo(output)
        assertEquals("header\nold-0\nold-1", output.toString(Charsets.UTF_8.name()))
        val clearedOutput = ByteArrayOutputStream()
        DiagnosticLogExport("header\n", history.snapshot()).writeTo(clearedOutput)
        assertEquals("header\nnew-generation", clearedOutput.toString(Charsets.UTF_8.name()))
    }

    @Test fun writeAndFlushFailuresReachTheCaller() {
        val export = DiagnosticLogExport("header\n", listOf("row"))
        val writeFailure = object : OutputStream() {
            override fun write(value: Int) { throw IOException("disk full") }
        }
        assertThrows(IOException::class.java) { export.writeTo(writeFailure) }
        val flushFailure = object : OutputStream() {
            override fun write(value: Int) {}
            override fun flush() { throw IOException("provider flush failed") }
        }
        assertThrows(IOException::class.java) { export.writeTo(flushFailure) }
    }

    @Test fun cancellationStopsReadingTheRemainingHistory() {
        var reads = 0
        val history = object : AbstractList<String>() {
            override val size = 100_000
            override fun get(index: Int): String { reads++; return "row=$index" }
        }
        assertThrows(CancellationException::class.java) {
            DiagnosticLogExport("header\n", history).writeTo(CountingOutput()) {
                if (reads == 100) throw CancellationException("cancelled")
            }
        }
        assertEquals(100, reads)
    }

    @Test fun storeExportsPendingRowsAndClearExcludesTheOldGeneration() = runBlocking {
        BridgeStore.clearLogs()
        val session = BridgeStore.begin(1)
        try {
            repeat(3000) { BridgeStore.log(session, "stream-export-$it 导航 password=secret") }
            val snapshot = BridgeStore.logs.value
            val output = ByteArrayOutputStream()
            BridgeStore.exportTo(output)
            val text = output.toString(Charsets.UTF_8.name())
            val exportedRows = text.lineSequence().filter { it.contains("stream-export-") }.toList()
            assertEquals(snapshot, exportedRows)
            assertTrue(text.startsWith("CarVeX diagnostics\nVersion: unavailable\n"))
            assertTrue(text.contains("Session=$session"))
            assertTrue(text.endsWith("stream-export-2999 导航 password=<redacted>"))
            assertFalse(text.contains("password=secret"))
            BridgeStore.clearLogs()
            val cleared = ByteArrayOutputStream()
            BridgeStore.exportTo(cleared)
            assertFalse(cleared.toString(Charsets.UTF_8.name()).contains("stream-export-"))
        } finally { BridgeStore.clearLogs(); BridgeStore.idle() }
    }
}

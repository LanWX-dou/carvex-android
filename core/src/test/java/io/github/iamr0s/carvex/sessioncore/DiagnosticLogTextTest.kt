package io.github.iamr0s.carvex.sessioncore

import org.junit.Assert.*
import org.junit.Test
import java.nio.file.Files
import java.time.Instant
import kotlin.concurrent.thread

class DiagnosticLogTextTest {
    private fun line(index: Int) = "${Instant.EPOCH.plusMillis(index.toLong())} [session] line=$index"

    @Test fun historyPreservesEveryEntryBeyondFormerLineLimit() {
        val all = (0 until 10000).map(::line)
        val buffer = DiagnosticLogBuffer()
        all.forEach(buffer::append)
        assertEquals(all, buffer.snapshot())
    }

    @Test fun publishedSnapshotRemainsStableDuringLaterAppendsAndClear() {
        var buffer = DiagnosticLogBuffer(listOf(line(0)))
        val first = buffer.snapshot()
        val second = buffer.append(line(1))
        buffer = DiagnosticLogBuffer()
        buffer.append(line(2))
        assertEquals(listOf(line(0)), first)
        assertEquals(listOf(line(0), line(1)), second)
        assertThrows(IndexOutOfBoundsException::class.java) { first[1] }
        assertEquals(listOf(line(2)), buffer.snapshot())
    }

    @Test(timeout = 5000) fun publishedHistoryCanBeReadWhileLoggingContinues() {
        val initial = (0 until 3000).map(::line)
        val buffer = DiagnosticLogBuffer(initial)
        val published = buffer.snapshot()
        val writer = thread { (3000 until 10000).forEach { buffer.append(line(it)) } }
        try {
            repeat(20) { assertEquals(initial, published.toList()) }
        } finally { writer.join() }
        assertEquals((0 until 10000).map(::line), buffer.snapshot())
    }

    @Test fun exportIncludesDiskHistoryAndPendingMemoryWithoutDuplicateRows() {
        val disk = (0 until 2700).map(::line)
        val recent = (1000 until 3000).map(::line)
        val exported = DiagnosticLogText.merge(1, 1, disk, listOf(line(15)), recent)
        assertEquals((0 until 3000).map(::line), exported)
        assertTrue(exported.first().startsWith("1970-01-01T00:00:00Z [session]"))
    }

    @Test fun pendingClearExcludesOldDiskEvenBeforeWriterTruncatesIt() {
        val exported = DiagnosticLogText.merge(2, 1, listOf(line(1)), emptyList(), listOf(line(2)))
        assertEquals(listOf(line(2)), exported)
    }

    @Test fun completedClearAllowsNewGenerationDisk() {
        val exported = DiagnosticLogText.merge(2, 2, listOf(line(2)), emptyList(), listOf(line(3)))
        assertEquals(listOf(line(2), line(3)), exported)
    }

    @Test fun timestampsSortChronologicallyAcrossZeroAndFractionalSeconds() {
        assertEquals(listOf(line(0), line(1), line(1000)),
            DiagnosticLogText.merge(0, 0, listOf(line(1)), listOf(line(1000)), listOf(line(0))))
    }

    @Test fun diskReadRetainsMoreThanFourHundredLinesAndUtf8() {
        val file = Files.createTempFile("carvex-log-test", ".txt").toFile()
        try {
            val lines = (0 until 3000).map { line(it) + " 导航" }
            file.writeText(lines.joinToString("\n", postfix = "\n"))
            assertEquals(lines, DiagnosticLogText.readDisk(file))
        } finally { file.delete() }
    }

    @Test fun diskReadPreservesCompleteUtf8HistoryBeyondFormerFileSizeLimit() {
        val file = Files.createTempFile("carvex-log-test", ".txt").toFile()
        try {
            val lines = (0 until 4000).map { line(it) + " 导航".repeat(100) }
            file.writeText(lines.joinToString("\n", postfix = "\n"))
            assertTrue(file.length() > 1024 * 1024)
            assertEquals(lines, DiagnosticLogText.readDisk(file))
        } finally { file.delete() }
    }

    @Test fun liveLoggerActuallyUpdatesMemoryAndRawExport() {
        BridgeStore.clearLogs()
        val session = BridgeStore.begin(1)
        try {
            repeat(2100) { BridgeStore.log(session, "retention-regression-$it") }
            assertEquals(2100, BridgeStore.logs.value.size)
            assertTrue(BridgeStore.logs.value.first().endsWith("retention-regression-0"))
            assertTrue(BridgeStore.logs.value[100].endsWith("retention-regression-100"))
            assertTrue(BridgeStore.logs.value.last().endsWith("retention-regression-2099"))
            val exported = BridgeStore.export()
            assertTrue(exported.contains("[$session] retention-regression-0"))
            assertTrue(exported.contains("[$session] retention-regression-100"))
            assertTrue(exported.contains("[$session] retention-regression-2099"))
            assertEquals(2100, exported.lineSequence().count { it.contains("retention-regression-") })
            BridgeStore.clearLogs()
            assertFalse(BridgeStore.export().contains("retention-regression-"))
        } finally { BridgeStore.clearLogs(); BridgeStore.idle() }
    }

    @Test fun longMessagesKeepTheirTailWhileSecretsRemainRedacted() {
        BridgeStore.clearLogs()
        val session = BridgeStore.begin(1)
        try {
            val message = "diagnostic-" + "x".repeat(4096) + " password=secret-value tail-marker"
            BridgeStore.log(session, message)
            val stored = BridgeStore.logs.value.single()
            assertTrue(stored.contains("x".repeat(4096)))
            assertTrue(stored.endsWith("password=<redacted> tail-marker"))
            assertFalse(stored.contains("secret-value"))
            assertTrue(BridgeStore.export().contains(stored))
        } finally { BridgeStore.clearLogs(); BridgeStore.idle() }
    }
}

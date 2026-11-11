package io.github.iamr0s.carvex.sessioncore

import org.junit.Assert.*
import org.junit.Test

class BusinessLogEvidenceTest {
    @Test fun singleLineTextKeepsCompleteEscapedValueAndIdentity() {
        val value = "歌词\n\r\t\"\\" + "\u0001".repeat(500) + "tail-marker"
        val rendered=DebugLogValue.text(value)
        assertFalse(rendered.contains('\n'));assertFalse(rendered.contains('\r'))
        assertTrue(rendered.contains("\\u0001".repeat(500)))
        assertTrue(rendered.contains("tail-marker\" chars=${value.length}"))
        assertTrue(rendered.contains("\\n"));assertTrue(rendered.contains("sha256="))
        assertNotEquals(DebugLogValue.text("a".repeat(100)+"X"),DebugLogValue.text("a".repeat(100)+"Y"))
        assertEquals("unknown",DebugLogValue.text(null))
    }

    @Test fun opaqueObjectsNeverRunTheirToStringAndBinaryContentsStayOutOfTheLog() {
        val opaque=object{override fun toString():String=error("must not inspect")}
        assertTrue(DebugLogValue.value(opaque).startsWith("type="))
        val bytes="raw-audio-or-image".toByteArray()
        assertFalse(DebugLogValue.bytes(bytes).contains("raw-audio"))
        assertTrue(DebugLogValue.bytes(bytes).contains("bytes=${bytes.size}"))
    }

    @Test fun highFrequencySamplesDoNotEvictSubscriptionPauseOrHangup() {
        val evidence=BusinessLogEvidence()
        fun record(message:String)=evidence.record(message,message)
        record("debug navigation event=subscription direction=rx id=5200 accepted=true")
        record("debug music event=playback source=media-session state=PAUSED")
        record("debug call event=demand active=false generation=2")
        repeat(5000){
            record("debug music event=field direction=tx id=5001 field=1.1 value=$it")
            record("debug navigation event=host-field source=intent field=road_name value=road-$it")
            record("debug call event=audio-health source=host acceptedBlocks=$it")
        }
        val lines=evidence.snapshot()
        assertTrue(lines.any{it.contains("id=5200")})
        assertTrue(lines.any{it.contains("state=PAUSED")})
        assertTrue(lines.any{it.contains("active=false")})
        assertEquals(1,lines.count{it.contains("field=1.1")})
        assertTrue(lines.any{it.contains("value=4999")})
        assertTrue(lines.size<12)
    }

    @Test fun repeatedSessionsClearEvidenceAndUniqueKeysHaveABoundedBudget() {
        val evidence=BusinessLogEvidence()
        repeat(1000){evidence.record("line-$it","debug navigation event=field direction=tx id=5201 field=$it value=x")}
        repeat(1000){evidence.record("call-$it","debug call event=demand active=true generation=$it")}
        assertTrue(evidence.snapshot().size<=320)
        evidence.clear();assertTrue(evidence.snapshot().isEmpty())
    }

    @Test fun exporterKeepsBusinessEventsAfterVideoNoiseAndIsolatesNextAttempt() {
        BridgeStore.clearLogs()
        try{
            val session=BridgeStore.begin(1)
            repeat(240){BridgeStore.log(session,"startup-$it")}
            BridgeStore.log(session,"debug navigation event=subscription direction=rx id=5200 accepted=true")
            BridgeStore.log(session,"debug music event=playback state=PAUSED")
            BridgeStore.log(session,"debug call event=demand active=false")
            repeat(2200){BridgeStore.log(session,"video-noise-$it")}
            val exported=BridgeStore.export()
            assertTrue(exported.contains("debug navigation event=subscription"))
            assertTrue(exported.contains("debug music event=playback"))
            assertTrue(exported.contains("debug call event=demand"))
            BridgeStore.clearLogs();BridgeStore.begin(2)
            assertFalse(BridgeStore.export().contains("debug navigation event=subscription"))
        }finally{BridgeStore.clearLogs();BridgeStore.idle()}
    }
}

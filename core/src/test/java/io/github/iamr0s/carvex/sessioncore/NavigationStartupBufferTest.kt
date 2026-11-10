package io.github.iamr0s.carvex.sessioncore

import io.github.iamr0s.carvex.pcm.PcmFormat
import kotlinx.coroutines.*
import kotlinx.coroutines.channels.Channel
import org.junit.Assert.*
import org.junit.Test

class NavigationStartupBufferTest {
    private val format=PcmFormat(16000,1)
    private class Stream:NegotiatedAudioTransport {
        var closed=false
        val output=Channel<ByteArray>(8)
        override val ready get()=!closed
        override val formats=mapOf(2 to PcmFormat(16000,1))
        override val microphoneFormat:PcmFormat?=null
        override suspend fun send(category:Int,pcm:ByteArray,format:PcmFormat){output.send(pcm)}
        override fun close(){closed=true}
    }
    @Test fun slowSetupPreservesCopiedPrefixBeforeLiveAudio():Unit=runBlocking {
        withTimeout(2000){
            var time=0L
            val gate=AudioDemandGate(now={time});val bridge=HostAudioBridge({},configureRoute={})
            val stream=Stream();val ready=CompletableDeferred<Unit>()
            try{
                val first=ByteArray(320){1}
                val ticket=gate.receiveNavigation(first,format,bridge::receive)!!
                first.fill(9) // Binder is allowed to reuse its buffer.
                val preparing=async(start=CoroutineStart.UNDISPATCHED){
                    gate.prepare(ticket,{ready.await();stream},bridge::attach,bridge::receive)
                }
                time=500_000_000L
                repeat(10){assertNull(gate.receiveNavigation(ByteArray(320){2},format,bridge::receive))}
                ready.complete(Unit);assertTrue(preparing.await())
                gate.receiveNavigation(ByteArray(320){3},format,bridge::receive)
                assertArrayEquals(ByteArray(320){1}+ByteArray(3200){2},stream.output.receive())
                assertArrayEquals(ByteArray(320){3},stream.output.receive())
            }finally{ready.complete(Unit);gate.close();bridge.close()}
        }
    }
    @Test fun sourceStopDiscardsPendingPrefixAndRejectsLateSetup():Unit=runBlocking {
        val gate=AudioDemandGate();val stream=Stream()
        val delivered=mutableListOf<ByteArray>()
        val forward:(ByteArray,Int,PcmFormat)->Unit={pcm,_,_->delivered.add(pcm)}
        val ticket=gate.receiveNavigation(ByteArray(320){1},format,forward)!!
        gate.sourceState(2,false)
        assertNull(gate.receiveNavigation(ByteArray(320){2},format,forward))
        assertFalse(gate.install(ticket,stream,{},forward))
        assertTrue(stream.closed);assertTrue(delivered.isEmpty())
        gate.sourceState(2,true)
        val next=gate.receiveNavigation(ByteArray(320){3},format,forward)!!
        assertTrue(gate.prepare(next,{Stream()},{},forward))
        assertEquals(1,delivered.size);assertEquals(3,delivered.single()[0].toInt())
        gate.close()
    }
    @Test fun bufferHasByteBoundAndPreservesPrefixOnOverflow():Unit=runBlocking {
        val logs=mutableListOf<String>();val gate=AudioDemandGate(log={logs.add(it)})
        val delivered=mutableListOf<ByteArray>()
        val forward:(ByteArray,Int,PcmFormat)->Unit={pcm,_,_->delivered.add(pcm)}
        val ticket=gate.receiveNavigation(ByteArray(32768){1},format,forward)!!
        repeat(20){gate.receiveNavigation(ByteArray(320){2},format,forward)}
        assertTrue(gate.prepare(ticket,{Stream()},{},forward))
        assertEquals(1,delivered.size);assertEquals(32768,delivered.single().size)
        assertTrue(delivered.single().all{it==1.toByte()})
        assertEquals(1,logs.count{it.contains("buffer full")})
        gate.close()
    }
    @Test fun formatChangesKeepTheirOwnPcmGeometry():Unit=runBlocking {
        val gate=AudioDemandGate();val delivered=mutableListOf<Pair<PcmFormat,ByteArray>>()
        val forward:(ByteArray,Int,PcmFormat)->Unit={pcm,_,fmt->delivered.add(fmt to pcm)}
        val stereo=PcmFormat(48000,2)
        val ticket=gate.receiveNavigation(ByteArray(320){1},format,forward)!!
        gate.receiveNavigation(ByteArray(960){2},stereo,forward)
        assertTrue(gate.prepare(ticket,{Stream()},{},forward))
        assertEquals(listOf(format,stereo),delivered.map{it.first})
        assertEquals(listOf(320,960),delivered.map{it.second.size})
        gate.close()
    }
    @Test fun failureAndDisconnectNeverReplayOldPendingData():Unit=runBlocking {
        val gate=AudioDemandGate(retryDelayNs=0);val delivered=mutableListOf<ByteArray>()
        val forward:(ByteArray,Int,PcmFormat)->Unit={pcm,_,_->delivered.add(pcm)}
        val old=gate.receiveNavigation(ByteArray(320){1},format,forward)!!
        gate.failed(old)
        val next=gate.receiveNavigation(ByteArray(320){2},format,forward)!!
        assertTrue(gate.prepare(next,{Stream()},{},forward))
        assertEquals(1,delivered.size);assertEquals(2,delivered.single()[0].toInt())
        gate.close()
        assertNull(gate.receiveNavigation(ByteArray(320){3},format,forward))
        assertEquals(1,delivered.size)
    }
}

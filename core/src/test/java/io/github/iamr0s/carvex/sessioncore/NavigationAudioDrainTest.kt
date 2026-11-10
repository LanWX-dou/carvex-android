package io.github.iamr0s.carvex.sessioncore

import io.github.iamr0s.carvex.pcm.PcmFormat
import kotlinx.coroutines.*
import kotlinx.coroutines.channels.Channel
import org.junit.Assert.*
import org.junit.Test

class NavigationAudioDrainTest {
    private val format=PcmFormat(16000,1)
    private class Stream(category:Int,private val beforeSend:suspend ()->Unit={},
        private val onFinish:suspend ()->Unit={}):NegotiatedAudioTransport {
        val output=Channel<ByteArray>(16)
        @Volatile var closed=false
        @Volatile var finishes=0
        override val ready get()=!closed
        override val formats=mapOf(category to PcmFormat(16000,1))
        override val microphoneFormat:PcmFormat?=null
        override suspend fun send(category:Int,pcm:ByteArray,format:PcmFormat){
            beforeSend();check(ready);output.send(pcm)
        }
        override suspend fun finish(){finishes++;onFinish()}
        override fun close(){closed=true}
    }

    @Test fun naturalStopPreservesAcceptedTailAndRejectsLatePcm():Unit=runBlocking {
        withTimeout(2000){
            val entered=CompletableDeferred<Unit>();val release=CompletableDeferred<Unit>()
            val prompt=Stream(2,{entered.complete(Unit);release.await()})
            val bridge=HostAudioBridge({},configureRoute={});val gate=AudioDemandGate()
            try{
                val ticket=gate.claim(2,320,format)!!
                gate.prepare(ticket,{prompt},bridge::attach)
                val first=ByteArray(320){1};val tail=ByteArray(320){2}
                bridge.receive(first,2,format);entered.await()
                bridge.receive(tail,2,format)
                gate.sourceState(2,false,bridge::finish);bridge.state(2,0)
                val done=bridge.finish(prompt)
                assertFalse(prompt.closed);assertNull(gate.claim(2,320,format))
                bridge.receive(ByteArray(320){3},2,format)
                release.complete(Unit);done.await()
                assertArrayEquals(first,prompt.output.receive())
                assertArrayEquals(tail,prompt.output.receive())
                assertTrue(prompt.output.tryReceive().isFailure)
                assertEquals(1,prompt.finishes);assertTrue(prompt.closed)
                assertFalse(gate.ifActive(ticket){fail("old first block escaped")})
            }finally{release.complete(Unit);gate.close();bridge.close()}
        }
    }

    @Test fun mediaContinuesDuringDrainAndNextPromptWaitsForOldClose():Unit=runBlocking {
        withTimeout(2000){
            val entered=CompletableDeferred<Unit>();val release=CompletableDeferred<Unit>()
            val prompt=Stream(2,onFinish={entered.complete(Unit);release.await()})
            val media=Stream(1);val next=Stream(2)
            val bridge=HostAudioBridge({},configureRoute={});val gate=AudioDemandGate()
            try{
                bridge.attach(media)
                gate.prepare(gate.claim(2,320,format)!!,{prompt},bridge::attach)
                gate.sourceState(2,false,bridge::finish);bridge.state(2,0);entered.await()
                gate.sourceState(2,true);bridge.state(2,1)
                var created=false
                val preparing=async(start=CoroutineStart.UNDISPATCHED){
                    gate.prepare(gate.claim(2,320,format)!!,{
                        assertTrue(prompt.closed);created=true;next
                    },bridge::attach)
                }
                assertFalse(created)
                val music=ByteArray(320){7};bridge.receive(music,1,format)
                assertArrayEquals(music,media.output.receive());assertTrue(media.ready)
                release.complete(Unit);assertTrue(preparing.await())
                assertTrue(next.ready);assertTrue(media.ready)
                bridge.receive(ByteArray(320){8},2,format)
                assertEquals(8,next.output.receive()[0].toInt())
            }finally{release.complete(Unit);gate.close();bridge.close()}
        }
    }

    @Test fun disconnectAbortsADrainingTransportImmediately():Unit=runBlocking {
        withTimeout(2000){
            val entered=CompletableDeferred<Unit>()
            val prompt=Stream(2,onFinish={entered.complete(Unit);awaitCancellation()})
            val bridge=HostAudioBridge({},configureRoute={});val gate=AudioDemandGate()
            try{
                gate.prepare(gate.claim(2,320,format)!!,{prompt},bridge::attach)
                gate.sourceState(2,false,bridge::finish);entered.await()
                gate.close();assertTrue(prompt.closed)
            }finally{gate.close();bridge.close()}
        }
    }

    @Test fun pendingAttachIsAbortedInsteadOfDrained():Unit=runBlocking {
        val gate=AudioDemandGate();val prompt=Stream(2)
        try{
            val ticket=gate.claim(2,320,format)!!
            assertFalse(gate.prepare(ticket,{prompt},{
                gate.sourceState(2,false){fail("uninstalled stream must not drain");CompletableDeferred(Unit)}
            }))
            assertTrue(prompt.closed);assertEquals(0,prompt.finishes)
        }finally{gate.close()}
    }

    @Test fun missingEncoderCompletionTimesOutAndStillReleasesTheLane():Unit=runBlocking {
        withTimeout(7000){
            val prompt=Stream(2,onFinish={awaitCancellation()})
            val bridge=HostAudioBridge({},configureRoute={});val gate=AudioDemandGate()
            try{
                gate.prepare(gate.claim(2,320,format)!!,{prompt},bridge::attach)
                gate.sourceState(2,false,bridge::finish)
                bridge.finish(prompt).await()
                assertTrue(prompt.closed)
                gate.sourceState(2,true)
                val next=Stream(2)
                assertTrue(gate.prepare(gate.claim(2,320,format)!!,{next},bridge::attach))
                assertTrue(next.ready)
                bridge.receive(ByteArray(320){9},2,format)
                assertEquals(9,next.output.receive()[0].toInt())
            }finally{gate.close();bridge.close()}
        }
    }

    @Test fun encoderFailureReleasesLaneAndRepeatedPromptsCanFinish():Unit=runBlocking {
        withTimeout(2000){
            val bridge=HostAudioBridge({},configureRoute={});val gate=AudioDemandGate()
            try{
                repeat(5){index->
                    gate.sourceState(2,true);bridge.state(2,1)
                    val prompt=Stream(2,onFinish={if(index==0)throw java.io.IOException("encoder failed")})
                    assertTrue(gate.prepare(gate.claim(2,320,format)!!,{prompt},bridge::attach))
                    bridge.receive(ByteArray(320){index.toByte()},2,format)
                    assertEquals(index,prompt.output.receive()[0].toInt())
                    gate.sourceState(2,false,bridge::finish);bridge.state(2,0)
                    bridge.finish(prompt).await()
                    assertTrue(prompt.closed);assertEquals(1,prompt.finishes)
                }
            }finally{gate.close();bridge.close()}
        }
    }
}

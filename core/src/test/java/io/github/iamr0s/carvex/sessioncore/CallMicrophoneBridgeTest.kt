package io.github.iamr0s.carvex.sessioncore

import android.content.Intent
import android.view.KeyEvent
import android.view.MotionEvent
import android.view.Surface
import io.github.iamr0s.carvex.pcm.PcmFormat
import kotlinx.coroutines.*
import org.junit.Assert.*
import org.junit.Test

class CallMicrophoneBridgeTest {
    private val format=PcmFormat(16000,1)
    private class Input:MicrophoneInput {
        var closed=false
        override val ready get()=!closed
        override fun close(){closed=true}
    }
    private class Stream:NegotiatedAudioTransport {
        var closed=false
        override val ready get()=!closed
        override val formats=mapOf(1 to PcmFormat(16000,1))
        override val microphoneFormat:PcmFormat?=null
        override suspend fun send(category:Int,pcm:ByteArray,format:PcmFormat){}
        override fun close(){closed=true}
    }
    private class Host:CastHost {
        var blocks=0;var accept=true
        override suspend fun microphone(pcm:ByteArray,rate:Int,channels:Int,encoding:Int):Boolean{blocks++;return accept}
        override suspend fun bind(){}
        override suspend fun selectCarLifePlusAudio(){}
        override suspend fun surface(surface:Surface,width:Int,height:Int,dpi:Int){}
        override suspend fun format(width:Int,height:Int):android.os.Bundle?=null
        override suspend fun invoke(action:String,configure:(Intent)->Intent):android.os.Bundle?=null
        override fun key(event:KeyEvent)=false
        override fun touch(event:MotionEvent)=false
        override fun close(){}
    }

    @Test fun oldCallDetachCannotRemoveNewInputAndRejectedPcmIsNotCounted():Unit=runBlocking {
        val bridge=HostAudioBridge({});val host=Host();val old=Input();val next=Input()
        try{
            bridge.bindHost(host);bridge.attachMicrophone(old,format);bridge.attachMicrophone(next,format)
            bridge.detachMicrophone(old)
            assertTrue(old.closed);assertFalse(next.closed);assertTrue(bridge.microphoneReady())
            assertTrue(bridge.microphone(ByteArray(320),format))
            host.accept=false;assertFalse(bridge.microphone(ByteArray(320),format))
            assertEquals(320L,bridge.snapshot().microphoneBytes)
            bridge.detachMicrophone(next);assertFalse(bridge.microphoneReady())
        }finally{bridge.close()}
    }

    @Test fun hangupWhileWaitingForRouteLockRejectsOldPcmBeforeHostDispatch():Unit=runBlocking {
        withTimeout(2000){
            val entered=CompletableDeferred<Unit>();val release=CompletableDeferred<Unit>()
            val bridge=HostAudioBridge({},configureRoute={entered.complete(Unit);release.await()})
            val host=Host();var active=true
            try{
                bridge.bindHost(host);bridge.attachMicrophone(Input(),format)
                val attaching=async{bridge.attach(Stream())};entered.await()
                val sending=async(start=CoroutineStart.UNDISPATCHED){bridge.microphone(ByteArray(320),format){active}}
                assertFalse(sending.isCompleted)
                active=false;release.complete(Unit);attaching.await()
                assertFalse(sending.await());assertEquals(0,host.blocks)
            }finally{release.complete(Unit);bridge.close()}
        }
    }

    @Test fun callTransitionWaitsForLateMediaSetupToClose():Unit=runBlocking {
        withTimeout(2000){
            val gate=AudioDemandGate();val input=Stream()
            val entered=CompletableDeferred<Unit>();val release=CompletableDeferred<Unit>()
            try{
                val ticket=gate.prime(1,format)!!
                val pending=async{gate.prepare(ticket,{entered.complete(Unit);release.await();input},{fail("obsolete stream attached")})}
                entered.await();gate.sourceState(1,false)
                val waiting=async(start=CoroutineStart.UNDISPATCHED){gate.awaitPreparation(1)}
                assertFalse(waiting.isCompleted)
                release.complete(Unit);waiting.await()
                assertFalse(pending.await());assertTrue(input.closed)
                assertNull(gate.prime(1,format))
            }finally{release.complete(Unit);gate.close()}
        }
    }
}

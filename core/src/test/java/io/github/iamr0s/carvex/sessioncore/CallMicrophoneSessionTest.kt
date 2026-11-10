package io.github.iamr0s.carvex.sessioncore

import kotlinx.coroutines.*
import org.junit.Assert.*
import org.junit.Test

class CallMicrophoneSessionTest {
    private class Input:AutoCloseable {var closes=0;override fun close(){closes++}}

    @Test fun activeCallBeforeAttachOpensOnceAndHangupRevokesImmediately():Unit=runBlocking {
        val call=CallMicrophoneSession(CoroutineScope(coroutineContext+Dispatchers.Unconfined)){}
        val input=Input();var opens=0;var current:(()->Boolean)?=null
        try{
            call.update(true)
            call.attach{valid->opens++;current=valid;input}
            call.update(true)
            assertEquals(1,opens);assertTrue(current!!());assertTrue(call.active)
            call.update(false)
            assertFalse(current!!());assertFalse(call.active);assertEquals(1,input.closes)
            call.update(false);assertEquals(1,input.closes)
        }finally{call.close()}
    }

    @Test fun nextCallWaitsForObsoleteSetupAndClosesItBeforeOpening():Unit=runBlocking {
        withTimeout(2000){
            val call=CallMicrophoneSession(CoroutineScope(coroutineContext+Dispatchers.Unconfined)){}
            val release=CompletableDeferred<Unit>();val first=Input();val second=Input()
            var opens=0;lateinit var oldCurrent:()->Boolean
            try{
                call.attach{valid->
                    if(++opens==1){oldCurrent=valid;release.await();first}
                    else{assertEquals(1,first.closes);assertTrue(valid());second}
                }
                call.update(true);assertTrue(oldCurrent())
                call.update(false);assertFalse(oldCurrent())
                call.update(true);assertEquals(1,opens);assertFalse(oldCurrent())
                release.complete(Unit)
                assertEquals(2,opens);assertEquals(1,first.closes)
                call.update(false);assertEquals(1,second.closes)
            }finally{release.complete(Unit);call.close()}
        }
    }

    @Test fun failureDoesNotRetryWithoutANewCall():Unit=runBlocking {
        val call=CallMicrophoneSession(CoroutineScope(coroutineContext+Dispatchers.Unconfined)){}
        var opens=0
        try{
            call.attach{opens++;error("SETUP refused")}
            call.update(true);call.update(true);yield()
            assertEquals(1,opens)
            call.update(false);call.update(true);assertEquals(2,opens)
        }finally{call.close()}
    }

    @Test fun disconnectCancelsPendingSetupAndIgnoresLateCallEvents():Unit=runBlocking {
        val call=CallMicrophoneSession(CoroutineScope(coroutineContext+Dispatchers.Unconfined)){}
        var cancelled=false;var opens=0;lateinit var current:()->Boolean
        call.attach{valid->
            opens++;current=valid
            try{awaitCancellation()}finally{cancelled=true}
        }
        call.update(true);call.close()
        assertTrue(cancelled);assertFalse(current());assertFalse(call.active)
        call.update(true);call.attach{fail("closed");Input()}
        assertEquals(1,opens)
    }

    @Test fun disconnectClosesInstalledInputOnce():Unit=runBlocking {
        val input=Input()
        val call=CallMicrophoneSession(CoroutineScope(coroutineContext+Dispatchers.Unconfined)){}
        call.attach{input};call.update(true);call.close();call.close()
        assertEquals(1,input.closes)
    }
}

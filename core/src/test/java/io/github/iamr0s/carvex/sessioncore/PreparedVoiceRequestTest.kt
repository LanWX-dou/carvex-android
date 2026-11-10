package io.github.iamr0s.carvex.sessioncore

import kotlinx.coroutines.*
import org.junit.Assert.*
import org.junit.Test

class PreparedVoiceRequestTest {
    @Test fun startWaitsForInputAndReservesTheToggleWithoutHoldingItsLock() = runBlocking {
        val voice=VoiceButtonToggle()
        val installed=CompletableDeferred<Boolean>()
        val commands=mutableListOf<Boolean>()
        val request=async(start=CoroutineStart.UNDISPATCHED){
            voice.preparedRequest(null,{installed.await()}){commands+=it;true}
        }
        assertFalse(request.isCompleted)
        assertFalse(voice.isRequestedActive)
        assertTrue(commands.isEmpty())
        assertFalse(voice.toggle{fail("another request overtook pending preparation");true})
        installed.complete(true)
        assertTrue(request.await())
        assertEquals(listOf(true),commands)
        assertTrue(voice.isRequestedActive)
    }

    @Test fun failedInputDoesNotDispatchOrTurnTheNextRequestIntoAStop() = runBlocking {
        val voice=VoiceButtonToggle()
        val commands=mutableListOf<Boolean>()
        assertFalse(voice.preparedRequest(null,{false}){commands+=it;true})
        assertFalse(voice.isRequestedActive)
        assertTrue(commands.isEmpty())
        assertTrue(voice.preparedRequest(null,{true}){commands+=it;true})
        assertEquals(listOf(true),commands)
    }

    @Test fun manualAndToggleStopsBypassInputPreparation() = runBlocking {
        val voice=VoiceButtonToggle()
        val commands=mutableListOf<Boolean>()
        val forbidden:suspend ()->Boolean={error("STOP attempted input SETUP")}
        assertTrue(voice.preparedRequest(false,forbidden){commands+=it;true})
        assertTrue(voice.request(true){commands+=it;true})
        assertTrue(voice.preparedRequest(null,forbidden){commands+=it;true})
        assertEquals(listOf(false,true,false),commands)
        assertFalse(voice.isRequestedActive)
    }

    @Test fun disconnectWhilePreparingRejectsLateInputCompletion() = runBlocking {
        val voice=VoiceButtonToggle()
        val installed=CompletableDeferred<Boolean>()
        val request=async(start=CoroutineStart.UNDISPATCHED){
            voice.preparedRequest(true,{installed.await()}){fail("START after close");true}
        }
        voice.close()
        installed.complete(true)
        assertFalse(request.await())
        assertFalse(voice.isRequestedActive)
    }

    @Test fun cancellingPreparationReleasesItsReservation() = runBlocking {
        val voice=VoiceButtonToggle()
        val installed=CompletableDeferred<Boolean>()
        val request=async(start=CoroutineStart.UNDISPATCHED){
            voice.preparedRequest(true,{installed.await()}){fail("cancelled START dispatched");true}
        }
        request.cancelAndJoin()
        assertFalse(voice.isRequestedActive)
        assertTrue(voice.preparedRequest(true,{true}){true})
        assertTrue(voice.isRequestedActive)
    }

    @Test fun aRejectedKeyAfterPreparationDoesNotCommitRequestedState() = runBlocking {
        val voice=VoiceButtonToggle()
        assertFalse(voice.preparedRequest(true,{true}){false})
        assertFalse(voice.isRequestedActive)
        assertTrue(voice.preparedRequest(null,{true}){start->assertTrue(start);true})
    }
}

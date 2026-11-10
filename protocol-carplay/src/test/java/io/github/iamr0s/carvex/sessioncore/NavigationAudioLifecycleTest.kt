package io.github.iamr0s.carvex.sessioncore

import io.github.iamr0s.carvex.carplay.core.AudioCapabilities
import io.github.iamr0s.carvex.carplay.core.AudioStreamLifecycle
import io.github.iamr0s.carvex.carplay.core.CarPlayAudioPlan
import io.github.iamr0s.carvex.pcm.PcmFormat
import kotlinx.coroutines.*
import kotlinx.coroutines.channels.Channel
import org.junit.Assert.*
import org.junit.Test

class NavigationAudioLifecycleTest {
    private val format=PcmFormat(16000,1)
    private class Stream(category:Int):NegotiatedAudioTransport {
        var closed=false
        override val ready get()=!closed
        override val formats=mapOf(category to PcmFormat(16000,1))
        override val microphoneFormat:PcmFormat?=null
        override suspend fun send(category:Int,pcm:ByteArray,format:PcmFormat){}
        override fun close(){closed=true}
    }

    @Test fun repeatedCompletionClosesOnlyNavigationAndRearmsBeyondRetryLimit():Unit=runBlocking {
        val gate=AudioDemandGate();val bridge=HostAudioBridge({},configureRoute={})
        val media=Stream(1);val speech=Stream(3)
        try{
            bridge.attach(media);bridge.attach(speech)
            repeat(5){
                gate.sourceState(2,true)
                val ticket=gate.claim(2,320,format)!!;val prompt=Stream(2)
                assertEquals(1,ticket.attempt)
                assertTrue(gate.prepare(ticket,{prompt},bridge::attach))
                assertEquals(setOf(1,2,3),bridge.categories())
                gate.sourceState(2,false);bridge.state(2,0);gate.sourceState(2,false)
                assertTrue(prompt.closed)
                assertEquals(setOf(1,3),bridge.categories())
                assertFalse(media.closed);assertFalse(speech.closed)
                assertNull("late PCM must not reopen a completed prompt",gate.claim(2,320,format))
                assertNull(gate.prime(2,format))
                assertFalse(gate.ifActive(ticket){fail("stopped first PCM must not be replayed")})
            }
        }finally{gate.close();bridge.close()}
    }

    @Test fun stoppedQueuedSetupIsSkippedAndCannotFailTheNextActivation():Unit=runBlocking {
        val gate=AudioDemandGate();val old=gate.claim(2,320,format)!!
        gate.sourceState(2,false);gate.sourceState(2,true)
        val next=gate.claim(2,320,format)!!
        assertFalse(gate.prepare(old,{error("stopped SETUP must not run")},{error("must not attach")}))
        gate.failed(old)
        assertTrue(gate.prepare(next,{Stream(2)},{}))
        assertTrue(gate.ifActive(next){})
        gate.close()
    }

    @Test fun currentPreparationFailureStillPropagatesAndConsumesItsBoundedRetry():Unit=runBlocking {
        val gate=AudioDemandGate(retryDelayNs=0)
        val failure=java.io.IOException("route failure")
        val first=gate.claim(2,320,format)!!;val stream=Stream(2)
        assertSame(failure,runCatching{gate.prepare(first,{stream},{throw failure})}.exceptionOrNull())
        assertTrue(stream.closed)
        val second=gate.claim(2,320,format)!!
        assertEquals(2,second.attempt)
        assertSame(failure,runCatching{gate.prepare(second,{throw failure},{})}.exceptionOrNull())
        assertNull(gate.claim(2,320,format))
        gate.close()
    }

    @Test fun nextPromptWaitsUntilLateOldSetupHasBeenClosed():Unit=runBlocking {
        withTimeout(2000){
            val gate=AudioDemandGate();val release=CompletableDeferred<Unit>()
            val oldStream=Stream(2);val old=gate.claim(2,320,format)!!
            var attachments=0
            val first=async(start=CoroutineStart.UNDISPATCHED){
                gate.prepare(old,{release.await();oldStream},{attachments++})
            }
            gate.sourceState(2,false);gate.sourceState(2,true)
            val next=gate.claim(2,320,format)!!;var newCreation=false
            val second=async(start=CoroutineStart.UNDISPATCHED){
                gate.prepare(next,{
                    assertTrue("old close must precede a new reservation",oldStream.closed)
                    newCreation=true;Stream(2)
                },{attachments++})
            }
            assertFalse(newCreation)
            release.complete(Unit)
            assertFalse(first.await());assertTrue(second.await());assertEquals(1,attachments)
            assertFalse(gate.ifActive(old){fail("old PCM must not cross the activation boundary")})
            assertTrue(gate.ifActive(next){})
            gate.close()
        }
    }

    @Test fun stopDuringSuspendingAttachClosesPromptAndPreservesMedia():Unit=runBlocking {
        withTimeout(2000){
            val gate=AudioDemandGate()
            val entered=CompletableDeferred<Unit>();val release=CompletableDeferred<Unit>()
            var attachments=0
            val bridge=HostAudioBridge({},configureRoute={
                if(++attachments==2){entered.complete(Unit);release.await()}
            })
            val media=Stream(1);val prompt=Stream(2)
            try{
                bridge.attach(media)
                val ticket=gate.claim(2,320,format)!!
                val installing=async(start=CoroutineStart.UNDISPATCHED){
                    runCatching{gate.prepare(ticket,{prompt},bridge::attach)}
                }
                entered.await();gate.sourceState(2,false)
                assertTrue("close must not wait for attach to return",prompt.closed)
                release.complete(Unit)
                assertFalse(installing.await().getOrThrow())
                assertEquals(setOf(1),bridge.categories());assertFalse(media.closed)
                gate.sourceState(2,true)
                val replacement=Stream(2)
                assertTrue(gate.prepare(gate.claim(2,320,format)!!,{replacement},bridge::attach))
                assertFalse(replacement.closed)
            }finally{release.complete(Unit);gate.close();bridge.close()}
        }
    }

    @Test fun sessionCloseClosesAttachedAndAttachingStreams():Unit=runBlocking {
        val gate=AudioDemandGate();val media=Stream(1);val prompt=Stream(2)
        assertTrue(gate.prepare(gate.claim(1,320,format)!!,{media},{}))
        assertFalse(gate.prepare(gate.claim(2,320,format)!!,{prompt},{gate.close()}))
        assertTrue(media.closed);assertTrue(prompt.closed)
        gate.sourceState(2,true)
        assertNull(gate.claim(2,320,format))
    }

    @Test fun nextPromptWaitsForReceiverTeardownAcknowledgement():Unit=runBlocking {
        withTimeout(2000){
            val gate=AudioDemandGate();val lifecycle=AudioStreamLifecycle()
            val lease=lifecycle.reserve(101,"default",1,exclusive=true)
            val old=object:NegotiatedAudioTransport {
                var closed=false
                override val ready get()=!closed
                override val formats=mapOf(2 to format)
                override val microphoneFormat:PcmFormat?=null
                override suspend fun send(category:Int,pcm:ByteArray,format:PcmFormat){}
                override fun close(){if(!closed){closed=true;lifecycle.beginClose(lease)}}
            }
            assertTrue(gate.prepare(gate.claim(2,320,format)!!,{old},{}))
            gate.sourceState(2,false);gate.sourceState(2,true)
            var setupStarted=false
            val next=async(start=CoroutineStart.UNDISPATCHED){
                gate.prepare(gate.claim(2,320,format)!!,{
                    lifecycle.reserve(101,"default",2,exclusive=true)
                    setupStarted=true;Stream(2)
                },{})
            }
            assertFalse(setupStarted);assertFalse(next.isCompleted)
            lifecycle.completeClose(lease)
            assertTrue(next.await());assertTrue(setupStarted)
            gate.close();lifecycle.close()
        }
    }

    @Test fun newPromptWaitsForBothLocalDrainAndReceiverTeardown():Unit=runBlocking {
        withTimeout(2000){
            val gate=AudioDemandGate();val lifecycle=AudioStreamLifecycle()
            val bridge=HostAudioBridge({},configureRoute={})
            val drained=CompletableDeferred<Unit>();val entered=CompletableDeferred<Unit>()
            val lease=lifecycle.reserve(101,"default",1,exclusive=true)
            val old=object:NegotiatedAudioTransport {
                @Volatile var closed=false
                override val ready get()=!closed
                override val formats=mapOf(2 to format)
                override val microphoneFormat:PcmFormat?=null
                override suspend fun send(category:Int,pcm:ByteArray,format:PcmFormat){}
                override suspend fun finish(){entered.complete(Unit);drained.await()}
                override fun close(){if(!closed){closed=true;lifecycle.beginClose(lease)}}
            }
            try{
                gate.prepare(gate.claim(2,320,format)!!,{old},bridge::attach)
                gate.sourceState(2,false,bridge::finish);entered.await();gate.sourceState(2,true)
                val creating=CompletableDeferred<Unit>();var setup=false
                val next=async(start=CoroutineStart.UNDISPATCHED){
                    gate.prepare(gate.claim(2,320,format)!!,{
                        assertFalse(old.ready);creating.complete(Unit)
                        lifecycle.reserve(101,"default",2,exclusive=true)
                        setup=true;Stream(2)
                    },bridge::attach)
                }
                assertFalse(creating.isCompleted);assertFalse(setup)
                drained.complete(Unit);creating.await()
                assertFalse(setup);assertFalse(next.isCompleted)
                lifecycle.completeClose(lease)
                assertTrue(next.await());assertTrue(setup)
            }finally{drained.complete(Unit);gate.close();bridge.close();lifecycle.close()}
        }
    }

    @Test fun musicContinuesWithNewSourcePcmAfterNavigationEnds():Unit=runBlocking {
        val gate=AudioDemandGate();val bridge=HostAudioBridge({},configureRoute={})
        val output=Channel<ByteArray>(4)
        val media=object:NegotiatedAudioTransport {
            var closed=false
            override val ready get()=!closed
            override val formats=mapOf(1 to format)
            override val microphoneFormat:PcmFormat?=null
            override suspend fun send(category:Int,pcm:ByteArray,format:PcmFormat){output.send(pcm)}
            override fun close(){closed=true}
        }
        try{
            bridge.attach(media)
            val firstApp=ByteArray(320){1};val nextApp=ByteArray(320){2}
            bridge.receive(firstApp,1,format)
            assertArrayEquals(firstApp,withTimeout(2000){output.receive()})
            assertTrue(gate.prepare(gate.claim(2,320,format)!!,{Stream(2)},bridge::attach))
            gate.sourceState(2,false);bridge.state(2,0)
            bridge.receive(nextApp,1,format)
            assertArrayEquals(nextApp,withTimeout(2000){output.receive()})
            assertTrue(media.ready);assertEquals(setOf(1),bridge.categories())
        }finally{gate.close();bridge.close();output.cancel()}
    }

    @Test fun navigationCannotShareAnotherPurposesTeardownSlot()=runBlocking {
        val gate=AudioStreamLifecycle();val speech=gate.reserve(100,"speechRecognition",1)
        assertTrue(gate.conflicts(100,"alert",exclusive=true))
        assertFalse(gate.conflicts(100,"speechRecognition"));assertFalse(gate.conflicts(101,"default"))
        assertTrue(runCatching{gate.reserve(100,"alert",2,exclusive=true)}.exceptionOrNull() is IllegalStateException)
        assertTrue(gate.isActive(speech.type,speech.purpose))
        assertEquals(3L,gate.reserve(101,"default",3,exclusive=true).id)
        gate.close()
    }

    @Test fun activePromptPreventsALaterPurposeFromSharingItsType()=runBlocking {
        val gate=AudioStreamLifecycle();val prompt=gate.reserve(100,"alert",1,exclusive=true)
        assertTrue(gate.conflicts(100,"speechRecognition"))
        assertTrue(runCatching{gate.reserve(100,"speechRecognition",2)}.exceptionOrNull() is IllegalStateException)
        assertTrue(gate.isActive(prompt.type,prompt.purpose))
        gate.beginClose(prompt);gate.completeClose(prompt)
        assertFalse(gate.conflicts(100,"speechRecognition"))
        assertEquals(3L,gate.reserve(100,"speechRecognition",3).id)
        gate.close()
    }

    @Test fun navigationUsesAdvertisedAlternateWhenMediaOccupiesType100()=runBlocking {
        val gate=AudioStreamLifecycle();val media=gate.reserve(100,"media",1)
        val entries=listOf(AudioCapabilities.Entry(100,"alert",null,0x8000L),
            AudioCapabilities.Entry(101,"default",null,0x8000L))
        val occupied=CarPlayAudioPlan.routes.filter{gate.conflicts(it.type,it.purpose,exclusive=true)}.toSet()
        val source=PcmFormat(48000,2)
        val route=CarPlayAudioPlan.selectPlayback(entries,2,source,excludedRoutes=occupied){false}!!.route
        assertEquals(CarPlayAudioPlan.alternate,route)
        val prompt=gate.reserve(route.type,route.purpose,2,exclusive=true)
        gate.beginClose(prompt);gate.completeClose(prompt)
        assertTrue(gate.isActive(media.type,media.purpose))
        assertNull(CarPlayAudioPlan.selectPlayback(entries.take(1),2,source,excludedRoutes=occupied){false})
        gate.close()
    }
}

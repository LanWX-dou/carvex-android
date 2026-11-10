package io.github.iamr0s.carvex.session

import org.junit.Assert.*
import org.junit.Test

class HeldSystemMediaKeysTest {
    private data class Event(val code:Int,val started:Long,val at:Long,val down:Boolean)
    private val events=mutableListOf<Event>()
    private val send:(Int,Long,Long,Boolean)->Boolean={code,started,at,down->
        events.add(Event(code,started,at,down));true}

    @Test fun forwardAndRewindKeepTheirPhysicalReleaseTimes(){
        val keys=HeldSystemMediaKeys()
        keys.transition(90,true,100,send);keys.transition(89,true,120,send)
        keys.transition(90,false,850,send);keys.transition(89,false,900,send)
        assertEquals(listOf(Event(90,100,100,true),Event(89,120,120,true),
            Event(90,100,850,false),Event(89,120,900,false)),events)
    }
    @Test fun concurrentDevicesDoNotReleaseAnotherDevicesHold(){
        val keys=HeldSystemMediaKeys()
        keys.transition(90,true,100,send);keys.transition(90,true,200,send)
        keys.transition(90,false,300,send)
        assertEquals(listOf(Event(90,100,100,true)),events)
        keys.transition(90,false,400,send)
        assertEquals(Event(90,100,400,false),events.last())
    }
    @Test fun cancellationReleasesEachHeldKeyOnceAndRejectsLateDown(){
        val keys=HeldSystemMediaKeys()
        keys.transition(90,true,100,send);keys.transition(89,true,110,send)
        keys.close(600,send);keys.close(700,send)
        assertEquals(listOf(Event(90,100,100,true),Event(89,110,110,true),
            Event(90,100,600,false),Event(89,110,600,false)),events)
        assertFalse(keys.transition(90,true,800,send))
    }
    @Test fun rejectedDownDoesNotGenerateARelease(){
        val keys=HeldSystemMediaKeys()
        assertFalse(keys.transition(90,true,100){_,_,_,_->false})
        assertTrue(keys.transition(90,false,200,send));keys.close(300,send)
        assertTrue(events.isEmpty())
    }
    @Test fun failedReleaseRemainsEligibleForCloseCleanup(){
        val keys=HeldSystemMediaKeys()
        keys.transition(90,true,100,send)
        assertFalse(keys.transition(90,false,200){_,_,_,_->false})
        keys.close(300,send)
        assertEquals(listOf(Event(90,100,100,true),Event(90,100,300,false)),events)
    }
    @Test fun aCompletedPressStartsANewDownTime(){
        val keys=HeldSystemMediaKeys()
        keys.transition(89,true,100,send);keys.transition(89,false,200,send)
        keys.transition(89,true,300,send);keys.transition(89,false,400,send)
        assertEquals(Event(89,300,400,false),events.last())
        keys.close(500,send);assertEquals(4,events.size)
    }
    @Test fun failedReleaseFollowedByANewPressDoesNotLeaveAPhantomUser(){
        val keys=HeldSystemMediaKeys()
        keys.transition(90,true,100,send)
        assertFalse(keys.transition(90,false,200){_,_,_,_->false})
        keys.transition(90,true,300,send);keys.transition(90,false,400,send)
        keys.close(500,send)
        assertEquals(listOf(Event(90,100,100,true),Event(90,100,400,false)),events)
    }
    @Test fun unchangedHidReportsDoNotSynthesizeRepeats(){
        val decoder=io.github.iamr0s.carvex.carplay.core.HidKeyState()
        val keys=HeldSystemMediaKeys()
        var at=100L
        val dispatch:(String,Int,Boolean)->Boolean={_,_,down->keys.transition(90,down,at,send)}
        decoder.dispatch("car","media",setOf(0xb3),dispatch)
        at=200;decoder.dispatch("car","media",setOf(0xb3),dispatch)
        at=300;decoder.dispatch("car","media",setOf(0xb3),dispatch)
        at=400;decoder.dispatch("car","media",emptySet(),dispatch)
        assertEquals(listOf(Event(90,100,100,true),Event(90,100,400,false)),events)
    }
    @Test fun oneFailingCleanupDoesNotPreventOtherReleases(){
        val keys=HeldSystemMediaKeys()
        keys.transition(90,true,100,send);keys.transition(89,true,110,send)
        keys.close(600){code,started,at,down->
            if(code==90)throw IllegalStateException("dispatch failed")
            send(code,started,at,down)
        }
        assertEquals(Event(89,110,600,false),events.last())
    }
}

package io.github.iamr0s.carvex.carplay.core

import org.junit.Assert.assertEquals
import org.junit.Assert.assertFalse
import org.junit.Assert.assertTrue
import org.junit.Test

class PhoneSubscriptionsTest {
    private val phoneSubscriptions = PhoneSubscriptions()
    private fun fields(vararg pairs: Pair<Int, ByteArray>) = IapFields(pairs.toList())

    @Test fun emptySubscriptionAppliesTheDefaultFieldSet(){
        assertTrue(phoneSubscriptions.startCallStateUpdates(fields()))
        assertEquals(setOf(0, 1, 2, 3, 4), phoneSubscriptions.callStateFields)
        assertTrue(phoneSubscriptions.callStateDefaultSet)
        assertTrue(phoneSubscriptions.callStateActive)
    }

    @Test fun onlyParamFiveAlsoKeepsTheDefaultSet(){
        assertTrue(phoneSubscriptions.startCallStateUpdates(fields(5 to ByteArray(0))))
        // 固件先把 id 本身加进集合，再追加默认集 0..4，所以 id 5 也在集合里。
        assertEquals(setOf(0, 1, 2, 3, 4, 5), phoneSubscriptions.callStateFields)
        assertTrue(phoneSubscriptions.callStateDefaultSet)
        assertTrue(phoneSubscriptions.sawParam5)
    }

    @Test fun explicitListReplacesTheDefaultSet(){
        assertTrue(phoneSubscriptions.startCallStateUpdates(fields(6 to ByteArray(0), 7 to ByteArray(0))))
        assertEquals(setOf(6, 7), phoneSubscriptions.callStateFields)
        assertFalse(phoneSubscriptions.callStateDefaultSet)
    }

    @Test fun nonEmptyPayloadFailsTheWholeSubscription(){
        assertFalse(phoneSubscriptions.startCallStateUpdates(fields(1 to byteArrayOf(9))))
        assertFalse(phoneSubscriptions.callStateActive)
    }

    @Test fun unknownIdsAreIgnoredAndStopClearsState(){
        assertTrue(phoneSubscriptions.startCallStateUpdates(fields(0x0d to ByteArray(0), 2 to ByteArray(0))))
        assertEquals(setOf(2), phoneSubscriptions.callStateFields)
        phoneSubscriptions.stopCallStateUpdates()
        assertFalse(phoneSubscriptions.callStateActive)
        assertEquals(emptySet<Int>(), phoneSubscriptions.callStateFields)
    }

    @Test fun communicationSubscriptionUsesTheSameShape(){
        assertTrue(phoneSubscriptions.startCommunicationUpdates(fields(0 to ByteArray(0), 3 to ByteArray(0))))
        assertEquals(setOf(0, 3), phoneSubscriptions.communicationFields)
        phoneSubscriptions.stopCommunicationUpdates()
        assertFalse(phoneSubscriptions.communicationActive)
    }

    @Test fun explicitCallStateUpdateOnlyEmitsSubscribedFieldsAndPreservesPlatformValues(){
        assertTrue(phoneSubscriptions.startCallStateUpdates(fields(0 to ByteArray(0), 1 to ByteArray(0),
            2 to ByteArray(0), 3 to ByteArray(0), 4 to ByteArray(0), 6 to ByteArray(0))))
        val out = phoneSubscriptions.callStateUpdate(setOf(0, 1, 2, 3, 4, 6),
            PhoneSubscriptions.CallState(remoteId = "+1", displayName = "Bob", status = 1, direction = 2,
                callUuid = "uuid", addressBookId = "ab"))
        assertEquals(listOf(0, 1, 2, 3, 4, 6), out.map { it.first })
        assertEquals(1, out.first { it.first == 2 }.second[0].toInt())
        assertEquals(2, out.first { it.first == 3 }.second[0].toInt())
        // 0x0a 只在会议通话时出现。
        assertFalse(out.any { it.first == 0x0a })
    }

    @Test fun communicationUpdateUsesDefaultValues(){
        assertTrue(phoneSubscriptions.startCommunicationUpdates(fields(0 to ByteArray(0), 4 to ByteArray(0), 5 to ByteArray(0))))
        val out = phoneSubscriptions.communicationUpdate(setOf(0, 4, 5), PhoneSubscriptions.Communications())
        assertEquals(listOf(0, 4, 5), out.map { it.first })
        assertEquals(0, out.first { it.first == 0 }.second[0].toInt())
        assertEquals(0, out.first { it.first == 5 }.second[0].toInt())
        assertEquals(0, out.first { it.first == 4 }.second.last().toInt())
    }

    @Test fun callerSelectionCannotBypassTheCurrentInstanceSubscription(){
        phoneSubscriptions.startCallStateUpdates(fields(2 to byteArrayOf()))
        val out=phoneSubscriptions.callStateUpdate(setOf(0, 1, 2, 4),
            PhoneSubscriptions.CallState(remoteId="private",displayName="private",status=4,callUuid="id"))
        assertEquals(listOf(2),out.map{it.first})
        val another=PhoneSubscriptions()
        assertTrue(another.callStateUpdate(setOf(2),PhoneSubscriptions.CallState(status=4)).isEmpty())
        phoneSubscriptions.stopCallStateUpdates()
        assertTrue(phoneSubscriptions.callStateUpdate(setOf(2),PhoneSubscriptions.CallState(status=4)).isEmpty())
    }

    @Test fun defaultAndExplicitFieldModesUseTheirOwnStatusAndDirectionBranches(){
        val expectedLegacy=listOf(0,3,3,1,1,2,1)
        for(status in 0..6){
            phoneSubscriptions.startCallStateUpdates(fields())
            val legacy=phoneSubscriptions.callStateUpdate(setOf(2,3),
                PhoneSubscriptions.CallState(status=status,direction=2))
            assertEquals(expectedLegacy[status],legacy.first{it.first==2}.second[0].toInt())
            assertEquals(1,legacy.first{it.first==3}.second[0].toInt())
            phoneSubscriptions.startCallStateUpdates(fields(0 to byteArrayOf(),1 to byteArrayOf(),
                2 to byteArrayOf(),3 to byteArrayOf(),4 to byteArrayOf(),11 to byteArrayOf()))
            val explicit=phoneSubscriptions.callStateUpdate(setOf(2,3),
                PhoneSubscriptions.CallState(status=status,direction=2))
            assertEquals(status,explicit.first{it.first==2}.second[0].toInt())
            assertEquals(2,explicit.first{it.first==3}.second[0].toInt())
        }
    }

    @Test fun conferenceFlagIsNotDerivedFromCallDirection(){
        phoneSubscriptions.startCallStateUpdates(fields(9 to byteArrayOf()))
        for(conferenced in listOf(false,true)){
            val out=phoneSubscriptions.callStateUpdate(setOf(9),
                PhoneSubscriptions.CallState(direction=2,callUuid="id",conferenced=conferenced))
            assertEquals(if(conferenced)1 else 0,out.single().second[0].toInt())
        }
    }
}

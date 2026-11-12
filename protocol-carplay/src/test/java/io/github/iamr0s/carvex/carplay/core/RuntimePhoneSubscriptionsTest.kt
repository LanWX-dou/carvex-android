package io.github.iamr0s.carvex.carplay.core

import org.junit.Assert.*
import org.junit.Test

class RuntimePhoneSubscriptionsTest {
    private val sends = setOf(0x4154, 0x4156, 0x4157, 0x4159)
    private val receives = setOf(0x4155, 0x4158)
    private fun fields(vararg ids:Int) = IapFields(ids.map { it to byteArrayOf() })

    @Test fun runtimeAndBootstrapSubscriptionsCannotAuthorizeEachOther() {
        val bootstrap = PhoneSubscriptions()
        val first = RuntimePhoneSubscriptions()
        val second = RuntimePhoneSubscriptions()
        bootstrap.startCallStateUpdates(fields())
        assertFalse(first.command(0x4154, fields(2)))
        first.linkReady(true, sends, receives);second.linkReady(true, sends, receives)
        assertFalse(first.callActive);assertFalse(second.callActive)
        assertTrue(first.command(0x4154, fields(0, 1, 2, 4, 11)))
        assertEquals(setOf(0, 1, 2, 4, 11), first.callFields)
        assertFalse(second.callActive)
        assertTrue(second.command(0x4157, fields(4, 5)))
        assertFalse(first.communicationActive);assertTrue(second.communicationActive)
        first.command(0x4156, fields())
        assertFalse(first.callActive);assertTrue(bootstrap.callStateActive)
        assertTrue(second.communicationActive)
    }

    @Test fun capabilityGroupsAreCheckedIndependentlyOnTheCurrentLink() {
        val peer = RuntimePhoneSubscriptions()
        for(missing in listOf(0x4154, 0x4155)) {
            peer.linkReady(true, sends - missing, receives - missing)
            assertFalse(peer.command(0x4154, fields(2)))
            assertFalse(peer.callActive)
            assertTrue(peer.command(0x4157, fields(4)))
        }
        for(missing in listOf(0x4157, 0x4158)) {
            peer.linkReady(true, sends - missing, receives - missing)
            assertFalse(peer.command(0x4157, fields(4)))
            assertFalse(peer.communicationActive)
            assertTrue(peer.command(0x4154, fields(2)))
        }
        peer.linkReady(false, sends, receives)
        assertFalse(peer.command(0x4154, fields()))
    }

    @Test fun optionalStopDoesNotBlockStartAndUndeclaredCommandsCannotMutateState() {
        val peer=RuntimePhoneSubscriptions()
        peer.linkReady(true,setOf(0x4154,0x4157),receives)
        assertTrue(peer.command(0x4154,fields(2)))
        assertTrue(peer.command(0x4157,fields(4)))
        assertFalse(peer.command(0x4156,fields()));assertTrue(peer.callActive)
        assertFalse(peer.command(0x4159,fields()));assertTrue(peer.communicationActive)
    }

    @Test fun invalidReplacementIsAtomicAndStopDoesNotAffectTheOtherGroup() {
        val peer = RuntimePhoneSubscriptions()
        peer.linkReady(true, sends, receives)
        assertTrue(peer.command(0x4154, fields(2, 4)))
        assertTrue(peer.command(0x4157, fields(4, 5)))
        assertFalse(peer.command(0x4154, IapFields(listOf(1 to byteArrayOf(1)))))
        assertEquals(setOf(2, 4), peer.callFields);assertTrue(peer.callActive)
        assertFalse(peer.command(0x4157, IapFields(listOf(0 to byteArrayOf(1)))))
        assertEquals(setOf(4, 5), peer.communicationFields)
        peer.command(0x4159, fields())
        assertFalse(peer.communicationActive);assertTrue(peer.callActive)
        peer.command(0x4156, fields())
        assertFalse(peer.callActive)
    }

    @Test fun newLinkRequiresNewStartAndDoesNotManufactureCallMetadata() {
        val logs = mutableListOf<String>()
        val peer = RuntimePhoneSubscriptions(logs::add)
        peer.linkReady(true, sends, receives)
        assertTrue(peer.command(0x4154, fields()))
        assertEquals(setOf(0, 1, 2, 3, 4), peer.callFields)
        assertTrue(logs.any { it.contains("accepted=true") })
        assertTrue(logs.any { it.contains("id=4155") && it.contains("reason=no-runtime-call-metadata-provider") })
        peer.linkReady(false)
        peer.linkReady(true, sends, receives)
        assertFalse(peer.callActive);assertTrue(peer.callFields.isEmpty())
        assertFalse(peer.communicationActive);assertTrue(peer.communicationFields.isEmpty())
    }
}

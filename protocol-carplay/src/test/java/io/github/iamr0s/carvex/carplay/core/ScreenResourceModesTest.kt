package io.github.iamr0s.carvex.carplay.core
import org.junit.Assert.*
import org.junit.Test
import java.io.ByteArrayInputStream
import java.io.ByteArrayOutputStream

class ScreenResourceModesTest {
    @Test fun failedAnnouncementRestoresExactAudioSnapshotAndKeepsScreenChanges(){
        val modes=ScreenResourceModes()
        modes.audio(true)
        modes.commit(requireNotNull(modes.propose(batch(2 to 3))))
        val before=modes.state
        val change=modes.audio(false)
        modes.commit(requireNotNull(modes.propose(batch(1 to 1))))
        modes.rollbackAudio(change)
        assertEquals(before.copy(owner=2,permanent=2),modes.state)
    }
    @Test fun failedAnnouncementCannotUndoNewAudioDeclarationEvenWithSameValues(){
        val modes=ScreenResourceModes()
        val change=modes.audio(true)
        modes.commit(modes.state,audioDeclared=true)
        modes.rollbackAudio(change)
        assertEquals(1,modes.state.audioOwner)
        assertEquals(1,modes.state.audioPermanent)
    }
    private fun batch(vararg entries:Pair<Int,Int>)=mapOf("resources" to entries.map{
        mapOf("resourceID" to it.first,"transferType" to it.second)
    })
    @Test fun combinedResourcesAreProposedWithoutPartialCommit(){
        for(request in listOf(batch(1 to 1,2 to 2),batch(2 to 2,1 to 1))){
            val modes=ScreenResourceModes()
            val decoded=Plist.dictionary(Plist.encode(request))
            assertEquals(setOf(1,2),modes.requestedResources(decoded))
            val next=requireNotNull(modes.propose(decoded))
            assertEquals(ScreenResourceModes.State(),modes.state)
            modes.commit(next)
            assertEquals(2,modes.state.owner)
            assertEquals(1,modes.state.audioOwner)
        }
    }
    @Test fun invalidSecondResourceCannotApplyFirst(){
        val modes=ScreenResourceModes()
        for(request in listOf(batch(1 to 1,2 to 99),batch(2 to 2,1 to 4),
            batch(1 to 1,1 to 2),batch(2 to 2,3 to 1),batch())){
            assertNull(modes.propose(request))
            assertEquals(ScreenResourceModes.State(),modes.state)
        }
    }
    @Test fun combinedBorrowAndReturnPreserveBothPermanentOwners(){
        val modes=ScreenResourceModes()
        modes.audio(true)
        modes.commit(requireNotNull(modes.propose(batch(1 to 3,2 to 3))))
        assertEquals(ScreenResourceModes.State(2,1,true,2,1,true),modes.state)
        modes.commit(requireNotNull(modes.propose(batch(2 to 4,1 to 4))))
        assertEquals(ScreenResourceModes.State(audioOwner=1,audioPermanent=1),modes.state)
    }
    private fun request(type:Int,extra:Map<String,Any?> = emptyMap())=mapOf("resources" to listOf(mapOf("resourceID" to 1,"transferType" to type)+extra))
    @Test fun borrowedScreenRetainsPermanentOwnerAndRestores(){
        val m=ScreenResourceModes()
        m.commit(requireNotNull(m.propose(request(3))))
        assertEquals(ScreenResourceModes.State(2,1,true),m.state)
        assertNull(m.propose(request(3)))
        m.commit(requireNotNull(m.propose(request(4))))
        assertEquals(ScreenResourceModes.State(),m.state)
        m.commit(requireNotNull(m.propose(request(1))))
        assertEquals(ScreenResourceModes.State(2,2),m.state)
        m.commit(requireNotNull(m.propose(request(2))))
        assertEquals(ScreenResourceModes.State(),m.state)
    }
    @Test fun unrecoveredConditionsAndOtherResourcesDoNotMutateState(){
        val m=ScreenResourceModes()
        for(key in listOf("transferPriority","takeConstraint","borrowConstraint","unborrowConstraint","borrowID"))
            assertNull(m.propose(request(1,mapOf(key to 1))))
        assertNotNull(m.propose(mapOf("resources" to listOf(mapOf("resourceID" to 2,"transferType" to 1)))))
        assertNull(m.propose(request(1)+mapOf("appStates" to listOf(mapOf("appStateID" to 1,"state" to 1)))))
        assertNull(m.propose(mapOf("resources" to listOf(mapOf("resourceID" to 1,"transferType" to 1.5)))))
        assertEquals(ScreenResourceModes.State(),m.state)
    }
    @Test fun postReplyHookRunsAfterEventResponseWasWritten(){
        val inbound=ByteArrayOutputStream()
        RtspWire.write(inbound,"POST /command RTSP/1.0",mapOf("CSeq" to "9"),Plist.encode(mapOf("type" to "changeModes")))
        RtspWire.write(inbound,"RTSP/1.0 200 OK",mapOf("CSeq" to "1"))
        val outbound=ByteArrayOutputStream()
        val client=RtspClient(ByteArrayInputStream(inbound.toByteArray()),outbound){200 to Plist.encode(mapOf("status" to 0))}
        var called=false
        client.afterEventReply={_,_,_->
            val written=ByteArrayInputStream(outbound.toByteArray())
            assertEquals("POST /feedback RTSP/1.0",RtspWire.read(written).first)
            val reply=RtspWire.read(written)
            assertEquals(200,reply.status);assertEquals("9",reply.headers["cseq"])
            called=true
        }
        client.request("POST","/feedback")
        assertTrue(called)
    }
}

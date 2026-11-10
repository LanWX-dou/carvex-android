package io.github.iamr0s.carvex.carplay.core

import org.junit.Assert.*
import org.junit.Test

class ResourceModeNotificationTest {
    @Test fun acceptedBinaryReplyRetainsTheWholeCommittedState(){
        val modes=ScreenResourceModes()
        val request=mapOf("resources" to listOf(
            mapOf("resourceID" to 1,"transferType" to 1),
            mapOf("resourceID" to 2,"transferType" to 2)))
        modes.commit(requireNotNull(modes.propose(request)),audioDeclared=true)
        val reply=Plist.dictionary(Plist.encode(mapOf("status" to 0,"params" to modes.params())))
        val notification=requireNotNull(ResourceModeNotification.fromReply(reply))
        assertEquals("modesChanged",notification["type"])
        assertEquals(reply["params"],notification["params"])
    }
    @Test fun deniedReplyDoesNotPublishAMissingState(){
        assertNull(ResourceModeNotification.fromReply(Plist.dictionary(Plist.encode(mapOf("status" to 1)))))
    }
    @Test fun deniedReplyCannotPublishEvenWhenParamsExist(){
        assertNull(ResourceModeNotification.fromReply(mapOf("status" to 1,"params" to ScreenResourceModes().params())))
    }
    @Test fun missingOrMalformedStatusCannotPublish(){
        for(status in listOf(null,"0",true,Double.NaN,0.5,-1))
            assertNull(ResourceModeNotification.fromReply(mapOf("status" to status,"params" to ScreenResourceModes().params())))
    }
    @Test fun acceptedReplyWithoutAStateCannotPublish(){
        for(params in listOf(null,0,"state",emptyList<Any>()))
            assertNull(ResourceModeNotification.fromReply(mapOf("status" to 0,"params" to params)))
    }
}

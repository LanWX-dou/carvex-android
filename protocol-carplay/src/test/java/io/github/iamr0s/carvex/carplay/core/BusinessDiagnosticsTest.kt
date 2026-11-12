package io.github.iamr0s.carvex.carplay.core

import org.junit.Assert.*
import org.junit.Test

class BusinessDiagnosticsTest {
    @Test fun lyricsAndRoadsRemainInTheirOwnMessageAndFieldWithUnchangedWireBytes() {
        val music=NowPlayingUpdate.fields(NowPlayingUpdate.Track(title="歌词一行",artist="歌名-歌手",status=NowPlayingUpdate.PlaybackStatus.PAUSED))
        val before=IapWire.csm(0x5001,music)
        val lines=BusinessDiagnostics.fields(0x5001,"tx",music,"source=runtime tx=9")
        assertTrue(lines.any{it.contains("field=0.1")&&it.contains("歌词一行")})
        assertTrue(lines.any{it.contains("field=1.0")&&it.contains("PAUSED")})
        assertTrue(lines.all{it.startsWith("debug music ")&&it.contains("tx=9")})
        assertArrayEquals(before,IapWire.csm(0x5001,music))
        val route=NavigationGuidance.route(NavigationGuidance.RouteUpdate(listOf(42),currentRoad="中山路",distanceRemaining=334),0)
        val nav=BusinessDiagnostics.fields(0x5201,"tx",route)
        assertTrue(nav.any{it.contains("name=currentRoad")&&it.contains("中山路")})
        assertTrue(nav.any{it.contains("name=distanceRemaining")&&it.contains("value=334")})
        assertFalse(nav.any{it.contains("歌词")||it.startsWith("debug music ")})
    }

    @Test fun subscriptionMarkersAreNotMisreadAsMissingTextAndMalformedGroupsCannotThrow() {
        val selected=listOf(0 to IapWire.fields(listOf(1 to byteArrayOf())),1 to IapWire.fields(listOf(0x11 to IapWire.be32(8))))
        val lines=BusinessDiagnostics.fields(0x5000,"rx",selected)
        assertTrue(lines.any{it.contains("name=title value=marker bytes=0")})
        assertTrue(lines.any{it.contains("name=queueStart value=8")})
        assertTrue(BusinessDiagnostics.fields(0x5001,"rx",listOf(0 to byteArrayOf(1))).any{it.contains("malformed-group")})
        assertTrue(BusinessDiagnostics.fields(0x5703,"rx",listOf(2 to IapWire.cstring("credential"))).isEmpty())
    }

    @Test fun callIdentityIsRedactedWhileCallStateRemainsVisible() {
        val lines=BusinessDiagnostics.fields(0x4155,"tx",listOf(
            0 to IapWire.cstring("15551234567"),1 to IapWire.cstring("ContactName"),
            2 to byteArrayOf(3),4 to IapWire.cstring("call-private-id")))
        assertFalse(lines.any{it.contains("15551234567")||it.contains("ContactName")||it.contains("call-private-id")})
        assertTrue(lines.any{it.contains("field=2")&&it.contains("value=3")})
        assertEquals(3,lines.count{it.contains("redacted")})
    }

    @Test fun repeatedComponentsAndUnsignedDistancesRemainVisible() {
        val lines=BusinessDiagnostics.fields(0x5201,"tx",listOf(0 to IapWire.be16(42),0 to IapWire.be16(43),7 to IapWire.be32(0xffffffffL)))
        assertEquals(2,lines.count{it.contains("field=0")})
        assertTrue(lines.any{it.contains("value=4294967295")})
    }

    @Test fun excessiveNestedFieldsAreBoundedAndExplicitlyReported() {
        val group=IapWire.fields((0 until 100).map{it to byteArrayOf(1)})
        val fields=(0 until 100).map{it to group}
        val before=IapWire.csm(0x5001,fields)
        val lines=BusinessDiagnostics.fields(0x5001,"rx",fields)
        assertTrue(lines.size<=194)
        assertEquals(128,lines.count{it.contains(" name=")})
        assertTrue(lines.any{it.contains("field=0.truncated")&&it.contains("remaining=36")})
        assertTrue(lines.any{it.contains("field=truncated remaining=36")})
        assertArrayEquals(before,IapWire.csm(0x5001,fields))
        val unknown=BusinessDiagnostics.fields(0x4158,"rx",listOf(99 to byteArrayOf(42)))
        assertTrue(unknown.any{it.contains("redacted bytes=1")})
    }

    @Test fun loggingSubscriptionAndCacheFailuresDoesNotInventMessagesOrLoseTheRoute() {
        val messages=mutableListOf<Int>();val logs=mutableListOf<String>()
        var snapshot:io.github.iamr0s.carvex.protocol.api.NavigationSnapshot?=
            io.github.iamr0s.carvex.protocol.api.NavigationSnapshot("test",1,1,1,
                io.github.iamr0s.carvex.protocol.api.NavigationLifecycle.ACTIVE)
        val publisher=NavigationPublisher({id,_,_,_->messages.add(id);true},logs::add)
        publisher.attachNavigation{snapshot}
        assertFalse(publisher.navigationChanged())
        assertTrue(logs.any{it.contains("reason=no-subscription")})
        publisher.linkReady(true,setOf(0x5200,0x5203),setOf(0x5201,0x5202))
        publisher.command(0x5200,IapFields(listOf(0 to IapWire.be16(42))))
        assertTrue(messages.isEmpty()) // Unverified wire states cannot be manufactured by diagnostics.
        snapshot=null
        publisher.navigationChanged()
        publisher.command(0x5200,IapFields(listOf(0 to IapWire.be16(43))))
        assertTrue(messages.isEmpty())
        assertTrue(logs.any{it.contains("reason=host-lifecycle-unverified")})
        assertTrue(logs.any{it.contains("reason=no-snapshot")})
    }
}

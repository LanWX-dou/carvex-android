package io.github.iamr0s.carvex.carplay.core

import org.junit.Assert.*
import org.junit.Test

class NavigationPublisherTest {
    private val sends=setOf(0x5200,0x5203)
    private val receives=setOf(0x5201,0x5202)
    private fun start(component:Int)=IapFields(listOf(0 to IapWire.be16(component)))
    private fun sample()=NavigationGuidance.RouteUpdate(emptyList(),currentRoad="Road",distanceRemaining=200)

    @Test fun cachesBeforeStartAndUsesRuntimeComponentsInsteadOfBootstrapGlobals() {
        NavigationGuidance.start(start(99))
        val packets=mutableListOf<Pair<Int,List<Pair<Int,ByteArray>>>>()
        val p=NavigationPublisher({id,fields->packets.add(id to fields);true})
        assertFalse(p.update(sample()))
        assertFalse(p.command(0x5200,start(42)))
        p.linkReady(true,sends,receives)
        assertTrue(p.command(0x5200,start(42)))
        assertEquals(1,packets.size)
        assertEquals(0x5201,packets.single().first)
        assertArrayEquals(IapWire.be16(42),packets.single().second.first().second)
        assertEquals(listOf(0,3,7),packets.single().second.map{it.first})
    }

    @Test fun stopBlocksAllNavigationAndReconnectRequiresNewStart() {
        val sent=mutableListOf<Int>()
        val p=NavigationPublisher({id,_->sent.add(id);true})
        p.linkReady(true,sends,receives+0x5204)
        p.command(0x5200,start(42))
        assertTrue(p.update(sample()))
        assertTrue(p.command(0x5203,IapFields(emptyList())))
        assertFalse(p.update(sample()))
        assertFalse(p.send(0x5202,listOf(1 to IapWire.be16(0))))
        assertFalse(p.send(0x5204,listOf(1 to IapWire.be16(0))))
        assertEquals(1,sent.size)
        p.linkReady(false)
        p.linkReady(true,sends,receives)
        assertFalse(p.update(sample()))
        p.command(0x5200,start(43))
        assertEquals(2,sent.size)
    }

    @Test fun malformedCommandsPreserveActiveSubscription() {
        val packets=mutableListOf<List<Pair<Int,ByteArray>>>()
        val p=NavigationPublisher({_,fields->packets.add(fields);true})
        p.linkReady(true,sends,receives)
        p.command(0x5200,start(42))
        assertFalse(p.command(0x5200,IapFields(listOf(1 to byteArrayOf(1)))))
        assertFalse(p.command(0x5203,IapFields(listOf(0 to byteArrayOf(1)))))
        assertTrue(p.update(sample()))
        assertArrayEquals(IapWire.be16(42),packets.single().first().second)
    }

    @Test fun capabilitiesAreRequiredAndLaneSupportIsOptional() {
        val p=NavigationPublisher({_,_->true})
        p.linkReady(true,sends,setOf(0x5201))
        assertFalse(p.command(0x5200,start(42)))
        assertFalse(p.update(sample()))
        p.linkReady(true,sends,receives)
        assertTrue(p.command(0x5200,start(42)))
        assertTrue(p.send(0x5202,listOf(1 to IapWire.be16(0))))
        assertFalse(p.send(0x5204,listOf(1 to IapWire.be16(0))))
    }

    @Test fun resubscriptionReencodesOptionsAndComponents() {
        val packets=mutableListOf<List<Pair<Int,ByteArray>>>()
        val p=NavigationPublisher({_,fields->packets.add(fields);true})
        p.update(sample().copy(sourceName="Maps",timezoneOffset=60,stopType=1))
        p.linkReady(true,sends,receives)
        p.command(0x5200,start(42))
        assertFalse(packets.last().any{it.first in 19..22})
        p.command(0x5200,IapFields(start(43).ordered+listOf(1 to byteArrayOf(),4 to byteArrayOf(),5 to byteArrayOf())))
        assertArrayEquals(IapWire.be16(43),packets.last().first().second)
        assertTrue(packets.last().map{it.first}.containsAll(listOf(19,21,22)))
    }

    @Test fun separateSessionsCannotInheritSubscriptionOrCachedRoute() {
        val p=NavigationPublisher({_,_->true})
        p.linkReady(true,sends,receives)
        p.command(0x5200,start(42))
        p.update(sample())
        val packets=mutableListOf<Int>()
        val other=NavigationPublisher({id,_->packets.add(id);true})
        other.linkReady(true,sends,receives)
        other.command(0x5200,start(43))
        assertTrue(packets.isEmpty())
    }
}

package io.github.iamr0s.carvex.carplay.core

import com.shilapi.xcertplay.airplay.AirPlayContact
import com.shilapi.xcertplay.airplay.AirPlayHid
import com.shilapi.xcertplay.airplay.ReceiverAudioFormats
import com.shilapi.xcertplay.hud.BydHudRouteState
import com.shilapi.xcertplay.hud.CarPlayCallCard
import com.shilapi.xcertplay.hud.CarPlayCallState
import com.shilapi.xcertplay.iap2.message.Iap2ControlMessages
import com.shilapi.xcertplay.iap2.wire.Iap2CsmFramer
import com.shilapi.xcertplay.iap2.wire.Iap2Frame
import com.shilapi.xcertplay.media.CarPlayPlaybackStatus
import io.github.iamr0s.carvex.carplay.HidKeyRegistry
import io.github.iamr0s.carvex.protocol.api.*
import io.github.iamr0s.carvex.sessioncore.RawParameter
import io.github.iamr0s.carvex.pcm.PcmFormat
import org.junit.Assert.*
import org.junit.Test

/** Optional tests: every com.shilapi receiver class comes from the supplied source. */
class ReceiverProtocolContractTest {
    private fun frame(id: Int, fields: List<Pair<Int, ByteArray>>) =
        Iap2CsmFramer().offer(IapWire.csm(id, fields)).single()
    private val selection = NavigationGuidance.Start(listOf(42), 3)
    private fun display(capacity: Int = 8) = NavigationDisplayCapabilities(listOf(RawParameter(30,
        IapWire.fields(listOf(0 to IapWire.be16(42), 6 to IapWire.be16(capacity))))))
    private fun snapshot(generation: Long = 1, turn: NavigationTurn? = NavigationTurn.RIGHT,
                         distance: Long? = 200) = NavigationSnapshot("xiaomi", 1, 1, generation,
        NavigationLifecycle.ACTIVE, maneuver = NavigationManeuver("hint-$generation",
            distanceMeters = distance, turn = turn), maneuverGeneration = generation,
        evidence = mapOf("lifecycle" to "H01:16fc3c", "maneuver" to "H01:HUD-maneuver"))
    private fun deliver(receiver: BydHudRouteState, plan: NavigationPlan) {
        assertNull(plan.blocked)
        plan.packets.forEach { packet ->
            val parsed = frame(packet.id, packet.fields)
            receiver.accept(parsed.messageId, parsed.payload)
        }
    }

    @Test fun sourceSubscriptionsSelectTheActualRequestedFields() {
        val requests = Iap2ControlMessages.subscriptions().associateBy { it.messageId }
        val music = NowPlayingUpdate.selection(
            IapWire.parseFieldList(requests.getValue(0x5000).payload))!!
        assertEquals(setOf(1, 4, 6, 12, 26), music.attributes.filter { it.group == 0 }.map { it.id }.toSet())
        assertEquals(setOf(0, 1, 7), music.attributes.filter { it.group == 1 }.map { it.id }.toSet())
        assertEquals(selection, NavigationGuidance.parseStart(
            IapWire.parseFieldList(requests.getValue(0x5200).payload)))
        val phone = PhoneSubscriptions()
        assertTrue(phone.startCallStateUpdates(IapWire.parseFieldList(requests.getValue(0x4154).payload)))
        assertEquals(setOf(0, 1, 2, 3, 4, 11), phone.callStateFields)
        assertFalse(phone.callStateDefaultSet)
    }

    @Test fun senderCsmSurvivesReceiverFragmentation() {
        val wire = IapWire.csm(0x5201, listOf(1 to byteArrayOf(1), 10 to IapWire.be32(200)))
        for (size in 1..wire.size) {
            val reader = Iap2CsmFramer()
            val frames = wire.asList().chunked(size).flatMap { reader.offer(it.toByteArray()) }
            assertEquals(1, frames.size)
            assertEquals(0x5201, frames.single().messageId)
            assertArrayEquals(wire.copyOfRange(6, wire.size), frames.single().payload)
        }
    }

    @Test fun everyVerifiedTurnDecodesToTheExpectedReceiverArrow() {
        for ((turn, type) in mapOf(NavigationTurn.LEFT to 1, NavigationTurn.RIGHT to 2,
            NavigationTurn.STRAIGHT to 3, NavigationTurn.U_TURN to 4,
            NavigationTurn.SHARP_LEFT to 47, NavigationTurn.SHARP_RIGHT to 48,
            NavigationTurn.SLIGHT_LEFT to 49, NavigationTurn.SLIGHT_RIGHT to 50)) {
            val receiver = BydHudRouteState()
            deliver(receiver, NavigationWireEncoding.plan(snapshot(turn = turn), selection, display()))
            assertEquals(type, receiver.currentApple()!!.type)
            assertEquals(200, receiver.currentApple()!!.distanceMeters)
        }
    }

    @Test fun distanceUpdatesAndUnknownValuesCannotLeaveStaleGuidance() {
        val receiver = BydHudRouteState()
        deliver(receiver, NavigationWireEncoding.plan(snapshot(), selection, display()))
        deliver(receiver, NavigationWireEncoding.plan(snapshot(distance = 80), selection, display()))
        assertEquals(80, receiver.currentApple()!!.distanceMeters)
        deliver(receiver, NavigationWireEncoding.plan(snapshot(turn = null), selection, display()))
        assertNull(receiver.currentApple())
        deliver(receiver, NavigationWireEncoding.plan(snapshot(distance = null), selection, display()))
        assertEquals(0, receiver.currentApple()!!.distanceMeters)
        deliver(receiver, NavigationWireEncoding.plan(snapshot().copy(lifecycle = NavigationLifecycle.ENDED), selection, display()))
        assertNull(receiver.currentApple())
    }

    @Test fun longRouteDoesNotExceedTheReceiversManeuverStorage() {
        val receiver = BydHudRouteState()
        val indices = mutableSetOf<Int>()
        for (generation in 1L..100L) {
            val plan = NavigationWireEncoding.plan(snapshot(generation, distance = 200 - generation), selection, display())
            plan.packets.filter { it.id == 0x5202 }.forEach {
                indices += IapWire.u16(IapWire.parseFieldList(IapWire.fields(it.fields))[1]!!, 0)
            }
            deliver(receiver, plan)
            assertEquals((200 - generation).toInt(), receiver.currentApple()!!.distanceMeters)
            val cached = BydHudRouteState::class.java.getDeclaredField("maneuvers").apply { isAccessible = true }
                .get(receiver) as Map<*, *>
            assertTrue("generation=$generation cached=${cached.size}", cached.size <= 8)
        }
        assertEquals(8, indices.size)
    }

    @Test fun singleSlotResetPreventsAnOldDistanceWithTheNewArrow() {
        val receiver = BydHudRouteState()
        deliver(receiver, NavigationWireEncoding.plan(snapshot(), selection, display(1)))
        val changed = NavigationWireEncoding.plan(snapshot(2, NavigationTurn.LEFT, 50), selection, display(1))
        assertEquals(listOf(0x5201, 0x5202, 0x5201), changed.packets.map { it.id })
        changed.packets.forEachIndexed { index, packet ->
            val parsed = frame(packet.id, packet.fields)
            receiver.accept(parsed.messageId, parsed.payload)
            if (index < 2) assertNull(receiver.currentApple())
        }
        assertEquals(1, receiver.currentApple()!!.type)
        assertEquals(50, receiver.currentApple()!!.distanceMeters)
    }

    @Test fun realNowPlayingParserRetainsAndClearsIncrementalFields() {
        val receiver = CarPlayPlaybackStatus()
        val requested = NowPlayingUpdate.selection(IapWire.parseFieldList(
            Iap2ControlMessages.startNowPlayingUpdates().payload))!!
        receiver.acceptUpdate(frame(0x5001, NowPlayingUpdate.fields(NowPlayingUpdate.Track(
            title = "歌曲", artist = "歌手", album = "专辑", durationMs = 123000, elapsedMs = 456,
            appName = "Player", status = NowPlayingUpdate.PlaybackStatus.PLAYING), requested)))
        assertEquals("歌曲", receiver.nowPlaying.title)
        assertEquals("歌手", receiver.nowPlaying.artist)
        assertEquals(123000L, receiver.nowPlaying.durationMillis)
        assertEquals(456L, receiver.nowPlaying.elapsedMillis)
        assertTrue(receiver.playing)
        receiver.acceptUpdate(frame(0x5001, NowPlayingUpdate.fields(NowPlayingUpdate.Track(
            elapsedMs = 2000, status = NowPlayingUpdate.PlaybackStatus.PAUSED), requested)))
        assertEquals("歌曲", receiver.nowPlaying.title)
        assertEquals(2000L, receiver.nowPlaying.elapsedMillis)
        assertFalse(receiver.playing)
        receiver.acceptUpdate(frame(0x5001, listOf(0 to IapWire.fields(listOf(26 to byteArrayOf(7))))))
        assertEquals(7, receiver.nowPlaying.artworkTransferId)
        receiver.acceptUpdate(frame(0x5001, listOf(0 to IapWire.fields(listOf(1 to IapWire.cstring(""))))))
        assertNull(receiver.nowPlaying.title)
        assertEquals("歌手", receiver.nowPlaying.artist)
    }

    @Test fun explicitCallFieldsDriveRingingConnectedHeldAndEndCards() {
        val request = Iap2ControlMessages.subscriptions().single { it.messageId == 0x4154 }
        val sender = PhoneSubscriptions()
        sender.startCallStateUpdates(IapWire.parseFieldList(request.payload))
        val receiver = CarPlayCallState { 1234 }
        for ((status, phase) in listOf(1 to CarPlayCallCard.Phase.DIALING,
            2 to CarPlayCallCard.Phase.RINGING, 4 to CarPlayCallCard.Phase.ACTIVE,
            5 to CarPlayCallCard.Phase.ACTIVE, 0 to null)) {
            receiver.accept(frame(0x4155, sender.callStateUpdate(sender.callStateFields,
                PhoneSubscriptions.CallState(displayName = "测试", status = status, direction = 1, callUuid = "call-one"))))
            assertEquals(phase, receiver.current()?.phase)
            if (phase == CarPlayCallCard.Phase.ACTIVE) assertEquals(1234L, receiver.current()!!.activeSinceMillis)
        }
    }

    @Test fun sourceAudioOffersSelectOnlyCommonRoutesAndCaptureFormats() {
        for (rate in listOf(44100, 48000)) for (callRate in listOf(false, true)) {
            val rows = ReceiverAudioFormats.audioFormats(rate, true, callAtCallRate = callRate)
            val capabilities = AudioCapabilities.parse(rows)
            val source = PcmFormat(rate, 2)
            val media = CarPlayAudioPlan.selectPlayback(capabilities, 1, source) { true }!!
            assertEquals(CarPlayAudioPlan.media, media.route)
            assertEquals(CarPlayAudioPlan.Codec.AAC_LC, media.format.codec)
            assertEquals(rate, media.format.rate)
            val prompt = CarPlayAudioPlan.selectPlayback(capabilities, 2, source) { true }!!
            assertEquals(CarPlayAudioPlan.alternate, prompt.route)
            val microphone = CallMicrophonePlan.select(capabilities) { true }!!
            val row = rows.single { it["audioType"] == "telephony" }
            assertTrue((row["audioInputFormats"] as Number).toLong() and microphone.bit != 0L)
            if (callRate) {
                assertEquals(CarPlayAudioPlan.Codec.PCM16, microphone.codec)
                assertTrue(microphone.rate in setOf(8000, 16000, 24000, 32000))
            }
        }
        val noAudio = AudioCapabilities.parse(ReceiverAudioFormats.audioFormats(48000, false))
        assertNull(CallMicrophonePlan.select(noAudio) { true })
        assertNull(CarPlayAudioPlan.selectPlayback(emptyList(), 2, PcmFormat(48000, 2)) { true })
    }

    @Test fun actualReceiverTouchAndTelephonyDescriptorsDecodeWithoutAliases() {
        val uuid = "screen"
        val device = AirPlayHid.touchHidDevice(1920, 1080, uuid)
        val decoder = HidTouch.parse(device["hidDescriptor"] as ByteArray)
        val down = AirPlayHid.touchReport(listOf(AirPlayContact(0, 960.0, 540.0, true)))
        assertEquals(TouchSample(true, 960f, 540f), decoder.decode(down, 1921, 1081))
        assertFalse(decoder.decode(AirPlayHid.touchReport(emptyList()), 1921, 1081).pressed)
        val telephony = AirPlayHid.telephonyHidDevice(uuid)
        val registry = HidKeyRegistry()
        registry.register(telephony["uuid"] as String, telephony["hidDescriptor"] as ByteArray)
        val decoded = mutableListOf<Triple<String, Int, Boolean>>()
        for (index in listOf(1, 0, 3, 0)) {
            assertTrue(registry.report(telephony["uuid"] as String, AirPlayHid.telephonyReport(index),
                null, 1, 1, { false }, { page, usage, pressed -> decoded += Triple(page, usage, pressed); true }).accepted)
        }
        assertEquals(listOf(Triple("pageb", 0x20, true), Triple("pageb", 0x20, false),
            Triple("pageb", 0x26, true), Triple("pageb", 0x26, false)), decoded)
    }
}

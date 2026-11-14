package io.github.iamr0s.carvex.carplay.core

import com.shilapi.xcertplay.airplay.AirPlayContact
import com.shilapi.xcertplay.airplay.AirPlayHid
import com.shilapi.xcertplay.airplay.ReceiverAudioFormats
import com.shilapi.xcertplay.hud.BydHudRouteState
import com.shilapi.xcertplay.hud.CarPlayCallCard
import com.shilapi.xcertplay.hud.CarPlayCallState
import com.shilapi.xcertplay.iap2.message.Iap2ControlMessages
import com.shilapi.xcertplay.iap2.message.Iap2LaneGuidance
import com.shilapi.xcertplay.iap2.wire.Iap2CsmFramer
import com.shilapi.xcertplay.iap2.wire.Iap2Frame
import com.shilapi.xcertplay.media.CarPlayPlaybackStatus
import com.shilapi.xcertplay.transport.Iap2FileTransferReceiver
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
                         distance: Long? = 200, remaining: Long? = null,
                         routeEvidence: String? = "fixture:verified-route") = NavigationSnapshot("xiaomi", 1, 1, generation,
        NavigationLifecycle.ACTIVE, route = NavigationRoute(distanceRemainingMeters = remaining),
        maneuver = NavigationManeuver("hint-$generation",
            distanceMeters = distance, turn = turn), maneuverGeneration = generation,
        evidence = mapOf("lifecycle" to "H01:16fc3c", "maneuver" to "H01:HUD-maneuver") +
            listOfNotNull(routeEvidence?.takeIf { remaining != null }?.let { "distanceRemainingMeters" to it }).toMap())
    private fun deliver(receiver: BydHudRouteState, plan: NavigationPlan) {
        assertNull(plan.blocked)
        plan.packets.forEach { packet ->
            val parsed = frame(packet.id, packet.fields)
            receiver.accept(parsed.messageId, parsed.payload)
        }
    }

    @Test fun replacingMusicClearsReceiverTextWithoutInventingUnknownNumbers() {
        val receiver=CarPlayPlaybackStatus()
        val packets=mutableListOf<List<Pair<Int,ByteArray>>>()
        val publisher=NowPlayingPublisher { fields->
            packets+=fields
            receiver.acceptUpdate(frame(0x5001,fields))
            true
        }
        val start=Iap2ControlMessages.subscriptions().single{it.messageId==0x5000}
        publisher.linkReady(true)
        assertTrue(publisher.command(0x5000,IapWire.parseFieldList(start.payload)))
        assertTrue(publisher.update(NowPlayingUpdate.Track(title="旧歌",artist="旧歌手",album="旧专辑",durationMs=12000),true))
        publisher.update(NowPlayingUpdate.Track(elapsedMs=50))
        assertEquals("旧专辑",receiver.nowPlaying.album)
        assertTrue(publisher.update(NowPlayingUpdate.Track(title="新歌"),true))
        assertEquals("新歌",receiver.nowPlaying.title)
        assertNull(receiver.nowPlaying.artist)
        assertNull(receiver.nowPlaying.album)
        val media=IapWire.parseFieldList(packets.last().single().second)
        assertArrayEquals(byteArrayOf(0),media[6])
        assertArrayEquals(byteArrayOf(0),media[12])
        assertNull(media[4]) // No invented duration=0 in the live replacement.
        assertEquals(12000L,receiver.nowPlaying.durationMillis) // Numeric invalidation remains OPEN.
        publisher.update(NowPlayingUpdate.Track(artist="新歌手"))
        publisher.update(NowPlayingUpdate.Track(elapsedMs=0))
        assertEquals("新歌手",receiver.nowPlaying.artist)
        assertNull(receiver.nowPlaying.album)
        assertEquals(0L,receiver.nowPlaying.elapsedMillis)
    }

    @Test fun knownPlaybackStatesReachTheReceiverWithoutLosingSeekOrStop() {
        val receiver = CarPlayPlaybackStatus()
        val requested = NowPlayingUpdate.selection(IapWire.parseFieldList(
            Iap2ControlMessages.startNowPlayingUpdates().payload))!!
        for (status in NowPlayingUpdate.PlaybackStatus.entries) {
            receiver.acceptUpdate(frame(0x5001, NowPlayingUpdate.fields(
                NowPlayingUpdate.Track(status = status), requested)))
            assertEquals(status.wire, receiver.nowPlaying.rawPlaybackStatus)
            assertEquals(status.wire in listOf(1, 3, 4), receiver.playing)
        }
        receiver.acceptUpdate(frame(0x5001, listOf(1 to IapWire.fields(listOf(0 to byteArrayOf(-1))))))
        assertEquals(255, receiver.nowPlaying.rawPlaybackStatus)
        assertNull(receiver.nowPlaying.playbackState)
        assertFalse(receiver.playing)
        receiver.acceptUpdate(frame(0x5001, listOf(0 to IapWire.fields(listOf(1 to IapWire.cstring("Track"))))))
        assertEquals(255, receiver.nowPlaying.rawPlaybackStatus)
    }

    @Test fun actualFileReceiverRejectsCancelledDataAndAcceptsTheReplacementArtwork() {
        val receiver = Iap2FileTransferReceiver()
        val first = byteArrayOf(1, 2, 3, 4)
        val second = byteArrayOf(5, 6, 7)
        assertArrayEquals(byteArrayOf(-128, 1), receiver.accept(ArtworkFileWire.setup(128, first.size, 2)).replies.single())
        assertArrayEquals(first, receiver.accept(ArtworkFileWire.chunk(128, first, 0, 12)).completed!!.bytes)
        // A pending second transfer is cancelled before completion; later chunks cannot revive it.
        receiver.accept(ArtworkFileWire.setup(129, second.size, 2))
        assertEquals(0, receiver.accept(ArtworkFileWire.control(129, 2)).completed!!.bytes.size)
        assertNull(receiver.accept(ArtworkFileWire.chunk(129, second, 0, 12)).completed)
        receiver.accept(ArtworkFileWire.setup(130, second.size, 2))
        val completed = receiver.accept(ArtworkFileWire.chunk(130, second, 0, 12)).completed!!
        assertEquals(130, completed.id)
        assertArrayEquals(second, completed.bytes)
        receiver.accept(ArtworkFileWire.setup(131, second.size, 2))
        receiver.clear()
        assertNull(receiver.accept(ArtworkFileWire.chunk(131, second, 0, 12)).completed)
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

    @Test fun actualReceiverSeparatesRouteRemainderFromManeuverDistanceAndAcceptsZero() {
        val receiver = BydHudRouteState()
        for (remaining in listOf(19000L, 18000L, 0L, 0xffffffffL)) {
            deliver(receiver, NavigationWireEncoding.plan(snapshot(distance = 245, remaining = remaining), selection, display()))
            assertEquals(remaining, receiver.currentApple()!!.remainingMeters)
            assertEquals(245, receiver.currentApple()!!.distanceMeters)
            assertEquals(2, receiver.currentApple()!!.type)
        }
        deliver(receiver, NavigationWireEncoding.plan(snapshot(distance = null, remaining = 19000), selection, display()))
        assertEquals(19000L, receiver.currentApple()!!.remainingMeters)
        assertEquals(0, receiver.currentApple()!!.distanceMeters)
    }

    @Test fun actualReceiverClearsKnownRouteRemainderOnUnknownValuesNewRoutesAndEnd() {
        val receiver = BydHudRouteState()
        val unknown = listOf(snapshot(remaining = null), snapshot(remaining = -1),
            snapshot(remaining = 0x100000000L), snapshot(remaining = 19000, routeEvidence = null),
            snapshot(remaining = 19000, routeEvidence = " "), snapshot().copy(routeEpoch = 2))
        for (next in unknown) {
            deliver(receiver, NavigationWireEncoding.plan(snapshot(remaining = 19000), selection, display()))
            assertEquals(19000L, receiver.currentApple()!!.remainingMeters)
            val plan = NavigationWireEncoding.plan(next, selection, display())
            assertEquals(listOf(0x5201, 0x5202, 0x5201), plan.packets.map { it.id })
            deliver(receiver, plan)
            assertNull(receiver.currentApple()!!.remainingMeters)
            assertEquals(200, receiver.currentApple()!!.distanceMeters)
            assertEquals(2, receiver.currentApple()!!.type)
        }
        for (lifecycle in listOf(NavigationLifecycle.ENDED, NavigationLifecycle.INVALIDATED)) {
            deliver(receiver, NavigationWireEncoding.plan(snapshot(remaining = 19000), selection, display()))
            deliver(receiver, NavigationWireEncoding.plan(snapshot(remaining = 19000).copy(lifecycle = lifecycle), selection, display()))
            assertNull(receiver.currentApple())
            deliver(receiver, NavigationWireEncoding.plan(snapshot(), selection, display()))
            assertNull(receiver.currentApple()!!.remainingMeters)
        }
    }

    @Test fun longRouteDoesNotExceedTheReceiversManeuverStorage() {
        val receiver = BydHudRouteState()
        val indices = mutableSetOf<Int>()
        for (generation in 1L..100L) {
            val plan = NavigationWireEncoding.plan(snapshot(generation, distance = 200 - generation,
                remaining = 19000 - generation), selection, display())
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
        deliver(receiver, NavigationWireEncoding.plan(snapshot(remaining = 19000), selection, display(1)))
        val changed = NavigationWireEncoding.plan(snapshot(2, NavigationTurn.LEFT, 50, remaining = 18000), selection, display(1))
        assertEquals(listOf(0x5201, 0x5202, 0x5201), changed.packets.map { it.id })
        changed.packets.forEachIndexed { index, packet ->
            val parsed = frame(packet.id, packet.fields)
            receiver.accept(parsed.messageId, parsed.payload)
            if (index < 2) assertNull(receiver.currentApple())
        }
        assertEquals(1, receiver.currentApple()!!.type)
        assertEquals(50, receiver.currentApple()!!.distanceMeters)
        assertEquals(18000L, receiver.currentApple()!!.remainingMeters)
    }

    @Test fun multipleComponentsUseTheSmallestCacheAndUnsignedComponentBoundaries() {
        val selected = NavigationGuidance.Start(listOf(0, 65535), 3)
        fun capabilities(capacity: Int) = NavigationDisplayCapabilities(listOf(0, 65535).map { id ->
            RawParameter(30, IapWire.fields(listOf(0 to IapWire.be16(id),
                6 to IapWire.be16(if (id == 0) 65535 else capacity))))
        })
        val receiver = BydHudRouteState()
        for (generation in 1L..100L) {
            val plan = NavigationWireEncoding.plan(snapshot(generation, distance = 200 - generation,
                remaining = 19000 - generation), selected, capabilities(3))
            for (packet in plan.packets) {
                val fields = IapWire.parseFieldList(IapWire.fields(packet.fields))
                assertEquals(listOf(0, 65535), fields.ordered.filter { it.first == 0 }.map { IapWire.u16(it.second, 0) })
            }
            val definition = IapWire.parseFieldList(IapWire.fields(plan.packets.first().fields))
            assertEquals((generation % 3).toInt(), IapWire.u16(definition[1]!!, 0))
            deliver(receiver, plan)
            assertEquals((200 - generation).toInt(), receiver.currentApple()!!.distanceMeters)
            val cache = BydHudRouteState::class.java.getDeclaredField("maneuvers").apply { isAccessible = true }
                .get(receiver) as Map<*, *>
            assertTrue(cache.size <= 3)
        }
        for (generation in listOf(65534L, 65535L, Long.MAX_VALUE)) {
            val plan = NavigationWireEncoding.plan(snapshot(generation, remaining = 19000), selected, capabilities(65535))
            val definition = IapWire.parseFieldList(IapWire.fields(plan.packets.first().fields))
            val reference = IapWire.parseFieldList(IapWire.fields(plan.packets.last().fields))
            assertEquals((generation % 65535).toInt(), IapWire.u16(definition[1]!!, 0))
            assertArrayEquals(definition[1], reference[13])
            deliver(receiver, plan)
            assertEquals(2, receiver.currentApple()!!.type)
        }
    }

    @Test fun reroutingAndNewRoutesRebuildGuidanceWithoutInferringAnArrival() {
        val receiver = BydHudRouteState()
        deliver(receiver, NavigationWireEncoding.plan(snapshot(remaining = 19000), selection, display()))
        val rerouting = snapshot(turn = null, remaining = 18000).copy(lifecycle = NavigationLifecycle.REROUTING)
        val plan = NavigationWireEncoding.plan(rerouting, selection, display())
        assertEquals(listOf(0, 5), plan.packets.map { it.fields.single { field -> field.first == 1 }.second.single().toInt() })
        deliver(receiver, plan)
        assertNull(receiver.currentApple())
        deliver(receiver, NavigationWireEncoding.plan(snapshot(2, NavigationTurn.LEFT, 50, remaining = 18000), selection, display()))
        assertEquals(1, receiver.currentApple()!!.type)
        assertEquals(50, receiver.currentApple()!!.distanceMeters)
        val ended = NavigationWireEncoding.plan(snapshot().copy(lifecycle = NavigationLifecycle.ENDED,
            endReason = NavigationEndReason.UNKNOWN), selection, display())
        assertArrayEquals(byteArrayOf(0), ended.packets.single().fields.single { it.first == 1 }.second)
        deliver(receiver, ended)
        assertNull(receiver.currentApple())
        deliver(receiver, NavigationWireEncoding.plan(snapshot(3, NavigationTurn.RIGHT, 70).copy(routeEpoch = 2), selection, display()))
        assertEquals(70, receiver.currentApple()!!.distanceMeters)
        assertNull(receiver.currentApple()!!.remainingMeters)
    }

    @Test fun musicRouteAndOptionalLaneUpdatesRemainIndependentIncludingMalformedInputs() {
        val route = BydHudRouteState()
        val music = CarPlayPlaybackStatus()
        val requested = NowPlayingUpdate.selection(IapWire.parseFieldList(
            Iap2ControlMessages.startNowPlayingUpdates().payload))!!
        deliver(route, NavigationWireEncoding.plan(snapshot(remaining = 19000), selection, display()))
        val guidance = route.currentApple()
        for (status in NowPlayingUpdate.PlaybackStatus.entries) {
            val update = frame(0x5001, NowPlayingUpdate.fields(NowPlayingUpdate.Track(
                title = "Track", status = status), requested))
            music.acceptUpdate(update)
            route.accept(update.messageId, update.payload)
            assertEquals(guidance, route.currentApple())
        }
        val nowPlaying = music.nowPlaying
        // Synthetic lane values test only receiver-domain isolation; no lane provider is enabled.
        val lane = frame(0x5204, NavigationGuidance.lane(NavigationGuidance.LaneUpdate(
            listOf(42), index = 0, lanes = listOf(NavigationGuidance.Lane(index = 0, status = 2,
                angles = listOf(0), highlight = 0)))))
        assertEquals(1, Iap2LaneGuidance.parse(lane.payload).size)
        assertTrue(Iap2LaneGuidance.parse(byteArrayOf(0, 9, 0, 2)).isEmpty())
        assertTrue(Iap2LaneGuidance.parse(byteArrayOf()).isEmpty())
        route.accept(lane.messageId, lane.payload)
        music.acceptUpdate(lane)
        assertEquals(guidance, route.currentApple())
        assertEquals(nowPlaying, music.nowPlaying)
        val malformed = frame(0x5001, listOf(0 to byteArrayOf(0, 9, 0, 1)))
        music.acceptUpdate(malformed)
        route.accept(malformed.messageId, malformed.payload)
        assertEquals(guidance, route.currentApple())
        val ended = NavigationWireEncoding.plan(snapshot().copy(lifecycle = NavigationLifecycle.ENDED), selection, display())
        ended.packets.forEach { packet -> music.acceptUpdate(frame(packet.id, packet.fields)) }
        deliver(route, ended)
        assertNull(route.currentApple())
        assertEquals(nowPlaying, music.nowPlaying)
    }

    @Test fun actualReceiverKeepsTextRolesAndClearsAfterRoadWithoutInventingCurrentRoad() {
        val route = BydHudRouteState()
        for (road in listOf("道路🚘", "طريق", "Rue é", "", null, "bad\u0000road", "\uD800")) {
            val initial = snapshot(remaining = 19000)
            val plan = NavigationWireEncoding.plan(initial.copy(
                maneuver = initial.maneuver!!.copy(afterRoad = road)), selection, display())
            deliver(route, plan)
            val expected = if (road != null && NowPlayingUpdate.textOrNull(road) != null) road else ""
            assertEquals(expected, route.currentApple()!!.road)
            assertTrue(plan.packets.filter { it.id == 0x5201 }.all { packet ->
                packet.fields.none { it.first == 3 || it.first == 4 }
            })
            assertTrue(plan.packets.single { it.id == 0x5202 }.fields.none { it.first == 2 })
        }
    }

    @Test fun retainedOverlayExpiresAcrossWirelessDropAndNewGuidanceStartsClean() {
        var now = 0L
        val route = BydHudRouteState(nanoTime = { now }, staleRouteNs = 120_000_000_000L,
            keepAcrossNoRoute = true)
        deliver(route, NavigationWireEncoding.plan(snapshot(remaining = 19000), selection, display()))
        route.holdAcrossDrop()
        now = 119_000_000_000L
        assertNotNull(route.currentApple())
        now = 120_000_000_000L
        assertNull(route.currentApple())
        route.clear()
        assertNull(route.currentApple())
        deliver(route, NavigationWireEncoding.plan(snapshot(2, NavigationTurn.LEFT, 50), selection, display()))
        assertEquals(50, route.currentApple()!!.distanceMeters)
        assertNull(route.currentApple()!!.remainingMeters)
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

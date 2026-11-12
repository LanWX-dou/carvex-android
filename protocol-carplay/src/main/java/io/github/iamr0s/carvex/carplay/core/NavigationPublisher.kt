package io.github.iamr0s.carvex.carplay.core

import io.github.iamr0s.carvex.protocol.api.NavigationLifecycle
import io.github.iamr0s.carvex.protocol.api.NavigationSink
import io.github.iamr0s.carvex.protocol.api.NavigationSnapshot
import io.github.iamr0s.carvex.protocol.api.NavigationTurn
import io.github.iamr0s.carvex.sessioncore.RawParameter
import java.util.concurrent.atomic.AtomicLong

internal data class NavigationPacket(val id: Int, val fields: List<Pair<Int, ByteArray>>, val evidence: String)
internal data class NavigationPlan(val packets: List<NavigationPacket> = emptyList(), val blocked: String? = null)

/** 24A446 1000c5704: Identification p30 contains component p0 and maneuver capacity p6.
 * Text length/NUL contracts remain separate from the numeric core publication. */
internal class NavigationDisplayCapabilities(parameters: List<RawParameter>) {
    private val raw = parameters.map { RawParameter(it.id, it.value.copyOf()) }
    fun parameters(): List<RawParameter> = raw.map { RawParameter(it.id, it.value.copyOf()) }

    fun maneuverCapacity(component: Int): Int? {
        val matches = raw.filter { it.id == 30 }.mapNotNull { parameter ->
            try {
                val fields = IapWire.parseFieldList(parameter.value)
                val id = fields[0]?.takeIf { it.size == 2 }?.let { IapWire.u16(it, 0) }
                if (id != component) null else fields
            } catch (_: IllegalArgumentException) { null }
        }
        if (matches.size != 1) return null
        return try {
            matches.single()[6]?.takeIf { it.size == 2 }?.let { IapWire.u16(it, 0) }?.takeIf { it > 0 }
        } catch (_: IllegalArgumentException) { null }
    }

    fun supportsManeuver(component: Int): Boolean = maneuverCapacity(component) != null
}

/** Numeric core: Apple state/type tables and encoders; GalaxyPlay 0.1.212 p7/p10 meter
 * consumer and definition/reference merge. Text, display units and lanes remain omitted.
 * See the navigation fix record for the receiver-specific unit/order evidence boundary. */
internal object NavigationWireEncoding {
    fun plan(snapshot: NavigationSnapshot, selection: NavigationGuidance.Start,
             capabilities: NavigationDisplayCapabilities): NavigationPlan {
        if (snapshot.evidence["lifecycle"].isNullOrBlank()) return NavigationPlan(blocked = "host-lifecycle-unverified")
        fun route(state: Int, index: Int? = null, distance: Long? = null,
                  remaining: Long? = null) = NavigationPacket(0x5201,
            NavigationGuidance.route(NavigationGuidance.RouteUpdate(selection.components,
                state = state, distanceRemaining = remaining, distanceToManeuver = distance,
                maneuverList = listOfNotNull(index)), selection.mask),
            "24A446:CarPlay:247b00444/table2690da898;accessoryd:100004428/1000027f4;GalaxyPlay:0249f0")
        if (snapshot.lifecycle in setOf(NavigationLifecycle.ENDED, NavigationLifecycle.INVALIDATED))
            return NavigationPlan(listOf(route(0))) // NotActive; no fabricated Arrived reason or STOP.
        if (snapshot.lifecycle !in setOf(NavigationLifecycle.ACTIVE, NavigationLifecycle.REROUTING))
            return NavigationPlan(blocked = "no-active-route")
        val state = if (snapshot.lifecycle == NavigationLifecycle.REROUTING) 5 else 1
        // accessoryd 100002b94..100002ba8 selects p7 and uses the U32 writer.
        // Require this field's source evidence; an explicit zero is a valid route value.
        val remaining = snapshot.route.distanceRemainingMeters?.takeIf {
            !snapshot.evidence["distanceRemainingMeters"].isNullOrBlank() && it in 0..0xffffffffL
        }
        val maneuver = snapshot.maneuver
        val type = maneuver?.turn?.let(::type)
        if (type == null || snapshot.evidence["maneuver"].isNullOrBlank()) {
            // Reset clears any previously joined arrow/distance; the route itself is still active.
            return NavigationPlan(listOf(route(0), route(state, remaining = remaining)))
        }
        val capacities = selection.components.map { component ->
            capabilities.maneuverCapacity(component)
                ?: return NavigationPlan(blocked = "maneuver-capacity-missing-or-zero")
        }
        val capacity = capacities.minOrNull()
            ?: return NavigationPlan(blocked = "maneuver-capacity-missing-or-zero")
        if (snapshot.maneuverGeneration <= 0) return NavigationPlan(blocked = "maneuver-generation-missing")
        // p6 is a storage limit, not just a Boolean. Both inspected receivers retain
        // definitions by U16 index until reset. Reuse a bounded set of slots so a
        // long route cannot exceed the smallest subscribed component's capacity.
        val index = (snapshot.maneuverGeneration % capacity).toInt()
        val distance = maneuver.distanceMeters?.takeIf { it in 1..0xffffffffL }
        val definition = NavigationPacket(0x5202,
            NavigationGuidance.maneuver(NavigationGuidance.ManeuverUpdate(selection.components,
                index = index, type = type)),
            "24A446:CarPlay:247b3a190/table2690da6a8;accessoryd:1000c5008/1001777c0;GalaxyPlay:024858")
        // Every batch is self-contained, including resubscription. No delivered snapshot cache.
        // Missing/invalid values must not leave the receiver's old segment or route
        // remainder intact. GalaxyPlay 024c74 skips a missing p7; 024838 resets it.
        // With one slot the new definition would immediately change the currently
        // referenced arrow while its old distance is still present. Clear first.
        return NavigationPlan((if (distance == null || remaining == null || capacity == 1) listOf(route(0)) else emptyList()) +
            listOf(definition, route(state, index, distance, remaining)))
    }

    private fun type(turn: NavigationTurn): Int = when (turn) {
        NavigationTurn.STRAIGHT -> 3
        NavigationTurn.LEFT -> 1
        NavigationTurn.RIGHT -> 2
        NavigationTurn.U_TURN -> 4
        NavigationTurn.SHARP_LEFT -> 47
        NavigationTurn.SHARP_RIGHT -> 48
        NavigationTurn.SLIGHT_LEFT -> 49
        NavigationTurn.SLIGHT_RIGHT -> 50
    }
}

/** A Link owns only subscriptions and delivery tokens; the session relay owns navigation data.
 * 24A446: navMainList 1001b40e0; START 10017527c; STOP 10017593c. */
internal class NavigationPublisher(
    private val emit: (Int, List<Pair<Int, ByteArray>>, () -> Boolean, (Throwable?) -> Unit) -> Boolean,
    private val log: (String) -> Unit = {},
    private val encode: (NavigationSnapshot, NavigationGuidance.Start, NavigationDisplayCapabilities) -> NavigationPlan =
        NavigationWireEncoding::plan,
) : NavigationSink {
    private var ready = false
    private var accessorySends = emptySet<Int>()
    private var accessoryReceives = emptySet<Int>()
    private var selection: NavigationGuidance.Start? = null
    private var display = NavigationDisplayCapabilities(emptyList())
    @Volatile private var source: (() -> NavigationSnapshot?)? = null
    private var linkEpoch = 0L
    private var subscriptionEpoch = 0L
    private val deliveryEpoch = AtomicLong()
    private val batches = AtomicLong()

    @Synchronized fun identification(parameters: List<RawParameter>) {
        display = NavigationDisplayCapabilities(parameters)
        deliveryEpoch.incrementAndGet()
    }

    @Synchronized fun linkReady(ready: Boolean, sends: Set<Int> = emptySet(), receives: Set<Int> = emptySet()) {
        this.ready = ready
        accessorySends = sends.toSet()
        accessoryReceives = receives.toSet()
        selection = null
        linkEpoch++
        subscriptionEpoch++
        deliveryEpoch.incrementAndGet()
        if (!ready) display = NavigationDisplayCapabilities(emptyList())
        log("debug navigation event=link ready=$ready link=$linkEpoch subscription=$subscriptionEpoch " +
            "accessorySends=${accessorySends.sorted().map { it.toString(16) }} " +
            "accessoryReceives=${accessoryReceives.sorted().map { it.toString(16) }}")
    }

    @Synchronized override fun attachNavigation(source: () -> NavigationSnapshot?) {
        deliveryEpoch.incrementAndGet()
        this.source = source
    }

    @Synchronized override fun detachNavigation() {
        deliveryEpoch.incrementAndGet()
        source = null
        selection = null
        subscriptionEpoch++
    }

    @Synchronized fun command(id: Int, fields: IapFields): Boolean {
        if (!ready) return blocked("link-not-ready", id)
        if (!NavigationGuidance.featureReady(accessorySends, accessoryReceives))
            return blocked("required-capabilities", id)
        when (id) {
            0x5200 -> {
                val parsed = NavigationGuidance.parseStart(fields) ?: return blocked("invalid-start", id)
                selection = parsed
                subscriptionEpoch++
                deliveryEpoch.incrementAndGet()
                log("debug navigation event=subscription id=5200 accepted=true link=$linkEpoch subscription=$subscriptionEpoch components=${parsed.components} options=${parsed.mask}")
                publish()
            }
            0x5203 -> {
                val components = NavigationGuidance.parseStop(fields) ?: return blocked("invalid-stop", id)
                selection = null // Fine-grained component stopping is still OPEN.
                subscriptionEpoch++
                deliveryEpoch.incrementAndGet()
                log("debug navigation event=subscription id=5203 accepted=true link=$linkEpoch subscription=$subscriptionEpoch components=$components")
            }
            else -> return false
        }
        return true
    }

    @Synchronized override fun navigationChanged(): Boolean {
        deliveryEpoch.incrementAndGet()
        return publish()
    }

    /** Field presence and evidence labels only: maneuver IDs can contain private road text. */
    private fun snapshotContext(snapshot: NavigationSnapshot?): String {
        if (snapshot == null) return "source=absent"
        val fields = linkedMapOf(
            "currentRoad" to snapshot.route.currentRoad,
            "destination" to snapshot.route.destination,
            "distanceRemainingMeters" to snapshot.route.distanceRemainingMeters,
            "timeRemainingSeconds" to snapshot.route.timeRemainingSeconds,
            "arrivalEpochSeconds" to snapshot.route.arrivalEpochSeconds,
            "maneuver.turn" to snapshot.maneuver?.turn,
            "maneuver.distanceMeters" to snapshot.maneuver?.distanceMeters,
            "maneuver.description" to snapshot.maneuver?.description,
            "maneuver.afterRoad" to snapshot.maneuver?.afterRoad,
            "lanes" to snapshot.lanes,
        )
        return "source=${snapshot.sourceId} binding=${snapshot.bindingEpoch} route=${snapshot.routeEpoch} " +
            "revision=${snapshot.revision} lifecycle=${snapshot.lifecycle} maneuverGeneration=${snapshot.maneuverGeneration} " +
            "available=${fields.filterValues { it != null }.keys} unavailable=${fields.filterValues { it == null }.keys} " +
            "sourceEvidence=${snapshot.evidence.toSortedMap()} unverified=${snapshot.unverifiedFields.sorted()}"
    }

    private fun blocked(reason: String, id: Int = 0x5201,
                        context: String = snapshotContext(source?.invoke())): Boolean {
        log("debug navigation event=blocked id=${id.toString(16)} link=$linkEpoch subscription=$subscriptionEpoch " +
            "ready=$ready components=${selection?.components.orEmpty()} options=${selection?.mask ?: 0} reason=$reason $context")
        return false
    }

    private fun publish(): Boolean {
        val selected = selection ?: return blocked("no-subscription")
        if (!ready) return blocked("link-not-ready")
        if (selected.components.isEmpty()) return blocked("empty-components-profile-unverified")
        val supplier = source ?: return blocked("no-source")
        val snapshot = supplier() ?: return blocked("no-snapshot")
        val context = snapshotContext(snapshot)
        val plan = encode(snapshot, selected, display)
        plan.blocked?.let { return blocked(it, context = context) }
        if (plan.packets.isEmpty()) return blocked("no-verified-fields", context = context)
        if (plan.packets.any { it.id == 0x5204 } && 0x5204 !in accessoryReceives)
            return blocked("lane-capability-missing", 0x5204, context)
        if (plan.packets.any { it.id !in accessoryReceives || it.id !in setOf(0x5201, 0x5202, 0x5204) })
            return blocked("message-not-declared", context = context)
        val token = deliveryEpoch.get()
        val batch = batches.incrementAndGet()
        val link = linkEpoch
        val subscription = subscriptionEpoch
        val valid = {
            // Writer callbacks must never take publisher or relay locks.
            deliveryEpoch.get() == token && source === supplier && supplier() === snapshot
        }
        // Validate and copy the entire plan before submitting any part of the batch.
        val packets = plan.packets.map { packet ->
            require(packet.evidence.isNotBlank())
            val checked = when (packet.id) {
                0x5201 -> NavigationGuidance.routeGuidanceUpdate(packet.fields)
                0x5202 -> NavigationGuidance.maneuverUpdate(packet.fields)
                else -> NavigationGuidance.laneGuidance(packet.fields)
            }
            require(checked.filter { it.first == 0 }.map { IapWire.u16(it.second, 0) } == selected.components)
            require(checked.any { it.first != 0 })
            packet.copy(fields = checked.map { it.first to it.second.copyOf() })
        }
        val batchValid = java.util.concurrent.atomic.AtomicBoolean(true)
        val completed = java.util.concurrent.atomic.AtomicInteger()
        val submitted = java.util.concurrent.atomic.AtomicInteger()
        val batchContext = "batch=$batch link=$link subscription=$subscription delivery=$token " +
            "components=${selected.components} options=${selected.mask} $context"
        log("debug navigation event=planned $batchContext " +
            "maneuverCapacities=${selected.components.associateWith { display.maneuverCapacity(it) }} " +
            "laneSupported=${0x5204 in accessoryReceives} messages=${packets.map { it.id.toString(16) }}")
        for ((position, packet) in packets.withIndex()) {
            if (!valid() || !batchValid.get()) return blocked("stale-batch", packet.id, context)
            val packetContext = "$batchContext packet=${position + 1}/${packets.size} id=${packet.id.toString(16)} " +
                "fields=${packet.fields.map { it.first }} evidence=${packet.evidence}"
            val writerChecked = java.util.concurrent.atomic.AtomicBoolean()
            val accepted = emit(packet.id, packet.fields, {
                val current = batchValid.get() && valid()
                if (writerChecked.compareAndSet(false, true))
                    runCatching {
                        log("debug navigation event=writer-check $packetContext accepted=$current; generation check before sequence allocation")
                    } // Diagnostics must not change the writer's generation decision.
                current
            }) { error ->
                if (error != null) batchValid.set(false)
                val count = if (error == null) completed.incrementAndGet() else completed.get()
                log("debug navigation event=transport $packetContext writerChecked=${writerChecked.get()} " +
                    "completed=$count/${packets.size} error=${error?.javaClass?.simpleName ?: "none"}; transport completion, instrument display unverified")
            }
            if (!accepted) {
                batchValid.set(false)
                log("debug navigation event=queue-rejected $packetContext submitted=${submitted.get()}/${packets.size}; partial submission possible")
                return false
            }
            submitted.incrementAndGet()
            log("debug navigation event=queued $packetContext")
        }
        return true // Queue acceptance only; no delivery baseline is advanced.
    }
}

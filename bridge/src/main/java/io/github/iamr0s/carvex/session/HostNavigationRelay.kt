package io.github.iamr0s.carvex.session

import io.github.iamr0s.carvex.protocol.api.*
import io.github.iamr0s.carvex.sessioncore.*
import java.util.concurrent.atomic.AtomicReference

/** One session owns the source snapshot; a Link owns only its subscription and delivery state. */
internal class HostNavigationRelay(private val log: (String) -> Unit = {}) : AutoCloseable {
    private val current = AtomicReference<NavigationSnapshot?>()
    private var source: HostNavigationSource? = null
    private var routeId: String? = null
    private var sequence: Long? = null
    private val retiredRoutes = mutableSetOf<String>()
    private var routeEpoch = 0L
    private var revision = 0L
    private var maneuverGeneration = 0L
    private var closed = false
    private var sink: NavigationSink? = null

    /** Lock-free: START callbacks must not take this relay's update lock. */
    fun snapshot(): NavigationSnapshot? = current.get()

    @Synchronized fun attach(target: NavigationSink) {
        if (closed) return
        sink?.detachNavigation()
        sink = target
        target.attachNavigation(::snapshot)
        target.navigationChanged()
    }

    @Synchronized fun detach() {
        sink?.detachNavigation()
        sink = null
    }

    @Synchronized fun update(event: HostNavigationEvent): Boolean {
        if (closed) return false
        val previousSource = source
        if (previousSource != null && (event.source.bindingEpoch < previousSource.bindingEpoch ||
                event.source.bindingEpoch == previousSource.bindingEpoch && event.source.id != previousSource.id))
            return blocked("stale-binding")
        val sourceChanged = previousSource == null || event.source.bindingEpoch > previousSource.bindingEpoch
        if (sourceChanged) {
            source = event.source
            routeId = null
            sequence = null
            retiredRoutes.clear()
            current.set(null)
            sink?.navigationChanged()
        }
        val old = current.get()
        if (old?.lifecycle == NavigationLifecycle.INVALIDATED && event.change != HostNavigationChange.SOURCE_INVALIDATED)
            return blocked("invalidated-binding")
        val newRoute = event.change == HostNavigationChange.STARTED &&
            (old == null || old.lifecycle in setOf(NavigationLifecycle.ENDED, NavigationLifecycle.INVALIDATED) ||
                event.routeId != null && event.routeId != routeId)
        if (event.routeId != null && event.routeId in retiredRoutes) return blocked("retired-route")
        // With an explicit new route ID, sequence is route-local; otherwise it is binding-local.
        val resetsSequence = newRoute && event.routeId != null && event.routeId != routeId
        val receivedSequence = event.sequence
        if (!resetsSequence && receivedSequence != null && sequence != null && receivedSequence <= requireNotNull(sequence))
            return blocked("stale-sequence")
        if (event.change != HostNavigationChange.STARTED && routeId != null &&
            event.routeId != null && event.routeId != routeId) return blocked("stale-route")
        if (event.change == HostNavigationChange.UPDATED || event.change == HostNavigationChange.REROUTING) {
            if (old == null || old.lifecycle in setOf(NavigationLifecycle.ENDED, NavigationLifecycle.INVALIDATED))
                return blocked("no-active-route")
        }
        if (event.change == HostNavigationChange.ENDED && old?.lifecycle == NavigationLifecycle.ENDED)
            return blocked("duplicate-end")
        if (event.change == HostNavigationChange.SOURCE_INVALIDATED && old?.lifecycle == NavigationLifecycle.INVALIDATED)
            return blocked("duplicate-invalidation")
        if (newRoute) {
            routeEpoch++
            if (resetsSequence) {
                routeId?.let { retiredRoutes += it }
                sequence = null
            }
        }
        if (event.routeId != null && (newRoute || routeId == null)) routeId = event.routeId
        if (event.sequence != null) sequence = event.sequence
        val lifecycle = when (event.change) {
            HostNavigationChange.STARTED -> NavigationLifecycle.ACTIVE
            HostNavigationChange.UPDATED -> old?.lifecycle ?: NavigationLifecycle.UNKNOWN
            HostNavigationChange.REROUTING -> NavigationLifecycle.REROUTING
            HostNavigationChange.ENDED -> NavigationLifecycle.ENDED
            HostNavigationChange.SOURCE_INVALIDATED -> NavigationLifecycle.INVALIDATED
        }
        val terminal = lifecycle in setOf(NavigationLifecycle.ENDED, NavigationLifecycle.INVALIDATED)
        val base = if (newRoute || terminal) null else old
        val delta = event.delta
        val evidence = base?.evidence.orEmpty().toMutableMap()
        fun <T> merge(name: String, field: HostNavigationField<T>, value: T?): T? = when (field) {
            HostNavigationField.Absent -> value
            HostNavigationField.Clear -> { evidence.remove(name); null }
            is HostNavigationField.Value -> { evidence[name] = field.evidence; field.value }
        }
        val route = if (terminal) NavigationRoute() else NavigationRoute(
            merge("currentRoad", delta.currentRoad, base?.route?.currentRoad),
            merge("destination", delta.destination, base?.route?.destination),
            merge("distanceRemainingMeters", delta.distanceRemainingMeters, base?.route?.distanceRemainingMeters),
            merge("timeRemainingSeconds", delta.timeRemainingSeconds, base?.route?.timeRemainingSeconds),
            merge("arrivalEpochSeconds", delta.arrivalEpochSeconds, base?.route?.arrivalEpochSeconds),
        )
        val maneuver = if (terminal) null else when (val field = delta.maneuver) {
            HostNavigationField.Absent -> base?.maneuver
            HostNavigationField.Clear -> { evidence.remove("maneuver"); null }
            is HostNavigationField.Value -> {
                evidence["maneuver"] = field.evidence
                field.value.let { NavigationManeuver(it.id, it.description, it.afterRoad, it.distanceMeters,
                    it.turn?.let { turn -> NavigationTurn.valueOf(turn.name) }) }
            }
        }
        val maneuverChanged = maneuver?.id != base?.maneuver?.id
        if (maneuver != null && maneuverChanged) maneuverGeneration++
        val lanes = if (terminal) null else when (val field = delta.lanes) {
            HostNavigationField.Absent -> if (maneuverChanged) null else base?.lanes
            HostNavigationField.Clear -> { evidence.remove("lanes"); null }
            is HostNavigationField.Value -> {
                evidence["lanes"] = field.evidence
                field.value.let { NavigationLanes(it.maneuverId, it.lanes.map { lane ->
                    NavigationLane(lane.directions.map { turn -> NavigationTurn.valueOf(turn.name) }, lane.recommended)
                }, it.description) }.takeIf { it.maneuverId == maneuver?.id }
            }
        }
        if (lanes == null) evidence.remove("lanes")
        evidence["lifecycle"] = event.evidence
        val next = NavigationSnapshot(event.source.id, event.source.bindingEpoch, routeEpoch, ++revision,
            lifecycle, route, maneuver, lanes, NavigationEndReason.valueOf(event.endReason.name),
            evidence.toMap(), if (terminal) emptySet() else base?.unverifiedFields.orEmpty() + event.unverifiedFields,
            maneuverGeneration)
        current.set(next)
        log("debug navigation event=normalized source=${next.sourceId} binding=${next.bindingEpoch} route=${next.routeEpoch} revision=${next.revision} lifecycle=${next.lifecycle} unverified=${next.unverifiedFields.sorted()}")
        sink?.navigationChanged()
        return true
    }

    private fun blocked(reason: String): Boolean {
        log("debug navigation event=blocked source=relay reason=$reason route=$routeEpoch revision=$revision")
        return false
    }

    @Synchronized override fun close() {
        if (closed) return
        closed = true
        current.set(null)
        detach()
        source = null
        routeId = null
        sequence = null
        retiredRoutes.clear()
    }
}

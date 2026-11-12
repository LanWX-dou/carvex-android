package io.github.iamr0s.carvex.protocol.api

/** Application semantics; enum ordinals are never protocol values. */
enum class NavigationLifecycle { UNKNOWN, ACTIVE, REROUTING, ENDED, INVALIDATED }
enum class NavigationEndReason { UNKNOWN, CANCELLED, ARRIVED }
enum class NavigationTurn { STRAIGHT, LEFT, RIGHT, SLIGHT_LEFT, SLIGHT_RIGHT, SHARP_LEFT, SHARP_RIGHT, U_TURN }

data class NavigationRoute(
    val currentRoad: String? = null,
    val destination: String? = null,
    val distanceRemainingMeters: Long? = null,
    val timeRemainingSeconds: Long? = null,
    val arrivalEpochSeconds: Long? = null,
)

data class NavigationManeuver(
    val id: String,
    val description: String? = null,
    val afterRoad: String? = null,
    val distanceMeters: Long? = null,
    val turn: NavigationTurn? = null,
)

data class NavigationLane(val directions: List<NavigationTurn>, val recommended: Boolean? = null)
data class NavigationLanes(val maneuverId: String, val lanes: List<NavigationLane>, val description: String? = null)

/** Immutable session snapshot supplied to a protocol implementation; no host or Android types. */
data class NavigationSnapshot(
    val sourceId: String,
    val bindingEpoch: Long,
    val routeEpoch: Long,
    val revision: Long,
    val lifecycle: NavigationLifecycle,
    val route: NavigationRoute = NavigationRoute(),
    val maneuver: NavigationManeuver? = null,
    val lanes: NavigationLanes? = null,
    val endReason: NavigationEndReason = NavigationEndReason.UNKNOWN,
    val evidence: Map<String, String> = emptyMap(),
    val unverifiedFields: Set<String> = emptySet(),
    /** Local generation of the current maneuver, stable across distance-only updates. */
    val maneuverGeneration: Long = 0,
)

/** The supplier must be nonblocking and safe to read while a protocol handles subscriptions. */
interface NavigationSink {
    fun attachNavigation(source: () -> NavigationSnapshot?)
    fun navigationChanged(): Boolean
    fun detachNavigation()
}

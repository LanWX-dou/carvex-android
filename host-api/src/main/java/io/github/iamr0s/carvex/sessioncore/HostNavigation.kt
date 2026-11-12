package io.github.iamr0s.carvex.sessioncore

/** Source identity is local bookkeeping, never an iAP component or wire state. */
data class HostNavigationSource(val id: String, val bindingEpoch: Long, val version: String? = null) {
    init { require(id.isNotBlank() && bindingEpoch >= 0) }
}

/** Absent does not overwrite a snapshot; Clear does. Values must have source evidence. */
sealed interface HostNavigationField<out T> {
    data object Absent : HostNavigationField<Nothing>
    data object Clear : HostNavigationField<Nothing>
    data class Value<T>(val value: T, val evidence: String) : HostNavigationField<T> {
        init { require(evidence.isNotBlank()) }
    }
}

enum class HostNavigationChange { STARTED, UPDATED, REROUTING, ENDED, SOURCE_INVALIDATED }
enum class HostNavigationEndReason { UNKNOWN, CANCELLED, ARRIVED }
enum class HostNavigationTurn { STRAIGHT, LEFT, RIGHT, SLIGHT_LEFT, SLIGHT_RIGHT, SHARP_LEFT, SHARP_RIGHT, U_TURN }

data class HostNavigationManeuver(
    val id: String,
    val description: String? = null,
    val afterRoad: String? = null,
    val distanceMeters: Long? = null,
    val turn: HostNavigationTurn? = null,
) { init { require(id.isNotBlank()); require(distanceMeters == null || distanceMeters >= 0) } }

data class HostNavigationLane(val directions: List<HostNavigationTurn>, val recommended: Boolean? = null)
data class HostNavigationLanes(val maneuverId: String, val lanes: List<HostNavigationLane>, val description: String? = null)

data class HostNavigationDelta(
    val currentRoad: HostNavigationField<String> = HostNavigationField.Absent,
    val destination: HostNavigationField<String> = HostNavigationField.Absent,
    val distanceRemainingMeters: HostNavigationField<Long> = HostNavigationField.Absent,
    val timeRemainingSeconds: HostNavigationField<Long> = HostNavigationField.Absent,
    val arrivalEpochSeconds: HostNavigationField<Long> = HostNavigationField.Absent,
    val maneuver: HostNavigationField<HostNavigationManeuver> = HostNavigationField.Absent,
    val lanes: HostNavigationField<HostNavigationLanes> = HostNavigationField.Absent,
) {
    init {
        listOf(distanceRemainingMeters, timeRemainingSeconds, arrivalEpochSeconds).forEach {
            require(it !is HostNavigationField.Value || it.value >= 0)
        }
    }
}

/** Raw HUD diagnostics. Published navigation fields are supplied explicitly through the delta. */
data class HostNavigationObservation(
    val roadHint: String? = null,
    val distanceHintMeters: Long? = null,
    val referenceDistanceMeters: Long? = null,
    val turnHint: Int? = null,
    val action: Int? = null,
    val iconBytes: Int? = null,
)

data class HostNavigationEvent(
    val source: HostNavigationSource,
    val change: HostNavigationChange,
    val evidence: String,
    val delta: HostNavigationDelta = HostNavigationDelta(),
    val routeId: String? = null,
    val sequence: Long? = null,
    val endReason: HostNavigationEndReason = HostNavigationEndReason.UNKNOWN,
    val observation: HostNavigationObservation? = null,
    val unverifiedFields: Set<String> = emptySet(),
) { init { require(evidence.isNotBlank()); require(sequence == null || sequence >= 0) } }

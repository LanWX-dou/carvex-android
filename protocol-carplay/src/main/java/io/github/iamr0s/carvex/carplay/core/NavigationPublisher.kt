package io.github.iamr0s.carvex.carplay.core

/** Runtime Link owns its 5200/5203 subscription (24A446: 10017527c / 10017593c).
 * A local backend sample may precede START; retain it and encode using the current
 * subscriber's component IDs and options. Bootstrap globals never authorize a send. */
class NavigationPublisher(
    private val emit: (Int, List<Pair<Int, ByteArray>>) -> Boolean,
    private val log: (String) -> Unit = {},
) {
    private var ready = false
    private var sends = emptySet<Int>()
    private var receives = emptySet<Int>()
    private var selection: NavigationGuidance.Start? = null
    private var route: NavigationGuidance.RouteUpdate? = null

    @Synchronized fun linkReady(ready: Boolean, sends: Set<Int> = emptySet(), receives: Set<Int> = emptySet()) {
        this.ready = ready
        this.sends = sends.toSet()
        this.receives = receives.toSet()
        selection = null
    }

    @Synchronized fun command(id: Int, fields: IapFields): Boolean {
        if (!ready || !NavigationGuidance.featureReady(sends, receives)) return false
        when (id) {
            0x5200 -> {
                val parsed = NavigationGuidance.parseStart(fields) ?: return false
                selection = parsed
                log("navigation runtime start components=${parsed.components} mask=${parsed.mask}")
                route?.let { sendRoute(it) }
            }
            0x5203 -> {
                val components = NavigationGuidance.parseStop(fields) ?: return false
                selection = null
                route = null
                log("navigation runtime stop components=$components")
            }
            else -> return false
        }
        return true
    }

    /** Complete latest backend sample, not a fabricated navigation lifecycle or maneuver. */
    @Synchronized fun update(value: NavigationGuidance.RouteUpdate): Boolean {
        NavigationGuidance.route(value, mask = 0x33) // Validate optional fields before caching too.
        route = value.copy(components = emptyList(), maneuverList = value.maneuverList.toList())
        return sendRoute(requireNotNull(route))
    }

    private fun sendRoute(value: NavigationGuidance.RouteUpdate): Boolean {
        val selected = selection ?: return false
        if (!ready) return false
        val fields = NavigationGuidance.route(value.copy(components = selected.components), selected.mask)
        if (fields.none { it.first != 0 }) return false
        return emit(0x5201, fields)
    }

    @Synchronized fun send(id: Int, values: List<Pair<Int, ByteArray>>): Boolean {
        val selected = selection ?: return false
        if (!ready || id !in receives) return false
        val fields = selected.components.map { 0 to IapWire.be16(it) } + values.filter { it.first != 0 }
        val checked = when (id) {
            0x5202 -> NavigationGuidance.maneuverUpdate(fields)
            0x5204 -> NavigationGuidance.laneGuidance(fields)
            else -> return false
        }
        return checked.any { it.first != 0 } && emit(id, checked)
    }
}

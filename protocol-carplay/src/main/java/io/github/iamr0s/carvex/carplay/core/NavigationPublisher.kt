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
        log("debug navigation event=link ready=$ready sends=${this.sends.filter{it in setOf(0x5200,0x5203)}.map{it.toString(16)}} receives=${this.receives.filter{it in setOf(0x5201,0x5202,0x5204)}.map{it.toString(16)}} cached=${route!=null}")
    }

    @Synchronized fun command(id: Int, fields: IapFields): Boolean {
        if (!ready || !NavigationGuidance.featureReady(sends, receives)) {
            log("debug navigation event=blocked direction=rx id=${id.toString(16)} ready=$ready reason=required-capabilities missingSends=${setOf(0x5200,0x5203)-sends} missingReceives=${setOf(0x5201,0x5202)-receives}")
            return false
        }
        when (id) {
            0x5200 -> {
                val parsed = NavigationGuidance.parseStart(fields) ?: run {
                    log("debug navigation event=subscription direction=rx id=5200 accepted=false reason=invalid-fields")
                    return false
                }
                selection = parsed
                log("navigation runtime start components=${parsed.components} mask=${parsed.mask}")
                log("debug navigation event=subscription direction=rx id=5200 accepted=true components=${parsed.components} mask=${parsed.mask} cached=${route!=null}")
                route?.let { sendRoute(it) }
            }
            0x5203 -> {
                val components = NavigationGuidance.parseStop(fields) ?: run {
                    log("debug navigation event=subscription direction=rx id=5203 accepted=false reason=invalid-fields")
                    return false
                }
                selection = null
                route = null
                log("navigation runtime stop components=$components")
                log("debug navigation event=subscription direction=rx id=5203 accepted=true components=$components cached=false")
            }
            else -> return false
        }
        return true
    }

    /** Complete latest backend sample, not a fabricated navigation lifecycle or maneuver. */
    @Synchronized fun update(value: NavigationGuidance.RouteUpdate): Boolean {
        NavigationGuidance.route(value, mask = 0x33) // Validate optional fields before caching too.
        route = value.copy(components = emptyList(), maneuverList = value.maneuverList.toList())
        log("debug navigation event=sample state=${value.state?:"unknown"} maneuverState=${value.maneuverState?:"unknown"} maneuverCount=${value.maneuverCount?:"unknown"} distanceRemaining=${value.distanceRemaining?:"unknown"} distanceToManeuver=${value.distanceToManeuver?:"unknown"}")
        return sendRoute(requireNotNull(route))
    }

    /** Local source invalidation is separate from the accessory's 5203 subscription.
     * Do not fabricate an iAP state value or replay an ended host route on a later START. */
    @Synchronized fun clearRoute() {
        log("debug navigation event=lifecycle source=host ended=true cached=${route!=null} subscribed=${selection!=null}; cached sample discarded, no guessed wire state")
        route = null
    }

    private fun sendRoute(value: NavigationGuidance.RouteUpdate): Boolean {
        val selected = selection ?: run { log("debug navigation event=blocked direction=tx id=5201 reason=no-subscription cached=true"); return false }
        if (!ready) { log("debug navigation event=blocked direction=tx id=5201 reason=link-not-ready"); return false }
        val fields = NavigationGuidance.route(value.copy(components = selected.components), selected.mask)
        if (fields.none { it.first != 0 }) { log("debug navigation event=blocked direction=tx id=5201 reason=no-selected-values"); return false }
        return emit(0x5201, fields)
    }

    @Synchronized fun send(id: Int, values: List<Pair<Int, ByteArray>>): Boolean {
        val selected = selection ?: run { log("debug navigation event=blocked direction=tx id=${id.toString(16)} reason=no-subscription"); return false }
        if (!ready || id !in receives) { log("debug navigation event=blocked direction=tx id=${id.toString(16)} ready=$ready declared=${id in receives}"); return false }
        val fields = selected.components.map { 0 to IapWire.be16(it) } + values.filter { it.first != 0 }
        val checked = when (id) {
            0x5202 -> NavigationGuidance.maneuverUpdate(fields)
            0x5204 -> NavigationGuidance.laneGuidance(fields)
            else -> return false
        }
        return checked.any { it.first != 0 } && emit(id, checked)
    }
}

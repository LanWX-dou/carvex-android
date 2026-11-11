package io.github.iamr0s.carvex.carplay.core

/** 24A446 accessoryd 1001b3158/1001b317c: each group requires START/update; STOP is optional.
 * Only this authenticated runtime Link can own subscriptions; no metadata source is inferred. */
internal class RuntimePhoneSubscriptions(private val log:(String)->Unit = {}) {
    private val state = PhoneSubscriptions()
    private var ready = false
    private var sends = emptySet<Int>()
    private var receives = emptySet<Int>()
    private var epoch = 0L

    val callFields:Set<Int> get() = state.callStateFields.toSet()
    val communicationFields:Set<Int> get() = state.communicationFields.toSet()
    val callActive:Boolean get() = state.callStateActive
    val communicationActive:Boolean get() = state.communicationActive

    @Synchronized fun linkReady(ready:Boolean, sends:Set<Int> = emptySet(), receives:Set<Int> = emptySet()) {
        this.ready = ready
        this.sends = sends.toSet()
        this.receives = receives.toSet()
        state.stopCallStateUpdates()
        state.stopCommunicationUpdates()
        epoch++
        log("debug call event=link source=subscriptions ready=$ready epoch=$epoch; metadata provider unavailable")
    }

    @Synchronized fun command(id:Int, fields:IapFields):Boolean {
        if(id !in COMMANDS)return false
        val call = id == 0x4154 || id == 0x4156
        val start = if(call)0x4154 else 0x4157
        val update = if(call)0x4155 else 0x4158
        if(!ready || start !in sends || update !in receives || id !in sends) {
            log("debug call event=subscription direction=rx id=${id.toString(16)} accepted=false epoch=$epoch reason=required-capabilities")
            return false
        }
        val accepted = when(id) {
            0x4154 -> state.startCallStateUpdates(fields)
            0x4156 -> {state.stopCallStateUpdates();true}
            0x4157 -> state.startCommunicationUpdates(fields)
            else -> {state.stopCommunicationUpdates();true}
        }
        if(accepted)epoch++
        val selected = if(call)callFields else communicationFields
        log("debug call event=subscription direction=rx id=${id.toString(16)} accepted=$accepted epoch=$epoch fields=${selected.sorted()}")
        if(accepted && id in setOf(0x4154, 0x4157))
            log("debug call event=blocked direction=tx id=${update.toString(16)} epoch=$epoch reason=no-runtime-call-metadata-provider; subscription accepted, no state fabricated")
        return accepted
    }

    companion object {
        val COMMANDS = setOf(0x4154, 0x4156, 0x4157, 0x4159)
    }
}

package io.github.iamr0s.carvex.sessioncore

/** Product adapter: action 2 immediately requests a toggle; action 3 rearms without sending STOP.
 * Neither pairing nor physical button edges are assumed. State is local, not CarWith-confirmed VR. */
class VoiceButtonToggle:AutoCloseable {
    private val lock=Any()
    private var closed=false
    private var activation:Any?=null
    private var togglePending:Any?=null
    private var requestedActive=false

    val isRequestedActive:Boolean get()=synchronized(lock){!closed&&requestedActive}

    fun button(action:Int,enqueue:()->Boolean):Boolean {
        val token=synchronized(lock){
            if(closed)return false
            when(action){
                2->{
                    if(activation!=null)return true
                    Any().also{activation=it}
                }
                3->{activation=null;return true}
                else->return false
            }
        }
        var accepted=false
        var committed=false
        try{accepted=enqueue()}finally{
            synchronized(lock){
                if(!closed){
                    // A failed old enqueue must not clear a newer activation after action 3.
                    if(!accepted&&activation===token)activation=null
                    committed=accepted
                }
            }
        }
        return committed
    }

    /** Called by one ordered worker. The callback, including any Binder call, runs outside lock. */
    fun toggle(dispatch:(start:Boolean)->Boolean):Boolean=dispatchRequest(null,dispatch)

    /** An explicit local command shares the toggle worker's state, including repeated commands. */
    fun request(start:Boolean,dispatch:(Boolean)->Boolean):Boolean=dispatchRequest(start,dispatch)

    /** Reserve the ordered request before waiting for input setup. STOP skips preparation.
     * Preparation and dispatch run outside the state lock; close revokes a pending START. */
    suspend fun preparedRequest(explicitStart:Boolean?,prepare:suspend ()->Boolean,
        dispatch:(Boolean)->Boolean):Boolean {
        val operation=beginRequest(explicitStart)?:return false
        var accepted=false
        var committed=false
        try{
            if(operation.second&&!prepare())return false
            if(synchronized(lock){closed||togglePending!==operation.first})return false
            accepted=dispatch(operation.second)
        }finally{committed=finishRequest(operation,accepted)}
        return committed
    }

    private fun beginRequest(explicitStart:Boolean?):Pair<Any,Boolean>?=synchronized(lock){
        if(closed||togglePending!=null)return null
        val token=Any();togglePending=token
        token to (explicitStart?:!requestedActive)
    }

    private fun finishRequest(operation:Pair<Any,Boolean>,accepted:Boolean):Boolean=synchronized(lock){
        if(closed||togglePending!==operation.first)return false
        togglePending=null
        if(accepted)requestedActive=operation.second
        accepted
    }

    private fun dispatchRequest(explicitStart:Boolean?,dispatch:(Boolean)->Boolean):Boolean {
        val operation=beginRequest(explicitStart)?:return false
        var accepted=false
        var committed=false
        try{accepted=dispatch(operation.second)}finally{
            committed=finishRequest(operation,accepted)
        }
        return committed
    }

    override fun close(){synchronized(lock){
        closed=true;activation=null;togglePending=null
        requestedActive=false
    }}
}

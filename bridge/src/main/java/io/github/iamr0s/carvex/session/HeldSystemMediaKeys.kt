package io.github.iamr0s.carvex.session

/** Preserve media-button edges and release accepted holds when the session closes.
 * The receiving app decides seek behavior; this adapter introduces no repeat timer. */
class HeldSystemMediaKeys {
    private data class Hold(val started:Long,var users:Int=1)
    private val held=mutableMapOf<Int,Hold>()
    private var closed=false

    @Synchronized fun transition(code:Int,down:Boolean,at:Long,
        send:(Int,Long,Long,Boolean)->Boolean):Boolean {
        if(closed)return false
        val hold=held[code]
        if(down){
            // Different HID devices can hold the same usage concurrently. Their decoder
            // suppresses repeated unchanged reports before this queue receives the edges.
            if(hold!=null){hold.users++;return true}
            if(!send(code,at,at,true))return false
            held[code]=Hold(at)
        }else{
            if(hold==null)return true
            if(hold.users>1){hold.users--;return true}
            hold.users=0
            if(!send(code,hold.started,at,false))return false
            held.remove(code)
        }
        return true
    }

    @Synchronized fun close(at:Long,send:(Int,Long,Long,Boolean)->Boolean){
        if(closed)return
        closed=true
        for((code,hold) in held)runCatching{send(code,hold.started,at,false)}
        held.clear()
    }
}

package io.github.iamr0s.carvex.sessioncore

import io.github.iamr0s.carvex.pcm.PcmFormat
import kotlinx.coroutines.CancellationException
import kotlinx.coroutines.sync.Mutex

/** PCM requests and explicit negotiated bootstrap requests share one setup/ownership gate.
 * A failed category gets one bounded retry per activation after local backoff. Source completion
 * invalidates that activation, closes its transport and rejects late PCM until the next start.
 * A SETUP completing after source/session stop is discarded before installation. */
class AudioDemandGate(private val now:()->Long=System::nanoTime,
    private val retryDelayNs:Long=1_000_000_000L,private val maximumAttempts:Int=2):AutoCloseable {
    class Ticket internal constructor(val category:Int,val format:PcmFormat,val attempt:Int,val capturedAtNs:Long)
    private enum class State { PENDING,ACTIVE,FAILED }
    private data class Entry(val ticket:Ticket,var state:State=State.PENDING,
        var failedAtNs:Long=0,var transport:NegotiatedAudioTransport?=null)
    private val entries=mutableMapOf<Int,Entry>()
    private val inactive=mutableSetOf<Int>()
    private val preparationLocks=(1..3).associateWith{Mutex()}
    private var closed=false
    init{require(retryDelayNs>=0&&maximumAttempts in 1..2)}

    @Synchronized fun claim(category:Int,pcmBytes:Int,format:PcmFormat):Ticket? {
        if(closed||category !in 1..3||!format.accepts(pcmBytes))return null
        return claimSetup(category,format)
    }
    /** Explicit v11 bootstrap, after intersecting receiver capability with local encoders.
     * An empty host callback is still not a demand and cannot use this entry point. */
    @Synchronized fun prime(category:Int,format:PcmFormat):Ticket? {
        if(closed||category !in 1..3)return null
        return claimSetup(category,format)
    }
    private fun claimSetup(category:Int,format:PcmFormat):Ticket? {
        if(category in inactive)return null
        val current=entries[category]
        val time=now()
        if(current!=null){
            if(current.state==State.ACTIVE&&current.transport?.ready!=true){
                current.state=State.FAILED;current.failedAtNs=time
            }
            if(current.state!=State.FAILED||current.ticket.attempt>=maximumAttempts||
                time-current.failedAtNs<retryDelayNs)return null
        }
        val ticket=Ticket(category,format,(current?.ticket?.attempt?:0)+1,time)
        entries[category]=Entry(ticket)
        return ticket
    }

    @Synchronized private fun pending(ticket:Ticket)=!closed&&entries[ticket.category]?.let{
        it.ticket===ticket&&it.state==State.PENDING}==true

    /** Admit a captured first block only to its own activation. The callback must not suspend. */
    @Synchronized fun ifActive(ticket:Ticket,action:()->Unit):Boolean {
        val entry=entries[ticket.category]
        if(closed||entry?.ticket!==ticket||entry.state!=State.ACTIVE||entry.transport?.ready!=true)return false
        action()
        return true
    }

    /** Use explicit activity only for lanes whose stop means the stream has ended (navigation).
     * close() is local and nonblocking; it must begin protocol teardown before a new claim can run.
     * Unknown activity still allows the first PCM to request a stream. */
    @Synchronized fun sourceState(category:Int,active:Boolean){
        require(category in 1..3)
        if(closed)return
        if(active){inactive.remove(category);return}
        inactive.add(category)
        entries.remove(category)?.transport?.close()
    }

    /** Serialize creation AND installation across successive activations of a category. A stopped
     * SETUP must close its late result before the next activation attempts to reserve that stream. */
    suspend fun prepare(ticket:Ticket,create:suspend ()->NegotiatedAudioTransport,
        attach:suspend (NegotiatedAudioTransport)->Unit):Boolean {
        val lock=preparationLocks.getValue(ticket.category)
        lock.lock()
        try{
            if(!pending(ticket))return false
            return install(ticket,create(),attach)
        }catch(t:Exception){
            // A stopped activation can make attach fail its readiness check. It is not a new
            // stream failure, and must not overwrite the status of the next activation.
            val obsolete=synchronized(this){closed||entries[ticket.category]?.ticket!==ticket}
            if(t is CancellationException||!obsolete)throw t
            return false
        }finally{failed(ticket);lock.unlock()}
    }

    /** The install callback must itself reject a closed downstream owner (HostAudioBridge does).
     * Recheck afterwards so a concurrent close cannot leave an accepted live transport behind. */
    suspend fun install(ticket:Ticket,transport:NegotiatedAudioTransport,
        attach:suspend (NegotiatedAudioTransport)->Unit):Boolean {
        val installing=synchronized(this){
            if(!pending(ticket))false else {
                // Publish before attach suspends, so sourceState(false) can close an in-flight attach.
                entries.getValue(ticket.category).transport=transport
                true
            }
        }
        if(!installing){transport.close();return false}
        try{
            attach(transport)
            val accepted=synchronized(this){
                if(!pending(ticket))false else {
                    entries.getValue(ticket.category).apply{state=State.ACTIVE;this.transport=transport}
                    true
                }
            }
            if(!accepted)transport.close()
            return accepted
        }catch(t:Throwable){failed(ticket);runCatching{transport.close()};throw t}
    }

    @Synchronized fun failed(ticket:Ticket){
        val entry=entries[ticket.category]
        if(!closed&&entry!=null&&entry.ticket===ticket&&entry.state==State.PENDING){
            entry.state=State.FAILED;entry.failedAtNs=now()
        }
    }
    @Synchronized override fun close(){
        if(closed)return
        closed=true
        val transports=entries.values.mapNotNull{it.transport}.distinct()
        entries.clear();inactive.clear()
        transports.forEach{runCatching{it.close()}}
    }
}

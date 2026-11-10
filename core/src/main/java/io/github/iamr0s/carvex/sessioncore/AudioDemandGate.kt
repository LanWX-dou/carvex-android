package io.github.iamr0s.carvex.sessioncore

import io.github.iamr0s.carvex.pcm.PcmFormat
import kotlinx.coroutines.CancellationException
import kotlinx.coroutines.Deferred
import kotlinx.coroutines.sync.Mutex
import java.io.ByteArrayOutputStream

/** PCM requests and explicit negotiated bootstrap requests share one setup/ownership gate.
 * A failed category gets one bounded retry per activation after local backoff. Source completion
 * invalidates that activation, finishes/closes its transport and rejects late PCM until the next start.
 * A SETUP completing after source/session stop is discarded before installation. */
class AudioDemandGate(private val now:()->Long=System::nanoTime,
    private val retryDelayNs:Long=1_000_000_000L,private val maximumAttempts:Int=2,
    private val log:(String)->Unit={}):AutoCloseable {
    class Ticket internal constructor(val category:Int,val format:PcmFormat,val attempt:Int,val capturedAtNs:Long)
    private enum class State { PENDING,ACTIVE,FAILED }
    private class BufferedPcm(val format:PcmFormat){val bytes=ByteArrayOutputStream()}
    private data class Entry(val ticket:Ticket,var state:State=State.PENDING,
        var failedAtNs:Long=0,var transport:NegotiatedAudioTransport?=null,
        val buffered:MutableList<BufferedPcm> = mutableListOf(),var bufferedBytes:Int=0,
        var overflow:Boolean=false)
    private val entries=mutableMapOf<Int,Entry>()
    private val inactive=mutableSetOf<Int>()
    private data class Finishing(val transport:NegotiatedAudioTransport,val done:Deferred<Unit>)
    private val finishing=mutableMapOf<Int,Finishing>()
    private val preparationLocks=(1..3).associateWith{Mutex()}
    private var closed=false
    init{require(retryDelayNs>=0&&maximumAttempts in 1..2)}

    @Synchronized fun claim(category:Int,pcmBytes:Int,format:PcmFormat):Ticket? {
        if(closed||category !in 1..3||!format.accepts(pcmBytes))return null
        return claimSetup(category,format)
    }
    /** Local navigation startup buffer. No wire timing is inferred from this memory bound.
     * Returns a ticket only for a new SETUP; all PCM is handled here, including revoked demand.
     * Forward must enqueue without suspending. It runs under the gate so live PCM cannot overtake
     * the startup prefix. Source stop/failure/close discards the entire pending activation. */
    @Synchronized fun receiveNavigation(pcm:ByteArray,format:PcmFormat,
        forward:(ByteArray,Int,PcmFormat)->Unit):Ticket? {
        if(closed||!format.accepts(pcm.size))return null
        val ticket=claimSetup(2,format)
        val entry=entries[2]?:return ticket
        if(entry.state==State.ACTIVE){forward(pcm,2,format);return ticket}
        if(entry.state!=State.PENDING)return ticket
        // At most one maximum host PCM block in bytes, and at most eight format segments.
        // Coalesce adjacent blocks of the same format so replay does not flood the bridge queue.
        val previous=entry.buffered.lastOrNull()?.takeIf{it.format==format}
        if(entry.overflow||entry.bufferedBytes+pcm.size>32768||previous==null&&entry.buffered.size>=8){
            if(!entry.overflow)log("Navigation startup buffer full bytes=${entry.bufferedBytes}; dropping subsequent pending PCM")
            entry.overflow=true
            return ticket
        }
        val segment=previous?:BufferedPcm(format).also{entry.buffered.add(it)}
        segment.bytes.write(pcm)
        entry.bufferedBytes+=pcm.size
        return ticket
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
     * An installed stream may finish accepted audio asynchronously; the next prepare waits for it.
     * Pending installation and abort paths still close immediately.
     * Unknown activity still allows the first PCM to request a stream. */
    @Synchronized fun sourceState(category:Int,active:Boolean,
        finish:((NegotiatedAudioTransport)->Deferred<Unit>)?=null){
        require(category in 1..3)
        if(closed)return
        if(active){inactive.remove(category);return}
        inactive.add(category)
        val entry=entries.remove(category)?:return
        val transport=entry.transport?:return
        if(entry.state==State.ACTIVE&&finish!=null)finishing[category]=Finishing(transport,finish(transport))
        else transport.close()
    }

    /** After revoking a source, wait until any in-flight creation has closed its stale result.
     * The caller must keep new demand gated while transitioning to another stream purpose. */
    suspend fun awaitPreparation(category:Int){
        val lock=preparationLocks.getValue(category)
        lock.lock();lock.unlock()
    }

    /** Serialize creation AND installation across successive activations of a category. A stopped
     * SETUP must close its late result before the next activation attempts to reserve that stream. */
    suspend fun prepare(ticket:Ticket,create:suspend ()->NegotiatedAudioTransport,
        attach:suspend (NegotiatedAudioTransport)->Unit):Boolean = prepare(ticket,create,attach,null)
    suspend fun prepare(ticket:Ticket,create:suspend ()->NegotiatedAudioTransport,
        attach:suspend (NegotiatedAudioTransport)->Unit,
        replay:((ByteArray,Int,PcmFormat)->Unit)?):Boolean {
        val lock=preparationLocks.getValue(ticket.category)
        lock.lock()
        try{
            val retiring=synchronized(this){finishing[ticket.category]}
            if(retiring!=null){
                retiring.done.await()
                synchronized(this){if(finishing[ticket.category]===retiring)finishing.remove(ticket.category)}
            }
            if(!pending(ticket))return false
            return install(ticket,create(),attach,replay)
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
        attach:suspend (NegotiatedAudioTransport)->Unit):Boolean = install(ticket,transport,attach,null)
    suspend fun install(ticket:Ticket,transport:NegotiatedAudioTransport,
        attach:suspend (NegotiatedAudioTransport)->Unit,
        replay:((ByteArray,Int,PcmFormat)->Unit)?):Boolean {
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
                    val entry=entries.getValue(ticket.category)
                    if(entry.buffered.isNotEmpty()){
                        val deliver=requireNotNull(replay){"Pending PCM requires an installation replay callback"}
                        for(segment in entry.buffered){
                            if(!pending(ticket))break
                            deliver(segment.bytes.toByteArray(),ticket.category,segment.format)
                        }
                        log("Navigation startup replay bytes=${entry.bufferedBytes} overflow=${entry.overflow}")
                        entry.buffered.clear();entry.bufferedBytes=0
                    }
                    if(!pending(ticket))false else {
                        entry.state=State.ACTIVE;entry.transport=transport
                        true
                    }
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
            entry.buffered.clear();entry.bufferedBytes=0
        }
    }
    @Synchronized override fun close(){
        if(closed)return
        closed=true
        val transports=(entries.values.mapNotNull{it.transport}+finishing.values.map{it.transport}).distinct()
        finishing.values.forEach{it.done.cancel()};finishing.clear()
        entries.clear();inactive.clear()
        transports.forEach{runCatching{it.close()}}
    }
}

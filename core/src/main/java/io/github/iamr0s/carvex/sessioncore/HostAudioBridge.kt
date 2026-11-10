package io.github.iamr0s.carvex.sessioncore
import io.github.iamr0s.carvex.pcm.PcmFormat
import io.github.iamr0s.carvex.pcm.Pcm16Converter
import kotlinx.coroutines.*
import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.sync.Mutex
import java.util.concurrent.atomic.*

/** Only established streams. Each transport owns its crypto, clock and unblocking close. */
interface NegotiatedAudioTransport:AutoCloseable {
    val ready:Boolean
    val formats:Map<Int,PcmFormat>
    val microphoneFormat:PcmFormat?
    val microphoneReady:Boolean get()=ready&&microphoneFormat!=null
    suspend fun send(category:Int,pcm:ByteArray,format:PcmFormat)
    /** Natural source completion. Abort/disconnect uses close() instead. */
    suspend fun finish(){close()}
    /** 已发出的 RTP 包数与最后一包的单调时刻（纳秒）；心跳用它判断哪条流停了。 */
    val packetsSent:Long get()=0
    val lastPacketNanos:Long get()=0
}
/** A configured microphone receiver must revoke readiness when its network/decoder worker exits. */
interface MicrophoneInput:AutoCloseable { val ready:Boolean }

/** Callback arrival is observed after the current PCM block has accumulated.
 * A 120 ms block arriving every 120 ms is continuous, not a >100 ms outage.
 * Keep queue freshness separate from source cadence and converter phase. */
internal fun pcmCallbackHasGap(previousNanos:Long?,currentNanos:Long,format:PcmFormat,bytes:Int):Boolean {
    require(format.accepts(bytes))
    val durationNanos=(bytes/(format.channels*2)).toLong()*1_000_000_000L/format.rate
    return previousNanos!=null&&currentNanos-previousNanos>durationNanos+100_000_000L
}

class HostAudioBridge(private val log:(String)->Unit,private val configureRoute:(suspend ()->Unit)?=null):AutoCloseable {
    data class Snapshot(val received:Long,val dropped:Long,val forwardedBytes:Long,val microphoneBytes:Long)
    private class Binding(val transport:NegotiatedAudioTransport,val formats:Map<Int,PcmFormat>,val mic:PcmFormat?){
        @Volatile var finishing=false
        var finishJob:Deferred<Unit>?=null
        val drained=CompletableDeferred<Unit>()
    }
    private sealed interface Work
    private data class Block(val pcm:ByteArray,val format:PcmFormat,val binding:Binding,val queuedAt:Long):Work
    private data class End(val binding:Binding):Work
    private val active=AtomicReference<Map<Int,Binding>>(emptyMap())
    private val micReceiver=AtomicReference<Pair<MicrophoneInput,PcmFormat>?>(null)
    private val closed=AtomicBoolean(false)
    private val received=AtomicLong();private val dropped=AtomicLong();private val forwarded=AtomicLong();private val microphoneBytes=AtomicLong()
    /** 抓包诊断：每类 host PCM 的块数/字节与 5 秒节流摘要，用来判断“同一声音到底走了哪一类”。 */
    private val rxBlocks=IntArray(4);private val rxBytes=LongArray(4);private val rxLastLogNs=LongArray(4)
    private val lastPcmNanos=AtomicLongArray(4)
    private val observedHostState=AtomicIntegerArray(IntArray(4){Int.MIN_VALUE})
    private val firstPcmObserved=AtomicIntegerArray(4)
    private val routeLock=Mutex()
    private val scope=CoroutineScope(SupervisorJob()+Dispatchers.IO)
    private val queues=(1..3).associateWith{Channel<Work>(8)}
    /** Host-side per-category activity: 1 is treated as active because the source is observed to stop during 0. */
    private val hostActive=(1..3).associateWith{AtomicBoolean(true)}
    @Volatile private var host:CastHost?=null
    fun bindHost(value:CastHost){check(!closed.get());host=value}
    private fun remove(binding:Binding){
        active.updateAndGet{routes->routes.filterValues{it!==binding}}
        runCatching{binding.transport.close()}
    }
    init{for((category,queue) in queues)scope.launch{
        var converter:Pcm16Converter?=null
        var previous:Binding?=null
        var lastArrival:Long?=null
        for(work in queue){
            if(work is End){
                try{
                    withTimeout(5000){
                        if(active.get()[category]===work.binding&&work.binding.transport.ready)work.binding.transport.finish()
                    }
                    work.binding.drained.complete(Unit)
                }catch(t:Exception){
                    work.binding.drained.completeExceptionally(t)
                    currentCoroutineContext().ensureActive()
                }
                converter=null;previous=null;lastArrival=null
                continue
            }
            val block=work as Block
            val now=System.nanoTime()
            if(closed.get()||active.get()[category]!==block.binding||!block.binding.transport.ready||now-block.queuedAt>100_000_000L){
                dropped.incrementAndGet();converter=null;continue
            }
            try{
                val target=block.binding.formats.getValue(category)
                if(previous!==block.binding||converter?.source!=block.format||
                    pcmCallbackHasGap(lastArrival,block.queuedAt,block.format,block.pcm.size)){
                    converter=Pcm16Converter(block.format,target);previous=block.binding
                    log("${"Audio category="}${category}${" PCM source="}${block.format.rate}${"/"}${block.format.channels}${" target="}${target.rate}${"/"}${target.channels}${"; independent lane"}")
                }
                lastArrival=block.queuedAt
                val converted=requireNotNull(converter).convert(block.pcm)
                val limit=(32768/(target.channels*2))*(target.channels*2)
                var offset=0
                while(offset<converted.size){
                    val end=minOf(offset+limit,converted.size)
                    // convert() already handed us a fresh array; slicing the single-packet case
                    // (the normal one) would copy the whole block again for nothing.
                    val slice=if(offset==0&&end==converted.size)converted else converted.copyOfRange(offset,end)
                    block.binding.transport.send(category,slice,target)
                    forwarded.addAndGet((end-offset).toLong());offset=end
                }
            }catch(t:CancellationException){throw t}
            catch(t:Exception){
                if(active.get()[category]===block.binding){
                    log("${"Audio category="}${category}${" degraded: "}"+t.javaClass.simpleName+" "+(t.message?:"")+"; other audio/video retained")
                    remove(block.binding)
                }
                dropped.incrementAndGet();converter=null
            }
        }
    }}
    /** Merge established categories. Attaching alternate audio must not close main audio. */
    suspend fun attach(transport:NegotiatedAudioTransport){
        routeLock.lock()
        var binding:Binding?=null
        var previous:Map<Int,Binding> = emptyMap()
        try{
            check(!closed.get()&&transport.ready){"Audio stream not ready"}
            val formats=transport.formats.toMap()
            require(formats.isNotEmpty()&&formats.keys.all{it in 1..3})
            val next=Binding(transport,formats,transport.microphoneFormat)
            val h=host
            check(h!=null||configureRoute!=null){"Host not bound"}
            if(active.get().values.any{it.transport===transport})return
            binding=next
            active.updateAndGet{routes->previous=routes;routes+formats.keys.associateWith{next}}
            if(configureRoute!=null)configureRoute.invoke() else requireNotNull(h).selectCarLifePlusAudio()
            check(!closed.get()&&transport.ready&&formats.keys.all{active.get()[it]===next})
            val retained=active.get().values.map{it.transport}.toSet()
            previous.values.distinct().filter{it.transport !in retained}.forEach{runCatching{it.transport.close()}}
            log("${"CarWith audio categories="}${active.get().keys.sorted()}${" configured; audible acceptance pending"}")
        }catch(t:Throwable){
            binding?.let{failed->active.updateAndGet{routes->
                if(closed.get())emptyMap() else routes.toMutableMap().apply{
                    for(category in failed.formats.keys)if(get(category)===failed){
                        val old=previous[category]
                        if(old!=null&&old.transport.ready)put(category,old) else remove(category)
                    }
                }
            }}
            if(closed.get())previous.values.distinct().forEach{runCatching{it.transport.close()}}
            runCatching{transport.close()};throw t
        }finally{routeLock.unlock()}
    }
    fun categories():Set<Int> = active.get().filterValues{it.transport.ready}.keys
    /** Enqueue completion behind accepted blocks. Revocation is synchronous; Binder never waits
     * for the encoder/network. A local timeout bounds a faulty drain, not normal playback timing. */
    fun finish(transport:NegotiatedAudioTransport):Deferred<Unit> {
        val binding=active.get().values.firstOrNull{it.transport===transport}
            ?:return CompletableDeferred(Unit).also{transport.close()}
        require(binding.formats.size==1){"Natural completion requires an independent lane"}
        synchronized(binding){
            binding.finishJob?.let{return it}
            binding.finishing=true
            val category=binding.formats.keys.single()
            val job=scope.async(start=CoroutineStart.LAZY){
                val began=System.nanoTime()
                try{
                    withTimeout(5000){queues.getValue(category).send(End(binding));binding.drained.await()}
                    log("Audio finish category=$category phase=drained elapsedMs="+(System.nanoTime()-began)/1_000_000)
                }catch(t:TimeoutCancellationException){
                    log("Audio finish category=$category phase=timeout; closing stream")
                }catch(t:Exception){
                    currentCoroutineContext().ensureActive()
                    log("Audio finish category=$category phase=failed error="+t.javaClass.simpleName)
                }finally{remove(binding)}
            }
            binding.finishJob=job;job.start()
            return job
        }
    }
    fun testFormat(category:Int):PcmFormat?=active.get()[category]?.takeIf{it.transport.ready}?.formats?.get(category)
    suspend fun sendTest(category:Int,pcm:ByteArray,format:PcmFormat):Boolean {
        val binding=active.get()[category]?:return false
        if(closed.get()||!binding.transport.ready||binding.formats[category]!=format)return false
        binding.transport.send(category,pcm,format)
        return true
    }
    fun musicSampleRate():Int=active.get()[1]?.takeIf{it.transport.ready}?.formats?.get(1)?.rate?:48000
    private fun microphoneBinding():Binding?=active.get().values.distinct().filter{it.transport.microphoneReady&&it.mic!=null}.singleOrNull()
    fun microphoneReady():Boolean=!closed.get()&&(micReceiver.get()?.first?.ready==true||microphoneBinding()!=null)
    suspend fun attachMicrophone(receiver:MicrophoneInput,format:PcmFormat){
        routeLock.lock();try{check(!closed.get()&&receiver.ready){"Microphone receiver not ready"};micReceiver.getAndSet(receiver to format)?.first?.close();log("${"CarWith microphone receiver configured format="}${format.rate}${"/"}${format.channels}")}finally{routeLock.unlock()}
    }
    /** Binder callback performs no conversion or network operation. Stale data cannot cross bindings. */
    fun receive(pcm:ByteArray,category:Int,format:PcmFormat){
        if(closed.get())return
        require(category in 1..3&&format.accepts(pcm.size))
        received.incrementAndGet()
        val binding=active.get()[category]
        if(firstPcmObserved.compareAndSet(category,0,1)){
            log("Audio source first category=$category monoNs="+System.nanoTime()+
                " bytes="+pcm.size+" source="+format.rate+"/"+format.channels+
                " attached="+(binding!=null)+" ready="+(binding?.transport?.ready==true)+
                "; callback observed before queue admission")
        }
        if(binding==null||binding.finishing||!binding.transport.ready){dropped.incrementAndGet();return}
        val queue=queues.getValue(category)
        // A fresh callback's duration is not its queue age. In particular, the host
        // supplies 120 ms speech blocks: clipping each to 100 ms loses 1/6 of speech.
        // PcmFormat already bounds each allocation to 32768 bytes; the eight-slot
        // queue and dequeue freshness check still bound memory and stale backlog.
        val block=Block(pcm.copyOf(),format,binding,System.nanoTime())
        val now=System.nanoTime()
        val previousPcm=lastPcmNanos.getAndSet(category,now)
        if(previousPcm==0L||now-previousPcm>200_000_000L){
            log("Audio source category=$category monoNs=$now blockMs="+
                (block.pcm.size.toLong()*1000/(format.rate*format.channels*2))+" sourceGapMs="+
                (if(previousPcm==0L)"none" else ((now-previousPcm)/1_000_000).toString())+
                "; source callback time, not capture or speaker time")
        }
        rxBlocks[category]++;rxBytes[category]+=block.pcm.size
        if(rxBlocks[category]==1||now-rxLastLogNs[category]>5_000_000_000L){
            rxLastLogNs[category]=now
            val target=binding.formats.getValue(category)
            log("Audio host category="+category+" blocks="+rxBlocks[category]+" bytes="+rxBytes[category]+
                " source="+format.rate+"/"+format.channels+" target="+target.rate+"/"+target.channels+
                "; this is the host lane that decides speech vs media")
        }
        synchronized(binding){
        if(binding.finishing){dropped.incrementAndGet();return}
        if(queue.trySend(block).isFailure){
            // Keep newest source audio when overloaded; never build an unbounded latency backlog.
            if(queue.tryReceive().isSuccess)dropped.incrementAndGet()
            if(queue.trySend(block).isFailure)dropped.incrementAndGet()
        }
        }
    }
    /** Host state never invents silence and never discards a live source; it only drops blocks the source already stopped producing. */
    fun state(category:Int,state:Int){
        if(closed.get())return
        val flag=hostActive[category]?:return
        val active=state==1
        // The first state=1 is still evidence of a source activation even though the
        // existing default is active. Observe it without changing pause semantics.
        if(observedHostState.getAndSet(category,state)!=state){
            log("Audio host state observed category=$category state=$state monoNs="+System.nanoTime()+
                " attached="+(this.active.get()[category]!=null)+
                "; host callback, not receiver playback confirmation")
        }
        if(flag.getAndSet(active)==active)return
        log("${"CarWith audio category="}${category}${" host state="}${state}${" -> "}"+(if(active)"resume" else "pause")+"; source stops during 0, no local silence inserted")
        if(!active&&this.active.get()[category]?.finishing!=true)
            while(queues.getValue(category).tryReceive().isSuccess)dropped.incrementAndGet()
        val now=System.nanoTime()
        val lastPcm=lastPcmNanos.get(category)
        val transport=this.active.get()[category]?.transport
        val lastSent=transport?.lastPacketNanos?:0L
        log("Audio state timing category=$category state=$state monoNs=$now lastPcmAgeMs="+
            (if(lastPcm==0L)"none" else ((now-lastPcm)/1_000_000).toString())+
            " packets="+(transport?.packetsSent?:0)+" lastSendMonoNs=$lastSent; receiver buffered audio not measured")
    }
    suspend fun microphone(pcm:ByteArray,format:PcmFormat):Boolean {
        routeLock.lock()
        try{
            val independent=micReceiver.get()
            val binding=microphoneBinding()
            if(closed.get()||!format.accepts(pcm.size))return false
            if(independent!=null&&independent.first.ready&&independent.second==format){
                val accepted=host?.microphone(pcm,format.rate,format.channels,format.encoding)==true
                if(accepted)microphoneBytes.addAndGet(pcm.size.toLong())
                return accepted
            }
            val receiver=binding?:return false
            if(receiver.mic!=format)return false
            val accepted=host?.microphone(pcm,format.rate,format.channels,format.encoding)==true
            if(accepted)microphoneBytes.addAndGet(pcm.size.toLong())
            return accepted
        }finally{routeLock.unlock()}
    }
    fun snapshot()=Snapshot(received.get(),dropped.get(),forwarded.get(),microphoneBytes.get())
    override fun close(){
        if(!closed.compareAndSet(false,true))return
        active.getAndSet(emptyMap()).values.distinct().forEach{runCatching{it.transport.close()}}
        micReceiver.getAndSet(null)?.first?.let{runCatching{it.close()}}
        queues.values.forEach{it.cancel()};scope.cancel();host=null
    }
}

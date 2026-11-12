package io.github.iamr0s.carvex.carplay.core

/** accessoryd 24A446: 0x10006c034 setup, 0x10006c1b0 data, 0x1001461c0 reference. */
object ArtworkFileWire {
    const val MAX_BYTES=512*1024
    fun reference(id:Int)=listOf(0 to IapWire.fields(listOf(0x1a to byteArrayOf(id.toByte()))))
    fun setup(id:Int,size:Int,version:Int):ByteArray {
        require(id in 128..255&&size in 0..MAX_BYTES&&version in 1..2)
        return byteArrayOf(id.toByte(),4)+IapWire.be64(size.toLong())+
            if(version==2)IapWire.be16(2) else byteArrayOf()
    }
    fun chunk(id:Int,bytes:ByteArray,offset:Int,maximumPayload:Int):ByteArray {
        require(id in 128..255&&offset in 0..bytes.size&&maximumPayload>=12)
        val end=minOf(bytes.size,offset+maximumPayload-2)
        val flags=(if(offset==0)0x80 else 0) or (if(end==bytes.size)0x40 else 0)
        return byteArrayOf(id.toByte(),flags.toByte())+bytes.copyOfRange(offset,end)
    }
    fun control(id:Int,operation:Int)=byteArrayOf(id.toByte(),operation.toByte())
}

/** One image per subscriber. Link ACK and file Start/Success are separate events.
 * Limits and timeout are local resource bounds, not new protocol retry rules. */
class NowPlayingArtwork(
    private val session:()->Pair<Int,Int>?,
    private val announce:(List<Pair<Int,ByteArray>>,()->Boolean,(Throwable?)->Unit)->Boolean,
    private val send:(ByteArray,()->Boolean,(Throwable?)->Unit)->Boolean,
    private val log:(String)->Unit={},
    private val now:()->Long=System::nanoTime,
) : AutoCloseable {
    private enum class Phase { ANNOUNCING, SETUP, SENDING, PAUSED, RESULT }
    private class Transfer(val id:Int,val data:ByteArray,val version:Int,val mtu:Int,var touched:Long) {
        var phase=Phase.ANNOUNCING
        var offset=0
        var inFlight=false
    }
    private var closed=false
    @Volatile private var ready=false
    @Volatile private var subscribed=false
    private var image:ByteArray?=null
    @Volatile private var current:Transfer?=null
    private val retired=mutableSetOf<Int>()
    private var nextId=128
    @Volatile private var epoch=0L

    @Synchronized fun linkReady(value:Boolean) {
        if(closed)return
        // Old callbacks are isolated by object identity even when buffer IDs are reused on a new link.
        epoch++;ready=value;subscribed=false;current=null;retired.clear();nextId=128
    }
    @Synchronized fun subscribe(value:Boolean) {
        if(closed)return
        cancelCurrent()
        subscribed=value
        if(value)start()
    }
    @Synchronized fun update(bytes:ByteArray) {
        if(closed)return
        require(bytes.size<=ArtworkFileWire.MAX_BYTES)
        if(image?.contentEquals(bytes)==true)return
        image=bytes.copyOf()
        cancelCurrent()
        start()
    }
    private fun start() {
        if(!ready||!subscribed||current!=null)return
        val data=image?:return
        val info=session()?:run{log("Artwork unavailable: no supported file session");return}
        if(info.first !in 1..2||info.second<12)return
        val id=(0 until 128).map{128+((nextId-128+it)%128)}.firstOrNull{it !in retired}
            ?:run{log("Artwork deferred: cancelled transfer IDs still pending");return}
        nextId=128+((id-127)%128)
        val transfer=Transfer(id,data,info.first,minOf(info.second,4096),now())
        current=transfer
        val accepted=announce(ArtworkFileWire.reference(id),{isCurrent(transfer)}){error->synchronized(this){
            if(current!==transfer)return@synchronized
            if(error!=null){abort(transfer,"reference failed");return@synchronized}
            transfer.phase=Phase.SETUP;transfer.inFlight=true;transfer.touched=now()
            val queued=send(ArtworkFileWire.setup(id,data.size,transfer.version),{isCurrent(transfer)}){failure->synchronized(this){
                if(current!==transfer)return@synchronized
                transfer.inFlight=false
                if(failure!=null)abort(transfer,"setup failed") else pump(transfer)
            }}
            if(!queued)abort(transfer,"setup not queued")
        }}
        if(!accepted)abort(transfer,"reference not queued")
        else log("Artwork reference queued id=$id bytes=${data.size} version=${info.first}")
    }
    // Writer callbacks must never acquire the artwork monitor while holding Link locks.
    private fun isCurrent(transfer:Transfer)=ready&&subscribed&&current===transfer
    private fun pump(transfer:Transfer) {
        if(current!==transfer||transfer.inFlight||transfer.phase!=Phase.SENDING)return
        val bytes=ArtworkFileWire.chunk(transfer.id,transfer.data,transfer.offset,transfer.mtu)
        transfer.offset+=bytes.size-2
        if(transfer.offset==transfer.data.size)transfer.phase=Phase.RESULT
        transfer.inFlight=true;transfer.touched=now()
        val queued=send(bytes,{isCurrent(transfer)}){error->synchronized(this){
            if(current!==transfer)return@synchronized
            transfer.inFlight=false;transfer.touched=now()
            if(error!=null)abort(transfer,"data failed") else pump(transfer)
        }}
        if(!queued)abort(transfer,"data not queued")
    }
    @Synchronized fun receive(bytes:ByteArray) {
        if(!ready||bytes.size!=2)return
        val id=bytes[0].toInt() and 255
        val operation=bytes[1].toInt() and 255
        if(operation==2&&retired.remove(id))return
        val transfer=current?.takeIf{it.id==id}?:return
        transfer.touched=now()
        when(operation){
            1->if(transfer.phase in setOf(Phase.SETUP,Phase.PAUSED)){
                transfer.phase=Phase.SENDING;pump(transfer)
            }
            2->{
                current=null
                retired.add(id)
                val observedEpoch=epoch
                send(ArtworkFileWire.control(id,2),{sameEpoch(observedEpoch)}){error->synchronized(this){
                    if(error==null&&epoch==observedEpoch)retired.remove(id)
                }}
                log("Artwork cancelled by receiver id=$id")
            }
            3->if(transfer.phase==Phase.SENDING){
                transfer.phase=Phase.PAUSED
                send(ArtworkFileWire.control(id,3),{isCurrent(transfer)}){}
            }
            5,6->if(transfer.phase==Phase.RESULT){
                current=null
                log("Artwork transfer id=$id result="+if(operation==5)"accepted" else "rejected")
            }
        }
    }
    /** A missing receiver response must not retain a bitmap or block later songs indefinitely. */
    @Synchronized fun expire() {
        current?.takeIf{now()-it.touched>30_000_000_000L}?.let{abort(it,"response timeout")}
    }
    private fun abort(transfer:Transfer,reason:String) {
        if(current!==transfer)return
        log("Artwork id=${transfer.id} $reason")
        cancelCurrent()
    }
    private fun cancelCurrent() {
        val old=current?:return
        current=null
        retired.add(old.id)
        val observedEpoch=epoch
        if(ready)send(ArtworkFileWire.control(old.id,2),{sameEpoch(observedEpoch)}){}
    }
    private fun sameEpoch(value:Long)=ready&&epoch==value
    @Synchronized override fun close() {
        if(closed)return
        closed=true;ready=false;subscribed=false;epoch++;current=null;image=null;retired.clear()
    }
}

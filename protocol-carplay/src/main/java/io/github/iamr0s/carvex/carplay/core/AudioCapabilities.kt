package io.github.iamr0s.carvex.carplay.core
import io.github.iamr0s.carvex.pcm.PcmFormat

/** Receiver /info announcements, not a network transport contract. Preserve stream/audio type. */
object AudioCapabilities {
    data class Entry(val streamType:Int,val audioType:String?,val inputMask:Long?,val outputMask:Long?,
        val manufacturer:String?=null,val outputFormatsExtended:List<Any?>?=null,
        val outputFormatsExtendedValid:Boolean=true,val valid:Boolean=true)
    data class MatchedFormats(val mask:Long,val extended:List<Any?>?,val fallback:Boolean,val index:Int?)
    data class Candidate(val entry:Entry,val formatBit:Long,val pcm:PcmFormat)
    private val pcm16=mapOf(
        0x4L to PcmFormat(8000,1),0x8L to PcmFormat(8000,2),
        0x10L to PcmFormat(16000,1),0x20L to PcmFormat(16000,2),
        0x40L to PcmFormat(24000,1),0x80L to PcmFormat(24000,2),
        0x100L to PcmFormat(32000,1),0x200L to PcmFormat(32000,2),
        0x400L to PcmFormat(44100,1),0x800L to PcmFormat(44100,2),
        0x4000L to PcmFormat(48000,1),0x8000L to PcmFormat(48000,2))
    private fun integer(value:Any?):Long? {
        if(value !is Number)return null
        if(value is Double||value is Float){
            val d=value.toDouble();if(!d.isFinite()||d<0||d>=Long.MAX_VALUE.toDouble())return null
            val n=d.toLong();return n.takeIf{it.toDouble()==d}
        }
        return value.toLong().takeIf{it>=0}
    }
    fun parse(value:Any?,log:(String)->Unit={},manufacturer:String?=null):List<Entry> {
        if(value==null){log("INFO audioFormats absent");return emptyList()}
        val items=value as? List<*>?:run{log("INFO audioFormats invalid container");return emptyList()}
        if(items.size>256){log("INFO audioFormats exceeds local parser budget 256");return emptyList()}
        val result=mutableListOf<Entry>()
        for((index,item) in items.withIndex()){
            // A malformed row cannot be removed: doing so changes which later row can win.
            val map=item as? Map<*,*>
            if(map==null){
                log("INFO audio row $index invalid dictionary")
                result.add(Entry(0,null,null,null,manufacturer,valid=false))
                continue
            }
            val type=integer(map["type"])?.takeIf{it<=Int.MAX_VALUE}?.toInt()
            if(type==null){
                log("INFO audio row $index invalid type")
                result.add(Entry(0,null,null,null,manufacturer,valid=false))
                continue
            }
            val purpose=map["audioType"]
            // The original typed getter has no error output here: non-strings become NULL.
            val audioType=purpose as? String
            val input=integer(map["audioInputFormats"]);val output=integer(map["audioOutputFormats"])
            val extended=map["audioOutputFormatsExtended"]
            log("${"INFO audio #"}${index}${" streamType="}${type}${" audioType="}"+(audioType?:"unknown")+" inputMask="+(input?.toString(16)?:"unknown")+" outputMask="+(output?.toString(16)?:"unknown"))
            result.add(Entry(type,audioType,input,output,manufacturer,(extended as? List<*>)?.toList(),
                !map.containsKey("audioOutputFormatsExtended")||extended is List<*>))
        }
        return result.takeIf{rows->rows.any{it.valid}}?:emptyList()
    }
    /** 24A446 0x251adc470..0x251adc6a8: stop on the first anonymous/exact row, even at zero.
     * Extended values are preserved as opaque values; their complete schema is still OPEN. */
    fun formatsFor(entries:List<Entry>,type:Int,purpose:String,input:Boolean):MatchedFormats? {
        var priorDefault=0L
        var selected=0L
        var anonymous=false
        var match:Int?=null
        var extended:List<Any?>?=null
        for((index,entry) in entries.withIndex()){
            if(!entry.valid)return null
            if(entry.streamType!=type)continue
            if(entry.audioType==null||entry.audioType==purpose){
                if(!entry.outputFormatsExtendedValid)return null
                selected=(if(input)entry.inputMask else entry.outputMask)?:0L
                extended=entry.outputFormatsExtended?.toList()
                anonymous=entry.audioType==null
                match=index
                break
            }
            if(entry.audioType=="default"){
                val defaultInput=type==100||type==107
                priorDefault=(if(defaultInput)entry.inputMask else entry.outputMask)?:0L
            }
        }
        if(selected==0L&&priorDefault!=0L&&entries.firstOrNull()?.manufacturer?.startsWith("Apple")==true){
            selected=priorDefault
            anonymous=true
        }
        return MatchedFormats(selected,extended,anonymous,match)
    }
    /** Output is receiver playback, input is receiver capture per supplied guide; no stream-type guessing. */
    fun playback(entries:List<Entry>,format:PcmFormat):List<Candidate> = entries.flatMap{entry->
        pcm16.filter{(bit,pcm)->pcm==format&&entry.outputMask?.let{it and bit!=0L}==true}
            .map{(bit,pcm)->Candidate(entry,bit,pcm)}
    }
    fun capture(entries:List<Entry>):List<Candidate> = entries.flatMap{entry->
        pcm16.filter{(bit,_)->entry.inputMask?.let{it and bit!=0L}==true}
            .map{(bit,pcm)->Candidate(entry,bit,pcm)}
    }
}

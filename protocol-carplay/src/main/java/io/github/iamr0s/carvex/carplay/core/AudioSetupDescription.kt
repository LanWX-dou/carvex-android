package io.github.iamr0s.carvex.carplay.core

/** SETUP fields follow the transports actually prepared for this stream.
 * Latency policy and capture clock mapping remain independently OPEN. */
object AudioSetupDescription {
    /** 24A446 0x2519be158..0x2519be19c: only raw102 creates output control. */
    fun outputControlTransportRequired(streamType:Int):Boolean {
        require(streamType in 100..102)
        return streamType==102
    }
    fun playback(route:CarPlayAudioPlan.Route,format:CarPlayAudioPlan.Format,connectionId:Long,
        controlPort:Int?=null,inputPort:Int?=null,offerRedundancy:Boolean=route.type!=102):Map<String,Any> {
        require(controlPort==null||controlPort in 1..65535)
        require(inputPort==null||inputPort in 1..65535)
        return linkedMapOf<String,Any>(
            "type" to route.type,"audioType" to route.purpose,"audioFormat" to format.bit,
            "streamConnectionID" to connectionId,"audioLatencyMs" to 100,
            "supportsHighAccuracyTimestamps" to true
        ).apply {
            // 0x2519be8ac..0x2519be8d8 writes both fields only for a positive control port.
            if(controlPort!=null){
                put("controlPort",controlPort)
                put("spf",if(format.codec==CarPlayAudioPlan.Codec.PCM16)format.rate/200 else format.framesPerPacket)
            }
            // 24A446 only offers RED on eligible wireless raw100/raw101 streams.
            // A future USB caller must pass false explicitly.
            if(offerRedundancy)put("supportsRTPPacketRedundancy",true)
            if(inputPort!=null){put("input",true);put("dataPort",inputPort)}
        }
    }
}

package io.github.iamr0s.carvex.carplay.core

/** Main/telephony input: WWDC 2016/723; 24A446 format-key branch 0x251adc96c.
 * Receiver declaration and a real local decoder are both required. */
object CallMicrophonePlan {
    val route=CarPlayAudioPlan.telephony
    fun select(entries:List<AudioCapabilities.Entry>,decodable:(CarPlayAudioPlan.Format)->Boolean):CarPlayAudioPlan.Format? =
        CarPlayAudioPlan.advertised(entries,route,capture=true)
            .filter{CarPlayAudioPlan.wireSupported(route,it)}
            .sortedWith(compareBy({CarPlayAudioPlan.codecPriority(it.codec)},{it.channels},{-it.rate}))
            .firstOrNull(decodable)
    fun description(format:CarPlayAudioPlan.Format,id:Long,port:Int):Map<String,Any> {
        require(port in 1..65535&&id>0&&CarPlayAudioPlan.wireSupported(route,format))
        // The input socket and decoder must exist before publishing their local port.
        // No vocoderInfo is invented: 0x2519be86c skips it when the source object is absent.
        return linkedMapOf("type" to 100,"audioType" to "telephony","audioFormat" to format.bit,
            "audioLatencyMs" to 100,"streamConnectionID" to id,"input" to true,"dataPort" to port,
            "supportsHighAccuracyTimestamps" to true,"supportsRTPPacketRedundancy" to true)
    }
}

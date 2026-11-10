package io.github.iamr0s.carvex.carplay.core

/** Publish a state only after the local changeModes transaction accepted it. */
object ResourceModeNotification {
    fun fromReply(reply:Map<String,Any?>):Map<String,Any?>? {
        val status=reply["status"] as? Number?:return null
        if(status.toDouble()!=0.0)return null
        val params=reply["params"] as? Map<*,*>?:return null
        return mapOf("type" to "modesChanged","params" to params)
    }
}

package io.github.iamr0s.carvex.carplay.core

/** Capability-driven subset for MainScreen(1) and MainAudio(2). Unknown constraints remain rejected. */
class ScreenResourceModes {
    data class State(val owner:Int=1,val permanent:Int=1,val borrowed:Boolean=false,
        val audioOwner:Int=2,val audioPermanent:Int=2,val audioBorrowed:Boolean=false)
    var state=State();private set
    private var audioRevision=0L
    class AudioChange internal constructor(internal val before:State,internal val revision:Long)
    fun audio(phone:Boolean):AudioChange {
        val before=state
        state=state.copy(audioOwner=if(phone)1 else 2,audioPermanent=if(phone)1 else 2,audioBorrowed=false)
        return AudioChange(before,++audioRevision)
    }
    /** A failed local announcement cannot undo a newer receiver declaration or a screen change. */
    fun rollbackAudio(change:AudioChange){
        if(audioRevision!=change.revision)return
        state=state.copy(audioOwner=change.before.audioOwner,audioPermanent=change.before.audioPermanent,
            audioBorrowed=change.before.audioBorrowed)
        audioRevision++
    }
    private fun integer(value:Any?):Int? {
        val number=value as? Number?:return null
        val double=number.toDouble()
        return number.toInt().takeIf{double.isFinite()&&double==it.toDouble()}
    }
    fun requestedResource(params:Map<*,*>):Int? = requestedResources(params)?.singleOrNull()
    fun requestedResources(params:Map<*,*>):Set<Int>? {
        val requests=params["resources"] as? List<*>?:return null
        if(requests.size !in 1..2)return null
        val ids=linkedSetOf<Int>()
        for(request in requests){
            val entry=request as? Map<*,*>?:return null
            val id=integer(entry["resourceID"])?.takeIf{it in 1..2}?:return null
            if(!ids.add(id))return null
        }
        return ids
    }
    fun propose(params:Map<*,*>):State? {
        if(params.keys.any{it !in setOf("resources","appStates")})return null
        val apps=params["appStates"]
        if(apps!=null&&(apps !is List<*>||apps.isNotEmpty()))return null
        requestedResources(params)?:return null
        val requests=params["resources"] as List<*>
        var next=state
        // 24A446 0x251afb178..0x251afb204 iterates resources 1 and 2 into one request.
        // Validate the entire supported subset before any host side effect or state commit.
        for(request in requests)next=proposeResource(next,request as Map<*,*>)?:return null
        return next
    }
    private fun proposeResource(state:State,r:Map<*,*>):State? {
        if(r.keys!=setOf("resourceID","transferType"))return null
        val resource=integer(r["resourceID"])?:return null;val transfer=integer(r["transferType"])?:return null
        if(resource==1)return when(transfer){
            1->if(state.borrowed)null else state.copy(owner=2,permanent=2,borrowed=false)
            2->if(state.borrowed)null else state.copy(owner=1,permanent=1,borrowed=false)
            3->if(state.borrowed||state.owner!=1)null else state.copy(owner=2,borrowed=true)
            4->if(!state.borrowed)null else state.copy(owner=state.permanent,borrowed=false)
            else->null
        }
        if(resource==2)return when(transfer){
            1->if(state.audioBorrowed)null else state.copy(audioOwner=2,audioPermanent=2,audioBorrowed=false)
            2->if(state.audioBorrowed)null else state.copy(audioOwner=1,audioPermanent=1,audioBorrowed=false)
            3->if(state.audioBorrowed||state.audioOwner!=1)null else state.copy(audioOwner=2,audioBorrowed=true)
            4->if(!state.audioBorrowed)null else state.copy(audioOwner=state.audioPermanent,audioBorrowed=false)
            else->null
        }
        return null
    }
    fun commit(next:State,audioDeclared:Boolean=false){
        if(audioDeclared||next.audioOwner!=state.audioOwner||next.audioPermanent!=state.audioPermanent||
            next.audioBorrowed!=state.audioBorrowed)audioRevision++
        state=next
    }
    fun params(value:State=state):Map<String,Any?> = mapOf(
        "resources" to listOf(
            mapOf("resourceID" to 1,"entity" to value.owner,"permanentEntity" to value.permanent),
            mapOf("resourceID" to 2,"entity" to value.audioOwner,"permanentEntity" to value.audioPermanent)
        ),
        "appStates" to listOf(mapOf("appStateID" to 1,"entity" to 0,"speechMode" to -1),mapOf("appStateID" to 2,"entity" to 0),mapOf("appStateID" to 3,"entity" to 0))
    )
}

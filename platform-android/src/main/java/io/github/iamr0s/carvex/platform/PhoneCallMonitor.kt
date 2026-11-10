package io.github.iamr0s.carvex.platform

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import android.os.Build
import android.os.Handler
import android.os.Looper
import android.telephony.PhoneStateListener
import android.telephony.SubscriptionManager
import android.telephony.TelephonyCallback
import android.telephony.TelephonyManager
import java.util.concurrent.atomic.AtomicBoolean
import java.util.concurrent.CopyOnWriteArraySet

/** Observe cellular activity only, never numbers or call contents. OFFHOOK also includes dialing
 * and held calls; it must not be reported as proof the remote party has answered. */
class PhoneCallMonitor(context:Context,private val changed:(Boolean)->Unit,
    private val log:(String)->Unit):AutoCloseable {
    private val context=context.applicationContext
    private val handler=Handler(Looper.getMainLooper())
    private val closed=AtomicBoolean(false)
    private val subscriptions=context.getSystemService(SubscriptionManager::class.java)
    private val telephony=context.getSystemService(TelephonyManager::class.java)
    private val registrations=mutableMapOf<Int,AutoCloseable>()
    private val states=mutableMapOf<Int,Int>()
    private var last:Boolean?=null
    private var watching=false
    private val tokens=mutableMapOf<Int,Any>()
    private val permission:()->Unit={handler.post{refresh()};Unit}
    private val subscriptionListener=object:SubscriptionManager.OnSubscriptionsChangedListener(){
        override fun onSubscriptionsChanged(){handler.post{refresh()}}
    }
    init{
        permissionObservers.add(permission)
        handler.post{
            if(!closed.get()){
                refresh()
            }
        }
    }
    private fun publish(){
        val active=states.values.any{it==TelephonyManager.CALL_STATE_OFFHOOK}
        if(last!=active){
            log("debug call event=state source=cellular previous=${last?:"unknown"} active=$active observed=${states.values.sorted()} registrations=${registrations.size}; OFFHOOK includes dialing/held")
            last=active;changed(active)
        }
    }
    private fun clear(){
        tokens.clear();registrations.values.forEach{runCatching{it.close()}}
        registrations.clear();states.clear()
    }
    private fun refresh(){
        if(closed.get())return
        if(context.checkSelfPermission(Manifest.permission.READ_PHONE_STATE)!=PackageManager.PERMISSION_GRANTED){
            log("debug call event=access source=cellular granted=false reason=READ_PHONE_STATE")
            clear();publish();log("Call microphone state unavailable: READ_PHONE_STATE not granted");return
        }
        try{
            if(!watching&&subscriptions!=null){
                if(Build.VERSION.SDK_INT>=30)subscriptions.addOnSubscriptionsChangedListener(context.mainExecutor,subscriptionListener)
                else subscriptions.addOnSubscriptionsChangedListener(subscriptionListener)
                watching=true
            }
            val ids=subscriptions?.activeSubscriptionInfoList.orEmpty().map{it.subscriptionId}.toSet()
            log("debug call event=monitor source=cellular granted=true subscriptions=${ids.size} registered=${registrations.size} manager=${telephony!=null}")
            if(registrations.keys==ids&&ids.isNotEmpty())return
            for(id in registrations.keys.toSet()-ids){
                tokens.remove(id);states.remove(id)
                registrations.remove(id)?.let{runCatching{it.close()}}
            }
            for(id in ids-registrations.keys){
                val manager=telephony?.createForSubscriptionId(id)?:continue
                val token=Any();tokens[id]=token
                fun state(value:Int){
                    if(closed.get()||tokens[id]!==token)return
                    if(context.checkSelfPermission(Manifest.permission.READ_PHONE_STATE)!=PackageManager.PERMISSION_GRANTED){refresh();return}
                    states[id]=value
                    val name=when(value){TelephonyManager.CALL_STATE_IDLE->"IDLE";TelephonyManager.CALL_STATE_RINGING->"RINGING";TelephonyManager.CALL_STATE_OFFHOOK->"OFFHOOK";else->"UNKNOWN"}
                    log("debug call event=state source=cellular sourceIndex=${ids.sorted().indexOf(id)} raw=$value name=$name; numbers not observed")
                    log("Call state source=cellular state=$value subscriptions="+ids.size+"; OFFHOOK includes dialing/held")
                    publish()
                }
                if(Build.VERSION.SDK_INT>=31){
                    val callback=object:TelephonyCallback(),TelephonyCallback.CallStateListener{
                        override fun onCallStateChanged(value:Int){state(value)}
                    }
                    manager.registerTelephonyCallback(context.mainExecutor,callback)
                    registrations[id]=AutoCloseable{manager.unregisterTelephonyCallback(callback)}
                }else{
                    @Suppress("DEPRECATION") val listener=object:PhoneStateListener(){
                        override fun onCallStateChanged(value:Int,number:String?){state(value)}
                    }
                    @Suppress("DEPRECATION")
                    manager.listen(listener,PhoneStateListener.LISTEN_CALL_STATE)
                    registrations[id]=AutoCloseable{manager.listen(listener,PhoneStateListener.LISTEN_NONE)}
                }
            }
            // Retain unchanged SIMs while new registrations deliver initial state asynchronously.
            // Removing another SIM must not momentarily end an ongoing call.
            publish()
            log("Call state monitoring subscriptions="+registrations.size)
        }catch(t:Exception){clear();publish();log("Call state monitoring failed: "+t.javaClass.simpleName)
            log("debug call event=monitor source=cellular failed=${t.javaClass.simpleName}")}
    }
    override fun close(){
        if(!closed.compareAndSet(false,true))return
        log("debug call event=lifecycle source=cellular closed=true")
        permissionObservers.remove(permission)
        handler.post{runCatching{if(watching)subscriptions?.removeOnSubscriptionsChangedListener(subscriptionListener)};clear()}
    }
    companion object{
        private val permissionObservers=CopyOnWriteArraySet<()->Unit>()
        fun refreshPermissions(){permissionObservers.forEach{it()}}
    }
}

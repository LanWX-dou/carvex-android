package io.github.iamr0s.carvex.sessioncore

import kotlinx.coroutines.*
import kotlinx.coroutines.sync.Mutex

/** Local call demand. Hangup revokes delivery immediately, including a SETUP still in flight.
 * Opening is serialized; a stale result is closed before a later call can open its stream. */
class CallMicrophoneSession(parent:CoroutineScope,private val log:(String)->Unit):AutoCloseable {
    private val scope=CoroutineScope(parent.coroutineContext+SupervisorJob(parent.coroutineContext[Job]))
    private val lock=Mutex()
    @Volatile var active=false;private set
    private var closed=false
    private var generation=0L
    private var open:(suspend (()->Boolean)->AutoCloseable)?=null
    private var installed:AutoCloseable?=null
    @Synchronized fun attach(factory:suspend (()->Boolean)->AutoCloseable){
        if(closed)return
        check(open==null);open=factory
        if(active)start()
    }
    @Synchronized fun update(value:Boolean){
        if(closed||active==value)return
        active=value;generation++
        log("Call microphone demand active=$value generation=$generation")
        installed?.close();installed=null
        if(value)start()
    }
    @Synchronized private fun current(ticket:Long)=!closed&&active&&generation==ticket
    private fun start(){
        val factory=open?:return
        val ticket=generation
        scope.launch{
            lock.lock()
            try{
                if(!current(ticket))return@launch
                val receiver=factory{current(ticket)}
                synchronized(this@CallMicrophoneSession){
                    if(current(ticket)){installed=receiver;log("Call microphone phase=installed generation=$ticket")}
                    else{receiver.close();log("Call microphone phase=obsolete generation=$ticket")}
                }
            }catch(t:CancellationException){throw t}
            catch(t:Exception){log("Call microphone phase=failed error="+t.javaClass.simpleName+" "+t.message)}
            finally{lock.unlock()}
        }
    }
    @Synchronized override fun close(){
        if(closed)return
        closed=true;active=false;generation++;installed?.close();installed=null;scope.cancel()
    }
}

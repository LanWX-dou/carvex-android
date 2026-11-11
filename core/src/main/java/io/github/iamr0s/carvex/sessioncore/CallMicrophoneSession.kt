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
        log("debug call event=provider attached=true active=$active generation=$generation")
        if(active)start()
    }
    @Synchronized fun update(value:Boolean){
        if(closed||active==value)return
        active=value;generation++
        log("debug call event=demand active=$value generation=$generation installed=${installed!=null} provider=${open!=null}")
        log("Call microphone demand active=$value generation=$generation")
        releaseInstalled()
        if(value)start()
    }
    @Synchronized private fun current(ticket:Long)=!closed&&active&&generation==ticket
    /** A local close failure must not keep a revoked input installed or prevent the next call.
     * Remote type100 teardown confirmation remains the transport's responsibility. */
    private fun releaseInstalled(){
        val receiver=installed;installed=null
        try{receiver?.close()}catch(t:Exception){
            log("debug call event=teardown source=microphone phase=failed generation=$generation error=${t.javaClass.simpleName} detail=${DebugLogValue.text(t.message)}")
        }
    }
    private fun start(){
        val factory=open?:run{log("debug call event=blocked source=microphone reason=no-provider generation=$generation");return}
        val ticket=generation
        scope.launch{
            lock.lock()
            try{
                if(!current(ticket)){log("debug call event=setup generation=$ticket current=false reason=obsolete-before-open");return@launch}
                log("debug call event=setup generation=$ticket phase=begin")
                val receiver=factory{current(ticket)}
                synchronized(this@CallMicrophoneSession){
                    if(current(ticket)){installed=receiver;log("Call microphone phase=installed generation=$ticket")
                        log("debug call event=setup generation=$ticket phase=installed")}
                    else{try{receiver.close()}catch(t:Exception){
                            log("debug call event=teardown source=microphone phase=failed generation=$ticket error=${t.javaClass.simpleName}")
                        };log("Call microphone phase=obsolete generation=$ticket")
                        log("debug call event=setup generation=$ticket phase=obsolete closed=true")}
                }
            }catch(t:CancellationException){log("debug call event=setup generation=$ticket phase=cancelled");throw t}
            catch(t:Exception){log("Call microphone phase=failed error="+t.javaClass.simpleName+" "+t.message)
                log("debug call event=setup generation=$ticket phase=failed error=${t.javaClass.simpleName} detail=${DebugLogValue.text(t.message)}")}
            finally{lock.unlock()}
        }
    }
    @Synchronized override fun close(){
        if(closed)return
        log("debug call event=lifecycle source=microphone closed=true active=$active installed=${installed!=null} generation=$generation")
        closed=true;active=false;generation++
        try{releaseInstalled()}finally{scope.cancel()}
    }
}

package io.github.iamr0s.carvex.host.vendor

import android.content.ComponentName
import android.content.Context
import android.content.Intent
import android.content.ServiceConnection
import android.os.Binder
import android.os.Bundle
import android.os.Handler
import android.os.IBinder
import android.os.Looper
import android.os.RemoteException
import android.view.KeyEvent
import android.view.MotionEvent
import android.view.Surface
import com.baidu.carlife.mixing.CastConfig
import com.baidu.carlife.mixing.MusicInfo
import com.baidu.carlife.mixing.aidl.ICarLifeCastCallback
import com.baidu.carlife.mixing.aidl.ICarLifeCastManager
import com.baidu.carlife.mixing.aidl.IRemoteAudioListener
import com.baidu.carlife.mixing.aidl.IRemoteKeyListener
import com.baidu.carlife.mixing.aidl.IRemoteTouchListener
import com.baidu.carlife.mixing.aidl.ISystemAudioCallback
import io.github.iamr0s.carvex.host.MixingMicrophonePcm
import io.github.iamr0s.carvex.pcm.PcmFormat
import io.github.iamr0s.carvex.sessioncore.CastHost
import io.github.iamr0s.carvex.sessioncore.HostCallbacks
import io.github.iamr0s.carvex.sessioncore.HostCapabilities
import io.github.iamr0s.carvex.sessioncore.HostMusic
import io.github.iamr0s.carvex.sessioncore.HostNavigationSource
import io.github.iamr0s.carvex.sessioncore.HostNavigationEvent
import io.github.iamr0s.carvex.sessioncore.HostNavigationChange
import kotlinx.coroutines.CompletableDeferred
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.SupervisorJob
import kotlinx.coroutines.cancel
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import kotlinx.coroutines.withTimeout
import org.json.JSONObject
import java.util.concurrent.atomic.AtomicBoolean
import java.util.concurrent.atomic.AtomicLong

/**
 * One implementation for every verified CarLife mixing endpoint.
 *
 * The APKs differ in the package/component used to reach this manager, while the
 * callback contract and the AIDL descriptor are the same. All transport behaviour
 * therefore lives here; [VendorHostConfig] only describes the endpoint.
 */
class VendorCastHost(
    private val context: Context,
    private val events: HostCallbacks,
    private val config: VendorHostConfig,
) : CastHost {
    companion object {
        const val MANAGER_DESCRIPTOR = "com.baidu.carlife.mixing.aidl.ICarLifeCastManager"
        private val navigationBindings = AtomicLong()
    }

    private val scope = CoroutineScope(SupervisorJob() + Dispatchers.IO)
    private val ready = CompletableDeferred<ICarLifeCastManager>()
    @Volatile private var remote: ICarLifeCastManager? = null
    @Volatile private var bound = false
    @Volatile private var closed = false
    @Volatile private var touch: IRemoteTouchListener? = null
    @Volatile private var key: IRemoteKeyListener? = null
    private class MicrophoneBinding(val listener: IRemoteAudioListener) {
        val delivered=AtomicBoolean(false)
    }
    @Volatile private var microphone: MicrophoneBinding? = null
    private val missingMicrophoneListener=AtomicBoolean(false)
    private val microphonePcm = MixingMicrophonePcm()
    private val navigationLock = Any()
    private val rawNavigation = NavigationRawDiagnostics({ events.event(it) }, ::expandNavigationValue)
    private var navigationSource: HostNavigationSource? = null
    @Volatile private var connectionEpoch = 0L
    private var death: IBinder.DeathRecipient? = null

    private fun invalidateNavigation(reason: String, expectedEpoch: Long? = null) = synchronized(navigationLock) {
        if (expectedEpoch != null && connectionEpoch != expectedEpoch) return@synchronized
        connectionEpoch = 0
        val source = navigationSource ?: return@synchronized
        navigationSource = null
        events.navigation(HostNavigationEvent(source, HostNavigationChange.SOURCE_INVALIDATED,
            "host-binding:$reason"))
    }

    private fun allowed(): Boolean {
        val packages = context.packageManager.getPackagesForUid(Binder.getCallingUid()).orEmpty()
        if (config.hostPackage !in packages) {
            throw SecurityException("Unexpected ${config.id} host callback UID")
        }
        return !closed
    }

    private val systemAudio = object : ISystemAudioCallback.Stub() {
        override fun onAudioStreamReady(pcm: ByteArray?, category: Int, sampleRate: Int, channels: Int, encoding: Int) {
            if (!allowed()) return
            if (pcm == null || category !in 1..3 || sampleRate !in 8000..192000 ||
                channels !in 1..2 || encoding != 2 || pcm.size !in 1..32768 ||
                pcm.size % (channels * 2) != 0) {
                events.event("invalid-pcm")
                return
            }
            events.pcm(pcm, category, sampleRate, channels, encoding)
        }

        override fun onAudioStateChange(category: Int, state: Int) {
            if (!allowed()) return
            if (category !in 1..3 || state !in 0..1) {
                events.event("unknown-audio-state", state)
                return
            }
            events.audioState(category, state)
        }
    }

    private fun callback(binding: HostNavigationSource) = object : ICarLifeCastCallback.Stub() {
        override fun onServiceReady() { if (allowed()) events.event("host-ready") }
        override fun onCastPrepared(displayId: Int) { if (allowed()) events.event("host-display", displayId) }
        override fun addTouchListener(listener: IRemoteTouchListener?) {
            if (allowed()) {
                touch = listener
                events.event("touch-listener", if (listener != null) 1 else 0)
            }
        }
        override fun removeTouchListener(listener: IRemoteTouchListener?) {
            if (allowed() && touch?.asBinder() == listener?.asBinder()) {
                touch = null
                events.event("touch-listener", 0)
            }
        }
        override fun addKeyListener(listener: IRemoteKeyListener?) {
            if (allowed()) {
                key = listener
                events.event("key-listener", if (listener != null) 1 else 0)
            }
        }
        override fun removeKeyListener(listener: IRemoteKeyListener?) {
            if (allowed() && key?.asBinder() == listener?.asBinder()) {
                key = null
                events.event("key-listener", 0)
            }
        }
        override fun addAudioListener(listener: IRemoteAudioListener?) {
            if (allowed()) {
                microphone = listener?.let { MicrophoneBinding(it) }
                events.event("microphone-listener", if (listener != null) 1 else 0)
            }
        }
        override fun removeAudioListener(listener: IRemoteAudioListener?) {
            if (allowed() && microphone?.listener?.asBinder() == listener?.asBinder()) {
                microphone = null
                events.event("microphone-listener", 0)
            }
        }
        override fun sendMusicInfo(info: MusicInfo?) {
            if (allowed()) events.music(info?.let {
                HostMusic(it.source, it.song, it.artist, it.duration, it.playlistSize, it.index)
            })
        }
        override fun notifyMusicProgress(progress: Long) { if (allowed()) events.musicProgress(progress) }

        override fun invokeMethod(intent: Intent?): Bundle? {
            if (!allowed()) return null
            if (CarWithNavigation.recognizes(intent?.action)) {
                synchronized(navigationLock) {
                    if (navigationSource !== binding || closed) return null
                    val values = intent?.extras?.let { bundle ->
                        bundle.keySet().associateWith { bundle.get(it) }
                    }.orEmpty()
                    rawNavigation.record(intent?.action, values, binding)
                    val event = config.navigationDecoder?.invoke(intent?.action, values, binding)
                    events.event(CarWithNavigation.diagnostic(intent?.action, values, binding, event))
                    if (event != null) events.navigation(event)
                    else events.event("host-navigation-unverified")
                }
                return null
            }
            return when (intent?.action) {
                "carlife_dynamic_params" -> {
                    events.fps(intent.getIntExtra("carlife_frame", 0)); null
                }
                "carlife_vr_hu_wake_up_enable" -> Bundle().apply {
                    putBoolean("hu_wake_up_enable", false)
                }
                "carlife_vr_use_phone_mic" -> Bundle().apply {
                    putBoolean("is_use_phone_mic", !(microphone != null && events.vehicleMicrophoneReady()))
                }
                "carlife_music_sample_rate" -> events.musicSampleRate()
                    ?.takeIf { it in 8000..192000 }
                    ?.let { Bundle().apply { putInt("music_sample_rate", it) } }
                else -> {
                    intent?.let {
                        if (NavigationRawDiagnostics.isNavigationAction(it.action)) {
                            val values = try {
                                it.extras?.let { bundle ->
                                    bundle.keySet().associateWith { key ->
                                        try { bundle.get(key) } catch (error: Exception) {
                                            NavigationRawDiagnostics.Failure(error.javaClass.name)
                                        }
                                    }
                                }.orEmpty()
                            } catch (error: Exception) {
                                mapOf("<extras-read-error>" to NavigationRawDiagnostics.Failure(error.javaClass.name))
                            }
                            rawNavigation.record(it.action, values, binding)
                        }
                        events.event("host-action:${it.action ?: "null"}")
                        events.optionalAction(it)
                    }
                    null
                }
            }
        }

        override fun notifyAudioState(state: Int) { if (allowed()) events.event("host-wakeup-audio-state", state) }
        override fun onServiceDestroy() { if (allowed()) {
            invalidateNavigation("destroy", binding.bindingEpoch)
            events.event("host-destroy")
        } }
    }

    private val connection = object : ServiceConnection {
        override fun onServiceConnected(name: ComponentName, binder: IBinder) {
            if (closed) return
            val connectedEpoch = synchronized(navigationLock) {
                invalidateNavigation("replaced")
                navigationBindings.incrementAndGet().also { connectionEpoch = it }
            }
            scope.launch {
                try {
                    if (closed || connectionEpoch != connectedEpoch) return@launch
                    check(binder.interfaceDescriptor == MANAGER_DESCRIPTOR) {
                        "${config.id} binder descriptor mismatch: ${binder.interfaceDescriptor}"
                    }
                    val binding = HostNavigationSource(config.id, connectedEpoch,
                        runCatching { context.packageManager.getPackageInfo(config.hostPackage, 0).versionName }.getOrNull())
                    val recipient = IBinder.DeathRecipient {
                        invalidateNavigation("binder-died", connectedEpoch)
                        events.event("host-binder-died")
                    }
                    binder.linkToDeath(recipient, 0)
                    val manager = ICarLifeCastManager.Stub.asInterface(binder)
                    if (closed || connectionEpoch != connectedEpoch) {
                        binder.unlinkToDeath(recipient, 0)
                        return@launch
                    }
                    synchronized(navigationLock) {
                        if (closed || connectionEpoch != connectedEpoch) {
                            binder.unlinkToDeath(recipient, 0)
                            return@launch
                        }
                        runCatching { death?.let { remote?.asBinder()?.unlinkToDeath(it, 0) } }
                        remote = manager
                        death = recipient
                        navigationSource = binding
                    }
                    manager.setCastCallback(callback(binding))
                    manager.setSystemAudioCallback(systemAudio)
                    if (!closed && connectionEpoch == connectedEpoch) {
                        ready.complete(manager)
                        events.event("host-bound")
                    }
                } catch (t: Throwable) {
                    invalidateNavigation("bind-error", connectedEpoch)
                    ready.completeExceptionally(t)
                    events.event("host-bind-error")
                }
            }
        }

        override fun onServiceDisconnected(name: ComponentName) { invalidateNavigation("disconnected"); events.event("host-disconnected") }
        override fun onBindingDied(name: ComponentName) { invalidateNavigation("binding-died"); events.event("host-binding-died") }
        override fun onNullBinding(name: ComponentName) {
            invalidateNavigation("null-binding")
            ready.completeExceptionally(IllegalStateException("Null host binding"))
            events.event("host-null-binding")
        }
    }

    override suspend fun bind() = withContext(Dispatchers.Main.immediate) {
        check(!closed && !bound)
        val classes = listOf(config.serviceClass) + config.fallbackServiceClasses
        var last: Throwable? = null
        for (serviceClass in classes) {
            val intent = Intent().setClassName(config.hostPackage, serviceClass)
            config.serviceAction?.let(intent::setAction)
            config.protocolType?.let { intent.putExtra("protocolType", it) }
            if (!context.bindService(intent, connection, Context.BIND_AUTO_CREATE)) continue
            bound = true
            try {
                withTimeout(10000) { ready.await() }
                return@withContext
            } catch (t: Throwable) {
                last = t
                break
            }
        }
        throw IllegalStateException("${config.displayName} rejected binding", last)
    }

    private suspend fun manager(): ICarLifeCastManager? =
        if (!bound || closed) null else ready.await()

    override suspend fun format(width: Int, height: Int): Bundle? = withContext(Dispatchers.IO) {
        manager()?.invokeMethod(Intent("carlife_encode_format").putExtra(
            "params", JSONObject().put("width", width).put("height", height)
                .put("real_width", width).put("real_height", height).toString()))
    }

    override suspend fun surface(surface: Surface, width: Int, height: Int, dpi: Int) = withContext(Dispatchers.IO) {
        check(!closed && surface.isValid)
        check(bound) { "${config.displayName} host is not bound" }
        ready.await().prepareCast(CastConfig(width, height, dpi, surface))
    }

    /** Preserve the existing PCM route. This bridge does not negotiate Bluetooth routing. */
    override suspend fun selectCarLifePlusAudio() {
        check(!closed)
        events.event(if (bound) "audio-route-default-pcm" else "audio-route-skipped-unbound")
    }

    override suspend fun invoke(action: String, configure: (Intent) -> Intent): Bundle? = withContext(Dispatchers.IO) {
        val manager = manager() ?: return@withContext null
        try {
            manager.invokeMethod(configure(Intent(action)))
        } catch (_: RemoteException) {
            events.event("host-invoke-error:$action")
            null
        }
    }

    override suspend fun microphone(pcm: ByteArray, rate: Int, channels: Int, encoding: Int): Boolean =
        withContext(Dispatchers.IO) {
            if (closed) return@withContext false
            require(rate in 8000..192000 && channels in 1..2 && encoding == 2 &&
                pcm.size in 1..32768 && pcm.size % (channels * 2) == 0)
            val binding = microphone ?: run {
                if(missingMicrophoneListener.compareAndSet(false,true))events.event("microphone-no-host-listener")
                return@withContext false
            }
            missingMicrophoneListener.set(false)
            val converted = microphonePcm.convert(pcm, PcmFormat(rate, channels, encoding), binding)
            if (closed || microphone !== binding) return@withContext false
            if (converted.isEmpty()) return@withContext true
            try {
                binding.listener.onReceiveAudioStream(converted, MixingMicrophonePcm.OUTPUT.rate,
                    MixingMicrophonePcm.CHANNEL_CONFIG, MixingMicrophonePcm.OUTPUT.encoding)
                if(binding.delivered.compareAndSet(false,true))events.event("microphone-host-callback-delivered")
                true
            } catch (_: RemoteException) {
                if (microphone === binding) {
                    microphone = null
                    events.event("microphone-listener", 0)
                }
                events.event("microphone-send-failed")
                false
            }
        }

    override fun keyMapper() = config.keyMapper
    override fun capabilities() = HostCapabilities(
        touch = true,
        keys = true,
        microphone = true,
        displayCount = 1,
        maxFps = null,
    )

    override fun touch(event: MotionEvent): Boolean = if (closed) false else touch?.onTouchEvent(event) ?: false
    override fun key(event: KeyEvent): Boolean = if (closed) false else key?.onKeyEvent(event) ?: false

    override fun close() {
        if (closed) return
        closed = true
        invalidateNavigation("closed")
        runCatching { remote?.stopCast() }
        runCatching { death?.let { remote?.asBinder()?.unlinkToDeath(it, 0) } }
        remote = null
        touch = null
        key = null
        microphone = null
        microphonePcm.reset()
        ready.cancel()
        scope.cancel()
        Handler(Looper.getMainLooper()).post {
            if (bound) runCatching { context.unbindService(connection) }
            bound = false
        }
    }
}

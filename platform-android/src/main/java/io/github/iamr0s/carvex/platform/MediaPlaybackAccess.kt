package io.github.iamr0s.carvex.platform

import android.app.NotificationManager
import android.content.ComponentName
import android.content.Context
import android.content.Intent
import android.media.MediaMetadata
import android.media.session.MediaController
import android.media.session.MediaSessionManager
import android.media.session.PlaybackState
import android.os.Handler
import android.os.Looper
import android.provider.Settings
import android.service.notification.NotificationListenerService
import java.util.concurrent.CopyOnWriteArraySet
import java.util.concurrent.atomic.AtomicBoolean

/** Grants MediaSessionManager access; notification contents are never read or retained. */
class MediaPlaybackAccess : NotificationListenerService() {
    override fun onListenerConnected() { observers.forEach { it() } }
    override fun onListenerDisconnected() { observers.forEach { it() } }

    companion object {
        internal val observers = CopyOnWriteArraySet<() -> Unit>()
        fun component(context: Context) = ComponentName(context, MediaPlaybackAccess::class.java)
        fun enabled(context: Context): Boolean = context.getSystemService(NotificationManager::class.java)
            ?.isNotificationListenerAccessGranted(component(context)) == true
        fun settings(): Intent = Intent(Settings.ACTION_NOTIFICATION_LISTENER_SETTINGS)
    }
}

/** All platform callbacks run on main. Close revokes queued work before releasing controllers. */
class MediaPlaybackMonitor(context: Context, private val log: (String) -> Unit = {},
                           private val changed: (State?) -> Unit) : AutoCloseable {
    enum class State { STOPPED, PLAYING, PAUSED, SEEK_FORWARD, SEEK_BACKWARD }
    private val context = context.applicationContext
    private val handler = Handler(Looper.getMainLooper())
    private val manager = context.getSystemService(MediaSessionManager::class.java)
    private val closed = AtomicBoolean(false)
    private var listening = false
    private var target = MediaSessionSelection.Item(null, null)
    private var additionalMatch: ((MediaSessionSelection.Item, MediaSessionSelection.Item) -> Boolean)? = null
    private var controllers = emptyList<MediaController>()
    private val callbacks = mutableMapOf<MediaController, MediaController.Callback>()
    private var last: State? = null
    private var lastDiagnostic: String? = null
    private val sessions = MediaSessionManager.OnActiveSessionsChangedListener { replace(it.orEmpty()) }
    private val accessChanged: () -> Unit = { handler.post { refresh() } }

    init {
        MediaPlaybackAccess.observers.add(accessChanged)
        handler.post { refresh() }
    }

    fun track(title: String?, artist: String?,
              additionalMatch: ((MediaSessionSelection.Item, MediaSessionSelection.Item) -> Boolean)? = null) {
        handler.post {
            if (!closed.get()) {
                target = MediaSessionSelection.Item(title, artist)
                this.additionalMatch = additionalMatch
                publish(force = true)
            }
        }
    }

    private fun refresh() {
        if (closed.get()) return
        try {
            val enabled=MediaPlaybackAccess.enabled(context)
            log("debug music event=access enabled=$enabled manager=${manager!=null}")
            if (!enabled) {
                if (listening) manager?.removeOnActiveSessionsChangedListener(sessions)
                listening = false
                replace(emptyList())
                return
            }
            if (!listening && manager != null) {
                manager.addOnActiveSessionsChangedListener(sessions, MediaPlaybackAccess.component(context), handler)
                listening = true
            }
            replace(manager?.getActiveSessions(MediaPlaybackAccess.component(context)).orEmpty())
        } catch (_: SecurityException) {
            log("debug music event=access enabled=false reason=SecurityException")
            if (listening) manager?.removeOnActiveSessionsChangedListener(sessions)
            listening = false
            replace(emptyList())
        }
    }

    private fun replace(next: List<MediaController>) {
        if (closed.get()) return
        callbacks.forEach { (controller, callback) -> controller.unregisterCallback(callback) }
        callbacks.clear()
        controllers = next
        next.forEach { controller ->
            val callback = object : MediaController.Callback() {
                override fun onPlaybackStateChanged(state: PlaybackState?) { publish() }
                override fun onMetadataChanged(metadata: MediaMetadata?) { publish() }
                override fun onSessionDestroyed() { refresh() }
            }
            callbacks[controller] = callback
            controller.registerCallback(callback, handler)
        }
        publish()
    }

    private fun publish(force: Boolean = false) {
        if (closed.get()) return
        val index = MediaSessionSelection.index(target, controllers.map { controller ->
            MediaSessionSelection.Item(controller.metadata?.getString(MediaMetadata.METADATA_KEY_TITLE),
                controller.metadata?.getString(MediaMetadata.METADATA_KEY_ARTIST))
        }, additionalMatch)
        val rawState=index?.let { controllers[it].playbackState?.state }
        val state = when (rawState) {
            PlaybackState.STATE_PLAYING -> State.PLAYING
            PlaybackState.STATE_PAUSED -> State.PAUSED
            PlaybackState.STATE_STOPPED -> State.STOPPED
            PlaybackState.STATE_FAST_FORWARDING -> State.SEEK_FORWARD
            PlaybackState.STATE_REWINDING -> State.SEEK_BACKWARD
            else -> null // Buffering, missing permission or ambiguous player is not "paused".
        }
        val diagnostic="candidates=${controllers.size} match=${index?:"none"} package=${index?.let{controllers[it].packageName}?:"unknown"} rawState=${rawState?:"unknown"} state=${state?:"unknown"} extraMatch=${additionalMatch!=null} targetTitle=${!target.title.isNullOrBlank()}"
        if(force||diagnostic!=lastDiagnostic){lastDiagnostic=diagnostic;log("debug music event=match $diagnostic")}
        if (force || state != last) { last = state; changed(state) }
    }

    override fun close() {
        if (!closed.compareAndSet(false, true)) return
        log("debug music event=lifecycle source=media-monitor closed=true")
        MediaPlaybackAccess.observers.remove(accessChanged)
        handler.post {
            if (listening) manager?.removeOnActiveSessionsChangedListener(sessions)
            callbacks.forEach { (controller, callback) -> controller.unregisterCallback(callback) }
            callbacks.clear(); controllers = emptyList(); listening = false
        }
    }
}

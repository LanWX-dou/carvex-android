package io.github.iamr0s.carvex.session

import io.github.iamr0s.carvex.carplay.core.NowPlayingUpdate

/** Session-local backend cache. Delivery only enqueues iAP work; it never waits for an ACK.
 * Serialize cache and delivery so an asynchronous progress task cannot replace a newer song. */
internal class HostMusicRelay : AutoCloseable {
    private var closed = false
    private var snapshot: NowPlayingUpdate.Track? = null
    private var sink: ((NowPlayingUpdate.Track, Boolean) -> Unit)? = null

    @Synchronized fun attach(deliver: (NowPlayingUpdate.Track, Boolean) -> Unit) {
        if (closed) return
        sink = deliver
        snapshot?.let { deliver(it, true) }
    }

    @Synchronized fun update(delta: NowPlayingUpdate.Track, replaceMedia: Boolean = false) {
        if (closed) return
        NowPlayingUpdate.fields(delta)
        val old = if (replaceMedia) NowPlayingUpdate.Track() else snapshot ?: NowPlayingUpdate.Track()
        snapshot = NowPlayingUpdate.merge(old, delta)
        sink?.invoke(delta, replaceMedia)
    }

    /** Retain application data without retaining an old destination callback. */
    @Synchronized fun detach() { sink = null }

    @Synchronized override fun close() {
        if (closed) return
        closed = true
        sink = null
        snapshot = null
    }
}

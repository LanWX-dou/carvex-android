package io.github.iamr0s.carvex.session

/** Host-side image cache; the loader serializes all access with its own lock. */
internal class HostArtworkState(private val deliver: (ByteArray) -> Unit) {
    data class Request(val generation: Long)

    var generation = 0L
        private set
    private var closed = false
    private var song: Pair<String, String?>? = null
    private var identity: List<Any?>? = null
    private var image: ByteArray? = null
    private var replacementPending = false

    fun track(title: String?, artist: String?): Boolean {
        if (!changeTrack(title, artist)) return false
        publish(byteArrayOf())
        return true
    }

    fun begin(title: String?, artist: String?, hasArtwork: Boolean,
              sources: List<Any?>): Request? {
        if (closed) return null
        val changed = changeTrack(title, artist)
        if (!hasArtwork) {
            if (changed) publish(byteArrayOf())
            return null
        }
        val next = listOf(song) + sources
        if (identity == next) return null
        identity = next
        generation++
        if (sources.isEmpty()) {
            publish(byteArrayOf())
            return null
        }
        // A single metadata+image update replaces the image when decoding completes.
        // Publishing an empty image first would make the receiver clear and redraw it.
        return Request(generation)
    }

    fun complete(request: Request, bytes: ByteArray?) {
        if (closed || request.generation != generation) return
        if (bytes != null) publish(bytes)
        else {
            // A failed source is not cached as successful. A later host event may
            // try it again; identical events still share an in-flight request.
            identity = null
            if (replacementPending) publish(byteArrayOf())
        }
    }

    private fun changeTrack(title: String?, artist: String?): Boolean {
        if (closed || title == null) return false
        val next = title to (artist ?: song?.takeIf { it.first == title }?.second)
        if (song == next) return false
        song = next
        identity = null
        generation++
        replacementPending = true
        return true
    }

    private fun publish(bytes: ByteArray) {
        replacementPending = false
        if (image?.contentEquals(bytes) == true) return
        image = bytes.copyOf()
        deliver(bytes.copyOf())
    }

    fun close() {
        closed = true
        generation++
        identity = null
        image = null
    }
}

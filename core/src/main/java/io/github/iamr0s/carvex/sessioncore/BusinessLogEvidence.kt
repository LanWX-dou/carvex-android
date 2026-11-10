package io.github.iamr0s.carvex.sessioncore

/** Session-local evidence independent of the high-frequency video/audio log tail. */
internal class BusinessLogEvidence {
    private val events = linkedMapOf<String, MutableList<String>>()
    private val samples = linkedMapOf<String, String>()

    fun record(line: String, message: String) {
        val match = PREFIX.find(message) ?: return
        val (domain, event) = match.destructured
        val key = "$domain/$event/" + KEYS.findAll(message.substringBefore(" value=")).joinToString("/") { it.value }
        samples.remove(key)
        samples[key] = line
        while (samples.size > 192) samples.remove(samples.keys.first())
        if (event in SAMPLE_EVENTS) return
        val history = events.getOrPut(domain) { mutableListOf() }
        history.add(line)
        // Preserve initial subscriptions as well as the latest state transitions.
        if (history.size > 128) history.removeAt(12)
    }

    fun snapshot(): List<String> = events.values.flatten() + samples.values
    fun clear() { events.clear(); samples.clear() }

    companion object {
        private val PREFIX = Regex("^debug (music|navigation|call) event=([a-z-]+)\\b")
        private val KEYS = Regex("\\b(?:direction|id|field|source|category)=[^ ]+")
        private val SAMPLE_EVENTS = setOf("field", "host-field", "wire", "transport", "queued", "progress", "sample", "blocked", "audio-health")
    }
}

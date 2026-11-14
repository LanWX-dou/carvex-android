package io.github.iamr0s.carvex.host.vendor

import io.github.iamr0s.carvex.sessioncore.HostNavigationSource
import java.lang.reflect.Array as ReflectArray
import java.security.MessageDigest
import java.util.ArrayDeque
import java.util.Base64
import java.util.IdentityHashMap
import java.util.concurrent.atomic.AtomicLong

/** User-requested field capture, independent of navigation decoding and publication.
 * Every payload is recoverable; text previews are only for reading the log directly. */
internal class NavigationRawDiagnostics(
    private val emit: (String) -> Unit,
    private val expand: (Any) -> Any? = { null },
) {
    data class Binary(val bytes: ByteArray, val encoding: String)
    data class Failure(val errorType: String)
    private data class Pending(val path: List<String>, val value: Any?)
    private val captures = AtomicLong()

    companion object {
        fun isNavigationAction(action: String?): Boolean = action?.lowercase()?.let { name ->
            listOf("navi", "hud", "lane", "route", "map").any(name::contains)
        } == true || NavigationCandidateDiagnostics.callbackAction(action) != null

        // Escape UTF-16 code units too, so even unusual source strings remain valid JSON.
        private fun quoted(value: String): String = buildString {
            append('"')
            for (c in value) when (c) {
                '"' -> append("\\\"")
                '\\' -> append("\\\\")
                ':', '=' -> append("\\u").append(c.code.toString(16).padStart(4, '0'))
                else -> if (c.code < 32 || c.code in 0xd800..0xdfff)
                    append("\\u").append(c.code.toString(16).padStart(4, '0')) else append(c)
            }
            append('"')
        }
        private fun pathJson(path: List<String>) = path.joinToString(",", "[", "]", transform = ::quoted)
    }

    fun observer(source: HostNavigationSource) {
        // These are remote CarWith internals, not callbacks registered by CarVeX.
        try {
            emit("navigation event=raw-candidate-observer source=${source.id} binding=${source.bindingEpoch} " +
                "payload={\"channel\":\"mixing-intent\",\"version\":${quoted(source.version ?: "unknown")}," +
                "\"nativeMapBundle\":\"not-attached\",\"easyconnNaviCallbacks\":\"not-registered\"," +
                "\"candidates\":${pathJson(NavigationCandidateDiagnostics.fields.map { it.name })}}")
        } catch (_: Exception) { }
    }

    fun record(action: String?, values: Map<String, Any?>, source: HostNavigationSource) {
        val capture = captures.incrementAndGet()
        val prefix = "navigation event=raw-"
        val context = "source=${source.id} binding=${source.bindingEpoch} capture=$capture"
        fun log(event: String, payload: String) {
            // An export/log sink failure must not reject an otherwise valid HUD update.
            try { emit("$prefix$event $context payload=$payload") } catch (_: Exception) { }
        }
        log("begin", "{\"action\":${quoted(action ?: "null")},\"version\":${quoted(source.version ?: "unknown")}," +
            "\"keys\":${pathJson(values.keys.sorted())}}")
        val observed = linkedMapOf<String, MutableList<Pair<List<String>, String>>>()
        val opaque = mutableListOf<List<String>>()
        NavigationCandidateDiagnostics.callbackAction(action)?.let {
            observed.getOrPut(it.name) { mutableListOf() }.add(listOf("action") to "action-only")
        }
        var fields = 0
        var chunks = 0
        fun field(path: List<String>, type: String, encoding: String, value: String,
                  bytes: ByteArray? = null, preview: String? = null) {
            val candidate = NavigationCandidateDiagnostics.field(path.lastOrNull())
            candidate?.let {
                val state = when (encoding) { "null" -> "null"; "error" -> "error"; else -> "present" }
                observed.getOrPut(it.name) { mutableListOf() }.add(path to state)
            }
            if (encoding in setOf("parcel-base64", "serialized-base64", "toString", "error")) opaque.add(path)
            val parts = value.chunked(2048).ifEmpty { listOf("") }
            val digest = bytes?.let { MessageDigest.getInstance("SHA-256").digest(it)
                .joinToString("") { b -> (b.toInt() and 0xff).toString(16).padStart(2, '0') } }
            fields++
            parts.forEachIndexed { index, part ->
                chunks++
                log("field", "{\"path\":${pathJson(path)},\"type\":${quoted(type)},\"encoding\":${quoted(encoding)}," +
                    "\"part\":${index + 1},\"parts\":${parts.size},\"value\":${quoted(part)}" +
                    (bytes?.let { ",\"bytes\":${it.size},\"sha256\":${quoted(digest!!)}" } ?: "") +
                    (if (index == 0 && preview != null) ",\"preview\":${quoted(preview.take(512))}" else "") +
                    (candidate?.let { ",\"candidate\":${quoted(it.name)},\"unit\":${quoted(it.unit)}" } ?: "") + "}")
            }
        }
        val pending = ArrayDeque<Pending>()
        val visited = IdentityHashMap<Any, List<String>>()
        pending.add(Pending(listOf("extras"), values))
        while (pending.isNotEmpty()) {
            val (path, original) = pending.removeFirst()
            val type = original?.javaClass?.name ?: "null"
            try {
                val value = when (original) {
                    null, is CharSequence, is Char, is Number, is Boolean, is ByteArray,
                    is Map<*, *>, is Iterable<*>, is Binary, is Failure -> original
                    else -> if (original.javaClass.isArray) original else {
                        val candidates = NavigationCandidateDiagnostics.readObject(original)
                        if (candidates == null) expand(original) ?: original else {
                            // Retain the original Parcel/serialization alongside decoded candidates.
                            val raw = try { expand(original) ?: original.toString() }
                                catch (error: Exception) { Failure(error.javaClass.name) }
                            candidates + mapOf("<raw>" to raw)
                        }
                    }
                }
                when (value) {
                    null -> field(path, type, "null", "null")
                    is Failure -> field(path, type, "error", value.errorType)
                    is ByteArray -> field(path, type, "base64", Base64.getEncoder().encodeToString(value), value)
                    is Binary -> field(path, type, value.encoding, Base64.getEncoder().encodeToString(value.bytes), value.bytes)
                    is CharSequence, is Char -> {
                        val text = value.toString()
                        // Encode each Java code unit, including unpaired surrogates, without loss.
                        val bytes = ByteArray(text.length * 2)
                        text.forEachIndexed { i, c -> bytes[2 * i] = (c.code ushr 8).toByte(); bytes[2 * i + 1] = c.code.toByte() }
                        field(path, type, "utf16be-base64", Base64.getEncoder().encodeToString(bytes), bytes, text)
                        if (original is String && text.length <= 65536 &&
                            text.trimStart().firstOrNull() in listOf('{', '[')) {
                            // Keep the original text above; JSON is an additional diagnostic view.
                            try { expand(original)?.let {
                                // An adapter returning text is not a structured JSON view.
                                if (it !is CharSequence && it !is Char) pending.add(Pending(path + "<json>", it))
                            } }
                            catch (error: Exception) { pending.add(Pending(path + "<json>", Failure(error.javaClass.name))) }
                        }
                    }
                    is Number, is Boolean -> field(path, type, "text", value.toString())
                    else -> {
                        val children: List<Pending>? = when {
                            value is Map<*, *> -> value.entries.sortedBy { it.key.toString() }
                                .map { Pending(path + it.key.toString(), it.value) }
                            value is Iterable<*> -> value.mapIndexed { i, item -> Pending(path + i.toString(), item) }
                            value.javaClass.isArray -> (0 until ReflectArray.getLength(value))
                                .map { Pending(path + it.toString(), ReflectArray.get(value, it)) }
                            else -> null
                        }
                        if (children == null) {
                            field(path, type, "toString", value.toString())
                        } else {
                            val previous = visited[original]
                            if (previous != null) field(path, type, "reference", pathJson(previous)) else {
                                visited[original] = path
                                field(path, type, "container", children.size.toString())
                                pending.addAll(children)
                            }
                        }
                    }
                }
            } catch (error: Exception) {
                field(path, type, "error", error.javaClass.name)
            }
        }
        val matches = observed.entries.joinToString(",", "[", "]") { (name, entries) ->
            "{\"candidate\":${quoted(name)},\"matches\":" + entries.joinToString(",", "[", "]") { (path, state) ->
                "{\"path\":${pathJson(path)},\"state\":${quoted(state)}}"
            } + "}"
        }
        log("candidate-summary", "{\"channel\":\"mixing-intent\",\"observed\":$matches," +
            "\"notObserved\":${pathJson(NavigationCandidateDiagnostics.fields.map { it.name }.filterNot(observed::containsKey))}," +
            "\"opaquePaths\":${opaque.joinToString(",", "[", "]", transform = ::pathJson)}," +
            "\"meaning\":\"notObserved means absent from decoded input, not zero or an upstream measurement\"}")
        log("end", "{\"fields\":$fields,\"chunks\":$chunks}")
    }
}

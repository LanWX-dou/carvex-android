// memory; never executes Apple code or connects to Bluetooth/head units.
import io.github.iamr0s.carvex.carplay.core.IapLink
import io.github.iamr0s.carvex.carplay.core.IapWire
import java.io.ByteArrayInputStream
import java.io.InputStream
import java.io.OutputStream
import java.util.concurrent.*

private class ProbeInput : InputStream() {
    private val queue = LinkedBlockingQueue<Int>()
    @Volatile private var closed = false
    fun put(bytes: ByteArray) { check(!closed); bytes.forEach { queue.add(it.toInt() and 255) } }
    override fun read(): Int = if (closed) -1 else queue.take()
    override fun close() { closed = true; queue.clear(); queue.offer(-1) }
}

private fun syn(retry: Int = 100, ack: Int = 10, retries: Int = 2,
                maxAck: Int = 0, window: Int = 5, mtu: Int = 2048,
                sessions: List<Int> = listOf(10, 0, 2)): ByteArray =
    byteArrayOf(1, window.toByte()) + IapWire.be16(mtu) + IapWire.be16(retry) +
        IapWire.be16(ack) + byteArrayOf(retries.toByte(), maxAck.toByte()) +
        sessions.map { it.toByte() }.toByteArray()
private fun frame(bytes: ByteArray) = IapWire.read(ByteArrayInputStream(bytes))
private fun packet(payload: ByteArray, ack: Int = 0, seq: Int = 20, flags: Int = 0x80) =
    IapWire.Frame(flags, seq, ack, 0, payload)
private fun decoded(bytes: ByteArray): Map<String, Any> {
    val p = checkNotNull(Iap2LinkEngine.SynchronizationPayload.decode(bytes))
    return linkedMapOf("version" to 1, "window" to p.maxOutgoing, "mtu" to p.maxLength,
        "retry" to p.retransmissionTimeoutMillis, "ack" to p.acknowledgementTimeoutMillis,
        "retries" to p.maxRetransmissions, "maxAck" to p.maxAcknowledgements,
        "sessions" to p.sessions.map { listOf(it.id, it.kind, it.version) })
}
private fun field(link: IapLink, name: String): Any =
    IapLink::class.java.getDeclaredField(name).also { it.isAccessible = true }.get(link)

private class ProbePhone : AutoCloseable {
    val input = ProbeInput()
    val output = LinkedBlockingQueue<ByteArray>()
    val link = IapLink(input, object : OutputStream() {
        override fun write(b: Int) { output.add(byteArrayOf(b.toByte())) }
        override fun write(b: ByteArray, off: Int, len: Int) { output.add(b.copyOfRange(off, off + len)) }
    }, {}, {}, firstByteTimeoutMs = 100, detectTimeoutMs = 100)
    private val executor = Executors.newSingleThreadExecutor {
        Thread(it, "syn-negotiation-probe").apply { isDaemon = true }
    }
    val start = executor.submit { link.start(allowDirectSyn = true) }
    fun send(f: IapWire.Frame) = input.put(IapWire.packet(f))
    fun begin(payload: ByteArray): IapWire.Frame {
        send(packet(payload))
        while (true) {
            val bytes = checkNotNull(output.poll(2, TimeUnit.SECONDS)) { "No SYNACK" }
            if (bytes.contentEquals(IapWire.detection)) continue
            return frame(bytes).also { check(it.flags == 0xc0) }
        }
    }
    fun result(): String = try { start.get(2, TimeUnit.SECONDS); "completed" }
        catch (e: ExecutionException) { e.cause!!.javaClass.simpleName + ": " + e.cause!!.message }
    override fun close() {
        link.close(); input.close(); executor.shutdownNow(); executor.awaitTermination(2, TimeUnit.SECONDS)
    }
}

private data class Vector(val id: String, val first: ByteArray = syn(), val second: ByteArray = first,
                          val expected: String = "SYNC_RENEGOTIATION_REQUIRED", val wrongAck: Boolean = false,
                          val pureAck: Boolean = false)
private fun json(value: Any?): String = when (value) {
    null -> "null"
    is String -> "\"" + value.replace("\\", "\\\\").replace("\"", "\\\"").replace("\n", "\\n") + "\""
    is Number, is Boolean -> value.toString()
    is Map<*, *> -> value.entries.joinToString(",", "{", "}") { json(it.key.toString()) + ":" + json(it.value) }
    is Iterable<*> -> value.joinToString(",", "[", "]") { json(it) }
    else -> error("Unknown JSON type: ${value.javaClass}")
}
fun main() {
    val sessions = listOf(10, 0, 2, 11, 2, 1)
    val vectors = listOf(
        Vector("N01-unchanged", expected = "completed"),
        Vector("N02-accept-our-retry", syn(retry = 2000), syn(retry = 1000)),
        Vector("N03-lower-retry", second = syn(retry = 50)),
        Vector("N04-raise-retry", second = syn(retry = 200)),
        Vector("N05-change-window", second = syn(window = 7)),
        Vector("N06-lower-mtu", second = syn(mtu = 1024), expected = "completed"),
        Vector("N07-raise-mtu", second = syn(mtu = 4096), expected = "completed"),
        Vector("N08-change-control-id", second = syn(sessions = listOf(11, 0, 2))),
        Vector("N09-change-control-version", second = syn(sessions = listOf(10, 0, 1))),
        Vector("N10-accept-control-only", syn(sessions = sessions), syn()),
        Vector("N11-reorder-sessions", syn(sessions = sessions),
            syn(sessions = listOf(11, 2, 1, 10, 0, 2)), expected = "completed"),
        Vector("N12-wrong-ack", expected = "Unassociated SYN ACK", wrongAck = true),
        Vector("N13-pure-ack-control", expected = "completed", pureAck = true),
        Vector("N14-accept-our-ack-timeout", syn(ack = 500), syn(ack = 10)),
        Vector("N15-accept-our-max-ack", syn(maxAck = 3), syn(maxAck = 0)),
        Vector("N16-lower-retry-count", syn(retries = 30), syn(retries = 2))
    )
    for (v in vectors) ProbePhone().use { p ->
        val response = p.begin(v.first)
        val a = (response.seq + if (v.wrongAck) 3 else 0) and 255
        p.send(packet(if (v.pureAck) byteArrayOf() else v.second, a,
            if (v.pureAck) 20 else 21, if (v.pureAck) 0x40 else 0xc0))
        val result = p.result()
        check(result.contains(v.expected)) { "${v.id}: unexpected phone result $result" }
        check(p.link.generation == if (v.expected == "completed") 1 else 0)
        val c = Iap2LinkEngine()
        c.start(0); c.takeOutput()
        c.feed(IapWire.packet(packet(v.first)), 1)
        val cr = frame(c.takeOutput())
        check(c.state == Iap2LinkEngine.State.NEGOTIATING)
        c.feed(IapWire.packet(packet(if (v.pureAck) byteArrayOf() else v.second,
            (cr.seq + if (v.wrongAck) 3 else 0) and 255,
            if (v.pureAck) 20 else 21, if (v.pureAck) 0x40 else 0xc0)), 2)
        check(c.state == Iap2LinkEngine.State.NORMAL)
        val cp = checkNotNull(c.peerSynchronization)
        check(cp == Iap2LinkEngine.SynchronizationPayload.decode(v.first))
        println(json(linkedMapOf("id" to v.id, "first" to decoded(v.first),
            "second" to if (v.pureAck) "pureACK" else decoded(v.second), "wrong_ack" to v.wrongAck,
            "phone" to linkedMapOf("reply" to decoded(response.payload), "result" to result,
                "generation" to p.link.generation,
                "active" to listOf("peerWindow", "maxPacket", "retryMs", "retryCount", "ackTimeoutMs", "maxCumulativeAck")
                    .associateWith { field(p.link, it) }),
                "retained_first_proposal" to true, "peer" to decoded(cp.encode())))))
    }
    println(json(mapOf("summary" to "16 implementation vectors passed", "apple_executed" to false,
        "headunit_tested" to false, "production_modified" to false)))
}

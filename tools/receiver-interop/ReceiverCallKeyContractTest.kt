package io.github.iamr0s.carvex.host

import com.shilapi.xcertplay.airplay.AirPlayHid
import org.junit.Assert.*
import org.junit.Test

class ReceiverCallKeyContractTest {
    private fun usage(index: Int): Int {
        // Ordered selector usages in the actual receiver descriptor. No sender descriptor copy.
        val descriptor = AirPlayHid.telephonyHidDevice("screen")["hidDescriptor"] as ByteArray
        val usages = mutableListOf<Int>()
        var page = 0
        var offset = 0
        while (offset < descriptor.size) {
            val prefix = descriptor[offset++].toInt() and 255
            val size = when (prefix and 3) { 3 -> 4; else -> prefix and 3 }
            var value = 0
            repeat(size) { value = value or ((descriptor[offset++].toInt() and 255) shl (8 * it)) }
            if (prefix and 0xfc == 0x04) page = value
            if (prefix and 0xfc == 0xa0) usages.clear()
            if (prefix and 0xfc == 0x08) usages += (page shl 16) or value
            if (prefix and 0xfc == 0x80) return usages[AirPlayHid.telephonyReport(index).single().toInt() and 255]
        }
        error("No receiver selector report")
    }

    @Test fun hookSwitchAnswersAndDropEndsTheCall() {
        val mapper = MixingKeyMapper()
        assertEquals(0x0b0020, usage(1))
        assertEquals(MixingKeys.CALL, mapper.hidKey("pageb", usage(1) and 65535))
        assertEquals(0x0b0026, usage(3))
        assertEquals(MixingKeys.END_CALL, mapper.hidKey("pageb", usage(3) and 65535))
    }

    @Test fun flashCannotBeMistakenForTheAnswerOperation() {
        assertEquals(0x0b0021, usage(2))
        assertNull(MixingKeyMapper().hidKey("pageb", usage(2) and 65535))
        assertEquals(MixingKeys.PHONE, MixingKeyMapper().uiKey("ui:mobilephone:"))
    }
}

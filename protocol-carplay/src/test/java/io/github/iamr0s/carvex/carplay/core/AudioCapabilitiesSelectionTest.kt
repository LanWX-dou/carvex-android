package io.github.iamr0s.carvex.carplay.core

import io.github.iamr0s.carvex.pcm.PcmFormat
import org.junit.Assert.*
import org.junit.Test

class AudioCapabilitiesSelectionTest {
    private fun entry(type:Int=100,purpose:String?,input:Long=0,output:Long=0,
                      manufacturer:String?=null,extended:List<Any?>?=null)=
        AudioCapabilities.Entry(type,purpose,input,output,manufacturer,extended)

    @Test fun anonymousEntryShadowsLaterExactEntryAndUsesRequestedDirection() {
        val rows=listOf(entry(purpose=null,input=0x10,output=0x8000),
            entry(purpose="speechRecognition",input=0x20000000))
        val selected=AudioCapabilities.formatsFor(rows,100,"speechRecognition",true)!!
        assertEquals(0x10L,selected.mask)
        assertEquals(0,selected.index)
        assertTrue(selected.fallback)
        assertEquals(listOf(0x10L),CarPlayAudioPlan.microphoneCandidates(rows,PcmFormat(16000,1)).map{it.bit})
    }

    @Test fun zeroExactEntryDoesNotReadLaterNonzeroEntriesOrFallBackToPcm() {
        val rows=listOf(entry(102,"media"),entry(102,"media",output=0x800000),
            entry(102,"media",output=0x8000))
        assertEquals(0L,AudioCapabilities.formatsFor(rows,102,"media",false)!!.mask)
        assertNull(CarPlayAudioPlan.selectPlayback(rows,1,PcmFormat(48000,2)){true})
    }

    @Test fun duplicateExactEntriesAreNotCombinedForLocalCodecIntersection() {
        val rows=listOf(entry(102,"media",output=0x2000000),entry(102,"media",output=0x800000))
        val seen=mutableListOf<CarPlayAudioPlan.Codec>()
        assertNull(CarPlayAudioPlan.selectPlayback(rows,1,PcmFormat(48000,2)){
            seen.add(it.codec);it.codec==CarPlayAudioPlan.Codec.AAC_LC
        })
        assertEquals(listOf(CarPlayAudioPlan.Codec.AAC_ELD),seen)
    }

    @Test fun lastPriorDefaultOverridesEarlierDefaultIncludingZero() {
        val rows=listOf(entry(purpose="default",input=0x10,manufacturer="Apple Receiver"),
            entry(purpose="default",input=0),entry(purpose="telephony"))
        assertEquals(0L,AudioCapabilities.formatsFor(rows,100,"telephony",true)!!.mask)
        val nonzero=rows.toMutableList().apply{set(1,entry(purpose="default",input=0x40))}
        val match=AudioCapabilities.formatsFor(nonzero,100,"telephony",true)!!
        assertEquals(0x40L,match.mask)
        assertTrue(match.fallback)
    }

    @Test fun defaultFallbackRequiresLiteralApplePrefix() {
        for(manufacturer in listOf(null,"Other","apple","NotApple")){
            val rows=listOf(entry(purpose="default",input=0x10,manufacturer=manufacturer),
                entry(purpose="telephony"))
            val match=AudioCapabilities.formatsFor(rows,100,"telephony",true)!!
            assertEquals(0L,match.mask)
            assertFalse(match.fallback)
        }
        val rows=listOf(entry(purpose="default",input=0x10,manufacturer="AppleCar"))
        val match=AudioCapabilities.formatsFor(rows,100,"telephony",true)!!
        assertEquals(0x10L,match.mask)
        assertNull(match.index)
        assertTrue(match.fallback)
    }

    @Test fun defaultAfterStopAndDefaultsFromOtherRawTypesAreNotAvailable() {
        val rows=listOf(entry(purpose="telephony",manufacturer="Apple"),
            entry(purpose="default",input=0x10))
        assertEquals(0L,AudioCapabilities.formatsFor(rows,100,"telephony",true)!!.mask)
        val otherType=listOf(entry(101,"default",output=0x8000,manufacturer="Apple"),
            entry(purpose="telephony"))
        assertEquals(0L,AudioCapabilities.formatsFor(otherType,100,"telephony",true)!!.mask)
    }

    @Test fun requestForDefaultStopsAtItsFirstExactEntry() {
        val rows=listOf(entry(101,"default",output=0x10),entry(101,"default",output=0x8000))
        val match=AudioCapabilities.formatsFor(rows,101,"default",false)!!
        assertEquals(0x10L,match.mask)
        assertFalse(match.fallback)
    }

    @Test fun priorDefaultUsesItsOwnDirectionEvenWhenRequestedPurposeUsesOutput() {
        val rows=listOf(entry(purpose="default",input=0x10,output=0x8000,manufacturer="Apple"),
            entry(purpose="media"))
        assertEquals(0x10L,AudioCapabilities.formatsFor(rows,100,"media",false)!!.mask)
    }

    @Test fun parserPreservesManufacturerAndOpaqueExtendedValues() {
        val extended=listOf<Any?>(23L,"unknown",mapOf("future" to true))
        val rows=AudioCapabilities.parse(listOf(mapOf("type" to 102,"audioType" to "media",
            "audioOutputFormats" to 0x800000L,"audioOutputFormatsExtended" to extended)),manufacturer="Apple")
        assertEquals("Apple",rows.single().manufacturer)
        assertEquals(extended,AudioCapabilities.formatsFor(rows,102,"media",false)!!.extended)
    }

    @Test fun wrongTypedAudioTypeBecomesAnonymousRatherThanInventingNumericPurpose() {
        val rows=AudioCapabilities.parse(listOf(mapOf("type" to 100,"audioType" to 1,
            "audioInputFormats" to 0x10L)))
        assertNull(rows.single().audioType)
        assertEquals(0x10L,AudioCapabilities.formatsFor(rows,100,"speechRecognition",true)!!.mask)
    }

    @Test fun invalidSelectedExtendedContainerFailsButUnselectedOneDoesNot() {
        val invalid=mapOf("type" to 100,"audioType" to "speechRecognition",
            "audioInputFormats" to 0x10L,"audioOutputFormatsExtended" to 23)
        val good=mapOf("type" to 100,"audioType" to "speechRecognition","audioInputFormats" to 0x40L)
        val rows=AudioCapabilities.parse(listOf(invalid,good))
        assertNull(AudioCapabilities.formatsFor(rows,100,"speechRecognition",true))
        assertTrue(CarPlayAudioPlan.microphoneCandidates(rows,PcmFormat(16000,1)).isEmpty())
        val different=AudioCapabilities.parse(listOf(invalid+mapOf("audioType" to "alert"),good))
        assertEquals(0x40L,AudioCapabilities.formatsFor(different,100,"speechRecognition",true)!!.mask)
    }

    @Test fun defaultFallbackKeepsSelectedExtendedArrayRatherThanDefaultsArray() {
        val rows=listOf(entry(purpose="default",input=0x10,manufacturer="Apple",extended=listOf(1)),
            entry(purpose="telephony",extended=listOf(23)))
        val match=AudioCapabilities.formatsFor(rows,100,"telephony",true)!!
        assertEquals(0x10L,match.mask)
        assertEquals(listOf(23),match.extended)
    }

    @Test fun invalidRowAndRawTypeCannotBeSkippedToGrantLaterCapabilities() {
        val good=mapOf("type" to 100,"audioType" to "speechRecognition","audioInputFormats" to 0x10L)
        assertNull(AudioCapabilities.formatsFor(AudioCapabilities.parse(listOf("bad",good)),100,"speechRecognition",true))
        assertNull(AudioCapabilities.formatsFor(AudioCapabilities.parse(listOf(mapOf("type" to "100"),good)),100,"speechRecognition",true))
        val early=AudioCapabilities.parse(listOf(good,"bad"))
        assertEquals(0x10L,AudioCapabilities.formatsFor(early,100,"speechRecognition",true)!!.mask)
    }

    @Test fun transportFilteringCannotExposeALaterMatchingRow() {
        val rows=listOf(entry(102,"media",output=0x8000),entry(102,"media",output=0x800000))
        assertTrue(CarPlayAudioPlan.wirelessCandidates(rows,CarPlayAudioPlan.media,PcmFormat(48000,2)).isEmpty())
    }
}

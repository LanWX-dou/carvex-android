package io.github.iamr0s.carvex.carplay.core

import kotlinx.coroutines.*
import org.junit.Assert.*
import org.junit.Test

class CallMicrophonePlanTest {
    private val eld=CarPlayAudioPlan.formats.single{it.bit==0x8000000L}
    private val opus=CarPlayAudioPlan.formats.single{it.bit==0x20000000L}
    private val pcm=CarPlayAudioPlan.formats.single{it.bit==0x10L}
    private fun entry(input:Long?,output:Long?=null)=AudioCapabilities.Entry(100,"telephony",input,output)

    @Test fun telephonyInputIsImplementedAndIntersectedWithActualDecoder(){
        val advertised=listOf(entry(eld.bit or opus.bit))
        assertEquals(eld,CallMicrophonePlan.select(advertised){true})
        assertEquals(opus,CallMicrophonePlan.select(advertised){it==opus})
        assertNull(CallMicrophonePlan.select(advertised){false})
    }

    @Test fun outputAndSpeechAnnouncementsCannotEnableCallCapture(){
        val entries=listOf(entry(null,eld.bit),AudioCapabilities.Entry(100,"speechRecognition",eld.bit,null),
            AudioCapabilities.Entry(101,"telephony",eld.bit,null))
        assertNull(CallMicrophonePlan.select(entries){true})
    }

    @Test fun unsupportedLocalDecoderMayUseAdvertisedPcmButCannotInventIt(){
        assertEquals(pcm,CallMicrophonePlan.select(listOf(entry(eld.bit or pcm.bit))){it.codec==CarPlayAudioPlan.Codec.PCM16})
        assertNull(CallMicrophonePlan.select(listOf(entry(eld.bit))){it.codec==CarPlayAudioPlan.Codec.PCM16})
        assertNull(CallMicrophonePlan.select(listOf(entry(1L shl 62))){true})
    }

    @Test fun inputDescriptorPublishesBoundPortWithoutInventingHostVocoderMetadata(){
        val descriptor=CallMicrophonePlan.description(opus,42,12000)
        assertEquals(100,descriptor["type"]);assertEquals("telephony",descriptor["audioType"])
        assertEquals(true,descriptor["input"]);assertEquals(12000,descriptor["dataPort"])
        assertEquals(opus.bit,descriptor["audioFormat"]);assertEquals(42L,descriptor["streamConnectionID"])
        assertFalse(descriptor.containsKey("vocoderInfo"));assertFalse(descriptor.containsKey("controlPort"))
        for(port in listOf(-1,0,65536))assertThrows(IllegalArgumentException::class.java){CallMicrophonePlan.description(opus,42,port)}
        assertThrows(IllegalArgumentException::class.java){CallMicrophonePlan.description(opus,0,12000)}
    }

    @Test fun callWaitsForSpeechTeardownWhileType102MediaRemainsLive():Unit=runBlocking {
        withTimeout(2000){
            val streams=AudioStreamLifecycle()
            val media=streams.reserve(102,"media",1)
            val speech=streams.reserve(100,"speechRecognition",2)
            streams.beginClose(speech)
            val call=async(start=CoroutineStart.UNDISPATCHED){streams.reserve(100,"telephony",3,exclusive=true)}
            assertFalse(call.isCompleted);assertTrue(streams.isActive(media.type,media.purpose))
            streams.completeClose(speech);val lease=call.await()
            assertTrue(runCatching{streams.reserve(100,"speechRecognition",4)}.isFailure)
            streams.beginClose(lease);streams.completeClose(lease)
            assertEquals(5L,streams.reserve(100,"speechRecognition",5).id)
            assertTrue(streams.isActive(media.type,media.purpose));streams.close()
        }
    }
}

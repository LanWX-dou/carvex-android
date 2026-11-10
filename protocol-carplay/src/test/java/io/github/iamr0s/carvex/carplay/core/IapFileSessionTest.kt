package io.github.iamr0s.carvex.carplay.core

import org.junit.Assert.*
import org.junit.Test
import java.io.ByteArrayInputStream
import java.io.OutputStream
import java.util.concurrent.*

class IapFileSessionTest {
    private class Peer(version:Int=1):AutoCloseable {
        val input=BoundedByteInput()
        val frames=LinkedBlockingQueue<IapWire.Frame>()
        val executor=Executors.newSingleThreadExecutor()
        val link=IapLink(input,object:OutputStream(){
            override fun write(b:Int)=error("whole frame expected")
            override fun write(b:ByteArray,off:Int,len:Int){
                frames.add(IapWire.read(ByteArrayInputStream(b,off,len)))
            }
        },{},{})
        var phoneSeq=0
        var carSeq=30
        init {
            val start=executor.submit{link.start(allowDirectSyn=true)}
            input.offer(IapWire.packet(IapWire.Frame(0x80,carSeq,0,0,
                byteArrayOf(1,1)+IapWire.be16(64)+IapWire.be16(1000)+IapWire.be16(10)+
                    byteArrayOf(2,0,10,0,1,20,1,version.toByte()))))
            val syn=take();phoneSeq=syn.seq
            ack();start.get(2,TimeUnit.SECONDS)
        }
        fun take():IapWire.Frame=frames.poll(2,TimeUnit.SECONDS)?:error("missing frame")
        fun ack(){input.offer(IapWire.packet(IapWire.Frame(0x40,carSeq,phoneSeq,0,byteArrayOf())))}
        fun incoming(session:Int,data:ByteArray){
            carSeq=(carSeq+1) and 255
            input.offer(IapWire.packet(IapWire.Frame(0x40,carSeq,phoneSeq,session,data)))
            assertEquals(carSeq,take().ack)
        }
        override fun close(){link.close();input.close();executor.shutdownNow()}
    }
    @Test(timeout=6000) fun fileDataUsesNegotiatedServiceAndWaitsForReliableAck() {
        Peer(2).use{peer->
            assertEquals(20,peer.link.negotiatedFileSession?.id)
            assertEquals(2,peer.link.negotiatedFileSession?.version)
            val done=CountDownLatch(1)
            val payload=ArtworkFileWire.setup(128,123,2)
            assertTrue(peer.link.sendFileAsync(payload,peer.link.generation){assertNull(it);done.countDown()})
            val packet=peer.take();assertEquals(20,packet.session);assertArrayEquals(payload,packet.payload)
            assertEquals(1L,done.count)
            peer.phoneSeq=packet.seq;peer.ack();assertTrue(done.await(1,TimeUnit.SECONDS))
        }
    }
    @Test(timeout=6000) fun fileControlDoesNotCorruptPartialCsm() {
        Peer().use{peer->
            val csm=IapWire.csm(0x5000,listOf(0 to IapWire.fields(listOf(26 to byteArrayOf()))))
            peer.incoming(10,csm.copyOfRange(0,5))
            peer.incoming(20,byteArrayOf(0x80.toByte(),1))
            val file=peer.link.poll(1000) as IapCommand.FileTransfer
            assertEquals(20,file.session);assertArrayEquals(byteArrayOf(0x80.toByte(),1),file.payload)
            peer.incoming(10,csm.copyOfRange(5,csm.size))
            assertEquals(0x5000,peer.link.poll(1000)?.id)
        }
    }
    @Test(timeout=6000) fun unsupportedVersionOversizeAndRevokedWorkNeverSendFileData() {
        Peer(3).use{assertNull(it.link.negotiatedFileSession)}
        Peer().use{peer->
            assertThrows(IllegalArgumentException::class.java){
                peer.link.sendFileAsync(ByteArray(peer.link.maximumFilePayload+1),peer.link.generation){}
            }
            val done=CountDownLatch(1)
            assertTrue(peer.link.sendFileAsync(byteArrayOf(0x80.toByte(),2),peer.link.generation,{false}){done.countDown()})
            assertTrue(done.await(1,TimeUnit.SECONDS));assertTrue(peer.frames.isEmpty())
        }
    }
}

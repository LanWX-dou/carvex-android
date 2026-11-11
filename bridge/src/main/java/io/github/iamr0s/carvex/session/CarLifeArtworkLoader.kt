package io.github.iamr0s.carvex.session

import android.content.Context
import android.content.Intent
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.net.Uri
import io.github.iamr0s.carvex.carplay.core.ArtworkFileWire
import io.github.iamr0s.carvex.carplay.core.NowPlayingUpdate
import io.github.iamr0s.carvex.sessioncore.DebugLogValue
import kotlinx.coroutines.*
import java.io.ByteArrayOutputStream
import java.io.InputStream
import java.net.HttpURLConnection
import java.net.URL

/** Session-owned loader. Slow URI reads cannot publish the previous song's picture. */
internal class CarLifeArtworkLoader(
    private val context:Context,private val scope:CoroutineScope,
    private val deliver:(ByteArray)->Unit,private val log:(String)->Unit,
):AutoCloseable {
    private val state=HostArtworkState(deliver)
    private var closed=false
    private var job:Job?=null

    @Synchronized fun track(title:String?,artist:String?) {
        if(state.track(title,artist)){job?.cancel();job=null}
    }

    @Synchronized fun update(intent:Intent,metadata:NowPlayingUpdate.Track?=CarLifeMusicIntent.parse(intent)) {
        if(closed||intent.action!="carlife_vehicle_music_info")return
        val extras=intent.extras?:return
        val keys=listOf("cover","artwork","MediaAlbumArt","MediaArtwork","coverUrl")
        val candidates=keys.mapNotNull{extras.get(it)}.filter{
            it is Bitmap||it is ByteArray||it is Uri||it is String&&it.isNotBlank()
        }
        val sources=candidates.map{value->when(value){
                is ByteArray->value.contentHashCode()
                is Bitmap->listOf(value.generationId,value.width,value.height)
                else->value.toString()
            }}
        val previousGeneration=state.generation
        val request=state.begin(metadata?.title,metadata?.artist,
            keys.any{extras.containsKey(it)},sources)
        log("debug music event=artwork-source present=${keys.any{extras.containsKey(it)}} types=${candidates.map{it.javaClass.simpleName}} generation=${state.generation} load=${request!=null}")
        if(state.generation!=previousGeneration){job?.cancel();job=null}
        if(request==null)return
        job=scope.launch(Dispatchers.IO){
            var image:ByteArray?=null
            for(candidate in candidates){
                ensureActive()
                try{image=load(candidate)}catch(t:CancellationException){throw t}
                catch(t:Exception){log("Artwork source unavailable: "+t.javaClass.simpleName)}
                if(image!=null)break
            }
            ensureActive()
            synchronized(this@CarLifeArtworkLoader){
                log("debug music event=artwork-decode generation=${request.generation} current=${request.generation==state.generation} result=${image?.let{DebugLogValue.bytes(it)}?:"unavailable"}")
                state.complete(request,image)
            }
        }
    }
    private fun load(value:Any):ByteArray? {
        if(value is Bitmap)return encode(value,false)
        val bytes=when(value){
            is ByteArray->value.takeIf{it.size<=MAX_SOURCE_BYTES}
            is Uri->readUri(value)
            is String->readUri(Uri.parse(value))
            else->null
        }?:return null
        val bounds=BitmapFactory.Options().apply{inJustDecodeBounds=true}
        BitmapFactory.decodeByteArray(bytes,0,bytes.size,bounds)
        if(bounds.outWidth<=0||bounds.outHeight<=0)return null
        var sample=1
        while(bounds.outWidth/sample>512||bounds.outHeight/sample>512)sample*=2
        val bitmap=BitmapFactory.decodeByteArray(bytes,0,bytes.size,BitmapFactory.Options().apply{inSampleSize=sample})?:return null
        return encode(bitmap,true)
    }
    private fun encode(bitmap:Bitmap,owned:Boolean):ByteArray? {
        var scaled:Bitmap?=null
        try{
            if(bitmap.isRecycled||bitmap.width<=0||bitmap.height<=0)return null
            val ratio=minOf(1.0,512.0/maxOf(bitmap.width,bitmap.height))
            val normalized=if(ratio<1)Bitmap.createScaledBitmap(bitmap,
                (bitmap.width*ratio).toInt().coerceAtLeast(1),(bitmap.height*ratio).toInt().coerceAtLeast(1),true)
                .also{scaled=it} else bitmap
            val out=ByteArrayOutputStream()
            if(!normalized.compress(Bitmap.CompressFormat.JPEG,85,out))return null
            return out.toByteArray().takeIf{it.size in 1..ArtworkFileWire.MAX_BYTES}
        }finally{
            scaled?.takeIf{it!==bitmap}?.recycle()
            if(owned)bitmap.recycle()
        }
    }
    private fun readUri(uri:Uri):ByteArray?=when(uri.scheme?.lowercase()){
        "content","android.resource"->context.contentResolver.openInputStream(uri)?.use{bounded(it)}
        "https","http"->{
            val connection=URL(uri.toString()).openConnection() as HttpURLConnection
            connection.connectTimeout=5000;connection.readTimeout=5000
            connection.instanceFollowRedirects=false
            try{
                if(connection.responseCode !in 200..299||connection.contentLengthLong>MAX_SOURCE_BYTES)null
                else connection.inputStream.use{bounded(it)}
            }finally{connection.disconnect()}
        }
        else->null
    }
    private fun bounded(input:InputStream):ByteArray {
        val out=ByteArrayOutputStream();val buffer=ByteArray(8192)
        while(true){
            val count=input.read(buffer)
            if(count<0)break
            require(out.size()+count<=MAX_SOURCE_BYTES){"Artwork source exceeds size limit"}
            out.write(buffer,0,count)
        }
        return out.toByteArray()
    }
    @Synchronized override fun close(){closed=true;state.close();job?.cancel();job=null}
    companion object{private const val MAX_SOURCE_BYTES=2*1024*1024}
}

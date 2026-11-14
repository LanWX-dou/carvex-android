package io.github.iamr0s.carvex.host.vendor

import android.graphics.Bitmap
import android.os.Bundle
import android.os.Parcel
import android.os.Parcelable
import android.util.SparseArray
import java.io.ByteArrayOutputStream
import java.io.ObjectOutputStream
import java.io.Serializable
import org.json.JSONArray
import org.json.JSONObject

/** Adapt Android containers/images without retaining them in the navigation snapshot. */
internal fun expandNavigationValue(value: Any): Any? = when (value) {
    is JSONObject -> value.keys().asSequence().associateWith { key ->
        value.opt(key).takeUnless { it === JSONObject.NULL }
    }
    is JSONArray -> List(value.length()) { index -> value.opt(index).takeUnless { it === JSONObject.NULL } }
    is String -> when (value.trimStart().firstOrNull()) {
        '{' -> try { JSONObject(value) } catch (error: Exception) { NavigationRawDiagnostics.Failure(error.javaClass.name) }
        '[' -> try { JSONArray(value) } catch (error: Exception) { NavigationRawDiagnostics.Failure(error.javaClass.name) }
        else -> null
    }
    is Bundle -> value.keySet().associateWith { key ->
        try { value.get(key) } catch (error: Exception) { NavigationRawDiagnostics.Failure(error.javaClass.name) }
    }
    is SparseArray<*> -> (0 until value.size()).associate { value.keyAt(it).toString() to value.valueAt(it) }
    is Bitmap -> {
        val output = ByteArrayOutputStream()
        check(value.compress(Bitmap.CompressFormat.PNG, 100, output)) { "Bitmap PNG capture failed" }
        NavigationRawDiagnostics.Binary(output.toByteArray(), "png-base64")
    }
    is Parcelable -> {
        val parcel = Parcel.obtain()
        try {
            parcel.writeParcelable(value, 0)
            NavigationRawDiagnostics.Binary(parcel.marshall(), "parcel-base64")
        } finally { parcel.recycle() }
    }
    is Serializable -> {
        val output = ByteArrayOutputStream()
        ObjectOutputStream(output).use { it.writeObject(value) }
        NavigationRawDiagnostics.Binary(output.toByteArray(), "serialized-base64")
    }
    else -> null
}

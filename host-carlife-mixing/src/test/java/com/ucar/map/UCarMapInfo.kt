package com.ucar.map

/** Fixture with the audited upstream class name; never included in production sources. */
class UCarMapInfo(private val title: String, private val failSecond: Boolean = false) {
    fun getTitle1(): String = title
    fun getTitle2(): String {
        if (failSecond) throw IllegalStateException("fixture getter failure")
        return "预计 12:45 到达"
    }
}

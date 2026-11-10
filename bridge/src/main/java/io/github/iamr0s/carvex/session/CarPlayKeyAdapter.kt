package io.github.iamr0s.carvex.session

import io.github.iamr0s.carvex.sessioncore.HostKeyMapper

/**
 * 协议 → 宿主键码的翻译层。
 *
 * 这里**不再内置任何宿主码表**：媒体 usage 与 UI 事件前缀只翻译成语义，实际键码由
 * `HostKeyMapper`（宿主模块提供）给出。CarWith 的 8101…8115 等码值因此从 `:session` 移出。
 *
 * 表本身仍然没有持久状态、没有用户绑定查找：只有两端都能证明含义的 usage 才映射，
 * 未知 usage 返回 null，由调用方按"不支持"记录。
 */
class CarPlayKeyAdapter(private val mapper:HostKeyMapper?) {
    fun mediaUsage(usage:Int):Int? = mapper?.mediaKey(usage)

    /** Page-qualified HID mapping for Consumer, Telephony and future HID pages. */
    fun hidEvent(prefix:String,usage:Int):Int? = mapper?.hidKey(prefix,usage)

    /** Standard Consumer usages mapped to Android media-button events, independent of vendor codes. */
    fun systemMediaUsage(usage:Int):Int?=when(usage){
        0xcd->android.view.KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE
        0xb3->android.view.KeyEvent.KEYCODE_MEDIA_FAST_FORWARD
        0xb4->android.view.KeyEvent.KEYCODE_MEDIA_REWIND
        else->null
    }

    fun continuousMediaUsage(usage:Int):Boolean=usage==0xb3||usage==0xb4

    fun uiEvent(eventId:String):Int? = mapper?.uiKey(eventId)
}

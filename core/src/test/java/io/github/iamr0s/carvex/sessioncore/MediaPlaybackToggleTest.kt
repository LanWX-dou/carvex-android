package io.github.iamr0s.carvex.sessioncore

import org.junit.Assert.assertEquals
import org.junit.Assert.assertNull
import org.junit.Test

class MediaPlaybackToggleTest {
    @Test fun unknownPlaybackNeverGuessesPlayOrPause() {
        val state=MediaPlaybackToggle()
        repeat(3){assertNull(state.choose(100,101))}
        state.playbackState(true)
        state.playbackState(null)
        assertNull(state.choose(100,101))
    }
    @Test fun rejectedOrUnconfirmedPressDoesNotInvertNextAction() {
        val state=MediaPlaybackToggle()
        state.playbackState(true)
        repeat(3){assertEquals(101,state.choose(100,101))}
        state.playbackState(false)
        repeat(3){assertEquals(100,state.choose(100,101))}
    }

    @Test fun selectionUsesLatestPlayerReportAtDispatch() {
        val state=MediaPlaybackToggle()
        state.playbackState(true)
        val queuedPress={state.choose(100,101)}
        state.playbackState(false)
        assertEquals(100,queuedPress())
        state.playbackState(null)
        assertNull(queuedPress())
    }
}

package io.github.iamr0s.carvex.platform

/** Only a unique metadata match can supply state for the host's current song. */
object MediaSessionSelection {
    data class Item(val title: String?, val artist: String?)

    fun index(target: Item, candidates: List<Item>,
              additionalMatch: ((Item, Item) -> Boolean)? = null): Int? {
        val title = target.title?.trim()?.takeIf { it.isNotEmpty() } ?: return null
        val artist = target.artist?.trim()?.takeIf { it.isNotEmpty() }
        return candidates.indices.filter { index ->
            val item = candidates[index]
            (item.title?.trim() == title && (artist == null || item.artist?.trim() == artist)) ||
                additionalMatch?.invoke(target, item) == true
        }.singleOrNull()
    }
}

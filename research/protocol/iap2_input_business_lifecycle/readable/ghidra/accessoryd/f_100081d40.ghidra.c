/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100081d40
 * original code SHA256: 20d05e9b56ff898f0961ee7493cc3bcb192815a18a4dc9051161bb91ffdd5867
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void ____setNowPlayingInfoHandler_block_invoke(long param_1)

{
  _platform_nowPlaying_setPlaybackElapsedTime(*(undefined4 *)(param_1 + 0x20));
  return;
}


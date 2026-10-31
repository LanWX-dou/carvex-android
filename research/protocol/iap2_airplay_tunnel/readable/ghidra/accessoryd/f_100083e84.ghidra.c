/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100083e84
 * original code SHA256: ce0e56e42ef4f350283ec66b91424f42d4f6afe65a859b63d59b02d3ba1181cc
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_release_x8 replaced with injection: _objc_release_fixup */

undefined8 _mfi4Auth_relay_cleanup(long param_1)

{
  long lVar1;
  long lVar2;
  
  lVar1 = 0;
  lVar2 = 3;
  do {
    *(undefined8 *)(param_1 + 0xe8 + lVar1 * 8) = 0;
    lVar1 = lVar1 + 1;
    lVar2 = lVar2 + -1;
  } while (lVar2 != 0);
  return 0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10017b5fc
 * original code SHA256: 64df48190b7fd9e3d9860e918d925f41792bd7304feeb0b2cd64181cddc2749a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 _acc_protocolParser_iAP2_create(long *param_1)

{
  undefined4 *puVar1;
  
  if ((param_1 != (long *)0x0) && (*param_1 == 0)) {
    puVar1 = (undefined4 *)_malloc_type_calloc(1,0x18,0x10100407125d048);
    *param_1 = (long)puVar1;
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = 0;
      *(undefined2 *)(puVar1 + 1) = 0;
      *(undefined1 *)((long)puVar1 + 6) = 0;
      *(undefined8 *)(puVar1 + 2) = 0;
      *(undefined2 *)(puVar1 + 4) = 0;
      *(undefined1 *)((long)puVar1 + 0x12) = 0;
      return 1;
    }
  }
  return 0;
}


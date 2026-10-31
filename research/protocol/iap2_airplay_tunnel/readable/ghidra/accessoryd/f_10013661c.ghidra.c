/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013661c
 * original code SHA256: eda038078c45df7cc973764ab65bcffe6191387497a6fba290ee005c1f316e21
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_sessionLog_start(long param_1)

{
  undefined4 *puVar1;
  long *plVar2;
  dispatch_queue_t pdVar3;
  undefined8 uVar4;
  
  uVar4 = 0;
  if (param_1 != 0) {
    puVar1 = (undefined4 *)_malloc_type_malloc(0xa8,0x1090040e72c28dd);
    uVar4 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      plVar2 = (long *)_malloc_type_calloc(1,0x50,0x10200401884bd0f);
      if (plVar2 == (long *)0x0) {
        _free(puVar1);
        uVar4 = 0;
      }
      else {
        *plVar2 = param_1;
        pdVar3 = _dispatch_queue_create
                           ("LoggingProtocol-DeviceContext-Queue",(dispatch_queue_attr_t)0x0);
        plVar2[8] = (long)pdVar3;
        *(long **)(puVar1 + 8) = plVar2;
        *puVar1 = 0;
        *(undefined2 *)(puVar1 + 1) = 2;
        *(undefined8 *)(puVar1 + 4) = 0;
        *(undefined2 *)(puVar1 + 6) = 0;
        puVar1[2] = 0;
        *(undefined8 *)(puVar1 + 0x16) = 0;
        *(undefined8 *)(puVar1 + 0x18) = 0;
        *(undefined8 *)(puVar1 + 0x14) = 0;
        *(undefined1 *)(puVar1 + 0x1a) = 0;
        puVar1[0x1b] = 2;
        *(undefined1 *)(puVar1 + 0x1c) = 0;
        puVar1[0x1d] = 0;
        uVar4 = 1;
        *(undefined4 **)(param_1 + 0x1c8) = puVar1;
      }
    }
  }
  return uVar4;
}


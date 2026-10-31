/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100007728
 * original code SHA256: 7b7f2c7d31343b147db48a3522d9a853a3b9dc3ebb27b7f8c0de57f80700b017
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkRunLoopSignal(long param_1,long param_2,undefined8 param_3)

{
  code *pcVar1;
  undefined8 *puVar2;
  ulong unaff_x30;
  undefined *local_48;
  undefined8 local_40;
  code *local_38;
  undefined *puStack_30;
  long local_28;
  undefined8 uStack_20;
  undefined8 local_18;
  
  if (param_2 == 0) {
    puVar2 = *(undefined8 **)(param_1 + 0x10);
    if (puVar2[3] != 0) {
      local_48 = PTR___NSConcreteStackBlock_10022bb78;
      local_40 = DAT_1001b3078;
      local_38 = ___iAP2LinkRunLoopSignal_block_invoke;
      puStack_30 = &___block_descriptor_56_e5_v8__0l;
      uStack_20 = 0;
      local_28 = param_1;
      local_18 = param_3;
      _acc_protocolEndpoint_performAsync(*puVar2,*(undefined1 *)(puVar2 + 4),puVar2[3],&local_48);
    }
    return;
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100007738);
    (*pcVar1)();
  }
  _iAP2LinkRunLoopRunOnce();
  return;
}


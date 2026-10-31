/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a761d8
 * original code SHA256: 374e8a9a76ddb4534157210e642b388473af60873191606a61189067b454c516
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _screenstreamudp_handleClearScreen(undefined8 param_1,undefined1 param_2)

{
  undefined8 *puVar1;
  undefined8 local_50;
  undefined8 local_48;
  code *local_40;
  undefined *puStack_38;
  undefined8 local_30;
  undefined1 local_28;
  
  puVar1 = (undefined8 *)func_0x00025810ac50();
  local_50 = _DAT_2681b4ed0;
  local_48 = DAT_251c6b008;
  local_40 = ___screenstreamudp_handleClearScreen_block_invoke;
  puStack_38 = &___block_descriptor_41_e5_v8__0l;
  local_30 = param_1;
  local_28 = param_2;
  func_0x0002580f54f0(&local_40,*puVar1,&local_50);
  return;
}


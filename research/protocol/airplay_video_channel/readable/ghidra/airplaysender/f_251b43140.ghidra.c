/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b43140
 * original code SHA256: b5267327c0748bf692e967da725445b087bba55417c6893dffa04e594c912af6
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _screenstream_handleFatalError(undefined8 param_1,undefined4 param_2,long param_3)

{
  undefined8 uVar1;
  int iVar2;
  undefined8 *puVar3;
  undefined8 local_a0;
  undefined8 local_98;
  code *local_90;
  undefined *puStack_88;
  undefined8 local_80;
  undefined8 local_78;
  undefined8 local_70;
  code *local_68;
  undefined *puStack_60;
  long local_58;
  undefined8 uStack_50;
  undefined4 local_48;
  
  puVar3 = (undefined8 *)func_0x00025810ac50();
  if ((_gLogCategory_APEndpointStreamScreen < 0x33) &&
     ((_gLogCategory_APEndpointStreamScreen != -1 ||
      (iVar2 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000032), iVar2 != 0))))
  {
    func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                        "void screenstream_handleFatalError(FigEndpointStreamRef, OSStatus, CFStringRef)"
                        ,0x2000032,"%@ ### handle error: %d (%@)\n");
  }
  func_0x0002580f6a60(param_1);
  if (param_3 != 0) {
    func_0x0002580f6a60(param_3);
  }
  uVar1 = DAT_251c6aff8;
  local_78 = _DAT_2681b4ed0;
  local_70 = DAT_251c6aff8;
  local_68 = ___screenstream_handleFatalError_block_invoke;
  puStack_60 = &___block_descriptor_tmp_42;
  local_58 = param_3;
  uStack_50 = param_1;
  local_48 = param_2;
  func_0x0002580f4bb0(puVar3[0xc],&local_78);
  func_0x0002580f6a60(param_1);
  local_a0 = _DAT_2681b4ed0;
  local_98 = uVar1;
  local_90 = ___screenstream_handleFatalError_block_invoke_2;
  puStack_88 = &___block_descriptor_tmp_43;
  local_80 = param_1;
  func_0x0002580f4bb0(*puVar3,&local_a0);
  return;
}


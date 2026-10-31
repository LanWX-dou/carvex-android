/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a77178
 * original code SHA256: 98dccc76e21906ec43e8d93139fbeae4ba41073f199fcf72e16b944ecedd31cd
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void __APEndpointStreamScreenAVCWrapper_getVideoResolutionFromOptions_width_height__
               (undefined1 param_1 [16],undefined8 param_2,undefined8 param_3,undefined8 param_4,
               double *param_5,long *param_6,long *param_7)

{
  int iVar1;
  undefined8 uVar2;
  undefined1 auVar3 [16];
  double dVar4;
  
  auVar3._0_8_ = (long)*param_5;
  auVar3._8_8_ = (long)param_5[1];
  auVar3 = NEON_ucvtf(auVar3,8);
  dVar4 = auVar3._8_8_;
  uVar2 = func_0x00025810d280();
  auVar3 = func_0x00025810c320(auVar3,dVar4,uVar2,param_2);
  iVar1 = func_0x000258109e20(&cfstringStruct_276131590,(int)auVar3._0_8_);
  *param_6 = (long)iVar1;
  iVar1 = func_0x000258109e20(&cfstringStruct_2761315b0,(int)dVar4);
  *param_7 = (long)iVar1;
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2518d3bdc
 * original code SHA256: 0f604c269b06ae7229dade8089fe43173a53cefc5d42fe43658fa1363072071a
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 __SetSecurityInfoAES(long param_1,undefined8 *param_2,undefined8 *param_3)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  lVar1 = param_1 + 0x140;
  func_0x000258109180(lVar1);
  *(undefined8 *)(param_1 + 0x158) = 0;
  uVar2 = func_0x000258109190(lVar1,param_2,param_3,0);
  if ((int)uVar2 == 0) {
    *(long *)(param_1 + 0x158) = lVar1;
    uVar3 = *param_2;
    *(undefined8 *)(param_1 + 0x168) = param_2[1];
    *(undefined8 *)(param_1 + 0x160) = uVar3;
    uVar3 = *param_3;
    *(undefined8 *)(param_1 + 0x178) = param_3[1];
    *(undefined8 *)(param_1 + 0x170) = uVar3;
  }
  else {
    func_0x000258109a30(uVar2,"_SetSecurityInfoAES",0x153f,0);
  }
  return uVar2;
}


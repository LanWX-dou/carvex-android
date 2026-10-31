/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x226ee9764
 * original code SHA256: be0265dd0168795e9bfab30c4b4017f7cd19d82a7fa1a93752da12b17242fcc9
 * source SHA256: d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _APSEncryptionUtilsDeriveAESKeySHA512ForScreen
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  long lVar4;
  long lVar5;
  char *pcVar6;
  undefined1 *local_60;
  undefined1 *local_58;
  
  local_60 = (undefined1 *)0x0;
  local_58 = (undefined1 *)0x0;
  iVar1 = func_0x00022818b6d0(&local_58,"%s%llu");
  lVar5 = (long)iVar1;
  pcVar6 = "AirPlayStreamIV";
  iVar2 = func_0x00022818b6d0(&local_60,"%s%llu");
  lVar4 = (long)iVar2;
  _APSEncryptionUtilsDeriveAESKeySHA512
            (param_1,param_2,local_58,lVar5,local_60,lVar4,param_4,param_5,pcVar6,param_3);
  puVar3 = local_58;
  if (iVar1 != 0) {
    do {
      *puVar3 = 0;
      lVar5 = lVar5 + -1;
      puVar3 = puVar3 + 1;
    } while (lVar5 != 0);
  }
  puVar3 = local_60;
  if (iVar2 != 0) {
    do {
      *puVar3 = 0;
      lVar4 = lVar4 + -1;
      puVar3 = puVar3 + 1;
    } while (lVar4 != 0);
  }
  func_0x00022813e830(local_58);
  func_0x00022813e830(local_60);
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10063cea4
 * original code SHA256: 534729da074c0ad3e320a163495a022d8d4d43a08b13ed724084e8859dc8f950
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void phone_fn_10063cea4(void)

{
  undefined8 *puVar1;
  char *pcStack_58;
  undefined8 uStack_50;
  undefined1 uStack_41;
  char **ppcStack_40;
  undefined8 uStack_38;
  
  pcStack_58 = "kCBMsgIdPairingAgentCreateMsg";
  uStack_50 = 0x1d;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063d1e0;
  puVar1[5] = 0;
  pcStack_58 = "kCBMsgIdPairingAgentDestroyMsg";
  uStack_50 = 0x1e;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063d430;
  puVar1[5] = 0;
  pcStack_58 = "kCBMsgIdPairingAgentStartMsg";
  uStack_50 = 0x1c;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063d630;
  puVar1[5] = 0;
  pcStack_58 = "kCBMsgIdPairingAgentStopMsg";
  uStack_50 = 0x1b;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063d6f8;
  puVar1[5] = 0;
  pcStack_58 = "kCBMsgIdPairingAgentCancelPairingMsg";
  uStack_50 = 0x24;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063d7c0;
  puVar1[5] = 0;
  pcStack_58 = "kCBMsgIdPairingAgentSetPincodeMsg";
  uStack_50 = 0x21;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063d888;
  puVar1[5] = 0;
  pcStack_58 = "kCBMsgIdPairingAgentAcceptSSPMsg";
  uStack_50 = 0x20;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063d98c;
  puVar1[5] = 0;
  pcStack_58 = "kCBMsgIdPairingAgentDeletePairedDeviceMsg";
  uStack_50 = 0x29;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063da90;
  puVar1[5] = 0;
  pcStack_58 = "kCBMsgIdPairingAgentSetIOCapabilityMsg";
  uStack_50 = 0x26;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063db7c;
  puVar1[5] = 0;
  pcStack_58 = "kCBMsgIdPairingAgentClearOOBDataForDeviceMsg";
  uStack_50 = 0x2c;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063dc68;
  puVar1[5] = 0;
  pcStack_58 = "kCBMsgIdPairingAgentSetOOBDataForDeviceMsg";
  uStack_50 = 0x2a;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063dd54;
  puVar1[5] = 0;
  pcStack_58 = "kCBMsgIdPairingAgentGetLocalOOBDataMsg";
  uStack_50 = 0x26;
  uStack_38 = 0x100cae230;
  puVar1 = &uStack_38;
  ppcStack_40 = &pcStack_58;
  FUN_10063e1a4(puVar1,&pcStack_58,&UNK_1009361a8,&ppcStack_40,&uStack_41);
  puVar1[4] = &LAB_10063dff0;
  puVar1[5] = 0;
  return;
}


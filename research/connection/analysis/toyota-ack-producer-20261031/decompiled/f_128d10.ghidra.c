/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x128d10
 * original code SHA256: cc6fd2191618e07bdcfe8f05ff989a751ff1037b58ddb6d03beb8488ffe7a73c
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodIap2::syncLink(int) */

void __thiscall CIpodIap2::syncLink(CIpodIap2 *this,int param_1)

{
  ushort uVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined2 uStack_10080;
  undefined1 uStack_1007e;
  undefined1 uStack_1007d;
  undefined2 uStack_1007c;
  undefined1 uStack_1007a;
  undefined1 uStack_10079;
  undefined2 uStack_10078;
  undefined2 uStack_10076;
  char cStack_10074;
  undefined2 uStack_10073;
  undefined1 uStack_10071;
  undefined2 uStack_10070;
  undefined8 uStack_1006e;
  undefined8 uStack_10066;
  undefined8 uStack_1005e;
  undefined8 uStack_10056;
  undefined8 uStack_1004e;
  undefined8 uStack_10046;
  undefined8 uStack_1003e;
  undefined8 uStack_10036;
  undefined8 uStack_1002e;
  undefined8 uStack_10026;
  undefined8 uStack_1001e;
  undefined8 uStack_10016;
  undefined8 uStack_1000e;
  undefined4 uStack_10006;
  undefined2 uStack_10002;
  uchar auStack_10000 [65536];
  
  CIpodLog::i("[ Accessory ] step 3:  SYN\n");
  uStack_10080 = 0x501;
  uStack_1007d = 0;
  uStack_1007a = 0;
  cStack_10074 = 0;
  uStack_10073 = 0;
  uStack_10071 = 0;
  uStack_10070 = 0;
  uStack_1006e = 0;
  uStack_10066 = 0;
  uStack_1005e = 0;
  uStack_10056 = 0;
  uStack_1004e = 0;
  uStack_10046 = 0;
  uStack_1003e = 0;
  uStack_10036 = 0;
  uStack_1002e = 0;
  uStack_10026 = 0;
  uStack_1001e = 0;
  uStack_10016 = 0;
  uStack_10002 = 0;
  uStack_1000e = 0;
  uStack_10006 = 0;
  if (param_1 - 3U < 2) {
    uStack_1007e = 8;
    uStack_1007c = 0xdc05;
    uStack_10079 = 0x49;
  }
  else {
    uStack_1007e = 0x10;
    uStack_1007c = 0xd007;
    uStack_10079 = 0x16;
  }
  uStack_10078 = 0x31e;
  uStack_10076 = 10;
  iVar2 = CIpodConfig::getMode();
  cStack_10074 = (iVar2 == 2) + '\x01';
  lVar3 = CIpodConfig::getIdentification();
  if (((*(byte *)(lVar3 + 0xc1) >> 1 & 1) == 0) &&
     (lVar3 = CIpodConfig::getIdentification(), (*(byte *)(lVar3 + 0xc1) >> 2 & 1) == 0)) {
    uVar7 = 0x10;
    iVar2 = 0xd;
    uVar4 = 0xd;
    iVar5 = 0xf;
    iVar6 = 0xe;
  }
  else {
    iVar2 = 0x10;
    uVar4 = 0x10;
    uStack_10073 = 0x10b;
    uVar7 = 0x13;
    uStack_10071 = 1;
    iVar5 = 0x12;
    iVar6 = 0x11;
  }
  lVar3 = CIpodConfig::getIdentification();
  if ((*(byte *)(lVar3 + 0xc0) >> 6 & 1) != 0) {
    lVar3 = CIpodConfig::getIdentification();
    if (*(short *)(lVar3 + 0xfc) == 0) {
      *(undefined1 *)((long)&uStack_10080 + (long)iVar2) = 0xc;
      *(undefined1 *)((long)&uStack_10080 + (long)iVar6) = 2;
      *(undefined1 *)((long)&uStack_10080 + (long)iVar5) = 1;
      uVar4 = uVar7;
    }
  }
  uVar1 = createLinkPacket(this,0xffffff80,this[0x10],this[0x11],0,&uStack_10080,uVar4,auStack_10000
                          );
  write(this,auStack_10000,uVar1);
  return;
}


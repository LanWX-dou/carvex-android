/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000221a8
 * original code SHA256: 7f5791529bfcb207168ca75fab75b20d54b5d8361f48af63deeb0ca1610c1676
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



long _mfi4Auth_util_parseMessage
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  
  uVar1 = _CFDataGetLength(param_3);
  lVar2 = _CFDataGetBytePtr(param_3);
  _iAP2MsgInitWithSom(param_2,param_4,0,0,0,0,0);
  uVar3 = _iAP2MsgParserInit(0xffff,param_1,0,param_4);
  uVar1 = uVar1 & 0xffffffff;
  if (uVar1 != 0) {
    lVar5 = 0;
    do {
      lVar4 = _iAP2MsgParserConsumeByte(uVar3,*(undefined1 *)(lVar2 + lVar5),param_2);
      if (lVar4 != 0) {
        return lVar4;
      }
      lVar5 = lVar5 + 1;
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0);
  }
  return 0;
}


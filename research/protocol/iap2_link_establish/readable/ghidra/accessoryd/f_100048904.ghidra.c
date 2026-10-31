/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100048904
 * original code SHA256: 319b289dc1b9bd4d2c694a67ed0c92d0928a2bc237c033190b414dd91e1c05d8
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x2 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

undefined8 _mfi4Auth_protocol_initMessage_RequestAuthCert(long param_1,long *param_2)

{
  undefined2 uVar1;
  long lVar2;
  ID IVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  if (param_1 == 0) {
    _mfi4Auth_protocol_initMessage_RequestAuthCert_cold_4();
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    _mfi4Auth_protocol_initMessage_RequestAuthCert_cold_3();
  }
  else {
    if (param_2 != (long *)0x0) {
      uVar1 = *(undefined2 *)(param_1 + 0x150);
      lVar2 = _malloc_type_malloc(0x48,0x109004066c3afe2);
      *param_2 = lVar2;
      if (lVar2 != 0) {
        _iAP2MsgInitWithSom(lVar2,uVar1,0x5112,*(undefined8 *)(param_1 + 0x10),
                            *(undefined4 *)(param_1 + 0x18),0,0);
        if (param_1 == 0) {
          lVar2 = *param_2;
          if (iRam00000000000000e0 == 0) {
            IVar3 = 0x318;
          }
          else {
            IVar3 = 0x21c;
          }
          uVar4 = 0;
          uVar5 = 0x20;
        }
        else {
          lVar2 = *param_2;
          IVar3 = _objc_retainAutorelease(param_1);
          IVar3 = objc_stub::bytes(IVar3);
          uVar4 = 1;
          uVar5 = 0x14;
        }
        _iAP2MsgAddArrayU8Param(lVar2,0,uVar4,IVar3,uVar5);
        *(undefined2 *)(param_1 + 0x1c) = 0x5112;
        return 0;
      }
      _mfi4Auth_protocol_initMessage_RequestAuthCert_cold_1();
      return 0xffffffff;
    }
    _mfi4Auth_protocol_initMessage_RequestAuthCert_cold_2();
  }
  return 1;
}


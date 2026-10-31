/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100044f3c
 * original code SHA256: b09c09befcf5bc06de1fd1cf2721e8ca5029222d26d60ad594d45d533b08e124
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _mfi4Auth_protocol_initMessage_RequestAuthChallengeResponse(long param_1,long *param_2)

{
  char cVar1;
  long lVar2;
  undefined4 uVar3;
  
  if (param_1 == 0) {
    _mfi4Auth_protocol_initMessage_RequestAuthChallengeResponse_cold_5();
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    _mfi4Auth_protocol_initMessage_RequestAuthChallengeResponse_cold_4();
  }
  else if (param_2 == (long *)0x0) {
    _mfi4Auth_protocol_initMessage_RequestAuthChallengeResponse_cold_3();
  }
  else {
    if (*(int *)(param_1 + 0xe0) == 0) {
      lVar2 = _malloc_type_malloc(0x48,0x109004066c3afe2);
      *param_2 = lVar2;
      if (lVar2 != 0) {
        cVar1 = *(char *)(param_1 + 0xd0);
        _iAP2MsgInitWithSom(lVar2,0,0x5115,*(undefined8 *)(param_1 + 0x10),
                            *(undefined4 *)(param_1 + 0x18),0,0);
        uVar3 = 0x21;
        if (cVar1 != '\x02') {
          uVar3 = 0x10;
        }
        _iAP2MsgAddArrayU8Param(*param_2,0,0,param_1 + 0x2c0,uVar3);
        *(undefined2 *)(param_1 + 0x1c) = 0x5115;
        return 0;
      }
      _mfi4Auth_protocol_initMessage_RequestAuthChallengeResponse_cold_2();
      return 0xffffffff;
    }
    _mfi4Auth_protocol_initMessage_RequestAuthChallengeResponse_cold_1();
  }
  return 1;
}


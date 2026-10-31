/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x226efbecc
 * original code SHA256: 376c19876bc30330134a1bb6e3eb7f55ee710582882bd076d7e96723c7fc8119
 * source SHA256: d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _APSCryptorCBCCreate(undefined8 param_1,long param_2,long param_3,long *param_4)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long local_48;
  
  local_48 = 0;
  if (param_2 == 0) {
    uVar4 = 0xfffee7e1;
    _APSLogErrorAt(0,"APSCryptorCBCCreate",0x92,0);
  }
  else {
    if (param_3 == 0) {
      uVar4 = 0xfffee7e1;
      uVar2 = 0;
      uVar5 = 0x93;
    }
    else {
      if (_APSCryptorGetClassID_sRegisterOnce != -1) {
        func_0x000228143b00(&_APSCryptorGetClassID_sRegisterOnce,&_APSCryptorGetClassID_sClassID,
                            _cryptor_registerBaseClass);
      }
      uVar2 = func_0x00022818bff0(param_1,&_kAPSCryptorCBCVTable,_APSCryptorGetClassID_sClassID,
                                  &local_48);
      if ((int)uVar2 == 0) {
        lVar3 = func_0x00022818bdd0(local_48);
        uVar4 = func_0x000228144160(param_2);
        uVar2 = func_0x000228144160(param_3);
        uVar2 = func_0x00022818b610(lVar3,uVar4,uVar2,1);
        if ((int)uVar2 == 0) {
          uVar4 = func_0x000228144160(param_2);
          uVar2 = func_0x000228144160(param_3);
          uVar2 = func_0x00022818b610(lVar3 + 0x18,uVar4,uVar2,0);
          if ((int)uVar2 == 0) {
            if ((_gLogCategory_APSCryptorCBC < 0x1f) &&
               ((_gLogCategory_APSCryptorCBC != -1 ||
                (iVar1 = func_0x00022818d2b0(&_gLogCategory_APSCryptorCBC,0x200001e), iVar1 != 0))))
            {
              func_0x00022818cd80(&_gLogCategory_APSCryptorCBC,
                                  "OSStatus APSCryptorCBCCreate(CFAllocatorRef, CFDataRef, CFDataRef, APSCryptorRef *)"
                                  ,0x200001e,"APSCryptorCBC %p created.\n");
            }
            *param_4 = local_48;
            return 0;
          }
          uVar5 = 0x9f;
          uVar4 = uVar2;
        }
        else {
          uVar5 = 0x9c;
          uVar4 = uVar2;
        }
      }
      else {
        uVar5 = 0x97;
        uVar4 = uVar2;
      }
    }
    _APSLogErrorAt(uVar2,"APSCryptorCBCCreate",uVar5,0);
    if (local_48 != 0) {
      func_0x00022813f190();
    }
  }
  return uVar4;
}


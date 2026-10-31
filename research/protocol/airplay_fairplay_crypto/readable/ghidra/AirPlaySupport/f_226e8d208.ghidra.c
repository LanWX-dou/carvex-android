/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x226e8d208
 * original code SHA256: 44350ccee07750a72e157cbda890339b55d76aa17cfa5c23d12799c612461faa
 * source SHA256: d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _APSCryptorCTRCreate(undefined8 param_1,long param_2,long param_3,long *param_4)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long local_38;
  
  local_38 = 0;
  if (param_2 == 0) {
    uVar3 = 0xfffee7e1;
    _APSLogErrorAt(0,"APSCryptorCTRCreate",0x83,0);
  }
  else {
    if (param_3 == 0) {
      uVar3 = 0xfffee7e1;
      uVar2 = 0;
      uVar4 = 0x84;
    }
    else {
      if (_APSCryptorGetClassID_sRegisterOnce != -1) {
        func_0x000228143b00(&_APSCryptorGetClassID_sRegisterOnce,&_APSCryptorGetClassID_sClassID,
                            _cryptor_registerBaseClass);
      }
      uVar2 = func_0x00022818bff0(param_1,&_kAPSCryptorCTRVTable,_APSCryptorGetClassID_sClassID,
                                  &local_38);
      if ((int)uVar2 == 0) {
        uVar3 = func_0x00022818bdd0(local_38);
        uVar2 = func_0x000228144160(param_2);
        uVar4 = func_0x000228144160(param_3);
        uVar2 = func_0x00022818b640(uVar3,uVar2,uVar4);
        if ((int)uVar2 == 0) {
          if ((_gLogCategory_APSCryptorCTR < 0x1f) &&
             ((_gLogCategory_APSCryptorCTR != -1 ||
              (iVar1 = func_0x00022818d2b0(&_gLogCategory_APSCryptorCTR,0x200001e), iVar1 != 0)))) {
            func_0x00022818cd80(&_gLogCategory_APSCryptorCTR,
                                "OSStatus APSCryptorCTRCreate(CFAllocatorRef, CFDataRef, CFDataRef, APSCryptorRef *)"
                                ,0x200001e,"APSCryptorCTR %p created.\n");
          }
          *param_4 = local_38;
          return 0;
        }
        uVar4 = 0x8d;
        uVar3 = uVar2;
      }
      else {
        uVar4 = 0x88;
        uVar3 = uVar2;
      }
    }
    _APSLogErrorAt(uVar2,"APSCryptorCTRCreate",uVar4,0);
    if (local_38 != 0) {
      func_0x00022813f190();
    }
  }
  return uVar3;
}


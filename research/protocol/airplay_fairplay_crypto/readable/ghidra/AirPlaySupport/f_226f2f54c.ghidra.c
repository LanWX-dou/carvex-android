/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x226f2f54c
 * original code SHA256: 74037b22dfbe361414c1f1d5603dfe02763d7f541f8ca6e9a176ad8575984e1e
 * source SHA256: d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_APSCryptorChaCha20Poly1305Create(undefined8 param_1,long param_2,undefined1 param_3,long *param_4)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined1 *puVar4;
  long local_38;
  
  local_38 = 0;
  if (param_2 == 0) {
    uVar3 = 0x97;
  }
  else {
    lVar2 = func_0x00022813f060(param_2);
    if (0x1f < lVar2) {
      if (_APSCryptorGetClassID_sRegisterOnce != -1) {
        func_0x000228143b00(&_APSCryptorGetClassID_sRegisterOnce,&_APSCryptorGetClassID_sClassID,
                            _cryptor_registerBaseClass);
      }
      uVar3 = func_0x00022818bff0(param_1,&_kAPSCryptorChaCha20Poly1305VTable,
                                  _APSCryptorGetClassID_sClassID,&local_38);
      if ((int)uVar3 == 0) {
        puVar4 = (undefined1 *)func_0x00022818bdd0(local_38);
        uVar3 = func_0x00022813f1a0(param_2);
        *(undefined8 *)(puVar4 + 0x108) = uVar3;
        *puVar4 = param_3;
        if ((_gLogCategory_APSCryptorChaCha20Poly1305 < 0x1f) &&
           ((_gLogCategory_APSCryptorChaCha20Poly1305 != -1 ||
            (iVar1 = func_0x00022818d2b0(&_gLogCategory_APSCryptorChaCha20Poly1305,0x200001e),
            iVar1 != 0)))) {
          func_0x00022818cd80(&_gLogCategory_APSCryptorChaCha20Poly1305,
                              "OSStatus APSCryptorChaCha20Poly1305Create(CFAllocatorRef, CFDataRef, Boolean, APSCryptorRef *)"
                              ,0x200001e,"APSCryptorChaCha20Poly1305 %p created.\n");
        }
        *param_4 = local_38;
        return 0;
      }
      _APSLogErrorAt(uVar3,"APSCryptorChaCha20Poly1305Create",0x9c,0);
      if (local_38 == 0) {
        return uVar3;
      }
      func_0x00022813f190();
      return uVar3;
    }
    uVar3 = 0x98;
  }
  _APSLogErrorAt(0,"APSCryptorChaCha20Poly1305Create",uVar3,0);
  return 0xfffee7e1;
}


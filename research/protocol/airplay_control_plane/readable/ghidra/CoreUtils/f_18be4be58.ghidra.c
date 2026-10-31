/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be4be58
 * original code SHA256: ce82fa0550bff9230974cb6cc28577e9584e4ab4434310995644a1291663a760
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _HTTPMessageCreate(long *param_1)

{
  long lVar1;
  undefined8 uVar2;
  
  if (_gHTTPMessageInitOnce != -1) {
    func_0x0001900cc2c0(&_gHTTPMessageInitOnce,0,__HTTPMessageGetTypeID);
  }
  lVar1 = func_0x0001900ce6a0(0,_gHTTPMessageTypeID,0x2630,0);
  if (lVar1 == 0) {
    uVar2 = 0xffffe5b8;
  }
  else {
    func_0x0001900cc250(lVar1 + 0x10,0x2630);
    *(undefined4 *)(lVar1 + 0x2600) = 0xffffffff;
    *(undefined4 *)(lVar1 + 0x2618) = 0xffffffff;
    *(undefined8 *)(lVar1 + 0x2158) = 16000000;
    _HTTPMessageReset(lVar1);
    uVar2 = 0;
    *param_1 = lVar1;
  }
  return uVar2;
}


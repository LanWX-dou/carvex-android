/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100060ff4
 * original code SHA256: cff738266b93a0852ace977223949080e35a4d5f1e8823ac56758b6bdb1326a5
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 phone_fn_100060ff4(void)

{
  int iVar1;
  ulong uStack_70;
  ulong uStack_68;
  
  _pthread_setname_np("StackLoop");
  if (bRam0000000100c25cc0 == 1) {
    uStack_70 = 0;
    uStack_68 = 0;
    do {
      _pthread_mutex_lock(0x100c25d00);
      do {
        if ((uRam0000000100c25cc8 == 0) || ((bRam0000000100c25d58 & 1) != 0)) break;
        uStack_70 = (ulong)uRam0000000100c25cc8 / 1000;
        uStack_68 = (ulong)((uRam0000000100c25cc8 % 1000) * 1000000);
        iVar1 = 0xc25cd0;
        _pthread_cond_timedwait_relative_np(0x100c25cd0,0x100c25d00,&uStack_70);
      } while (iVar1 != 0x3c);
      uRam0000000100c25cc8 = 0xffffffff;
      _pthread_mutex_unlock(0x100c25d00);
      FUN_100003a30();
      FUN_100060df0();
      FUN_100010fe8();
    } while ((bRam0000000100c25cc0 & 1) != 0);
  }
  return 0;
}


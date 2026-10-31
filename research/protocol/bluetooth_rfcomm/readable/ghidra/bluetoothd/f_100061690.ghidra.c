/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100061690
 * original code SHA256: 9c329deb7c0af81b125e3516a9fcaef8df2480bcec6399442d620653fe66a5c6
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_100061690(undefined4 param_1)

{
  code *pcVar1;
  ulong unaff_x30;
  
  _pthread_mutex_lock(0x100c25d00);
  uRam0000000100c25cc8 = param_1;
  _pthread_cond_signal(0x100c25cd0);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000616e4);
    (*pcVar1)();
  }
  _pthread_mutex_unlock(0x100c25d00);
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fda6c70
 * original code SHA256: c37aab84649f08bc1cfa89b48b92fb711f998643b5d5b03baa180a38642fdd11
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Control flow encountered bad instruction data */

void _APTransportPackageHTTPSetURL(undefined8 param_1,long param_2)

{
  code *pcVar1;
  long *plVar2;
  long lVar3;
  ulong unaff_x30;
  
  plVar2 = (long *)func_0x0002500e5a60();
  lVar3 = *plVar2;
  if (param_2 != 0) {
    func_0x0002500903e0(param_2);
  }
  *plVar2 = param_2;
  if (lVar3 != 0) {
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x24fda6cc8);
      (*pcVar1)();
    }
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  return;
}


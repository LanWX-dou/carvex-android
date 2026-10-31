/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000cae54
 * original code SHA256: d07b5492924b235afaaddd550bf583d89a68ed61d142bb0c890076a6d028cdad
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 * _iAP2LinkRunLoopCreate(undefined8 param_1,undefined8 param_2)

{
  undefined8 uVar1;
  ulong uVar2;
  undefined8 in_x5;
  undefined8 in_x6;
  undefined8 *in_x7;
  
  if (in_x7 == (undefined8 *)0x0) {
    _iAP2LinkRunLoopCreate_cold_2();
  }
  else {
    in_x7[1] = 0;
    *in_x7 = 0;
    in_x7[3] = 0;
    in_x7[2] = 0;
    in_x7[9] = 0;
    in_x7[8] = 0;
    in_x7[0xb] = 0;
    in_x7[10] = 0;
    in_x7[5] = 0;
    in_x7[4] = 0;
    in_x7[7] = 0;
    in_x7[6] = 0;
    *in_x7 = in_x7;
    in_x7[2] = param_2;
    uVar1 = _iAP2LinkCreate(param_1,in_x7);
    in_x7[3] = uVar1;
    uVar2 = _iAP2LinkGetBuffSize(in_x5,in_x6);
    if (in_x7[3] != 0) {
      in_x7[1] = (long)in_x7 + (uVar2 & 0xffffffff) + 0x60;
      _iAP2LinkSetUseiAP2LinkRunLoop();
      _iAP2LinkStart(in_x7[3]);
      _iAP2LinkRunLoopInitImplementation(in_x7);
      return in_x7;
    }
  }
                    /* WARNING: Subroutine does not return */
  _iAP2LinkRunLoopCreate_cold_1();
}


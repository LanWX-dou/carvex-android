/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10006baac
 * original code SHA256: 5d28bc6b39e78140aaf020b45c6bf870ed4f305e3331173d5d13635eedcd1d11
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2FSMCreate(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined8 param_4,
                   undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                   undefined8 *param_9)

{
  if (param_9 != (undefined8 *)0x0) {
    *param_9 = param_4;
    *(undefined1 *)((long)param_9 + 9) = param_3;
    *(undefined1 *)(param_9 + 1) = param_1;
    *(undefined1 *)((long)param_9 + 10) = param_2;
    *(undefined1 *)((long)param_9 + 0xb) = param_3;
    param_9[2] = param_5;
    param_9[3] = param_6;
    param_9[4] = param_7;
    param_9[5] = param_8;
    return;
  }
                    /* WARNING: Subroutine does not return */
  _iAP2FSMCreate_cold_1();
}


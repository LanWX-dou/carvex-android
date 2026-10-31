/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100003424
 * original code SHA256: dc557ffa14983c98ed6ab09a8b24270e4e3d64ef6619c40737cbdbd4b1340518
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2MsgInit(undefined8 *param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,
                 undefined8 param_5,undefined8 param_6)

{
  long lVar1;
  
  if (param_1 != (undefined8 *)0x0) {
    param_1[5] = 0;
    param_1[4] = 0;
    param_1[7] = 0;
    param_1[6] = 0;
    param_1[8] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    param_1[3] = 0;
    param_1[2] = 0;
    param_1[3] = param_3;
    *(undefined4 *)(param_1 + 2) = param_4;
    param_1[5] = param_5;
    param_1[6] = param_6;
    if (param_3 == (undefined4 *)0x0) {
      lVar1 = 0;
    }
    else {
      *param_3 = (int)DAT_1001b3ad0;
      *(char *)(param_3 + 1) = (char)((uint)param_2 >> 8);
      *(char *)((long)param_3 + 5) = (char)param_2;
      lVar1 = (long)param_3 + 6;
    }
    param_1[4] = lVar1;
  }
  return;
}


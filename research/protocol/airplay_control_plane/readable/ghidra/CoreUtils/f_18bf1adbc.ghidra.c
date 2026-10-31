/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf1adbc
 * original code SHA256: 4f2d18b83eaba58430fb601786d520648eec1dcb5631c4e29be55856ae3a26d6
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_NetTransportChaCha20Poly1305Configure
          (undefined8 *param_1,undefined4 *param_2,undefined8 *param_3,undefined8 *param_4,
          undefined8 *param_5,undefined8 *param_6)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  puVar2 = (undefined4 *)func_0x0001900cc460(1,0x46c8,0x103004090bedf2e);
  if (puVar2 == (undefined4 *)0x0) {
    uVar3 = 0xffffe5b8;
  }
  else {
    *puVar2 = 0xffffffff;
    puVar1 = &_gLogCategory_NetTransportChaCha20Poly1305;
    if (param_2 != (undefined4 *)0x0) {
      puVar1 = param_2;
    }
    *(undefined4 **)(puVar2 + 2) = puVar1;
    puVar2[4] = 1;
    uVar4 = param_3[1];
    uVar3 = *param_3;
    uVar5 = param_3[2];
    *(undefined8 *)(puVar2 + 0x105a) = param_3[3];
    *(undefined8 *)(puVar2 + 0x1058) = uVar5;
    *(undefined8 *)(puVar2 + 0x1056) = uVar4;
    *(undefined8 *)(puVar2 + 0x1054) = uVar3;
    if (param_4 != (undefined8 *)0x0) {
      *(undefined8 *)(puVar2 + 0x105c) = *param_4;
    }
    uVar4 = param_5[1];
    uVar3 = *param_5;
    uVar5 = param_5[2];
    *(undefined8 *)(puVar2 + 0x11ae) = param_5[3];
    *(undefined8 *)(puVar2 + 0x11ac) = uVar5;
    *(undefined8 *)(puVar2 + 0x11aa) = uVar4;
    *(undefined8 *)(puVar2 + 0x11a8) = uVar3;
    if (param_6 != (undefined8 *)0x0) {
      *(undefined8 *)(puVar2 + 0x11b0) = *param_6;
    }
    uVar3 = 0;
    *param_1 = puVar2;
    param_1[1] = __NetTransportInitialize;
    param_1[2] = &__NetTransportFinalize;
    param_1[3] = __NetTransportRead;
    param_1[4] = __NetTransportWriteV;
  }
  return uVar3;
}


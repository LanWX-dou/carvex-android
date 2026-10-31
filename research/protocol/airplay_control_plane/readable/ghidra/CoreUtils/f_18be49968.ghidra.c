/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be49968
 * original code SHA256: 8ba447bd15f98dd3531e6d7e2c2c9dc6255162bbb2d70da47de32c625890413b
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



int __NetTransportRead(long param_1,ulong param_2,long *param_3,undefined4 *param_4)

{
  uint uVar1;
  long lVar2;
  undefined4 *puVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  long lVar10;
  int local_64;
  
  lVar2 = (long)param_4 + 0x2a;
  puVar3 = param_4 + 0x105c;
  lVar7 = *(long *)(param_4 + 0x1010);
  lVar10 = param_1;
LAB_18be499b8:
  uVar9 = *(long *)(param_4 + 0x1012) - lVar7;
  if (uVar9 != 0) {
    if (param_2 <= uVar9) {
      uVar9 = param_2;
    }
    func_0x0001900cc480(lVar10,lVar7,uVar9);
    lVar7 = *(long *)(param_4 + 0x1010) + uVar9;
    *(long *)(param_4 + 0x1010) = lVar7;
    lVar10 = lVar10 + uVar9;
    param_2 = param_2 - uVar9;
  }
  if (param_2 == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = param_4[4];
    if (iVar5 != 1) {
      if (iVar5 != 3) goto code_r0x00018be49a08;
      goto LAB_18be49a6c;
    }
    iVar5 = _SocketReadData(*param_4,param_4 + 10,2,param_4 + 8);
    if (iVar5 == 0) {
      uVar9 = (ulong)*(ushort *)(param_4 + 10);
      *(ulong *)(param_4 + 6) = uVar9;
      if (*(ushort *)(param_4 + 10) < 0x4001) {
        *(undefined8 *)(param_4 + 8) = 0;
        param_4[4] = 2;
        goto LAB_18be49a4c;
      }
      if ((_gLogCategory_NetTransportChaCha20Poly1305 < 0x3d) &&
         ((_gLogCategory_NetTransportChaCha20Poly1305 != -1 ||
          (iVar5 = __LogCategory_Initialize(&_gLogCategory_NetTransportChaCha20Poly1305,0x3c),
          iVar5 != 0)))) {
        _LogPrintF(&_gLogCategory_NetTransportChaCha20Poly1305,
                   "OSStatus _NetTransportRead(void *, size_t, size_t *, void *)",0x3c,
                   "### NTCP bad size: %zu / %H\n");
      }
      iVar5 = -0x1a57;
    }
  }
  goto LAB_18be49b40;
code_r0x00018be49a08:
  if (iVar5 == 2) {
    uVar9 = *(ulong *)(param_4 + 6);
LAB_18be49a4c:
    iVar5 = _SocketReadData(*param_4,lVar2,uVar9,param_4 + 8);
    if (iVar5 != 0) goto LAB_18be49b40;
    *(undefined8 *)(param_4 + 8) = 0;
    param_4[4] = 3;
LAB_18be49a6c:
    iVar5 = _SocketReadData(*param_4,(long)param_4 + 0x402a,0x10,param_4 + 8);
    if (iVar5 != 0) goto LAB_18be49b40;
    _chacha20_poly1305_init_64x64(param_4 + 0x1014,param_4 + 0x1054,puVar3);
    _poly1305_update(param_4 + 0x1036,param_4 + 10,2);
    *(long *)(param_4 + 0x104e) = *(long *)(param_4 + 0x104e) + 2;
    lVar7 = _chacha20_poly1305_decrypt(param_4 + 0x1014,lVar2,*(undefined8 *)(param_4 + 6),lVar2);
    lVar8 = _chacha20_poly1305_verify
                      (param_4 + 0x1014,lVar2 + lVar7,(long)param_4 + 0x402a,&local_64);
    if (local_64 != 0) {
      iVar5 = local_64;
      if ((_gLogCategory_NetTransportChaCha20Poly1305 < 0x3d) &&
         ((_gLogCategory_NetTransportChaCha20Poly1305 != -1 ||
          (iVar6 = __LogCategory_Initialize(&_gLogCategory_NetTransportChaCha20Poly1305,0x3c),
          iVar6 != 0)))) {
        _LogPrintF(&_gLogCategory_NetTransportChaCha20Poly1305,
                   "OSStatus _NetTransportRead(void *, size_t, size_t *, void *)",0x3c,
                   "### NTCP verify failed: %#m\n");
      }
      goto LAB_18be49b40;
    }
    if (lVar8 + lVar7 != *(long *)(param_4 + 6)) {
      if ((_gLogCategory_NetTransportChaCha20Poly1305 < 0x3d) &&
         ((_gLogCategory_NetTransportChaCha20Poly1305 != -1 ||
          (iVar5 = __LogCategory_Initialize(&_gLogCategory_NetTransportChaCha20Poly1305,0x3c),
          iVar5 != 0)))) {
        _LogPrintF(&_gLogCategory_NetTransportChaCha20Poly1305,
                   "OSStatus _NetTransportRead(void *, size_t, size_t *, void *)",0x3c,
                   "### NTCP verify len failed: %zu vs %zu\n");
      }
      iVar5 = -0x1a6a;
LAB_18be49b40:
      if (param_3 != (long *)0x0) {
        *param_3 = lVar10 - param_1;
      }
      iVar6 = 0;
      if (iVar5 != -0x1a61 && iVar5 != 0x23 || lVar10 == param_1) {
        iVar6 = iVar5;
      }
      return iVar6;
    }
    uVar9 = 0;
    do {
      uVar1 = *(byte *)((long)puVar3 + uVar9) + 1;
      *(char *)((long)puVar3 + uVar9) = (char)uVar1;
      if (uVar1 >> 8 == 0) break;
      bVar4 = uVar9 < 7;
      uVar9 = uVar9 + 1;
    } while (bVar4);
    *(long *)(param_4 + 0x1010) = lVar2;
    *(long *)(param_4 + 0x1012) = lVar2 + lVar8 + lVar7;
    *(undefined8 *)(param_4 + 8) = 0;
    param_4[4] = 1;
    lVar7 = lVar2;
  }
  goto LAB_18be499b8;
}


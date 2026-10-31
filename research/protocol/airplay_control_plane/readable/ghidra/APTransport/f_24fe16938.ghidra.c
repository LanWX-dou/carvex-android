/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fe16938
 * original code SHA256: 53b155a021b5c4886b7e8664316ad69f8c26e50031e33cffdb704ee943dbd9f0
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_httpconnection_connect
          (undefined8 param_1,char *param_2,uint param_3,undefined4 param_4,int param_5)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  undefined8 uVar5;
  long lVar6;
  undefined8 uVar7;
  uint uVar8;
  double dVar9;
  undefined1 auVar10 [16];
  undefined8 local_150;
  undefined8 uStack_148;
  undefined8 local_140;
  char *local_138;
  undefined4 local_130;
  uint uStack_12c;
  long local_128;
  undefined8 local_120;
  code *local_118;
  long lStack_110;
  code *local_108;
  long lStack_100;
  undefined8 local_f8;
  undefined *puStack_f0;
  undefined8 local_e8;
  undefined8 uStack_e0;
  undefined8 *local_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined8 uStack_b0;
  ulong local_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined1 local_90;
  long local_88;
  
  local_88 = *_DAT_2681b4ee0;
  pcVar4 = (char *)func_0x0002500e5a60();
  local_90 = 0;
  local_98 = 0;
  func_0x000250090fc0(&local_138,0xa0);
  if (param_3 == 0) {
    param_3 = *(uint *)(pcVar4 + 0xc4);
  }
  if (*pcVar4 != '\0') {
    uVar5 = 0;
    goto LAB_24fe16bf0;
  }
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    func_0x0002500ee220(0,"httpconnection_connect",0x60a,0);
    auVar10 = _OUTLINED_FUNCTION_37();
    uVar5 = func_0x0002500ee620(auVar10._0_8_,auVar10._8_8_,"httpconnection_connect");
    if ((int)uVar5 == 0) goto LAB_24fe16bf0;
  }
  else {
    local_140 = *(undefined8 *)(pcVar4 + 0x1c8);
    uStack_148 = *(undefined8 *)(pcVar4 + 0x1c0);
    local_150 = *(undefined8 *)(pcVar4 + 0x1b8);
    dVar9 = (double)func_0x0002500b81f0(&local_150);
    uVar1 = *(uint *)(pcVar4 + 0x30);
    bVar2 = (uVar1 & 0x1b) != 0;
    uVar8 = 8;
    if (bVar2) {
      uVar8 = 9;
    }
    if ((uVar1 & 4) == 0 && param_3 == 0) {
      uVar8 = (uint)bVar2;
    }
    if ((uVar1 >> 5 & 1) != 0) {
      if (_gLogCategory_APTransportConnectionHTTP < 0x1f) {
        if (_gLogCategory_APTransportConnectionHTTP == -1) {
          uVar5 = _OUTLINED_FUNCTION_10();
          iVar3 = func_0x0002500a8720(uVar5,0x200001e);
          if (iVar3 == 0) goto LAB_24fe16a60;
        }
        _OUTLINED_FUNCTION_10();
        _OUTLINED_FUNCTION_34();
        _OUTLINED_FUNCTION_11();
      }
LAB_24fe16a60:
      uVar8 = uVar8 | 0x10;
    }
    if ((param_5 != 0) && (uVar8 = uVar8 | 0x8c, _gLogCategory_APTransportConnectionHTTP < 0x3d)) {
      if (_gLogCategory_APTransportConnectionHTTP == -1) {
        uVar5 = _OUTLINED_FUNCTION_10();
        iVar3 = func_0x0002500a8720(uVar5,0x200003c);
        if (iVar3 == 0) goto LAB_24fe16adc;
      }
      _OUTLINED_FUNCTION_10();
      auVar10 = _OUTLINED_FUNCTION_34();
      func_0x0002500ef250(auVar10._0_8_,auVar10._8_8_,0x200003c,
                          "[%{ptr}] Forcing iPv4 addressing mode");
    }
LAB_24fe16adc:
    if (pcVar4[0x154] != '\0') {
      uVar8 = uVar8 | 0x1000;
    }
    if (_gLogCategory_APTransportConnectionHTTP < 0x33) {
      if (_gLogCategory_APTransportConnectionHTTP == -1) {
        uVar5 = _OUTLINED_FUNCTION_10();
        iVar3 = func_0x0002500a8720(uVar5,0x2000032);
        if (iVar3 == 0) goto LAB_24fe16b40;
      }
      _OUTLINED_FUNCTION_10();
      auVar10 = _OUTLINED_FUNCTION_34();
      func_0x0002500ef250(auVar10._0_8_,auVar10._8_8_,0x2000032,
                          "[%{ptr}] Async connecting to \'%s\' port %d ifIndex: %u");
    }
LAB_24fe16b40:
    func_0x0002500ef390(&local_98,9,"[%{ptr}]");
    lVar6 = func_0x0002500903e0(*(undefined8 *)(pcVar4 + 0xd8));
    local_f8 = *(undefined8 *)(pcVar4 + 8);
    uStack_b0 = 0;
    uStack_b4 = 0;
    uStack_a0 = 0;
    local_e8 = 0;
    uStack_d0 = 0;
    uStack_c0 = 0;
    local_c8 = 0;
    uStack_e0 = 0xa0;
    local_a8 = (ulong)param_3;
    local_120 = 0xffffffffffffffff;
    local_118 = _httpconnection_asyncConnectionProgressed;
    local_108 = _httpconnection_asyncConnectionCompleted;
    puStack_f0 = &_gLogCategory_AsyncCnxAirPlayHTTP;
    uStack_bc = (undefined4)DAT_24fe44b50;
    uStack_b8 = (undefined4)((ulong)DAT_24fe44b50 >> 0x20);
    local_138 = param_2;
    local_130 = param_4;
    uStack_12c = uVar8 | 0x400;
    local_128 = (long)dVar9 * 1000000000;
    lStack_110 = lVar6;
    lStack_100 = lVar6;
    local_d8 = &local_98;
    uVar5 = func_0x0002500ee750(pcVar4 + 0xf0,&local_138);
    if ((int)uVar5 == 0) goto LAB_24fe16bf0;
    func_0x0002500ee220(uVar5,"httpconnection_connect",0x632,0);
    if (lVar6 != 0) {
      func_0x0002500903d0(lVar6);
    }
  }
  if (_gLogCategory_APTransportConnectionHTTP < 0x5b) {
    if (_gLogCategory_APTransportConnectionHTTP == -1) {
      uVar7 = _OUTLINED_FUNCTION_10();
      iVar3 = func_0x0002500a8720(uVar7,0x200005a);
      if (iVar3 == 0) goto LAB_24fe16cdc;
    }
    _OUTLINED_FUNCTION_10();
    auVar10 = _OUTLINED_FUNCTION_34();
    func_0x0002500ef250(auVar10._0_8_,auVar10._8_8_,0x200005a,
                        "[%{ptr}] Connecting failed with error %#m");
  }
LAB_24fe16cdc:
  if (*(long *)(pcVar4 + 0xf0) != 0) {
    func_0x0002500ee760();
    pcVar4[0xf0] = '\0';
    pcVar4[0xf1] = '\0';
    pcVar4[0xf2] = '\0';
    pcVar4[0xf3] = '\0';
    pcVar4[0xf4] = '\0';
    pcVar4[0xf5] = '\0';
    pcVar4[0xf6] = '\0';
    pcVar4[0xf7] = '\0';
  }
LAB_24fe16bf0:
  if (*_DAT_2681b4ee0 != local_88) {
    uVar5 = func_0x000250090ec0();
    return uVar5;
  }
  return uVar5;
}


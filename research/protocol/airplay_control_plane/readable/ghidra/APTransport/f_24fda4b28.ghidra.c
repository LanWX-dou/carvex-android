/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fda4b28
 * original code SHA256: c218b2d1afd50277f39056fe007b8fc11d8410631dfadf52fc7a82487b59171f
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x00024fda4e80) */
/* WARNING: Removing unreachable block (ram,0x00024fda4da0) */
/* WARNING: Removing unreachable block (ram,0x00024fda4e20) */
/* WARNING: Removing unreachable block (ram,0x00024fda4f04) */
/* WARNING: Removing unreachable block (ram,0x00024fda4bc8) */

void _httpconnection_httpResponseReceived(long param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  char *pcVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  code *extraout_x9;
  code *pcVar8;
  code *extraout_x9_00;
  long *plVar9;
  long extraout_x16;
  undefined8 *puVar10;
  long extraout_x16_00;
  long lVar11;
  long lVar12;
  undefined8 local_90;
  undefined8 local_88;
  long local_80;
  undefined8 local_78;
  undefined8 uStack_70;
  undefined8 local_68;
  
  lVar12 = *(long *)(param_1 + 0x25c8);
  lVar11 = *(long *)(param_1 + 0x25e0);
  local_88 = 0;
  local_80 = 0;
  local_90 = 0;
  lVar2 = func_0x000250091250();
  lVar3 = func_0x0002500eede0(lVar12);
  if (lVar3 == 0) goto LAB_24fda4f98;
  pcVar4 = (char *)func_0x0002500e5a60();
  if (*pcVar4 == '\0') {
    lVar5 = func_0x0002500b5820(lVar11);
    plVar9 = (long *)(*(long *)(lVar5 + 0x10) + 0x50);
    if ((*plVar9 == 0) || (_OUTLINED_FUNCTION_28(plVar9), extraout_x16 == 0)) {
      uVar6 = 0;
    }
    else {
      uVar6 = (*extraout_x9)(lVar11);
    }
    if (*(long *)(pcVar4 + 0x1e8) != 0) {
      lVar5 = func_0x0002500b8490(lVar2 - *(long *)(pcVar4 + 0x1e8));
      pcVar4[0x1e8] = '\0';
      pcVar4[0x1e9] = '\0';
      pcVar4[0x1ea] = '\0';
      pcVar4[0x1eb] = '\0';
      pcVar4[0x1ec] = '\0';
      pcVar4[0x1ed] = '\0';
      pcVar4[0x1ee] = '\0';
      pcVar4[0x1ef] = '\0';
      *(long *)(pcVar4 + 0x1d0) = *(long *)(pcVar4 + 0x1d0) + lVar5;
      iVar1 = func_0x0002500ef140(param_1,"X-Apple-ProcessingTime",0,0,&local_88,&local_90);
      if (iVar1 == 0) {
        func_0x0002500ef3a0(local_88,local_90,"%llu");
        *(undefined8 *)(pcVar4 + 0x1d8) = *(undefined8 *)(pcVar4 + 0x1d8);
        *(long *)(pcVar4 + 0x1e0) = lVar5 + *(long *)(pcVar4 + 0x1e0);
      }
    }
    if (*(int *)(param_1 + 0x2108) - 100U < 500) {
      if (_gLogCategory_APTransportConnectionHTTP < 0x1f) {
        if (_gLogCategory_APTransportConnectionHTTP == -1) {
          uVar7 = _OUTLINED_FUNCTION_10();
          iVar1 = func_0x0002500a8720(uVar7,0x200001e);
          if (iVar1 != 0) goto LAB_24fda4cb4;
        }
        else {
LAB_24fda4cb4:
          func_0x0002500eefa0(*(undefined8 *)(pcVar4 + 0x108));
          func_0x0002500ef250(&_gLogCategory_APTransportConnectionHTTP,
                              "void httpconnection_httpResponseReceived(HTTPMessageRef)",0x200001e,
                              "[%{ptr}] Received response for CID:0x%08X groupID %llu%?{end} duration %llums%?{end} receiver %llums"
                             );
        }
        if (_gLogCategory_APTransportConnectionHTTP < 0xb) {
          if (_gLogCategory_APTransportConnectionHTTP == -1) {
            uVar7 = _OUTLINED_FUNCTION_10();
            iVar1 = func_0x0002500a8720(uVar7,10);
            if (iVar1 == 0) goto LAB_24fda4d44;
          }
          uVar7 = _OUTLINED_FUNCTION_10();
          func_0x0002500ef240(uVar7,uVar7,param_1 + 0x18);
        }
      }
LAB_24fda4d44:
      *(long *)(pcVar4 + 0x1f0) = lVar2;
      _APTTrafficMetricsResponseReceived
                (*(undefined8 *)(pcVar4 + 0x200),
                 *(long *)(param_1 + 0x2150) + *(long *)(param_1 + 0x2018));
      lVar2 = func_0x0002500b5820(lVar11);
      puVar10 = (undefined8 *)(*(long *)(lVar2 + 0x10) + 0x60);
      pcVar8 = (code *)*puVar10;
      if (((pcVar8 != (code *)0x0) && (pcVar8 != (code *)0x0)) &&
         (iVar1 = (*pcVar8)((ulong)puVar10 & 0xffffffffffff | 0xcf23000000000000,lVar11),
         iVar1 == 0x73796e63)) {
        uVar7 = _OUTLINED_FUNCTION_11();
        uVar7 = _APTransportPackageHTTPCreateWithHTTPMessage(uVar7,param_1,&local_80);
        lVar2 = local_80;
        if ((int)uVar7 != 0) {
          func_0x0002500ee220(uVar7,"httpconnection_httpResponseReceived",0xa6f,0);
          goto LAB_24fda4f90;
        }
        lVar5 = func_0x0002500b5820(local_80);
        puVar10 = (undefined8 *)(*(long *)(lVar5 + 0x10) + 0x58);
        pcVar8 = (code *)*puVar10;
        if ((pcVar8 != (code *)0x0) && (pcVar8 != (code *)0x0)) {
          (*pcVar8)((ulong)puVar10 & 0xffffffffffff | 0xfc31000000000000,lVar2,0x72706c79);
        }
        lVar2 = local_80;
        lVar5 = func_0x0002500b5820(lVar11);
        plVar9 = (long *)(*(long *)(lVar5 + 0x10) + 0x50);
        if ((*plVar9 == 0) || (_OUTLINED_FUNCTION_28(plVar9), extraout_x16_00 == 0)) {
          uVar7 = 0;
        }
        else {
          uVar7 = (*extraout_x9_00)(lVar11);
        }
        lVar5 = func_0x0002500b5820(lVar2);
        puVar10 = (undefined8 *)(*(long *)(lVar5 + 0x10) + 0x48);
        pcVar8 = (code *)*puVar10;
        if ((pcVar8 != (code *)0x0) && (pcVar8 != (code *)0x0)) {
          (*pcVar8)((ulong)puVar10 & 0xffffffffffff | 0x75df000000000000,lVar2,uVar7);
        }
        _httpconnection_callEventCallbacks(lVar3,7,local_80,0,0,uVar6);
      }
      lVar2 = func_0x0002500e5a60(lVar3);
      func_0x0002500b5840();
      func_0x0002500b5850(&local_78);
      *(undefined8 *)(lVar2 + 0x180) = uStack_70;
      *(undefined8 *)(lVar2 + 0x178) = local_78;
      *(undefined8 *)(lVar2 + 0x188) = local_68;
      iVar1 = *(int *)(lVar2 + 0x174) + -1;
      *(int *)(lVar2 + 0x174) = iVar1;
      if ((iVar1 == 0) && (lVar5 = *(long *)(lVar2 + 0x1a8), lVar5 != 0)) {
        func_0x0002500910c0(lVar5);
        func_0x000250091090(lVar5);
        *(undefined8 *)(lVar2 + 0x1a8) = 0;
      }
    }
    else {
      _httpconnection_callEventCallbacks(lVar3,8,lVar11,0,0,uVar6);
    }
  }
LAB_24fda4f90:
  func_0x0002500903d0(lVar3);
LAB_24fda4f98:
  if (lVar12 != 0) {
    func_0x0002500903d0(lVar12);
  }
  if (lVar11 != 0) {
    func_0x0002500903d0(lVar11);
  }
  if (local_80 != 0) {
    func_0x0002500903d0();
  }
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2518a50b4
 * original code SHA256: 54c1053516d86a4de1777f02474a34f3cd135a7be734cc0baf2e20e4a9e2edeb
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x0002518a53a8) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
_airplayReqProcessor_requestProcessFPSetup(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  undefined4 uVar8;
  code *pcVar9;
  undefined8 *puVar10;
  undefined8 uVar11;
  undefined4 local_90;
  undefined8 local_8c;
  undefined2 local_84;
  undefined8 local_82;
  undefined2 local_7a;
  uint local_78;
  long local_70;
  char local_65;
  undefined4 local_64;
  long local_60;
  uint local_54;
  
  local_54 = 0;
  lVar3 = func_0x00025810ac50();
  local_60 = 0;
  local_64 = 0;
  local_65 = '\0';
  local_70 = 0;
  iVar2 = func_0x00025810b820();
  if (iVar2 == 0) {
    lVar4 = 0;
  }
  else {
    func_0x000258109330();
    lVar4 = func_0x0002580f5640();
    uVar5 = func_0x000258109330();
    if ((lVar4 - 1U < 0xfffffffffffffffe) && (iVar2 = func_0x0002580f5630(), iVar2 != 0)) {
      uVar11 = *(undefined8 *)(lVar3 + 0x80);
      uVar1 = *(undefined8 *)(lVar3 + 0x88);
      lVar6 = func_0x00025810ac50(param_1);
      local_90 = (undefined4)DAT_251913250;
      local_84 = 0x800;
      local_7a = 0x400;
      local_78 = (uint)(*(int *)(lVar6 + 0x28) == 1);
      local_8c = uVar11;
      local_82 = uVar1;
      func_0x0002580f5490(&MACH_HEADER,uVar5,1,lVar4,"Receiver Authenticate",
                          "SenderDeviceID: %llu ReceiverDeviceID: %llu isRC: %d",&local_90,0x1c);
    }
  }
  if ((_gLogCategory_APReceiverRequestProcessorAirPlay < 0x33) &&
     ((_gLogCategory_APReceiverRequestProcessorAirPlay != -1 ||
      (iVar2 = func_0x000258101e40(&_gLogCategory_APReceiverRequestProcessorAirPlay,0x2000032),
      iVar2 != 0)))) {
    func_0x000258101eb0(&_gLogCategory_APReceiverRequestProcessorAirPlay,
                        "APSTransportMessageProcessingStatus airplayReqProcessor_requestProcessFPSetup(APReceiverRequestProcessorRef, CFDictionaryRef, CFDictionaryRef *)"
                        ,0x2000032,"[%{ptr}] F %d\n");
  }
  *(int *)(lVar3 + 300) = *(int *)(lVar3 + 300) + 1;
  uVar7 = _airplayReqProcessor_isAllowedToConnectBasedOnACL(param_1);
  if ((uVar7 & 1) == 0) {
    func_0x000258109a30(0,"airplayReqProcessor_requestProcessFPSetup",0xa3b,0);
    lVar6 = 0;
LAB_2518a56c8:
    uVar8 = 0xfffee706;
  }
  else {
    local_60 = 0;
    if (*(long *)(lVar3 + 8) != 0) {
      uVar5 = func_0x0002581026d0(*_DAT_2680d3150,0,&cfstringStruct_276117ff0);
      uVar11 = *(undefined8 *)(lVar3 + 8);
      lVar6 = func_0x000258109150(uVar11);
      puVar10 = (undefined8 *)(*(long *)(lVar6 + 0x10) + 0x18);
      pcVar9 = (code *)*puVar10;
      if ((pcVar9 != (code *)0x0) && (pcVar9 != (code *)0x0)) {
        (*pcVar9)((ulong)puVar10 & 0xffffffffffff | 0x98f3000000000000,uVar11,0x1e,uVar5);
      }
      func_0x0002580f5830(uVar5);
    }
    iVar2 = func_0x00025810a700(param_2,&cfstringStruct_276118010,0,0xffffffff,&local_54);
    if (local_54 == 0) {
      if (iVar2 == 8) {
        lVar6 = 0;
        goto LAB_2518a5434;
      }
      if (iVar2 != 0x20) {
        if ((_gLogCategory_APReceiverRequestProcessorAirPlay < 0x3d) &&
           ((_gLogCategory_APReceiverRequestProcessorAirPlay != -1 ||
            (iVar2 = func_0x000258101e40(&_gLogCategory_APReceiverRequestProcessorAirPlay,0x200003c)
            , iVar2 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APReceiverRequestProcessorAirPlay,
                              "APSTransportMessageProcessingStatus airplayReqProcessor_requestProcessFPSetup(APReceiverRequestProcessorRef, CFDictionaryRef, CFDictionaryRef *)"
                              ,0x200003c,"### [%{ptr}] Bad ET: %d\n");
        }
        lVar6 = 0;
        uVar8 = 0xfffee704;
        goto LAB_2518a55f4;
      }
LAB_2518a5424:
      lVar6 = 0;
      uVar8 = 3;
    }
    else {
      lVar6 = func_0x00025810a680(param_2,&cfstringStruct_276118030,0);
      if (lVar6 == 0) goto LAB_2518a5424;
LAB_2518a5434:
      uVar8 = 2;
    }
    *(undefined4 *)(lVar3 + 0x100) = uVar8;
    if (*(char *)(lVar3 + 0x128) == '\0') {
      if (*(long *)(lVar3 + 0x120) == 0) goto LAB_2518a5460;
LAB_2518a54a0:
      uVar5 = func_0x00025810a6b0(param_2,*_DAT_2681041b8,0,0,&local_70,&local_54);
      if (local_70 == 0) {
        func_0x000258109a30(0,"airplayReqProcessor_requestProcessFPSetup",0xa7d,0);
        goto LAB_2518a56c8;
      }
      uVar7 = _Mib5yocT(*(undefined4 *)(lVar3 + 0x100),lVar3 + 0x104,*(undefined8 *)(lVar3 + 0x120),
                        uVar5,local_70,&local_60,&local_64,&local_65);
      local_54 = (uint)uVar7;
      if (local_54 != 0) {
        if (*(long *)(lVar3 + 0x120) != 0) {
          _IPaI1oem5iL(*(long *)(lVar3 + 0x120));
          *(undefined8 *)(lVar3 + 0x120) = 0;
          uVar7 = (ulong)local_54;
          if (local_54 == 0) goto LAB_2518a5510;
        }
        func_0x000258109a30(uVar7,"airplayReqProcessor_requestProcessFPSetup",0xa82,0);
        uVar8 = 0xfffee703;
        goto LAB_2518a55f4;
      }
LAB_2518a5510:
      uVar8 = 0xfffee702;
      if (local_65 == -1) {
        uVar8 = 0xfffee703;
        goto LAB_2518a55f4;
      }
      if (local_65 != '\x01') {
        if (local_65 != '\0') goto LAB_2518a55f4;
        *(undefined1 *)(lVar3 + 0x128) = 1;
      }
      uVar5 = _airplayReqProcessor_createBinaryDataResponse
                        ("application/octet-stream",local_60,local_64,param_3);
      local_54 = (uint)uVar5;
      if (local_54 == 0) {
        uVar8 = 0;
        goto LAB_2518a55f4;
      }
      uVar11 = 0xa96;
    }
    else {
      if (*(long *)(lVar3 + 0x120) != 0) {
        _IPaI1oem5iL();
        *(undefined8 *)(lVar3 + 0x120) = 0;
        *(undefined1 *)(lVar3 + 0x128) = 0;
      }
LAB_2518a5460:
      *(undefined8 *)(lVar3 + 0x10c) = 0;
      puVar10 = (undefined8 *)(lVar3 + 0x104);
      *puVar10 = 0;
      *(undefined8 *)(lVar3 + 0x114) = 0;
      uVar5 = func_0x000258109260(puVar10,0,0);
      local_54 = (uint)uVar5;
      if (local_54 == 0) {
        uVar5 = _cp2g1b9ro(lVar3 + 0x120,puVar10);
        local_54 = (uint)uVar5;
        if (local_54 == 0) goto LAB_2518a54a0;
        uVar11 = 0xa78;
      }
      else {
        uVar11 = 0xa75;
      }
    }
    uVar8 = 0xfffee702;
    func_0x000258109a30(uVar5,"airplayReqProcessor_requestProcessFPSetup",uVar11,0);
  }
LAB_2518a55f4:
  iVar2 = func_0x00025810b820();
  if (((iVar2 != 0) && (uVar5 = func_0x000258109330(), lVar4 - 1U < 0xfffffffffffffffe)) &&
     (iVar2 = func_0x0002580f5630(), iVar2 != 0)) {
    local_90 = (undefined4)DAT_251913210;
    local_8c = CONCAT44(local_8c._4_4_,uVar8);
    func_0x0002580f5490(&MACH_HEADER,uVar5,2,lVar4,"Receiver Authenticate","Error: %d",&local_90,8);
  }
  if (local_60 != 0) {
    _jEHf8Xzsv8K();
  }
  if (lVar6 != 0) {
    func_0x0002580f4d30(lVar6);
  }
  return uVar8;
}


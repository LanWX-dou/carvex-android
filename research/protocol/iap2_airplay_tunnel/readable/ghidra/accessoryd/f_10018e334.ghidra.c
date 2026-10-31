/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10018e334
 * original code SHA256: 3bd2166e50b6476000c5033b2f8f62df4ac9cb08b45b881d7aeba1f864286eb7
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x25 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x25 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_retain_x21 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x8 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */

undefined8 _acc_endpoint2_processIncomingData(long param_1,long param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  char cVar5;
  char cVar6;
  bool bVar7;
  undefined1 uVar8;
  int iVar9;
  int iVar10;
  long lVar11;
  ulong uVar12;
  ulong uVar13;
  ulong uVar14;
  undefined8 uVar15;
  long extraout_x8;
  long extraout_x8_00;
  undefined8 extraout_x9;
  long *unaff_x19;
  undefined8 uVar16;
  ulong uVar17;
  undefined *puVar18;
  long lVar19;
  long lVar20;
  undefined4 local_90;
  int iStack_8c;
  undefined2 uStack_88;
  undefined2 uStack_86;
  undefined2 uStack_84;
  undefined2 uStack_82;
  undefined2 uStack_80;
  undefined2 uStack_7e;
  undefined2 uStack_7c;
  undefined2 local_7a;
  undefined4 local_78;
  undefined2 local_74;
  undefined2 local_72;
  undefined2 uStack_70;
  undefined2 uStack_6e;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  
  if (param_1 == 0) {
    uVar16 = 0;
  }
  else {
    uVar16 = 0;
    if ((param_2 != 0) && (_OUTLINED_FUNCTION_82(), extraout_x8 != 0)) {
      lVar11 = _CFDataGetLength(param_2);
      iVar9 = _acc_userDefaultsLogging_boolForKey(_kCFACCUserDefaultsLoggingKey_TransportSignpost);
      if (iVar9 != 0) {
        uVar12 = _CFHash(unaff_x19[2]);
        uVar13 = _CFHash(param_2);
        iVar9 = _gNumLogSignpostObjects;
        lVar19 = _gLogSignpostObjects;
        uVar17 = uVar13 ^ uVar12;
        if (((_gLogSignpostObjects == 0) || (uVar14 = uVar13, _gNumLogSignpostObjects < 3)) &&
           (uVar14 = _OUTLINED_FUNCTION_53(), (int)uVar14 != 0)) {
          _OUTLINED_FUNCTION_0(DAT_1001b3100);
          uStack_86 = (undefined2)lVar19;
          uStack_84 = (undefined2)((ulong)lVar19 >> 0x10);
          uStack_82 = (undefined2)((ulong)lVar19 >> 0x20);
          uStack_80 = (undefined2)((ulong)lVar19 >> 0x30);
          _OUTLINED_FUNCTION_26();
          uStack_7c = (undefined2)iVar9;
          local_7a = (undefined2)((uint)iVar9 >> 0x10);
          _OUTLINED_FUNCTION_2();
          uVar14 = _OUTLINED_FUNCTION_84();
        }
        bVar7 = uVar12 == uVar13;
        in_OV = !bVar7 && SCARRY8(uVar17,1);
        in_ZR = bVar7 || uVar17 == 0xffffffffffffffff;
        in_NG = !bVar7 && (long)(uVar17 + 1) < 0;
        if ((!bVar7 && uVar17 != 0xffffffffffffffff) &&
           (iVar9 = _os_signpost_enabled(uVar14), iVar9 != 0)) {
          lVar19 = unaff_x19[2];
          uVar16 = _CFDataGetLength(param_2);
          local_90 = (undefined4)DAT_1001b30f0;
          iStack_8c = (int)lVar19;
          uStack_88 = (undefined2)((ulong)lVar19 >> 0x20);
          uStack_86 = (undefined2)((ulong)lVar19 >> 0x30);
          uStack_84 = 0x800;
          uStack_82 = (undefined2)uVar16;
          uStack_80 = (undefined2)((ulong)uVar16 >> 0x10);
          uStack_7e = (undefined2)((ulong)uVar16 >> 0x20);
          uStack_7c = (undefined2)((ulong)uVar16 >> 0x30);
          uVar16 = _OUTLINED_FUNCTION_6();
          __os_signpost_emit_with_name_impl
                    (uVar16,uVar14,0,uVar17,"Endpoint RECV","Received incoming data! %@, %lu bytes",
                     &local_90,0x16);
        }
      }
      iVar9 = _acc_endpoint2_isTransportRestricted();
      uVar3 = uStack_84;
      uVar1 = uStack_86;
      uStack_86 = (undefined2)lVar11;
      uVar2 = uStack_86;
      uStack_84 = (undefined2)((ulong)lVar11 >> 0x10);
      uVar4 = uStack_84;
      uStack_86 = uVar1;
      uStack_84 = uVar3;
      if (iVar9 == 0) {
        uVar12 = _acc_platform_packetLogging_isLogPacketDataAsMsg();
        if (((uVar12 & 1) == 0) && (iVar9 = _platform_systemInfo_isInternalBuild(), iVar9 == 0)) {
          if ((_gLogObjects == 0) || (uVar16 = _OUTLINED_FUNCTION_28(), in_NG != in_OV)) {
            _OUTLINED_FUNCTION_49();
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_1();
              _dispatch_once();
            }
            uVar16 = _OUTLINED_FUNCTION_19();
          }
          iVar9 = _os_log_type_enabled(uVar16,2);
          if (iVar9 != 0) {
            lVar20 = unaff_x19[2];
            lVar19 = unaff_x19[3];
            _CFDataGetBytePtr(param_2);
            uVar15 = _OUTLINED_FUNCTION_35(DAT_1001b3b48);
            uStack_84 = 0x840;
            uStack_82 = (undefined2)lVar20;
            uStack_80 = (undefined2)((ulong)lVar20 >> 0x10);
            uStack_7e = (undefined2)((ulong)lVar20 >> 0x20);
            uStack_7c = (undefined2)((ulong)lVar20 >> 0x30);
            local_7a = 0x400;
            local_74 = 0x410;
            uStack_6e = 0x830;
            uStack_6c = (undefined4)uVar15;
            uStack_68 = (undefined4)((ulong)uVar15 >> 0x20);
            local_78 = (int)lVar19;
            local_72 = uVar2;
            uStack_70 = uVar4;
            uVar15 = _OUTLINED_FUNCTION_6();
            __os_log_debug_impl(uVar15,uVar16,2,
                                "Received %ld bytes of incoming data for endpoint %@ (type:%{coreacc:ACCEndpoint_TransportType_t}d):\n%{coreacc:bytes}.*P"
                                ,&local_90,0x2c);
          }
        }
        else {
          if ((_gLogObjects == 0) || (uVar16 = _OUTLINED_FUNCTION_28(), in_NG != in_OV)) {
            _OUTLINED_FUNCTION_49();
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_1();
              _dispatch_once();
            }
            uVar16 = _OUTLINED_FUNCTION_19();
          }
          iVar9 = _os_log_type_enabled(uVar16,1);
          if (iVar9 != 0) {
            lVar20 = unaff_x19[2];
            lVar19 = unaff_x19[3];
            _CFDataGetBytePtr(param_2);
            uVar15 = _OUTLINED_FUNCTION_35(DAT_1001b3b48);
            uStack_84 = 0x840;
            uStack_82 = (undefined2)lVar20;
            uStack_80 = (undefined2)((ulong)lVar20 >> 0x10);
            uStack_7e = (undefined2)((ulong)lVar20 >> 0x20);
            uStack_7c = (undefined2)((ulong)lVar20 >> 0x30);
            local_7a = 0x400;
            local_74 = 0x410;
            uStack_6e = 0x830;
            uStack_6c = (undefined4)uVar15;
            uStack_68 = (undefined4)((ulong)uVar15 >> 0x20);
            local_78 = (int)lVar19;
            local_72 = uVar2;
            uStack_70 = uVar4;
            uVar15 = _OUTLINED_FUNCTION_6();
            __os_log_impl(uVar15,uVar16,1,
                          "Received %ld bytes of incoming data for endpoint %@ (type:%{coreacc:ACCEndpoint_TransportType_t}d):\n%{coreacc:bytes}.*P"
                          ,&local_90,0x2c);
          }
        }
        cVar5 = SBORROW8(lVar11,1);
        cVar6 = lVar11 + -1 < 0;
        uVar8 = lVar11 == 1;
        if (0 < lVar11) {
          if (*(int *)((long)unaff_x19 + 0x1c) != 0) {
            _OUTLINED_FUNCTION_6(0);
            uVar16 = _acc_protocolRouter_routeIncomingData();
            return uVar16;
          }
          iVar9 = _acc_protocolParser_detectProtocol(unaff_x19 + 6,param_2);
          if (iVar9 != 0) {
            if ((_gLogObjects == 0) || (uVar16 = _OUTLINED_FUNCTION_28(), cVar6 != cVar5)) {
              _OUTLINED_FUNCTION_49();
              if (!(bool)uVar8) {
                _OUTLINED_FUNCTION_1();
                _dispatch_once();
              }
              uVar16 = _OUTLINED_FUNCTION_19();
            }
            iVar10 = _OUTLINED_FUNCTION_72(uVar16);
            if (iVar10 != 0) {
              lVar11 = unaff_x19[2];
              local_90 = (undefined4)DAT_1001b3138;
              uStack_88 = 0x840;
              uStack_86 = (undefined2)lVar11;
              uStack_84 = (undefined2)((ulong)lVar11 >> 0x10);
              uStack_82 = (undefined2)((ulong)lVar11 >> 0x20);
              uStack_80 = (undefined2)((ulong)lVar11 >> 0x30);
              iStack_8c = iVar9;
              _OUTLINED_FUNCTION_6();
              _OUTLINED_FUNCTION_10();
              __os_log_impl();
            }
            iVar10 = *(int *)((long)unaff_x19 + 0x1c);
            *(int *)((long)unaff_x19 + 0x1c) = iVar9;
            cVar5 = SBORROW4(iVar10,iVar9);
            cVar6 = iVar10 - iVar9 < 0;
            uVar8 = iVar10 == iVar9;
            if (!(bool)uVar8) {
              if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_28(0), cVar6 != cVar5)) {
                _OUTLINED_FUNCTION_49();
                puVar18 = PTR___os_log_default_10022bbb0;
                if (!(bool)uVar8) {
                  _OUTLINED_FUNCTION_1();
                  _dispatch_once();
                  puVar18 = PTR___os_log_default_10022bbb0;
                }
              }
              else {
                puVar18 = *(undefined **)(extraout_x8_00 + 0x88);
              }
              iVar10 = _os_log_type_enabled(puVar18,0);
              if (iVar10 != 0) {
                lVar11 = unaff_x19[2];
                local_90 = (undefined4)DAT_1001b3138;
                uStack_88 = 0x840;
                uStack_86 = (undefined2)lVar11;
                uStack_84 = (undefined2)((ulong)lVar11 >> 0x10);
                uStack_82 = (undefined2)((ulong)lVar11 >> 0x20);
                uStack_80 = (undefined2)((ulong)lVar11 >> 0x30);
                iStack_8c = iVar9;
                _OUTLINED_FUNCTION_6();
                _OUTLINED_FUNCTION_10();
                __os_log_impl();
              }
              if (*unaff_x19 != 0) {
                _acc_connection2_mapAccessoryInfo_internal();
              }
              lVar11 = _acc_endpoint2_createSnapshotInfo();
              if (lVar11 != 0) {
                uVar16 = _OUTLINED_FUNCTION_9();
                uStack_88 = (undefined2)DAT_1001b3078;
                uStack_86 = (undefined2)((ulong)DAT_1001b3078 >> 0x10);
                uStack_84 = (undefined2)((ulong)DAT_1001b3078 >> 0x20);
                uStack_82 = (undefined2)((ulong)DAT_1001b3078 >> 0x30);
                uStack_80 = 0x5e58;
                uStack_7e = 0xf;
                uStack_7c = 1;
                local_7a = 0;
                local_78 = 0x2181c0;
                local_74 = 1;
                local_72 = 0;
                uStack_70 = (undefined2)uVar16;
                uStack_6e = (undefined2)((ulong)uVar16 >> 0x10);
                uStack_6c = (undefined4)((ulong)uVar16 >> 0x20);
                _acc_manager2_performPlatformWorkAsync(&local_90);
              }
              _OUTLINED_FUNCTION_32(0);
              if (((bool)uVar8) && (*unaff_x19 != 0)) {
                uVar16 = _acc_endpoint2_createSnapshotInfo();
                uStack_68 = *(undefined4 *)((long)unaff_x19 + 0x1c);
                local_90 = SUB84(PTR___NSConcreteStackBlock_10022bb78,0);
                iStack_8c = (int)((ulong)PTR___NSConcreteStackBlock_10022bb78 >> 0x20);
                uStack_88 = (undefined2)DAT_1001b3078;
                uStack_86 = (undefined2)((ulong)DAT_1001b3078 >> 0x10);
                uStack_84 = (undefined2)((ulong)DAT_1001b3078 >> 0x20);
                uStack_82 = (undefined2)((ulong)DAT_1001b3078 >> 0x30);
                uStack_80 = 0x5e60;
                uStack_7e = 0xf;
                uStack_7c = 1;
                local_7a = 0;
                local_78 = 0x220cb0;
                local_74 = 1;
                local_72 = 0;
                uStack_70 = (undefined2)uVar16;
                uStack_6e = (undefined2)((ulong)uVar16 >> 0x10);
                uStack_6c = (undefined4)((ulong)uVar16 >> 0x20);
                _acc_manager2_performPlatformWorkForConnectionEndpointAsync
                          (unaff_x19[1],unaff_x19[2],&local_90);
              }
            }
            _acc_protocolRouter_initProtocolLayer();
            _OUTLINED_FUNCTION_6();
            uVar16 = _acc_protocolRouter_routeIncomingData();
            _acc_protocolParser_destroy(unaff_x19 + 6);
            return uVar16;
          }
        }
      }
      else {
        uVar16 = _logObjectForModule(0x11);
        iVar9 = _OUTLINED_FUNCTION_59(uVar16);
        if (iVar9 != 0) {
          _OUTLINED_FUNCTION_80((int)unaff_x19[3],DAT_1001b3150);
          uStack_82 = (undefined2)((ulong)lVar11 >> 0x20);
          uStack_80 = (undefined2)((ulong)lVar11 >> 0x30);
          uStack_7e = 0x840;
          uStack_7c = (undefined2)extraout_x9;
          local_7a = (undefined2)((ulong)extraout_x9 >> 0x10);
          local_78 = (undefined4)((ulong)extraout_x9 >> 0x20);
          uStack_86 = uVar2;
          uStack_84 = uVar4;
          _OUTLINED_FUNCTION_6();
          _OUTLINED_FUNCTION_4();
          __os_log_impl();
        }
      }
      uVar16 = 1;
    }
  }
  return uVar16;
}


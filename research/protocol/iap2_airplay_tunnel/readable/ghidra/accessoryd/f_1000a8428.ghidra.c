/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000a8428
 * original code SHA256: fa899a965614d6ba85fd002438b572ebd0eb7fac513d663004651a6f7a765bdf
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void __mfi4Auth_endpoint_initSession(long *param_1,undefined8 param_2)

{
  uint uVar1;
  bool bVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  dispatch_queue_t pdVar13;
  undefined8 uVar14;
  ulong uVar15;
  undefined *puVar16;
  long lVar17;
  undefined *local_200;
  undefined8 local_1f8;
  code *local_1f0;
  undefined *puStack_1e8;
  long *local_1e0;
  undefined *local_1d8;
  undefined8 local_1d0;
  code *local_1c8;
  undefined *puStack_1c0;
  long *local_1b8;
  undefined *local_1b0;
  undefined8 local_1a8;
  code *local_1a0;
  undefined *puStack_198;
  long *local_190;
  undefined *local_188;
  undefined8 local_180;
  code *local_178;
  undefined *puStack_170;
  long *local_168;
  undefined *local_160;
  undefined8 local_158;
  code *local_150;
  undefined *puStack_148;
  long *local_140;
  undefined *local_138;
  undefined8 local_130;
  code *local_128;
  undefined *puStack_120;
  long *local_118;
  undefined *local_110;
  undefined8 local_108;
  code *local_100;
  undefined *puStack_f8;
  long *local_f0;
  undefined *local_e8;
  undefined8 local_e0;
  code *local_d8;
  undefined *puStack_d0;
  long *local_c8;
  undefined4 local_c0;
  char *local_bc;
  undefined2 local_b4;
  uint local_b2;
  undefined2 uStack_ae;
  ushort uStack_ac;
  undefined2 uStack_aa;
  undefined2 local_a8;
  undefined2 uStack_a6;
  undefined2 local_a4;
  ushort local_a2;
  ushort uStack_a0;
  undefined2 local_9e;
  undefined2 local_9c;
  undefined2 uStack_9a;
  undefined2 uStack_98;
  undefined2 local_96;
  undefined4 local_94;
  undefined1 local_85;
  uint local_84 [5];
  
  lVar10 = _malloc_type_calloc(1,0x358,0x10f0040268e578f);
  param_1[1] = lVar10;
  lVar17 = *param_1;
  local_84[0] = local_84[0] & 0xffffff00;
  uVar11 = _MFAADeviceIdentityCertsExist();
  if (lVar17 == 0) {
    uVar15 = 0;
  }
  else {
    lVar12 = _acc_endpoint2_copyProperty
                       (lVar17,*(undefined8 *)
                                PTR__kCFACCProperties_Endpoint_MFi4Auth_OneWayOnly_10022b918);
    uVar15 = uVar11;
    if (lVar12 != 0) {
      _CFNumberGetValue(lVar12,1,local_84);
      uVar15 = (ulong)((uint)((char)local_84[0] == '\0') & (uint)uVar11);
    }
  }
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
    puVar16 = PTR___os_log_default_10022bbb0;
    if (DAT_10023eb40 != -1) {
      __mfi4Auth_endpoint_initSession_cold_2();
      puVar16 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
  }
  iVar7 = _os_log_type_enabled(puVar16,1);
  uVar6 = uStack_a6;
  uVar5 = local_a8;
  local_a8 = (undefined2)uVar15;
  uVar3 = local_a8;
  uStack_a6 = (undefined2)(uVar15 >> 0x10);
  uVar4 = uStack_a6;
  if (iVar7 != 0) {
    if (lVar17 == 0) {
      uVar14 = 0;
    }
    else {
      uVar14 = *(undefined8 *)(lVar17 + 0x10);
    }
    local_c0 = (undefined4)DAT_1001b3110;
    local_bc = "_mfi4Auth_endpoint_isEndpointSupportsMutualAuth";
    local_b4 = 0x840;
    local_b2 = (uint)uVar14;
    uStack_ae = (undefined2)((ulong)uVar14 >> 0x20);
    uStack_ac = (ushort)((ulong)uVar14 >> 0x30);
    uStack_aa = 0x400;
    local_a4 = 0x400;
    local_a2 = (ushort)local_84[0] & 0xff;
    uStack_a0 = 0;
    local_9e = 0x400;
    local_9c = (undefined2)uVar11;
    uStack_9a = (undefined2)(uVar11 >> 0x10);
    __os_log_impl(0x100000000,puVar16,1,
                  "%s: endpointUUID %@, EndpointSupportsMutualAuth %d, (bOneWayOnly %d, deviceIdentityCertsExist %d)"
                  ,&local_c0,0x28);
    uVar5 = local_a8;
    uVar6 = uStack_a6;
  }
  uStack_a6 = uVar6;
  local_a8 = uVar5;
  if ((uVar11 & 1) == 0) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
      puVar16 = PTR___os_log_default_10022bbb0;
      if (DAT_10023eb40 != -1) {
        __mfi4Auth_endpoint_initSession_cold_2();
        puVar16 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
    }
    iVar7 = _os_log_type_enabled(puVar16,0);
    if (iVar7 != 0) {
      local_c0 = (undefined4)DAT_1001b3098;
      local_bc = "_mfi4Auth_endpoint_isEndpointSupportsMutualAuth";
      local_b4 = 0x400;
      local_b2 = 0;
      __os_log_impl(0x100000000,puVar16,0,
                    "%s: deviceIdentityCertsExist %d, trigger re-init for next time.",&local_c0,0x12
                   );
    }
    pdVar13 = _dispatch_get_global_queue(0,0);
    _dispatch_async(pdVar13,&___block_literal_global_49);
  }
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
    puVar16 = PTR___os_log_default_10022bbb0;
    if (DAT_10023eb40 != -1) {
      __mfi4Auth_endpoint_initSession_cold_2();
      puVar16 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
  }
  iVar7 = _os_log_type_enabled(puVar16,2);
  if (iVar7 != 0) {
    __mfi4Auth_endpoint_initSession_cold_4(param_2,uVar15,puVar16);
  }
  local_84[0] = 0;
  local_85 = 0;
  uVar11 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_MFi4ECDSADisallow);
  uVar8 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_MFi4SigmaIRequired);
  uVar9 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_MFi4ECDSAOnly);
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
    puVar16 = PTR___os_log_default_10022bbb0;
    if (DAT_10023eb40 != -1) {
      __mfi4Auth_endpoint_initSession_cold_2();
      puVar16 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
  }
  uVar1 = (uVar9 ^ 1) & (uVar8 | (uint)uVar15);
  iVar7 = _os_log_type_enabled(puVar16,1);
  if (iVar7 != 0) {
    uStack_ac = (ushort)uVar11 ^ 1;
    uStack_a0 = (ushort)uVar8 & 1;
    local_c0 = (undefined4)DAT_1001b3128;
    local_bc = "_mfi4Auth_endpoint_initSession";
    local_b4 = 0x400;
    uStack_ae = 0x400;
    uStack_aa = (undefined2)(uVar11 >> 0x10);
    local_a8 = 0x400;
    local_a2 = 0x400;
    local_9e = 0;
    local_9c = 0x400;
    uStack_9a = (undefined2)uVar9;
    uStack_98 = (undefined2)(uVar9 >> 0x10);
    local_96 = 0x400;
    local_b2 = uVar1;
    uStack_a6 = uVar3;
    local_a4 = uVar4;
    local_94 = (int)uVar11;
    __os_log_impl(0x100000000,puVar16,1,
                  "%s: allowSigmaI %d, allowOneWay %d, (endpointSupportsMutualAuth %d, mfi4SigmaIRequired %d, mfi4ECDSAOnly %d, mfi4ECDSADisallow %d)"
                  ,&local_c0,0x30);
  }
  bVar2 = uVar1 != 0;
  if (bVar2) {
    local_84[0] = CONCAT31(local_84[0]._1_3_,2);
  }
  uVar15 = (ulong)bVar2;
  if ((uVar11 & 1) == 0) {
    *(undefined1 *)((ulong)local_84 | uVar15) = 0;
    uVar15 = (ulong)(bVar2 + 1);
  }
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
    puVar16 = PTR___os_log_default_10022bbb0;
    if (DAT_10023eb40 != -1) {
      __mfi4Auth_endpoint_initSession_cold_2();
      puVar16 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
  }
  iVar7 = _os_log_type_enabled(puVar16,0);
  if (iVar7 != 0) {
    uVar8 = local_84[0] >> 8 & 0xff;
    if ((uint)uVar15 < 2) {
      uVar8 = 0xffffffff;
    }
    local_c0 = (undefined4)DAT_1001b3128;
    local_bc = "_mfi4Auth_endpoint_initSession";
    local_b4 = 0x400;
    local_b2 = local_84[0] & 0xff;
    uStack_ae = 0x400;
    uStack_ac = (ushort)uVar8;
    uStack_aa = (undefined2)(uVar8 >> 0x10);
    local_a8 = 0x400;
    uStack_a6 = 0xffff;
    local_a4 = 0xffff;
    local_a2 = 0x400;
    uStack_a0 = 0;
    local_9e = 0;
    local_9c = 0x400;
    uStack_9a = 0xffff;
    uStack_98 = 0xffff;
    local_96 = 0x400;
    local_94 = 0xffffffff;
    __os_log_impl(0x100000000,puVar16,0,
                  "%s: supportedAuthTypes [%d %d %d], supportedCapabilities [%d %d %d]",&local_c0,
                  0x30);
  }
  *(undefined4 *)(lVar10 + 0x24) = 1;
  uVar14 = _CFRetain(param_2);
  uVar11 = _mfi4Auth_protocol_initSessionCommon(lVar10,uVar14,0x400,local_84,uVar15,&local_85,1);
  uVar14 = DAT_1001b3118;
  if ((uVar11 & 1) == 0) {
    __mfi4Auth_endpoint_initSession_cold_7();
  }
  else {
    local_e8 = PTR___NSConcreteStackBlock_10022bb78;
    local_e0 = DAT_1001b3118;
    local_d8 = ____mfi4Auth_endpoint_initSession_block_invoke;
    puStack_d0 = &___block_descriptor_tmp_34;
    local_c8 = param_1;
    _mfi4Auth_protocol_setOutgoingDataHandler(lVar10,&local_e8);
    local_110 = PTR___NSConcreteStackBlock_10022bb78;
    local_108 = uVar14;
    local_100 = ____mfi4Auth_endpoint_initSession_block_invoke_2;
    puStack_f8 = &___block_descriptor_tmp_36;
    local_f0 = param_1;
    _mfi4Auth_protocol_setSessionCloseHandler(lVar10,&local_110);
    local_138 = PTR___NSConcreteStackBlock_10022bb78;
    local_130 = uVar14;
    local_128 = ____mfi4Auth_endpoint_initSession_block_invoke_3;
    puStack_120 = &___block_descriptor_tmp_38;
    local_118 = param_1;
    _mfi4Auth_protocol_setAuthStateHandler(lVar10,&local_138);
    local_160 = PTR___NSConcreteStackBlock_10022bb78;
    local_158 = uVar14;
    local_150 = ____mfi4Auth_endpoint_initSession_block_invoke_4;
    puStack_148 = &___block_descriptor_tmp_39;
    local_140 = param_1;
    _mfi4Auth_protocol_setPairingHandler(lVar10,&local_160);
    local_188 = PTR___NSConcreteStackBlock_10022bb78;
    local_180 = uVar14;
    local_178 = ____mfi4Auth_endpoint_initSession_block_invoke_5;
    puStack_170 = &___block_descriptor_tmp_41;
    local_168 = param_1;
    _mfi4Auth_protocol_setNvmReadHandler(lVar10,&local_188);
    local_1b0 = PTR___NSConcreteStackBlock_10022bb78;
    local_1a8 = uVar14;
    local_1a0 = ____mfi4Auth_endpoint_initSession_block_invoke_6;
    puStack_198 = &___block_descriptor_tmp_42;
    local_190 = param_1;
    _mfi4Auth_protocol_setAccessoryInfoOverridesHandler(lVar10,&local_1b0);
    local_1d8 = PTR___NSConcreteStackBlock_10022bb78;
    local_1d0 = uVar14;
    local_1c8 = ____mfi4Auth_endpoint_initSession_block_invoke_7;
    puStack_1c0 = &___block_descriptor_tmp_44;
    local_1b8 = param_1;
    _mfi4Auth_protocol_setStartRelayHandler(lVar10,&local_1d8);
    local_200 = PTR___NSConcreteStackBlock_10022bb78;
    local_1f8 = uVar14;
    local_1f0 = ____mfi4Auth_endpoint_initSession_block_invoke_8;
    puStack_1e8 = &___block_descriptor_tmp_46;
    local_1e0 = param_1;
    _mfi4Auth_protocol_setPacketLoggingHandler(lVar10,&local_200);
    lVar17 = _malloc_type_calloc(1,0xa0,0x107004053570430);
    *(long *)(lVar10 + 0x350) = lVar17;
    uVar14 = _CFDictionaryCreateMutable
                       (*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0,0x40,
                        PTR__kCFTypeDictionaryKeyCallBacks_10022bd40,
                        PTR__kCFTypeDictionaryValueCallBacks_10022bd48);
    *(undefined8 *)(lVar17 + 0x30) = uVar14;
    lVar10 = _CFAbsoluteTimeGetCurrent();
    param_1[4] = lVar10;
  }
  return;
}


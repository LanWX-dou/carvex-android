/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10019c124
 * original code SHA256: 916deec9e75a34d247c75aa2f939b01bb1264d860719fd27331c4afcc4e72a9e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

long _iAP2LinkSendDetectCB(long param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  undefined8 uVar5;
  undefined *puVar6;
  undefined8 *puVar7;
  ulong unaff_x30;
  undefined2 local_30 [8];
  
  if (((param_1 != 0) && (*(long *)(param_1 + 0xb0) != 0)) &&
     (puVar7 = *(undefined8 **)(*(long *)(param_1 + 0xb0) + 0x10), puVar7 != (undefined8 *)0x0)) {
    if (param_2 == 0) {
      uVar5 = puVar7[1];
      uVar3 = _acc_endpoint2_getTransportTypeString(*puVar7);
      _acc_platform_packetLogging_logEventForEndpoint(uVar5,uVar3,"DETECT","Send DETECT packet");
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
        lVar4 = _iap2_endpoint_sendOutgoingData
                          (puVar7,&_kIap2PacketDetectData,_kIap2PacketDetectDataLen);
        return lVar4;
      }
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10019c1cc);
      (*pcVar1)();
    }
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
      puVar6 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        param_1 = _OUTLINED_FUNCTION_0();
        puVar6 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar6 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar2 = _os_log_type_enabled(puVar6,param_1,0);
    if (iVar2 != 0) {
      local_30[0] = 0;
      uVar5 = _OUTLINED_FUNCTION_6();
      __os_log_impl(uVar5,param_1,0,
                    "-------------------------------------------------------\n  BadParameter or RequestIdentify response to DETECT:  \n    must be iAP1 only device!                          \n-------------------------------------------------------"
                    ,local_30,2);
    }
    param_1 = 0;
  }
  return param_1;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10017a344
 * original code SHA256: a44eff57406987954e73c8c48412d3819f79d6350113bf8de6333bc929a3a84f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _acc_protocolRouter_destroyProtocolLayer(long param_1)

{
  code *pcVar1;
  undefined8 uVar2;
  long extraout_x8;
  int extraout_w9;
  ulong unaff_x30;
  undefined *local_48;
  undefined8 local_40;
  code *local_38;
  undefined *puStack_30;
  undefined8 local_28;
  
  if (param_1 == 0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x1c) - 3U < 0x10) {
    switch(*(int *)(param_1 + 0x1c)) {
    default:
      local_28 = _CFRetain(*(undefined8 *)(param_1 + 0x10));
      local_48 = PTR___NSConcreteStackBlock_10022bb78;
      local_40 = DAT_1001b3118;
      local_38 = ___acc_protocolRouter_destroyProtocolLayer_block_invoke;
      puStack_30 = &___block_descriptor_tmp_1;
      _acc_manager2_performPlatformWorkAsync(&local_48);
      break;
    case 4:
      if (*(long *)(param_1 + 0x38) != 0) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          uVar2 = _iap2_endpoint_destroy((long *)(param_1 + 0x38));
          return uVar2;
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10017a5d8);
        (*pcVar1)();
      }
      break;
    case 5:
    case 6:
    case 7:
      if (*(long *)(param_1 + 0x38) != 0) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          uVar2 = _ea_endpoint_destroy((long *)(param_1 + 0x38));
          return uVar2;
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10017a3b8);
        (*pcVar1)();
      }
      break;
    case 8:
      if (*(long *)(param_1 + 0x38) != 0) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          uVar2 = _oobPairing_endpoint_destroy((long *)(param_1 + 0x38));
          return uVar2;
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10017a4c0);
        (*pcVar1)();
      }
      break;
    case 9:
    case 0xc:
      goto switchD_10017a38c_caseD_6;
    case 10:
      if (*(long *)(param_1 + 0x38) != 0) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          uVar2 = _accAuthProtocol_endpoint_destroy((long *)(param_1 + 0x38));
          return uVar2;
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10017a4ec);
        (*pcVar1)();
      }
      break;
    case 0xb:
      if (*(long *)(param_1 + 0x38) != 0) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          uVar2 = _configStream_endpoint_destroy((long *)(param_1 + 0x38));
          return uVar2;
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10017a43c);
        (*pcVar1)();
      }
      break;
    case 0xd:
      if (*(long *)(param_1 + 0x38) != 0) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          uVar2 = _audioProductCerts_endpoint_destroy((long *)(param_1 + 0x38));
          return uVar2;
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10017a494);
        (*pcVar1)();
      }
      break;
    case 0xe:
      if (*(long *)(param_1 + 0x38) != 0) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          uVar2 = _mfi4Auth_endpoint_destroy((long *)(param_1 + 0x38));
          return uVar2;
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10017a3e4);
        (*pcVar1)();
      }
      break;
    case 0xf:
      if (*(long *)(param_1 + 0x38) != 0) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          uVar2 = _accSNTPTimeSync_endpoint_destroy((long *)(param_1 + 0x38));
          return uVar2;
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10017a468);
        (*pcVar1)();
      }
      break;
    case 0x10:
      uVar2 = _platform_systemInfo_supportsQiAuth();
      if ((int)uVar2 == 0) {
        return uVar2;
      }
      if (*(long *)(param_1 + 0x38) != 0) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          uVar2 = _qiAuth_endpoint_destroy((long *)(param_1 + 0x38));
          return uVar2;
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10017a5ac);
        (*pcVar1)();
      }
      break;
    case 0x11:
      if (*(long *)(param_1 + 0x38) != 0) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          uVar2 = _t56_endpoint_destroy((long *)(param_1 + 0x38));
          return uVar2;
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10017a578);
        (*pcVar1)();
      }
      break;
    case 0x12:
      if (*(long *)(param_1 + 0x38) != 0) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
          uVar2 = _genericMFi_endpoint_destroy((long *)(param_1 + 0x38));
          return uVar2;
        }
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10017a410);
        (*pcVar1)();
      }
    }
    uVar2 = 1;
  }
  else {
switchD_10017a38c_caseD_6:
    _OUTLINED_FUNCTION_6();
    if (extraout_x8 == 0 || extraout_w9 < 0x14) {
      if (_logObjectForModule_onceToken != -1) {
        _OUTLINED_FUNCTION_1();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    uVar2 = _OUTLINED_FUNCTION_71();
    if ((int)uVar2 != 0) {
      _OUTLINED_FUNCTION_11(*(undefined4 *)(param_1 + 0x1c),DAT_1001b30b0);
      _OUTLINED_FUNCTION_5();
      uVar2 = 0;
    }
  }
  return uVar2;
}


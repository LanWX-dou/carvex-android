/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000500a8
 * original code SHA256: bd12ca1504cc0214ce58634ab61deb5d332a500c172a22b47c19dc1854048a81
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_iap2_identification_parseTransportComponent
          (undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined4 param_5,
          undefined8 param_6)

{
  undefined2 uVar1;
  undefined8 uVar2;
  undefined2 *puVar3;
  undefined8 uVar4;
  void *pvVar5;
  undefined8 uVar6;
  
  uVar2 = _iAP2MsgGetParamID(param_4);
  puVar3 = (undefined2 *)_malloc_type_calloc(1,0x50,0x107004078fb23ee);
  *(undefined4 *)(puVar3 + 10) = param_5;
  uVar4 = _iap2_messageParameterUtility_initWithMaxParamCount(7);
  *(undefined8 *)(puVar3 + 0x24) = uVar4;
  uVar4 = _iAP2MsgForEachParamDo(param_3,param_4,param_6,puVar3);
  if ((int)uVar4 == 0) {
    if (*(char *)((long)puVar3 + 0x37) == '\x01') {
      *(undefined1 *)(param_2 + 0x80) = 1;
      if (*(int *)(puVar3 + 10) - 1U < 2) {
        *(undefined1 *)(param_2 + 0x82) = 1;
      }
      else if (*(int *)(puVar3 + 10) == 4) {
        *(undefined1 *)(param_2 + 0x81) = 1;
      }
      if (*(char *)(puVar3 + 0x1c) == '\x01') {
        *(undefined1 *)(param_2 + 0x83) = 1;
        if (*(long *)(param_2 + 0x88) != 0) {
          _CFRelease();
          *(undefined8 *)(param_2 + 0x88) = 0;
        }
        uVar4 = 0;
        if (*(long *)(puVar3 + 0x20) != 0) {
          uVar4 = _CFRetain();
        }
        *(undefined8 *)(param_2 + 0x88) = uVar4;
      }
    }
    else if ((*(int *)(puVar3 + 10) == 2) && (*(char *)((long)puVar3 + 0x35) == '\x01')) {
      *(undefined1 *)(param_2 + 0x80) = 1;
      *(undefined1 *)(param_2 + 0x82) = 1;
    }
    uVar6 = _iap2_identification_addTransportComponent(param_1,param_2,puVar3);
    if ((int)uVar6 == 0) {
      return uVar6;
    }
    uVar1 = *puVar3;
    uVar4 = uVar6;
  }
  else {
    uVar1 = *puVar3;
    uVar6 = 10;
  }
  __addRejectGroup(param_2,uVar2,uVar1,uVar6);
  if ((*(undefined8 **)(puVar3 + 0x24) != (undefined8 *)0x0) &&
     (pvVar5 = (void *)**(undefined8 **)(puVar3 + 0x24), pvVar5 != (void *)0x0)) {
    _free(pvVar5);
  }
  if (*(long *)(puVar3 + 4) != 0) {
    _CFRelease();
    *(undefined8 *)(puVar3 + 4) = 0;
  }
  if (*(long *)(puVar3 + 0x20) != 0) {
    _CFRelease();
    *(undefined8 *)(puVar3 + 0x20) = 0;
  }
  if (*(void **)(puVar3 + 0x24) != (void *)0x0) {
    _free(*(void **)(puVar3 + 0x24));
  }
  _free(puVar3);
  return uVar4;
}


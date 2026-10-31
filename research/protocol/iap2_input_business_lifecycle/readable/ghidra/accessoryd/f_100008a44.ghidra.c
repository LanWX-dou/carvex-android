/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100008a44
 * original code SHA256: 3918f119b56471a43ac44a48ea3dd418ed4779f62c715fb17edb596af3ab73f9
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkSendPacketCB(long param_1,long param_2)

{
  undefined8 uVar1;
  undefined2 uVar2;
  code *pcVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
  ulong unaff_x30;
  
  if ((((param_1 != 0) && (param_2 != 0)) && (*(long *)(param_1 + 0xb0) != 0)) &&
     (puVar6 = *(undefined8 **)(*(long *)(param_1 + 0xb0) + 0x10), puVar6 != (undefined8 *)0x0)) {
    uVar4 = _iAP2PacketGenerateBuffer(param_2);
    uVar2 = *(undefined2 *)(param_2 + 0x36);
    uVar1 = puVar6[1];
    uVar5 = _acc_endpoint2_getTransportTypeString(*puVar6);
    _acc_platform_packetLogging_logiAP2PacketForEndpoint(uVar1,uVar5,param_2,0);
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
      pcVar3 = (code *)SoftwareBreakpoint(0xc471,0x100008ad0);
      (*pcVar3)();
    }
    _iap2_endpoint_sendOutgoingData(puVar6,uVar4,uVar2);
    return;
  }
  return;
}


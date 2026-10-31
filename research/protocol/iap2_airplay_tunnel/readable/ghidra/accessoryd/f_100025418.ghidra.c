/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100025418
 * original code SHA256: 5b7c1765305ffb8235d05aa92498edc8ca2ec210a06da4253f8ba4b8a260e003
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x3 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain_x19 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain_x22 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x8 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

void ACCTransportServer::receivedSecureTunnelDataHandler_forEndpointWithUUID_connectionUUID_
               (ID param_1,SEL param_2,void *param_3,ID param_4,ID param_5)

{
  undefined *local_70;
  undefined8 local_68;
  code *local_60;
  undefined *puStack_58;
  ID local_50;
  ID local_48;
  ID local_40;
  void *pvStack_38;
  
  local_70 = PTR___NSConcreteStackBlock_10022bb78;
  local_68 = DAT_1001b3078;
  local_60 = 
  ___89__ACCTransportServer_receivedSecureTunnelDataHandler_forEndpointWithUUID_connectionUUID___block_invoke
  ;
  puStack_58 = &DAT_1002183f8;
  local_50 = param_1;
  local_48 = param_1;
  local_40 = param_1;
  pvStack_38 = param_3;
  ACCXPCServerBase::_performServerOperationSync_(param_1,(ID)&local_70,(int)param_4);
  return;
}


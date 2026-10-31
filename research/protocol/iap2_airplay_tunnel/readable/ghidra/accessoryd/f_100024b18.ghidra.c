/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100024b18
 * original code SHA256: 20e8f3a8c44c915b424b78a8cd4dd2de36b73bef4655db509cfeccba4784e040
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x2 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain_x20 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain_x22 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x8 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x28 bytes */

bool ACCTransportServer::receivedSecureTunnelData_forEndpointWithUUID_connectionUUID_
               (ID param_1,SEL param_2,ID param_3,ID param_4,ID param_5)

{
  bool bVar1;
  undefined *local_98;
  undefined8 local_90;
  code *local_88;
  undefined *puStack_80;
  ID local_78;
  ID local_70;
  undefined8 *local_68;
  undefined8 local_60;
  undefined8 *local_58;
  undefined8 local_50;
  code *local_48;
  code *local_40;
  undefined8 local_38;
  
  local_68 = &local_60;
  local_60 = 0;
  local_50 = DAT_1001b3070;
  local_48 = ___Block_byref_object_copy_;
  local_40 = ___Block_byref_object_dispose_;
  local_38 = 0;
  local_98 = PTR___NSConcreteStackBlock_10022bb78;
  local_90 = DAT_1001b3078;
  local_88 = 
  ___82__ACCTransportServer_receivedSecureTunnelData_forEndpointWithUUID_connectionUUID___block_invoke
  ;
  puStack_80 = &DAT_100218250;
  local_78 = param_1;
  local_70 = param_1;
  local_58 = local_68;
  ACCXPCServerBase::_performServerOperationSync_(param_1,(ID)&local_98,(int)param_4);
  bVar1 = receivedSecureTunnelData_forEndpointWithUUID_connectionUUID_toClient_
                    (param_1,param_1,param_1,param_1,local_58[5]);
  __Block_object_dispose(&local_60,8);
  return bVar1;
}


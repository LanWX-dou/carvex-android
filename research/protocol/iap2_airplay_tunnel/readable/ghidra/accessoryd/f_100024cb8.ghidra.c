/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100024cb8
 * original code SHA256: 01b6e4e915ceb4ce37a1b2cae846e3a20ab8a72f94f52b15f29a0cc6c0d77f4a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x3 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain_x21 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* Function Stack Size: 0x30 bytes */

bool ACCTransportServer::receivedSecureTunnelData_forEndpointWithUUID_connectionUUID_toClient_
               (ID param_1,SEL param_2,ID param_3,ID param_4,ID param_5,ID param_6)

{
  ID IVar1;
  
  if ((param_4 != 0 && param_5 != 0) && param_6 != 0) {
    IVar1 = objc_stub::XPCConnection(param_6);
    IVar1 = objc_stub::remoteObjectProxyWithErrorHandler_(IVar1,&___block_literal_global_7);
    objc_stub::receivedSecureTunnelData_forEndpoint_(IVar1,param_1,param_1);
  }
  return (bool)((param_4 != 0 && param_5 != 0) && param_6 != 0);
}


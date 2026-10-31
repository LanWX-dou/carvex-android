/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000b2dbc
 * original code SHA256: c866e1f0621647ec94519166f62c1e8bcd47c1b4b6625619617b40ae19e616af
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x24 replaced with injection: _objc_release_fixup */

undefined8
_platform_hid_get_report_response
          (ID param_1,unsigned_short param_2,unsigned_char param_3,unsigned_char param_4,ID param_5)

{
  ID IVar1;
  
  IVar1 = ACCHIDServer::sharedServer((ID)PTR_ACCHIDServer_10022aed8);
  ACCHIDServer::getReportResponse_componentID_reportType_reportID_report_
            (IVar1,param_1,param_2,param_3,param_4,param_5);
  return 1;
}


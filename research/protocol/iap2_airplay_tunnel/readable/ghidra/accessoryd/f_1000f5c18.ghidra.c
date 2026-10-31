/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000f5c18
 * original code SHA256: b51cf7168bada1ddb8a3c877bf40d69ee8c2d809b29834c96456af22ec92fa14
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _acc_endpoint2_getTransportTypeStringWithTransportType(uint param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)(PTR__kACCEndpoint_TransportType_Strings_10022b438 + 0x98);
  if (param_1 < 0x12) {
    puVar1 = (undefined8 *)(PTR__kACCEndpoint_TransportType_Strings_10022b438 + (ulong)param_1 * 8);
  }
  return *puVar1;
}


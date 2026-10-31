/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10003f740
 * original code SHA256: 0a16676dc0237b2e5c82bfc02d0823a1fd8079187fa25be06439970b557ae8d3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



char * _t56_protocol_msgTypeString(int param_1)

{
  if (param_1 - 1U < 8) {
    return (&PTR_s_SESSION_100219fc8)[param_1 - 1U];
  }
  return "UNKNOWN";
}


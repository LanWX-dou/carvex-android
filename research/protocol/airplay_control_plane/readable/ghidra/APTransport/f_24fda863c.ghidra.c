/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fda863c
 * original code SHA256: c892b3dca4109387374d9fbeb2c07b7d15d64d353c01f37abe7c5c5a94b2b00d
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong _APTransportStreamIDGetStreamCategory(ulong param_1)

{
  return param_1 >> 0x20 & 3;
}


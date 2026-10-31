/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fdfad5c
 * original code SHA256: b1371571ad1feee34a1c9fb288f960a48f9485146bc44534c355288b8fb229bc
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong _APTransportStreamIDMake(long param_1,long param_2,uint param_3)

{
  return param_2 << 0x20 | param_1 << 0x30 | (ulong)param_3;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fdfad94
 * original code SHA256: 895deeb4d88b7ce2e944700f57c9493e2c01c95ddff429f9072eccf78c358405
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong _APTransportStreamIDMakeWithPort(long param_1)

{
  return param_1 << 0x30 | 0x200000000;
}


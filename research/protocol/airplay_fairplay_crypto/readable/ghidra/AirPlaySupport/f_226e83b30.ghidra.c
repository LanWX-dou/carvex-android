/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x226e83b30
 * original code SHA256: 58301116774d5ff02c99c5b1577ca4112852aae3144ebb536ad47ae1e794fc9c
 * source SHA256: d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _APSCryptorGetNull(void)

{
  if (_APSCryptorGetNull_sAPSCryptorNullOnce != -1) {
    func_0x000228143b00(&_APSCryptorGetNull_sAPSCryptorNullOnce,&_APSCryptorGetNull_sAPSCryptorNull,
                        _nullCryptor_create);
  }
  return _APSCryptorGetNull_sAPSCryptorNull;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x40a270
 * original code SHA256: 69fbc4b0326b31c689d453bd6f1271ec637394d54b3b2223623ae0eb8019b029
 * source SHA256: bb8a5b0d9fa57eafa8a9358341db3c9661d210ec778620e52e8d3b9fa4fd9f5e
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 KnobUpdate(void)

{
  undefined1 auStack_8 [8];
  
  HIDKnobFillReport(auStack_8,gSelectButtonPressed,gHomeButtonPressed,gBackButtonPressed,
                    (int)(DAT_0040edc8 + DAT_0040edc0 * (gXPosition + 1.0) * 0.5),
                    (int)(DAT_0040edc8 + DAT_0040edc0 * ((gYPosition + 1.0) / 0.0)),
                    gWheelPositionRelative);
  AirPlayReceiverSessionSendHIDReport(DAT_004256e8,DAT_004257e5,auStack_8,4);
  return 0;
}


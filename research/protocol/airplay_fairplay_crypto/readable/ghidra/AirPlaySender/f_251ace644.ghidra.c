/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251ace644
 * original code SHA256: b99c7dd12552317ed4ee02ed662f5d9ba3f81c4c7f192ed034178824a0cb84a8
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _fpAuthentication_Finalize(undefined8 param_1)

{
  int iVar1;
  long *plVar2;
  
  plVar2 = (long *)func_0x00025810ac50();
  if ((_gLogCategory_APAuthenticationClientFairPlay < 0x1f) &&
     ((_gLogCategory_APAuthenticationClientFairPlay != -1 ||
      (iVar1 = func_0x000258101e40(&_gLogCategory_APAuthenticationClientFairPlay,0x200001e),
      iVar1 != 0)))) {
    _fpAuthentication_Finalize_cold_1(param_1);
  }
  if (*plVar2 != 0) {
    _IPaI1oem5iL();
    *plVar2 = 0;
  }
  if (plVar2[1] != 0) {
    func_0x0002580f5830();
    plVar2[1] = 0;
  }
  return;
}


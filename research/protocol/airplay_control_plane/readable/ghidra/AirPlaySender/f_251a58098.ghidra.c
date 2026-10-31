/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a58098
 * original code SHA256: 697381aacf59b6b0afb33e26492af9a4f9b8be641e7278442b53401e7e93ea44
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251a58120) */

ulong _apsession_CreateTransportStream(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  char *pcVar1;
  long lVar2;
  ulong uVar3;
  code *pcVar4;
  undefined8 *puVar5;
  long local_40;
  uint local_34;
  
  pcVar1 = (char *)func_0x00025810ac50();
  if (*pcVar1 != '\0') {
    _apsession_CreateTransportStream_cold_1(&local_34);
    return (ulong)local_34;
  }
  _apsession_copyTransportSession(param_1,&local_40);
  if (local_40 == 0) {
    _apsession_CreateTransportStream_cold_2();
    return 0xfffee76b;
  }
  lVar2 = func_0x000258109150(local_40);
  puVar5 = (undefined8 *)(*(long *)(lVar2 + 0x10) + 0x18);
  pcVar4 = (code *)*puVar5;
  if ((pcVar4 == (code *)0x0) || (pcVar4 == (code *)0x0)) {
    uVar3 = 0xffffce12;
  }
  else {
    uVar3 = (*pcVar4)((ulong)puVar5 & 0xffffffffffff | 0x3564000000000000,local_40,param_2,param_3);
    if ((int)uVar3 == 0) goto LAB_251a58164;
  }
  func_0x000258109a30(uVar3,"apsession_CreateTransportStream",0x215a,0);
LAB_251a58164:
  func_0x0002580f5830(local_40);
  return uVar3;
}


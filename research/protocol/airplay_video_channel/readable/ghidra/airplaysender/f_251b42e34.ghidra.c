/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b42e34
 * original code SHA256: 64e55eacf54aa82b5ed572e898e9c462a4868faf016036590269a04a772f9c07
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _screenstream_cleanup(undefined8 param_1)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 local_48;
  undefined8 local_40;
  code *local_38;
  undefined *puStack_30;
  long local_28;
  
  lVar1 = func_0x00025810ac50();
  _screenstream_stopStatsTimer(param_1);
  uVar2 = func_0x00025810ad10();
  func_0x00025810ad30(uVar2,param_1,_screenstream_virtualDisplaySourceTerminated,0,0);
  if (*(long *)(lVar1 + 0xa0) != 0) {
    func_0x00025810f7f0();
    if (*(long *)(lVar1 + 0xa0) != 0) {
      func_0x0002580f5830();
      *(undefined8 *)(lVar1 + 0xa0) = 0;
    }
  }
  _screenstream_teardownTransportStream(param_1,1);
  if (*(long *)(lVar1 + 0x68) != 0) {
    if (*(long *)(lVar1 + 0x70) != 0) {
      func_0x00025810eb80();
      *(undefined8 *)(lVar1 + 0x70) = 0;
      if (*(long *)(lVar1 + 0x68) == 0) goto LAB_251b42ed0;
    }
    func_0x0002580f5830();
    *(undefined8 *)(lVar1 + 0x68) = 0;
  }
LAB_251b42ed0:
  if (*(long *)(lVar1 + 0xd0) != 0) {
    func_0x0002580f5830();
    *(undefined8 *)(lVar1 + 0xd0) = 0;
  }
  if (*(long *)(lVar1 + 0x130) != 0) {
    func_0x0002580f5830();
    *(undefined8 *)(lVar1 + 0x130) = 0;
  }
  if (*(long *)(lVar1 + 0x138) != 0) {
    func_0x0002580f5830();
    *(undefined8 *)(lVar1 + 0x138) = 0;
  }
  if (*(long *)(lVar1 + 0x140) != 0) {
    func_0x0002580f5830();
    *(undefined8 *)(lVar1 + 0x140) = 0;
  }
  if (*(long *)(lVar1 + 0x148) != 0) {
    func_0x0002580f5830();
    *(undefined8 *)(lVar1 + 0x148) = 0;
  }
  if (*(long *)(lVar1 + 0x128) != 0) {
    func_0x0002580f5830();
    *(undefined8 *)(lVar1 + 0x128) = 0;
  }
  if (*(long *)(lVar1 + 0x198) != 0) {
    func_0x0002580f5830();
    *(undefined8 *)(lVar1 + 0x198) = 0;
  }
  uVar3 = _DAT_2680d3700[1];
  uVar2 = *_DAT_2680d3700;
  *(undefined8 *)(lVar1 + 0xe0) = uVar3;
  *(undefined8 *)(lVar1 + 0xd8) = uVar2;
  *(undefined8 *)(lVar1 + 0x100) = uVar3;
  *(undefined8 *)(lVar1 + 0xf8) = uVar2;
  *(undefined8 *)(lVar1 + 0x110) = uVar3;
  *(undefined8 *)(lVar1 + 0x108) = uVar2;
  if (*(long *)(lVar1 + 0x78) != 0) {
    func_0x0002580f5830();
    *(undefined8 *)(lVar1 + 0x78) = 0;
  }
  if (*(long *)(lVar1 + 0x1f0) != 0) {
    local_48 = _DAT_2681b4ed0;
    local_40 = DAT_251c6aff8;
    local_38 = ___screenstream_cleanup_block_invoke;
    puStack_30 = &___block_descriptor_tmp_35;
    local_28 = lVar1;
    func_0x0002580f54f0(*(long *)(lVar1 + 0x1f0),&local_48);
  }
  return;
}


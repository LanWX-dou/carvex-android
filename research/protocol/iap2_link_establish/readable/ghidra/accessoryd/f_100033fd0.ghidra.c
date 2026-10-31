/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100033fd0
 * original code SHA256: 4c1e87d568d15ec191a8f0bc8a2b62fda6507bc9b3830831c44374d89e828e79
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x000100034314) */
/* WARNING: Removing unreachable block (ram,0x000100034354) */

void * _iAP2LinkCreate(int param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4,
                      int param_5,undefined8 param_6,undefined2 param_7,void *param_8)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  long lVar4;
  void *pvVar5;
  uint uVar6;
  byte bVar7;
  long lVar8;
  long lVar9;
  uint uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined1 auVar16 [16];
  
  if (param_8 == (void *)0x0) {
    auVar16 = _iAP2LinkCreate_cold_1();
    if ((auVar16._0_8_ != 0) && (lVar4 = _iAP2TimeGetContext(), lVar4 != 0)) {
      if ((*(byte *)(lVar4 + 0xd4) >> 4 & 1) == 0) {
        pvVar5 = (void *)_iAP2FSMHandleEvent(*(undefined8 *)(lVar4 + 8),param_3);
        return pvVar5;
      }
      pvVar5 = (void *)_iAP2LinkRunLoopTimeout
                                 (*(undefined8 *)(lVar4 + 0xb0),auVar16._8_8_,param_3,param_4);
      return pvVar5;
    }
    return (void *)0x0;
  }
  _bzero(param_8,0x268);
  *(void **)param_8 = param_8;
  if ((param_5 == 0) || (iVar1 = _iAP2LinkIsValidSynParam(param_4,param_3,0,0), iVar1 != 0)) {
    lVar4 = (long)param_8 + 0x268;
    uVar6 = (uint)param_6;
    if (param_1 == 0) {
      uVar10 = 0;
    }
    else {
      if (param_1 != 1) goto LAB_100034098;
      uVar10 = uVar6 + 2;
      uVar2 = _iAP2FSMCreate(8,0,0x1d,&_iAP2LinkDeviceStates,param_8,"DeviceFSM",0,0,lVar4);
      *(undefined8 *)((long)param_8 + 8) = uVar2;
      uVar3 = _iAP2FSMGetBuffSize();
      lVar4 = lVar4 + (uVar3 & 0xffffffff);
    }
    *(int *)((long)param_8 + 0xb8) = param_1;
    *(undefined8 *)((long)param_8 + 0xb0) = param_2;
    *(undefined2 *)((long)param_8 + 0xc0) = param_7;
    bVar7 = 0x40;
    if (param_5 == 0) {
      bVar7 = 0;
    }
    *(byte *)((long)param_8 + 0xd4) = *(byte *)((long)param_8 + 0xd4) & 0xbf | bVar7;
    *(undefined1 *)((long)param_8 + 0xc2) = 0xff;
    *(undefined1 *)((long)param_8 + 0xd5) = 1;
    *(char *)((long)param_8 + 0xd7) = (char)param_3;
    uVar2 = _iAP2TimeCreate(param_8,__iAP2LinkHandleTimerExpire,__iAP2LinkHandleTimerCancel,
                            uVar10 & 0xff,lVar4);
    *(undefined8 *)((long)param_8 + 200) = uVar2;
    uVar3 = _iAP2TimeGetBuffSize(uVar10 & 0xff);
    lVar4 = lVar4 + (uVar3 & 0xffffffff);
    _iAP2ListArrayInit(lVar4,param_6,8);
    *(long *)((long)param_8 + 0x120) = lVar4;
    uVar3 = _iAP2ListArrayGetBuffSize(param_6,8);
    lVar4 = lVar4 + (uVar3 & 0xffffffff);
    _iAP2ListArrayInit(lVar4,param_6,8);
    *(long *)((long)param_8 + 0x128) = lVar4;
    uVar3 = _iAP2ListArrayGetBuffSize(param_6,8);
    lVar8 = 0;
    lVar4 = lVar4 + (uVar3 & 0xffffffff);
    lVar9 = 5;
    do {
      _iAP2ListArrayInit(lVar4,0xff,8);
      *(long *)((long)param_8 + lVar8 * 8 + 0x130) = lVar4;
      uVar3 = _iAP2ListArrayGetBuffSize(0xff,8);
      lVar4 = lVar4 + (uVar3 & 0xffffffff);
      lVar8 = lVar8 + 1;
      lVar9 = lVar9 + -1;
    } while (lVar9 != 0);
    *(undefined8 **)((long)param_8 + 0x160) = param_4;
    uVar11 = param_4[1];
    uVar2 = *param_4;
    uVar13 = param_4[3];
    uVar12 = param_4[2];
    uVar15 = param_4[5];
    uVar14 = param_4[4];
    *(undefined2 *)((long)param_8 + 0x198) = *(undefined2 *)(param_4 + 6);
    *(undefined8 *)((long)param_8 + 0x180) = uVar13;
    *(undefined8 *)((long)param_8 + 0x178) = uVar12;
    *(undefined8 *)((long)param_8 + 400) = uVar15;
    *(undefined8 *)((long)param_8 + 0x188) = uVar14;
    *(undefined8 *)((long)param_8 + 0x170) = uVar11;
    *(undefined8 *)((long)param_8 + 0x168) = uVar2;
    *(undefined4 *)((long)param_8 + 0x19e) = 0x3e8ffff;
    *(undefined2 *)((long)param_8 + 0x1a2) = 10;
    *(int *)((long)param_8 + 0x19a) = (int)DAT_1001b3348;
    *(undefined4 *)((long)param_8 + 0x1a4) = 0xffff0100;
    uVar2 = _iAP2BuffPoolInit(2,param_8,0xffff,param_6,lVar4);
    *(undefined8 *)((long)param_8 + 0xf0) = uVar2;
    uVar3 = _iAP2BuffPoolGetBuffSize(2,0xffff,param_6);
    lVar4 = lVar4 + (uVar3 & 0xffffffff);
    if (uVar6 < 0x81) {
      uVar6 = 0x80;
    }
    uVar2 = _iAP2BuffPoolInit(1,param_8,*(undefined2 *)((long)param_8 + 0xc0),uVar6,lVar4);
    *(undefined8 *)((long)param_8 + 0xf8) = uVar2;
    uVar3 = _iAP2BuffPoolGetBuffSize(1,*(undefined2 *)((long)param_8 + 0xc0),uVar6);
    lVar4 = lVar4 + (uVar3 & 0xffffffff);
    uVar2 = _iAP2BuffPoolInit(0,param_8,0,0,lVar4);
    *(undefined8 *)((long)param_8 + 0x100) = uVar2;
    uVar3 = _iAP2BuffPoolGetBuffSize(0,0,0);
    uVar2 = _iAP2TimeSyncInit(lVar4 + (uVar3 & 0xffffffff));
    *(undefined8 *)((long)param_8 + 0x108) = uVar2;
    _iAP2TimeSyncGetBuffSize();
  }
  else {
LAB_100034098:
    param_8 = (void *)0x0;
  }
  return param_8;
}


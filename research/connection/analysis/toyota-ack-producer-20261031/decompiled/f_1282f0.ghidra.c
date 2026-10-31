/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1282f0
 * original code SHA256: babba6dca1e94e2b9194c95172b8e091023086dcb1a74182e28b6a97385b7c16
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodIap2::createLinkPacket(IAP2_CONTROL_BYTE, unsigned char, unsigned char, unsigned char,
   unsigned char const*, unsigned short, IAP2_LINK_PACKET_OUT*) */

uint __thiscall
CIpodIap2::createLinkPacket
          (undefined8 param_1,char param_2,char param_3,char param_4,char param_5,void *param_6,
          uint param_7,undefined2 *param_8)

{
  uint uVar1;
  undefined8 *puVar2;
  long lVar3;
  long lVar4;
  char cVar5;
  char cVar6;
  uint uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  short sVar10;
  
  uVar1 = param_7 & 0xffff;
  if ((param_7 & 0xffff) == 0) {
    cVar5 = '\t';
    cVar6 = '\0';
    uVar7 = 9;
  }
  else {
    uVar7 = uVar1 + 10 & 0xffff;
    cVar6 = (char)(uVar7 >> 8);
    cVar5 = (char)(uVar1 + 10);
  }
  *(char *)(param_8 + 2) = param_2;
  *(char *)((long)param_8 + 5) = param_3;
  *param_8 = 0x5aff;
  *(char *)(param_8 + 4) = -(param_2 + cVar5 + cVar6 + param_4 + param_3 + param_5 + 'Y');
  *(char *)(param_8 + 1) = cVar6;
  *(char *)((long)param_8 + 3) = cVar5;
  *(char *)(param_8 + 3) = param_4;
  *(char *)((long)param_8 + 7) = param_5;
  memcpy((void *)((long)param_8 + 9),param_6,(ulong)uVar1);
  if ((param_7 & 0xffff) == 0) {
    *(undefined1 *)((long)param_8 + (long)(int)uVar1 + 9) = 0;
    return uVar7;
  }
  if (uVar1 - 1 < 0xf) {
    param_7 = 0;
    cVar5 = '\0';
  }
  else {
    sVar10 = 0;
    cVar5 = '\0';
    lVar3 = 0;
    do {
      lVar4 = lVar3 * 0x10;
      lVar3 = lVar3 + 1;
      puVar2 = (undefined8 *)((long)param_6 + lVar4);
      uVar9 = puVar2[1];
      uVar8 = *puVar2;
      sVar10 = sVar10 + (ushort)(byte)((ulong)uVar8 >> 0x10) + ((ushort)uVar8 & 0xff) +
                        (ushort)(byte)((ulong)uVar8 >> 0x20) + (ushort)(byte)((ulong)uVar8 >> 0x30)
                        + ((ushort)uVar9 & 0xff) + (ushort)(byte)((ulong)uVar9 >> 0x10) +
                        (ushort)(byte)((ulong)uVar9 >> 0x20) + (ushort)(byte)((ulong)uVar9 >> 0x30);
      cVar5 = cVar5 + (char)((ulong)uVar8 >> 0x18) + (char)((ulong)uVar8 >> 8) +
                      (char)((ulong)uVar8 >> 0x28) + (char)((ulong)uVar8 >> 0x38) +
                      (char)((ulong)uVar9 >> 8) + (char)((ulong)uVar9 >> 0x18) +
                      (char)((ulong)uVar9 >> 0x28) + (char)((ulong)uVar9 >> 0x38);
    } while ((uint)lVar3 < uVar1 >> 4);
    cVar5 = (char)sVar10 + cVar5;
    param_7 = param_7 & 0xfff0;
    if (param_7 == uVar1) goto LAB_0012854c;
  }
  cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)param_7);
  if (param_7 + 1 < uVar1) {
    cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 1));
    if (param_7 + 2 < uVar1) {
      cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 2));
      if (param_7 + 3 < uVar1) {
        cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 3));
        if (param_7 + 4 < uVar1) {
          cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 4));
          if (param_7 + 5 < uVar1) {
            cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 5));
            if (param_7 + 6 < uVar1) {
              cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 6));
              if (param_7 + 7 < uVar1) {
                cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 7));
                if (param_7 + 8 < uVar1) {
                  cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 8));
                  if (param_7 + 9 < uVar1) {
                    cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 9));
                    if (param_7 + 10 < uVar1) {
                      cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 10));
                      if (param_7 + 0xb < uVar1) {
                        cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 0xb));
                        if (param_7 + 0xc < uVar1) {
                          cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 0xc));
                          if (param_7 + 0xd < uVar1) {
                            cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 0xd));
                            if (param_7 + 0xe < uVar1) {
                              cVar5 = cVar5 + *(char *)((long)param_6 + (long)(int)(param_7 + 0xe));
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_0012854c:
  *(char *)((long)param_8 + (long)(int)uVar1 + 9) = -cVar5;
  return uVar7;
}


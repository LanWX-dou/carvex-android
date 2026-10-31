/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be4c4c8
 * original code SHA256: 19ad4c7b7dbb051d17262b89abfd0014cc344f98c8c618dec6929eb985e8b3eb
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _HTTPHeader_Parse(char *param_1)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  char *pcVar6;
  undefined4 uVar7;
  ulong uVar8;
  long lVar9;
  char *pcVar10;
  int iVar11;
  char *pcVar12;
  undefined8 local_60;
  long local_58;
  
  uVar8 = *(ulong *)(param_1 + 0x2000);
  if (uVar8 >> 0xd != 0) {
    return 0xffffe5cf;
  }
  *(char **)(param_1 + 0x2018) = "";
  param_1[0x2020] = '\0';
  param_1[0x2021] = '\0';
  param_1[0x2022] = '\0';
  param_1[0x2023] = '\0';
  param_1[0x2024] = '\0';
  param_1[0x2025] = '\0';
  param_1[0x2026] = '\0';
  param_1[0x2027] = '\0';
  param_1[0x2028] = '\0';
  param_1[0x2029] = '\0';
  param_1[0x202a] = '\0';
  param_1[0x202b] = '\0';
  *(char **)(param_1 + 0x2030) = "";
  param_1[0x20d8] = '\0';
  param_1[0x20d9] = '\0';
  param_1[0x20da] = '\0';
  param_1[0x20db] = '\0';
  param_1[0x20dc] = '\0';
  param_1[0x20dd] = '\0';
  param_1[0x20de] = '\0';
  param_1[0x20df] = '\0';
  param_1[0x2040] = '\0';
  param_1[0x2041] = '\0';
  param_1[0x2042] = '\0';
  param_1[0x2043] = '\0';
  param_1[0x2044] = '\0';
  param_1[0x2045] = '\0';
  param_1[0x2046] = '\0';
  param_1[0x2047] = '\0';
  *(long *)(param_1 + 0x2038) = 0;
  param_1[0x2050] = '\0';
  param_1[0x2051] = '\0';
  param_1[0x2052] = '\0';
  param_1[0x2053] = '\0';
  param_1[0x2054] = '\0';
  param_1[0x2055] = '\0';
  param_1[0x2056] = '\0';
  param_1[0x2057] = '\0';
  param_1[0x2048] = '\0';
  param_1[0x2049] = '\0';
  param_1[0x204a] = '\0';
  param_1[0x204b] = '\0';
  param_1[0x204c] = '\0';
  param_1[0x204d] = '\0';
  param_1[0x204e] = '\0';
  param_1[0x204f] = '\0';
  param_1[0x2060] = '\0';
  param_1[0x2061] = '\0';
  param_1[0x2062] = '\0';
  param_1[0x2063] = '\0';
  param_1[0x2064] = '\0';
  param_1[0x2065] = '\0';
  param_1[0x2066] = '\0';
  param_1[0x2067] = '\0';
  param_1[0x2058] = '\0';
  param_1[0x2059] = '\0';
  param_1[0x205a] = '\0';
  param_1[0x205b] = '\0';
  param_1[0x205c] = '\0';
  param_1[0x205d] = '\0';
  param_1[0x205e] = '\0';
  param_1[0x205f] = '\0';
  param_1[0x2070] = '\0';
  param_1[0x2071] = '\0';
  param_1[0x2072] = '\0';
  param_1[0x2073] = '\0';
  param_1[0x2074] = '\0';
  param_1[0x2075] = '\0';
  param_1[0x2076] = '\0';
  param_1[0x2077] = '\0';
  param_1[0x2068] = '\0';
  param_1[0x2069] = '\0';
  param_1[0x206a] = '\0';
  param_1[0x206b] = '\0';
  param_1[0x206c] = '\0';
  param_1[0x206d] = '\0';
  param_1[0x206e] = '\0';
  param_1[0x206f] = '\0';
  param_1[0x2080] = '\0';
  param_1[0x2081] = '\0';
  param_1[0x2082] = '\0';
  param_1[0x2083] = '\0';
  param_1[0x2084] = '\0';
  param_1[0x2085] = '\0';
  param_1[0x2086] = '\0';
  param_1[0x2087] = '\0';
  param_1[0x2078] = '\0';
  param_1[0x2079] = '\0';
  param_1[0x207a] = '\0';
  param_1[0x207b] = '\0';
  param_1[0x207c] = '\0';
  param_1[0x207d] = '\0';
  param_1[0x207e] = '\0';
  param_1[0x207f] = '\0';
  param_1[0x2090] = '\0';
  param_1[0x2091] = '\0';
  param_1[0x2092] = '\0';
  param_1[0x2093] = '\0';
  param_1[0x2094] = '\0';
  param_1[0x2095] = '\0';
  param_1[0x2096] = '\0';
  param_1[0x2097] = '\0';
  param_1[0x2088] = '\0';
  param_1[0x2089] = '\0';
  param_1[0x208a] = '\0';
  param_1[0x208b] = '\0';
  param_1[0x208c] = '\0';
  param_1[0x208d] = '\0';
  param_1[0x208e] = '\0';
  param_1[0x208f] = '\0';
  param_1[0x20a0] = '\0';
  param_1[0x20a1] = '\0';
  param_1[0x20a2] = '\0';
  param_1[0x20a3] = '\0';
  param_1[0x20a4] = '\0';
  param_1[0x20a5] = '\0';
  param_1[0x20a6] = '\0';
  param_1[0x20a7] = '\0';
  param_1[0x2098] = '\0';
  param_1[0x2099] = '\0';
  param_1[0x209a] = '\0';
  param_1[0x209b] = '\0';
  param_1[0x209c] = '\0';
  param_1[0x209d] = '\0';
  param_1[0x209e] = '\0';
  param_1[0x209f] = '\0';
  param_1[0x20b0] = '\0';
  param_1[0x20b1] = '\0';
  param_1[0x20b2] = '\0';
  param_1[0x20b3] = '\0';
  param_1[0x20b4] = '\0';
  param_1[0x20b5] = '\0';
  param_1[0x20b6] = '\0';
  param_1[0x20b7] = '\0';
  param_1[0x20a8] = '\0';
  param_1[0x20a9] = '\0';
  param_1[0x20aa] = '\0';
  param_1[0x20ab] = '\0';
  param_1[0x20ac] = '\0';
  param_1[0x20ad] = '\0';
  param_1[0x20ae] = '\0';
  param_1[0x20af] = '\0';
  param_1[0x20c0] = '\0';
  param_1[0x20c1] = '\0';
  param_1[0x20c2] = '\0';
  param_1[0x20c3] = '\0';
  param_1[0x20c4] = '\0';
  param_1[0x20c5] = '\0';
  param_1[0x20c6] = '\0';
  param_1[0x20c7] = '\0';
  param_1[0x20b8] = '\0';
  param_1[0x20b9] = '\0';
  param_1[0x20ba] = '\0';
  param_1[0x20bb] = '\0';
  param_1[0x20bc] = '\0';
  param_1[0x20bd] = '\0';
  param_1[0x20be] = '\0';
  param_1[0x20bf] = '\0';
  param_1[0x20d0] = '\0';
  param_1[0x20d1] = '\0';
  param_1[0x20d2] = '\0';
  param_1[0x20d3] = '\0';
  param_1[0x20d4] = '\0';
  param_1[0x20d5] = '\0';
  param_1[0x20d6] = '\0';
  param_1[0x20d7] = '\0';
  param_1[0x20c8] = '\0';
  param_1[0x20c9] = '\0';
  param_1[0x20ca] = '\0';
  param_1[0x20cb] = '\0';
  param_1[0x20cc] = '\0';
  param_1[0x20cd] = '\0';
  param_1[0x20ce] = '\0';
  param_1[0x20cf] = '\0';
  *(char **)(param_1 + 0x20e0) = "";
  param_1[0x20e8] = '\0';
  param_1[0x20e9] = '\0';
  param_1[0x20ea] = '\0';
  param_1[0x20eb] = '\0';
  param_1[0x20ec] = '\0';
  param_1[0x20ed] = '\0';
  param_1[0x20ee] = '\0';
  param_1[0x20ef] = '\0';
  param_1[0x20f0] = -1;
  param_1[0x20f1] = -1;
  param_1[0x20f2] = -1;
  param_1[0x20f3] = -1;
  *(char **)(param_1 + 0x20f8) = "";
  param_1[0x2100] = '\0';
  param_1[0x2101] = '\0';
  param_1[0x2102] = '\0';
  param_1[0x2103] = '\0';
  param_1[0x2104] = '\0';
  param_1[0x2105] = '\0';
  param_1[0x2106] = '\0';
  param_1[0x2107] = '\0';
  param_1[0x2108] = '\0';
  param_1[0x2110] = '\0';
  param_1[0x2111] = '\0';
  param_1[0x2112] = '\0';
  param_1[0x2113] = '\0';
  param_1[0x2114] = '\0';
  param_1[0x2115] = '\0';
  param_1[0x2116] = '\0';
  param_1[0x2117] = '\0';
  param_1[0x2118] = '\0';
  if (uVar8 == 0) {
    return 0xffffe5aa;
  }
  if ((uVar8 == 4) && (*param_1 == '$')) {
    param_1[0x2108] = param_1[1];
    *(ulong *)(param_1 + 0x2110) =
         (ulong)((uint)(*(ushort *)(param_1 + 2) >> 8) | (*(ushort *)(param_1 + 2) & 0xff00ff) << 8)
    ;
    *(char **)(param_1 + 0x2018) = param_1;
    param_1[0x2020] = '\x01';
    param_1[0x2021] = '\0';
    param_1[0x2022] = '\0';
    param_1[0x2023] = '\0';
    param_1[0x2024] = '\0';
    param_1[0x2025] = '\0';
    param_1[0x2026] = '\0';
    param_1[0x2027] = '\0';
    return 0;
  }
  pcVar2 = param_1 + uVar8;
  local_60 = 0;
  local_58 = 0;
  pcVar6 = param_1;
  while (*pcVar6 != ' ') {
    if (*pcVar6 == '/') {
      *(char **)(param_1 + 0x20e0) = param_1;
      pcVar10 = pcVar6 + 1;
      pcVar12 = pcVar10;
      if (pcVar10 < pcVar2) goto LAB_18be4c5e8;
      goto LAB_18be4c60c;
    }
    pcVar6 = pcVar6 + 1;
    if (pcVar2 <= pcVar6) {
      return 0xffffe5aa;
    }
  }
  *(char **)(param_1 + 0x2018) = param_1;
  lVar9 = (long)pcVar6 - (long)param_1;
  *(long *)(param_1 + 0x2020) = lVar9;
  pcVar6 = pcVar6 + 1;
  local_58 = lVar9;
  iVar4 = _strnicmpx(param_1,lVar9,"GET");
  if (iVar4 == 0) {
    uVar7 = 1;
LAB_18be4c714:
    *(undefined4 *)(param_1 + 0x2028) = uVar7;
  }
  else {
    iVar4 = _strnicmpx(param_1,lVar9,"POST");
    if (iVar4 == 0) {
      uVar7 = 2;
      goto LAB_18be4c714;
    }
    iVar4 = _strnicmpx(param_1,lVar9,"PUT");
    if (iVar4 == 0) {
      uVar7 = 3;
      goto LAB_18be4c714;
    }
    iVar4 = _strnicmpx(param_1,lVar9,"DELETE");
    if (iVar4 == 0) {
      uVar7 = 4;
      goto LAB_18be4c714;
    }
  }
  *(char **)(param_1 + 0x2030) = pcVar6;
  pcVar10 = pcVar6;
  pcVar12 = pcVar6;
  if (pcVar6 < pcVar2) {
    do {
      if (*pcVar10 == ' ') {
        *(long *)(param_1 + 0x2038) = (long)pcVar10 - (long)pcVar6;
        pcVar12 = pcVar10 + 1;
        _URLParseComponents(pcVar6,pcVar6 + ((long)pcVar10 - (long)pcVar6),param_1 + 0x2040,0);
        *(char **)(param_1 + 0x20e0) = pcVar12;
        pcVar6 = pcVar12;
        pcVar10 = pcVar12;
        if (pcVar12 < pcVar2) goto LAB_18be4c7a4;
        goto LAB_18be4c7d0;
      }
      pcVar10 = pcVar10 + 1;
      pcVar12 = pcVar2;
    } while (pcVar10 != pcVar2);
  }
  *(long *)(param_1 + 0x2038) = (long)pcVar12 - (long)pcVar6;
  return 0xffffe5aa;
  while (pcVar6 = pcVar6 + 1, pcVar10 = pcVar2, pcVar6 != pcVar2) {
LAB_18be4c7a4:
    if (*pcVar6 == '\n' || *pcVar6 == '\r') {
      *(long *)(param_1 + 0x20e8) = (long)pcVar6 - (long)pcVar12;
      goto LAB_18be4c848;
    }
  }
LAB_18be4c7d0:
  lVar9 = (long)pcVar10 - (long)pcVar12;
  goto LAB_18be4c610;
LAB_18be4c6cc:
  pcVar12 = pcVar6;
  iVar11 = (int)((long)iVar4 * 10);
  if (((long)iVar4 * 10 - (long)iVar11 != 0) ||
     (iVar4 = iVar11 + (uint)(byte)(cVar3 - 0x30), SCARRY4(iVar11,(uint)(byte)(cVar3 - 0x30)))) {
    return 0xffffe5ca;
  }
  pcVar6 = pcVar12 + 1;
  if (pcVar6 == pcVar2) {
    *(int *)(param_1 + 0x20f0) = iVar4;
    *(char **)(param_1 + 0x20f8) = pcVar2;
    pcVar12 = pcVar2;
    pcVar10 = pcVar2;
    goto LAB_18be4c8e4;
  }
  cVar3 = *pcVar6;
  if (9 < (byte)(cVar3 - 0x30U)) {
LAB_18be4c7e8:
    *(int *)(param_1 + 0x20f0) = iVar4;
    pcVar10 = pcVar12 + 2;
    if (cVar3 != ' ') {
      pcVar10 = pcVar6;
    }
LAB_18be4c7fc:
    *(char **)(param_1 + 0x20f8) = pcVar10;
    pcVar12 = pcVar10;
    if (pcVar10 < pcVar2) {
      pcVar6 = pcVar10;
      do {
        if (*pcVar6 == '\n' || *pcVar6 == '\r') {
          *(long *)(param_1 + 0x2100) = (long)pcVar6 - (long)pcVar10;
LAB_18be4c848:
          if (pcVar2 <= pcVar6 + 1) {
            return 0xffffe5aa;
          }
          iVar4 = _HTTPGetHeaderField(param_1,*(undefined8 *)(param_1 + 0x2000),"Connection",0,0,
                                      &local_60,&local_58,0);
          if (iVar4 == 0) {
            pcVar6 = "close";
            uVar5 = local_60;
            lVar9 = local_58;
          }
          else {
            pcVar6 = "HTTP/1.0";
            uVar5 = *(undefined8 *)(param_1 + 0x20e0);
            lVar9 = *(long *)(param_1 + 0x20e8);
          }
          iVar4 = _strnicmpx(uVar5,lVar9,pcVar6);
          param_1[0x2118] = iVar4 != 0;
          _HTTPScanFHeaderValue(param_1,*(undefined8 *)(param_1 + 0x2000),"Content-Length","%llu");
          return 0;
        }
        pcVar6 = pcVar6 + 1;
        pcVar12 = param_1 + uVar8;
      } while (pcVar6 != param_1 + uVar8);
    }
LAB_18be4c8e4:
    *(long *)(param_1 + 0x2100) = (long)pcVar12 - (long)pcVar10;
    return 0xffffe5aa;
  }
  goto LAB_18be4c6cc;
  while (pcVar1 = pcVar12 + 1, pcVar6 = pcVar12, pcVar10 = pcVar2, pcVar12 = pcVar1,
        pcVar1 != pcVar2) {
LAB_18be4c5e8:
    if (pcVar6[1] == ' ') {
      *(long *)(param_1 + 0x20e8) = (long)pcVar12 - (long)param_1;
      pcVar6 = pcVar6 + 2;
      if (pcVar2 <= pcVar6) {
        param_1[0x20f0] = '\0';
        param_1[0x20f1] = '\0';
        param_1[0x20f2] = '\0';
        param_1[0x20f3] = '\0';
        pcVar10 = pcVar6;
        goto LAB_18be4c7fc;
      }
      cVar3 = *pcVar6;
      if ((byte)(cVar3 - 0x30U) < 10) {
        iVar4 = 0;
        goto LAB_18be4c6cc;
      }
      iVar4 = 0;
      goto LAB_18be4c7e8;
    }
  }
LAB_18be4c60c:
  lVar9 = (long)pcVar10 - (long)param_1;
LAB_18be4c610:
  *(long *)(param_1 + 0x20e8) = lVar9;
  return 0xffffe5aa;
}


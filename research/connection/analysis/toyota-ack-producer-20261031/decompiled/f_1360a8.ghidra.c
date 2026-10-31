/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1360a8
 * original code SHA256: b177fd810d71bb57b4228bc81691be042131843f98806554b2028bde022e6e4f
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodIap2::CIpodIap2() */

void __thiscall CIpodIap2::CIpodIap2(CIpodIap2 *this)

{
  int iVar1;
  
  CIpodProtocol::CIpodProtocol((CIpodProtocol *)this);
  *(undefined **)this = PTR_vtable_0016ff80 + 0x10;
  *(CIpodIap2 **)(this + 0x20) = this + 0x20;
  *(CIpodIap2 **)(this + 0x28) = this + 0x20;
  *(undefined8 *)(this + 0x30) = 0;
  *(CIpodIap2 **)(this + 0x38) = this + 0x38;
  *(CIpodIap2 **)(this + 0x40) = this + 0x38;
  *(CIpodIap2 **)(this + 0x568) = this + 0x578;
  *(CIpodIap2 **)(this + 0x58) = this + 0x68;
  *(undefined8 *)(this + 0x60) = 0;
  *(CIpodIap2 **)(this + 0x78) = this + 0x88;
  *(undefined8 *)(this + 0x80) = 0;
  *(CIpodIap2 **)(this + 0x98) = this + 0xa8;
  *(undefined8 *)(this + 0xa0) = 0;
  *(CIpodIap2 **)(this + 0x5d0) = this + 0x5e0;
  this[0x68] = (CIpodIap2)0x0;
  this[0x88] = (CIpodIap2)0x0;
  this[0xa8] = (CIpodIap2)0x0;
  this[0x578] = (CIpodIap2)0x0;
  this[0x5a8] = (CIpodIap2)0x0;
  this[0x590] = (CIpodIap2)0x0;
  *(undefined2 *)(this + 0x592) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x570) = 0;
  *(CIpodIap2 **)(this + 0x598) = this + 0x5a8;
  *(undefined8 *)(this + 0x5a0) = 0;
  *(undefined4 *)(this + 0x5b8) = 1;
  *(undefined8 *)(this + 0x5d8) = 0;
  *(CIpodIap2 **)(this + 0x5f0) = this + 0x600;
  *(CIpodIap2 **)(this + 0x610) = this + 0x620;
  *(CIpodIap2 **)(this + 0x650) = this + 0x660;
  *(CIpodIap2 **)(this + 0x630) = this + 0x640;
  *(CIpodIap2 **)(this + 0x6d0) = this + 0x6e0;
  *(CIpodIap2 **)(this + 0x6b0) = this + 0x6c0;
  *(CIpodIap2 **)(this + 0x728) = this + 0x738;
  *(CIpodIap2 **)(this + 0x6f8) = this + 0x708;
  *(CIpodIap2 **)(this + 0x750) = this + 0x760;
  *(undefined8 *)(this + 0x5c0) = 0;
  *(undefined8 *)(this + 0x5f8) = 0;
  *(undefined8 *)(this + 0x618) = 0;
  *(undefined8 *)(this + 0x638) = 0;
  *(undefined8 *)(this + 0x658) = 0;
  *(undefined8 *)(this + 0x6b8) = 0;
  *(undefined8 *)(this + 0x6d8) = 0;
  *(undefined8 *)(this + 0x700) = 0;
  *(undefined8 *)(this + 0x730) = 0;
  *(undefined8 *)(this + 0x758) = 0;
  this[0x5e0] = (CIpodIap2)0x0;
  this[0x600] = (CIpodIap2)0x0;
  this[0x620] = (CIpodIap2)0x0;
  this[0x640] = (CIpodIap2)0x0;
  this[0x660] = (CIpodIap2)0x0;
  this[0x6c0] = (CIpodIap2)0x0;
  this[0x6e0] = (CIpodIap2)0x0;
  this[0x708] = (CIpodIap2)0x0;
  this[0x738] = (CIpodIap2)0x0;
  this[0x760] = (CIpodIap2)0x0;
  *(undefined8 *)(this + 0x5c8) = 0;
  *(undefined8 *)(this + 0x670) = 0;
  this[0x678] = (CIpodIap2)0x0;
  this[0x679] = (CIpodIap2)0x0;
  this[0x67a] = (CIpodIap2)0x0;
  this[0x67b] = (CIpodIap2)0x0;
  *(undefined2 *)(this + 0x67c) = 0;
  *(undefined8 *)(this + 0x680) = 0;
  *(undefined4 *)(this + 0x688) = 0;
  *(undefined8 *)(this + 0x690) = 0;
  *(undefined8 *)(this + 0x698) = 0;
  *(undefined8 *)(this + 0x6a0) = 0;
  *(undefined8 *)(this + 0x6a8) = 0;
  this[0x6f0] = (CIpodIap2)0x0;
  *(undefined2 *)(this + 0x720) = 0;
  this[0x722] = (CIpodIap2)0x0;
  this[0x723] = (CIpodIap2)0x0;
  this[0x748] = (CIpodIap2)0x0;
  this[0x770] = (CIpodIap2)0x0;
  *(undefined8 *)(this + 0x718) = 0;
  *(CIpodIap2 **)(this + 0x778) = this + 0x788;
  *(CIpodIap2 **)(this + 0x798) = this + 0x7a8;
  this[0x788] = (CIpodIap2)0x0;
  this[0x7a8] = (CIpodIap2)0x0;
  this[2000] = (CIpodIap2)0x0;
  *(undefined8 *)(this + 0x780) = 0;
  *(undefined8 *)(this + 0x7a0) = 0;
  *(undefined8 *)(this + 0x7b8) = 0;
  *(CIpodIap2 **)(this + 0x7c0) = this + 2000;
  *(undefined8 *)(this + 0x7c8) = 0;
  *(CIpodIap2 **)(this + 0x7e8) = this + 0x7e8;
  *(CIpodIap2 **)(this + 0x7f0) = this + 0x7e8;
  *(undefined8 *)(this + 0x7f8) = 0;
  *(CIpodIap2 **)(this + 0x848) = this + 0x858;
  *(CIpodIap2 **)(this + 0x800) = this + 0x810;
  *(undefined8 *)(this + 0x808) = 0;
  *(CIpodIap2 **)(this + 0x820) = this + 0x830;
  *(undefined8 *)(this + 0x828) = 0;
  *(undefined8 *)(this + 0x850) = 0;
  this[0x810] = (CIpodIap2)0x0;
  this[0x830] = (CIpodIap2)0x0;
  this[0x858] = (CIpodIap2)0x0;
  this[0x868] = (CIpodIap2)0x0;
  this[0x869] = (CIpodIap2)0x0;
  this[0x86a] = (CIpodIap2)0x1;
  *(undefined4 *)(this + 0x840) = 0;
  CIap2Sqlite::CIap2Sqlite((CIap2Sqlite *)(this + 0x870));
  this[0x8b8] = (CIpodIap2)0x0;
  *(CIpodIap2 **)(this + 0x8c8) = this + 0x8d8;
  this[0x8d8] = (CIpodIap2)0x0;
  *(CIpodIap2 **)(this + 0x8f0) = this + 0x900;
  this[0x900] = (CIpodIap2)0x0;
  *(CIpodIap2 **)(this + 0x8a8) = this + 0x8b8;
  *(undefined8 *)(this + 0x8b0) = 0;
  *(undefined8 *)(this + 0x8d0) = 0;
  *(undefined8 *)(this + 0x8f8) = 0;
  this[0x912] = (CIpodIap2)0x1;
  this[0x910] = (CIpodIap2)0x0;
  this[0x911] = (CIpodIap2)0x0;
  *(undefined4 *)(this + 0x8e8) = 0;
  CIap2Sqlite::CIap2Sqlite((CIap2Sqlite *)(this + 0x918));
  *(CIpodIap2 **)(this + 0x950) = this + 0x950;
  *(CIpodIap2 **)(this + 0x958) = this + 0x950;
  *(undefined8 *)(this + 0x960) = 0;
  *(CIpodIap2 **)(this + 0x970) = this + 0x970;
  *(CIpodIap2 **)(this + 0x978) = this + 0x970;
  this[0x98c] = (CIpodIap2)0x0;
  *(undefined8 *)(this + 0x968) = 0;
  *(undefined8 *)(this + 0x980) = 0;
  *(undefined4 *)(this + 0x988) = 0;
  *(undefined8 *)(this + 0x990) = 0;
  CIpodLog::w("CIpodIap2 CIpodIap2::CIpodIap2()\n");
  iVar1 = rand();
  this[0x11] = (CIpodIap2)0x0;
  this[0x10] = SUB41(iVar1,0);
  this[0x50] = (CIpodIap2)0x0;
  this[0x51] = (CIpodIap2)0x0;
  this[0x52] = (CIpodIap2)0x1;
  this[0x53] = (CIpodIap2)0x1;
  this[0x54] = (CIpodIap2)0x0;
  *(undefined2 *)(this + 0x588) = 0;
  *(undefined8 *)(this + 0x14) = 0;
  return;
}


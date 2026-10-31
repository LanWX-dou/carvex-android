/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11f7e8
 * original code SHA256: 216d4962aaf09a23cdf907f3488b0a32c985c2e0909ebde06dea3cd37685b60e
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodDevice::checkIap2Support() */

int __thiscall CIpodDevice::checkIap2Support(CIpodDevice *this)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  
  CIpodLog::i("[ Accessory ] step 1:  DETECT\n");
  *(undefined4 *)(this + 0xa8) = 1;
  if (*(code **)(*(long *)this + 0x18) == send) {
    if (this[0x118] != (CIpodDevice)0x0) goto LAB_0011f888;
    iVar1 = FUN_0011e368(this,&DAT_001427d0,6);
  }
  else {
    iVar1 = (**(code **)(*(long *)this + 0x18))(this,&DAT_001427d0,6,0);
  }
  if (iVar1 != -1) {
    sem_wait((sem_t *)(this + 0x88));
    return -(uint)(*(int *)(this + 0xa8) != 2);
  }
LAB_0011f888:
  piVar2 = __errno_location();
  pcVar3 = strerror(*piVar2);
  CIpodLog::i("CIpodDevice::checkIap2Support, send error! %s\n",pcVar3);
  return -1;
}


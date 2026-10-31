/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x13c9a0
 * original code SHA256: 6085fc56f9de574d486bce3eb6e634a4888ee5c6ff5f15a37c2dd1335620a845
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodLib::disconnect(int*) */

undefined8 __thiscall CIpodLib::disconnect(CIpodLib *this,int *param_1)

{
  char cVar1;
  undefined8 uVar2;
  
  CIpodLog::i("iAP2 device starts to disconnect handle: %d.\n",(ulong)(uint)*param_1);
  CIpodSync::lock();
  cVar1 = CIpodList::isDeviceExist(*param_1);
  if (cVar1 == '\0') {
    uVar2 = 0xffffffff;
    CIpodLog::i("iAP2 device dose not exist handle: %d.\n",(ulong)(uint)*param_1);
  }
  else {
    CIpodLog::i("iAP2 device exist and start pop handle: %d.\n",(ulong)(uint)*param_1);
    uVar2 = 0;
    CIpodList::pop(*param_1);
    *param_1 = -1;
    CIpodLog::i("iAP2 device disconnect successfully.\n");
  }
  CIpodSync::unlock();
  return uVar2;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x13d738
 * original code SHA256: ba4c9fa1775d28c0f19c218c1ed3d2e5d76115f77a697f75fa69ab77740e9af3
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodLib::ipod_bt_spp_state_change(__BtSppState) */

void __thiscall CIpodLib::ipod_bt_spp_state_change(undefined8 param_1,uint param_2)

{
  int iVar1;
  ulong uVar2;
  
  uVar2 = CIpodVehicle::getbtSppConnStatus();
  CIpodLog::i("Rfcomm connect state changed :%d -> %d\n",uVar2 & 0xffffffff,(ulong)param_2);
  iVar1 = CIpodVehicle::getbtSppConnStatus();
  CIpodVehicle::setbtSppConnStatus(param_2);
  if (param_2 == 3 || iVar1 != 3) {
    return;
  }
  CIpodEvent::sendEvent(0,0xff,0);
  return;
}


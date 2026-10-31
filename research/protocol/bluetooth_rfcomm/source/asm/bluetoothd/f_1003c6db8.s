; bluetoothd 0x1003c6db8..0x1003c6df4; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1003c6db8: 7f2303d5 pacibsp 
0x1003c6dbc: f44fbea9 stp x20, x19, [sp, #-0x20]!
0x1003c6dc0: fd7b01a9 stp x29, x30, [sp, #0x10]
0x1003c6dc4: fd430091 add x29, sp, #0x10
0x1003c6dc8: f30300aa mov x19, x0
0x1003c6dcc: 400000b5 cbnz x0, #0x1003c6dd4
0x1003c6dd0: 9ac9f497 bl #0x1000f9438
0x1003c6dd4: 602640b9 ldr w0, [x19, #0x24]
0x1003c6dd8: fd7b41a9 ldp x29, x30, [sp, #0x10]
0x1003c6ddc: f44fc2a8 ldp x20, x19, [sp], #0x20
0x1003c6de0: ff2303d5 autibsp 
0x1003c6de4: d0071eca eor x16, x30, x30, lsl #1
0x1003c6de8: 5000f0b6 tbz x16, #0x3e, #0x1003c6df0
0x1003c6dec: 208e38d4 brk #0xc471
0x1003c6df0: 0367f217 b #0x1000609fc

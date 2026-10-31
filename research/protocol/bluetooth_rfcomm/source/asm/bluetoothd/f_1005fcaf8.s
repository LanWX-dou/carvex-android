; bluetoothd 0x1005fcaf8..0x1005fcb40; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1005fcaf8: 7f2303d5 pacibsp 
0x1005fcafc: ffc300d1 sub sp, sp, #0x30
0x1005fcb00: f44f01a9 stp x20, x19, [sp, #0x10]
0x1005fcb04: fd7b02a9 stp x29, x30, [sp, #0x20]
0x1005fcb08: fd830091 add x29, sp, #0x20
0x1005fcb0c: f30300aa mov x19, x0
0x1005fcb10: ff7f00a9 stp xzr, xzr, [sp]
0x1005fcb14: e0030091 mov x0, sp
0x1005fcb18: e10313aa mov x1, x19
0x1005fcb1c: f728e897 bl #0x100006ef8
0x1005fcb20: 731e5939 ldrb w19, [x19, #0x647]
0x1005fcb24: e0030091 mov x0, sp
0x1005fcb28: e628e897 bl #0x100006ec0
0x1005fcb2c: e00313aa mov x0, x19
0x1005fcb30: fd7b42a9 ldp x29, x30, [sp, #0x20]
0x1005fcb34: f44f41a9 ldp x20, x19, [sp, #0x10]
0x1005fcb38: ffc30091 add sp, sp, #0x30
0x1005fcb3c: ff0f5fd6 retab 

; bluetoothd 0x1003c6c18..0x1003c6c8c; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1003c6c18: 7f2303d5 pacibsp 
0x1003c6c1c: ff0301d1 sub sp, sp, #0x40
0x1003c6c20: f44f02a9 stp x20, x19, [sp, #0x20]
0x1003c6c24: fd7b03a9 stp x29, x30, [sp, #0x30]
0x1003c6c28: fdc30091 add x29, sp, #0x30
0x1003c6c2c: f30300aa mov x19, x0
0x1003c6c30: e00f00f9 str x0, [sp, #0x18]
0x1003c6c34: ff0700f9 str xzr, [sp, #8]
0x1003c6c38: 600e42b8 ldr w0, [x19, #0x20]!
0x1003c6c3c: 7067f297 bl #0x1000609fc
0x1003c6c40: e8630091 add x8, sp, #0x18
0x1003c6c44: e80b00f9 str x8, [sp, #0x10]
0x1003c6c48: 08018052 mov w8, #8
0x1003c6c4c: e8130079 strh w8, [sp, #8]
0x1003c6c50: 284700f0 adrp x8, #0x100cad000
0x1003c6c54: 08a13591 add x8, x8, #0xd68
0x1003c6c58: 080140f9 ldr x8, [x8]
0x1003c6c5c: 02094079 ldrh w2, [x8, #4]
0x1003c6c60: 10000090 adrp x16, #0x1003c6000
0x1003c6c64: 10323291 add x16, x16, #0xc8c
0x1003c6c68: f023c1da paciza x16
0x1003c6c6c: e00310aa mov x0, x16
0x1003c6c70: e1230091 add x1, sp, #8
0x1003c6c74: e30313aa mov x3, x19
0x1003c6c78: b969f297 bl #0x10006135c
0x1003c6c7c: fd7b43a9 ldp x29, x30, [sp, #0x30]
0x1003c6c80: f44f42a9 ldp x20, x19, [sp, #0x20]
0x1003c6c84: ff030191 add sp, sp, #0x40
0x1003c6c88: ff0f5fd6 retab 

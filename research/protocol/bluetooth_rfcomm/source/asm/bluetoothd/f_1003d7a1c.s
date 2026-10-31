; bluetoothd 0x1003d7a1c..0x1003d7a60; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1003d7a1c: 7f2303d5 pacibsp 
0x1003d7a20: f44fbea9 stp x20, x19, [sp, #-0x20]!
0x1003d7a24: fd7b01a9 stp x29, x30, [sp, #0x10]
0x1003d7a28: fd430091 add x29, sp, #0x10
0x1003d7a2c: f30300aa mov x19, x0
0x1003d7a30: 1f1c0171 cmp w0, #0x47
0x1003d7a34: 43000054 b.lo #0x1003d7a3c
0x1003d7a38: 8086f497 bl #0x1000f9438
0x1003d7a3c: 144300b0 adrp x20, #0x100c38000
0x1003d7a40: 94021591 add x20, x20, #0x540
0x1003d7a44: 805a73f8 ldr x0, [x20, w19, uxtw #3]
0x1003d7a48: 600000b5 cbnz x0, #0x1003d7a54
0x1003d7a4c: 7b86f497 bl #0x1000f9438
0x1003d7a50: 805a73f8 ldr x0, [x20, w19, uxtw #3]
0x1003d7a54: fd7b41a9 ldp x29, x30, [sp, #0x10]
0x1003d7a58: f44fc2a8 ldp x20, x19, [sp], #0x20
0x1003d7a5c: ff0f5fd6 retab 

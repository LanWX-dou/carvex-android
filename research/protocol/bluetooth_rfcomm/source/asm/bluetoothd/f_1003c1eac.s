; bluetoothd 0x1003c1eac..0x1003c1f0c; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1003c1eac: 7f2303d5 pacibsp 
0x1003c1eb0: f44fbea9 stp x20, x19, [sp, #-0x20]!
0x1003c1eb4: fd7b01a9 stp x29, x30, [sp, #0x10]
0x1003c1eb8: fd430091 add x29, sp, #0x10
0x1003c1ebc: b34300f0 adrp x19, #0x100c38000
0x1003c1ec0: 689241f9 ldr x8, [x19, #0x320]
0x1003c1ec4: 880000b5 cbnz x8, #0x1003c1ed4
0x1003c1ec8: 5cddf497 bl #0x1000f9438
0x1003c1ecc: 689241f9 ldr x8, [x19, #0x320]
0x1003c1ed0: a80000b4 cbz x8, #0x1003c1ee4
0x1003c1ed4: 090140b9 ldr w9, [x8]
0x1003c1ed8: 29050071 subs w9, w9, #1
0x1003c1edc: 090100b9 str w9, [x8]
0x1003c1ee0: 80000054 b.eq #0x1003c1ef0
0x1003c1ee4: fd7b41a9 ldp x29, x30, [sp, #0x10]
0x1003c1ee8: f44fc2a8 ldp x20, x19, [sp], #0x20
0x1003c1eec: ff0f5fd6 retab 
0x1003c1ef0: fd7b41a9 ldp x29, x30, [sp, #0x10]
0x1003c1ef4: f44fc2a8 ldp x20, x19, [sp], #0x20
0x1003c1ef8: ff2303d5 autibsp 
0x1003c1efc: d0071eca eor x16, x30, x30, lsl #1
0x1003c1f00: 5000f0b6 tbz x16, #0x3e, #0x1003c1f08
0x1003c1f04: 208e38d4 brk #0xc471
0x1003c1f08: 99030014 b #0x1003c2d6c

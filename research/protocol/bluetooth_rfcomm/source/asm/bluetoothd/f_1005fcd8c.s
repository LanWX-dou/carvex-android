; bluetoothd 0x1005fcd8c..0x1005fcf24; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1005fcd8c: 7f2303d5 pacibsp 
0x1005fcd90: ff8302d1 sub sp, sp, #0xa0
0x1005fcd94: f65707a9 stp x22, x21, [sp, #0x70]
0x1005fcd98: f44f08a9 stp x20, x19, [sp, #0x80]
0x1005fcd9c: fd7b09a9 stp x29, x30, [sp, #0x90]
0x1005fcda0: fd430291 add x29, sp, #0x90
0x1005fcda4: f40301aa mov x20, x1
0x1005fcda8: f30300aa mov x19, x0
0x1005fcdac: bf7f3da9 stp xzr, xzr, [x29, #-0x30]
0x1005fcdb0: a0c300d1 sub x0, x29, #0x30
0x1005fcdb4: e10313aa mov x1, x19
0x1005fcdb8: 5028e897 bl #0x100006ef8
0x1005fcdbc: 763e43f9 ldr x22, [x19, #0x678]
0x1005fcdc0: f60300b5 cbnz x22, #0x1005fce3c
0x1005fcdc4: dd6ae897 bl #0x100017938
0x1005fcdc8: 030440f9 ldr x3, [x0, #8]
0x1005fcdcc: 00300090 adrp x0, #0x100bfc000
0x1005fcdd0: 00e044f9 ldr x0, [x0, #0x9c0]
0x1005fcdd4: 010080d2 mov x1, #0
0x1005fcdd8: 020080d2 mov x2, #0
0x1005fcddc: 1d360c94 bl #0x10090a650
0x1005fcde0: 603e03f9 str x0, [x19, #0x678]
0x1005fcde4: e8e30091 add x8, sp, #0x38
0x1005fcde8: 10300090 adrp x16, #0x100bfc000
0x1005fcdec: 10be44f9 ldr x16, [x16, #0x978]
0x1005fcdf0: f10308aa mov x17, x8
0x1005fcdf4: 315cedf2 movk x17, #0x6ae1, lsl #48
0x1005fcdf8: 300ac1da pacda x16, x17
0x1005fcdfc: f01f00f9 str x16, [sp, #0x38]
0x1005fce00: a9190090 adrp x9, #0x100930000
0x1005fce04: 203940fd ldr d0, [x9, #0x70]
0x1005fce08: e02300fd str d0, [sp, #0x40]
0x1005fce0c: 08410091 add x8, x8, #0x10
0x1005fce10: 10000090 adrp x16, #0x1005fc000
0x1005fce14: 10923c91 add x16, x16, #0xf24
0x1005fce18: 1001c1da pacia x16, x8
0x1005fce1c: 082d0090 adrp x8, #0x100b9c000
0x1005fce20: 08e11291 add x8, x8, #0x4b8
0x1005fce24: f0a304a9 stp x16, x8, [sp, #0x48]
0x1005fce28: f32f00f9 str x19, [sp, #0x58]
0x1005fce2c: e1e30091 add x1, sp, #0x38
0x1005fce30: 14360c94 bl #0x10090a680
0x1005fce34: 763e43f9 ldr x22, [x19, #0x678]
0x1005fce38: d60500b4 cbz x22, #0x1005fcef0
0x1005fce3c: 883500d0 adrp x8, #0x100cae000
0x1005fce40: 08011191 add x8, x8, #0x440
0x1005fce44: 150140f9 ldr x21, [x8]
0x1005fce48: e00315aa mov x0, x21
0x1005fce4c: 01008052 mov w1, #0
0x1005fce50: 003a0c94 bl #0x10090b650
0x1005fce54: 60030034 cbz w0, #0x1005fcec0
0x1005fce58: f6230091 add x22, sp, #8
0x1005fce5c: e8230091 add x8, sp, #8
0x1005fce60: e00313aa mov x0, x19
0x1005fce64: 0837ec97 bl #0x10010aa84
0x1005fce68: e87fc039 ldrsb w8, [sp, #0x1f]
0x1005fce6c: e90740f9 ldr x9, [sp, #8]
0x1005fce70: 1f010071 cmp w8, #0
0x1005fce74: 28b1969a csel x8, x9, x22, lt
0x1005fce78: a9190090 adrp x9, #0x100930000
0x1005fce7c: 209145fd ldr d0, [x9, #0xb20]
0x1005fce80: e02300bd str s0, [sp, #0x20]
0x1005fce84: e84302f8 stur x8, [sp, #0x24]
0x1005fce88: 20d0ff90 adrp x0, #0x100000000
0x1005fce8c: 00000091 add x0, x0, #0
0x1005fce90: 63280090 adrp x3, #0x100b08000
0x1005fce94: 63a40191 add x3, x3, #0x69
0x1005fce98: e4830091 add x4, sp, #0x20
0x1005fce9c: e10315aa mov x1, x21
0x1005fcea0: 02008052 mov w2, #0
0x1005fcea4: 85018052 mov w5, #0xc
0x1005fcea8: f2330c94 bl #0x100909e70
0x1005fceac: e87fc039 ldrsb w8, [sp, #0x1f]
0x1005fceb0: 6800f836 tbz w8, #0x1f, #0x1005fcebc
0x1005fceb4: e00740f9 ldr x0, [sp, #8]
0x1005fceb8: 5e330c94 bl #0x100909c30
0x1005fcebc: 763e43f9 ldr x22, [x19, #0x678]
0x1005fcec0: 08409952 mov w8, #0xca00
0x1005fcec4: 4873a772 movk w8, #0x3b9a, lsl #16
0x1005fcec8: 817ea89b umull x1, w20, w8
0x1005fcecc: 000080d2 mov x0, #0
0x1005fced0: 00360c94 bl #0x10090a6d0
0x1005fced4: e10300aa mov x1, x0
0x1005fced8: e00316aa mov x0, x22
0x1005fcedc: 02008092 mov x2, #-1
0x1005fcee0: 030080d2 mov x3, #0
0x1005fcee4: ef350c94 bl #0x10090a6a0
0x1005fcee8: 603e43f9 ldr x0, [x19, #0x678]
0x1005fceec: b9350c94 bl #0x10090a5d0
0x1005fcef0: a0c300d1 sub x0, x29, #0x30
0x1005fcef4: f327e897 bl #0x100006ec0
0x1005fcef8: fd7b49a9 ldp x29, x30, [sp, #0x90]
0x1005fcefc: f44f48a9 ldp x20, x19, [sp, #0x80]
0x1005fcf00: f65747a9 ldp x22, x21, [sp, #0x70]
0x1005fcf04: ff830291 add sp, sp, #0xa0
0x1005fcf08: ff0f5fd6 retab 
0x1005fcf0c: 01000014 b #0x1005fcf10
0x1005fcf10: f30300aa mov x19, x0
0x1005fcf14: a0c300d1 sub x0, x29, #0x30
0x1005fcf18: ea27e897 bl #0x100006ec0
0x1005fcf1c: e00313aa mov x0, x19
0x1005fcf20: 18320c94 bl #0x100909780

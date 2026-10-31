; bluetoothd 0x1005fcb40..0x1005fccfc; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1005fcb40: 7f2303d5 pacibsp 
0x1005fcb44: ff8302d1 sub sp, sp, #0xa0
0x1005fcb48: f65707a9 stp x22, x21, [sp, #0x70]
0x1005fcb4c: f44f08a9 stp x20, x19, [sp, #0x80]
0x1005fcb50: fd7b09a9 stp x29, x30, [sp, #0x90]
0x1005fcb54: fd430291 add x29, sp, #0x90
0x1005fcb58: f30300aa mov x19, x0
0x1005fcb5c: bf7f3da9 stp xzr, xzr, [x29, #-0x30]
0x1005fcb60: a0c300d1 sub x0, x29, #0x30
0x1005fcb64: e10313aa mov x1, x19
0x1005fcb68: e428e897 bl #0x100006ef8
0x1005fcb6c: 752643f9 ldr x21, [x19, #0x648]
0x1005fcb70: f50300b5 cbnz x21, #0x1005fcbec
0x1005fcb74: 716be897 bl #0x100017938
0x1005fcb78: 030440f9 ldr x3, [x0, #8]
0x1005fcb7c: 00300090 adrp x0, #0x100bfc000
0x1005fcb80: 00e044f9 ldr x0, [x0, #0x9c0]
0x1005fcb84: 010080d2 mov x1, #0
0x1005fcb88: 020080d2 mov x2, #0
0x1005fcb8c: b1360c94 bl #0x10090a650
0x1005fcb90: 602603f9 str x0, [x19, #0x648]
0x1005fcb94: e8e30091 add x8, sp, #0x38
0x1005fcb98: 10300090 adrp x16, #0x100bfc000
0x1005fcb9c: 10be44f9 ldr x16, [x16, #0x978]
0x1005fcba0: f10308aa mov x17, x8
0x1005fcba4: 315cedf2 movk x17, #0x6ae1, lsl #48
0x1005fcba8: 300ac1da pacda x16, x17
0x1005fcbac: f01f00f9 str x16, [sp, #0x38]
0x1005fcbb0: a9190090 adrp x9, #0x100930000
0x1005fcbb4: 203940fd ldr d0, [x9, #0x70]
0x1005fcbb8: e02300fd str d0, [sp, #0x40]
0x1005fcbbc: 08410091 add x8, x8, #0x10
0x1005fcbc0: 10000090 adrp x16, #0x1005fc000
0x1005fcbc4: 10f23391 add x16, x16, #0xcfc
0x1005fcbc8: 1001c1da pacia x16, x8
0x1005fcbcc: 082d0090 adrp x8, #0x100b9c000
0x1005fcbd0: 08e11291 add x8, x8, #0x4b8
0x1005fcbd4: f0a304a9 stp x16, x8, [sp, #0x48]
0x1005fcbd8: f32f00f9 str x19, [sp, #0x58]
0x1005fcbdc: e1e30091 add x1, sp, #0x38
0x1005fcbe0: a8360c94 bl #0x10090a680
0x1005fcbe4: 752643f9 ldr x21, [x19, #0x648]
0x1005fcbe8: 150700b4 cbz x21, #0x1005fccc8
0x1005fcbec: 68c24c79 ldrh w8, [x19, #0x660]
0x1005fcbf0: 08050011 add w8, w8, #1
0x1005fcbf4: 68c20c79 strh w8, [x19, #0x660]
0x1005fcbf8: 68425939 ldrb w8, [x19, #0x650]
0x1005fcbfc: 08050011 add w8, w8, #1
0x1005fcc00: 68421939 strb w8, [x19, #0x650]
0x1005fcc04: 883500d0 adrp x8, #0x100cae000
0x1005fcc08: 08011191 add x8, x8, #0x440
0x1005fcc0c: 140140f9 ldr x20, [x8]
0x1005fcc10: e00314aa mov x0, x20
0x1005fcc14: 01008052 mov w1, #0
0x1005fcc18: 8e3a0c94 bl #0x10090b650
0x1005fcc1c: e0030034 cbz w0, #0x1005fcc98
0x1005fcc20: f5230091 add x21, sp, #8
0x1005fcc24: e8230091 add x8, sp, #8
0x1005fcc28: e00313aa mov x0, x19
0x1005fcc2c: 9637ec97 bl #0x10010aa84
0x1005fcc30: e87fc039 ldrsb w8, [sp, #0x1f]
0x1005fcc34: e90740f9 ldr x9, [sp, #8]
0x1005fcc38: 1f010071 cmp w8, #0
0x1005fcc3c: 28b1959a csel x8, x9, x21, lt
0x1005fcc40: a9190090 adrp x9, #0x100930000
0x1005fcc44: 207942fd ldr d0, [x9, #0x4f0]
0x1005fcc48: e02300bd str s0, [sp, #0x20]
0x1005fcc4c: 89258052 mov w9, #0x12c
0x1005fcc50: e92700b9 str w9, [sp, #0x24]
0x1005fcc54: 49048152 mov w9, #0x822
0x1005fcc58: e9530079 strh w9, [sp, #0x28]
0x1005fcc5c: e8a302f8 stur x8, [sp, #0x2a]
0x1005fcc60: 20d0ff90 adrp x0, #0x100000000
0x1005fcc64: 00000091 add x0, x0, #0
0x1005fcc68: 432800f0 adrp x3, #0x100b07000
0x1005fcc6c: 63703f91 add x3, x3, #0xfdc
0x1005fcc70: e4830091 add x4, sp, #0x20
0x1005fcc74: e10314aa mov x1, x20
0x1005fcc78: 02008052 mov w2, #0
0x1005fcc7c: 45028052 mov w5, #0x12
0x1005fcc80: 7c340c94 bl #0x100909e70
0x1005fcc84: e87fc039 ldrsb w8, [sp, #0x1f]
0x1005fcc88: 6800f836 tbz w8, #0x1f, #0x1005fcc94
0x1005fcc8c: e00740f9 ldr x0, [sp, #8]
0x1005fcc90: e8330c94 bl #0x100909c30
0x1005fcc94: 752643f9 ldr x21, [x19, #0x648]
0x1005fcc98: 010097d2 mov x1, #0xb800
0x1005fcc9c: 812cbbf2 movk x1, #0xd964, lsl #16
0x1005fcca0: a108c0f2 movk x1, #0x45, lsl #32
0x1005fcca4: 000080d2 mov x0, #0
0x1005fcca8: 8a360c94 bl #0x10090a6d0
0x1005fccac: e10300aa mov x1, x0
0x1005fccb0: e00315aa mov x0, x21
0x1005fccb4: 02008092 mov x2, #-1
0x1005fccb8: 030080d2 mov x3, #0
0x1005fccbc: 79360c94 bl #0x10090a6a0
0x1005fccc0: 602643f9 ldr x0, [x19, #0x648]
0x1005fccc4: 43360c94 bl #0x10090a5d0
0x1005fccc8: a0c300d1 sub x0, x29, #0x30
0x1005fcccc: 7d28e897 bl #0x100006ec0
0x1005fccd0: fd7b49a9 ldp x29, x30, [sp, #0x90]
0x1005fccd4: f44f48a9 ldp x20, x19, [sp, #0x80]
0x1005fccd8: f65747a9 ldp x22, x21, [sp, #0x70]
0x1005fccdc: ff830291 add sp, sp, #0xa0
0x1005fcce0: ff0f5fd6 retab 
0x1005fcce4: 01000014 b #0x1005fcce8
0x1005fcce8: f30300aa mov x19, x0
0x1005fccec: a0c300d1 sub x0, x29, #0x30
0x1005fccf0: 7428e897 bl #0x100006ec0
0x1005fccf4: e00313aa mov x0, x19
0x1005fccf8: a2320c94 bl #0x100909780

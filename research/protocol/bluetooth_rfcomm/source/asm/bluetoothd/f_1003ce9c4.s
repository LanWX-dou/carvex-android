; bluetoothd 0x1003ce9c4..0x1003cec64; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1003ce9c4: 7f2303d5 pacibsp 
0x1003ce9c8: ffc301d1 sub sp, sp, #0x70
0x1003ce9cc: fa6702a9 stp x26, x25, [sp, #0x20]
0x1003ce9d0: f85f03a9 stp x24, x23, [sp, #0x30]
0x1003ce9d4: f65704a9 stp x22, x21, [sp, #0x40]
0x1003ce9d8: f44f05a9 stp x20, x19, [sp, #0x50]
0x1003ce9dc: fd7b06a9 stp x29, x30, [sp, #0x60]
0x1003ce9e0: fd830191 add x29, sp, #0x60
0x1003ce9e4: f30302aa mov x19, x2
0x1003ce9e8: f40300aa mov x20, x0
0x1003ce9ec: ff7f01a9 stp xzr, xzr, [sp, #0x10]
0x1003ce9f0: ff1b0079 strh wzr, [sp, #0xc]
0x1003ce9f4: 283c4039 ldrb w8, [x1, #0xf]
0x1003ce9f8: 08010034 cbz w8, #0x1003cea18
0x1003ce9fc: 403300d0 adrp x0, #0x100a38000
0x1003cea00: 003c2a91 add x0, x0, #0xa8f
0x1003cea04: 423300d0 adrp x2, #0x100a38000
0x1003cea08: 426c3c91 add x2, x2, #0xf1b
0x1003cea0c: 01998052 mov w1, #0x4c8
0x1003cea10: d7fdf697 bl #0x10018e16c
0x1003cea14: 07000014 b #0x1003cea30
0x1003cea18: f80301aa mov x24, x1
0x1003cea1c: 29144079 ldrh w9, [x1, #0xa]
0x1003cea20: 28184079 ldrh w8, [x1, #0xc]
0x1003cea24: 2a0108cb sub x10, x9, x8
0x1003cea28: 5f1900f1 cmp x10, #6
0x1003cea2c: 02040054 b.hs #0x1003ceaac
0x1003cea30: 96648052 mov w22, #0x324
0x1003cea34: 40008052 mov w0, #2
0x1003cea38: a1068052 mov w1, #0x35
0x1003cea3c: bffbf097 bl #0x10000d938
0x1003cea40: 60010034 cbz w0, #0x1003cea6c
0x1003cea44: f60300f9 str x22, [sp]
0x1003cea48: 403300d0 adrp x0, #0x100a38000
0x1003cea4c: 000c3e91 add x0, x0, #0xf83
0x1003cea50: b4f9f097 bl #0x10000d120
0x1003cea54: a0068052 mov w0, #0x35
0x1003cea58: dffff097 bl #0x10000e9d4
0x1003cea5c: f50300aa mov x21, x0
0x1003cea60: 01028052 mov w1, #0x10
0x1003cea64: fbf21494 bl #0x10090b650
0x1003cea68: e0080035 cbnz w0, #0x1003ceb84
0x1003cea6c: 600240f9 ldr x0, [x19]
0x1003cea70: 400000b4 cbz x0, #0x1003cea78
0x1003cea74: 9109f197 bl #0x1000110b8
0x1003cea78: e0430091 add x0, sp, #0x10
0x1003cea7c: 961dfd97 bl #0x1003160d4
0x1003cea80: e00316aa mov x0, x22
0x1003cea84: e10314aa mov x1, x20
0x1003cea88: e20313aa mov x2, x19
0x1003cea8c: 76fdff97 bl #0x1003ce064
0x1003cea90: fd7b46a9 ldp x29, x30, [sp, #0x60]
0x1003cea94: f44f45a9 ldp x20, x19, [sp, #0x50]
0x1003cea98: f65744a9 ldp x22, x21, [sp, #0x40]
0x1003cea9c: f85f43a9 ldp x24, x23, [sp, #0x30]
0x1003ceaa0: fa6742a9 ldp x26, x25, [sp, #0x20]
0x1003ceaa4: ffc30191 add sp, sp, #0x70
0x1003ceaa8: ff0f5fd6 retab 
0x1003ceaac: 0a3b4039 ldrb w10, [x24, #0xe]
0x1003ceab0: 5f050071 cmp w10, #1
0x1003ceab4: c10c0054 b.ne #0x1003cec4c
0x1003ceab8: 2a01084b sub w10, w9, w8
0x1003ceabc: 5f0d0071 cmp w10, #3
0x1003ceac0: ad040054 b.le #0x1003ceb54
0x1003ceac4: 0a0340f9 ldr x10, [x24]
0x1003ceac8: 596968b8 ldr w25, [x10, x8]
0x1003ceacc: 0a110011 add w10, w8, #4
0x1003cead0: 0a1b0079 strh w10, [x24, #0xc]
0x1003cead4: 29212a4b sub w9, w9, w10, uxth
0x1003cead8: 3f050071 cmp w9, #1
0x1003ceadc: cd040054 b.le #0x1003ceb74
0x1003ceae0: 090340f9 ldr x9, [x24]
0x1003ceae4: 29212a8b add x9, x9, w10, uxth
0x1003ceae8: 3a014079 ldrh w26, [x9]
0x1003ceaec: 490bc05a rev w9, w26
0x1003ceaf0: 297d1053 lsr w9, w9, #0x10
0x1003ceaf4: 08190011 add w8, w8, #6
0x1003ceaf8: 081b0079 strh w8, [x24, #0xc]
0x1003ceafc: 3f1d0071 cmp w9, #7
0x1003ceb00: e3030054 b.lo #0x1003ceb7c
0x1003ceb04: f50304aa mov x21, x4
0x1003ceb08: f70303aa mov x23, x3
0x1003ceb0c: e1430091 add x1, sp, #0x10
0x1003ceb10: e00318aa mov x0, x24
0x1003ceb14: 71020094 bl #0x1003cf4d8
0x1003ceb18: a0010035 cbnz w0, #0x1003ceb4c
0x1003ceb1c: e13b0091 add x1, sp, #0xe
0x1003ceb20: e00318aa mov x0, x24
0x1003ceb24: 73010094 bl #0x1003cf0f0
0x1003ceb28: 20010035 cbnz w0, #0x1003ceb4c
0x1003ceb2c: 4807c05a rev16 w8, w26
0x1003ceb30: ff170079 strh wzr, [sp, #0xa]
0x1003ceb34: 013d0012 and w1, w8, #0xffff
0x1003ceb38: e32b0091 add x3, sp, #0xa
0x1003ceb3c: e00313aa mov x0, x19
0x1003ceb40: e20317aa mov x2, x23
0x1003ceb44: 86020094 bl #0x1003cf55c
0x1003ceb48: 40020034 cbz w0, #0x1003ceb90
0x1003ceb4c: f60300aa mov x22, x0
0x1003ceb50: b9ffff17 b #0x1003cea34
0x1003ceb54: 28008052 mov w8, #1
0x1003ceb58: 083f0039 strb w8, [x24, #0xf]
0x1003ceb5c: 403300d0 adrp x0, #0x100a38000
0x1003ceb60: 003c2a91 add x0, x0, #0xa8f
0x1003ceb64: 423300d0 adrp x2, #0x100a38000
0x1003ceb68: 426c3c91 add x2, x2, #0xf1b
0x1003ceb6c: a1998052 mov w1, #0x4cd
0x1003ceb70: 7ffdf697 bl #0x10018e16c
0x1003ceb74: 28008052 mov w8, #1
0x1003ceb78: 083f0039 strb w8, [x24, #0xf]
0x1003ceb7c: 76648052 mov w22, #0x323
0x1003ceb80: adffff17 b #0x1003cea34
0x1003ceb84: e00315aa mov x0, x21
0x1003ceb88: 7201f797 bl #0x10018f150
0x1003ceb8c: b8ffff17 b #0x1003cea6c
0x1003ceb90: 370bc05a rev w23, w25
0x1003ceb94: f61f4079 ldrh w22, [sp, #0xe]
0x1003ceb98: b6020034 cbz w22, #0x1003cebec
0x1003ceb9c: f61b0079 strh w22, [sp, #0xc]
0x1003ceba0: 781a4079 ldrh w24, [x19, #0xc]
0x1003ceba4: e1430091 add x1, sp, #0x10
0x1003ceba8: e2330091 add x2, sp, #0xc
0x1003cebac: e00317aa mov x0, x23
0x1003cebb0: e30313aa mov x3, x19
0x1003cebb4: e40315aa mov x4, x21
0x1003cebb8: 79030094 bl #0x1003cf99c
0x1003cebbc: e0000037 tbnz w0, #0, #0x1003cebd8
0x1003cebc0: 681a4079 ldrh w8, [x19, #0xc]
0x1003cebc4: 0801184b sub w8, w8, w24
0x1003cebc8: 0801160b add w8, w8, w22
0x1003cebcc: 1f3d0072 tst w8, #0xffff
0x1003cebd0: 61000054 b.ne #0x1003cebdc
0x1003cebd4: 19aaf497 bl #0x1000f9438
0x1003cebd8: 08008052 mov w8, #0
0x1003cebdc: e91b4079 ldrh w9, [sp, #0xc]
0x1003cebe0: e9010034 cbz w9, #0x1003cec1c
0x1003cebe4: b6648052 mov w22, #0x325
0x1003cebe8: 93ffff17 b #0x1003cea34
0x1003cebec: e1430091 add x1, sp, #0x10
0x1003cebf0: e2230091 add x2, sp, #8
0x1003cebf4: e00317aa mov x0, x23
0x1003cebf8: e30315aa mov x3, x21
0x1003cebfc: 91020094 bl #0x1003cf640
0x1003cec00: 60faff35 cbnz w0, #0x1003ceb4c
0x1003cec04: e1134079 ldrh w1, [sp, #8]
0x1003cec08: e23b0091 add x2, sp, #0xe
0x1003cec0c: e00313aa mov x0, x19
0x1003cec10: ca020094 bl #0x1003cf738
0x1003cec14: f61f4079 ldrh w22, [sp, #0xe]
0x1003cec18: e1ffff17 b #0x1003ceb9c
0x1003cec1c: e1174079 ldrh w1, [sp, #0xa]
0x1003cec20: 023d0012 and w2, w8, #0xffff
0x1003cec24: e00313aa mov x0, x19
0x1003cec28: a6030094 bl #0x1003cfac0
0x1003cec2c: e00313aa mov x0, x19
0x1003cec30: a1008052 mov w1, #5
0x1003cec34: e20314aa mov x2, x20
0x1003cec38: a9010094 bl #0x1003cf2dc
0x1003cec3c: e0430091 add x0, sp, #0x10
0x1003cec40: 251dfd97 bl #0x1003160d4
0x1003cec44: 00008052 mov w0, #0
0x1003cec48: 92ffff17 b #0x1003cea90
0x1003cec4c: 403300d0 adrp x0, #0x100a38000
0x1003cec50: 003c2a91 add x0, x0, #0xa8f
0x1003cec54: 423300d0 adrp x2, #0x100a38000
0x1003cec58: 42c83191 add x2, x2, #0xc72
0x1003cec5c: 81998052 mov w1, #0x4cc
0x1003cec60: 85fdf497 bl #0x10010e274

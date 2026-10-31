; bluetoothd 0x1003cec64..0x1003cef98; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1003cec64: 7f2303d5 pacibsp 
0x1003cec68: ff4302d1 sub sp, sp, #0x90
0x1003cec6c: fa6704a9 stp x26, x25, [sp, #0x40]
0x1003cec70: f85f05a9 stp x24, x23, [sp, #0x50]
0x1003cec74: f65706a9 stp x22, x21, [sp, #0x60]
0x1003cec78: f44f07a9 stp x20, x19, [sp, #0x70]
0x1003cec7c: fd7b08a9 stp x29, x30, [sp, #0x80]
0x1003cec80: fd030291 add x29, sp, #0x80
0x1003cec84: f50304aa mov x21, x4
0x1003cec88: f70303aa mov x23, x3
0x1003cec8c: f30302aa mov x19, x2
0x1003cec90: f80301aa mov x24, x1
0x1003cec94: f40300aa mov x20, x0
0x1003cec98: ff7f03a9 stp xzr, xzr, [sp, #0x30]
0x1003cec9c: ff7f02a9 stp xzr, xzr, [sp, #0x20]
0x1003ceca0: ff1f00b9 str wzr, [sp, #0x1c]
0x1003ceca4: ff0b00f9 str xzr, [sp, #0x10]
0x1003ceca8: e1430091 add x1, sp, #0x10
0x1003cecac: e00304aa mov x0, x4
0x1003cecb0: 05a2f797 bl #0x1001b74c4
0x1003cecb4: e1830091 add x1, sp, #0x20
0x1003cecb8: e00318aa mov x0, x24
0x1003cecbc: ee000094 bl #0x1003cf074
0x1003cecc0: 60000034 cbz w0, #0x1003ceccc
0x1003cecc4: f60300aa mov x22, x0
0x1003cecc8: 54000014 b #0x1003cee18
0x1003ceccc: 083b4039 ldrb w8, [x24, #0xe]
0x1003cecd0: 1f050071 cmp w8, #1
0x1003cecd4: 61150054 b.ne #0x1003cef80
0x1003cecd8: 083f4039 ldrb w8, [x24, #0xf]
0x1003cecdc: 08010034 cbz w8, #0x1003cecfc
0x1003cece0: 403300d0 adrp x0, #0x100a38000
0x1003cece4: 003c2a91 add x0, x0, #0xa8f
0x1003cece8: 423300f0 adrp x2, #0x100a39000
0x1003cecec: 42680a91 add x2, x2, #0x29a
0x1003cecf0: 61ab8052 mov w1, #0x55b
0x1003cecf4: 1efdf697 bl #0x10018e16c
0x1003cecf8: 45000014 b #0x1003cee0c
0x1003cecfc: 09174079 ldrh w9, [x24, #0xa]
0x1003ced00: 081b4079 ldrh w8, [x24, #0xc]
0x1003ced04: 2901084b sub w9, w9, w8
0x1003ced08: 3f050071 cmp w9, #1
0x1003ced0c: 0d080054 b.le #0x1003cee0c
0x1003ced10: 090340f9 ldr x9, [x24]
0x1003ced14: 39696878 ldrh w25, [x9, x8]
0x1003ced18: 290bc05a rev w9, w25
0x1003ced1c: 297d1053 lsr w9, w9, #0x10
0x1003ced20: 08090011 add w8, w8, #2
0x1003ced24: 081b0079 strh w8, [x24, #0xc]
0x1003ced28: 3f1d0071 cmp w9, #7
0x1003ced2c: 43070054 b.lo #0x1003cee14
0x1003ced30: e1c30091 add x1, sp, #0x30
0x1003ced34: e00318aa mov x0, x24
0x1003ced38: e8010094 bl #0x1003cf4d8
0x1003ced3c: 40fcff35 cbnz w0, #0x1003cecc4
0x1003ced40: e16b0091 add x1, sp, #0x1a
0x1003ced44: e00318aa mov x0, x24
0x1003ced48: ea000094 bl #0x1003cf0f0
0x1003ced4c: c0fbff35 cbnz w0, #0x1003cecc4
0x1003ced50: 2807c05a rev16 w8, w25
0x1003ced54: ff330079 strh wzr, [sp, #0x18]
0x1003ced58: 013d0012 and w1, w8, #0xffff
0x1003ced5c: e3630091 add x3, sp, #0x18
0x1003ced60: e00313aa mov x0, x19
0x1003ced64: e20317aa mov x2, x23
0x1003ced68: fd010094 bl #0x1003cf55c
0x1003ced6c: c0faff35 cbnz w0, #0x1003cecc4
0x1003ced70: f7374079 ldrh w23, [sp, #0x1a]
0x1003ced74: 97090034 cbz w23, #0x1003ceea4
0x1003ced78: f73b0079 strh w23, [sp, #0x1c]
0x1003ced7c: 781a4079 ldrh w24, [x19, #0xc]
0x1003ced80: ff3f0079 strh wzr, [sp, #0x1e]
0x1003ced84: ff0f00b9 str wzr, [sp, #0xc]
0x1003ced88: e01740f9 ldr x0, [sp, #0x28]
0x1003ced8c: e1474079 ldrh w1, [sp, #0x22]
0x1003ced90: e40b40f9 ldr x4, [sp, #0x10]
0x1003ced94: e27b0091 add x2, sp, #0x1e
0x1003ced98: e3330091 add x3, sp, #0xc
0x1003ced9c: 3bf2ff97 bl #0x1003cb688
0x1003ceda0: 200b0035 cbnz w0, #0x1003cef04
0x1003ceda4: e00f40b9 ldr w0, [sp, #0xc]
0x1003ceda8: e1c30091 add x1, sp, #0x30
0x1003cedac: e22b0091 add x2, sp, #0xa
0x1003cedb0: e30315aa mov x3, x21
0x1003cedb4: 23020094 bl #0x1003cf640
0x1003cedb8: 60f8ff35 cbnz w0, #0x1003cecc4
0x1003cedbc: e1174079 ldrh w1, [sp, #0xa]
0x1003cedc0: 21feff34 cbz w1, #0x1003ced84
0x1003cedc4: e2730091 add x2, sp, #0x1c
0x1003cedc8: e00313aa mov x0, x19
0x1003cedcc: 5b020094 bl #0x1003cf738
0x1003cedd0: 00010034 cbz w0, #0x1003cedf0
0x1003cedd4: e00f40b9 ldr w0, [sp, #0xc]
0x1003cedd8: e1c30091 add x1, sp, #0x30
0x1003ceddc: e2730091 add x2, sp, #0x1c
0x1003cede0: e30313aa mov x3, x19
0x1003cede4: e40315aa mov x4, x21
0x1003cede8: ed020094 bl #0x1003cf99c
0x1003cedec: c0fc0737 tbnz w0, #0, #0x1003ced84
0x1003cedf0: 681a4079 ldrh w8, [x19, #0xc]
0x1003cedf4: 0801184b sub w8, w8, w24
0x1003cedf8: 0801170b add w8, w8, w23
0x1003cedfc: 1f3d0072 tst w8, #0xffff
0x1003cee00: a1080054 b.ne #0x1003cef14
0x1003cee04: 8da9f497 bl #0x1000f9438
0x1003cee08: 42000014 b #0x1003cef10
0x1003cee0c: 28008052 mov w8, #1
0x1003cee10: 083f0039 strb w8, [x24, #0xf]
0x1003cee14: 76648052 mov w22, #0x323
0x1003cee18: 40008052 mov w0, #2
0x1003cee1c: a1068052 mov w1, #0x35
0x1003cee20: c6faf097 bl #0x10000d938
0x1003cee24: 60010034 cbz w0, #0x1003cee50
0x1003cee28: f60300f9 str x22, [sp]
0x1003cee2c: 403300d0 adrp x0, #0x100a38000
0x1003cee30: 00703791 add x0, x0, #0xddc
0x1003cee34: bbf8f097 bl #0x10000d120
0x1003cee38: a0068052 mov w0, #0x35
0x1003cee3c: e6fef097 bl #0x10000e9d4
0x1003cee40: f50300aa mov x21, x0
0x1003cee44: 01028052 mov w1, #0x10
0x1003cee48: 02f21494 bl #0x10090b650
0x1003cee4c: 60020035 cbnz w0, #0x1003cee98
0x1003cee50: 600240f9 ldr x0, [x19]
0x1003cee54: 400000b4 cbz x0, #0x1003cee5c
0x1003cee58: 9808f197 bl #0x1000110b8
0x1003cee5c: e0830091 add x0, sp, #0x20
0x1003cee60: 9d1cfd97 bl #0x1003160d4
0x1003cee64: e0c30091 add x0, sp, #0x30
0x1003cee68: 9b1cfd97 bl #0x1003160d4
0x1003cee6c: e00316aa mov x0, x22
0x1003cee70: e10314aa mov x1, x20
0x1003cee74: e20313aa mov x2, x19
0x1003cee78: 7bfcff97 bl #0x1003ce064
0x1003cee7c: fd7b48a9 ldp x29, x30, [sp, #0x80]
0x1003cee80: f44f47a9 ldp x20, x19, [sp, #0x70]
0x1003cee84: f65746a9 ldp x22, x21, [sp, #0x60]
0x1003cee88: f85f45a9 ldp x24, x23, [sp, #0x50]
0x1003cee8c: fa6744a9 ldp x26, x25, [sp, #0x40]
0x1003cee90: ff430291 add sp, sp, #0x90
0x1003cee94: ff0f5fd6 retab 
0x1003cee98: e00315aa mov x0, x21
0x1003cee9c: ad00f797 bl #0x10018f150
0x1003ceea0: ecffff17 b #0x1003cee50
0x1003ceea4: ff0f00b9 str wzr, [sp, #0xc]
0x1003ceea8: ff3f0079 strh wzr, [sp, #0x1e]
0x1003ceeac: 58008052 mov w24, #2
0x1003ceeb0: e01740f9 ldr x0, [sp, #0x28]
0x1003ceeb4: e1474079 ldrh w1, [sp, #0x22]
0x1003ceeb8: e40b40f9 ldr x4, [sp, #0x10]
0x1003ceebc: e27b0091 add x2, sp, #0x1e
0x1003ceec0: e3330091 add x3, sp, #0xc
0x1003ceec4: f1f1ff97 bl #0x1003cb688
0x1003ceec8: e0020035 cbnz w0, #0x1003cef24
0x1003ceecc: e00f40b9 ldr w0, [sp, #0xc]
0x1003ceed0: e1c30091 add x1, sp, #0x30
0x1003ceed4: e22b0091 add x2, sp, #0xa
0x1003ceed8: e30315aa mov x3, x21
0x1003ceedc: d9010094 bl #0x1003cf640
0x1003ceee0: 20efff35 cbnz w0, #0x1003cecc4
0x1003ceee4: e8174079 ldrh w8, [sp, #0xa]
0x1003ceee8: 1ffd0371 cmp w8, #0xff
0x1003ceeec: 0997981a cinc w9, w24, hi
0x1003ceef0: 0a01170b add w10, w8, w23
0x1003ceef4: 4901090b add w9, w10, w9
0x1003ceef8: 1f010071 cmp w8, #0
0x1003ceefc: f702891a csel w23, w23, w9, eq
0x1003cef00: ecffff17 b #0x1003ceeb0
0x1003cef04: f60300aa mov x22, x0
0x1003cef08: 1fdc0c71 cmp w0, #0x337
0x1003cef0c: 61f8ff54 b.ne #0x1003cee18
0x1003cef10: 08008052 mov w8, #0
0x1003cef14: e93b4079 ldrh w9, [sp, #0x1c]
0x1003cef18: 89010034 cbz w9, #0x1003cef48
0x1003cef1c: b6648052 mov w22, #0x325
0x1003cef20: beffff17 b #0x1003cee18
0x1003cef24: f60300aa mov x22, x0
0x1003cef28: 1fdc0c71 cmp w0, #0x337
0x1003cef2c: 61f7ff54 b.ne #0x1003cee18
0x1003cef30: e13e0012 and w1, w23, #0xffff
0x1003cef34: e26b0091 add x2, sp, #0x1a
0x1003cef38: e00313aa mov x0, x19
0x1003cef3c: ff010094 bl #0x1003cf738
0x1003cef40: f7374079 ldrh w23, [sp, #0x1a]
0x1003cef44: 8dffff17 b #0x1003ced78
0x1003cef48: e1334079 ldrh w1, [sp, #0x18]
0x1003cef4c: 023d0012 and w2, w8, #0xffff
0x1003cef50: e00313aa mov x0, x19
0x1003cef54: db020094 bl #0x1003cfac0
0x1003cef58: e00313aa mov x0, x19
0x1003cef5c: e1008052 mov w1, #7
0x1003cef60: e20314aa mov x2, x20
0x1003cef64: de000094 bl #0x1003cf2dc
0x1003cef68: e0830091 add x0, sp, #0x20
0x1003cef6c: 5a1cfd97 bl #0x1003160d4
0x1003cef70: e0c30091 add x0, sp, #0x30
0x1003cef74: 581cfd97 bl #0x1003160d4
0x1003cef78: 00008052 mov w0, #0
0x1003cef7c: c0ffff17 b #0x1003cee7c
0x1003cef80: 403300d0 adrp x0, #0x100a38000
0x1003cef84: 003c2a91 add x0, x0, #0xa8f
0x1003cef88: 423300d0 adrp x2, #0x100a38000
0x1003cef8c: 42c83191 add x2, x2, #0xc72
0x1003cef90: 61ab8052 mov w1, #0x55b
0x1003cef94: b8fcf497 bl #0x10010e274

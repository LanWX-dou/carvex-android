; bluetoothd 0x1005fbae8..0x1005fbd8c; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1005fbae8: 7f2303d5 pacibsp 
0x1005fbaec: ff0302d1 sub sp, sp, #0x80
0x1005fbaf0: f65705a9 stp x22, x21, [sp, #0x50]
0x1005fbaf4: f44f06a9 stp x20, x19, [sp, #0x60]
0x1005fbaf8: fd7b07a9 stp x29, x30, [sp, #0x70]
0x1005fbafc: fdc30191 add x29, sp, #0x70
0x1005fbb00: f30302aa mov x19, x2
0x1005fbb04: f40301aa mov x20, x1
0x1005fbb08: f50300aa mov x21, x0
0x1005fbb0c: bf831df8 stur xzr, [x29, #-0x28]
0x1005fbb10: bf731d38 sturb wzr, [x29, #-0x29]
0x1005fbb14: ff7f03a9 stp xzr, xzr, [sp, #0x30]
0x1005fbb18: e0c30091 add x0, sp, #0x30
0x1005fbb1c: a1a20891 add x1, x21, #0x228
0x1005fbb20: f62ce897 bl #0x100006ef8
0x1005fbb24: a0a20991 add x0, x21, #0x268
0x1005fbb28: 172de897 bl #0x100006f84
0x1005fbb2c: e00400b4 cbz x0, #0x1005fbbc8
0x1005fbb30: a0a20991 add x0, x21, #0x268
0x1005fbb34: 6a55e897 bl #0x1000110dc
0x1005fbb38: a2a700d1 sub x2, x29, #0x29
0x1005fbb3c: a3a300d1 sub x3, x29, #0x28
0x1005fbb40: e11f8052 mov w1, #0xff
0x1005fbb44: 36a6f497 bl #0x10032541c
0x1005fbb48: 20080035 cbnz w0, #0x1005fbc4c
0x1005fbb4c: ab835df8 ldur x11, [x29, #-0x28]
0x1005fbb50: eb0700b4 cbz x11, #0x1005fbc4c
0x1005fbb54: a8735d38 ldurb w8, [x29, #-0x29]
0x1005fbb58: a8070034 cbz w8, #0x1005fbc4c
0x1005fbb5c: 69014039 ldrb w9, [x11]
0x1005fbb60: c9000034 cbz w9, #0x1005fbb78
0x1005fbb64: 3f310171 cmp w9, #0x4c
0x1005fbb68: 80000054 b.eq #0x1005fbb78
0x1005fbb6c: 6a054039 ldrb w10, [x11, #1]
0x1005fbb70: 5f310171 cmp w10, #0x4c
0x1005fbb74: a10b0054 b.ne #0x1005fbce8
0x1005fbb78: 0a008052 mov w10, #0
0x1005fbb7c: 3f310171 cmp w9, #0x4c
0x1005fbb80: 29008052 mov w9, #1
0x1005fbb84: 2c05899a cinc x12, x9, ne
0x1005fbb88: 69010c8b add x9, x11, x12
0x1005fbb8c: a9831df8 stur x9, [x29, #-0x28]
0x1005fbb90: 2b014039 ldrb w11, [x9]
0x1005fbb94: 6b1d0012 and w11, w11, #0xff
0x1005fbb98: 7f050071 cmp w11, #1
0x1005fbb9c: c1070054 b.ne #0x1005fbc94
0x1005fbba0: eb030aaa mov x11, x10
0x1005fbba4: ea030baa mov x10, x11
0x1005fbba8: 2b012b8b add x11, x9, w11, uxtb
0x1005fbbac: 6c014039 ldrb w12, [x11]
0x1005fbbb0: 4b050011 add w11, w10, #1
0x1005fbbb4: 8cffff35 cbnz w12, #0x1005fbba4
0x1005fbbb8: 0b008052 mov w11, #0
0x1005fbbbc: 1f012a6b cmp w8, w10, uxtb
0x1005fbbc0: 490c0054 b.ls #0x1005fbd48
0x1005fbbc4: f4ffff17 b #0x1005fbb94
0x1005fbbc8: 883500f0 adrp x8, #0x100cae000
0x1005fbbcc: 08011191 add x8, x8, #0x440
0x1005fbbd0: 130140f9 ldr x19, [x8]
0x1005fbbd4: e00313aa mov x0, x19
0x1005fbbd8: 21008052 mov w1, #1
0x1005fbbdc: 9d3e0c94 bl #0x10090b650
0x1005fbbe0: 400b0034 cbz w0, #0x1005fbd48
0x1005fbbe4: f4030091 mov x20, sp
0x1005fbbe8: e8030091 mov x8, sp
0x1005fbbec: e00315aa mov x0, x21
0x1005fbbf0: a53bec97 bl #0x10010aa84
0x1005fbbf4: e85fc039 ldrsb w8, [sp, #0x17]
0x1005fbbf8: e90340f9 ldr x9, [sp]
0x1005fbbfc: 1f010071 cmp w8, #0
0x1005fbc00: 28b1949a csel x8, x9, x20, lt
0x1005fbc04: a91900b0 adrp x9, #0x100930000
0x1005fbc08: 209145fd ldr d0, [x9, #0xb20]
0x1005fbc0c: e02300bd str s0, [sp, #0x20]
0x1005fbc10: e84302f8 stur x8, [sp, #0x24]
0x1005fbc14: 20d0ffb0 adrp x0, #0x100000000
0x1005fbc18: 00000091 add x0, x0, #0
0x1005fbc1c: 63280090 adrp x3, #0x100b07000
0x1005fbc20: 63f43c91 add x3, x3, #0xf3d
0x1005fbc24: e4830091 add x4, sp, #0x20
0x1005fbc28: e10313aa mov x1, x19
0x1005fbc2c: 22008052 mov w2, #1
0x1005fbc30: 85018052 mov w5, #0xc
0x1005fbc34: 8f380c94 bl #0x100909e70
0x1005fbc38: e85fc039 ldrsb w8, [sp, #0x17]
0x1005fbc3c: 6808f836 tbz w8, #0x1f, #0x1005fbd48
0x1005fbc40: e00340f9 ldr x0, [sp]
0x1005fbc44: fb370c94 bl #0x100909c30
0x1005fbc48: 40000014 b #0x1005fbd48
0x1005fbc4c: 883500f0 adrp x8, #0x100cae000
0x1005fbc50: 08011191 add x8, x8, #0x440
0x1005fbc54: 130140f9 ldr x19, [x8]
0x1005fbc58: e00313aa mov x0, x19
0x1005fbc5c: 21008052 mov w1, #1
0x1005fbc60: 7c3e0c94 bl #0x10090b650
0x1005fbc64: 20070034 cbz w0, #0x1005fbd48
0x1005fbc68: ff030079 strh wzr, [sp]
0x1005fbc6c: 20d0ffb0 adrp x0, #0x100000000
0x1005fbc70: 00000091 add x0, x0, #0
0x1005fbc74: 63280090 adrp x3, #0x100b07000
0x1005fbc78: 63b03b91 add x3, x3, #0xeec
0x1005fbc7c: e4030091 mov x4, sp
0x1005fbc80: e10313aa mov x1, x19
0x1005fbc84: 22008052 mov w2, #1
0x1005fbc88: 45008052 mov w5, #2
0x1005fbc8c: 79380c94 bl #0x100909e70
0x1005fbc90: 2e000014 b #0x1005fbd48
0x1005fbc94: 7f090071 cmp w11, #2
0x1005fbc98: 81050054 b.ne #0x1005fbd48
0x1005fbc9c: 481d4092 and x8, x10, #0xff
0x1005fbca0: 08050091 add x8, x8, #1
0x1005fbca4: 28696838 ldrb w8, [x9, x8]
0x1005fbca8: 1f0d0071 cmp w8, #3
0x1005fbcac: e3040054 b.lo #0x1005fbd48
0x1005fbcb0: 4b090011 add w11, w10, #2
0x1005fbcb4: 2b012b8b add x11, x9, w11, uxtb
0x1005fbcb8: 6b014039 ldrb w11, [x11]
0x1005fbcbc: 7f090071 cmp w11, #2
0x1005fbcc0: 41040054 b.ne #0x1005fbd48
0x1005fbcc4: 4a110011 add w10, w10, #4
0x1005fbcc8: 08110051 sub w8, w8, #4
0x1005fbccc: 20012a8b add x0, x9, w10, uxtb
0x1005fbcd0: 011d0012 and w1, w8, #0xff
0x1005fbcd4: e20314aa mov x2, x20
0x1005fbcd8: e30313aa mov x3, x19
0x1005fbcdc: 8e890094 bl #0x10061e314
0x1005fbce0: f30300aa mov x19, x0
0x1005fbce4: 1a000014 b #0x1005fbd4c
0x1005fbce8: 883500f0 adrp x8, #0x100cae000
0x1005fbcec: 08011191 add x8, x8, #0x440
0x1005fbcf0: 130140f9 ldr x19, [x8]
0x1005fbcf4: e00313aa mov x0, x19
0x1005fbcf8: 21008052 mov w1, #1
0x1005fbcfc: 553e0c94 bl #0x10090b650
0x1005fbd00: 40020034 cbz w0, #0x1005fbd48
0x1005fbd04: f4030091 mov x20, sp
0x1005fbd08: e8030091 mov x8, sp
0x1005fbd0c: e00315aa mov x0, x21
0x1005fbd10: 5d3bec97 bl #0x10010aa84
0x1005fbd14: e85fc039 ldrsb w8, [sp, #0x17]
0x1005fbd18: e90340f9 ldr x9, [sp]
0x1005fbd1c: 1f010071 cmp w8, #0
0x1005fbd20: 28b1949a csel x8, x9, x20, lt
0x1005fbd24: a91900b0 adrp x9, #0x100930000
0x1005fbd28: 209145fd ldr d0, [x9, #0xb20]
0x1005fbd2c: e02300bd str s0, [sp, #0x20]
0x1005fbd30: e84302f8 stur x8, [sp, #0x24]
0x1005fbd34: 20d0ffb0 adrp x0, #0x100000000
0x1005fbd38: 00000091 add x0, x0, #0
0x1005fbd3c: 63280090 adrp x3, #0x100b07000
0x1005fbd40: 63503c91 add x3, x3, #0xf14
0x1005fbd44: b8ffff17 b #0x1005fbc24
0x1005fbd48: 13008052 mov w19, #0
0x1005fbd4c: e0c30091 add x0, sp, #0x30
0x1005fbd50: 5c2ce897 bl #0x100006ec0
0x1005fbd54: e00313aa mov x0, x19
0x1005fbd58: fd7b47a9 ldp x29, x30, [sp, #0x70]
0x1005fbd5c: f44f46a9 ldp x20, x19, [sp, #0x60]
0x1005fbd60: f65745a9 ldp x22, x21, [sp, #0x50]
0x1005fbd64: ff030291 add sp, sp, #0x80
0x1005fbd68: ff0f5fd6 retab 
0x1005fbd6c: 03000014 b #0x1005fbd78
0x1005fbd70: 02000014 b #0x1005fbd78
0x1005fbd74: 01000014 b #0x1005fbd78
0x1005fbd78: f30300aa mov x19, x0
0x1005fbd7c: e0c30091 add x0, sp, #0x30
0x1005fbd80: 502ce897 bl #0x100006ec0
0x1005fbd84: e00313aa mov x0, x19
0x1005fbd88: 7e360c94 bl #0x100909780

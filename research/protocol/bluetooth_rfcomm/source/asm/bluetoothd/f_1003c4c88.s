; bluetoothd 0x1003c4c88..0x1003c4d8c; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1003c4c88: 7f2303d5 pacibsp 
0x1003c4c8c: f657bda9 stp x22, x21, [sp, #-0x30]!
0x1003c4c90: f44f01a9 stp x20, x19, [sp, #0x10]
0x1003c4c94: fd7b02a9 stp x29, x30, [sp, #0x20]
0x1003c4c98: fd830091 add x29, sp, #0x20
0x1003c4c9c: f30300aa mov x19, x0
0x1003c4ca0: 400000b5 cbnz x0, #0x1003c4ca8
0x1003c4ca4: e5d1f497 bl #0x1000f9438
0x1003c4ca8: 68424179 ldrh w8, [x19, #0xa0]
0x1003c4cac: 68040034 cbz w8, #0x1003c4d38
0x1003c4cb0: 1ffd0371 cmp w8, #0xff
0x1003c4cb4: e91f8052 mov w9, #0xff
0x1003c4cb8: 0831891a csel w8, w8, w9, lo
0x1003c4cbc: 688a0239 strb w8, [x19, #0xa2]
0x1003c4cc0: 7f8e0239 strb wzr, [x19, #0xa3]
0x1003c4cc4: 0805080b add w8, w8, w8, lsl #1
0x1003c4cc8: 00711d53 lsl w0, w8, #3
0x1003c4ccc: c10f8ed2 mov x1, #0x707e
0x1003c4cd0: 016daff2 movk x1, #0x7b68, lsl #16
0x1003c4cd4: 0108c0f2 movk x1, #0x40, lsl #32
0x1003c4cd8: 6120e0f2 movk x1, #0x103, lsl #48
0x1003c4cdc: fc20f197 bl #0x10000d0cc
0x1003c4ce0: 603600f9 str x0, [x19, #0x68]
0x1003c4ce4: a00400b4 cbz x0, #0x1003c4d78
0x1003c4ce8: 688a4239 ldrb w8, [x19, #0xa2]
0x1003c4cec: 28020034 cbz w8, #0x1003c4d30
0x1003c4cf0: 140080d2 mov x20, #0
0x1003c4cf4: 60224079 ldrh w0, [x19, #0x10]
0x1003c4cf8: 815f9152 mov w1, #0x8afc
0x1003c4cfc: a140b372 movk w1, #0x9a05, lsl #16
0x1003c4d00: f320f197 bl #0x10000d0cc
0x1003c4d04: e80300aa mov x8, x0
0x1003c4d08: 603640f9 ldr x0, [x19, #0x68]
0x1003c4d0c: 8906148b add x9, x20, x20, lsl #1
0x1003c4d10: 0a0c098b add x10, x0, x9, lsl #3
0x1003c4d14: 480100f9 str x8, [x10]
0x1003c4d18: 5f110079 strh wzr, [x10, #8]
0x1003c4d1c: 680100b4 cbz x8, #0x1003c4d48
0x1003c4d20: 94060091 add x20, x20, #1
0x1003c4d24: 688a4239 ldrb w8, [x19, #0xa2]
0x1003c4d28: 9f0208eb cmp x20, x8
0x1003c4d2c: 43feff54 b.lo #0x1003c4cf4
0x1003c4d30: 00008052 mov w0, #0
0x1003c4d34: 03000014 b #0x1003c4d40
0x1003c4d38: 00008052 mov w0, #0
0x1003c4d3c: 7f8a0239 strb wzr, [x19, #0xa2]
0x1003c4d40: 7f3a0039 strb wzr, [x19, #0xe]
0x1003c4d44: 0e000014 b #0x1003c4d7c
0x1003c4d48: 540100b4 cbz x20, #0x1003c4d70
0x1003c4d4c: 150080d2 mov x21, #0
0x1003c4d50: 683640f9 ldr x8, [x19, #0x68]
0x1003c4d54: a906158b add x9, x21, x21, lsl #1
0x1003c4d58: 007969f8 ldr x0, [x8, x9, lsl #3]
0x1003c4d5c: d730f197 bl #0x1000110b8
0x1003c4d60: b5060091 add x21, x21, #1
0x1003c4d64: 940600f1 subs x20, x20, #1
0x1003c4d68: 41ffff54 b.ne #0x1003c4d50
0x1003c4d6c: 603640f9 ldr x0, [x19, #0x68]
0x1003c4d70: d230f197 bl #0x1000110b8
0x1003c4d74: 7f8a0239 strb wzr, [x19, #0xa2]
0x1003c4d78: 400d8052 mov w0, #0x6a
0x1003c4d7c: fd7b42a9 ldp x29, x30, [sp, #0x20]
0x1003c4d80: f44f41a9 ldp x20, x19, [sp, #0x10]
0x1003c4d84: f657c3a8 ldp x22, x21, [sp], #0x30
0x1003c4d88: ff0f5fd6 retab 

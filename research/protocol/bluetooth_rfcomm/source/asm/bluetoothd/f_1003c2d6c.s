; bluetoothd 0x1003c2d6c..0x1003c2df0; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1003c2d6c: 7f2303d5 pacibsp 
0x1003c2d70: f44fbea9 stp x20, x19, [sp, #-0x20]!
0x1003c2d74: fd7b01a9 stp x29, x30, [sp, #0x10]
0x1003c2d78: fd430091 add x29, sp, #0x10
0x1003c2d7c: 534700f0 adrp x19, #0x100cad000
0x1003c2d80: 73823691 add x19, x19, #0xda0
0x1003c2d84: 68ca40b9 ldr w8, [x19, #0xc8]
0x1003c2d88: 1f050071 cmp w8, #1
0x1003c2d8c: 40000054 b.eq #0x1003c2d94
0x1003c2d90: aad9f497 bl #0x1000f9438
0x1003c2d94: 60008052 mov w0, #3
0x1003c2d98: 8db0fe97 bl #0x10036efcc
0x1003c2d9c: 80020035 cbnz w0, #0x1003c2dec
0x1003c2da0: b44300d0 adrp x20, #0x100c38000
0x1003c2da4: 809241f9 ldr x0, [x20, #0x320]
0x1003c2da8: 600000b4 cbz x0, #0x1003c2db4
0x1003c2dac: c338f197 bl #0x1000110b8
0x1003c2db0: 9f9201f9 str xzr, [x20, #0x320]
0x1003c2db4: b44300d0 adrp x20, #0x100c38000
0x1003c2db8: 808e41f9 ldr x0, [x20, #0x318]
0x1003c2dbc: 600000b4 cbz x0, #0x1003c2dc8
0x1003c2dc0: be38f197 bl #0x1000110b8
0x1003c2dc4: 9f8e01f9 str xzr, [x20, #0x318]
0x1003c2dc8: b44300d0 adrp x20, #0x100c38000
0x1003c2dcc: 808641f9 ldr x0, [x20, #0x308]
0x1003c2dd0: 600000b4 cbz x0, #0x1003c2ddc
0x1003c2dd4: b938f197 bl #0x1000110b8
0x1003c2dd8: 9f8601f9 str xzr, [x20, #0x308]
0x1003c2ddc: 7fca00b9 str wzr, [x19, #0xc8]
0x1003c2de0: fd7b41a9 ldp x29, x30, [sp, #0x10]
0x1003c2de4: f44fc2a8 ldp x20, x19, [sp], #0x20
0x1003c2de8: ff0f5fd6 retab 
0x1003c2dec: f883f497 bl #0x1000e3dcc

; bluetoothd 0x1003c6b60..0x1003c6ba4; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1003c6b60: 3f1c0072 tst w1, #0xff
0x1003c6b64: a0010054 b.eq #0x1003c6b98
0x1003c6b68: e81f8052 mov w8, #0xff
0x1003c6b6c: 692b00d0 adrp x9, #0x100934000
0x1003c6b70: 29812691 add x9, x9, #0x9a0
0x1003c6b74: 21040051 sub w1, w1, #1
0x1003c6b78: 0a144038 ldrb w10, [x0], #1
0x1003c6b7c: 4801084a eor w8, w10, w8
0x1003c6b80: 2801288b add x8, x9, w8, uxtb
0x1003c6b84: 08014039 ldrb w8, [x8]
0x1003c6b88: 3f1c0072 tst w1, #0xff
0x1003c6b8c: 41ffff54 b.ne #0x1003c6b74
0x1003c6b90: e803282a mvn w8, w8
0x1003c6b94: 02000014 b #0x1003c6b9c
0x1003c6b98: 08008052 mov w8, #0
0x1003c6b9c: 001d0012 and w0, w8, #0xff
0x1003c6ba0: c0035fd6 ret 

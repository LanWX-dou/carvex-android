; bluetoothd 0x1003c6be4..0x1003c6c18; source SHA256 cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1; original firmware bytes
; disassembly: Capstone 5.0.7 (ARM64, little endian, skipdata); no rewriting
0x1003c6be4: e803202a mvn w8, w0
0x1003c6be8: 692b00d0 adrp x9, #0x100934000
0x1003c6bec: 29812691 add x9, x9, #0x9a0
0x1003c6bf0: 2801288b add x8, x9, w8, uxtb
0x1003c6bf4: 08014039 ldrb w8, [x8]
0x1003c6bf8: 0801014a eor w8, w8, w1
0x1003c6bfc: 2801288b add x8, x9, w8, uxtb
0x1003c6c00: 08014039 ldrb w8, [x8]
0x1003c6c04: 0801024a eor w8, w8, w2
0x1003c6c08: 1ffd0371 cmp w8, #0xff
0x1003c6c0c: e81f8052 mov w8, #0xff
0x1003c6c10: 00119f1a csel w0, w8, wzr, ne
0x1003c6c14: c0035fd6 ret 

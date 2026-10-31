; accessoryd 0x10000b3bc-0x10000b3cc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10000b3bc:	ldr	x8, [x0, #0x40]
0x10000b3c0:	ldrb	w8, [x8, #4]
0x10000b3c4:	ubfx	w0, w8, #5, #1
0x10000b3c8:	ret	

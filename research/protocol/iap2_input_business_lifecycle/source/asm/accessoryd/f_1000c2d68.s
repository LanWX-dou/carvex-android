; accessoryd 0x1000c2d68-0x1000c2d7c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000c2d68:	cbz	x0, #0x1000c2d78
0x1000c2d6c:	ldr	x0, [x0, #8]
0x1000c2d70:	cbz	x0, #0x1000c2d78
0x1000c2d74:	b	#0x100028278
0x1000c2d78:	ret	

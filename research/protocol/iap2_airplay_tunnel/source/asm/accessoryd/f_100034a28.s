; accessoryd 0x100034a28-0x100034a40; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100034a28:	cbz	x0, #0x100034a3c
0x100034a2c:	ldrh	w8, [x0, #0x1a6]
0x100034a30:	ldrh	w9, [x0, #0xc0]
0x100034a34:	cmp	w8, w9
0x100034a38:	csel	w0, w8, w9, lo
0x100034a3c:	ret	

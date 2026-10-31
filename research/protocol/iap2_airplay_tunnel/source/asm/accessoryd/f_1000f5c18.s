; accessoryd 0x1000f5c18-0x1000f5c38; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000f5c18:	adrp	x8, #0x10022b000
0x1000f5c1c:	ldr	x8, [x8, #0x438]
0x1000f5c20:	add	x9, x8, w0, uxtw #3
0x1000f5c24:	add	x8, x8, #0x98
0x1000f5c28:	cmp	w0, #0x11
0x1000f5c2c:	csel	x8, x8, x9, hi
0x1000f5c30:	ldr	x0, [x8]
0x1000f5c34:	ret	

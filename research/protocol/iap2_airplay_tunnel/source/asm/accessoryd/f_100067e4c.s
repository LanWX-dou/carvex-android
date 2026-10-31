; accessoryd 0x100067e4c-0x100067e74; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100067e4c:	ldrh	w8, [x0]
0x100067e50:	rev16	w8, w8
0x100067e54:	cmp	w8, #5
0x100067e58:	cset	w8, ne
0x100067e5c:	str	w8, [x1]
0x100067e60:	b.eq	#0x100067e6c
0x100067e64:	mov	w0, #0
0x100067e68:	ret	
0x100067e6c:	ldrb	w0, [x0, #4]
0x100067e70:	ret	

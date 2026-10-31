; accessoryd 0x1000070fc-0x10000713c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000070fc:	cbz	x0, #0x100007138
0x100007100:	ldrh	w8, [x0, #0x1a6]
0x100007104:	ldrh	w9, [x0, #0xc0]
0x100007108:	cmp	w8, w9
0x10000710c:	csel	w8, w8, w9, lo
0x100007110:	cbz	x1, #0x100007120
0x100007114:	ldr	w9, [x1, #0x28]
0x100007118:	cmp	w9, w8
0x10000711c:	csel	w8, w9, w8, lo
0x100007120:	ldrb	w9, [x0, #0xd5]
0x100007124:	cmp	w9, #2
0x100007128:	mov	w9, #-0xa
0x10000712c:	mov	w10, #-0xc
0x100007130:	csel	w9, w10, w9, eq
0x100007134:	add	w0, w9, w8
0x100007138:	ret	

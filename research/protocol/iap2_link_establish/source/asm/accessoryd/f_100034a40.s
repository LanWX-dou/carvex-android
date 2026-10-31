; accessoryd 0x100034a40-0x100034a70; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100034a40:	cbz	x0, #0x100034a6c
0x100034a44:	cbz	x1, #0x100034a50
0x100034a48:	ldr	w8, [x1, #0x28]
0x100034a4c:	b	#0x100034a54
0x100034a50:	mov	w8, #0xffff
0x100034a54:	ldrb	w9, [x0, #0xd5]
0x100034a58:	cmp	w9, #2
0x100034a5c:	mov	w9, #-0xa
0x100034a60:	mov	w10, #-0xc
0x100034a64:	csel	w9, w10, w9, eq
0x100034a68:	add	w0, w9, w8
0x100034a6c:	ret	

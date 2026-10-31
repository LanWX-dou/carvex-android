; accessoryd 0x100009c3c-0x100009cf8; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100009c3c:	cbz	x0, #0x100009cec
0x100009c40:	pacibsp	
0x100009c44:	sub	sp, sp, #0x50
0x100009c48:	stp	x20, x19, [sp, #0x30]
0x100009c4c:	stp	x29, x30, [sp, #0x40]
0x100009c50:	add	x29, sp, #0x40
0x100009c54:	mov	x19, x1
0x100009c58:	mov	x20, x0
0x100009c5c:	mov	w0, #0
0x100009c60:	cbz	x1, #0x100009cdc
0x100009c64:	ldr	x8, [x20, #0x28]
0x100009c68:	cbz	x8, #0x100009cdc
0x100009c6c:	ldr	x8, [x20, #0x18]
0x100009c70:	cbz	x8, #0x100009cf0
0x100009c74:	mov	x0, x19
0x100009c78:	bl	#0x1001a1830
0x100009c7c:	ldr	x0, [x20]
0x100009c80:	ldrb	w1, [x20, #0x20]
0x100009c84:	ldr	x2, [x20, #0x18]
0x100009c88:	mov	x8, sp
0x100009c8c:	adrp	x16, #0x10022b000
0x100009c90:	ldr	x16, [x16, #0xb78]
0x100009c94:	mov	x17, x8
0x100009c98:	movk	x17, #0x6ae1, lsl #48
0x100009c9c:	pacda	x16, x17
0x100009ca0:	str	x16, [sp]
0x100009ca4:	adrp	x9, #0x1001b3000
0x100009ca8:	ldr	d0, [x9, #0x118]
0x100009cac:	str	d0, [sp, #8]
0x100009cb0:	add	x8, x8, #0x10
0x100009cb4:	adrp	x9, #0x100219000
0x100009cb8:	add	x9, x9, #0x7c0
0x100009cbc:	adrp	x16, #0x100009000
0x100009cc0:	add	x16, x16, #0xcf8
0x100009cc4:	pacia	x16, x8
0x100009cc8:	stp	x16, x9, [sp, #0x10]
0x100009ccc:	stp	x20, x19, [sp, #0x20]
0x100009cd0:	mov	x3, sp
0x100009cd4:	bl	#0x1000ca3a0
0x100009cd8:	mov	w0, #1
0x100009cdc:	ldp	x29, x30, [sp, #0x40]
0x100009ce0:	ldp	x20, x19, [sp, #0x30]
0x100009ce4:	add	sp, sp, #0x50
0x100009ce8:	autibsp	
0x100009cec:	ret	
0x100009cf0:	mov	w0, #0
0x100009cf4:	b	#0x100009cdc

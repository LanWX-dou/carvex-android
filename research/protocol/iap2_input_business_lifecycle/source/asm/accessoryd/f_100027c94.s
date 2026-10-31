; accessoryd 0x100027c94-0x100027d7c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100027c94:	pacibsp	
0x100027c98:	sub	sp, sp, #0x70
0x100027c9c:	stp	x20, x19, [sp, #0x50]
0x100027ca0:	stp	x29, x30, [sp, #0x60]
0x100027ca4:	add	x29, sp, #0x60
0x100027ca8:	add	x8, sp, #0x30
0x100027cac:	stp	xzr, x8, [sp, #0x30]
0x100027cb0:	adrp	x8, #0x1001b3000
0x100027cb4:	ldr	d0, [x8, #0x120]
0x100027cb8:	str	d0, [sp, #0x40]
0x100027cbc:	mov	w20, #1
0x100027cc0:	strb	w20, [sp, #0x48]
0x100027cc4:	cbz	x0, #0x100027d44
0x100027cc8:	mov	x19, x0
0x100027ccc:	bl	#0x1001a1830
0x100027cd0:	mov	x0, #0
0x100027cd4:	mov	x1, #0
0x100027cd8:	bl	#0x1001a2130
0x100027cdc:	bl	#0x1001a2490
0x100027ce0:	mov	x20, x0
0x100027ce4:	mov	x8, sp
0x100027ce8:	adrp	x16, #0x10022b000
0x100027cec:	ldr	x16, [x16, #0xb78]
0x100027cf0:	mov	x17, x8
0x100027cf4:	movk	x17, #0x6ae1, lsl #48
0x100027cf8:	pacda	x16, x17
0x100027cfc:	str	x16, [sp]
0x100027d00:	adrp	x9, #0x1001b3000
0x100027d04:	ldr	d0, [x9, #0x78]
0x100027d08:	str	d0, [sp, #8]
0x100027d0c:	add	x8, x8, #0x10
0x100027d10:	adrp	x16, #0x100027000
0x100027d14:	add	x16, x16, #0xd7c
0x100027d18:	pacia	x16, x8
0x100027d1c:	adrp	x8, #0x100218000
0x100027d20:	add	x8, x8, #0x4b0
0x100027d24:	stp	x16, x8, [sp, #0x10]
0x100027d28:	add	x8, sp, #0x30
0x100027d2c:	stp	x8, x19, [sp, #0x20]
0x100027d30:	mov	x1, sp
0x100027d34:	bl	#0x1001a2120
0x100027d38:	bl	#0x1001a2580
0x100027d3c:	ldr	x8, [sp, #0x38]
0x100027d40:	ldrb	w20, [x8, #0x18]
0x100027d44:	add	x0, sp, #0x30
0x100027d48:	mov	w1, #8
0x100027d4c:	bl	#0x1001a1f10
0x100027d50:	and	w0, w20, #1
0x100027d54:	ldp	x29, x30, [sp, #0x60]
0x100027d58:	ldp	x20, x19, [sp, #0x50]
0x100027d5c:	add	sp, sp, #0x70
0x100027d60:	retab	
0x100027d64:	mov	x19, x0
0x100027d68:	add	x0, sp, #0x30
0x100027d6c:	mov	w1, #8
0x100027d70:	bl	#0x1001a1f10
0x100027d74:	mov	x0, x19
0x100027d78:	bl	#0x1001a1f30

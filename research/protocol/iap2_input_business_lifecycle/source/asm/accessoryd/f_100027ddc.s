; accessoryd 0x100027ddc-0x100027ec4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100027ddc:	pacibsp	
0x100027de0:	sub	sp, sp, #0x70
0x100027de4:	stp	x20, x19, [sp, #0x50]
0x100027de8:	stp	x29, x30, [sp, #0x60]
0x100027dec:	add	x29, sp, #0x60
0x100027df0:	add	x8, sp, #0x30
0x100027df4:	stp	xzr, x8, [sp, #0x30]
0x100027df8:	adrp	x8, #0x1001b3000
0x100027dfc:	ldr	d0, [x8, #0x120]
0x100027e00:	str	d0, [sp, #0x40]
0x100027e04:	mov	w20, #1
0x100027e08:	strb	w20, [sp, #0x48]
0x100027e0c:	cbz	x0, #0x100027e8c
0x100027e10:	mov	x19, x0
0x100027e14:	bl	#0x1001a1830
0x100027e18:	mov	x0, #0
0x100027e1c:	mov	x1, #0
0x100027e20:	bl	#0x1001a2130
0x100027e24:	bl	#0x1001a2490
0x100027e28:	mov	x20, x0
0x100027e2c:	mov	x8, sp
0x100027e30:	adrp	x16, #0x10022b000
0x100027e34:	ldr	x16, [x16, #0xb78]
0x100027e38:	mov	x17, x8
0x100027e3c:	movk	x17, #0x6ae1, lsl #48
0x100027e40:	pacda	x16, x17
0x100027e44:	str	x16, [sp]
0x100027e48:	adrp	x9, #0x1001b3000
0x100027e4c:	ldr	d0, [x9, #0x78]
0x100027e50:	str	d0, [sp, #8]
0x100027e54:	add	x8, x8, #0x10
0x100027e58:	adrp	x16, #0x100027000
0x100027e5c:	add	x16, x16, #0xec4
0x100027e60:	pacia	x16, x8
0x100027e64:	adrp	x8, #0x100218000
0x100027e68:	add	x8, x8, #0x4b0
0x100027e6c:	stp	x16, x8, [sp, #0x10]
0x100027e70:	add	x8, sp, #0x30
0x100027e74:	stp	x8, x19, [sp, #0x20]
0x100027e78:	mov	x1, sp
0x100027e7c:	bl	#0x1001a2120
0x100027e80:	bl	#0x1001a2580
0x100027e84:	ldr	x8, [sp, #0x38]
0x100027e88:	ldrb	w20, [x8, #0x18]
0x100027e8c:	add	x0, sp, #0x30
0x100027e90:	mov	w1, #8
0x100027e94:	bl	#0x1001a1f10
0x100027e98:	and	w0, w20, #1
0x100027e9c:	ldp	x29, x30, [sp, #0x60]
0x100027ea0:	ldp	x20, x19, [sp, #0x50]
0x100027ea4:	add	sp, sp, #0x70
0x100027ea8:	retab	
0x100027eac:	mov	x19, x0
0x100027eb0:	add	x0, sp, #0x30
0x100027eb4:	mov	w1, #8
0x100027eb8:	bl	#0x1001a1f10
0x100027ebc:	mov	x0, x19
0x100027ec0:	bl	#0x1001a1f30

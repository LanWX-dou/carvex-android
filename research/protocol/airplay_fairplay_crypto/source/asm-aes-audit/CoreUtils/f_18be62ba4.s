; CoreUtils 0x18be62ba4-0x18be62c50; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be62ba4:	pacibsp	
0x18be62ba8:	sub	sp, sp, #0x50
0x18be62bac:	stp	x24, x23, [sp, #0x10]
0x18be62bb0:	stp	x22, x21, [sp, #0x20]
0x18be62bb4:	stp	x20, x19, [sp, #0x30]
0x18be62bb8:	stp	x29, x30, [sp, #0x40]
0x18be62bbc:	add	x29, sp, #0x40
0x18be62bc0:	mov	x19, x3
0x18be62bc4:	mov	x20, x1
0x18be62bc8:	add	x23, x1, x2
0x18be62bcc:	ands	x21, x2, #-0x10
0x18be62bd0:	str	x21, [sp, #8]
0x18be62bd4:	b.eq	#0x18be62c2c
0x18be62bd8:	mov	x22, x0
0x18be62bdc:	mov	x1, x0
0x18be62be0:	ldr	x0, [x1], #8
0x18be62be4:	bl	#0x1900eb6b0
0x18be62be8:	cbnz	w0, #0x18be62c38
0x18be62bec:	ldr	x0, [x22]
0x18be62bf0:	add	x5, sp, #8
0x18be62bf4:	mov	x1, x20
0x18be62bf8:	mov	x2, x21
0x18be62bfc:	mov	x3, x19
0x18be62c00:	mov	x4, x21
0x18be62c04:	bl	#0x1900cd770
0x18be62c08:	cbnz	w0, #0x18be62c38
0x18be62c0c:	ldr	x8, [sp, #8]
0x18be62c10:	add	x9, x20, x8
0x18be62c14:	add	x10, x19, x8
0x18be62c18:	mov	x20, x9
0x18be62c1c:	mov	x19, x10
0x18be62c20:	b	#0x18be62c2c
0x18be62c24:	ldrb	w8, [x20], #1
0x18be62c28:	strb	w8, [x19], #1
0x18be62c2c:	cmp	x20, x23
0x18be62c30:	b.ne	#0x18be62c24
0x18be62c34:	mov	w0, #0
0x18be62c38:	ldp	x29, x30, [sp, #0x40]
0x18be62c3c:	ldp	x20, x19, [sp, #0x30]
0x18be62c40:	ldp	x22, x21, [sp, #0x20]
0x18be62c44:	ldp	x24, x23, [sp, #0x10]
0x18be62c48:	add	sp, sp, #0x50
0x18be62c4c:	retab	

; CoreUtils 0x18be4da90-0x18be4db54; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be4da90:	pacibsp	
0x18be4da94:	sub	sp, sp, #0x40
0x18be4da98:	stp	x22, x21, [sp, #0x10]
0x18be4da9c:	stp	x20, x19, [sp, #0x20]
0x18be4daa0:	stp	x29, x30, [sp, #0x30]
0x18be4daa4:	add	x29, sp, #0x30
0x18be4daa8:	mov	x19, x0
0x18be4daac:	ldr	w0, [x0, #0x2134]
0x18be4dab0:	cbz	w0, #0x18be4dac8
0x18be4dab4:	ldp	x29, x30, [sp, #0x30]
0x18be4dab8:	ldp	x20, x19, [sp, #0x20]
0x18be4dabc:	ldp	x22, x21, [sp, #0x10]
0x18be4dac0:	add	sp, sp, #0x40
0x18be4dac4:	retab	
0x18be4dac8:	mov	x21, x3
0x18be4dacc:	mov	x22, x2
0x18be4dad0:	mov	x20, x1
0x18be4dad4:	mov	x0, x19
0x18be4dad8:	mov	x1, x3
0x18be4dadc:	bl	#0x18be4ceb4
0x18be4dae0:	cbz	w0, #0x18be4daf4
0x18be4dae4:	ldr	w8, [x19, #0x2134]
0x18be4dae8:	cbnz	w8, #0x18be4dab4
0x18be4daec:	str	w0, [x19, #0x2134]
0x18be4daf0:	b	#0x18be4dab4
0x18be4daf4:	cbz	x22, #0x18be4db10
0x18be4daf8:	ldr	x0, [x19, #0x2148]
0x18be4dafc:	cmp	x22, x0
0x18be4db00:	b.eq	#0x18be4db10
0x18be4db04:	mov	x1, x22
0x18be4db08:	mov	x2, x21
0x18be4db0c:	bl	#0x1900cc490
0x18be4db10:	adrp	x1, #0x18bf69000
0x18be4db14:	add	x1, x1, #0xce1
0x18be4db18:	str	x21, [sp]
0x18be4db1c:	adrp	x2, #0x18bf69000
0x18be4db20:	add	x2, x2, #0xb12
0x18be4db24:	add	x0, x19, #0x18
0x18be4db28:	bl	#0x18be4d44c
0x18be4db2c:	cbz	x20, #0x18be4db4c
0x18be4db30:	adrp	x1, #0x18bf69000
0x18be4db34:	add	x1, x1, #0xb05
0x18be4db38:	str	x20, [sp]
0x18be4db3c:	adrp	x2, #0x18bf70000
0x18be4db40:	add	x2, x2, #0x51e
0x18be4db44:	add	x0, x19, #0x18
0x18be4db48:	bl	#0x18be4d44c
0x18be4db4c:	mov	w0, #0
0x18be4db50:	b	#0x18be4dab4

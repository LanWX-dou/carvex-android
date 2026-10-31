; CoreUtils 0x18be62b48-0x18be62ba4; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be62b48:	pacibsp	
0x18be62b4c:	stp	x20, x19, [sp, #-0x20]!
0x18be62b50:	stp	x29, x30, [sp, #0x10]
0x18be62b54:	add	x29, sp, #0x10
0x18be62b58:	mov	x19, x2
0x18be62b5c:	mov	x8, x1
0x18be62b60:	mov	x20, x0
0x18be62b64:	str	xzr, [x0]
0x18be62b68:	cmp	w3, #0
0x18be62b6c:	cset	w0, eq
0x18be62b70:	mov	w1, #0
0x18be62b74:	mov	w2, #0
0x18be62b78:	mov	x3, x8
0x18be62b7c:	mov	w4, #0x10
0x18be62b80:	mov	x5, #0
0x18be62b84:	mov	x6, x20
0x18be62b88:	bl	#0x1900cd730
0x18be62b8c:	cbnz	w0, #0x18be62b98
0x18be62b90:	ldr	q0, [x19]
0x18be62b94:	stur	q0, [x20, #8]
0x18be62b98:	ldp	x29, x30, [sp, #0x10]
0x18be62b9c:	ldp	x20, x19, [sp], #0x20
0x18be62ba0:	retab	

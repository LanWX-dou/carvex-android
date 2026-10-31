; CoreUtils 0x18be628bc-0x18be62914; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be628bc:	pacibsp	
0x18be628c0:	stp	x20, x19, [sp, #-0x20]!
0x18be628c4:	stp	x29, x30, [sp, #0x10]
0x18be628c8:	add	x29, sp, #0x10
0x18be628cc:	mov	x20, x2
0x18be628d0:	mov	x3, x1
0x18be628d4:	mov	x19, x0
0x18be628d8:	str	xzr, [x0]
0x18be628dc:	mov	w0, #0
0x18be628e0:	mov	w1, #0
0x18be628e4:	mov	w2, #2
0x18be628e8:	mov	w4, #0x10
0x18be628ec:	mov	x5, #0
0x18be628f0:	mov	x6, x19
0x18be628f4:	bl	#0x1900cd730
0x18be628f8:	cbnz	w0, #0x18be62908
0x18be628fc:	ldr	q0, [x20]
0x18be62900:	stur	q0, [x19, #8]
0x18be62904:	str	xzr, [x19, #0x28]
0x18be62908:	ldp	x29, x30, [sp, #0x10]
0x18be6290c:	ldp	x20, x19, [sp], #0x20
0x18be62910:	retab	

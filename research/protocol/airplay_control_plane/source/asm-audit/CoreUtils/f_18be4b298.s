; CoreUtils 0x18be4b298-0x18be4b330; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be4b298:	pacibsp	
0x18be4b29c:	stp	x22, x21, [sp, #-0x30]!
0x18be4b2a0:	stp	x20, x19, [sp, #0x10]
0x18be4b2a4:	stp	x29, x30, [sp, #0x20]
0x18be4b2a8:	add	x29, sp, #0x20
0x18be4b2ac:	mov	x20, x3
0x18be4b2b0:	mov	x21, x2
0x18be4b2b4:	mov	x22, x1
0x18be4b2b8:	mov	x19, x0
0x18be4b2bc:	ldrb	w8, [x0, #0xf8]
0x18be4b2c0:	cbnz	w8, #0x18be4b2f0
0x18be4b2c4:	ldr	x8, [x19, #0xe8]
0x18be4b2c8:	ands	x8, x8, #0xf
0x18be4b2cc:	b.eq	#0x18be4b2e8
0x18be4b2d0:	mov	w9, #0x10
0x18be4b2d4:	sub	x2, x9, x8
0x18be4b2d8:	adrp	x1, #0x18bf71000
0x18be4b2dc:	add	x1, x1, #0x1b4
0x18be4b2e0:	add	x0, x19, #0x88
0x18be4b2e4:	bl	#0x18be48df8
0x18be4b2e8:	mov	w8, #1
0x18be4b2ec:	strb	w8, [x19, #0xf8]
0x18be4b2f0:	add	x0, x19, #0x88
0x18be4b2f4:	mov	x1, x22
0x18be4b2f8:	mov	x2, x21
0x18be4b2fc:	bl	#0x18be48df8
0x18be4b300:	mov	x0, x19
0x18be4b304:	mov	x1, x22
0x18be4b308:	mov	x2, x21
0x18be4b30c:	mov	x3, x20
0x18be4b310:	bl	#0x18be4a6e0
0x18be4b314:	ldr	x8, [x19, #0xf0]
0x18be4b318:	add	x8, x8, x0
0x18be4b31c:	str	x8, [x19, #0xf0]
0x18be4b320:	ldp	x29, x30, [sp, #0x20]
0x18be4b324:	ldp	x20, x19, [sp, #0x10]
0x18be4b328:	ldp	x22, x21, [sp], #0x30
0x18be4b32c:	retab	

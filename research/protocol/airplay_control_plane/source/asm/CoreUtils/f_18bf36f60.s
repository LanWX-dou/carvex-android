; CoreUtils 0x18bf36f60-0x18bf36fd0; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18bf36f60:	pacibsp	
0x18bf36f64:	stp	x20, x19, [sp, #-0x20]!
0x18bf36f68:	stp	x29, x30, [sp, #0x10]
0x18bf36f6c:	add	x29, sp, #0x10
0x18bf36f70:	mov	x19, x0
0x18bf36f74:	ldr	x0, [x0]
0x18bf36f78:	cbz	x0, #0x18bf36fb8
0x18bf36f7c:	lsr	x8, x2, #0x1f
0x18bf36f80:	cbnz	x8, #0x18bf36fc0
0x18bf36f84:	ldr	x8, [x0, #0x60]
0x18bf36f88:	ldr	x8, [x8, #0x40]
0x18bf36f8c:	blraaz	x8
0x18bf36f90:	cbnz	w0, #0x18bf36fc8
0x18bf36f94:	mov	w20, #0
0x18bf36f98:	ldr	x0, [x19]
0x18bf36f9c:	cbz	x0, #0x18bf36fa8
0x18bf36fa0:	bl	#0x18bf09448
0x18bf36fa4:	str	xzr, [x19]
0x18bf36fa8:	mov	x0, x20
0x18bf36fac:	ldp	x29, x30, [sp, #0x10]
0x18bf36fb0:	ldp	x20, x19, [sp], #0x20
0x18bf36fb4:	retab	
0x18bf36fb8:	mov	w20, #-0x1a59
0x18bf36fbc:	b	#0x18bf36fa8
0x18bf36fc0:	mov	w20, #-0x1a57
0x18bf36fc4:	b	#0x18bf36fa0
0x18bf36fc8:	mov	w20, #-0x1a62
0x18bf36fcc:	b	#0x18bf36f98

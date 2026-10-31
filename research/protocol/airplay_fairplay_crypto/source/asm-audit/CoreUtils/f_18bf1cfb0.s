; CoreUtils 0x18bf1cfb0-0x18bf1d008; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18bf1cfb0:	tbnz	w1, #0x1f, #0x18bf1d000
0x18bf1cfb4:	pacibsp	
0x18bf1cfb8:	sub	sp, sp, #0x30
0x18bf1cfbc:	stp	x20, x19, [sp, #0x10]
0x18bf1cfc0:	stp	x29, x30, [sp, #0x20]
0x18bf1cfc4:	add	x29, sp, #0x20
0x18bf1cfc8:	mov	x20, x1
0x18bf1cfcc:	mov	x19, x0
0x18bf1cfd0:	str	xzr, [sp, #8]
0x18bf1cfd4:	add	x0, sp, #8
0x18bf1cfd8:	bl	#0x18bf1c660
0x18bf1cfdc:	cbnz	w0, #0x18bf1cfec
0x18bf1cfe0:	ldr	x8, [sp, #8]
0x18bf1cfe4:	str	w20, [x8, #4]
0x18bf1cfe8:	str	x8, [x19]
0x18bf1cfec:	ldp	x29, x30, [sp, #0x20]
0x18bf1cff0:	ldp	x20, x19, [sp, #0x10]
0x18bf1cff4:	add	sp, sp, #0x30
0x18bf1cff8:	autibsp	
0x18bf1cffc:	ret	
0x18bf1d000:	mov	w0, #-0x1a31
0x18bf1d004:	ret	

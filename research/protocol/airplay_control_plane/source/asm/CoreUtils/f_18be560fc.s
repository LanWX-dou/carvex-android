; CoreUtils 0x18be560fc-0x18be56150; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be560fc:	mov	w8, #-0x1a31
0x18be56100:	cmp	x2, #0xc
0x18be56104:	b.ne	#0x18be56148
0x18be56108:	pacibsp	
0x18be5610c:	sub	sp, sp, #0x20
0x18be56110:	stp	x29, x30, [sp, #0x10]
0x18be56114:	add	x29, sp, #0x10
0x18be56118:	ldr	x9, [x29, #0x18]
0x18be5611c:	cmp	x9, #0x10
0x18be56120:	b.ne	#0x18be5613c
0x18be56124:	ldr	x8, [x29, #0x10]
0x18be56128:	str	x8, [sp]
0x18be5612c:	add	x0, x0, #0x18
0x18be56130:	mov	w2, #0xc
0x18be56134:	bl	#0x18be55eec
0x18be56138:	mov	w8, #0
0x18be5613c:	ldp	x29, x30, [sp, #0x10]
0x18be56140:	add	sp, sp, #0x20
0x18be56144:	autibsp	
0x18be56148:	mov	x0, x8
0x18be5614c:	ret	

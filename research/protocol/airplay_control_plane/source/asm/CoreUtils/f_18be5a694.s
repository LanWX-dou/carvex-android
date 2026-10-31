; CoreUtils 0x18be5a694-0x18be5a6c8; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be5a694:	cmp	x2, #0xc
0x18be5a698:	b.ne	#0x18be5a6c0
0x18be5a69c:	ldr	x8, [sp, #8]
0x18be5a6a0:	cmp	x8, #0x10
0x18be5a6a4:	b.ne	#0x18be5a6c0
0x18be5a6a8:	ldr	x9, [sp]
0x18be5a6ac:	mov	w8, #0x10
0x18be5a6b0:	stp	x9, x8, [sp]
0x18be5a6b4:	add	x0, x0, #0x18
0x18be5a6b8:	mov	w2, #0xc
0x18be5a6bc:	b	#0x18be578a4
0x18be5a6c0:	mov	w0, #-0x1a31
0x18be5a6c4:	ret	

; CoreUtils 0x18be7c3f8-0x18be7c420; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be7c3f8:	cmp	x3, #0x20
0x18be7c3fc:	b.ne	#0x18be7c418
0x18be7c400:	mov	x8, x0
0x18be7c404:	mov	w0, #0
0x18be7c408:	ldp	q0, q1, [x2]
0x18be7c40c:	stur	q1, [x8, #0x28]
0x18be7c410:	stur	q0, [x8, #0x18]
0x18be7c414:	ret	
0x18be7c418:	mov	w0, #-0x1a31
0x18be7c41c:	ret	

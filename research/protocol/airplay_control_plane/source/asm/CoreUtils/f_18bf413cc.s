; CoreUtils 0x18bf413cc-0x18bf41440; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18bf413cc:	cmp	x0, x1
0x18bf413d0:	b.eq	#0x18bf41428
0x18bf413d4:	b.hs	#0x18bf41430
0x18bf413d8:	sub	x8, x1, x0
0x18bf413dc:	cmp	x8, #2
0x18bf413e0:	b.lo	#0x18bf41428
0x18bf413e4:	add	x10, x0, #2
0x18bf413e8:	ldrb	w9, [x0, #1]
0x18bf413ec:	add	x8, x10, x9
0x18bf413f0:	cmp	x8, x1
0x18bf413f4:	b.hi	#0x18bf41438
0x18bf413f8:	ldrb	w11, [x0]
0x18bf413fc:	mov	x0, x8
0x18bf41400:	cmp	w11, w2
0x18bf41404:	b.ne	#0x18bf413cc
0x18bf41408:	cbz	x3, #0x18bf41410
0x18bf4140c:	str	x10, [x3]
0x18bf41410:	cbz	x4, #0x18bf41418
0x18bf41414:	str	x9, [x4]
0x18bf41418:	mov	w0, #0
0x18bf4141c:	cbz	x5, #0x18bf41424
0x18bf41420:	str	x8, [x5]
0x18bf41424:	ret	
0x18bf41428:	mov	w0, #-0x1a47
0x18bf4142c:	ret	
0x18bf41430:	mov	w0, #-0x1a31
0x18bf41434:	ret	
0x18bf41438:	mov	w0, #-0x1a5e
0x18bf4143c:	ret	

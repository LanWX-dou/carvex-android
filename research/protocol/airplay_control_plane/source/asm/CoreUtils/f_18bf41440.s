; CoreUtils 0x18bf41440-0x18bf414a4; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18bf41440:	cmp	x0, x1
0x18bf41444:	b.eq	#0x18bf4148c
0x18bf41448:	b.hs	#0x18bf41494
0x18bf4144c:	sub	x8, x1, x0
0x18bf41450:	cmp	x8, #2
0x18bf41454:	b.lo	#0x18bf4148c
0x18bf41458:	add	x10, x0, #2
0x18bf4145c:	ldrb	w9, [x0, #1]
0x18bf41460:	add	x8, x10, x9
0x18bf41464:	cmp	x8, x1
0x18bf41468:	b.hi	#0x18bf4149c
0x18bf4146c:	ldrb	w11, [x0]
0x18bf41470:	strb	w11, [x2]
0x18bf41474:	str	x10, [x3]
0x18bf41478:	str	x9, [x4]
0x18bf4147c:	mov	w0, #0
0x18bf41480:	cbz	x5, #0x18bf41488
0x18bf41484:	str	x8, [x5]
0x18bf41488:	ret	
0x18bf4148c:	mov	w0, #-0x1a47
0x18bf41490:	ret	
0x18bf41494:	mov	w0, #-0x1a31
0x18bf41498:	ret	
0x18bf4149c:	mov	w0, #-0x1a5e
0x18bf414a0:	ret	

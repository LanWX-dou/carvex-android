; CoreUtils 0x18bf414a4-0x18bf415f0; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18bf414a4:	pacibsp	
0x18bf414a8:	stp	x28, x27, [sp, #-0x60]!
0x18bf414ac:	stp	x26, x25, [sp, #0x10]
0x18bf414b0:	stp	x24, x23, [sp, #0x20]
0x18bf414b4:	stp	x22, x21, [sp, #0x30]
0x18bf414b8:	stp	x20, x19, [sp, #0x40]
0x18bf414bc:	stp	x29, x30, [sp, #0x50]
0x18bf414c0:	add	x29, sp, #0x50
0x18bf414c4:	mov	x19, x7
0x18bf414c8:	mov	x20, x6
0x18bf414cc:	mov	x21, x5
0x18bf414d0:	mov	x22, x3
0x18bf414d4:	mov	x23, x2
0x18bf414d8:	mov	x24, x1
0x18bf414dc:	cmp	x0, x24
0x18bf414e0:	b.eq	#0x18bf415d0
0x18bf414e4:	b.hs	#0x18bf415e0
0x18bf414e8:	sub	x8, x24, x0
0x18bf414ec:	cmp	x8, #2
0x18bf414f0:	b.lo	#0x18bf415d0
0x18bf414f4:	add	x1, x0, #2
0x18bf414f8:	ldrb	w26, [x0, #1]
0x18bf414fc:	add	x28, x1, x26
0x18bf41500:	cmp	x28, x24
0x18bf41504:	b.hi	#0x18bf415d8
0x18bf41508:	ldrb	w8, [x0]
0x18bf4150c:	mov	x0, x28
0x18bf41510:	cmp	w8, w23
0x18bf41514:	b.ne	#0x18bf414dc
0x18bf41518:	add	x27, x21, x4
0x18bf4151c:	cmp	x4, x26
0x18bf41520:	b.lo	#0x18bf415e8
0x18bf41524:	mov	x0, x21
0x18bf41528:	mov	x2, x26
0x18bf4152c:	bl	#0x1900cc480
0x18bf41530:	add	x25, x21, x26
0x18bf41534:	mov	x8, x28
0x18bf41538:	subs	x9, x24, x8
0x18bf4153c:	b.ls	#0x18bf41594
0x18bf41540:	cmp	x9, #2
0x18bf41544:	b.lo	#0x18bf41594
0x18bf41548:	add	x1, x8, #2
0x18bf4154c:	ldrb	w26, [x8, #1]
0x18bf41550:	add	x28, x1, x26
0x18bf41554:	cmp	x28, x24
0x18bf41558:	b.hi	#0x18bf41594
0x18bf4155c:	ldrb	w9, [x8]
0x18bf41560:	cmp	w9, w23
0x18bf41564:	b.ne	#0x18bf41594
0x18bf41568:	mov	x8, x28
0x18bf4156c:	cbz	w26, #0x18bf41538
0x18bf41570:	sub	x8, x27, x25
0x18bf41574:	cmp	x8, x26
0x18bf41578:	b.lo	#0x18bf415e8
0x18bf4157c:	mov	x0, x25
0x18bf41580:	mov	x2, x26
0x18bf41584:	bl	#0x1900cc480
0x18bf41588:	add	x8, x25, x26
0x18bf4158c:	mov	x25, x8
0x18bf41590:	b	#0x18bf41534
0x18bf41594:	sub	x9, x25, x21
0x18bf41598:	cmp	x9, x22
0x18bf4159c:	b.lo	#0x18bf415d8
0x18bf415a0:	cbz	x20, #0x18bf415a8
0x18bf415a4:	str	x9, [x20]
0x18bf415a8:	mov	w0, #0
0x18bf415ac:	cbz	x19, #0x18bf415b4
0x18bf415b0:	str	x8, [x19]
0x18bf415b4:	ldp	x29, x30, [sp, #0x50]
0x18bf415b8:	ldp	x20, x19, [sp, #0x40]
0x18bf415bc:	ldp	x22, x21, [sp, #0x30]
0x18bf415c0:	ldp	x24, x23, [sp, #0x20]
0x18bf415c4:	ldp	x26, x25, [sp, #0x10]
0x18bf415c8:	ldp	x28, x27, [sp], #0x60
0x18bf415cc:	retab	
0x18bf415d0:	mov	w0, #-0x1a47
0x18bf415d4:	b	#0x18bf415b4
0x18bf415d8:	mov	w0, #-0x1a5e
0x18bf415dc:	b	#0x18bf415b4
0x18bf415e0:	mov	w0, #-0x1a31
0x18bf415e4:	b	#0x18bf415b4
0x18bf415e8:	mov	w0, #-0x1a5f
0x18bf415ec:	b	#0x18bf415b4

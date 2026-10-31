; AirPlaySender 0x251aa9524-0x251aa9668; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251aa9524:	pacibsp	
0x251aa9528:	sub	sp, sp, #0x50
0x251aa952c:	stp	x24, x23, [sp, #0x10]
0x251aa9530:	stp	x22, x21, [sp, #0x20]
0x251aa9534:	stp	x20, x19, [sp, #0x30]
0x251aa9538:	stp	x29, x30, [sp, #0x40]
0x251aa953c:	add	x29, sp, #0x40
0x251aa9540:	mov	x19, x2
0x251aa9544:	mov	x20, x1
0x251aa9548:	str	xzr, [sp, #8]
0x251aa954c:	bl	#0x25810ac50
0x251aa9550:	mov	x22, x0
0x251aa9554:	ldr	x0, [x0, #0x30]
0x251aa9558:	add	x1, x22, #0x10
0x251aa955c:	mov	w2, #0x10
0x251aa9560:	bl	#0x2580f6ff0
0x251aa9564:	cbz	x0, #0x251aa9644
0x251aa9568:	mov	x21, x0
0x251aa956c:	ldr	x23, [x22, #8]
0x251aa9570:	cbz	x23, #0x251aa95e0
0x251aa9574:	ldr	x24, [x22, #0x30]
0x251aa9578:	mov	x0, x23
0x251aa957c:	bl	#0x258109150
0x251aa9580:	ldr	x16, [x0, #0x10]!
0x251aa9584:	mov	x17, x0
0x251aa9588:	movk	x17, #0x97e1, lsl #48
0x251aa958c:	autda	x16, x17
0x251aa9590:	ldr	x9, [x16, #0x18]!
0x251aa9594:	cbz	x9, #0x251aa95e8
0x251aa9598:	mov	x8, x16
0x251aa959c:	movk	x8, #0xa2e6, lsl #48
0x251aa95a0:	mov	x16, x9
0x251aa95a4:	mov	x17, x8
0x251aa95a8:	autia	x16, x17
0x251aa95ac:	mov	x17, x16
0x251aa95b0:	xpaci	x17
0x251aa95b4:	cmp	x16, x17
0x251aa95b8:	b.eq	#0x251aa95c0
0x251aa95bc:	brk	#0xc470
0x251aa95c0:	paciza	x16
0x251aa95c4:	cbz	x16, #0x251aa95e8
0x251aa95c8:	add	x3, sp, #8
0x251aa95cc:	mov	x0, x23
0x251aa95d0:	mov	x1, x21
0x251aa95d4:	mov	x2, x24
0x251aa95d8:	blraa	x9, x8
0x251aa95dc:	b	#0x251aa95e8
0x251aa95e0:	str	x21, [sp, #8]
0x251aa95e4:	mov	x21, #0
0x251aa95e8:	ldr	x0, [x22, #0x30]
0x251aa95ec:	add	x1, x22, #0x20
0x251aa95f0:	mov	w2, #0x10
0x251aa95f4:	bl	#0x2580f6ff0
0x251aa95f8:	cbz	x0, #0x251aa9654
0x251aa95fc:	mov	w22, #0
0x251aa9600:	ldr	x8, [sp, #8]
0x251aa9604:	str	x8, [x20]
0x251aa9608:	str	xzr, [sp, #8]
0x251aa960c:	str	x0, [x19]
0x251aa9610:	cbz	x21, #0x251aa961c
0x251aa9614:	mov	x0, x21
0x251aa9618:	bl	#0x2580f5830
0x251aa961c:	ldr	x0, [sp, #8]
0x251aa9620:	cbz	x0, #0x251aa9628
0x251aa9624:	bl	#0x2580f5830
0x251aa9628:	mov	x0, x22
0x251aa962c:	ldp	x29, x30, [sp, #0x40]
0x251aa9630:	ldp	x20, x19, [sp, #0x30]
0x251aa9634:	ldp	x22, x21, [sp, #0x20]
0x251aa9638:	ldp	x24, x23, [sp, #0x10]
0x251aa963c:	add	sp, sp, #0x50
0x251aa9640:	retab	
0x251aa9644:	mov	w22, #0xe7d8
0x251aa9648:	movk	w22, #0xfffe, lsl #16
0x251aa964c:	bl	#0x251b84504
0x251aa9650:	b	#0x251aa961c
0x251aa9654:	mov	w22, #0xe7d8
0x251aa9658:	movk	w22, #0xfffe, lsl #16
0x251aa965c:	bl	#0x251b844d8
0x251aa9660:	cbnz	x21, #0x251aa9614
0x251aa9664:	b	#0x251aa961c

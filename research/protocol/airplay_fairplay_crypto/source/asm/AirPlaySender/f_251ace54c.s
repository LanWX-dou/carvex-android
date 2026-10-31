; AirPlaySender 0x251ace54c-0x251ace644; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251ace54c:	pacibsp	
0x251ace550:	sub	sp, sp, #0x40
0x251ace554:	stp	x22, x21, [sp, #0x10]
0x251ace558:	stp	x20, x19, [sp, #0x20]
0x251ace55c:	stp	x29, x30, [sp, #0x30]
0x251ace560:	add	x29, sp, #0x30
0x251ace564:	str	xzr, [sp, #8]
0x251ace568:	cbz	x1, #0x251ace60c
0x251ace56c:	mov	x19, x2
0x251ace570:	mov	x21, x1
0x251ace574:	mov	x20, x0
0x251ace578:	bl	#0x251aa9b80
0x251ace57c:	mov	x2, x0
0x251ace580:	adrp	x1, #0x276127000
0x251ace584:	add	x1, x1, #0x410
0x251ace588:	add	x3, sp, #8
0x251ace58c:	mov	x0, x20
0x251ace590:	bl	#0x25810acc0
0x251ace594:	cbnz	w0, #0x251ace61c
0x251ace598:	ldr	x0, [sp, #8]
0x251ace59c:	bl	#0x25810ac50
0x251ace5a0:	str	x21, [x0, #8]
0x251ace5a4:	mov	x0, x21
0x251ace5a8:	bl	#0x2580f6a60
0x251ace5ac:	adrp	x8, #0x27097a000
0x251ace5b0:	ldr	w8, [x8, #0xf80]
0x251ace5b4:	cmp	w8, #0x1e
0x251ace5b8:	b.gt	#0x251ace5dc
0x251ace5bc:	cmn	w8, #1
0x251ace5c0:	b.ne	#0x251ace600
0x251ace5c4:	adrp	x0, #0x27097a000
0x251ace5c8:	add	x0, x0, #0xf80
0x251ace5cc:	mov	w1, #0x1e
0x251ace5d0:	movk	w1, #0x200, lsl #16
0x251ace5d4:	bl	#0x258101e40
0x251ace5d8:	cbnz	w0, #0x251ace600
0x251ace5dc:	mov	w20, #0
0x251ace5e0:	ldr	x8, [sp, #8]
0x251ace5e4:	str	x8, [x19]
0x251ace5e8:	mov	x0, x20
0x251ace5ec:	ldp	x29, x30, [sp, #0x30]
0x251ace5f0:	ldp	x20, x19, [sp, #0x20]
0x251ace5f4:	ldp	x22, x21, [sp, #0x10]
0x251ace5f8:	add	sp, sp, #0x40
0x251ace5fc:	retab	
0x251ace600:	add	x0, sp, #8
0x251ace604:	bl	#0x251ba42a8
0x251ace608:	b	#0x251ace5dc
0x251ace60c:	bl	#0x251ba42ec
0x251ace610:	mov	w20, #0xe787
0x251ace614:	movk	w20, #0xfffe, lsl #16
0x251ace618:	b	#0x251ace5e8
0x251ace61c:	mov	x20, x0
0x251ace620:	adrp	x1, #0x251c2e000
0x251ace624:	add	x1, x1, #0xb9f
0x251ace628:	mov	w2, #0x7c
0x251ace62c:	mov	w3, #0
0x251ace630:	bl	#0x258109a30
0x251ace634:	ldr	x0, [sp, #8]
0x251ace638:	cbz	x0, #0x251ace5e8
0x251ace63c:	bl	#0x2580f5830
0x251ace640:	b	#0x251ace5e8

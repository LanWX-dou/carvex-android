; accessoryd 0x1000ab604-0x1000ab6f0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000ab604:	pacibsp	
0x1000ab608:	sub	sp, sp, #0x30
0x1000ab60c:	stp	x20, x19, [sp, #0x10]
0x1000ab610:	stp	x29, x30, [sp, #0x20]
0x1000ab614:	add	x29, sp, #0x20
0x1000ab618:	str	xzr, [sp, #8]
0x1000ab61c:	cbz	x3, #0x1000ab6c0
0x1000ab620:	mov	x19, x3
0x1000ab624:	mov	x0, x3
0x1000ab628:	ldr	w8, [x0, #0x1c]!
0x1000ab62c:	cmp	w8, #0xe
0x1000ab630:	b.ne	#0x1000ab6d0
0x1000ab634:	ldr	x20, [x19, #0x38]
0x1000ab638:	cbz	x20, #0x1000ab6dc
0x1000ab63c:	ldr	x0, [x20, #8]
0x1000ab640:	add	x1, sp, #8
0x1000ab644:	bl	#0x100044ee4
0x1000ab648:	cbnz	w0, #0x1000ab6e8
0x1000ab64c:	ldr	x0, [x20, #8]
0x1000ab650:	ldr	x1, [sp, #8]
0x1000ab654:	bl	#0x1000ff070
0x1000ab658:	ldr	w8, [x19, #0x18]
0x1000ab65c:	cmp	w8, #0xd
0x1000ab660:	b.ne	#0x1000ab6a0
0x1000ab664:	adrp	x8, #0x100221000
0x1000ab668:	add	x8, x8, #0x740
0x1000ab66c:	ldr	x0, [x8]
0x1000ab670:	bl	#0x100102d48
0x1000ab674:	tbnz	w0, #0, #0x1000ab6a0
0x1000ab678:	ldr	x19, [x20, #0x28]
0x1000ab67c:	mov	x0, #0
0x1000ab680:	mov	w1, #0x5e00
0x1000ab684:	movk	w1, #0xb2d0, lsl #16
0x1000ab688:	bl	#0x1001a2270
0x1000ab68c:	mov	x1, x0
0x1000ab690:	mov	x0, x19
0x1000ab694:	mov	x2, #-1
0x1000ab698:	mov	x3, #0
0x1000ab69c:	bl	#0x1001a2240
0x1000ab6a0:	ldr	x0, [sp, #8]
0x1000ab6a4:	cbz	x0, #0x1000ab6ac
0x1000ab6a8:	bl	#0x1001a22d0
0x1000ab6ac:	mov	w0, #1
0x1000ab6b0:	ldp	x29, x30, [sp, #0x20]
0x1000ab6b4:	ldp	x20, x19, [sp, #0x10]
0x1000ab6b8:	add	sp, sp, #0x30
0x1000ab6bc:	retab	
0x1000ab6c0:	mov	x0, x2
0x1000ab6c4:	bl	#0x100165af0
0x1000ab6c8:	tbz	w0, #0, #0x1000ab6a0
0x1000ab6cc:	b	#0x1000ab6ac
0x1000ab6d0:	mov	x1, x2
0x1000ab6d4:	bl	#0x1001659c8
0x1000ab6d8:	b	#0x1000ab6a0
0x1000ab6dc:	mov	x0, x2
0x1000ab6e0:	bl	#0x100165a90
0x1000ab6e4:	b	#0x1000ab6a0
0x1000ab6e8:	bl	#0x100165a44
0x1000ab6ec:	b	#0x1000ab6a0

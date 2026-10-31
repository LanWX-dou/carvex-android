; accessoryd 0x100007728-0x1000077cc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100007728:	cbz	x1, #0x10000773c
0x10000772c:	eor	x16, x30, x30, lsl #1
0x100007730:	tbz	x16, #0x3e, #0x100007738
0x100007734:	brk	#0xc471
0x100007738:	b	#0x100008698
0x10000773c:	ldr	x10, [x0, #0x10]
0x100007740:	ldr	x8, [x10, #0x18]
0x100007744:	cbz	x8, #0x1000077c8
0x100007748:	pacibsp	
0x10000774c:	sub	sp, sp, #0x50
0x100007750:	stp	x29, x30, [sp, #0x40]
0x100007754:	add	x29, sp, #0x40
0x100007758:	ldr	x9, [x10]
0x10000775c:	ldrb	w1, [x10, #0x20]
0x100007760:	add	x10, sp, #8
0x100007764:	adrp	x16, #0x10022b000
0x100007768:	ldr	x16, [x16, #0xb78]
0x10000776c:	mov	x17, x10
0x100007770:	movk	x17, #0x6ae1, lsl #48
0x100007774:	pacda	x16, x17
0x100007778:	str	x16, [sp, #8]
0x10000777c:	adrp	x11, #0x1001b3000
0x100007780:	ldr	d0, [x11, #0x78]
0x100007784:	str	d0, [sp, #0x10]
0x100007788:	add	x10, x10, #0x10
0x10000778c:	adrp	x16, #0x100008000
0x100007790:	add	x16, x16, #0x4dc
0x100007794:	pacia	x16, x10
0x100007798:	adrp	x10, #0x10021f000
0x10000779c:	add	x10, x10, #0x550
0x1000077a0:	stp	x16, x10, [sp, #0x18]
0x1000077a4:	stp	x0, xzr, [sp, #0x28]
0x1000077a8:	str	x2, [sp, #0x38]
0x1000077ac:	add	x3, sp, #8
0x1000077b0:	mov	x0, x9
0x1000077b4:	mov	x2, x8
0x1000077b8:	bl	#0x1000ca3a0
0x1000077bc:	ldp	x29, x30, [sp, #0x40]
0x1000077c0:	add	sp, sp, #0x50
0x1000077c4:	autibsp	
0x1000077c8:	ret	

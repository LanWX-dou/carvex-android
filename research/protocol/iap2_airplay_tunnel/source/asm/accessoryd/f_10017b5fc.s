; accessoryd 0x10017b5fc-0x10017b680; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10017b5fc:	cbz	x0, #0x10017b678
0x10017b600:	pacibsp	
0x10017b604:	stp	x20, x19, [sp, #-0x20]!
0x10017b608:	stp	x29, x30, [sp, #0x10]
0x10017b60c:	add	x29, sp, #0x10
0x10017b610:	mov	x19, x0
0x10017b614:	ldr	x8, [x0]
0x10017b618:	cbnz	x8, #0x10017b670
0x10017b61c:	mov	x2, #0xd048
0x10017b620:	movk	x2, #0x7125, lsl #16
0x10017b624:	movk	x2, #0x40, lsl #32
0x10017b628:	movk	x2, #0x101, lsl #48
0x10017b62c:	mov	w0, #1
0x10017b630:	mov	w1, #0x18
0x10017b634:	bl	#0x1001a2360
0x10017b638:	str	x0, [x19]
0x10017b63c:	cbz	x0, #0x10017b670
0x10017b640:	str	wzr, [x0]
0x10017b644:	strh	wzr, [x0, #4]
0x10017b648:	strb	wzr, [x0, #6]
0x10017b64c:	str	xzr, [x0, #8]
0x10017b650:	strh	wzr, [x0, #0x10]
0x10017b654:	mov	w8, #1
0x10017b658:	strb	wzr, [x0, #0x12]
0x10017b65c:	ldp	x29, x30, [sp, #0x10]
0x10017b660:	ldp	x20, x19, [sp], #0x20
0x10017b664:	autibsp	
0x10017b668:	mov	x0, x8
0x10017b66c:	ret	
0x10017b670:	mov	w8, #0
0x10017b674:	b	#0x10017b65c
0x10017b678:	mov	w8, #0
0x10017b67c:	b	#0x10017b668

; AirPlaySupport 0x226ee961c-0x226ee9764; source SHA256 d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x226ee961c:	pacibsp	
0x226ee9620:	sub	sp, sp, #0x180
0x226ee9624:	stp	x28, x27, [sp, #0x120]
0x226ee9628:	stp	x26, x25, [sp, #0x130]
0x226ee962c:	stp	x24, x23, [sp, #0x140]
0x226ee9630:	stp	x22, x21, [sp, #0x150]
0x226ee9634:	stp	x20, x19, [sp, #0x160]
0x226ee9638:	stp	x29, x30, [sp, #0x170]
0x226ee963c:	add	x29, sp, #0x170
0x226ee9640:	mov	x19, x7
0x226ee9644:	mov	x22, x5
0x226ee9648:	mov	x23, x4
0x226ee964c:	mov	x20, x1
0x226ee9650:	mov	x21, x0
0x226ee9654:	adrp	x8, #0x2681b4000
0x226ee9658:	ldr	x8, [x8, #0xee0]
0x226ee965c:	ldr	x8, [x8]
0x226ee9660:	stur	x8, [x29, #-0x58]
0x226ee9664:	movi	v0.2d, #0000000000000000
0x226ee9668:	stp	q0, q0, [sp, #0xb0]
0x226ee966c:	stp	q0, q0, [sp, #0x90]
0x226ee9670:	sub	x27, x29, #0x98
0x226ee9674:	stp	q0, q0, [sp, #0x70]
0x226ee9678:	stp	q0, q0, [sp, #0x50]
0x226ee967c:	stp	q0, q0, [sp, #0x30]
0x226ee9680:	stp	q0, q0, [sp, #0x10]
0x226ee9684:	str	q0, [sp]
0x226ee9688:	cbz	x6, #0x226ee96d4
0x226ee968c:	mov	x24, x6
0x226ee9690:	mov	x25, x3
0x226ee9694:	mov	x26, x2
0x226ee9698:	mov	x0, sp
0x226ee969c:	bl	#0x22818b840
0x226ee96a0:	mov	x0, sp
0x226ee96a4:	mov	x1, x26
0x226ee96a8:	mov	x2, x25
0x226ee96ac:	bl	#0x22818b850
0x226ee96b0:	mov	x0, sp
0x226ee96b4:	mov	x1, x21
0x226ee96b8:	mov	x2, x20
0x226ee96bc:	bl	#0x22818b850
0x226ee96c0:	sub	x0, x29, #0x98
0x226ee96c4:	mov	x1, sp
0x226ee96c8:	bl	#0x22818b830
0x226ee96cc:	ldr	q0, [x27]
0x226ee96d0:	str	q0, [x24]
0x226ee96d4:	cbz	x19, #0x226ee9714
0x226ee96d8:	mov	x0, sp
0x226ee96dc:	bl	#0x22818b840
0x226ee96e0:	mov	x0, sp
0x226ee96e4:	mov	x1, x23
0x226ee96e8:	mov	x2, x22
0x226ee96ec:	bl	#0x22818b850
0x226ee96f0:	mov	x0, sp
0x226ee96f4:	mov	x1, x21
0x226ee96f8:	mov	x2, x20
0x226ee96fc:	bl	#0x22818b850
0x226ee9700:	sub	x0, x29, #0x98
0x226ee9704:	mov	x1, sp
0x226ee9708:	bl	#0x22818b830
0x226ee970c:	ldr	q0, [x27]
0x226ee9710:	str	q0, [x19]
0x226ee9714:	sub	x8, x29, #0x98
0x226ee9718:	mov	x9, #-0x40
0x226ee971c:	strb	wzr, [x8], #1
0x226ee9720:	adds	x9, x9, #1
0x226ee9724:	b.lo	#0x226ee971c
0x226ee9728:	ldur	x8, [x29, #-0x58]
0x226ee972c:	adrp	x9, #0x2681b4000
0x226ee9730:	ldr	x9, [x9, #0xee0]
0x226ee9734:	ldr	x9, [x9]
0x226ee9738:	cmp	x9, x8
0x226ee973c:	b.ne	#0x226ee9760
0x226ee9740:	ldp	x29, x30, [sp, #0x170]
0x226ee9744:	ldp	x20, x19, [sp, #0x160]
0x226ee9748:	ldp	x22, x21, [sp, #0x150]
0x226ee974c:	ldp	x24, x23, [sp, #0x140]
0x226ee9750:	ldp	x26, x25, [sp, #0x130]
0x226ee9754:	ldp	x28, x27, [sp, #0x120]
0x226ee9758:	add	sp, sp, #0x180
0x226ee975c:	retab	
0x226ee9760:	bl	#0x22813e7e0

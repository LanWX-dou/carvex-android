; CoreUtils 0x18be4d5fc-0x18be4d8b0; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be4d5fc:	pacibsp	
0x18be4d600:	sub	sp, sp, #0xd0
0x18be4d604:	stp	x28, x27, [sp, #0x70]
0x18be4d608:	stp	x26, x25, [sp, #0x80]
0x18be4d60c:	stp	x24, x23, [sp, #0x90]
0x18be4d610:	stp	x22, x21, [sp, #0xa0]
0x18be4d614:	stp	x20, x19, [sp, #0xb0]
0x18be4d618:	stp	x29, x30, [sp, #0xc0]
0x18be4d61c:	add	x29, sp, #0xc0
0x18be4d620:	mov	x21, x2
0x18be4d624:	adrp	x8, #0x1e016a000
0x18be4d628:	ldr	x8, [x8, #0xf28]
0x18be4d62c:	ldr	x8, [x8]
0x18be4d630:	stur	x8, [x29, #-0x58]
0x18be4d634:	add	x9, x2, #4, lsl #12
0x18be4d638:	mov	w8, #0x4178
0x18be4d63c:	add	x20, x2, x8
0x18be4d640:	mov	w8, #0x417a
0x18be4d644:	add	x24, x2, x8
0x18be4d648:	mov	w8, #0x457a
0x18be4d64c:	add	x8, x2, x8
0x18be4d650:	stp	x9, x8, [sp, #0x28]
0x18be4d654:	stp	x0, x1, [sp, #8]
0x18be4d658:	ldr	x25, [x0]
0x18be4d65c:	ldrsw	x8, [x1]
0x18be4d660:	add	x26, x25, x8, lsl #4
0x18be4d664:	mov	w8, #0x46c0
0x18be4d668:	add	x23, x2, x8
0x18be4d66c:	ldr	x8, [x2, #0x4590]
0x18be4d670:	add	x27, sp, #0x58
0x18be4d674:	mov	w28, #1
0x18be4d678:	stp	x20, x24, [sp, #0x18]
0x18be4d67c:	ldr	x9, [x21, #0x4598]
0x18be4d680:	subs	x19, x9, x8
0x18be4d684:	b.eq	#0x18be4d6c0
0x18be4d688:	stp	x8, x19, [sp, #0x58]
0x18be4d68c:	str	x27, [sp, #0x38]
0x18be4d690:	str	w28, [sp, #0x44]
0x18be4d694:	ldr	w0, [x21]
0x18be4d698:	add	x1, sp, #0x38
0x18be4d69c:	add	x2, sp, #0x44
0x18be4d6a0:	bl	#0x18be4d8b0
0x18be4d6a4:	ldr	x8, [sp, #0x60]
0x18be4d6a8:	sub	x9, x19, x8
0x18be4d6ac:	ldr	x10, [x21, #0x4590]
0x18be4d6b0:	add	x8, x10, x9
0x18be4d6b4:	str	x8, [x21, #0x4590]
0x18be4d6b8:	cbz	w0, #0x18be4d67c
0x18be4d6bc:	b	#0x18be4d858
0x18be4d6c0:	cmp	x25, x26
0x18be4d6c4:	b.hs	#0x18be4d704
0x18be4d6c8:	mov	x22, #0
0x18be4d6cc:	mov	x9, x24
0x18be4d6d0:	mov	x8, x25
0x18be4d6d4:	ldr	x10, [sp, #0x30]
0x18be4d6d8:	sub	x11, x10, x9
0x18be4d6dc:	ldr	x10, [x8, #8]
0x18be4d6e0:	cmp	x11, x10
0x18be4d6e4:	b.lo	#0x18be4d718
0x18be4d6e8:	add	x22, x10, x22
0x18be4d6ec:	add	x11, x9, x10
0x18be4d6f0:	add	x8, x8, #0x10
0x18be4d6f4:	mov	x9, x11
0x18be4d6f8:	cmp	x8, x26
0x18be4d6fc:	b.lo	#0x18be4d6d4
0x18be4d700:	b	#0x18be4d70c
0x18be4d704:	mov	x22, #0
0x18be4d708:	mov	x8, x25
0x18be4d70c:	str	x8, [sp, #0x38]
0x18be4d710:	cbz	x22, #0x18be4d854
0x18be4d714:	b	#0x18be4d724
0x18be4d718:	str	x8, [sp, #0x38]
0x18be4d71c:	add	x22, x11, x22
0x18be4d720:	cbz	x22, #0x18be4d854
0x18be4d724:	mov	w8, #0x45a0
0x18be4d728:	add	x0, x21, x8
0x18be4d72c:	mov	w8, #0x46a0
0x18be4d730:	add	x1, x21, x8
0x18be4d734:	mov	x2, x23
0x18be4d738:	bl	#0x18be4a104
0x18be4d73c:	ldr	x8, [sp, #0x28]
0x18be4d740:	strh	w22, [x8, #0x178]
0x18be4d744:	mov	w8, #0x4628
0x18be4d748:	add	x0, x21, x8
0x18be4d74c:	mov	x1, x20
0x18be4d750:	mov	w2, #2
0x18be4d754:	bl	#0x18be48df8
0x18be4d758:	ldr	x8, [x21, #0x4688]
0x18be4d75c:	add	x8, x8, #2
0x18be4d760:	str	x8, [x21, #0x4688]
0x18be4d764:	cmp	x25, x26
0x18be4d768:	b.hs	#0x18be4d7bc
0x18be4d76c:	mov	x3, x24
0x18be4d770:	mov	w19, #0x417a
0x18be4d774:	mov	x20, x24
0x18be4d778:	ldr	x8, [sp, #0x30]
0x18be4d77c:	sub	x24, x8, x20
0x18be4d780:	ldp	x1, x2, [x25]
0x18be4d784:	mov	w8, #0x45a0
0x18be4d788:	add	x0, x21, x8
0x18be4d78c:	cmp	x24, x2
0x18be4d790:	b.lo	#0x18be4d7c4
0x18be4d794:	bl	#0x18be4d1f4
0x18be4d798:	ldr	x8, [x25, #8]
0x18be4d79c:	add	x9, x20, x8
0x18be4d7a0:	add	x19, x0, x19
0x18be4d7a4:	add	x25, x25, #0x10
0x18be4d7a8:	add	x3, x21, x19
0x18be4d7ac:	mov	x20, x9
0x18be4d7b0:	cmp	x25, x26
0x18be4d7b4:	b.lo	#0x18be4d778
0x18be4d7b8:	b	#0x18be4d7e0
0x18be4d7bc:	mov	w19, #0x417a
0x18be4d7c0:	b	#0x18be4d7e0
0x18be4d7c4:	mov	x2, x24
0x18be4d7c8:	bl	#0x18be4d1f4
0x18be4d7cc:	ldp	x10, x8, [x25]
0x18be4d7d0:	add	x9, x10, x24
0x18be4d7d4:	sub	x8, x8, x24
0x18be4d7d8:	stp	x9, x8, [x25]
0x18be4d7dc:	add	x19, x0, x19
0x18be4d7e0:	add	x1, x21, x19
0x18be4d7e4:	mov	w8, #0x45a0
0x18be4d7e8:	add	x0, x21, x8
0x18be4d7ec:	add	x2, sp, #0x48
0x18be4d7f0:	bl	#0x18be4d06c
0x18be4d7f4:	add	x9, x0, x19
0x18be4d7f8:	add	x8, x21, x9
0x18be4d7fc:	ldr	x24, [sp, #0x20]
0x18be4d800:	add	x10, x24, x22
0x18be4d804:	mov	w11, #0x457a
0x18be4d808:	cmp	x9, x11
0x18be4d80c:	ccmp	x8, x10, #0, le
0x18be4d810:	b.ne	#0x18be4d8a4
0x18be4d814:	mov	x9, #0
0x18be4d818:	ldur	q0, [sp, #0x48]
0x18be4d81c:	str	q0, [x8]
0x18be4d820:	ldrb	w10, [x23, x9]
0x18be4d824:	add	w10, w10, #1
0x18be4d828:	strb	w10, [x23, x9]
0x18be4d82c:	tbz	w10, #8, #0x18be4d83c
0x18be4d830:	cmp	x9, #7
0x18be4d834:	add	x9, x9, #1
0x18be4d838:	b.lo	#0x18be4d820
0x18be4d83c:	add	x8, x8, #0x10
0x18be4d840:	ldr	x20, [sp, #0x18]
0x18be4d844:	str	x20, [x21, #0x4590]
0x18be4d848:	str	x8, [x21, #0x4598]
0x18be4d84c:	mov	x8, x20
0x18be4d850:	b	#0x18be4d67c
0x18be4d854:	mov	w0, #0
0x18be4d858:	ldp	x8, x9, [sp, #8]
0x18be4d85c:	str	x25, [x8]
0x18be4d860:	sub	x8, x26, x25
0x18be4d864:	lsr	x8, x8, #4
0x18be4d868:	str	w8, [x9]
0x18be4d86c:	ldur	x8, [x29, #-0x58]
0x18be4d870:	adrp	x9, #0x1e016a000
0x18be4d874:	ldr	x9, [x9, #0xf28]
0x18be4d878:	ldr	x9, [x9]
0x18be4d87c:	cmp	x9, x8
0x18be4d880:	b.ne	#0x18be4d8ac
0x18be4d884:	ldp	x29, x30, [sp, #0xc0]
0x18be4d888:	ldp	x20, x19, [sp, #0xb0]
0x18be4d88c:	ldp	x22, x21, [sp, #0xa0]
0x18be4d890:	ldp	x24, x23, [sp, #0x90]
0x18be4d894:	ldp	x26, x25, [sp, #0x80]
0x18be4d898:	ldp	x28, x27, [sp, #0x70]
0x18be4d89c:	add	sp, sp, #0xd0
0x18be4d8a0:	retab	
0x18be4d8a4:	mov	w0, #-0x1a6a
0x18be4d8a8:	b	#0x18be4d858
0x18be4d8ac:	bl	#0x1900cc180

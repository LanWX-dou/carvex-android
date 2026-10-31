; AirPlaySender 0x251a6f7c0-0x251a6f9a8; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a6f7c0:	pacibsp	
0x251a6f7c4:	sub	sp, sp, #0x60
0x251a6f7c8:	stp	x26, x25, [sp, #0x10]
0x251a6f7cc:	stp	x24, x23, [sp, #0x20]
0x251a6f7d0:	stp	x22, x21, [sp, #0x30]
0x251a6f7d4:	stp	x20, x19, [sp, #0x40]
0x251a6f7d8:	stp	x29, x30, [sp, #0x50]
0x251a6f7dc:	add	x29, sp, #0x50
0x251a6f7e0:	mov	x22, x3
0x251a6f7e4:	mov	x21, x2
0x251a6f7e8:	mov	x20, x1
0x251a6f7ec:	mov	x19, x0
0x251a6f7f0:	stp	xzr, xzr, [sp]
0x251a6f7f4:	ldr	x0, [x0, #0x10]
0x251a6f7f8:	bl	#0x25810b430
0x251a6f7fc:	mov	x23, x19
0x251a6f800:	ldrh	w8, [x23, #0x1a]!
0x251a6f804:	ldur	x9, [x23, #6]
0x251a6f808:	ldurh	w10, [x23, #-2]
0x251a6f80c:	sub	w8, w8, w10
0x251a6f810:	cmp	x9, w8, uxth
0x251a6f814:	b.eq	#0x251a6f980
0x251a6f818:	cbz	w22, #0x251a6f98c
0x251a6f81c:	neg	w8, w22, lsl #16
0x251a6f820:	cmp	w8, #0x10, lsl #12
0x251a6f824:	b.ge	#0x251a6f994
0x251a6f828:	add	x4, sp, #8
0x251a6f82c:	mov	x0, x20
0x251a6f830:	mov	x1, #0
0x251a6f834:	mov	x2, #0
0x251a6f838:	mov	x3, #0
0x251a6f83c:	bl	#0x25810eae0
0x251a6f840:	mov	x0, #0
0x251a6f844:	ldr	x8, [x19, #0x20]
0x251a6f848:	ldrh	w9, [x19, #0x1a]
0x251a6f84c:	ldrh	w10, [x19, #0x18]
0x251a6f850:	sub	w10, w9, w10
0x251a6f854:	cmp	x8, w10, uxth
0x251a6f858:	b.eq	#0x251a6f86c
0x251a6f85c:	ldr	x10, [x19, #0x30]
0x251a6f860:	udiv	x11, x9, x8
0x251a6f864:	msub	x8, x11, x8, x9
0x251a6f868:	ldr	x0, [x10, x8, lsl #3]
0x251a6f86c:	mov	x4, sp
0x251a6f870:	mov	x1, #0
0x251a6f874:	mov	x2, #0
0x251a6f878:	mov	x3, #0
0x251a6f87c:	bl	#0x25810eae0
0x251a6f880:	ldp	x9, x8, [sp]
0x251a6f884:	cmp	x8, x9
0x251a6f888:	b.ne	#0x251a6f99c
0x251a6f88c:	ldrh	w1, [x23]
0x251a6f890:	mov	x0, x20
0x251a6f894:	bl	#0x25810e060
0x251a6f898:	adrp	x8, #0x26e7d9000
0x251a6f89c:	ldr	w8, [x8, #0x710]
0x251a6f8a0:	cmp	w8, #0xa
0x251a6f8a4:	b.gt	#0x251a6f8c8
0x251a6f8a8:	cmn	w8, #1
0x251a6f8ac:	b.ne	#0x251a6f970
0x251a6f8b0:	adrp	x0, #0x26e7d9000
0x251a6f8b4:	add	x0, x0, #0x710
0x251a6f8b8:	mov	w1, #0xa
0x251a6f8bc:	movk	w1, #0x200, lsl #16
0x251a6f8c0:	bl	#0x258101e40
0x251a6f8c4:	cbnz	w0, #0x251a6f970
0x251a6f8c8:	ldrh	w8, [x19, #0x1a]
0x251a6f8cc:	ldp	x9, x24, [x19, #0x20]
0x251a6f8d0:	udiv	x10, x8, x9
0x251a6f8d4:	msub	x25, x10, x9, x8
0x251a6f8d8:	ldr	x23, [x24, x25, lsl #3]
0x251a6f8dc:	cbz	x20, #0x251a6f8e8
0x251a6f8e0:	mov	x0, x20
0x251a6f8e4:	bl	#0x2580f6a60
0x251a6f8e8:	str	x20, [x24, x25, lsl #3]
0x251a6f8ec:	cbz	x23, #0x251a6f8f8
0x251a6f8f0:	mov	x0, x23
0x251a6f8f4:	bl	#0x2580f5830
0x251a6f8f8:	ldr	x8, [x19, #0x38]
0x251a6f8fc:	ldrh	w9, [x19, #0x1a]
0x251a6f900:	ldr	x10, [x19, #0x20]
0x251a6f904:	udiv	x11, x9, x10
0x251a6f908:	msub	x9, x11, x10, x9
0x251a6f90c:	str	w22, [x8, x9, lsl #2]
0x251a6f910:	ldr	x8, [x19, #0x48]
0x251a6f914:	add	x9, x9, x9, lsl #1
0x251a6f918:	add	x10, x8, x9, lsl #3
0x251a6f91c:	ldr	q0, [x21]
0x251a6f920:	ldr	x8, [x21, #0x10]
0x251a6f924:	str	x8, [x10, #0x10]
0x251a6f928:	str	q0, [x10]
0x251a6f92c:	ldr	x0, [x19, #0x60]
0x251a6f930:	mov	x1, x20
0x251a6f934:	bl	#0x25810e490
0x251a6f938:	mov	w20, #0
0x251a6f93c:	ldrh	w8, [x19, #0x1a]
0x251a6f940:	add	w8, w8, #1
0x251a6f944:	strh	w8, [x19, #0x1a]
0x251a6f948:	ldr	x0, [x19, #0x10]
0x251a6f94c:	bl	#0x25810b440
0x251a6f950:	mov	x0, x20
0x251a6f954:	ldp	x29, x30, [sp, #0x50]
0x251a6f958:	ldp	x20, x19, [sp, #0x40]
0x251a6f95c:	ldp	x22, x21, [sp, #0x30]
0x251a6f960:	ldp	x24, x23, [sp, #0x20]
0x251a6f964:	ldp	x26, x25, [sp, #0x10]
0x251a6f968:	add	sp, sp, #0x60
0x251a6f96c:	retab	
0x251a6f970:	mov	x0, x23
0x251a6f974:	mov	x1, x21
0x251a6f978:	bl	#0x251b68d8c
0x251a6f97c:	b	#0x251a6f8c8
0x251a6f980:	bl	#0x251b68dfc
0x251a6f984:	mov	w20, #-0x1a35
0x251a6f988:	b	#0x251a6f948
0x251a6f98c:	bl	#0x251b68de8
0x251a6f990:	b	#0x251a6f9a0
0x251a6f994:	bl	#0x251b68dd4
0x251a6f998:	b	#0x251a6f9a0
0x251a6f99c:	bl	#0x251b68d60
0x251a6f9a0:	mov	w20, #-0x1a31
0x251a6f9a4:	b	#0x251a6f948

; CoreUtils 0x18be62914-0x18be62afc; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be62914:	pacibsp	
0x18be62918:	sub	sp, sp, #0x60
0x18be6291c:	stp	x26, x25, [sp, #0x10]
0x18be62920:	stp	x24, x23, [sp, #0x20]
0x18be62924:	stp	x22, x21, [sp, #0x30]
0x18be62928:	stp	x20, x19, [sp, #0x40]
0x18be6292c:	stp	x29, x30, [sp, #0x50]
0x18be62930:	add	x29, sp, #0x50
0x18be62934:	mov	x19, x3
0x18be62938:	mov	x21, x2
0x18be6293c:	mov	x22, x1
0x18be62940:	mov	x20, x0
0x18be62944:	add	x23, x0, #0x18
0x18be62948:	ldr	x8, [x0, #0x28]
0x18be6294c:	cbz	x2, #0x18be62988
0x18be62950:	cbz	x8, #0x18be62988
0x18be62954:	ldrb	w9, [x22], #1
0x18be62958:	ldrb	w10, [x23, x8]
0x18be6295c:	add	w11, w8, #1
0x18be62960:	eor	w9, w10, w9
0x18be62964:	strb	w9, [x19], #1
0x18be62968:	and	x25, x11, #0xf
0x18be6296c:	subs	x21, x21, #1
0x18be62970:	b.eq	#0x18be6298c
0x18be62974:	and	x9, x8, #0xf
0x18be62978:	mov	x8, x25
0x18be6297c:	cmp	x9, #0xf
0x18be62980:	b.ne	#0x18be62954
0x18be62984:	b	#0x18be6298c
0x18be62988:	mov	x25, x8
0x18be6298c:	str	xzr, [sp, #8]
0x18be62990:	str	x25, [x20, #0x28]
0x18be62994:	cmp	x21, #0x10
0x18be62998:	b.lo	#0x18be62a3c
0x18be6299c:	add	x24, x20, #8
0x18be629a0:	ldr	x0, [x20]
0x18be629a4:	add	x5, sp, #8
0x18be629a8:	mov	x1, x24
0x18be629ac:	mov	w2, #0x10
0x18be629b0:	mov	x3, x23
0x18be629b4:	mov	w4, #0x10
0x18be629b8:	bl	#0x1900cd770
0x18be629bc:	cbnz	w0, #0x18be62ad8
0x18be629c0:	ldr	x8, [sp, #8]
0x18be629c4:	cmp	x8, #0x10
0x18be629c8:	b.ne	#0x18be62af4
0x18be629cc:	mov	x8, #-0xf
0x18be629d0:	mov	w9, #0x10
0x18be629d4:	sub	x9, x9, #1
0x18be629d8:	ldrb	w10, [x24, x9]
0x18be629dc:	add	w10, w10, #1
0x18be629e0:	and	w11, w10, #0xff
0x18be629e4:	strb	w10, [x24, x9]
0x18be629e8:	cmp	w11, #0
0x18be629ec:	ccmp	x8, #0, #4, eq
0x18be629f0:	add	x8, x8, #1
0x18be629f4:	b.ne	#0x18be629d4
0x18be629f8:	mov	x8, #0
0x18be629fc:	str	xzr, [sp, #8]
0x18be62a00:	mov	w9, #1
0x18be62a04:	ldrb	w10, [x22, x8]
0x18be62a08:	ldrb	w11, [x23, x8]
0x18be62a0c:	eor	w10, w11, w10
0x18be62a10:	strb	w10, [x19, x8]
0x18be62a14:	add	x8, x8, #1
0x18be62a18:	str	x9, [sp, #8]
0x18be62a1c:	add	x9, x9, #1
0x18be62a20:	cmp	x9, #0x11
0x18be62a24:	b.ne	#0x18be62a04
0x18be62a28:	add	x22, x22, #0x10
0x18be62a2c:	add	x19, x19, #0x10
0x18be62a30:	sub	x21, x21, #0x10
0x18be62a34:	cmp	x21, #0xf
0x18be62a38:	b.hi	#0x18be629a0
0x18be62a3c:	cbz	x21, #0x18be62ad4
0x18be62a40:	mov	x24, x20
0x18be62a44:	ldr	x0, [x24], #8
0x18be62a48:	add	x5, sp, #8
0x18be62a4c:	mov	x1, x24
0x18be62a50:	mov	w2, #0x10
0x18be62a54:	mov	x3, x23
0x18be62a58:	mov	w4, #0x10
0x18be62a5c:	bl	#0x1900cd770
0x18be62a60:	cbnz	w0, #0x18be62ad8
0x18be62a64:	ldr	x8, [sp, #8]
0x18be62a68:	cmp	x8, #0x10
0x18be62a6c:	b.ne	#0x18be62af4
0x18be62a70:	mov	x8, #-0xf
0x18be62a74:	mov	w9, #0x10
0x18be62a78:	sub	x9, x9, #1
0x18be62a7c:	ldrb	w10, [x24, x9]
0x18be62a80:	add	w10, w10, #1
0x18be62a84:	and	w11, w10, #0xff
0x18be62a88:	strb	w10, [x24, x9]
0x18be62a8c:	cmp	w11, #0
0x18be62a90:	ccmp	x8, #0, #4, eq
0x18be62a94:	add	x8, x8, #1
0x18be62a98:	b.ne	#0x18be62a78
0x18be62a9c:	str	xzr, [sp, #8]
0x18be62aa0:	mov	w8, #1
0x18be62aa4:	ldrb	w9, [x22], #1
0x18be62aa8:	ldrb	w10, [x23, x25]
0x18be62aac:	add	x25, x25, #1
0x18be62ab0:	eor	w9, w10, w9
0x18be62ab4:	strb	w9, [x19], #1
0x18be62ab8:	str	x8, [sp, #8]
0x18be62abc:	add	x8, x8, #1
0x18be62ac0:	subs	x21, x21, #1
0x18be62ac4:	b.ne	#0x18be62aa4
0x18be62ac8:	mov	w0, #0
0x18be62acc:	str	x25, [x20, #0x28]
0x18be62ad0:	b	#0x18be62ad8
0x18be62ad4:	mov	w0, #0
0x18be62ad8:	ldp	x29, x30, [sp, #0x50]
0x18be62adc:	ldp	x20, x19, [sp, #0x40]
0x18be62ae0:	ldp	x22, x21, [sp, #0x30]
0x18be62ae4:	ldp	x24, x23, [sp, #0x20]
0x18be62ae8:	ldp	x26, x25, [sp, #0x10]
0x18be62aec:	add	sp, sp, #0x60
0x18be62af0:	retab	
0x18be62af4:	mov	w0, #-0x1a57
0x18be62af8:	b	#0x18be62ad8

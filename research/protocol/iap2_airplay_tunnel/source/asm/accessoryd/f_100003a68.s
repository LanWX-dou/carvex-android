; accessoryd 0x100003a68-0x100003b18; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100003a68:	cbz	x5, #0x100003a98
0x100003a6c:	ldrb	w8, [x5]
0x100003a70:	ldrb	w9, [x5, #1]
0x100003a74:	orr	w8, w9, w8, lsl #8
0x100003a78:	cmp	w3, #0xc
0x100003a7c:	mov	w10, #4
0x100003a80:	csel	w10, w10, w4, eq
0x100003a84:	add	w8, w8, w10
0x100003a88:	lsr	w8, w8, #8
0x100003a8c:	strb	w8, [x5]
0x100003a90:	add	w8, w9, w10
0x100003a94:	strb	w8, [x5, #1]
0x100003a98:	ldr	x8, [x0, #0x20]
0x100003a9c:	add	x8, x8, w4, uxtw
0x100003aa0:	str	x8, [x0, #0x20]
0x100003aa4:	lsr	w8, w4, #8
0x100003aa8:	strb	w8, [x1]
0x100003aac:	strb	w4, [x1, #1]
0x100003ab0:	lsr	w8, w2, #8
0x100003ab4:	strb	w8, [x1, #2]
0x100003ab8:	strb	w2, [x1, #3]
0x100003abc:	ldr	x8, [x0, #0x18]
0x100003ac0:	cbz	x8, #0x100003adc
0x100003ac4:	ldr	w9, [x0, #0x10]
0x100003ac8:	cmp	w9, #6
0x100003acc:	b.lo	#0x100003adc
0x100003ad0:	ldrh	w9, [x8, #2]
0x100003ad4:	rev16	w9, w9
0x100003ad8:	b	#0x100003ae0
0x100003adc:	mov	w9, #0
0x100003ae0:	add	w9, w9, w4
0x100003ae4:	lsr	w9, w9, #8
0x100003ae8:	strb	w9, [x8, #2]
0x100003aec:	ldr	x8, [x0, #0x18]
0x100003af0:	cbz	x8, #0x100003b08
0x100003af4:	ldr	w9, [x0, #0x10]
0x100003af8:	cmp	w9, #6
0x100003afc:	b.lo	#0x100003b08
0x100003b00:	ldrb	w9, [x8, #3]
0x100003b04:	b	#0x100003b0c
0x100003b08:	mov	w9, #0
0x100003b0c:	add	w9, w9, w4
0x100003b10:	strb	w9, [x8, #3]
0x100003b14:	ret	

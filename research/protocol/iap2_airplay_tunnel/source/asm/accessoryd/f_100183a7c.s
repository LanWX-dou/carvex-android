; accessoryd 0x100183a7c-0x100183b28; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100183a7c:	cbz	x0, #0x100183b14
0x100183a80:	pacibsp	
0x100183a84:	sub	sp, sp, #0x30
0x100183a88:	stp	x20, x19, [sp, #0x10]
0x100183a8c:	stp	x29, x30, [sp, #0x20]
0x100183a90:	add	x29, sp, #0x20
0x100183a94:	bl	#0x100183b28
0x100183a98:	mov	x19, x0
0x100183a9c:	bl	#0x100003564
0x100183aa0:	cmp	x8, #0
0x100183aa4:	ccmp	w9, #0x1b, #8, ne
0x100183aa8:	b.ge	#0x100183ac4
0x100183aac:	adrp	x8, #0x10023e000
0x100183ab0:	ldr	x8, [x8, #0xe18]
0x100183ab4:	cmn	x8, #1
0x100183ab8:	b.ne	#0x100183b1c
0x100183abc:	bl	#0x1000034c0
0x100183ac0:	b	#0x100183ac8
0x100183ac4:	ldr	x20, [x8, #0xd0]
0x100183ac8:	mov	x0, x20
0x100183acc:	mov	w1, #1
0x100183ad0:	bl	#0x1001a2830
0x100183ad4:	cbz	w0, #0x100183b04
0x100183ad8:	adrp	x8, #0x1001b3000
0x100183adc:	ldr	d0, [x8, #0xb0]
0x100183ae0:	str	s0, [sp]
0x100183ae4:	str	w19, [sp, #4]
0x100183ae8:	bl	#0x100003474
0x100183aec:	adrp	x3, #0x100209000
0x100183af0:	add	x3, x3, #0x8b4
0x100183af4:	bl	#0x100009360
0x100183af8:	mov	w2, #1
0x100183afc:	mov	w5, #8
0x100183b00:	bl	#0x1001a1fe0
0x100183b04:	ldp	x29, x30, [sp, #0x20]
0x100183b08:	ldp	x20, x19, [sp, #0x10]
0x100183b0c:	add	sp, sp, #0x30
0x100183b10:	autibsp	
0x100183b14:	mov	w0, #0
0x100183b18:	ret	
0x100183b1c:	bl	#0x100017c1c
0x100183b20:	bl	#0x1001a2140
0x100183b24:	b	#0x100183abc

; AirPlayReceiver 0x25185b970-0x25185ba2c; source SHA256 ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x25185b970:	pacibsp	
0x25185b974:	sub	sp, sp, #0x40
0x25185b978:	stp	x20, x19, [sp, #0x20]
0x25185b97c:	stp	x29, x30, [sp, #0x30]
0x25185b980:	add	x29, sp, #0x30
0x25185b984:	bl	#0x25810ac50
0x25185b988:	stp	xzr, xzr, [sp, #8]
0x25185b98c:	str	xzr, [sp, #0x18]
0x25185b990:	ldr	x8, [x0, #0x88]
0x25185b994:	cbz	x8, #0x25185ba0c
0x25185b998:	ldr	x19, [x0, #0x80]
0x25185b99c:	cbz	x19, #0x25185ba08
0x25185b9a0:	mov	x0, x19
0x25185b9a4:	bl	#0x258109150
0x25185b9a8:	ldr	x16, [x0, #0x10]!
0x25185b9ac:	mov	x17, x0
0x25185b9b0:	movk	x17, #0x8d19, lsl #48
0x25185b9b4:	autda	x16, x17
0x25185b9b8:	ldr	x9, [x16, #8]!
0x25185b9bc:	cbz	x9, #0x25185ba24
0x25185b9c0:	mov	x8, x16
0x25185b9c4:	movk	x8, #0x386b, lsl #48
0x25185b9c8:	mov	x16, x9
0x25185b9cc:	mov	x17, x8
0x25185b9d0:	autia	x16, x17
0x25185b9d4:	mov	x17, x16
0x25185b9d8:	xpaci	x17
0x25185b9dc:	cmp	x16, x17
0x25185b9e0:	b.eq	#0x25185b9e8
0x25185b9e4:	brk	#0xc470
0x25185b9e8:	paciza	x16
0x25185b9ec:	cbz	x16, #0x25185ba08
0x25185b9f0:	add	x1, sp, #8
0x25185b9f4:	mov	x0, x19
0x25185b9f8:	blraa	x9, x8
0x25185b9fc:	ldr	w9, [sp, #0x18]
0x25185ba00:	ldr	x8, [sp, #0x10]
0x25185ba04:	b	#0x25185ba10
0x25185ba08:	mov	x8, #0
0x25185ba0c:	mov	x9, #0
0x25185ba10:	extr	x0, x9, x8, #0x20
0x25185ba14:	ldp	x29, x30, [sp, #0x30]
0x25185ba18:	ldp	x20, x19, [sp, #0x20]
0x25185ba1c:	add	sp, sp, #0x40
0x25185ba20:	retab	
0x25185ba24:	mov	x8, #0
0x25185ba28:	b	#0x25185ba10

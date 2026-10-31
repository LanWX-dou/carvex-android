; AirPlaySupport 0x226e689e0-0x226e68a88; source SHA256 d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x226e689e0:	pacibsp	
0x226e689e4:	sub	sp, sp, #0x30
0x226e689e8:	stp	x20, x19, [sp, #0x10]
0x226e689ec:	stp	x29, x30, [sp, #0x20]
0x226e689f0:	add	x29, sp, #0x20
0x226e689f4:	cbz	x1, #0x226e68a4c
0x226e689f8:	mov	x19, x1
0x226e689fc:	strh	wzr, [sp, #8]
0x226e68a00:	str	xzr, [sp]
0x226e68a04:	mov	x3, sp
0x226e68a08:	mov	x1, #0
0x226e68a0c:	mov	w2, #0xa
0x226e68a10:	bl	#0x22818be20
0x226e68a14:	mov	x20, x0
0x226e68a18:	cbnz	w0, #0x226e68a6c
0x226e68a1c:	ldrh	w8, [sp]
0x226e68a20:	rev	w8, w8
0x226e68a24:	lsr	w8, w8, #0x10
0x226e68a28:	strh	w8, [x19]
0x226e68a2c:	ldur	d0, [sp, #2]
0x226e68a30:	rev32	v0.8b, v0.8b
0x226e68a34:	stur	d0, [x19, #2]
0x226e68a38:	mov	x0, x20
0x226e68a3c:	ldp	x29, x30, [sp, #0x20]
0x226e68a40:	ldp	x20, x19, [sp, #0x10]
0x226e68a44:	add	sp, sp, #0x30
0x226e68a48:	retab	
0x226e68a4c:	adrp	x1, #0x226f5f000
0x226e68a50:	add	x1, x1, #0xf73
0x226e68a54:	mov	w0, #0
0x226e68a58:	mov	w2, #0xe7
0x226e68a5c:	mov	w3, #0
0x226e68a60:	bl	#0x226e8acd4
0x226e68a64:	mov	w20, #-0x1a31
0x226e68a68:	b	#0x226e68a38
0x226e68a6c:	adrp	x1, #0x226f5f000
0x226e68a70:	add	x1, x1, #0xf73
0x226e68a74:	mov	x0, x20
0x226e68a78:	mov	w2, #0xea
0x226e68a7c:	mov	w3, #0
0x226e68a80:	bl	#0x226e8acd4
0x226e68a84:	b	#0x226e68a38

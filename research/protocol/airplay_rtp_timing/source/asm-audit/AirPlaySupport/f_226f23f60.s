; AirPlaySupport 0x226f23f60-0x226f24010; source SHA256 d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x226f23f60:	pacibsp	
0x226f23f64:	sub	sp, sp, #0x30
0x226f23f68:	stp	x20, x19, [sp, #0x10]
0x226f23f6c:	stp	x29, x30, [sp, #0x20]
0x226f23f70:	add	x29, sp, #0x20
0x226f23f74:	mov	x20, x1
0x226f23f78:	mov	x19, x0
0x226f23f7c:	bl	#0x22818be70
0x226f23f80:	cmp	x0, #9
0x226f23f84:	b.ls	#0x226f23fd4
0x226f23f88:	ldrh	w8, [x20]
0x226f23f8c:	rev	w8, w8
0x226f23f90:	lsr	w8, w8, #0x10
0x226f23f94:	strh	w8, [sp, #6]
0x226f23f98:	ldur	d0, [x20, #2]
0x226f23f9c:	rev32	v0.8b, v0.8b
0x226f23fa0:	stur	d0, [sp, #8]
0x226f23fa4:	add	x0, sp, #6
0x226f23fa8:	mov	x1, x19
0x226f23fac:	mov	x2, #0
0x226f23fb0:	mov	w3, #0xa
0x226f23fb4:	bl	#0x22818bec0
0x226f23fb8:	mov	x19, x0
0x226f23fbc:	cbnz	w0, #0x226f23ff4
0x226f23fc0:	mov	x0, x19
0x226f23fc4:	ldp	x29, x30, [sp, #0x20]
0x226f23fc8:	ldp	x20, x19, [sp, #0x10]
0x226f23fcc:	add	sp, sp, #0x30
0x226f23fd0:	retab	
0x226f23fd4:	adrp	x1, #0x226f5f000
0x226f23fd8:	add	x1, x1, #0xf99
0x226f23fdc:	mov	w0, #0
0x226f23fe0:	mov	w2, #0xf9
0x226f23fe4:	mov	w3, #0
0x226f23fe8:	bl	#0x226e8acd4
0x226f23fec:	mov	w19, #-0x1a31
0x226f23ff0:	b	#0x226f23fc0
0x226f23ff4:	adrp	x1, #0x226f5f000
0x226f23ff8:	add	x1, x1, #0xf99
0x226f23ffc:	mov	x0, x19
0x226f24000:	mov	w2, #0x100
0x226f24004:	mov	w3, #0
0x226f24008:	bl	#0x226e8acd4
0x226f2400c:	b	#0x226f23fc0

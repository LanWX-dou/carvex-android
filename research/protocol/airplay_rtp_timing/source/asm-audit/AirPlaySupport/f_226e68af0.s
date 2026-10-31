; AirPlaySupport 0x226e68af0-0x226e68b54; source SHA256 d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x226e68af0:	pacibsp	
0x226e68af4:	stp	x20, x19, [sp, #-0x20]!
0x226e68af8:	stp	x29, x30, [sp, #0x10]
0x226e68afc:	add	x29, sp, #0x10
0x226e68b00:	mov	x19, x2
0x226e68b04:	mov	x4, x1
0x226e68b08:	mov	w1, #2
0x226e68b0c:	mov	x2, #0
0x226e68b10:	mov	x3, #0
0x226e68b14:	bl	#0x22818be80
0x226e68b18:	mov	x20, x0
0x226e68b1c:	cbnz	w0, #0x226e68b38
0x226e68b20:	mov	w8, #8
0x226e68b24:	str	x8, [x19]
0x226e68b28:	mov	x0, x20
0x226e68b2c:	ldp	x29, x30, [sp, #0x10]
0x226e68b30:	ldp	x20, x19, [sp], #0x20
0x226e68b34:	retab	
0x226e68b38:	adrp	x1, #0x226f5f000
0x226e68b3c:	add	x1, x1, #0xfbf
0x226e68b40:	mov	x0, x20
0x226e68b44:	mov	w2, #0x10c
0x226e68b48:	mov	w3, #0
0x226e68b4c:	bl	#0x226e8acd4
0x226e68b50:	b	#0x226e68b28

; AirPlaySupport 0x226f23d54-0x226f23dac; source SHA256 d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x226f23d54:	pacibsp	
0x226f23d58:	stp	x20, x19, [sp, #-0x20]!
0x226f23d5c:	stp	x29, x30, [sp, #0x10]
0x226f23d60:	add	x29, sp, #0x10
0x226f23d64:	mov	x5, x3
0x226f23d68:	add	x3, x2, #0xa
0x226f23d6c:	mov	x2, #0
0x226f23d70:	mov	w4, #0
0x226f23d74:	bl	#0x22818be50
0x226f23d78:	mov	x19, x0
0x226f23d7c:	cbnz	w0, #0x226f23d90
0x226f23d80:	mov	x0, x19
0x226f23d84:	ldp	x29, x30, [sp, #0x10]
0x226f23d88:	ldp	x20, x19, [sp], #0x20
0x226f23d8c:	retab	
0x226f23d90:	adrp	x1, #0x226f5f000
0x226f23d94:	add	x1, x1, #0xe55
0x226f23d98:	mov	x0, x19
0x226f23d9c:	mov	w2, #0x97
0x226f23da0:	mov	w3, #0
0x226f23da4:	bl	#0x226e8acd4
0x226f23da8:	b	#0x226f23d80

; AirPlaySupport 0x226e83b30-0x226e83b88; source SHA256 d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x226e83b30:	adrp	x8, #0x26d0a4000
0x226e83b34:	ldr	x8, [x8, #0x720]
0x226e83b38:	cmn	x8, #1
0x226e83b3c:	b.ne	#0x226e83b4c
0x226e83b40:	adrp	x8, #0x26d0a4000
0x226e83b44:	ldr	x0, [x8, #0x718]
0x226e83b48:	ret	
0x226e83b4c:	pacibsp	
0x226e83b50:	stp	x29, x30, [sp, #-0x10]!
0x226e83b54:	mov	x29, sp
0x226e83b58:	adrp	x0, #0x26d0a4000
0x226e83b5c:	add	x0, x0, #0x720
0x226e83b60:	adrp	x1, #0x26d0a4000
0x226e83b64:	add	x1, x1, #0x718
0x226e83b68:	adrp	x16, #0x226e83000
0x226e83b6c:	add	x16, x16, #0xb88
0x226e83b70:	paciza	x16
0x226e83b74:	mov	x2, x16
0x226e83b78:	bl	#0x228143b00
0x226e83b7c:	ldp	x29, x30, [sp], #0x10
0x226e83b80:	autibsp	
0x226e83b84:	b	#0x226e83b40

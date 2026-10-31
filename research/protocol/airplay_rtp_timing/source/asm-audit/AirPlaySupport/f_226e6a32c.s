; AirPlaySupport 0x226e6a32c-0x226e6a380; source SHA256 d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x226e6a32c:	pacibsp	
0x226e6a330:	stp	x20, x19, [sp, #-0x20]!
0x226e6a334:	stp	x29, x30, [sp, #0x10]
0x226e6a338:	add	x29, sp, #0x10
0x226e6a33c:	mov	x4, x1
0x226e6a340:	mov	w1, #0xa
0x226e6a344:	mov	x3, #0
0x226e6a348:	bl	#0x22818be80
0x226e6a34c:	mov	x19, x0
0x226e6a350:	cbnz	w0, #0x226e6a364
0x226e6a354:	mov	x0, x19
0x226e6a358:	ldp	x29, x30, [sp, #0x10]
0x226e6a35c:	ldp	x20, x19, [sp], #0x20
0x226e6a360:	retab	
0x226e6a364:	adrp	x1, #0x226f5f000
0x226e6a368:	add	x1, x1, #0xec7
0x226e6a36c:	mov	x0, x19
0x226e6a370:	mov	w2, #0xb5
0x226e6a374:	mov	w3, #0
0x226e6a378:	bl	#0x226e8acd4
0x226e6a37c:	b	#0x226e6a354

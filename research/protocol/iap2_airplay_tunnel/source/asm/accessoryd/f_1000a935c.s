; accessoryd 0x1000a935c-0x1000a93b0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000a935c:	pacibsp	
0x1000a9360:	stp	x20, x19, [sp, #-0x20]!
0x1000a9364:	stp	x29, x30, [sp, #0x10]
0x1000a9368:	add	x29, sp, #0x10
0x1000a936c:	mov	x19, x0
0x1000a9370:	ldp	x8, x2, [x0, #0x20]
0x1000a9374:	ldr	x0, [x8, #8]
0x1000a9378:	ldrb	w1, [x19, #0x30]
0x1000a937c:	bl	#0x1000ff27c
0x1000a9380:	ldr	x0, [x19, #0x28]
0x1000a9384:	cbz	x0, #0x1000a93a4
0x1000a9388:	ldp	x29, x30, [sp, #0x10]
0x1000a938c:	ldp	x20, x19, [sp], #0x20
0x1000a9390:	autibsp	
0x1000a9394:	eor	x16, x30, x30, lsl #1
0x1000a9398:	tbz	x16, #0x3e, #0x1000a93a0
0x1000a939c:	brk	#0xc471
0x1000a93a0:	b	#0x1001a1820
0x1000a93a4:	ldp	x29, x30, [sp, #0x10]
0x1000a93a8:	ldp	x20, x19, [sp], #0x20
0x1000a93ac:	retab	

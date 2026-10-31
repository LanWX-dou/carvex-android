; accessoryd 0x1000a93b0-0x1000a9414; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000a93b0:	pacibsp	
0x1000a93b4:	sub	sp, sp, #0x20
0x1000a93b8:	stp	x29, x30, [sp, #0x10]
0x1000a93bc:	add	x29, sp, #0x10
0x1000a93c0:	cbz	x0, #0x1000a93ec
0x1000a93c4:	cbz	x2, #0x1000a93fc
0x1000a93c8:	ldr	x8, [x0, #0x38]
0x1000a93cc:	ldr	x0, [x8, #8]
0x1000a93d0:	ldp	x29, x30, [sp, #0x10]
0x1000a93d4:	add	sp, sp, #0x20
0x1000a93d8:	autibsp	
0x1000a93dc:	eor	x16, x30, x30, lsl #1
0x1000a93e0:	tbz	x16, #0x3e, #0x1000a93e8
0x1000a93e4:	brk	#0xc471
0x1000a93e8:	b	#0x1000ff1d0
0x1000a93ec:	sub	x0, x29, #1
0x1000a93f0:	bl	#0x100165554
0x1000a93f4:	ldurb	w0, [x29, #-1]
0x1000a93f8:	b	#0x1000a9408
0x1000a93fc:	sub	x0, x29, #2
0x1000a9400:	bl	#0x1001655a0
0x1000a9404:	ldurb	w0, [x29, #-2]
0x1000a9408:	ldp	x29, x30, [sp, #0x10]
0x1000a940c:	add	sp, sp, #0x20
0x1000a9410:	retab	

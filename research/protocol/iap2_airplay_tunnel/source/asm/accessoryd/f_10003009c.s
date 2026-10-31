; accessoryd 0x10003009c-0x100030128; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10003009c:	pacibsp	
0x1000300a0:	stp	x20, x19, [sp, #-0x20]!
0x1000300a4:	stp	x29, x30, [sp, #0x10]
0x1000300a8:	add	x29, sp, #0x10
0x1000300ac:	cbz	x0, #0x100030120
0x1000300b0:	cbz	x1, #0x100030124
0x1000300b4:	mov	w8, #0x1d
0x1000300b8:	strb	w8, [x1]
0x1000300bc:	ldr	x19, [x0, #0x10]
0x1000300c0:	add	x8, x19, #0x19a
0x1000300c4:	add	x2, x19, #0x168
0x1000300c8:	ldrh	w9, [x19, #0x198]
0x1000300cc:	strh	w9, [x19, #0x1ca]
0x1000300d0:	ldp	q0, q1, [x2]
0x1000300d4:	stp	q0, q1, [x8]
0x1000300d8:	ldr	q0, [x2, #0x20]
0x1000300dc:	str	q0, [x8, #0x20]
0x1000300e0:	ldrb	w8, [x19, #0xd5]
0x1000300e4:	strb	w8, [x19, #0xd6]
0x1000300e8:	ldrb	w8, [x19, #0x19a]
0x1000300ec:	strb	w8, [x19, #0xd5]
0x1000300f0:	mov	x0, x19
0x1000300f4:	mov	w1, #2
0x1000300f8:	bl	#0x1000321a8
0x1000300fc:	mov	x0, x19
0x100030100:	mov	w1, #1
0x100030104:	ldp	x29, x30, [sp, #0x10]
0x100030108:	ldp	x20, x19, [sp], #0x20
0x10003010c:	autibsp	
0x100030110:	eor	x16, x30, x30, lsl #1
0x100030114:	tbz	x16, #0x3e, #0x10003011c
0x100030118:	brk	#0xc471
0x10003011c:	b	#0x100103970
0x100030120:	bl	#0x1001291d0
0x100030124:	bl	#0x1001291a8

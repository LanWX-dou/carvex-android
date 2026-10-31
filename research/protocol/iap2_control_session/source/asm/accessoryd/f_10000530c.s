; accessoryd 0x10000530c-0x1000053a4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10000530c:	pacibsp	
0x100005310:	stp	x22, x21, [sp, #-0x30]!
0x100005314:	stp	x20, x19, [sp, #0x10]
0x100005318:	stp	x29, x30, [sp, #0x20]
0x10000531c:	add	x29, sp, #0x20
0x100005320:	mov	x19, x1
0x100005324:	mov	x20, x0
0x100005328:	mov	x0, x1
0x10000532c:	bl	#0x1000053a4
0x100005330:	mov	x21, x0
0x100005334:	ldr	x0, [x20, #0x10]
0x100005338:	mov	x1, x19
0x10000533c:	bl	#0x100005738
0x100005340:	lsr	w8, w21, #8
0x100005344:	ldr	x9, [x19, #0x18]
0x100005348:	strb	w8, [x9, #2]
0x10000534c:	ldr	x8, [x19, #0x18]
0x100005350:	strb	w21, [x8, #3]
0x100005354:	ands	w8, w21, #0xffff
0x100005358:	b.eq	#0x100005394
0x10000535c:	ldr	x9, [x19, #0x18]
0x100005360:	str	x9, [x19]
0x100005364:	stp	w8, wzr, [x19, #8]
0x100005368:	strb	wzr, [x19, #0x38]
0x10000536c:	ldr	x0, [x20, #0x18]
0x100005370:	mov	x1, x19
0x100005374:	ldp	x29, x30, [sp, #0x20]
0x100005378:	ldp	x20, x19, [sp, #0x10]
0x10000537c:	ldp	x22, x21, [sp], #0x30
0x100005380:	autibsp	
0x100005384:	eor	x16, x30, x30, lsl #1
0x100005388:	tbz	x16, #0x3e, #0x100005390
0x10000538c:	brk	#0xc471
0x100005390:	b	#0x100005bd0
0x100005394:	ldp	x29, x30, [sp, #0x20]
0x100005398:	ldp	x20, x19, [sp, #0x10]
0x10000539c:	ldp	x22, x21, [sp], #0x30
0x1000053a0:	retab	

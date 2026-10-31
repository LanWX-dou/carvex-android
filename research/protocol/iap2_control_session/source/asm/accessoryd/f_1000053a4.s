; accessoryd 0x1000053a4-0x100005448; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000053a4:	pacibsp	
0x1000053a8:	stp	x20, x19, [sp, #-0x20]!
0x1000053ac:	stp	x29, x30, [sp, #0x10]
0x1000053b0:	add	x29, sp, #0x10
0x1000053b4:	mov	x19, x0
0x1000053b8:	ldp	x8, x9, [x0, #0x18]
0x1000053bc:	add	x2, x8, #6
0x1000053c0:	cmp	x9, #0
0x1000053c4:	ccmp	x9, x2, #0, ne
0x1000053c8:	b.ls	#0x1000053d8
0x1000053cc:	sub	x9, x9, x2
0x1000053d0:	cmp	x9, #4
0x1000053d4:	b.ge	#0x1000053e8
0x1000053d8:	mov	w20, #6
0x1000053dc:	cbnz	x8, #0x100005428
0x1000053e0:	mov	w20, #0
0x1000053e4:	b	#0x100005438
0x1000053e8:	ldrh	w10, [x8, #6]
0x1000053ec:	rev16	w10, w10
0x1000053f0:	mov	w20, #6
0x1000053f4:	cmp	x9, x10
0x1000053f8:	b.lo	#0x100005428
0x1000053fc:	ldrh	w8, [x2]
0x100005400:	rev	w8, w8
0x100005404:	add	w20, w20, w8, lsr #16
0x100005408:	mov	x0, x19
0x10000540c:	mov	x1, #0
0x100005410:	mov	x3, #0
0x100005414:	bl	#0x100005448
0x100005418:	mov	x2, x0
0x10000541c:	cbnz	x0, #0x1000053fc
0x100005420:	ldr	x8, [x19, #0x18]
0x100005424:	cbz	x8, #0x1000053e0
0x100005428:	lsr	w9, w20, #8
0x10000542c:	strb	w9, [x8, #2]
0x100005430:	ldr	x8, [x19, #0x18]
0x100005434:	strb	w20, [x8, #3]
0x100005438:	mov	x0, x20
0x10000543c:	ldp	x29, x30, [sp, #0x10]
0x100005440:	ldp	x20, x19, [sp], #0x20
0x100005444:	retab	

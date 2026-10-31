; CoreUtils 0x18be5021c-0x18be5032c; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be5021c:	pacibsp	
0x18be50220:	sub	sp, sp, #0x60
0x18be50224:	stp	x26, x25, [sp, #0x10]
0x18be50228:	stp	x24, x23, [sp, #0x20]
0x18be5022c:	stp	x22, x21, [sp, #0x30]
0x18be50230:	stp	x20, x19, [sp, #0x40]
0x18be50234:	stp	x29, x30, [sp, #0x50]
0x18be50238:	add	x29, sp, #0x50
0x18be5023c:	mov	x25, x0
0x18be50240:	ldr	w8, [x0, #0x60]
0x18be50244:	mov	w0, #-0x1a4f
0x18be50248:	cmp	w8, #6
0x18be5024c:	b.hi	#0x18be50308
0x18be50250:	mov	x24, x6
0x18be50254:	mov	x19, x5
0x18be50258:	mov	x21, x4
0x18be5025c:	mov	x20, x3
0x18be50260:	mov	x23, x2
0x18be50264:	mov	x22, x1
0x18be50268:	mov	w9, #1
0x18be5026c:	lsl	w9, w9, w8
0x18be50270:	tst	w9, #6
0x18be50274:	b.ne	#0x18be502c0
0x18be50278:	tst	w9, #0x18
0x18be5027c:	b.ne	#0x18be502a0
0x18be50280:	mov	w9, #1
0x18be50284:	lsl	w8, w9, w8
0x18be50288:	tst	w8, #0x60
0x18be5028c:	b.eq	#0x18be50308
0x18be50290:	ldrb	w8, [x25, #0x80]
0x18be50294:	cmp	w8, #3
0x18be50298:	b.eq	#0x18be502ac
0x18be5029c:	b	#0x18be50324
0x18be502a0:	ldrb	w8, [x25, #0x80]
0x18be502a4:	cmp	w8, #5
0x18be502a8:	b.ne	#0x18be50324
0x18be502ac:	bl	#0x1900cf870
0x18be502b0:	str	x24, [sp]
0x18be502b4:	add	x2, x25, #0x28e
0x18be502b8:	mov	w1, #0x20
0x18be502bc:	b	#0x18be502ec
0x18be502c0:	ldrb	w8, [x25, #0x80]
0x18be502c4:	cmp	w8, #7
0x18be502c8:	b.ne	#0x18be50324
0x18be502cc:	ldr	x26, [x25, #0x300]
0x18be502d0:	cbz	x26, #0x18be50324
0x18be502d4:	ldr	x25, [x25, #0x308]
0x18be502d8:	cbz	x25, #0x18be50324
0x18be502dc:	bl	#0x1900cf870
0x18be502e0:	str	x24, [sp]
0x18be502e4:	mov	x1, x25
0x18be502e8:	mov	x2, x26
0x18be502ec:	mov	x3, x23
0x18be502f0:	mov	x4, x22
0x18be502f4:	mov	x5, x21
0x18be502f8:	mov	x6, x20
0x18be502fc:	mov	x7, x19
0x18be50300:	bl	#0x1900cf190
0x18be50304:	mov	w0, #0
0x18be50308:	ldp	x29, x30, [sp, #0x50]
0x18be5030c:	ldp	x20, x19, [sp, #0x40]
0x18be50310:	ldp	x22, x21, [sp, #0x30]
0x18be50314:	ldp	x24, x23, [sp, #0x20]
0x18be50318:	ldp	x26, x25, [sp, #0x10]
0x18be5031c:	add	sp, sp, #0x60
0x18be50320:	retab	
0x18be50324:	mov	w0, #-0x1a35
0x18be50328:	b	#0x18be50308

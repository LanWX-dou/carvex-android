; accessoryd 0x100103230-0x1001033bc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100103230:	subs	w8, w1, #0xa
0x100103234:	b.lo	#0x1001033b0
0x100103238:	ldrb	w10, [x0]
0x10010323c:	strb	w10, [x2]
0x100103240:	ldrb	w9, [x0, #1]
0x100103244:	strb	w9, [x2, #1]
0x100103248:	ldrb	w9, [x0, #2]
0x10010324c:	lsl	w11, w9, #8
0x100103250:	strh	w11, [x2, #4]
0x100103254:	ldrb	w11, [x0, #3]
0x100103258:	bfi	w11, w9, #8, #0x18
0x10010325c:	strh	w11, [x2, #4]
0x100103260:	ldrb	w9, [x0, #4]
0x100103264:	lsl	w11, w9, #8
0x100103268:	strh	w11, [x2, #6]
0x10010326c:	ldrb	w11, [x0, #5]
0x100103270:	bfi	w11, w9, #8, #0x18
0x100103274:	strh	w11, [x2, #6]
0x100103278:	ldrb	w9, [x0, #6]
0x10010327c:	lsl	w11, w9, #8
0x100103280:	strh	w11, [x2, #8]
0x100103284:	ldrb	w11, [x0, #7]
0x100103288:	bfi	w11, w9, #8, #0x18
0x10010328c:	strh	w11, [x2, #8]
0x100103290:	ldrb	w9, [x0, #8]
0x100103294:	strb	w9, [x2, #2]
0x100103298:	ldrb	w9, [x0, #9]
0x10010329c:	strb	w9, [x2, #3]
0x1001032a0:	cbz	w10, #0x1001032c8
0x1001032a4:	cmp	w10, #1
0x1001032a8:	b.ne	#0x1001032d0
0x1001032ac:	mov	w9, #0xaaab
0x1001032b0:	movk	w9, #0xaaaa, lsl #16
0x1001032b4:	umull	x8, w8, w9
0x1001032b8:	lsr	x10, x8, #0x21
0x1001032bc:	strb	wzr, [x2, #0x18]
0x1001032c0:	mov	w8, #0xa
0x1001032c4:	b	#0x100103318
0x1001032c8:	mov	x8, x10
0x1001032cc:	b	#0x100103318
0x1001032d0:	ldrb	w9, [x0, #0xa]
0x1001032d4:	cmp	w9, #5
0x1001032d8:	mov	w10, #5
0x1001032dc:	csel	w8, w9, w10, lo
0x1001032e0:	strb	w8, [x2, #0x18]
0x1001032e4:	cbz	w9, #0x10010330c
0x1001032e8:	mov	x9, #0
0x1001032ec:	add	x10, x2, #0x19
0x1001032f0:	mov	x11, x8
0x1001032f4:	add	x12, x9, #0xb
0x1001032f8:	ldrb	w12, [x0, x12]
0x1001032fc:	strb	w12, [x10, x9]
0x100103300:	add	x9, x9, #1
0x100103304:	subs	x11, x11, #1
0x100103308:	b.ne	#0x1001032f4
0x10010330c:	add	x9, x8, #0xb
0x100103310:	ldrb	w10, [x0, x9]
0x100103314:	add	w8, w8, #0xc
0x100103318:	mov	x9, x2
0x10010331c:	str	xzr, [x9, #0x1e]!
0x100103320:	stur	xzr, [x9, #7]
0x100103324:	and	w11, w10, #0xff
0x100103328:	cmp	w11, #5
0x10010332c:	mov	w12, #5
0x100103330:	csel	w10, w11, w12, lo
0x100103334:	cbz	w11, #0x1001033ac
0x100103338:	and	w14, w8, #0xff
0x10010333c:	add	w11, w14, #3
0x100103340:	cmp	w11, w1
0x100103344:	b.hi	#0x1001033ac
0x100103348:	mov	x12, #0
0x10010334c:	mov	w13, #1
0x100103350:	mov	w14, w14
0x100103354:	add	x15, x14, #1
0x100103358:	ldrb	w15, [x0, x15]
0x10010335c:	add	x8, x0, w8, uxtb
0x100103360:	ldrb	w8, [x8]
0x100103364:	add	x17, x9, x12, lsl #2
0x100103368:	strb	w8, [x17]
0x10010336c:	add	x8, x14, #2
0x100103370:	ldrb	w8, [x0, x8]
0x100103374:	strb	w8, [x17, #2]
0x100103378:	and	w8, w15, #0x7f
0x10010337c:	strb	w8, [x17, #1]
0x100103380:	lsr	w8, w15, #7
0x100103384:	strb	w8, [x17, #3]
0x100103388:	cmp	x13, x10
0x10010338c:	b.hs	#0x1001033ac
0x100103390:	add	x12, x12, #1
0x100103394:	mov	x8, x11
0x100103398:	and	w14, w11, #0xff
0x10010339c:	add	w11, w14, #3
0x1001033a0:	add	x13, x13, #1
0x1001033a4:	cmp	w11, w1
0x1001033a8:	b.ls	#0x100103350
0x1001033ac:	strb	w10, [x2, #0xa]
0x1001033b0:	cmp	w1, #9
0x1001033b4:	cset	w0, hi
0x1001033b8:	ret	

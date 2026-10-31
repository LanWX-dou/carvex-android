; AirPlaySender 0x251bd0250-0x251bd0300; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251bd0250:	pacibsp	
0x251bd0254:	sub	sp, sp, #0x30
0x251bd0258:	stp	x20, x19, [sp, #0x10]
0x251bd025c:	stp	x29, x30, [sp, #0x20]
0x251bd0260:	add	x29, sp, #0x20
0x251bd0264:	mov	x20, x8
0x251bd0268:	bl	#0x25810ac50
0x251bd026c:	mov	x19, x0
0x251bd0270:	adrp	x8, #0x2680d4000
0x251bd0274:	ldr	x8, [x8, #0x6b8]
0x251bd0278:	ldr	q0, [x8]
0x251bd027c:	str	q0, [x20]
0x251bd0280:	ldr	x8, [x8, #0x10]
0x251bd0284:	str	x8, [x20, #0x10]
0x251bd0288:	ldr	x0, [x0, #0x78]
0x251bd028c:	bl	#0x25810b430
0x251bd0290:	ldr	w8, [x19, #0x98]
0x251bd0294:	cmp	w8, #2
0x251bd0298:	b.ne	#0x251bd02dc
0x251bd029c:	ldr	x0, [x19, #0xa8]
0x251bd02a0:	adrp	x8, #0x2680d5000
0x251bd02a4:	ldr	x8, [x8, #0x7e0]
0x251bd02a8:	ldr	x1, [x8]
0x251bd02ac:	bl	#0x258102680
0x251bd02b0:	add	x1, sp, #0xc
0x251bd02b4:	mov	x8, x20
0x251bd02b8:	bl	#0x251b3cfac
0x251bd02bc:	ldr	x8, [x20]
0x251bd02c0:	cbnz	x8, #0x251bd02dc
0x251bd02c4:	ldr	x0, [x19, #0xa8]
0x251bd02c8:	bl	#0x251b40994
0x251bd02cc:	bl	#0x258102680
0x251bd02d0:	add	x1, sp, #0xc
0x251bd02d4:	mov	x8, x20
0x251bd02d8:	bl	#0x251b3cfac
0x251bd02dc:	ldr	x0, [x19, #0x78]
0x251bd02e0:	ldp	x29, x30, [sp, #0x20]
0x251bd02e4:	ldp	x20, x19, [sp, #0x10]
0x251bd02e8:	add	sp, sp, #0x30
0x251bd02ec:	autibsp	
0x251bd02f0:	eor	x16, x30, x30, lsl #1
0x251bd02f4:	tbz	x16, #0x3e, #0x251bd02fc
0x251bd02f8:	brk	#0xc471
0x251bd02fc:	b	#0x25810b440

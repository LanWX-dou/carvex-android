; AirPlaySender 0x251ab019c-0x251ab02e0; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251ab019c:	pacibsp	
0x251ab01a0:	sub	sp, sp, #0x50
0x251ab01a4:	stp	x24, x23, [sp, #0x10]
0x251ab01a8:	stp	x22, x21, [sp, #0x20]
0x251ab01ac:	stp	x20, x19, [sp, #0x30]
0x251ab01b0:	stp	x29, x30, [sp, #0x40]
0x251ab01b4:	add	x29, sp, #0x40
0x251ab01b8:	mov	x19, x2
0x251ab01bc:	mov	x20, x1
0x251ab01c0:	str	xzr, [sp, #8]
0x251ab01c4:	bl	#0x25810ac50
0x251ab01c8:	mov	x22, x0
0x251ab01cc:	ldr	x0, [x0, #0x28]
0x251ab01d0:	add	x1, x22, #8
0x251ab01d4:	mov	w2, #0x10
0x251ab01d8:	bl	#0x2580f6ff0
0x251ab01dc:	cbz	x0, #0x251ab02bc
0x251ab01e0:	mov	x21, x0
0x251ab01e4:	ldr	x23, [x22]
0x251ab01e8:	cbz	x23, #0x251ab0258
0x251ab01ec:	ldr	x24, [x22, #0x28]
0x251ab01f0:	mov	x0, x23
0x251ab01f4:	bl	#0x258109150
0x251ab01f8:	ldr	x16, [x0, #0x10]!
0x251ab01fc:	mov	x17, x0
0x251ab0200:	movk	x17, #0x97e1, lsl #48
0x251ab0204:	autda	x16, x17
0x251ab0208:	ldr	x9, [x16, #0x18]!
0x251ab020c:	cbz	x9, #0x251ab0260
0x251ab0210:	mov	x8, x16
0x251ab0214:	movk	x8, #0xa2e6, lsl #48
0x251ab0218:	mov	x16, x9
0x251ab021c:	mov	x17, x8
0x251ab0220:	autia	x16, x17
0x251ab0224:	mov	x17, x16
0x251ab0228:	xpaci	x17
0x251ab022c:	cmp	x16, x17
0x251ab0230:	b.eq	#0x251ab0238
0x251ab0234:	brk	#0xc470
0x251ab0238:	paciza	x16
0x251ab023c:	cbz	x16, #0x251ab0260
0x251ab0240:	add	x3, sp, #8
0x251ab0244:	mov	x0, x23
0x251ab0248:	mov	x1, x21
0x251ab024c:	mov	x2, x24
0x251ab0250:	blraa	x9, x8
0x251ab0254:	b	#0x251ab0260
0x251ab0258:	str	x21, [sp, #8]
0x251ab025c:	mov	x21, #0
0x251ab0260:	ldr	x0, [x22, #0x28]
0x251ab0264:	add	x1, x22, #0x18
0x251ab0268:	mov	w2, #0x10
0x251ab026c:	bl	#0x2580f6ff0
0x251ab0270:	cbz	x0, #0x251ab02cc
0x251ab0274:	mov	w22, #0
0x251ab0278:	ldr	x8, [sp, #8]
0x251ab027c:	str	x8, [x20]
0x251ab0280:	str	xzr, [sp, #8]
0x251ab0284:	str	x0, [x19]
0x251ab0288:	cbz	x21, #0x251ab0294
0x251ab028c:	mov	x0, x21
0x251ab0290:	bl	#0x2580f5830
0x251ab0294:	ldr	x0, [sp, #8]
0x251ab0298:	cbz	x0, #0x251ab02a0
0x251ab029c:	bl	#0x2580f5830
0x251ab02a0:	mov	x0, x22
0x251ab02a4:	ldp	x29, x30, [sp, #0x40]
0x251ab02a8:	ldp	x20, x19, [sp, #0x30]
0x251ab02ac:	ldp	x22, x21, [sp, #0x20]
0x251ab02b0:	ldp	x24, x23, [sp, #0x10]
0x251ab02b4:	add	sp, sp, #0x50
0x251ab02b8:	retab	
0x251ab02bc:	mov	w22, #0xe7d8
0x251ab02c0:	movk	w22, #0xfffe, lsl #16
0x251ab02c4:	bl	#0x251b89c5c
0x251ab02c8:	b	#0x251ab0294
0x251ab02cc:	mov	w22, #0xe7d8
0x251ab02d0:	movk	w22, #0xfffe, lsl #16
0x251ab02d4:	bl	#0x251b89c30
0x251ab02d8:	cbnz	x21, #0x251ab028c
0x251ab02dc:	b	#0x251ab0294

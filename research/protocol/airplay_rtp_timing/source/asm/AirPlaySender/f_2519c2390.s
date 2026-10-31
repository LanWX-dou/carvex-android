; AirPlaySender 0x2519c2390-0x2519c2400; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519c2390:	pacibsp	
0x2519c2394:	stp	x20, x19, [sp, #-0x20]!
0x2519c2398:	stp	x29, x30, [sp, #0x10]
0x2519c239c:	add	x29, sp, #0x10
0x2519c23a0:	ldrb	w8, [x0, #0x18]
0x2519c23a4:	tbz	w8, #0, #0x2519c23e8
0x2519c23a8:	mov	x19, x1
0x2519c23ac:	cbz	x1, #0x2519c23f0
0x2519c23b0:	mov	x20, x0
0x2519c23b4:	ldr	x0, [x19, #0x10]
0x2519c23b8:	str	xzr, [x19, #0x10]
0x2519c23bc:	cbz	x0, #0x2519c23c4
0x2519c23c0:	bl	#0x2580f5830
0x2519c23c4:	ldr	x0, [x20, #0x58]
0x2519c23c8:	mov	x1, x19
0x2519c23cc:	ldp	x29, x30, [sp, #0x10]
0x2519c23d0:	ldp	x20, x19, [sp], #0x20
0x2519c23d4:	autibsp	
0x2519c23d8:	eor	x16, x30, x30, lsl #1
0x2519c23dc:	tbz	x16, #0x3e, #0x2519c23e4
0x2519c23e0:	brk	#0xc471
0x2519c23e4:	b	#0x25810ecc0
0x2519c23e8:	bl	#0x251ba3de4
0x2519c23ec:	b	#0x2519c23f4
0x2519c23f0:	bl	#0x251ba3dd0
0x2519c23f4:	ldp	x29, x30, [sp, #0x10]
0x2519c23f8:	ldp	x20, x19, [sp], #0x20
0x2519c23fc:	retab	

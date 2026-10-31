; AirPlaySender 0x251aa9490-0x251aa9524; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251aa9490:	pacibsp	
0x251aa9494:	stp	x22, x21, [sp, #-0x30]!
0x251aa9498:	stp	x20, x19, [sp, #0x10]
0x251aa949c:	stp	x29, x30, [sp, #0x20]
0x251aa94a0:	add	x29, sp, #0x20
0x251aa94a4:	mov	x19, x2
0x251aa94a8:	mov	x20, x1
0x251aa94ac:	bl	#0x25810ac50
0x251aa94b0:	mov	x22, x0
0x251aa94b4:	ldr	x0, [x0, #0x30]
0x251aa94b8:	add	x1, x22, #0x10
0x251aa94bc:	mov	w2, #0x10
0x251aa94c0:	bl	#0x2580f6ff0
0x251aa94c4:	cbz	x0, #0x251aa9500
0x251aa94c8:	mov	x21, x0
0x251aa94cc:	ldr	x0, [x22, #0x30]
0x251aa94d0:	add	x1, x22, #0x20
0x251aa94d4:	mov	w2, #0x10
0x251aa94d8:	bl	#0x2580f6ff0
0x251aa94dc:	cbz	x0, #0x251aa9510
0x251aa94e0:	mov	w22, #0
0x251aa94e4:	str	x21, [x20]
0x251aa94e8:	str	x0, [x19]
0x251aa94ec:	mov	x0, x22
0x251aa94f0:	ldp	x29, x30, [sp, #0x20]
0x251aa94f4:	ldp	x20, x19, [sp, #0x10]
0x251aa94f8:	ldp	x22, x21, [sp], #0x30
0x251aa94fc:	retab	
0x251aa9500:	mov	w22, #0xe7d8
0x251aa9504:	movk	w22, #0xfffe, lsl #16
0x251aa9508:	bl	#0x251b844c4
0x251aa950c:	b	#0x251aa94ec
0x251aa9510:	mov	w22, #0xe7d8
0x251aa9514:	movk	w22, #0xfffe, lsl #16
0x251aa9518:	mov	x0, x21
0x251aa951c:	bl	#0x251b84478
0x251aa9520:	b	#0x251aa94ec

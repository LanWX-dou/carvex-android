; AirPlaySender 0x251ace4e4-0x251ace54c; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251ace4e4:	ldr	x8, [x0, #0xa8]
0x251ace4e8:	cbz	x8, #0x251ace530
0x251ace4ec:	add	x9, x8, #0xc
0x251ace4f0:	ubfiz	x8, x1, #2, #0x20
0x251ace4f4:	ldrsb	w10, [x9, x8]
0x251ace4f8:	and	w8, w10, #0xff
0x251ace4fc:	str	w8, [x2]
0x251ace500:	tbnz	w10, #0x1f, #0x251ace508
0x251ace504:	ret	
0x251ace508:	mov	w10, w1
0x251ace50c:	add	x9, x9, x10, lsl #2
0x251ace510:	ldr	w9, [x9]
0x251ace514:	rev	w9, w9
0x251ace518:	lsr	w10, w9, #2
0x251ace51c:	and	w10, w10, #0x3fff00
0x251ace520:	orr	w9, w10, w9, lsl #22
0x251ace524:	orr	w8, w9, w8
0x251ace528:	str	w8, [x2]
0x251ace52c:	ret	
0x251ace530:	pacibsp	
0x251ace534:	stp	x29, x30, [sp, #-0x10]!
0x251ace538:	mov	x29, sp
0x251ace53c:	bl	#0x251ba4294
0x251ace540:	ldp	x29, x30, [sp], #0x10
0x251ace544:	autibsp	
0x251ace548:	ret	

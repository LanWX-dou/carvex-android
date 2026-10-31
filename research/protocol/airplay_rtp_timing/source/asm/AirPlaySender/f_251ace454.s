; AirPlaySender 0x251ace454-0x251ace49c; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251ace454:	ldrsb	w9, [x0]
0x251ace458:	and	w8, w9, #0xff
0x251ace45c:	str	w8, [x1]
0x251ace460:	tbz	w9, #0x1f, #0x251ace480
0x251ace464:	ldr	w9, [x0]
0x251ace468:	rev	w9, w9
0x251ace46c:	lsr	w10, w9, #2
0x251ace470:	and	w10, w10, #0x3fff00
0x251ace474:	orr	w9, w10, w9, lsl #22
0x251ace478:	orr	w8, w9, w8
0x251ace47c:	str	w8, [x1]
0x251ace480:	cbz	x2, #0x251ace498
0x251ace484:	tst	w8, #0x80
0x251ace488:	mov	w8, #4
0x251ace48c:	csinc	x8, x8, xzr, ne
0x251ace490:	add	x9, x0, x8
0x251ace494:	str	x9, [x2]
0x251ace498:	ret	

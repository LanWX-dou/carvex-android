; AirPlaySender 0x251ace49c-0x251ace4e4; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251ace49c:	ldr	x8, [x0, #0xa8]
0x251ace4a0:	cbz	x8, #0x251ace4c4
0x251ace4a4:	ldrh	w8, [x8, #2]
0x251ace4a8:	rev	w8, w8
0x251ace4ac:	ldr	w9, [x0, #0x678]
0x251ace4b0:	sub	w9, w1, w9
0x251ace4b4:	add	w8, w9, w8, lsr #16
0x251ace4b8:	add	w8, w8, #1
0x251ace4bc:	and	w0, w8, #0xffff
0x251ace4c0:	ret	
0x251ace4c4:	pacibsp	
0x251ace4c8:	stp	x29, x30, [sp, #-0x10]!
0x251ace4cc:	mov	x29, sp
0x251ace4d0:	bl	#0x251ba4280
0x251ace4d4:	mov	w8, #0
0x251ace4d8:	ldp	x29, x30, [sp], #0x10
0x251ace4dc:	autibsp	
0x251ace4e0:	b	#0x251ace4bc

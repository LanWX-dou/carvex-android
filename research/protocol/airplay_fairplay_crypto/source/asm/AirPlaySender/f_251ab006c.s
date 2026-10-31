; AirPlaySender 0x251ab006c-0x251ab0108; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251ab006c:	pacibsp	
0x251ab0070:	stp	x20, x19, [sp, #-0x20]!
0x251ab0074:	stp	x29, x30, [sp, #0x10]
0x251ab0078:	add	x29, sp, #0x10
0x251ab007c:	bl	#0x25810ac50
0x251ab0080:	ldr	x19, [x0]
0x251ab0084:	cbz	x19, #0x251ab00f8
0x251ab0088:	mov	x0, x19
0x251ab008c:	bl	#0x258109150
0x251ab0090:	ldr	x16, [x0, #0x10]!
0x251ab0094:	mov	x17, x0
0x251ab0098:	movk	x17, #0x97e1, lsl #48
0x251ab009c:	autda	x16, x17
0x251ab00a0:	ldr	x2, [x16, #8]!
0x251ab00a4:	cbz	x2, #0x251ab00f8
0x251ab00a8:	mov	x1, x16
0x251ab00ac:	movk	x1, #0xd6e6, lsl #48
0x251ab00b0:	mov	x16, x2
0x251ab00b4:	mov	x17, x1
0x251ab00b8:	autia	x16, x17
0x251ab00bc:	mov	x17, x16
0x251ab00c0:	xpaci	x17
0x251ab00c4:	cmp	x16, x17
0x251ab00c8:	b.eq	#0x251ab00d0
0x251ab00cc:	brk	#0xc470
0x251ab00d0:	paciza	x16
0x251ab00d4:	cbz	x16, #0x251ab00f8
0x251ab00d8:	mov	x0, x19
0x251ab00dc:	ldp	x29, x30, [sp, #0x10]
0x251ab00e0:	ldp	x20, x19, [sp], #0x20
0x251ab00e4:	autibsp	
0x251ab00e8:	eor	x16, x30, x30, lsl #1
0x251ab00ec:	tbz	x16, #0x3e, #0x251ab00f4
0x251ab00f0:	brk	#0xc471
0x251ab00f4:	braa	x2, x1
0x251ab00f8:	mov	w0, #0
0x251ab00fc:	ldp	x29, x30, [sp, #0x10]
0x251ab0100:	ldp	x20, x19, [sp], #0x20
0x251ab0104:	retab	

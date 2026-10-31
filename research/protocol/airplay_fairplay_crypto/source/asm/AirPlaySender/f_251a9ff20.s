; AirPlaySender 0x251a9ff20-0x251a9ffb0; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a9ff20:	pacibsp	
0x251a9ff24:	stp	x20, x19, [sp, #-0x20]!
0x251a9ff28:	stp	x29, x30, [sp, #0x10]
0x251a9ff2c:	add	x29, sp, #0x10
0x251a9ff30:	mov	x19, x0
0x251a9ff34:	bl	#0x258109150
0x251a9ff38:	ldr	x16, [x0, #0x10]!
0x251a9ff3c:	mov	x17, x0
0x251a9ff40:	movk	x17, #0xa363, lsl #48
0x251a9ff44:	autda	x16, x17
0x251a9ff48:	ldr	x2, [x16, #8]!
0x251a9ff4c:	cbz	x2, #0x251a9ffa0
0x251a9ff50:	mov	x1, x16
0x251a9ff54:	movk	x1, #0x36eb, lsl #48
0x251a9ff58:	mov	x16, x2
0x251a9ff5c:	mov	x17, x1
0x251a9ff60:	autia	x16, x17
0x251a9ff64:	mov	x17, x16
0x251a9ff68:	xpaci	x17
0x251a9ff6c:	cmp	x16, x17
0x251a9ff70:	b.eq	#0x251a9ff78
0x251a9ff74:	brk	#0xc470
0x251a9ff78:	paciza	x16
0x251a9ff7c:	cbz	x16, #0x251a9ffa0
0x251a9ff80:	mov	x0, x19
0x251a9ff84:	ldp	x29, x30, [sp, #0x10]
0x251a9ff88:	ldp	x20, x19, [sp], #0x20
0x251a9ff8c:	autibsp	
0x251a9ff90:	eor	x16, x30, x30, lsl #1
0x251a9ff94:	tbz	x16, #0x3e, #0x251a9ff9c
0x251a9ff98:	brk	#0xc471
0x251a9ff9c:	braa	x2, x1
0x251a9ffa0:	mov	w0, #0
0x251a9ffa4:	ldp	x29, x30, [sp, #0x10]
0x251a9ffa8:	ldp	x20, x19, [sp], #0x20
0x251a9ffac:	retab	

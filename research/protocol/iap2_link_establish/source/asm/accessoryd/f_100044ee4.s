; accessoryd 0x100044ee4-0x100044f3c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100044ee4:	pacibsp	
0x100044ee8:	stp	x29, x30, [sp, #-0x10]!
0x100044eec:	mov	x29, sp
0x100044ef0:	cbz	x0, #0x100044f1c
0x100044ef4:	ldrb	w8, [x0, #0x1e]
0x100044ef8:	cmp	w8, #1
0x100044efc:	b.eq	#0x100044f24
0x100044f00:	cbz	x1, #0x100044f2c
0x100044f04:	ldp	x29, x30, [sp], #0x10
0x100044f08:	autibsp	
0x100044f0c:	eor	x16, x30, x30, lsl #1
0x100044f10:	tbz	x16, #0x3e, #0x100044f18
0x100044f14:	brk	#0xc471
0x100044f18:	b	#0x100132e28
0x100044f1c:	bl	#0x100134090
0x100044f20:	b	#0x100044f30
0x100044f24:	bl	#0x100134044
0x100044f28:	b	#0x100044f30
0x100044f2c:	bl	#0x100133ff8
0x100044f30:	mov	w0, #1
0x100044f34:	ldp	x29, x30, [sp], #0x10
0x100044f38:	retab	

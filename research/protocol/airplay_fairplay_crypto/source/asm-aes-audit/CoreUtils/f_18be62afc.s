; CoreUtils 0x18be62afc-0x18be62b48; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be62afc:	pacibsp	
0x18be62b00:	stp	x20, x19, [sp, #-0x20]!
0x18be62b04:	stp	x29, x30, [sp, #0x10]
0x18be62b08:	add	x29, sp, #0x10
0x18be62b0c:	mov	x19, x0
0x18be62b10:	ldr	x0, [x0]
0x18be62b14:	cbz	x0, #0x18be62b1c
0x18be62b18:	bl	#0x1900cd760
0x18be62b1c:	mov	x0, x19
0x18be62b20:	mov	w1, #0x30
0x18be62b24:	mov	w2, #0
0x18be62b28:	mov	w3, #0x30
0x18be62b2c:	ldp	x29, x30, [sp, #0x10]
0x18be62b30:	ldp	x20, x19, [sp], #0x20
0x18be62b34:	autibsp	
0x18be62b38:	eor	x16, x30, x30, lsl #1
0x18be62b3c:	tbz	x16, #0x3e, #0x18be62b44
0x18be62b40:	brk	#0xc471
0x18be62b44:	b	#0x1900cfdb0

; CoreUtils 0x18be62c50-0x18be62c9c; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be62c50:	pacibsp	
0x18be62c54:	stp	x20, x19, [sp, #-0x20]!
0x18be62c58:	stp	x29, x30, [sp, #0x10]
0x18be62c5c:	add	x29, sp, #0x10
0x18be62c60:	mov	x19, x0
0x18be62c64:	ldr	x0, [x0]
0x18be62c68:	cbz	x0, #0x18be62c70
0x18be62c6c:	bl	#0x1900cd760
0x18be62c70:	mov	x0, x19
0x18be62c74:	mov	w1, #0x18
0x18be62c78:	mov	w2, #0
0x18be62c7c:	mov	w3, #0x18
0x18be62c80:	ldp	x29, x30, [sp, #0x10]
0x18be62c84:	ldp	x20, x19, [sp], #0x20
0x18be62c88:	autibsp	
0x18be62c8c:	eor	x16, x30, x30, lsl #1
0x18be62c90:	tbz	x16, #0x3e, #0x18be62c98
0x18be62c94:	brk	#0xc471
0x18be62c98:	b	#0x1900cfdb0

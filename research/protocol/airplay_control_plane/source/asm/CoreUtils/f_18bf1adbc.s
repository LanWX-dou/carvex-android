; CoreUtils 0x18bf1adbc-0x18bf1aecc; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18bf1adbc:	pacibsp	
0x18bf1adc0:	stp	x26, x25, [sp, #-0x50]!
0x18bf1adc4:	stp	x24, x23, [sp, #0x10]
0x18bf1adc8:	stp	x22, x21, [sp, #0x20]
0x18bf1adcc:	stp	x20, x19, [sp, #0x30]
0x18bf1add0:	stp	x29, x30, [sp, #0x40]
0x18bf1add4:	add	x29, sp, #0x40
0x18bf1add8:	mov	x20, x5
0x18bf1addc:	mov	x21, x4
0x18bf1ade0:	mov	x22, x3
0x18bf1ade4:	mov	x23, x2
0x18bf1ade8:	mov	x24, x1
0x18bf1adec:	mov	x19, x0
0x18bf1adf0:	mov	w25, #1
0x18bf1adf4:	mov	x2, #0xdf2e
0x18bf1adf8:	movk	x2, #0x90be, lsl #16
0x18bf1adfc:	movk	x2, #0x40, lsl #32
0x18bf1ae00:	movk	x2, #0x103, lsl #48
0x18bf1ae04:	mov	w0, #1
0x18bf1ae08:	mov	w1, #0x46c8
0x18bf1ae0c:	bl	#0x1900cc460
0x18bf1ae10:	cbz	x0, #0x18bf1aec4
0x18bf1ae14:	mov	w8, #-1
0x18bf1ae18:	str	w8, [x0]
0x18bf1ae1c:	adrp	x8, #0x1e43d0000
0x18bf1ae20:	add	x8, x8, #0x4c8
0x18bf1ae24:	cmp	x24, #0
0x18bf1ae28:	csel	x8, x8, x24, eq
0x18bf1ae2c:	str	x8, [x0, #8]
0x18bf1ae30:	str	w25, [x0, #0x10]
0x18bf1ae34:	ldp	q0, q1, [x23]
0x18bf1ae38:	str	q1, [x0, #0x4160]
0x18bf1ae3c:	str	q0, [x0, #0x4150]
0x18bf1ae40:	cbz	x22, #0x18bf1ae4c
0x18bf1ae44:	ldr	x8, [x22]
0x18bf1ae48:	str	x8, [x0, #0x4170]
0x18bf1ae4c:	ldp	q0, q1, [x21]
0x18bf1ae50:	str	q1, [x0, #0x46b0]
0x18bf1ae54:	str	q0, [x0, #0x46a0]
0x18bf1ae58:	cbz	x20, #0x18bf1ae64
0x18bf1ae5c:	ldr	x8, [x20]
0x18bf1ae60:	str	x8, [x0, #0x46c0]
0x18bf1ae64:	mov	w8, #0
0x18bf1ae68:	adrp	x16, #0x18bf48000
0x18bf1ae6c:	add	x16, x16, #0xfdc
0x18bf1ae70:	paciza	x16
0x18bf1ae74:	stp	x0, x16, [x19]
0x18bf1ae78:	adrp	x16, #0x18bf48000
0x18bf1ae7c:	add	x16, x16, #0xf90
0x18bf1ae80:	paciza	x16
0x18bf1ae84:	str	x16, [x19, #0x10]
0x18bf1ae88:	adrp	x16, #0x18be49000
0x18bf1ae8c:	add	x16, x16, #0x968
0x18bf1ae90:	paciza	x16
0x18bf1ae94:	str	x16, [x19, #0x18]
0x18bf1ae98:	adrp	x16, #0x18be4d000
0x18bf1ae9c:	add	x16, x16, #0x5fc
0x18bf1aea0:	paciza	x16
0x18bf1aea4:	str	x16, [x19, #0x20]
0x18bf1aea8:	mov	x0, x8
0x18bf1aeac:	ldp	x29, x30, [sp, #0x40]
0x18bf1aeb0:	ldp	x20, x19, [sp, #0x30]
0x18bf1aeb4:	ldp	x22, x21, [sp, #0x20]
0x18bf1aeb8:	ldp	x24, x23, [sp, #0x10]
0x18bf1aebc:	ldp	x26, x25, [sp], #0x50
0x18bf1aec0:	retab	
0x18bf1aec4:	mov	w8, #-0x1a48
0x18bf1aec8:	b	#0x18bf1aea8

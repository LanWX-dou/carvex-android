; CoreUtils 0x18be4be58-0x18be4bf08; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be4be58:	pacibsp	
0x18be4be5c:	stp	x20, x19, [sp, #-0x20]!
0x18be4be60:	stp	x29, x30, [sp, #0x10]
0x18be4be64:	add	x29, sp, #0x10
0x18be4be68:	mov	x19, x0
0x18be4be6c:	adrp	x8, #0x1e43d0000
0x18be4be70:	ldr	x8, [x8, #0xbe8]
0x18be4be74:	cmn	x8, #1
0x18be4be78:	b.ne	#0x18be4bedc
0x18be4be7c:	adrp	x8, #0x1e43d0000
0x18be4be80:	ldr	x1, [x8, #0xbe0]
0x18be4be84:	mov	x0, #0
0x18be4be88:	mov	w2, #0x2630
0x18be4be8c:	mov	x3, #0
0x18be4be90:	bl	#0x1900ce6a0
0x18be4be94:	cbz	x0, #0x18be4bf00
0x18be4be98:	mov	x20, x0
0x18be4be9c:	add	x0, x0, #0x10
0x18be4bea0:	mov	w1, #0x2630
0x18be4bea4:	bl	#0x1900cc250
0x18be4bea8:	mov	w8, #-1
0x18be4beac:	str	w8, [x20, #0x2600]
0x18be4beb0:	str	w8, [x20, #0x2618]
0x18be4beb4:	mov	w8, #0x2400
0x18be4beb8:	movk	w8, #0xf4, lsl #16
0x18be4bebc:	str	x8, [x20, #0x2158]
0x18be4bec0:	mov	x0, x20
0x18be4bec4:	bl	#0x18be4bf08
0x18be4bec8:	mov	w0, #0
0x18be4becc:	str	x20, [x19]
0x18be4bed0:	ldp	x29, x30, [sp, #0x10]
0x18be4bed4:	ldp	x20, x19, [sp], #0x20
0x18be4bed8:	retab	
0x18be4bedc:	adrp	x0, #0x1e43d0000
0x18be4bee0:	add	x0, x0, #0xbe8
0x18be4bee4:	adrp	x16, #0x18bf0c000
0x18be4bee8:	add	x16, x16, #0xc34
0x18be4beec:	paciza	x16
0x18be4bef0:	mov	x2, x16
0x18be4bef4:	mov	x1, #0
0x18be4bef8:	bl	#0x1900cc2c0
0x18be4befc:	b	#0x18be4be7c
0x18be4bf00:	mov	w0, #-0x1a48
0x18be4bf04:	b	#0x18be4bed0

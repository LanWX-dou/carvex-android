; CoreUtils 0x18be4dc0c-0x18be4dccc; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be4dc0c:	pacibsp	
0x18be4dc10:	sub	sp, sp, #0x80
0x18be4dc14:	stp	x20, x19, [sp, #0x60]
0x18be4dc18:	stp	x29, x30, [sp, #0x70]
0x18be4dc1c:	add	x29, sp, #0x70
0x18be4dc20:	mov	x19, x0
0x18be4dc24:	stp	xzr, x4, [x29, #-0x20]
0x18be4dc28:	stp	xzr, x4, [x29, #-0x28]
0x18be4dc2c:	stur	wzr, [x29, #-0x2c]
0x18be4dc30:	adrp	x8, #0x18bf6a000
0x18be4dc34:	add	x8, x8, #0xb3a
0x18be4dc38:	cmp	x1, #0
0x18be4dc3c:	csel	x10, x8, x1, eq
0x18be4dc40:	sub	x8, x29, #0x2c
0x18be4dc44:	sub	x9, x29, #0x20
0x18be4dc48:	stp	x8, x10, [sp, #0x28]
0x18be4dc4c:	stp	x3, x9, [sp, #0x18]
0x18be4dc50:	sub	x8, x29, #0x28
0x18be4dc54:	str	x8, [sp, #0x10]
0x18be4dc58:	adrp	x8, #0x18bf69000
0x18be4dc5c:	add	x8, x8, #0xc87
0x18be4dc60:	sub	x9, x29, #0x24
0x18be4dc64:	stp	x2, x9, [sp]
0x18be4dc68:	mov	w1, #0x2000
0x18be4dc6c:	mov	x2, x8
0x18be4dc70:	bl	#0x18be383ac
0x18be4dc74:	sub	w9, w0, #2, lsl #12
0x18be4dc78:	cmn	w9, #2, lsl #12
0x18be4dc7c:	b.ls	#0x18be4dcc4
0x18be4dc80:	mov	x8, x0
0x18be4dc84:	mov	w0, #0
0x18be4dc88:	str	x19, [x19, #0x2018]
0x18be4dc8c:	ldpsw	x9, x10, [x29, #-0x28]
0x18be4dc90:	str	x10, [x19, #0x2020]
0x18be4dc94:	add	x10, x19, x9
0x18be4dc98:	str	x10, [x19, #0x2030]
0x18be4dc9c:	ldursw	x10, [x29, #-0x2c]
0x18be4dca0:	sub	x9, x10, x9
0x18be4dca4:	str	x9, [x19, #0x2038]
0x18be4dca8:	mov	w8, w8
0x18be4dcac:	str	x8, [x19, #0x2000]
0x18be4dcb0:	str	w0, [x19, #0x211c]
0x18be4dcb4:	ldp	x29, x30, [sp, #0x70]
0x18be4dcb8:	ldp	x20, x19, [sp, #0x60]
0x18be4dcbc:	add	sp, sp, #0x80
0x18be4dcc0:	retab	
0x18be4dcc4:	mov	w0, #-0x1a5f
0x18be4dcc8:	b	#0x18be4dcb0

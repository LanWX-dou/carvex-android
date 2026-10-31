; CoreUtils 0x18be48df8-0x18be48ef0; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be48df8:	pacibsp	
0x18be48dfc:	stp	x22, x21, [sp, #-0x30]!
0x18be48e00:	stp	x20, x19, [sp, #0x10]
0x18be48e04:	stp	x29, x30, [sp, #0x20]
0x18be48e08:	add	x29, sp, #0x20
0x18be48e0c:	mov	x19, x2
0x18be48e10:	mov	x21, x1
0x18be48e14:	mov	x20, x0
0x18be48e18:	ldr	x9, [x0, #0x48]
0x18be48e1c:	cbz	x9, #0x18be48e90
0x18be48e20:	mov	w8, #0x10
0x18be48e24:	sub	x8, x8, x9
0x18be48e28:	cmp	x8, x19
0x18be48e2c:	csel	x8, x8, x19, lo
0x18be48e30:	cbz	x8, #0x18be48e60
0x18be48e34:	mov	x9, #0
0x18be48e38:	add	x10, x20, #0x38
0x18be48e3c:	mov	x11, x8
0x18be48e40:	ldrb	w12, [x21, x9]
0x18be48e44:	ldr	x13, [x20, #0x48]
0x18be48e48:	add	x13, x13, x9
0x18be48e4c:	strb	w12, [x10, x13]
0x18be48e50:	add	x9, x9, #1
0x18be48e54:	subs	x11, x11, #1
0x18be48e58:	b.ne	#0x18be48e40
0x18be48e5c:	ldr	x9, [x20, #0x48]
0x18be48e60:	add	x9, x9, x8
0x18be48e64:	str	x9, [x20, #0x48]
0x18be48e68:	sub	x19, x19, x8
0x18be48e6c:	add	x10, x21, x8
0x18be48e70:	mov	x21, x10
0x18be48e74:	cmp	x9, #0x10
0x18be48e78:	b.ne	#0x18be48e90
0x18be48e7c:	add	x1, x20, #0x38
0x18be48e80:	mov	x0, x20
0x18be48e84:	mov	w2, #0x10
0x18be48e88:	bl	#0x18be4b048
0x18be48e8c:	str	xzr, [x20, #0x48]
0x18be48e90:	cmp	x19, #0x10
0x18be48e94:	b.lo	#0x18be48eb8
0x18be48e98:	and	x22, x19, #0xfffffffffffffff0
0x18be48e9c:	mov	x0, x20
0x18be48ea0:	mov	x1, x21
0x18be48ea4:	mov	x2, x22
0x18be48ea8:	bl	#0x18be4b048
0x18be48eac:	add	x8, x21, x22
0x18be48eb0:	and	x19, x19, #0xf
0x18be48eb4:	mov	x21, x8
0x18be48eb8:	cbz	x19, #0x18be48ee0
0x18be48ebc:	mov	x8, #0
0x18be48ec0:	add	x9, x20, #0x38
0x18be48ec4:	mov	x10, x19
0x18be48ec8:	ldrb	w11, [x21, x8]
0x18be48ecc:	strb	w11, [x9, x8]
0x18be48ed0:	add	x8, x8, #1
0x18be48ed4:	subs	x10, x10, #1
0x18be48ed8:	b.ne	#0x18be48ec8
0x18be48edc:	str	x19, [x20, #0x48]
0x18be48ee0:	ldp	x29, x30, [sp, #0x20]
0x18be48ee4:	ldp	x20, x19, [sp, #0x10]
0x18be48ee8:	ldp	x22, x21, [sp], #0x30
0x18be48eec:	retab	

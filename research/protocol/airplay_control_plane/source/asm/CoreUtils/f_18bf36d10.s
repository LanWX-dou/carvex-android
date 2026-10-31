; CoreUtils 0x18bf36d10-0x18bf36f60; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18bf36d10:	pacibsp	
0x18bf36d14:	sub	sp, sp, #0x70
0x18bf36d18:	stp	x26, x25, [sp, #0x20]
0x18bf36d1c:	stp	x24, x23, [sp, #0x30]
0x18bf36d20:	stp	x22, x21, [sp, #0x40]
0x18bf36d24:	stp	x20, x19, [sp, #0x50]
0x18bf36d28:	stp	x29, x30, [sp, #0x60]
0x18bf36d2c:	add	x29, sp, #0x60
0x18bf36d30:	stp	xzr, xzr, [sp, #0x10]
0x18bf36d34:	str	xzr, [sp, #8]
0x18bf36d38:	adrp	x8, #0x18bf71000
0x18bf36d3c:	add	x8, x8, #0xbab
0x18bf36d40:	cmp	x1, x8
0x18bf36d44:	b.eq	#0x18bf36d50
0x18bf36d48:	mov	w20, #-0x1a4f
0x18bf36d4c:	b	#0x18bf36e98
0x18bf36d50:	mov	x22, x7
0x18bf36d54:	mov	x23, x6
0x18bf36d58:	mov	x21, x5
0x18bf36d5c:	mov	x20, x4
0x18bf36d60:	mov	x25, x3
0x18bf36d64:	mov	x24, x2
0x18bf36d68:	mov	x19, x0
0x18bf36d6c:	ldr	x0, [x0]
0x18bf36d70:	cbz	x0, #0x18bf36d7c
0x18bf36d74:	bl	#0x18bf09448
0x18bf36d78:	str	xzr, [x19]
0x18bf36d7c:	adrp	x0, #0x1e8360000
0x18bf36d80:	add	x0, x0, #0xe90
0x18bf36d84:	bl	#0x18bf09358
0x18bf36d88:	str	x0, [x19]
0x18bf36d8c:	cbz	x0, #0x18bf36f58
0x18bf36d90:	mov	x26, x0
0x18bf36d94:	cmn	x25, #1
0x18bf36d98:	b.ne	#0x18bf36da8
0x18bf36d9c:	mov	x0, x24
0x18bf36da0:	bl	#0x1900d0320
0x18bf36da4:	mov	x25, x0
0x18bf36da8:	lsr	x8, x25, #0x1f
0x18bf36dac:	cbnz	x8, #0x18bf36f50
0x18bf36db0:	mov	x0, x26
0x18bf36db4:	mov	x1, x24
0x18bf36db8:	mov	x2, x25
0x18bf36dbc:	bl	#0x18bf09514
0x18bf36dc0:	cbnz	w0, #0x18bf36e94
0x18bf36dc4:	lsr	x8, x22, #0x1f
0x18bf36dc8:	cbnz	x8, #0x18bf36f50
0x18bf36dcc:	ldr	x0, [x19]
0x18bf36dd0:	mov	x1, x23
0x18bf36dd4:	mov	x2, x22
0x18bf36dd8:	bl	#0x18bf09570
0x18bf36ddc:	cbnz	w0, #0x18bf36e94
0x18bf36de0:	cmn	x21, #1
0x18bf36de4:	b.ne	#0x18bf36df4
0x18bf36de8:	mov	x0, x20
0x18bf36dec:	bl	#0x1900d0320
0x18bf36df0:	mov	x21, x0
0x18bf36df4:	lsr	x8, x21, #0x1f
0x18bf36df8:	cbnz	x8, #0x18bf36f50
0x18bf36dfc:	ldr	x0, [x19]
0x18bf36e00:	ldr	x8, [x0, #0x60]
0x18bf36e04:	ldr	x8, [x8, #0x28]
0x18bf36e08:	mov	x1, x20
0x18bf36e0c:	mov	x2, x21
0x18bf36e10:	blraaz	x8
0x18bf36e14:	cbnz	w0, #0x18bf36e94
0x18bf36e18:	ldr	x0, [x19]
0x18bf36e1c:	ldr	x8, [x0, #0x60]
0x18bf36e20:	ldr	x8, [x8, #0x30]
0x18bf36e24:	add	x1, sp, #0x18
0x18bf36e28:	blraaz	x8
0x18bf36e2c:	cbnz	w0, #0x18bf36e94
0x18bf36e30:	ldr	x3, [x29, #0x18]
0x18bf36e34:	mov	w20, #-0x1a57
0x18bf36e38:	lsr	x8, x3, #0x1f
0x18bf36e3c:	cbnz	x8, #0x18bf36e98
0x18bf36e40:	ldr	x8, [sp, #0x18]
0x18bf36e44:	ldr	w8, [x8, #8]
0x18bf36e48:	cmp	w8, #1
0x18bf36e4c:	b.lt	#0x18bf36e98
0x18bf36e50:	ldr	x2, [x29, #0x10]
0x18bf36e54:	ldr	x0, [x19]
0x18bf36e58:	ldr	x8, [x0, #0x60]
0x18bf36e5c:	ldr	x8, [x8, #0x38]
0x18bf36e60:	add	x1, sp, #0x10
0x18bf36e64:	blraaz	x8
0x18bf36e68:	cbnz	w0, #0x18bf36e94
0x18bf36e6c:	ldr	x8, [sp, #0x10]
0x18bf36e70:	ldr	w8, [x8, #8]
0x18bf36e74:	cmp	w8, #1
0x18bf36e78:	b.lt	#0x18bf36e98
0x18bf36e7c:	ldr	x0, [x19]
0x18bf36e80:	ldr	x8, [x0, #0x60]
0x18bf36e84:	ldr	x8, [x8, #0x48]
0x18bf36e88:	add	x1, sp, #8
0x18bf36e8c:	blraaz	x8
0x18bf36e90:	cbz	w0, #0x18bf36ee4
0x18bf36e94:	mov	w20, #-0x1a2c
0x18bf36e98:	ldr	x0, [sp, #0x18]
0x18bf36e9c:	cbz	x0, #0x18bf36ea8
0x18bf36ea0:	bl	#0x18bf091a4
0x18bf36ea4:	str	xzr, [sp, #0x18]
0x18bf36ea8:	ldr	x0, [sp, #0x10]
0x18bf36eac:	cbz	x0, #0x18bf36eb8
0x18bf36eb0:	bl	#0x18bf09140
0x18bf36eb4:	str	xzr, [sp, #0x10]
0x18bf36eb8:	ldr	x0, [sp, #8]
0x18bf36ebc:	cbz	x0, #0x18bf36ec4
0x18bf36ec0:	bl	#0x18bf091a4
0x18bf36ec4:	mov	x0, x20
0x18bf36ec8:	ldp	x29, x30, [sp, #0x60]
0x18bf36ecc:	ldp	x20, x19, [sp, #0x50]
0x18bf36ed0:	ldp	x22, x21, [sp, #0x40]
0x18bf36ed4:	ldp	x24, x23, [sp, #0x30]
0x18bf36ed8:	ldp	x26, x25, [sp, #0x20]
0x18bf36edc:	add	sp, sp, #0x70
0x18bf36ee0:	retab	
0x18bf36ee4:	ldr	x8, [sp, #8]
0x18bf36ee8:	ldr	w9, [x8, #8]
0x18bf36eec:	cmp	w9, #1
0x18bf36ef0:	b.lt	#0x18bf36e98
0x18bf36ef4:	mov	w20, #0
0x18bf36ef8:	ldp	x10, x9, [x29, #0x40]
0x18bf36efc:	ldp	x12, x11, [x29, #0x20]
0x18bf36f00:	ldr	x13, [sp, #0x18]
0x18bf36f04:	ldr	x14, [x13]
0x18bf36f08:	str	x14, [x12]
0x18bf36f0c:	ldp	x14, x12, [x29, #0x30]
0x18bf36f10:	ldrsw	x15, [x13, #8]
0x18bf36f14:	str	x15, [x11]
0x18bf36f18:	movi	v0.2d, #0000000000000000
0x18bf36f1c:	str	d0, [x13, #8]
0x18bf36f20:	ldr	x11, [sp, #0x10]
0x18bf36f24:	ldr	x13, [x11]
0x18bf36f28:	str	x13, [x14]
0x18bf36f2c:	ldrsw	x13, [x11, #8]
0x18bf36f30:	str	x13, [x12]
0x18bf36f34:	str	d0, [x11, #8]
0x18bf36f38:	ldr	x11, [x8]
0x18bf36f3c:	str	x11, [x10]
0x18bf36f40:	ldrsw	x10, [x8, #8]
0x18bf36f44:	str	x10, [x9]
0x18bf36f48:	str	d0, [x8, #8]
0x18bf36f4c:	b	#0x18bf36e98
0x18bf36f50:	mov	w20, #-0x1a57
0x18bf36f54:	b	#0x18bf36e98
0x18bf36f58:	mov	w20, #-0x1a48
0x18bf36f5c:	b	#0x18bf36e98

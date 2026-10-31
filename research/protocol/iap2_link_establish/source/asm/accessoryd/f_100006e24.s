; accessoryd 0x100006e24-0x100006f8c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100006e24:	pacibsp	
0x100006e28:	sub	sp, sp, #0x70
0x100006e2c:	stp	x28, x27, [sp, #0x10]
0x100006e30:	stp	x26, x25, [sp, #0x20]
0x100006e34:	stp	x24, x23, [sp, #0x30]
0x100006e38:	stp	x22, x21, [sp, #0x40]
0x100006e3c:	stp	x20, x19, [sp, #0x50]
0x100006e40:	stp	x29, x30, [sp, #0x60]
0x100006e44:	add	x29, sp, #0x60
0x100006e48:	mov	x20, x7
0x100006e4c:	mov	x22, x6
0x100006e50:	mov	x19, x5
0x100006e54:	str	x4, [sp]
0x100006e58:	mov	x24, x3
0x100006e5c:	mov	x25, x2
0x100006e60:	mov	x26, x1
0x100006e64:	mov	x23, x0
0x100006e68:	str	w5, [sp, #0xc]
0x100006e6c:	bl	#0x100005f4c
0x100006e70:	mov	x27, x0
0x100006e74:	cbz	w19, #0x100006e84
0x100006e78:	mov	x0, x23
0x100006e7c:	bl	#0x100005f38
0x100006e80:	mov	x19, x0
0x100006e84:	cbz	w20, #0x100006e98
0x100006e88:	add	x1, sp, #0xc
0x100006e8c:	mov	x0, x23
0x100006e90:	bl	#0x10000626c
0x100006e94:	b	#0x100006ea0
0x100006e98:	mov	x0, x23
0x100006e9c:	bl	#0x10000a488
0x100006ea0:	mov	x21, x0
0x100006ea4:	cbz	x0, #0x100006f68
0x100006ea8:	ldr	x8, [x21, #0x40]
0x100006eac:	ldr	w28, [sp, #0xc]
0x100006eb0:	add	w9, w19, w27
0x100006eb4:	add	w9, w9, w28
0x100006eb8:	strh	w9, [x21, #0x36]
0x100006ebc:	mov	w10, #0x5aff
0x100006ec0:	strh	w10, [x8]
0x100006ec4:	lsr	w10, w9, #8
0x100006ec8:	strb	w10, [x8, #2]
0x100006ecc:	strb	w9, [x8, #3]
0x100006ed0:	strb	w26, [x8, #4]
0x100006ed4:	strb	w25, [x8, #5]
0x100006ed8:	strb	w24, [x8, #6]
0x100006edc:	strb	w22, [x8, #7]
0x100006ee0:	mov	x0, x23
0x100006ee4:	bl	#0x1000071e4
0x100006ee8:	mov	x1, x0
0x100006eec:	mov	x0, x21
0x100006ef0:	mov	w2, #0
0x100006ef4:	bl	#0x1000071f4
0x100006ef8:	ldurh	w8, [x21, #0x3d]
0x100006efc:	cmp	w20, #0
0x100006f00:	mov	w9, #0x200
0x100006f04:	csel	w9, w9, wzr, ne
0x100006f08:	and	w8, w8, #0xfffffdff
0x100006f0c:	orr	w8, w8, w9
0x100006f10:	sturh	w8, [x21, #0x3d]
0x100006f14:	strb	wzr, [x21, #0x3f]
0x100006f18:	ldrh	w8, [x21, #0x36]
0x100006f1c:	str	w8, [x21, #0x2c]
0x100006f20:	ldr	x1, [sp]
0x100006f24:	cbz	x1, #0x100006f38
0x100006f28:	cbz	w28, #0x100006f38
0x100006f2c:	ldr	x0, [x21, #0x48]
0x100006f30:	mov	x2, x28
0x100006f34:	bl	#0x1001a23a0
0x100006f38:	mov	x0, x21
0x100006f3c:	bl	#0x100006120
0x100006f40:	strh	w0, [x21, #0x34]
0x100006f44:	mov	w8, #-0x1000000
0x100006f48:	str	w8, [x21, #0x38]
0x100006f4c:	ldurh	w8, [x21, #0x3d]
0x100006f50:	mov	w9, #0xf600
0x100006f54:	and	w8, w8, w9
0x100006f58:	mov	w9, #0x12
0x100006f5c:	orr	w8, w8, w9
0x100006f60:	stp	xzr, xzr, [x21, #8]
0x100006f64:	sturh	w8, [x21, #0x3d]
0x100006f68:	mov	x0, x21
0x100006f6c:	ldp	x29, x30, [sp, #0x60]
0x100006f70:	ldp	x20, x19, [sp, #0x50]
0x100006f74:	ldp	x22, x21, [sp, #0x40]
0x100006f78:	ldp	x24, x23, [sp, #0x30]
0x100006f7c:	ldp	x26, x25, [sp, #0x20]
0x100006f80:	ldp	x28, x27, [sp, #0x10]
0x100006f84:	add	sp, sp, #0x70
0x100006f88:	retab	

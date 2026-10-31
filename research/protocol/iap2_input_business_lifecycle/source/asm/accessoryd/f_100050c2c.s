; accessoryd 0x100050c2c-0x100050d04; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100050c2c:	pacibsp	
0x100050c30:	stp	x28, x27, [sp, #-0x60]!
0x100050c34:	stp	x26, x25, [sp, #0x10]
0x100050c38:	stp	x24, x23, [sp, #0x20]
0x100050c3c:	stp	x22, x21, [sp, #0x30]
0x100050c40:	stp	x20, x19, [sp, #0x40]
0x100050c44:	stp	x29, x30, [sp, #0x50]
0x100050c48:	add	x29, sp, #0x50
0x100050c4c:	mov	x19, x3
0x100050c50:	mov	x21, x2
0x100050c54:	mov	x20, x1
0x100050c58:	bl	#0x100005238
0x100050c5c:	cbz	w21, #0x100050cd4
0x100050c60:	mov	x24, #0
0x100050c64:	mov	w22, #0
0x100050c68:	ldp	x25, x26, [x0, #0x60]
0x100050c6c:	mov	w23, #1
0x100050c70:	mov	w21, w21
0x100050c74:	add	x8, x24, x24, lsl #1
0x100050c78:	add	x27, x20, x8, lsl #2
0x100050c7c:	ldrh	w1, [x27]
0x100050c80:	ldr	w8, [x27, #4]
0x100050c84:	cmp	w8, #1
0x100050c88:	b.ne	#0x100050c9c
0x100050c8c:	mov	x0, x26
0x100050c90:	cbnz	x26, #0x100050ca4
0x100050c94:	mov	w8, #0
0x100050c98:	b	#0x100050cb0
0x100050c9c:	mov	x0, x25
0x100050ca0:	cbz	x25, #0x100050c94
0x100050ca4:	bl	#0x1001a1890
0x100050ca8:	cmp	w0, #0
0x100050cac:	cset	w8, ne
0x100050cb0:	orr	w22, w22, w8
0x100050cb4:	ldrb	w9, [x27, #8]
0x100050cb8:	eor	w9, w9, #1
0x100050cbc:	orr	w8, w9, w8
0x100050cc0:	and	w23, w23, w8
0x100050cc4:	add	x24, x24, #1
0x100050cc8:	subs	x21, x21, #1
0x100050ccc:	b.ne	#0x100050c74
0x100050cd0:	b	#0x100050cdc
0x100050cd4:	mov	w22, #0
0x100050cd8:	mov	w23, #1
0x100050cdc:	and	w8, w22, #1
0x100050ce0:	strb	w8, [x19]
0x100050ce4:	and	w0, w23, #1
0x100050ce8:	ldp	x29, x30, [sp, #0x50]
0x100050cec:	ldp	x20, x19, [sp, #0x40]
0x100050cf0:	ldp	x22, x21, [sp, #0x30]
0x100050cf4:	ldp	x24, x23, [sp, #0x20]
0x100050cf8:	ldp	x26, x25, [sp, #0x10]
0x100050cfc:	ldp	x28, x27, [sp], #0x60
0x100050d00:	retab	

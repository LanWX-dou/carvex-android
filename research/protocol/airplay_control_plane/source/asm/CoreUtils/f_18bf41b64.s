; CoreUtils 0x18bf41b64-0x18bf41cf8; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18bf41b64:	pacibsp	
0x18bf41b68:	stp	x26, x25, [sp, #-0x50]!
0x18bf41b6c:	stp	x24, x23, [sp, #0x10]
0x18bf41b70:	stp	x22, x21, [sp, #0x20]
0x18bf41b74:	stp	x20, x19, [sp, #0x30]
0x18bf41b78:	stp	x29, x30, [sp, #0x40]
0x18bf41b7c:	add	x29, sp, #0x40
0x18bf41b80:	mov	x22, x3
0x18bf41b84:	mov	x21, x2
0x18bf41b88:	mov	x20, x1
0x18bf41b8c:	mov	x19, x0
0x18bf41b90:	cmn	x3, #1
0x18bf41b94:	b.ne	#0x18bf41ba4
0x18bf41b98:	mov	x0, x21
0x18bf41b9c:	bl	#0x1900d0320
0x18bf41ba0:	mov	x22, x0
0x18bf41ba4:	mov	x8, #-3
0x18bf41ba8:	movk	x8, #0x7fff, lsl #48
0x18bf41bac:	cmp	x22, x8
0x18bf41bb0:	b.hi	#0x18bf41ce0
0x18bf41bb4:	mov	x8, #-0x7f7f7f7f7f7f7f80
0x18bf41bb8:	movk	x8, #0x8081
0x18bf41bbc:	umulh	x8, x22, x8
0x18bf41bc0:	lsr	x8, x8, #7
0x18bf41bc4:	sub	x9, x8, x8, lsl #8
0x18bf41bc8:	cmn	x9, x22
0x18bf41bcc:	cinc	x8, x8, ne
0x18bf41bd0:	add	x8, x22, x8, lsl #1
0x18bf41bd4:	add	x9, x22, #2
0x18bf41bd8:	cmp	x22, #0xff
0x18bf41bdc:	csel	x9, x8, x9, hi
0x18bf41be0:	ldp	x8, x10, [x19, #8]
0x18bf41be4:	add	x0, x8, x9
0x18bf41be8:	cmp	x0, x10
0x18bf41bec:	b.hi	#0x18bf41ce0
0x18bf41bf0:	cmp	x0, x8
0x18bf41bf4:	b.lo	#0x18bf41ce8
0x18bf41bf8:	cmp	x0, #0x12c
0x18bf41bfc:	b.hi	#0x18bf41c0c
0x18bf41c00:	add	x9, x19, #0x20
0x18bf41c04:	add	x24, x9, x8
0x18bf41c08:	b	#0x18bf41c68
0x18bf41c0c:	mov	x1, #0x4924
0x18bf41c10:	movk	x1, #0x7777, lsl #16
0x18bf41c14:	movk	x1, #0x40, lsl #32
0x18bf41c18:	movk	x1, #0x100, lsl #48
0x18bf41c1c:	bl	#0x1900cfd70
0x18bf41c20:	cbz	x0, #0x18bf41cf0
0x18bf41c24:	mov	x23, x0
0x18bf41c28:	ldr	x1, [x19, #0x18]
0x18bf41c2c:	ldr	x2, [x19, #8]
0x18bf41c30:	cbz	x1, #0x18bf41c48
0x18bf41c34:	mov	x0, x23
0x18bf41c38:	bl	#0x1900cc480
0x18bf41c3c:	ldr	x0, [x19, #0x18]
0x18bf41c40:	bl	#0x1900cc3a0
0x18bf41c44:	b	#0x18bf41c58
0x18bf41c48:	cbz	x2, #0x18bf41c58
0x18bf41c4c:	add	x1, x19, #0x20
0x18bf41c50:	mov	x0, x23
0x18bf41c54:	bl	#0x1900cc480
0x18bf41c58:	str	x23, [x19]
0x18bf41c5c:	str	x23, [x19, #0x18]
0x18bf41c60:	ldr	x8, [x19, #8]
0x18bf41c64:	add	x24, x23, x8
0x18bf41c68:	add	x23, x21, x22
0x18bf41c6c:	mov	w25, #0xff
0x18bf41c70:	subs	x8, x23, x21
0x18bf41c74:	cmp	x8, #0xff
0x18bf41c78:	csel	x22, x8, x25, lo
0x18bf41c7c:	strb	w20, [x24]
0x18bf41c80:	strb	w22, [x24, #1]
0x18bf41c84:	cmp	x23, x21
0x18bf41c88:	b.eq	#0x18bf41c9c
0x18bf41c8c:	add	x0, x24, #2
0x18bf41c90:	mov	x1, x21
0x18bf41c94:	mov	x2, x22
0x18bf41c98:	bl	#0x1900cc480
0x18bf41c9c:	add	x9, x21, x22
0x18bf41ca0:	add	x10, x22, #2
0x18bf41ca4:	add	x8, x24, x10
0x18bf41ca8:	mov	x24, x8
0x18bf41cac:	cmp	x9, x23
0x18bf41cb0:	mov	x21, x9
0x18bf41cb4:	b.ne	#0x18bf41c70
0x18bf41cb8:	mov	w0, #0
0x18bf41cbc:	ldr	x9, [x19]
0x18bf41cc0:	sub	x8, x8, x9
0x18bf41cc4:	str	x8, [x19, #8]
0x18bf41cc8:	ldp	x29, x30, [sp, #0x40]
0x18bf41ccc:	ldp	x20, x19, [sp, #0x30]
0x18bf41cd0:	ldp	x22, x21, [sp, #0x20]
0x18bf41cd4:	ldp	x24, x23, [sp, #0x10]
0x18bf41cd8:	ldp	x26, x25, [sp], #0x50
0x18bf41cdc:	retab	
0x18bf41ce0:	mov	w0, #-0x1a57
0x18bf41ce4:	b	#0x18bf41cc8
0x18bf41ce8:	mov	w0, #-0x1a5f
0x18bf41cec:	b	#0x18bf41cc8
0x18bf41cf0:	mov	w0, #-0x1a48
0x18bf41cf4:	b	#0x18bf41cc8

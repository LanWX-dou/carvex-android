; AirPlaySender 0x2519c8f04-0x2519c9018; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519c8f04:	pacibsp	
0x2519c8f08:	sub	sp, sp, #0x40
0x2519c8f0c:	stp	x22, x21, [sp, #0x10]
0x2519c8f10:	stp	x20, x19, [sp, #0x20]
0x2519c8f14:	stp	x29, x30, [sp, #0x30]
0x2519c8f18:	add	x29, sp, #0x30
0x2519c8f1c:	mov	x20, x3
0x2519c8f20:	mov	x21, x2
0x2519c8f24:	mov	x22, x1
0x2519c8f28:	mov	x19, x0
0x2519c8f2c:	bl	#0x25810ac50
0x2519c8f30:	ldrb	w8, [x0]
0x2519c8f34:	cbnz	w8, #0x2519c8ff8
0x2519c8f38:	mov	x1, sp
0x2519c8f3c:	mov	x0, x19
0x2519c8f40:	bl	#0x2519c8d58
0x2519c8f44:	ldr	x19, [sp]
0x2519c8f48:	cbz	x19, #0x2519c9008
0x2519c8f4c:	mov	x0, x19
0x2519c8f50:	bl	#0x258109150
0x2519c8f54:	ldr	x16, [x0, #0x10]!
0x2519c8f58:	mov	x17, x0
0x2519c8f5c:	movk	x17, #0x5584, lsl #48
0x2519c8f60:	autda	x16, x17
0x2519c8f64:	ldr	x9, [x16, #0x20]!
0x2519c8f68:	cbz	x9, #0x2519c8fbc
0x2519c8f6c:	mov	x8, x16
0x2519c8f70:	movk	x8, #0xd6b7, lsl #48
0x2519c8f74:	mov	x16, x9
0x2519c8f78:	mov	x17, x8
0x2519c8f7c:	autia	x16, x17
0x2519c8f80:	mov	x17, x16
0x2519c8f84:	xpaci	x17
0x2519c8f88:	cmp	x16, x17
0x2519c8f8c:	b.eq	#0x2519c8f94
0x2519c8f90:	brk	#0xc470
0x2519c8f94:	paciza	x16
0x2519c8f98:	cbz	x16, #0x2519c8fbc
0x2519c8f9c:	mov	x0, x19
0x2519c8fa0:	mov	x1, x22
0x2519c8fa4:	mov	x2, x21
0x2519c8fa8:	mov	x3, x20
0x2519c8fac:	blraa	x9, x8
0x2519c8fb0:	mov	x20, x0
0x2519c8fb4:	cbnz	w0, #0x2519c8fc0
0x2519c8fb8:	b	#0x2519c8fd8
0x2519c8fbc:	mov	w20, #-0x31ee
0x2519c8fc0:	adrp	x1, #0x251bf6000
0x2519c8fc4:	add	x1, x1, #0xb5d
0x2519c8fc8:	mov	x0, x20
0x2519c8fcc:	mov	w2, #0x2174
0x2519c8fd0:	mov	w3, #0
0x2519c8fd4:	bl	#0x258109a30
0x2519c8fd8:	mov	x0, x19
0x2519c8fdc:	bl	#0x2580f5830
0x2519c8fe0:	mov	x0, x20
0x2519c8fe4:	ldp	x29, x30, [sp, #0x30]
0x2519c8fe8:	ldp	x20, x19, [sp, #0x20]
0x2519c8fec:	ldp	x22, x21, [sp, #0x10]
0x2519c8ff0:	add	sp, sp, #0x40
0x2519c8ff4:	retab	
0x2519c8ff8:	add	x0, sp, #0xc
0x2519c8ffc:	bl	#0x251b5ff64
0x2519c9000:	ldr	w20, [sp, #0xc]
0x2519c9004:	b	#0x2519c8fe0
0x2519c9008:	bl	#0x251b5ffa4
0x2519c900c:	mov	w20, #0xe76b
0x2519c9010:	movk	w20, #0xfffe, lsl #16
0x2519c9014:	b	#0x2519c8fe0

; accessoryd 0x10013ec58-0x10013ed5c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10013ec58:	pacibsp	
0x10013ec5c:	sub	sp, sp, #0x40
0x10013ec60:	stp	x22, x21, [sp, #0x10]
0x10013ec64:	stp	x20, x19, [sp, #0x20]
0x10013ec68:	stp	x29, x30, [sp, #0x30]
0x10013ec6c:	add	x29, sp, #0x30
0x10013ec70:	mov	x20, x1
0x10013ec74:	mov	x19, x0
0x10013ec78:	bl	#0x100015560
0x10013ec7c:	bl	#0x100003650
0x10013ec80:	ldr	x21, [x11, #8]
0x10013ec84:	cmp	w12, w20
0x10013ec88:	ccmp	x21, #0, #4, eq
0x10013ec8c:	b.eq	#0x10013ec98
0x10013ec90:	ldr	x11, [x21]
0x10013ec94:	cbnz	x11, #0x10013eca8
0x10013ec98:	add	x8, x8, #1
0x10013ec9c:	subs	x9, x9, #1
0x10013eca0:	b.ne	#0x10013ec7c
0x10013eca4:	b	#0x10013ed38
0x10013eca8:	ldrb	w8, [x21, #0x22]
0x10013ecac:	tbnz	w8, #0, #0x10013ecc4
0x10013ecb0:	mov	x0, x19
0x10013ecb4:	mov	x1, x20
0x10013ecb8:	bl	#0x10013c0ec
0x10013ecbc:	cbz	w0, #0x10013ed38
0x10013ecc0:	ldr	x11, [x21]
0x10013ecc4:	ldr	x22, [x11, #0x10]
0x10013ecc8:	cbz	x22, #0x10013ed38
0x10013eccc:	adrp	x8, #0x10023f000
0x10013ecd0:	ldr	x8, [x8, #0xa28]
0x10013ecd4:	cbz	x8, #0x10013ece8
0x10013ecd8:	bl	#0x10000962c
0x10013ecdc:	b.lt	#0x10013ece8
0x10013ece0:	ldr	x21, [x8, #0xa8]
0x10013ece4:	b	#0x10013ecf4
0x10013ece8:	bl	#0x10000c2f4
0x10013ecec:	b.ne	#0x10013ed50
0x10013ecf0:	bl	#0x100003370
0x10013ecf4:	mov	x0, x21
0x10013ecf8:	mov	w1, #1
0x10013ecfc:	bl	#0x1001a2830
0x10013ed00:	cbz	w0, #0x10013ed30
0x10013ed04:	adrp	x8, #0x1001b3000
0x10013ed08:	ldr	d0, [x8, #0xb0]
0x10013ed0c:	str	s0, [sp]
0x10013ed10:	str	w20, [sp, #4]
0x10013ed14:	bl	#0x100003474
0x10013ed18:	adrp	x3, #0x1001e9000
0x10013ed1c:	add	x3, x3, #0x602
0x10013ed20:	mov	x4, sp
0x10013ed24:	bl	#0x100004c64
0x10013ed28:	mov	w5, #8
0x10013ed2c:	bl	#0x1001a1fe0
0x10013ed30:	mov	x0, x19
0x10013ed34:	blraaz	x22
0x10013ed38:	mov	w0, #0
0x10013ed3c:	ldp	x29, x30, [sp, #0x30]
0x10013ed40:	ldp	x20, x19, [sp, #0x20]
0x10013ed44:	ldp	x22, x21, [sp, #0x10]
0x10013ed48:	add	sp, sp, #0x40
0x10013ed4c:	retab	
0x10013ed50:	bl	#0x100015e84
0x10013ed54:	bl	#0x1001a2140
0x10013ed58:	b	#0x10013ecf0

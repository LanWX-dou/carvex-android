; accessoryd 0x10008eb68-0x10008ece8; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008eb68:	pacibsp	
0x10008eb6c:	sub	sp, sp, #0x40
0x10008eb70:	stp	x20, x19, [sp, #0x20]
0x10008eb74:	stp	x29, x30, [sp, #0x30]
0x10008eb78:	add	x29, sp, #0x30
0x10008eb7c:	mov	x19, x0
0x10008eb80:	ldrh	w8, [x0]
0x10008eb84:	ldrh	w9, [x0, #2]
0x10008eb88:	cmp	w8, w9
0x10008eb8c:	b.hs	#0x10008ebb8
0x10008eb90:	ldr	x9, [x19, #8]
0x10008eb94:	strb	w1, [x9, w8, uxtw]
0x10008eb98:	ldrh	w10, [x19]
0x10008eb9c:	add	w8, w10, #1
0x10008eba0:	and	w9, w8, #0xffff
0x10008eba4:	strh	w8, [x19]
0x10008eba8:	cmp	w9, w8
0x10008ebac:	b.eq	#0x10008ec00
0x10008ebb0:	mov	x0, #0
0x10008ebb4:	b	#0x10008ecd0
0x10008ebb8:	adrp	x8, #0x10023d000
0x10008ebbc:	add	x8, x8, #0x280
0x10008ebc0:	ldrb	w8, [x8]
0x10008ebc4:	tbz	w8, #0, #0x10008ecc8
0x10008ebc8:	adrp	x8, #0x10023f000
0x10008ebcc:	ldr	x8, [x8, #0xa28]
0x10008ebd0:	adrp	x9, #0x10023f000
0x10008ebd4:	ldr	w9, [x9, #0xa30]
0x10008ebd8:	cmp	x8, #0
0x10008ebdc:	ccmp	w9, #0x17, #8, ne
0x10008ebe0:	b.ge	#0x10008ec50
0x10008ebe4:	adrp	x8, #0x10023e000
0x10008ebe8:	ldr	x8, [x8, #0x8e8]
0x10008ebec:	cmn	x8, #1
0x10008ebf0:	b.ne	#0x10008ece0
0x10008ebf4:	adrp	x20, #0x10022b000
0x10008ebf8:	ldr	x20, [x20, #0xbb0]
0x10008ebfc:	b	#0x10008ec54
0x10008ec00:	ldrh	w1, [x19, #0x18]
0x10008ec04:	ldr	x8, [x19, #8]
0x10008ec08:	ldrb	w11, [x8]
0x10008ec0c:	cmp	w11, w1, lsr #8
0x10008ec10:	b.ne	#0x10008ecc8
0x10008ec14:	cbz	w10, #0x10008ebb0
0x10008ec18:	ldrb	w10, [x8, #1]
0x10008ec1c:	cmp	w10, w1, uxtb
0x10008ec20:	b.ne	#0x10008ecc8
0x10008ec24:	cmp	w9, #4
0x10008ec28:	b.lo	#0x10008ebb0
0x10008ec2c:	ldrh	w10, [x8, #2]
0x10008ec30:	rev	w10, w10
0x10008ec34:	cmp	w9, w10, lsr #16
0x10008ec38:	b.ne	#0x10008ebb0
0x10008ec3c:	ldrh	w3, [x19, #2]
0x10008ec40:	mov	x0, x2
0x10008ec44:	mov	x2, x8
0x10008ec48:	bl	#0x10008ece8
0x10008ec4c:	b	#0x10008eccc
0x10008ec50:	ldr	x20, [x8, #0xb0]
0x10008ec54:	mov	x0, x20
0x10008ec58:	mov	w1, #0
0x10008ec5c:	bl	#0x1001a2830
0x10008ec60:	cbz	w0, #0x10008ecc8
0x10008ec64:	ldrh	w8, [x19]
0x10008ec68:	ldrh	w9, [x19, #2]
0x10008ec6c:	adrp	x10, #0x1001b3000
0x10008ec70:	ldr	d0, [x10, #0xe0]
0x10008ec74:	str	s0, [sp]
0x10008ec78:	adrp	x10, #0x1001d2000
0x10008ec7c:	add	x10, x10, #0xf9
0x10008ec80:	stur	x10, [sp, #4]
0x10008ec84:	mov	w10, #0x400
0x10008ec88:	strh	w10, [sp, #0xc]
0x10008ec8c:	mov	w11, #0x86
0x10008ec90:	stur	w11, [sp, #0xe]
0x10008ec94:	strh	w10, [sp, #0x12]
0x10008ec98:	str	w8, [sp, #0x14]
0x10008ec9c:	strh	w10, [sp, #0x18]
0x10008eca0:	stur	w9, [sp, #0x1a]
0x10008eca4:	adrp	x0, #0x100000000
0x10008eca8:	add	x0, x0, #0
0x10008ecac:	adrp	x3, #0x1001f3000
0x10008ecb0:	add	x3, x3, #0xcc0
0x10008ecb4:	mov	x4, sp
0x10008ecb8:	mov	x1, x20
0x10008ecbc:	mov	w2, #0
0x10008ecc0:	mov	w5, #0x1e
0x10008ecc4:	bl	#0x1001a1fe0
0x10008ecc8:	mov	x0, #0
0x10008eccc:	strh	wzr, [x19]
0x10008ecd0:	ldp	x29, x30, [sp, #0x30]
0x10008ecd4:	ldp	x20, x19, [sp, #0x20]
0x10008ecd8:	add	sp, sp, #0x40
0x10008ecdc:	retab	
0x10008ece0:	bl	#0x10014f034
0x10008ece4:	b	#0x10008ebf4

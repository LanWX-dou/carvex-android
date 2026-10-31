; accessoryd 0x100034e68-0x100034f1c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100034e68:	pacibsp	
0x100034e6c:	stp	x20, x19, [sp, #-0x20]!
0x100034e70:	stp	x29, x30, [sp, #0x10]
0x100034e74:	add	x29, sp, #0x10
0x100034e78:	mov	x19, x0
0x100034e7c:	adrp	x8, #0x10023d000
0x100034e80:	add	x8, x8, #0x280
0x100034e84:	ldrb	w8, [x8]
0x100034e88:	tbz	w8, #2, #0x100034ed8
0x100034e8c:	adrp	x8, #0x10023f000
0x100034e90:	ldr	x8, [x8, #0xa28]
0x100034e94:	adrp	x9, #0x10023f000
0x100034e98:	ldr	w9, [x9, #0xa30]
0x100034e9c:	cmp	x8, #0
0x100034ea0:	ccmp	w9, #0x17, #8, ne
0x100034ea4:	b.ge	#0x100034ec4
0x100034ea8:	adrp	x8, #0x10023e000
0x100034eac:	ldr	x8, [x8, #0x580]
0x100034eb0:	cmn	x8, #1
0x100034eb4:	b.ne	#0x100034f14
0x100034eb8:	adrp	x20, #0x10022b000
0x100034ebc:	ldr	x20, [x20, #0xbb0]
0x100034ec0:	b	#0x100034ec8
0x100034ec4:	ldr	x20, [x8, #0xb0]
0x100034ec8:	mov	x0, x20
0x100034ecc:	mov	w1, #2
0x100034ed0:	bl	#0x1001a2830
0x100034ed4:	cbnz	w0, #0x100034f04
0x100034ed8:	cbz	x19, #0x100034ef8
0x100034edc:	ldr	x0, [x19, #8]
0x100034ee0:	cbz	x0, #0x100034ef8
0x100034ee4:	ldr	w8, [x19, #0xb8]
0x100034ee8:	cmp	w8, #1
0x100034eec:	b.ne	#0x100034ef8
0x100034ef0:	mov	w1, #0x1c
0x100034ef4:	bl	#0x10000639c
0x100034ef8:	ldp	x29, x30, [sp, #0x10]
0x100034efc:	ldp	x20, x19, [sp], #0x20
0x100034f00:	retab	
0x100034f04:	mov	x0, x19
0x100034f08:	mov	x1, x20
0x100034f0c:	bl	#0x10012bad8
0x100034f10:	b	#0x100034edc
0x100034f14:	bl	#0x10012b6d4
0x100034f18:	b	#0x100034eb8

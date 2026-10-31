; accessoryd 0x100034db4-0x100034e68; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100034db4:	pacibsp	
0x100034db8:	stp	x20, x19, [sp, #-0x20]!
0x100034dbc:	stp	x29, x30, [sp, #0x10]
0x100034dc0:	add	x29, sp, #0x10
0x100034dc4:	mov	x19, x0
0x100034dc8:	adrp	x8, #0x10023d000
0x100034dcc:	add	x8, x8, #0x280
0x100034dd0:	ldrb	w8, [x8]
0x100034dd4:	tbz	w8, #2, #0x100034e24
0x100034dd8:	adrp	x8, #0x10023f000
0x100034ddc:	ldr	x8, [x8, #0xa28]
0x100034de0:	adrp	x9, #0x10023f000
0x100034de4:	ldr	w9, [x9, #0xa30]
0x100034de8:	cmp	x8, #0
0x100034dec:	ccmp	w9, #0x17, #8, ne
0x100034df0:	b.ge	#0x100034e10
0x100034df4:	adrp	x8, #0x10023e000
0x100034df8:	ldr	x8, [x8, #0x580]
0x100034dfc:	cmn	x8, #1
0x100034e00:	b.ne	#0x100034e60
0x100034e04:	adrp	x20, #0x10022b000
0x100034e08:	ldr	x20, [x20, #0xbb0]
0x100034e0c:	b	#0x100034e14
0x100034e10:	ldr	x20, [x8, #0xb0]
0x100034e14:	mov	x0, x20
0x100034e18:	mov	w1, #2
0x100034e1c:	bl	#0x1001a2830
0x100034e20:	cbnz	w0, #0x100034e50
0x100034e24:	cbz	x19, #0x100034e44
0x100034e28:	ldr	x0, [x19, #8]
0x100034e2c:	cbz	x0, #0x100034e44
0x100034e30:	ldr	w8, [x19, #0xb8]
0x100034e34:	cmp	w8, #1
0x100034e38:	b.ne	#0x100034e44
0x100034e3c:	mov	w1, #0x1b
0x100034e40:	bl	#0x10000639c
0x100034e44:	ldp	x29, x30, [sp, #0x10]
0x100034e48:	ldp	x20, x19, [sp], #0x20
0x100034e4c:	retab	
0x100034e50:	mov	x0, x19
0x100034e54:	mov	x1, x20
0x100034e58:	bl	#0x10012ba60
0x100034e5c:	b	#0x100034e28
0x100034e60:	bl	#0x10012b6d4
0x100034e64:	b	#0x100034e04

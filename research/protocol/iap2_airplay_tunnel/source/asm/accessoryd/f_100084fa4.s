; accessoryd 0x100084fa4-0x100085034; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100084fa4:	cbz	x1, #0x100085014
0x100084fa8:	pacibsp	
0x100084fac:	stp	x22, x21, [sp, #-0x30]!
0x100084fb0:	stp	x20, x19, [sp, #0x10]
0x100084fb4:	stp	x29, x30, [sp, #0x20]
0x100084fb8:	add	x29, sp, #0x20
0x100084fbc:	mov	x21, x1
0x100084fc0:	mov	x19, x0
0x100084fc4:	ldrh	w20, [x0, #0x150]
0x100084fc8:	mov	x1, #0xafe2
0x100084fcc:	movk	x1, #0x66c3, lsl #16
0x100084fd0:	movk	x1, #0x40, lsl #32
0x100084fd4:	movk	x1, #0x109, lsl #48
0x100084fd8:	mov	w0, #0x48
0x100084fdc:	bl	#0x1001a2370
0x100084fe0:	str	x0, [x21]
0x100084fe4:	cbz	x0, #0x10008501c
0x100084fe8:	ldr	x3, [x19, #0x10]
0x100084fec:	ldr	w4, [x19, #0x18]
0x100084ff0:	mov	w21, #0x5163
0x100084ff4:	mov	x1, x20
0x100084ff8:	mov	w2, #0x5163
0x100084ffc:	mov	x5, #0
0x100085000:	mov	x6, #0
0x100085004:	bl	#0x100068004
0x100085008:	mov	w0, #0
0x10008500c:	strh	w21, [x19, #0x1c]
0x100085010:	b	#0x100085020
0x100085014:	mov	w0, #1
0x100085018:	ret	
0x10008501c:	mov	w0, #-1
0x100085020:	ldp	x29, x30, [sp, #0x20]
0x100085024:	ldp	x20, x19, [sp, #0x10]
0x100085028:	ldp	x22, x21, [sp], #0x30
0x10008502c:	autibsp	
0x100085030:	ret	

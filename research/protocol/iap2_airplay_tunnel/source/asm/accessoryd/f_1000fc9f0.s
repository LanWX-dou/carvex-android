; accessoryd 0x1000fc9f0-0x1000fcac4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000fc9f0:	pacibsp	
0x1000fc9f4:	sub	sp, sp, #0x80
0x1000fc9f8:	stp	x20, x19, [sp, #0x60]
0x1000fc9fc:	stp	x29, x30, [sp, #0x70]
0x1000fca00:	add	x29, sp, #0x70
0x1000fca04:	sub	x8, x29, #0x30
0x1000fca08:	stp	xzr, x8, [x29, #-0x30]
0x1000fca0c:	adrp	x8, #0x1001b3000
0x1000fca10:	ldr	d0, [x8, #0x120]
0x1000fca14:	stur	d0, [x29, #-0x20]
0x1000fca18:	mov	w19, #0x13
0x1000fca1c:	stur	w19, [x29, #-0x18]
0x1000fca20:	cbz	x0, #0x1000fca8c
0x1000fca24:	cbz	x1, #0x1000fca8c
0x1000fca28:	add	x8, sp, #8
0x1000fca2c:	adrp	x16, #0x10022b000
0x1000fca30:	ldr	x16, [x16, #0xb78]
0x1000fca34:	mov	x17, x8
0x1000fca38:	movk	x17, #0x6ae1, lsl #48
0x1000fca3c:	pacda	x16, x17
0x1000fca40:	str	x16, [sp, #8]
0x1000fca44:	adrp	x9, #0x1001b3000
0x1000fca48:	ldr	d0, [x9, #0x78]
0x1000fca4c:	str	d0, [sp, #0x10]
0x1000fca50:	add	x8, x8, #0x10
0x1000fca54:	adrp	x16, #0x100195000
0x1000fca58:	add	x16, x16, #0xec4
0x1000fca5c:	pacia	x16, x8
0x1000fca60:	adrp	x8, #0x100220000
0x1000fca64:	add	x8, x8, #0xdb0
0x1000fca68:	stp	x16, x8, [sp, #0x18]
0x1000fca6c:	sub	x8, x29, #0x30
0x1000fca70:	stp	x8, x0, [sp, #0x28]
0x1000fca74:	str	x1, [sp, #0x38]
0x1000fca78:	add	x1, sp, #8
0x1000fca7c:	mov	x2, #0
0x1000fca80:	bl	#0x1000f8934
0x1000fca84:	ldur	x8, [x29, #-0x28]
0x1000fca88:	ldr	w19, [x8, #0x18]
0x1000fca8c:	sub	x0, x29, #0x30
0x1000fca90:	mov	w1, #8
0x1000fca94:	bl	#0x1001a1f10
0x1000fca98:	mov	x0, x19
0x1000fca9c:	ldp	x29, x30, [sp, #0x70]
0x1000fcaa0:	ldp	x20, x19, [sp, #0x60]
0x1000fcaa4:	add	sp, sp, #0x80
0x1000fcaa8:	retab	
0x1000fcaac:	mov	x19, x0
0x1000fcab0:	sub	x0, x29, #0x30
0x1000fcab4:	mov	w1, #8
0x1000fcab8:	bl	#0x1001a1f10
0x1000fcabc:	mov	x0, x19
0x1000fcac0:	bl	#0x1001a1f30

; accessoryd 0x100034bbc-0x100034c1c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100034bbc:	cbz	x0, #0x100034c18
0x100034bc0:	pacibsp	
0x100034bc4:	stp	x20, x19, [sp, #-0x20]!
0x100034bc8:	stp	x29, x30, [sp, #0x10]
0x100034bcc:	add	x29, sp, #0x10
0x100034bd0:	mov	x19, x0
0x100034bd4:	ldr	x0, [x0, #8]
0x100034bd8:	mov	w1, #0xe
0x100034bdc:	bl	#0x10000639c
0x100034be0:	add	x8, x19, #0x19a
0x100034be4:	add	x9, x19, #0x19e
0x100034be8:	mov	w10, #0x3e8ffff
0x100034bec:	str	w10, [x9]
0x100034bf0:	mov	w9, #0xa
0x100034bf4:	strh	w9, [x19, #0x1a2]
0x100034bf8:	adrp	x9, #0x1001b3000
0x100034bfc:	ldr	d0, [x9, #0x348]
0x100034c00:	str	s0, [x8]
0x100034c04:	mov	w8, #-0xff00
0x100034c08:	str	w8, [x19, #0x1a4]
0x100034c0c:	ldp	x29, x30, [sp, #0x10]
0x100034c10:	ldp	x20, x19, [sp], #0x20
0x100034c14:	autibsp	
0x100034c18:	ret	

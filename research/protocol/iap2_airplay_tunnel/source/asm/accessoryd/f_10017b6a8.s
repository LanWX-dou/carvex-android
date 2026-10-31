; accessoryd 0x10017b6a8-0x10017b6e4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10017b6a8:	pacibsp	
0x10017b6ac:	stp	x20, x19, [sp, #-0x20]!
0x10017b6b0:	stp	x29, x30, [sp, #0x10]
0x10017b6b4:	add	x29, sp, #0x10
0x10017b6b8:	mov	x19, x0
0x10017b6bc:	cbz	x0, #0x10017b6d0
0x10017b6c0:	ldr	x0, [x19]
0x10017b6c4:	cbz	x0, #0x10017b6d0
0x10017b6c8:	bl	#0x1001a22d0
0x10017b6cc:	str	xzr, [x19]
0x10017b6d0:	cmp	x19, #0
0x10017b6d4:	cset	w0, ne
0x10017b6d8:	ldp	x29, x30, [sp, #0x10]
0x10017b6dc:	ldp	x20, x19, [sp], #0x20
0x10017b6e0:	retab	

; accessoryd 0x10000a488-0x10000a4fc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10000a488:	pacibsp	
0x10000a48c:	stp	x20, x19, [sp, #-0x20]!
0x10000a490:	stp	x29, x30, [sp, #0x10]
0x10000a494:	add	x29, sp, #0x10
0x10000a498:	mov	x19, x0
0x10000a49c:	ldr	x20, [x0, #0xf0]
0x10000a4a0:	mov	x1, #0
0x10000a4a4:	bl	#0x100034a40
0x10000a4a8:	mov	w1, w0
0x10000a4ac:	mov	x0, x20
0x10000a4b0:	bl	#0x100007088
0x10000a4b4:	mov	x20, x0
0x10000a4b8:	cbz	x0, #0x10000a4ec
0x10000a4bc:	ldurh	w8, [x20, #0x3d]
0x10000a4c0:	mov	w9, #0x1ff
0x10000a4c4:	sturh	w9, [x20, #0x3b]
0x10000a4c8:	strb	wzr, [x20, #0x3f]
0x10000a4cc:	mov	w9, #0xf5ff
0x10000a4d0:	and	w8, w8, w9
0x10000a4d4:	stp	xzr, xzr, [x20, #8]
0x10000a4d8:	str	x19, [x20]
0x10000a4dc:	sturh	w8, [x20, #0x3d]
0x10000a4e0:	str	xzr, [x20, #0x20]
0x10000a4e4:	mov	x0, x20
0x10000a4e8:	bl	#0x10000713c
0x10000a4ec:	mov	x0, x20
0x10000a4f0:	ldp	x29, x30, [sp, #0x10]
0x10000a4f4:	ldp	x20, x19, [sp], #0x20
0x10000a4f8:	retab	

; accessoryd 0x100003424-0x100003474; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100003424:	cbz	x0, #0x100003470
0x100003428:	movi	v0.2d, #0000000000000000
0x10000342c:	stp	q0, q0, [x0, #0x20]
0x100003430:	str	xzr, [x0, #0x40]
0x100003434:	stp	q0, q0, [x0]
0x100003438:	str	x2, [x0, #0x18]
0x10000343c:	str	w3, [x0, #0x10]
0x100003440:	stp	x4, x5, [x0, #0x28]
0x100003444:	cbz	x2, #0x100003468
0x100003448:	adrp	x8, #0x1001b3000
0x10000344c:	ldr	d0, [x8, #0xad0]
0x100003450:	str	s0, [x2]
0x100003454:	lsr	w8, w1, #8
0x100003458:	strb	w8, [x2, #4]
0x10000345c:	strb	w1, [x2, #5]
0x100003460:	add	x8, x2, #6
0x100003464:	b	#0x10000346c
0x100003468:	mov	x8, #0
0x10000346c:	str	x8, [x0, #0x20]
0x100003470:	ret	

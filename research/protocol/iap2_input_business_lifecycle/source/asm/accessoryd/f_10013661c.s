; accessoryd 0x10013661c-0x1001366f4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10013661c:	cbz	x0, #0x1001366e0
0x100136620:	pacibsp	
0x100136624:	stp	x22, x21, [sp, #-0x30]!
0x100136628:	stp	x20, x19, [sp, #0x10]
0x10013662c:	stp	x29, x30, [sp, #0x20]
0x100136630:	add	x29, sp, #0x20
0x100136634:	mov	x19, x0
0x100136638:	mov	x1, #0x28dd
0x10013663c:	movk	x1, #0xe72c, lsl #16
0x100136640:	movk	x1, #0x40, lsl #32
0x100136644:	movk	x1, #0x109, lsl #48
0x100136648:	mov	w0, #0xa8
0x10013664c:	bl	#0x1001a2370
0x100136650:	cbz	x0, #0x1001366d0
0x100136654:	mov	x20, x0
0x100136658:	mov	x2, #0xbd0f
0x10013665c:	movk	x2, #0x1884, lsl #16
0x100136660:	movk	x2, #0x40, lsl #32
0x100136664:	movk	x2, #0x102, lsl #48
0x100136668:	mov	w0, #1
0x10013666c:	mov	w1, #0x50
0x100136670:	bl	#0x1001a2360
0x100136674:	cbz	x0, #0x1001366e4
0x100136678:	mov	x21, x0
0x10013667c:	str	x19, [x0]
0x100136680:	adrp	x0, #0x1001cd000
0x100136684:	add	x0, x0, #0xa0c
0x100136688:	mov	x1, #0
0x10013668c:	bl	#0x1001a2160
0x100136690:	str	x0, [x21, #0x40]
0x100136694:	str	x21, [x20, #0x20]
0x100136698:	str	wzr, [x20]
0x10013669c:	mov	w8, #2
0x1001366a0:	strh	w8, [x20, #4]
0x1001366a4:	str	xzr, [x20, #0x10]
0x1001366a8:	strh	wzr, [x20, #0x18]
0x1001366ac:	str	wzr, [x20, #8]
0x1001366b0:	stp	xzr, xzr, [x20, #0x58]
0x1001366b4:	str	xzr, [x20, #0x50]
0x1001366b8:	strb	wzr, [x20, #0x68]
0x1001366bc:	str	w8, [x20, #0x6c]
0x1001366c0:	strb	wzr, [x20, #0x70]
0x1001366c4:	str	wzr, [x20, #0x74]
0x1001366c8:	mov	w0, #1
0x1001366cc:	str	x20, [x19, #0x1c8]
0x1001366d0:	ldp	x29, x30, [sp, #0x20]
0x1001366d4:	ldp	x20, x19, [sp, #0x10]
0x1001366d8:	ldp	x22, x21, [sp], #0x30
0x1001366dc:	autibsp	
0x1001366e0:	ret	
0x1001366e4:	mov	x0, x20
0x1001366e8:	bl	#0x1001a22d0
0x1001366ec:	mov	w0, #0
0x1001366f0:	b	#0x1001366d0

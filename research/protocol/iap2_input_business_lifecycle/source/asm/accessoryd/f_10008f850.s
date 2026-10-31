; accessoryd 0x10008f850-0x10008f8a4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008f850:	pacibsp	
0x10008f854:	sub	sp, sp, #0x20
0x10008f858:	stp	x29, x30, [sp, #0x10]
0x10008f85c:	add	x29, sp, #0x10
0x10008f860:	adrp	x8, #0x10023e000
0x10008f864:	mov	w9, #1
0x10008f868:	strb	w9, [x8, #0x908]
0x10008f86c:	bl	#0x10008f3b8
0x10008f870:	bl	#0x1001a2490
0x10008f874:	str	x0, [sp, #8]
0x10008f878:	adrp	x2, #0x10021c000
0x10008f87c:	add	x2, x2, #0x978
0x10008f880:	bl	#0x1001a9640
0x10008f884:	ldr	x0, [sp, #8]
0x10008f888:	ldp	x29, x30, [sp, #0x10]
0x10008f88c:	add	sp, sp, #0x20
0x10008f890:	autibsp	
0x10008f894:	eor	x16, x30, x30, lsl #1
0x10008f898:	tbz	x16, #0x3e, #0x10008f8a0
0x10008f89c:	brk	#0xc471
0x10008f8a0:	b	#0x1001a2540

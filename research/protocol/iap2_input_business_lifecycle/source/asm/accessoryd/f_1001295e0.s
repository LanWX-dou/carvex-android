; accessoryd 0x1001295e0-0x10012961c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1001295e0:	cbz	x0, #0x100129614
0x1001295e4:	strb	w1, [x0, #0x1c0]
0x1001295e8:	ldr	x0, [x0]
0x1001295ec:	cbz	x0, #0x100129614
0x1001295f0:	adrp	x8, #0x10022b000
0x1001295f4:	ldr	x8, [x8, #0x978]
0x1001295f8:	ldr	x8, [x8]
0x1001295fc:	cbz	w1, #0x10012960c
0x100129600:	mov	x1, x8
0x100129604:	mov	x2, #0
0x100129608:	b	#0x10018cd30
0x10012960c:	mov	x1, x8
0x100129610:	b	#0x10018d6b4
0x100129614:	mov	w0, #0
0x100129618:	ret	

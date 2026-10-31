; accessoryd 0x100032828-0x10003286c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100032828:	cbz	x0, #0x100032860
0x10003282c:	mov	x8, x0
0x100032830:	ldrb	w9, [x0, #0x1a4]
0x100032834:	cbz	x9, #0x100032864
0x100032838:	mov	x10, #0
0x10003283c:	mov	x0, #0
0x100032840:	add	x8, x8, #0x1b8
0x100032844:	add	x11, x8, x10, lsl #2
0x100032848:	ldrb	w12, [x11]
0x10003284c:	cmp	w12, w1
0x100032850:	csel	x0, x11, x0, eq
0x100032854:	add	x10, x10, #1
0x100032858:	subs	x9, x9, #1
0x10003285c:	b.ne	#0x100032844
0x100032860:	ret	
0x100032864:	mov	x0, #0
0x100032868:	ret	

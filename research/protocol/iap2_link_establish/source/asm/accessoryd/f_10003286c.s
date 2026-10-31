; accessoryd 0x10003286c-0x1000328b0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10003286c:	pacibsp	
0x100032870:	stp	x29, x30, [sp, #-0x10]!
0x100032874:	mov	x29, sp
0x100032878:	cbz	x0, #0x1000328a8
0x10003287c:	cbz	x1, #0x1000328ac
0x100032880:	mov	w8, #0x1d
0x100032884:	strb	w8, [x1]
0x100032888:	ldr	x0, [x0, #0x10]
0x10003288c:	mov	w1, #0
0x100032890:	ldp	x29, x30, [sp], #0x10
0x100032894:	autibsp	
0x100032898:	eor	x16, x30, x30, lsl #1
0x10003289c:	tbz	x16, #0x3e, #0x1000328a4
0x1000328a0:	brk	#0xc471
0x1000328a4:	b	#0x100103970
0x1000328a8:	bl	#0x10012b82c
0x1000328ac:	bl	#0x10012b804

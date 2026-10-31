; accessoryd 0x10008fcb0-0x10008fcf0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008fcb0:	pacibsp	
0x10008fcb4:	sub	sp, sp, #0x20
0x10008fcb8:	stp	x29, x30, [sp, #0x10]
0x10008fcbc:	add	x29, sp, #0x10
0x10008fcc0:	bl	#0x10008f3b8
0x10008fcc4:	bl	#0x1001a2490
0x10008fcc8:	str	x0, [sp, #8]
0x10008fccc:	bl	#0x1001a5f60
0x10008fcd0:	ldr	x0, [sp, #8]
0x10008fcd4:	ldp	x29, x30, [sp, #0x10]
0x10008fcd8:	add	sp, sp, #0x20
0x10008fcdc:	autibsp	
0x10008fce0:	eor	x16, x30, x30, lsl #1
0x10008fce4:	tbz	x16, #0x3e, #0x10008fcec
0x10008fce8:	brk	#0xc471
0x10008fcec:	b	#0x1001a2540

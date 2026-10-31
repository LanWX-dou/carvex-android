; accessoryd 0x100037068-0x1000370b0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100037068:	pacibsp	
0x10003706c:	sub	sp, sp, #0x20
0x100037070:	stp	x29, x30, [sp, #0x10]
0x100037074:	add	x29, sp, #0x10
0x100037078:	adrp	x8, #0x10022a000
0x10003707c:	ldr	x0, [x8, #0xea0]
0x100037080:	bl	#0x1001aadc0
0x100037084:	bl	#0x1001a2490
0x100037088:	str	x0, [sp, #8]
0x10003708c:	bl	#0x1001a5f60
0x100037090:	ldr	x0, [sp, #8]
0x100037094:	ldp	x29, x30, [sp, #0x10]
0x100037098:	add	sp, sp, #0x20
0x10003709c:	autibsp	
0x1000370a0:	eor	x16, x30, x30, lsl #1
0x1000370a4:	tbz	x16, #0x3e, #0x1000370ac
0x1000370a8:	brk	#0xc471
0x1000370ac:	b	#0x1001a2540

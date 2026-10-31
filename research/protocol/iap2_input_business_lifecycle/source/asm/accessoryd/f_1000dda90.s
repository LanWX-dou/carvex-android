; accessoryd 0x1000dda90-0x1000ddad8; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000dda90:	pacibsp	
0x1000dda94:	sub	sp, sp, #0x20
0x1000dda98:	stp	x29, x30, [sp, #0x10]
0x1000dda9c:	add	x29, sp, #0x10
0x1000ddaa0:	adrp	x8, #0x10022a000
0x1000ddaa4:	ldr	x0, [x8, #0xef8]
0x1000ddaa8:	bl	#0x1001aadc0
0x1000ddaac:	bl	#0x1001a2490
0x1000ddab0:	str	x0, [sp, #8]
0x1000ddab4:	bl	#0x1001a5f60
0x1000ddab8:	ldr	x0, [sp, #8]
0x1000ddabc:	ldp	x29, x30, [sp, #0x10]
0x1000ddac0:	add	sp, sp, #0x20
0x1000ddac4:	autibsp	
0x1000ddac8:	eor	x16, x30, x30, lsl #1
0x1000ddacc:	tbz	x16, #0x3e, #0x1000ddad4
0x1000ddad0:	brk	#0xc471
0x1000ddad4:	b	#0x1001a2540

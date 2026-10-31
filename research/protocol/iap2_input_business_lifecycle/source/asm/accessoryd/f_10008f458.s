; accessoryd 0x10008f458-0x10008f4a0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008f458:	pacibsp	
0x10008f45c:	sub	sp, sp, #0x20
0x10008f460:	stp	x29, x30, [sp, #0x10]
0x10008f464:	add	x29, sp, #0x10
0x10008f468:	bl	#0x10008f3b8
0x10008f46c:	bl	#0x1001a2490
0x10008f470:	str	x0, [sp, #8]
0x10008f474:	adrp	x2, #0x10021c000
0x10008f478:	add	x2, x2, #0x918
0x10008f47c:	bl	#0x1001a9620
0x10008f480:	ldr	x0, [sp, #8]
0x10008f484:	ldp	x29, x30, [sp, #0x10]
0x10008f488:	add	sp, sp, #0x20
0x10008f48c:	autibsp	
0x10008f490:	eor	x16, x30, x30, lsl #1
0x10008f494:	tbz	x16, #0x3e, #0x10008f49c
0x10008f498:	brk	#0xc471
0x10008f49c:	b	#0x1001a2540

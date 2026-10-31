; accessoryd 0x10008f70c-0x10008f754; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008f70c:	pacibsp	
0x10008f710:	sub	sp, sp, #0x20
0x10008f714:	stp	x29, x30, [sp, #0x10]
0x10008f718:	add	x29, sp, #0x10
0x10008f71c:	bl	#0x10008f3b8
0x10008f720:	bl	#0x1001a2490
0x10008f724:	str	x0, [sp, #8]
0x10008f728:	adrp	x2, #0x10021c000
0x10008f72c:	add	x2, x2, #0x958
0x10008f730:	bl	#0x1001a9600
0x10008f734:	ldr	x0, [sp, #8]
0x10008f738:	ldp	x29, x30, [sp, #0x10]
0x10008f73c:	add	sp, sp, #0x20
0x10008f740:	autibsp	
0x10008f744:	eor	x16, x30, x30, lsl #1
0x10008f748:	tbz	x16, #0x3e, #0x10008f750
0x10008f74c:	brk	#0xc471
0x10008f750:	b	#0x1001a2540

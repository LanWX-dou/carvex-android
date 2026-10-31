; accessoryd 0x100034778-0x1000347b0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100034778:	cbz	x0, #0x1000347ac
0x10003477c:	pacibsp	
0x100034780:	stp	x20, x19, [sp, #-0x20]!
0x100034784:	stp	x29, x30, [sp, #0x10]
0x100034788:	add	x29, sp, #0x10
0x10003478c:	mov	x19, x0
0x100034790:	ldr	x0, [x0, #0xc8]
0x100034794:	cbz	x0, #0x1000347a0
0x100034798:	bl	#0x1000ebeb0
0x10003479c:	str	xzr, [x19, #0xc8]
0x1000347a0:	ldp	x29, x30, [sp, #0x10]
0x1000347a4:	ldp	x20, x19, [sp], #0x20
0x1000347a8:	autibsp	
0x1000347ac:	ret	

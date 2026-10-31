; accessoryd 0x10002a980-0x10002a9bc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10002a980:	pacibsp	
0x10002a984:	stp	x20, x19, [sp, #-0x20]!
0x10002a988:	stp	x29, x30, [sp, #0x10]
0x10002a98c:	add	x29, sp, #0x10
0x10002a990:	mov	x19, x0
0x10002a994:	ldr	x0, [x0, #0x20]
0x10002a998:	bl	#0x1000ebc44
0x10002a99c:	ldr	x0, [x19, #0x20]
0x10002a9a0:	ldp	x29, x30, [sp, #0x10]
0x10002a9a4:	ldp	x20, x19, [sp], #0x20
0x10002a9a8:	autibsp	
0x10002a9ac:	eor	x16, x30, x30, lsl #1
0x10002a9b0:	tbz	x16, #0x3e, #0x10002a9b8
0x10002a9b4:	brk	#0xc471
0x10002a9b8:	b	#0x1001a1820

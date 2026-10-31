; accessoryd 0x10008fc20-0x10008fc70; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008fc20:	pacibsp	
0x10008fc24:	sub	sp, sp, #0x30
0x10008fc28:	stp	x20, x19, [sp, #0x10]
0x10008fc2c:	stp	x29, x30, [sp, #0x20]
0x10008fc30:	add	x29, sp, #0x20
0x10008fc34:	mov	x19, x0
0x10008fc38:	bl	#0x10008f3b8
0x10008fc3c:	bl	#0x1001a2490
0x10008fc40:	str	x0, [sp, #8]
0x10008fc44:	mov	x2, x19
0x10008fc48:	bl	#0x1001a9520
0x10008fc4c:	ldr	x0, [sp, #8]
0x10008fc50:	ldp	x29, x30, [sp, #0x20]
0x10008fc54:	ldp	x20, x19, [sp, #0x10]
0x10008fc58:	add	sp, sp, #0x30
0x10008fc5c:	autibsp	
0x10008fc60:	eor	x16, x30, x30, lsl #1
0x10008fc64:	tbz	x16, #0x3e, #0x10008fc6c
0x10008fc68:	brk	#0xc471
0x10008fc6c:	b	#0x1001a2540

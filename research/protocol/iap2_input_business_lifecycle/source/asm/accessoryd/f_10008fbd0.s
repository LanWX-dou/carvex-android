; accessoryd 0x10008fbd0-0x10008fc20; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008fbd0:	pacibsp	
0x10008fbd4:	sub	sp, sp, #0x30
0x10008fbd8:	stp	x20, x19, [sp, #0x10]
0x10008fbdc:	stp	x29, x30, [sp, #0x20]
0x10008fbe0:	add	x29, sp, #0x20
0x10008fbe4:	mov	x19, x0
0x10008fbe8:	bl	#0x10008f3b8
0x10008fbec:	bl	#0x1001a2490
0x10008fbf0:	str	x0, [sp, #8]
0x10008fbf4:	mov	x2, x19
0x10008fbf8:	bl	#0x1001a4800
0x10008fbfc:	ldr	x0, [sp, #8]
0x10008fc00:	ldp	x29, x30, [sp, #0x20]
0x10008fc04:	ldp	x20, x19, [sp, #0x10]
0x10008fc08:	add	sp, sp, #0x30
0x10008fc0c:	autibsp	
0x10008fc10:	eor	x16, x30, x30, lsl #1
0x10008fc14:	tbz	x16, #0x3e, #0x10008fc1c
0x10008fc18:	brk	#0xc471
0x10008fc1c:	b	#0x1001a2540

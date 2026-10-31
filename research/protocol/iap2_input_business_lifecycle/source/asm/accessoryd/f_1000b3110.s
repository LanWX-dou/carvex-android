; accessoryd 0x1000b3110-0x1000b3158; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000b3110:	pacibsp	
0x1000b3114:	sub	sp, sp, #0x20
0x1000b3118:	stp	x29, x30, [sp, #0x10]
0x1000b311c:	add	x29, sp, #0x10
0x1000b3120:	adrp	x8, #0x10022a000
0x1000b3124:	ldr	x0, [x8, #0xed8]
0x1000b3128:	bl	#0x1001aadc0
0x1000b312c:	bl	#0x1001a2490
0x1000b3130:	str	x0, [sp, #8]
0x1000b3134:	bl	#0x1001a5f60
0x1000b3138:	ldr	x0, [sp, #8]
0x1000b313c:	ldp	x29, x30, [sp, #0x10]
0x1000b3140:	add	sp, sp, #0x20
0x1000b3144:	autibsp	
0x1000b3148:	eor	x16, x30, x30, lsl #1
0x1000b314c:	tbz	x16, #0x3e, #0x1000b3154
0x1000b3150:	brk	#0xc471
0x1000b3154:	b	#0x1001a2540

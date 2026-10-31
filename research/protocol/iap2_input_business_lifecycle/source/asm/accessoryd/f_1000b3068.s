; accessoryd 0x1000b3068-0x1000b3110; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000b3068:	pacibsp	
0x1000b306c:	sub	sp, sp, #0x30
0x1000b3070:	stp	x20, x19, [sp, #0x10]
0x1000b3074:	stp	x29, x30, [sp, #0x20]
0x1000b3078:	add	x29, sp, #0x20
0x1000b307c:	adrp	x20, #0x10022a000
0x1000b3080:	ldr	x0, [x20, #0xed8]
0x1000b3084:	bl	#0x1001aadc0
0x1000b3088:	bl	#0x1001a2490
0x1000b308c:	mov	x19, x0
0x1000b3090:	bl	#0x1001a7080
0x1000b3094:	bl	#0x1001a2560
0x1000b3098:	ldr	x0, [x20, #0xed8]
0x1000b309c:	bl	#0x1001aadc0
0x1000b30a0:	bl	#0x1001a2490
0x1000b30a4:	mov	x19, x0
0x1000b30a8:	bl	#0x1001a67a0
0x1000b30ac:	mov	x20, x0
0x1000b30b0:	bl	#0x1001a2560
0x1000b30b4:	cmp	w20, #1
0x1000b30b8:	b.ne	#0x1000b3100
0x1000b30bc:	adrp	x8, #0x10022a000
0x1000b30c0:	ldr	x0, [x8, #0xed0]
0x1000b30c4:	bl	#0x1001aad80
0x1000b30c8:	bl	#0x1001a2490
0x1000b30cc:	str	x0, [sp, #8]
0x1000b30d0:	adrp	x2, #0x10022a000
0x1000b30d4:	add	x2, x2, #0xa8
0x1000b30d8:	bl	#0x1001ab1c0
0x1000b30dc:	ldr	x0, [sp, #8]
0x1000b30e0:	ldp	x29, x30, [sp, #0x20]
0x1000b30e4:	ldp	x20, x19, [sp, #0x10]
0x1000b30e8:	add	sp, sp, #0x30
0x1000b30ec:	autibsp	
0x1000b30f0:	eor	x16, x30, x30, lsl #1
0x1000b30f4:	tbz	x16, #0x3e, #0x1000b30fc
0x1000b30f8:	brk	#0xc471
0x1000b30fc:	b	#0x1001a2540
0x1000b3100:	ldp	x29, x30, [sp, #0x20]
0x1000b3104:	ldp	x20, x19, [sp, #0x10]
0x1000b3108:	add	sp, sp, #0x30
0x1000b310c:	retab	

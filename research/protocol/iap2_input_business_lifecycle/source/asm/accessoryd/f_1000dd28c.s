; accessoryd 0x1000dd28c-0x1000dd2f8; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000dd28c:	pacibsp	
0x1000dd290:	sub	sp, sp, #0x30
0x1000dd294:	stp	x20, x19, [sp, #0x10]
0x1000dd298:	stp	x29, x30, [sp, #0x20]
0x1000dd29c:	add	x29, sp, #0x20
0x1000dd2a0:	strh	w1, [sp, #0xe]
0x1000dd2a4:	cbz	x0, #0x1000dd2e8
0x1000dd2a8:	mov	x19, x0
0x1000dd2ac:	adrp	x8, #0x10022b000
0x1000dd2b0:	ldr	x8, [x8, #0xce0]
0x1000dd2b4:	ldr	x0, [x8]
0x1000dd2b8:	add	x2, sp, #0xe
0x1000dd2bc:	mov	w1, #2
0x1000dd2c0:	bl	#0x1001a17a0
0x1000dd2c4:	mov	x20, x0
0x1000dd2c8:	adrp	x8, #0x10023d000
0x1000dd2cc:	add	x8, x8, #0xbb0
0x1000dd2d0:	ldr	x1, [x8]
0x1000dd2d4:	mov	x0, x19
0x1000dd2d8:	mov	x2, x20
0x1000dd2dc:	bl	#0x1001a16d0
0x1000dd2e0:	mov	x0, x20
0x1000dd2e4:	bl	#0x1001a1820
0x1000dd2e8:	ldp	x29, x30, [sp, #0x20]
0x1000dd2ec:	ldp	x20, x19, [sp, #0x10]
0x1000dd2f0:	add	sp, sp, #0x30
0x1000dd2f4:	retab	

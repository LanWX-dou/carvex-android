; accessoryd 0x1000dd364-0x1000dd3d0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000dd364:	pacibsp	
0x1000dd368:	sub	sp, sp, #0x30
0x1000dd36c:	stp	x20, x19, [sp, #0x10]
0x1000dd370:	stp	x29, x30, [sp, #0x20]
0x1000dd374:	add	x29, sp, #0x20
0x1000dd378:	strh	w1, [sp, #0xe]
0x1000dd37c:	cbz	x0, #0x1000dd3c0
0x1000dd380:	mov	x19, x0
0x1000dd384:	adrp	x8, #0x10022b000
0x1000dd388:	ldr	x8, [x8, #0xce0]
0x1000dd38c:	ldr	x0, [x8]
0x1000dd390:	add	x2, sp, #0xe
0x1000dd394:	mov	w1, #2
0x1000dd398:	bl	#0x1001a17a0
0x1000dd39c:	mov	x20, x0
0x1000dd3a0:	adrp	x8, #0x10023d000
0x1000dd3a4:	add	x8, x8, #0xbc0
0x1000dd3a8:	ldr	x1, [x8]
0x1000dd3ac:	mov	x0, x19
0x1000dd3b0:	mov	x2, x20
0x1000dd3b4:	bl	#0x1001a16d0
0x1000dd3b8:	mov	x0, x20
0x1000dd3bc:	bl	#0x1001a1820
0x1000dd3c0:	ldp	x29, x30, [sp, #0x20]
0x1000dd3c4:	ldp	x20, x19, [sp, #0x10]
0x1000dd3c8:	add	sp, sp, #0x30
0x1000dd3cc:	retab	

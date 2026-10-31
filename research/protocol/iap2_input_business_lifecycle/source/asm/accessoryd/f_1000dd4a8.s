; accessoryd 0x1000dd4a8-0x1000dd514; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000dd4a8:	pacibsp	
0x1000dd4ac:	sub	sp, sp, #0x30
0x1000dd4b0:	stp	x20, x19, [sp, #0x10]
0x1000dd4b4:	stp	x29, x30, [sp, #0x20]
0x1000dd4b8:	add	x29, sp, #0x20
0x1000dd4bc:	strh	w1, [sp, #0xe]
0x1000dd4c0:	cbz	x0, #0x1000dd504
0x1000dd4c4:	mov	x19, x0
0x1000dd4c8:	adrp	x8, #0x10022b000
0x1000dd4cc:	ldr	x8, [x8, #0xce0]
0x1000dd4d0:	ldr	x0, [x8]
0x1000dd4d4:	add	x2, sp, #0xe
0x1000dd4d8:	mov	w1, #2
0x1000dd4dc:	bl	#0x1001a17a0
0x1000dd4e0:	mov	x20, x0
0x1000dd4e4:	adrp	x8, #0x10023d000
0x1000dd4e8:	add	x8, x8, #0xbd8
0x1000dd4ec:	ldr	x1, [x8]
0x1000dd4f0:	mov	x0, x19
0x1000dd4f4:	mov	x2, x20
0x1000dd4f8:	bl	#0x1001a16d0
0x1000dd4fc:	mov	x0, x20
0x1000dd500:	bl	#0x1001a1820
0x1000dd504:	ldp	x29, x30, [sp, #0x20]
0x1000dd508:	ldp	x20, x19, [sp, #0x10]
0x1000dd50c:	add	sp, sp, #0x30
0x1000dd510:	retab	

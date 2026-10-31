; accessoryd 0x1000dd43c-0x1000dd4a8; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000dd43c:	pacibsp	
0x1000dd440:	sub	sp, sp, #0x30
0x1000dd444:	stp	x20, x19, [sp, #0x10]
0x1000dd448:	stp	x29, x30, [sp, #0x20]
0x1000dd44c:	add	x29, sp, #0x20
0x1000dd450:	strh	w1, [sp, #0xe]
0x1000dd454:	cbz	x0, #0x1000dd498
0x1000dd458:	mov	x19, x0
0x1000dd45c:	adrp	x8, #0x10022b000
0x1000dd460:	ldr	x8, [x8, #0xce0]
0x1000dd464:	ldr	x0, [x8]
0x1000dd468:	add	x2, sp, #0xe
0x1000dd46c:	mov	w1, #2
0x1000dd470:	bl	#0x1001a17a0
0x1000dd474:	mov	x20, x0
0x1000dd478:	adrp	x8, #0x10023d000
0x1000dd47c:	add	x8, x8, #0xbd0
0x1000dd480:	ldr	x1, [x8]
0x1000dd484:	mov	x0, x19
0x1000dd488:	mov	x2, x20
0x1000dd48c:	bl	#0x1001a16d0
0x1000dd490:	mov	x0, x20
0x1000dd494:	bl	#0x1001a1820
0x1000dd498:	ldp	x29, x30, [sp, #0x20]
0x1000dd49c:	ldp	x20, x19, [sp, #0x10]
0x1000dd4a0:	add	sp, sp, #0x30
0x1000dd4a4:	retab	

; accessoryd 0x1000dd3d0-0x1000dd43c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000dd3d0:	pacibsp	
0x1000dd3d4:	sub	sp, sp, #0x30
0x1000dd3d8:	stp	x20, x19, [sp, #0x10]
0x1000dd3dc:	stp	x29, x30, [sp, #0x20]
0x1000dd3e0:	add	x29, sp, #0x20
0x1000dd3e4:	strh	w1, [sp, #0xe]
0x1000dd3e8:	cbz	x0, #0x1000dd42c
0x1000dd3ec:	mov	x19, x0
0x1000dd3f0:	adrp	x8, #0x10022b000
0x1000dd3f4:	ldr	x8, [x8, #0xce0]
0x1000dd3f8:	ldr	x0, [x8]
0x1000dd3fc:	add	x2, sp, #0xe
0x1000dd400:	mov	w1, #2
0x1000dd404:	bl	#0x1001a17a0
0x1000dd408:	mov	x20, x0
0x1000dd40c:	adrp	x8, #0x10023d000
0x1000dd410:	add	x8, x8, #0xbc8
0x1000dd414:	ldr	x1, [x8]
0x1000dd418:	mov	x0, x19
0x1000dd41c:	mov	x2, x20
0x1000dd420:	bl	#0x1001a16d0
0x1000dd424:	mov	x0, x20
0x1000dd428:	bl	#0x1001a1820
0x1000dd42c:	ldp	x29, x30, [sp, #0x20]
0x1000dd430:	ldp	x20, x19, [sp, #0x10]
0x1000dd434:	add	sp, sp, #0x30
0x1000dd438:	retab	

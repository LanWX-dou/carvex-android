; accessoryd 0x10008f3fc-0x10008f458; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008f3fc:	pacibsp	
0x10008f400:	stp	x20, x19, [sp, #-0x20]!
0x10008f404:	stp	x29, x30, [sp, #0x10]
0x10008f408:	add	x29, sp, #0x10
0x10008f40c:	mov	x19, x0
0x10008f410:	bl	#0x10008f3b8
0x10008f414:	bl	#0x1001a2490
0x10008f418:	mov	x20, x0
0x10008f41c:	adrp	x8, #0x10022b000
0x10008f420:	ldr	x0, [x8, #0xb28]
0x10008f424:	mov	w2, w19
0x10008f428:	bl	#0x1001a8560
0x10008f42c:	bl	#0x1001a2490
0x10008f430:	mov	x19, x0
0x10008f434:	mov	x0, x20
0x10008f438:	mov	x2, x19
0x10008f43c:	bl	#0x1001aa740
0x10008f440:	bl	#0x1001a2560
0x10008f444:	bl	#0x1001a2580
0x10008f448:	mov	w0, #1
0x10008f44c:	ldp	x29, x30, [sp, #0x10]
0x10008f450:	ldp	x20, x19, [sp], #0x20
0x10008f454:	retab	

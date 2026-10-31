; accessoryd 0x10008f35c-0x10008f3b8; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008f35c:	pacibsp	
0x10008f360:	stp	x20, x19, [sp, #-0x20]!
0x10008f364:	stp	x29, x30, [sp, #0x10]
0x10008f368:	add	x29, sp, #0x10
0x10008f36c:	mov	x19, x0
0x10008f370:	bl	#0x10008f3b8
0x10008f374:	bl	#0x1001a2490
0x10008f378:	mov	x20, x0
0x10008f37c:	adrp	x8, #0x10022b000
0x10008f380:	ldr	x0, [x8, #0xb28]
0x10008f384:	mov	w2, w19
0x10008f388:	bl	#0x1001a8560
0x10008f38c:	bl	#0x1001a2490
0x10008f390:	mov	x19, x0
0x10008f394:	mov	x0, x20
0x10008f398:	mov	x2, x19
0x10008f39c:	bl	#0x1001aa720
0x10008f3a0:	bl	#0x1001a2560
0x10008f3a4:	bl	#0x1001a2580
0x10008f3a8:	mov	w0, #1
0x10008f3ac:	ldp	x29, x30, [sp, #0x10]
0x10008f3b0:	ldp	x20, x19, [sp], #0x20
0x10008f3b4:	retab	

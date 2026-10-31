; accessoryd 0x10008f2e4-0x10008f34c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008f2e4:	pacibsp	
0x10008f2e8:	sub	sp, sp, #0x30
0x10008f2ec:	stp	x20, x19, [sp, #0x10]
0x10008f2f0:	stp	x29, x30, [sp, #0x20]
0x10008f2f4:	add	x29, sp, #0x20
0x10008f2f8:	strb	w0, [sp, #0xf]
0x10008f2fc:	adrp	x8, #0x10022b000
0x10008f300:	ldr	x8, [x8, #0xce0]
0x10008f304:	ldr	x0, [x8]
0x10008f308:	add	x2, sp, #0xf
0x10008f30c:	mov	w1, #7
0x10008f310:	bl	#0x1001a17a0
0x10008f314:	mov	x19, x0
0x10008f318:	mov	x0, #0
0x10008f31c:	mov	w1, #0xcb
0x10008f320:	mov	x2, x19
0x10008f324:	bl	#0x1000022a4
0x10008f328:	mov	x20, x0
0x10008f32c:	cbz	x19, #0x10008f338
0x10008f330:	mov	x0, x19
0x10008f334:	bl	#0x1001a1820
0x10008f338:	mov	x0, x20
0x10008f33c:	ldp	x29, x30, [sp, #0x20]
0x10008f340:	ldp	x20, x19, [sp, #0x10]
0x10008f344:	add	sp, sp, #0x30
0x10008f348:	retab	

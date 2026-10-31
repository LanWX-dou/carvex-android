; accessoryd 0x10000b368-0x10000b3bc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10000b368:	ldr	x8, [x0, #0x40]
0x10000b36c:	ldrb	w8, [x8, #4]
0x10000b370:	and	w8, w8, #0xf0
0x10000b374:	cmp	w8, #0x40
0x10000b378:	b.ne	#0x10000b3b4
0x10000b37c:	pacibsp	
0x10000b380:	stp	x20, x19, [sp, #-0x20]!
0x10000b384:	stp	x29, x30, [sp, #0x10]
0x10000b388:	add	x29, sp, #0x10
0x10000b38c:	ldr	x8, [x0]
0x10000b390:	ldrh	w19, [x0, #0x36]
0x10000b394:	mov	x0, x8
0x10000b398:	bl	#0x100005f4c
0x10000b39c:	cmp	w19, w0
0x10000b3a0:	cset	w0, eq
0x10000b3a4:	ldp	x29, x30, [sp, #0x10]
0x10000b3a8:	ldp	x20, x19, [sp], #0x20
0x10000b3ac:	autibsp	
0x10000b3b0:	ret	
0x10000b3b4:	mov	w0, #0
0x10000b3b8:	ret	

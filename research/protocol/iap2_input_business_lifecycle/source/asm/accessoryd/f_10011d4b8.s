; accessoryd 0x10011d4b8-0x10011d518; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10011d4b8:	cbz	x0, #0x10011d50c
0x10011d4bc:	ldr	x8, [x0, #0x28]
0x10011d4c0:	cbz	x8, #0x10011d508
0x10011d4c4:	pacibsp	
0x10011d4c8:	stp	x20, x19, [sp, #-0x20]!
0x10011d4cc:	stp	x29, x30, [sp, #0x10]
0x10011d4d0:	add	x29, sp, #0x10
0x10011d4d4:	ldr	x19, [x8, #0x18]
0x10011d4d8:	cbz	x19, #0x10011d510
0x10011d4dc:	bl	#0x10002b140
0x10011d4e0:	bl	#0x100005740
0x10011d4e4:	mov	x1, x0
0x10011d4e8:	mov	x0, x19
0x10011d4ec:	bl	#0x100032828
0x10011d4f0:	cbz	x0, #0x10011d4f8
0x10011d4f4:	ldrb	w0, [x0, #2]
0x10011d4f8:	ldp	x29, x30, [sp, #0x10]
0x10011d4fc:	ldp	x20, x19, [sp], #0x20
0x10011d500:	autibsp	
0x10011d504:	ret	
0x10011d508:	mov	w0, #0
0x10011d50c:	ret	
0x10011d510:	mov	w0, #0
0x10011d514:	b	#0x10011d4f8

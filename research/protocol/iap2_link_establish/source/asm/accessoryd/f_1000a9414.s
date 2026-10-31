; accessoryd 0x1000a9414-0x1000a945c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000a9414:	pacibsp	
0x1000a9418:	stp	x20, x19, [sp, #-0x20]!
0x1000a941c:	stp	x29, x30, [sp, #0x10]
0x1000a9420:	add	x29, sp, #0x10
0x1000a9424:	cmp	w0, #3
0x1000a9428:	mov	w8, #0xa
0x1000a942c:	csel	w19, w8, wzr, eq
0x1000a9430:	adrp	x8, #0x100221000
0x1000a9434:	add	x8, x8, #0x728
0x1000a9438:	ldr	x0, [x8]
0x1000a943c:	bl	#0x100102d90
0x1000a9440:	asr	x8, x0, #0x3f
0x1000a9444:	bic	w8, w0, w8
0x1000a9448:	cmp	x0, #0
0x1000a944c:	csel	w0, w19, w8, eq
0x1000a9450:	ldp	x29, x30, [sp, #0x10]
0x1000a9454:	ldp	x20, x19, [sp], #0x20
0x1000a9458:	retab	

; accessoryd 0x10012356c-0x1001235c0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10012356c:	pacibsp	
0x100123570:	stp	x20, x19, [sp, #-0x20]!
0x100123574:	stp	x29, x30, [sp, #0x10]
0x100123578:	add	x29, sp, #0x10
0x10012357c:	mov	w19, #0
0x100123580:	cbz	x0, #0x1001235a8
0x100123584:	cbz	x1, #0x1001235a8
0x100123588:	mov	x20, x0
0x10012358c:	mov	w1, #7
0x100123590:	bl	#0x100003360
0x100123594:	cbz	x0, #0x1001235b8
0x100123598:	mov	w19, #1
0x10012359c:	mov	x0, x20
0x1001235a0:	mov	w1, #1
0x1001235a4:	bl	#0x1001235c0
0x1001235a8:	mov	x0, x19
0x1001235ac:	ldp	x29, x30, [sp, #0x10]
0x1001235b0:	ldp	x20, x19, [sp], #0x20
0x1001235b4:	retab	
0x1001235b8:	mov	w19, #0
0x1001235bc:	b	#0x1001235a8

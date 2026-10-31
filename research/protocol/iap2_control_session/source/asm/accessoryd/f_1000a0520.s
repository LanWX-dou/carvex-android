; accessoryd 0x1000a0520-0x1000a05bc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000a0520:	pacibsp	
0x1000a0524:	stp	x22, x21, [sp, #-0x30]!
0x1000a0528:	stp	x20, x19, [sp, #0x10]
0x1000a052c:	stp	x29, x30, [sp, #0x20]
0x1000a0530:	add	x29, sp, #0x20
0x1000a0534:	mov	x19, x1
0x1000a0538:	mov	x20, x0
0x1000a053c:	mov	x0, x1
0x1000a0540:	bl	#0x1000053a4
0x1000a0544:	mov	x21, x0
0x1000a0548:	ldr	x0, [x20, #0x10]
0x1000a054c:	mov	x1, x19
0x1000a0550:	bl	#0x100005738
0x1000a0554:	lsr	w8, w21, #8
0x1000a0558:	ldr	x9, [x19, #0x18]
0x1000a055c:	strb	w8, [x9, #2]
0x1000a0560:	ldr	x8, [x19, #0x18]
0x1000a0564:	strb	w21, [x8, #3]
0x1000a0568:	ands	w8, w21, #0xffff
0x1000a056c:	b.eq	#0x1000a05ac
0x1000a0570:	ldr	x9, [x19, #0x18]
0x1000a0574:	str	x9, [x19]
0x1000a0578:	str	w8, [x19, #8]
0x1000a057c:	mov	w8, #1
0x1000a0580:	strb	w8, [x19, #0x38]
0x1000a0584:	ldr	x0, [x20, #0x18]
0x1000a0588:	mov	x1, x19
0x1000a058c:	ldp	x29, x30, [sp, #0x20]
0x1000a0590:	ldp	x20, x19, [sp, #0x10]
0x1000a0594:	ldp	x22, x21, [sp], #0x30
0x1000a0598:	autibsp	
0x1000a059c:	eor	x16, x30, x30, lsl #1
0x1000a05a0:	tbz	x16, #0x3e, #0x1000a05a8
0x1000a05a4:	brk	#0xc471
0x1000a05a8:	b	#0x100005bd0
0x1000a05ac:	ldp	x29, x30, [sp, #0x20]
0x1000a05b0:	ldp	x20, x19, [sp, #0x10]
0x1000a05b4:	ldp	x22, x21, [sp], #0x30
0x1000a05b8:	retab	

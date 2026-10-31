; accessoryd 0x100046780-0x1000467e4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100046780:	pacibsp	
0x100046784:	stp	x29, x30, [sp, #-0x10]!
0x100046788:	mov	x29, sp
0x10004678c:	cbz	x0, #0x1000467d0
0x100046790:	ldrb	w8, [x0, #0x1e]
0x100046794:	cmp	w8, #1
0x100046798:	b.eq	#0x1000467d8
0x10004679c:	ldr	x8, [x0, #0x110]
0x1000467a0:	cbz	x8, #0x1000467dc
0x1000467a4:	mov	x2, x1
0x1000467a8:	ldr	x1, [x0]
0x1000467ac:	mov	x3, x8
0x1000467b0:	ldr	x4, [x3, #0x10]!
0x1000467b4:	mov	x0, x8
0x1000467b8:	ldp	x29, x30, [sp], #0x10
0x1000467bc:	autibsp	
0x1000467c0:	eor	x16, x30, x30, lsl #1
0x1000467c4:	tbz	x16, #0x3e, #0x1000467cc
0x1000467c8:	brk	#0xc471
0x1000467cc:	braa	x4, x3
0x1000467d0:	bl	#0x100134c88
0x1000467d4:	b	#0x1000467dc
0x1000467d8:	bl	#0x100134c3c
0x1000467dc:	ldp	x29, x30, [sp], #0x10
0x1000467e0:	retab	

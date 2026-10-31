; accessoryd 0x1000cb23c-0x1000cb288; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000cb23c:	cbz	x0, #0x1000cb284
0x1000cb240:	pacibsp	
0x1000cb244:	stp	x20, x19, [sp, #-0x20]!
0x1000cb248:	stp	x29, x30, [sp, #0x10]
0x1000cb24c:	add	x29, sp, #0x10
0x1000cb250:	mov	x19, x0
0x1000cb254:	mov	w1, #8
0x1000cb258:	bl	#0x10010395c
0x1000cb25c:	mov	x0, x19
0x1000cb260:	mov	x1, #0
0x1000cb264:	mov	x2, #0
0x1000cb268:	ldp	x29, x30, [sp, #0x10]
0x1000cb26c:	ldp	x20, x19, [sp], #0x20
0x1000cb270:	autibsp	
0x1000cb274:	eor	x16, x30, x30, lsl #1
0x1000cb278:	tbz	x16, #0x3e, #0x1000cb280
0x1000cb27c:	brk	#0xc471
0x1000cb280:	b	#0x100008698
0x1000cb284:	ret	

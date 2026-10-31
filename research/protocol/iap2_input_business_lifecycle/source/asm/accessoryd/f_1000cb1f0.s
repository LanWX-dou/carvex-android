; accessoryd 0x1000cb1f0-0x1000cb23c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000cb1f0:	cbz	x0, #0x1000cb238
0x1000cb1f4:	pacibsp	
0x1000cb1f8:	stp	x20, x19, [sp, #-0x20]!
0x1000cb1fc:	stp	x29, x30, [sp, #0x10]
0x1000cb200:	add	x29, sp, #0x10
0x1000cb204:	mov	x19, x0
0x1000cb208:	mov	w1, #4
0x1000cb20c:	bl	#0x10010395c
0x1000cb210:	mov	x0, x19
0x1000cb214:	mov	x1, #0
0x1000cb218:	mov	x2, #0
0x1000cb21c:	ldp	x29, x30, [sp, #0x10]
0x1000cb220:	ldp	x20, x19, [sp], #0x20
0x1000cb224:	autibsp	
0x1000cb228:	eor	x16, x30, x30, lsl #1
0x1000cb22c:	tbz	x16, #0x3e, #0x1000cb234
0x1000cb230:	brk	#0xc471
0x1000cb234:	b	#0x100008698
0x1000cb238:	ret	

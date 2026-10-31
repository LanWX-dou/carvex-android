; accessoryd 0x1000cb158-0x1000cb1a4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000cb158:	cbz	x0, #0x1000cb1a0
0x1000cb15c:	pacibsp	
0x1000cb160:	stp	x20, x19, [sp, #-0x20]!
0x1000cb164:	stp	x29, x30, [sp, #0x10]
0x1000cb168:	add	x29, sp, #0x10
0x1000cb16c:	mov	x19, x0
0x1000cb170:	mov	w1, #1
0x1000cb174:	bl	#0x10010395c
0x1000cb178:	mov	x0, x19
0x1000cb17c:	mov	x1, #0
0x1000cb180:	mov	x2, #0
0x1000cb184:	ldp	x29, x30, [sp, #0x10]
0x1000cb188:	ldp	x20, x19, [sp], #0x20
0x1000cb18c:	autibsp	
0x1000cb190:	eor	x16, x30, x30, lsl #1
0x1000cb194:	tbz	x16, #0x3e, #0x1000cb19c
0x1000cb198:	brk	#0xc471
0x1000cb19c:	b	#0x100007728
0x1000cb1a0:	ret	

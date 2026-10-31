; accessoryd 0x10002fac8-0x10002fb54; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10002fac8:	pacibsp	
0x10002facc:	stp	x20, x19, [sp, #-0x20]!
0x10002fad0:	stp	x29, x30, [sp, #0x10]
0x10002fad4:	add	x29, sp, #0x10
0x10002fad8:	cbz	x0, #0x10002fb4c
0x10002fadc:	cbz	x1, #0x10002fb50
0x10002fae0:	mov	w8, #0x1d
0x10002fae4:	strb	w8, [x1]
0x10002fae8:	ldr	x19, [x0, #0x10]
0x10002faec:	mov	x0, x19
0x10002faf0:	mov	w1, #0
0x10002faf4:	mov	w2, #1
0x10002faf8:	bl	#0x1000346c8
0x10002fafc:	add	x8, x19, #0x168
0x10002fb00:	ldr	x9, [x19, #0x160]
0x10002fb04:	ldp	q1, q0, [x9, #0x10]
0x10002fb08:	ldrh	w10, [x9, #0x30]
0x10002fb0c:	ldr	q2, [x9]
0x10002fb10:	strh	w10, [x19, #0x198]
0x10002fb14:	stp	q1, q0, [x8, #0x10]
0x10002fb18:	str	q2, [x8]
0x10002fb1c:	mov	x0, x19
0x10002fb20:	mov	w1, #0
0x10002fb24:	bl	#0x100103970
0x10002fb28:	mov	x0, x19
0x10002fb2c:	mov	w1, #0
0x10002fb30:	ldp	x29, x30, [sp, #0x10]
0x10002fb34:	ldp	x20, x19, [sp], #0x20
0x10002fb38:	autibsp	
0x10002fb3c:	eor	x16, x30, x30, lsl #1
0x10002fb40:	tbz	x16, #0x3e, #0x10002fb48
0x10002fb44:	brk	#0xc471
0x10002fb48:	b	#0x10019c124
0x10002fb4c:	bl	#0x10012903c
0x10002fb50:	bl	#0x100129014

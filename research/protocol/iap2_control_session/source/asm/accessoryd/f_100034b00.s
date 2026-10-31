; accessoryd 0x100034b00-0x100034bbc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100034b00:	pacibsp	
0x100034b04:	stp	x20, x19, [sp, #-0x20]!
0x100034b08:	stp	x29, x30, [sp, #0x10]
0x100034b0c:	add	x29, sp, #0x10
0x100034b10:	mov	x19, x0
0x100034b14:	mov	w1, #0
0x100034b18:	bl	#0x100103970
0x100034b1c:	mov	x0, x19
0x100034b20:	mov	w1, #0
0x100034b24:	mov	w2, #0
0x100034b28:	bl	#0x1000346c8
0x100034b2c:	add	x8, x19, #0x19a
0x100034b30:	add	x9, x19, #0x19e
0x100034b34:	mov	w10, #0x3e8ffff
0x100034b38:	str	w10, [x9]
0x100034b3c:	mov	w9, #0xa
0x100034b40:	strh	w9, [x19, #0x1a2]
0x100034b44:	adrp	x9, #0x1001b3000
0x100034b48:	ldr	d0, [x9, #0x348]
0x100034b4c:	str	s0, [x8]
0x100034b50:	mov	w8, #-0xff00
0x100034b54:	str	w8, [x19, #0x1a4]
0x100034b58:	add	x8, x19, #0x168
0x100034b5c:	ldr	x9, [x19, #0x160]
0x100034b60:	ldp	q1, q0, [x9, #0x10]
0x100034b64:	ldrh	w10, [x9, #0x30]
0x100034b68:	ldr	q2, [x9]
0x100034b6c:	strh	w10, [x19, #0x198]
0x100034b70:	stp	q1, q0, [x8, #0x10]
0x100034b74:	str	q2, [x8]
0x100034b78:	ldrb	w1, [x19, #0xbe]
0x100034b7c:	mov	x0, x19
0x100034b80:	bl	#0x1001031f0
0x100034b84:	mov	x20, x0
0x100034b88:	mov	x0, x19
0x100034b8c:	mov	x1, x20
0x100034b90:	mov	w2, #0
0x100034b94:	mov	w3, #0
0x100034b98:	bl	#0x100007914
0x100034b9c:	mov	x0, x20
0x100034ba0:	ldp	x29, x30, [sp, #0x10]
0x100034ba4:	ldp	x20, x19, [sp], #0x20
0x100034ba8:	autibsp	
0x100034bac:	eor	x16, x30, x30, lsl #1
0x100034bb0:	tbz	x16, #0x3e, #0x100034bb8
0x100034bb4:	brk	#0xc471
0x100034bb8:	b	#0x100006174

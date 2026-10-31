; accessoryd 0x10011d148-0x10011d1c4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10011d148:	cbz	x0, #0x10011d1c0
0x10011d14c:	pacibsp	
0x10011d150:	stp	x22, x21, [sp, #-0x30]!
0x10011d154:	stp	x20, x19, [sp, #0x10]
0x10011d158:	stp	x29, x30, [sp, #0x20]
0x10011d15c:	add	x29, sp, #0x20
0x10011d160:	mov	x19, x0
0x10011d164:	ldr	x8, [x0, #0xc8]
0x10011d168:	cbz	x8, #0x10011d174
0x10011d16c:	mov	w21, #1
0x10011d170:	b	#0x10011d190
0x10011d174:	mov	w0, #0xffff
0x10011d178:	mov	w1, #0x7cb3
0x10011d17c:	movk	w1, #0x4c7b, lsl #16
0x10011d180:	bl	#0x1001a2370
0x10011d184:	str	x0, [x19, #0xc8]
0x10011d188:	cmp	x0, #0
0x10011d18c:	cset	w21, ne
0x10011d190:	bl	#0x10006a1d0
0x10011d194:	mov	x20, x0
0x10011d198:	bl	#0x10006a3e4
0x10011d19c:	and	w20, w20, w0
0x10011d1a0:	bl	#0x10000946c
0x10011d1a4:	bl	#0x10013e49c
0x10011d1a8:	and	w8, w20, w0
0x10011d1ac:	and	w0, w21, w8
0x10011d1b0:	ldp	x29, x30, [sp, #0x20]
0x10011d1b4:	ldp	x20, x19, [sp, #0x10]
0x10011d1b8:	ldp	x22, x21, [sp], #0x30
0x10011d1bc:	autibsp	
0x10011d1c0:	ret	

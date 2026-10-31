; accessoryd 0x10013c0ec-0x10013c148; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10013c0ec:	cbz	x0, #0x10013c13c
0x10013c0f0:	pacibsp	
0x10013c0f4:	stp	x20, x19, [sp, #-0x20]!
0x10013c0f8:	stp	x29, x30, [sp, #0x10]
0x10013c0fc:	add	x29, sp, #0x10
0x10013c100:	bl	#0x1000031f8
0x10013c104:	cbz	x0, #0x10013c130
0x10013c108:	bl	#0x100001b04
0x10013c10c:	b.ne	#0x10013c140
0x10013c110:	ldr	x8, [x0, #8]
0x10013c114:	cbz	x8, #0x10013c140
0x10013c118:	ldr	x0, [x8, #0x70]
0x10013c11c:	cbz	x0, #0x10013c130
0x10013c120:	mov	w1, w19
0x10013c124:	bl	#0x1001a1890
0x10013c128:	cmp	w0, #0
0x10013c12c:	cset	w0, ne
0x10013c130:	ldp	x29, x30, [sp, #0x10]
0x10013c134:	ldp	x20, x19, [sp], #0x20
0x10013c138:	autibsp	
0x10013c13c:	ret	
0x10013c140:	mov	w0, #0
0x10013c144:	b	#0x10013c130

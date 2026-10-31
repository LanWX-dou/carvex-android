; accessoryd 0x10000626c-0x100006314; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10000626c:	pacibsp	
0x100006270:	stp	x22, x21, [sp, #-0x30]!
0x100006274:	stp	x20, x19, [sp, #0x10]
0x100006278:	stp	x29, x30, [sp, #0x20]
0x10000627c:	add	x29, sp, #0x20
0x100006280:	mov	x20, #0
0x100006284:	cbz	x0, #0x100006300
0x100006288:	mov	x21, x1
0x10000628c:	cbz	x1, #0x100006300
0x100006290:	mov	x19, x0
0x100006294:	mov	x1, #0
0x100006298:	bl	#0x1000349e8
0x10000629c:	ldr	w8, [x21]
0x1000062a0:	cbz	w8, #0x1000062ac
0x1000062a4:	cmp	w8, w0
0x1000062a8:	b.lo	#0x1000062bc
0x1000062ac:	cmp	w8, w0
0x1000062b0:	b.ls	#0x1000062b8
0x1000062b4:	str	w0, [x21]
0x1000062b8:	mov	x8, x0
0x1000062bc:	ldr	x0, [x19, #0xf8]
0x1000062c0:	mov	w1, w8
0x1000062c4:	bl	#0x100007088
0x1000062c8:	mov	x20, x0
0x1000062cc:	cbz	x0, #0x100006300
0x1000062d0:	ldurh	w8, [x20, #0x3d]
0x1000062d4:	mov	w9, #0x1ff
0x1000062d8:	sturh	w9, [x20, #0x3b]
0x1000062dc:	strb	wzr, [x20, #0x3f]
0x1000062e0:	and	w8, w8, #0xfffff7ff
0x1000062e4:	orr	w8, w8, #0x200
0x1000062e8:	stp	xzr, xzr, [x20, #8]
0x1000062ec:	str	x19, [x20]
0x1000062f0:	sturh	w8, [x20, #0x3d]
0x1000062f4:	str	xzr, [x20, #0x20]
0x1000062f8:	mov	x0, x20
0x1000062fc:	bl	#0x10000713c
0x100006300:	mov	x0, x20
0x100006304:	ldp	x29, x30, [sp, #0x20]
0x100006308:	ldp	x20, x19, [sp, #0x10]
0x10000630c:	ldp	x22, x21, [sp], #0x30
0x100006310:	retab	

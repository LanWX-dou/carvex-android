; accessoryd 0x1000d4f44-0x1000d4fb8; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000d4f44:	ldrb	w9, [x1, #0x18]
0x1000d4f48:	cbz	x9, #0x1000d4fa0
0x1000d4f4c:	mov	x10, #0
0x1000d4f50:	mov	w8, #0
0x1000d4f54:	add	x11, x1, #0x19
0x1000d4f58:	mov	w12, #-0xffffffff80000000
0x1000d4f5c:	mov	w13, #2
0x1000d4f60:	ldrb	w14, [x11, x10]
0x1000d4f64:	cmp	w14, #0x55
0x1000d4f68:	csel	w15, w13, w12, eq
0x1000d4f6c:	cmp	w14, #0x54
0x1000d4f70:	csinc	w14, w15, wzr, ne
0x1000d4f74:	orr	w8, w14, w8
0x1000d4f78:	add	x10, x10, #1
0x1000d4f7c:	subs	x9, x9, #1
0x1000d4f80:	b.ne	#0x1000d4f60
0x1000d4f84:	tst	w8, #3
0x1000d4f88:	b.eq	#0x1000d4fa8
0x1000d4f8c:	mov	w9, #0x5554
0x1000d4f90:	sturh	w9, [x1, #0x19]
0x1000d4f94:	orr	w8, w8, #3
0x1000d4f98:	mov	w9, #2
0x1000d4f9c:	b	#0x1000d4fac
0x1000d4fa0:	mov	w8, #0
0x1000d4fa4:	b	#0x1000d4fac
0x1000d4fa8:	mov	w9, #0
0x1000d4fac:	strb	w9, [x1, #0x18]
0x1000d4fb0:	str	w8, [x0, #0x110]
0x1000d4fb4:	ret	

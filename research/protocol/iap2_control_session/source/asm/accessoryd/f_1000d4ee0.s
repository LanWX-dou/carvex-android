; accessoryd 0x1000d4ee0-0x1000d4f44; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000d4ee0:	ldrb	w9, [x0, #0x18]
0x1000d4ee4:	cbz	x9, #0x1000d4f2c
0x1000d4ee8:	mov	x10, #0
0x1000d4eec:	mov	w8, #0
0x1000d4ef0:	add	x11, x0, #0x19
0x1000d4ef4:	mov	w12, #-0xffffffff80000000
0x1000d4ef8:	mov	w13, #2
0x1000d4efc:	ldrb	w14, [x11, x10]
0x1000d4f00:	cmp	w14, #0x55
0x1000d4f04:	csel	w15, w13, w12, eq
0x1000d4f08:	cmp	w14, #0x54
0x1000d4f0c:	csinc	w14, w15, wzr, ne
0x1000d4f10:	orr	w8, w14, w8
0x1000d4f14:	add	x10, x10, #1
0x1000d4f18:	subs	x9, x9, #1
0x1000d4f1c:	b.ne	#0x1000d4efc
0x1000d4f20:	tbz	w8, #0x1f, #0x1000d4f30
0x1000d4f24:	mov	w0, #0
0x1000d4f28:	ret	
0x1000d4f2c:	mov	w8, #0
0x1000d4f30:	ands	w8, w8, #3
0x1000d4f34:	cset	w9, eq
0x1000d4f38:	cmp	w8, #3
0x1000d4f3c:	csinc	w0, w9, wzr, ne
0x1000d4f40:	ret	

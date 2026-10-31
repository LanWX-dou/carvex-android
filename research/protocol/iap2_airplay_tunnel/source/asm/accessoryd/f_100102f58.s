; accessoryd 0x100102f58-0x100102fdc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100102f58:	ldr	x8, [x0, #0x40]
0x100102f5c:	mov	x10, x8
0x100102f60:	ldrb	w9, [x10], #1
0x100102f64:	cmp	w9, #0xff
0x100102f68:	csel	x10, x8, x10, ne
0x100102f6c:	ldrb	w10, [x10]
0x100102f70:	cmp	w10, #0x55
0x100102f74:	b.ne	#0x100102fb8
0x100102f78:	cmp	w9, #0xff
0x100102f7c:	mov	w10, #1
0x100102f80:	cinc	x10, x10, eq
0x100102f84:	ldrb	w10, [x8, x10]
0x100102f88:	cmp	w10, #2
0x100102f8c:	b.ne	#0x100102fb8
0x100102f90:	cmp	w9, #0xff
0x100102f94:	mov	w10, #2
0x100102f98:	cinc	x10, x10, eq
0x100102f9c:	ldrb	w10, [x8, x10]
0x100102fa0:	cbnz	w10, #0x100102fb8
0x100102fa4:	cmp	w9, #0xff
0x100102fa8:	mov	w10, #3
0x100102fac:	cinc	x10, x10, eq
0x100102fb0:	ldrb	w10, [x8, x10]
0x100102fb4:	cbz	w10, #0x100102fc0
0x100102fb8:	mov	w0, #0
0x100102fbc:	ret	
0x100102fc0:	cmp	w9, #0xff
0x100102fc4:	mov	w9, #4
0x100102fc8:	cinc	x9, x9, eq
0x100102fcc:	ldrb	w8, [x8, x9]
0x100102fd0:	cmp	w8, #0xfe
0x100102fd4:	cset	w0, eq
0x100102fd8:	ret	

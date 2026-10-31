; accessoryd 0x100102e20-0x100102ea0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100102e20:	ldr	x8, [x0, #0x40]
0x100102e24:	mov	x11, x8
0x100102e28:	ldrb	w9, [x11], #1
0x100102e2c:	sub	w10, w9, #0xff
0x100102e30:	cmn	w10, #0xfe
0x100102e34:	cset	w9, lo
0x100102e38:	csel	x11, x8, x11, hs
0x100102e3c:	ldrb	w11, [x11]
0x100102e40:	cmp	w11, #0x55
0x100102e44:	b.ne	#0x100102e98
0x100102e48:	cmn	w10, #0xfe
0x100102e4c:	mov	w11, #1
0x100102e50:	cinc	x11, x11, lo
0x100102e54:	ldrb	w11, [x8, x11]
0x100102e58:	cmp	w11, #2
0x100102e5c:	b.ne	#0x100102e98
0x100102e60:	orr	x11, x9, #2
0x100102e64:	ldrb	w11, [x8, x11]
0x100102e68:	cbnz	w11, #0x100102e98
0x100102e6c:	cmn	w10, #0xfe
0x100102e70:	mov	w10, #3
0x100102e74:	cinc	x10, x10, lo
0x100102e78:	ldrb	w10, [x8, x10]
0x100102e7c:	cmp	w10, #0xee
0x100102e80:	b.ne	#0x100102e98
0x100102e84:	orr	x9, x9, #4
0x100102e88:	ldrb	w8, [x8, x9]
0x100102e8c:	cmp	w8, #0x10
0x100102e90:	cset	w0, eq
0x100102e94:	ret	
0x100102e98:	mov	w0, #0
0x100102e9c:	ret	

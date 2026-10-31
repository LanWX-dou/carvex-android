; accessoryd 0x100102ea0-0x100102f58; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100102ea0:	ldr	x8, [x0, #0x40]
0x100102ea4:	mov	x10, x8
0x100102ea8:	ldrb	w9, [x10], #1
0x100102eac:	cmp	w9, #0xff
0x100102eb0:	csel	x10, x8, x10, ne
0x100102eb4:	ldrb	w10, [x10]
0x100102eb8:	cmp	w10, #0x55
0x100102ebc:	b.ne	#0x100102f50
0x100102ec0:	cmp	w9, #0xff
0x100102ec4:	mov	w10, #1
0x100102ec8:	cinc	x10, x10, eq
0x100102ecc:	ldrb	w10, [x8, x10]
0x100102ed0:	cmp	w10, #4
0x100102ed4:	b.ne	#0x100102f50
0x100102ed8:	cmp	w9, #0xff
0x100102edc:	mov	w10, #2
0x100102ee0:	cinc	x10, x10, eq
0x100102ee4:	ldrb	w10, [x8, x10]
0x100102ee8:	cbnz	w10, #0x100102f50
0x100102eec:	cmp	w9, #0xff
0x100102ef0:	mov	w10, #3
0x100102ef4:	cinc	x10, x10, eq
0x100102ef8:	ldrb	w10, [x8, x10]
0x100102efc:	cmp	w10, #2
0x100102f00:	b.ne	#0x100102f50
0x100102f04:	cmp	w9, #0xff
0x100102f08:	mov	w10, #4
0x100102f0c:	cinc	x10, x10, eq
0x100102f10:	ldrb	w10, [x8, x10]
0x100102f14:	cmp	w10, #4
0x100102f18:	b.ne	#0x100102f50
0x100102f1c:	cmp	w9, #0xff
0x100102f20:	mov	w10, #5
0x100102f24:	cinc	x10, x10, eq
0x100102f28:	ldrb	w10, [x8, x10]
0x100102f2c:	cmp	w10, #0xee
0x100102f30:	b.ne	#0x100102f50
0x100102f34:	cmp	w9, #0xff
0x100102f38:	mov	w9, #6
0x100102f3c:	cinc	x9, x9, eq
0x100102f40:	ldrb	w8, [x8, x9]
0x100102f44:	cmp	w8, #8
0x100102f48:	cset	w0, eq
0x100102f4c:	ret	
0x100102f50:	mov	w0, #0
0x100102f54:	ret	

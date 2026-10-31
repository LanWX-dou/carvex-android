; accessoryd 0x100131c14-0x100131c5c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100131c14:	cbz	x1, #0x100131c58
0x100131c18:	pacibsp	
0x100131c1c:	stp	x20, x19, [sp, #-0x20]!
0x100131c20:	stp	x29, x30, [sp, #0x10]
0x100131c24:	add	x29, sp, #0x10
0x100131c28:	mov	x19, x1
0x100131c2c:	ldr	x0, [x1, #8]
0x100131c30:	cbz	x0, #0x100131c38
0x100131c34:	bl	#0x1001a1820
0x100131c38:	mov	x0, x19
0x100131c3c:	ldp	x29, x30, [sp, #0x10]
0x100131c40:	ldp	x20, x19, [sp], #0x20
0x100131c44:	autibsp	
0x100131c48:	eor	x16, x30, x30, lsl #1
0x100131c4c:	tbz	x16, #0x3e, #0x100131c54
0x100131c50:	brk	#0xc471
0x100131c54:	b	#0x1001a22d0
0x100131c58:	ret	

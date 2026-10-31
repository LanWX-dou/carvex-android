; accessoryd 0x100081e20-0x100081e3c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100081e20:	stur	w19, [x29, #-0x54]
0x100081e24:	sub	x1, x29, #0x54
0x100081e28:	mov	x0, x25
0x100081e2c:	eor	x16, x30, x30, lsl #1
0x100081e30:	tbz	x16, #0x3e, #0x100081e38
0x100081e34:	brk	#0xc471
0x100081e38:	b	#0x100067df0

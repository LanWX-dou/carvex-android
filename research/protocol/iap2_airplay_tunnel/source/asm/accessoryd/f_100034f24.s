; accessoryd 0x100034f24-0x100034f50; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100034f24:	cbz	x0, #0x100034f40
0x100034f28:	ldr	x0, [x0, #8]
0x100034f2c:	mov	x1, x2
0x100034f30:	eor	x16, x30, x30, lsl #1
0x100034f34:	tbz	x16, #0x3e, #0x100034f3c
0x100034f38:	brk	#0xc471
0x100034f3c:	b	#0x10000639c
0x100034f40:	pacibsp	
0x100034f44:	stp	x29, x30, [sp, #-0x10]!
0x100034f48:	mov	x29, sp
0x100034f4c:	bl	#0x10012bb50

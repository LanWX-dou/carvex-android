; accessoryd 0x100031c7c-0x100031cc0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100031c7c:	pacibsp	
0x100031c80:	stp	x29, x30, [sp, #-0x10]!
0x100031c84:	mov	x29, sp
0x100031c88:	cbz	x0, #0x100031cb8
0x100031c8c:	cbz	x1, #0x100031cbc
0x100031c90:	mov	w8, #0x1d
0x100031c94:	strb	w8, [x1]
0x100031c98:	ldr	x0, [x0, #0x10]
0x100031c9c:	mov	w1, #0
0x100031ca0:	ldp	x29, x30, [sp], #0x10
0x100031ca4:	autibsp	
0x100031ca8:	eor	x16, x30, x30, lsl #1
0x100031cac:	tbz	x16, #0x3e, #0x100031cb4
0x100031cb0:	brk	#0xc471
0x100031cb4:	b	#0x100103970
0x100031cb8:	bl	#0x10012b594
0x100031cbc:	bl	#0x10012b56c

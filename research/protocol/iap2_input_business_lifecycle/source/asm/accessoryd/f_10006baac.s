; accessoryd 0x10006baac-0x10006baec; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10006baac:	pacibsp	
0x10006bab0:	stp	x29, x30, [sp, #-0x10]!
0x10006bab4:	mov	x29, sp
0x10006bab8:	mov	x8, x0
0x10006babc:	ldr	x0, [x29, #0x10]
0x10006bac0:	cbz	x0, #0x10006bae8
0x10006bac4:	str	x3, [x0]
0x10006bac8:	strb	w2, [x0, #9]
0x10006bacc:	strb	w8, [x0, #8]
0x10006bad0:	strb	w1, [x0, #0xa]
0x10006bad4:	strb	w2, [x0, #0xb]
0x10006bad8:	stp	x4, x5, [x0, #0x10]
0x10006badc:	stp	x6, x7, [x0, #0x20]
0x10006bae0:	ldp	x29, x30, [sp], #0x10
0x10006bae4:	retab	
0x10006bae8:	bl	#0x10013f058

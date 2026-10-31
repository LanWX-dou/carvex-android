; accessoryd 0x10000bc04-0x10000bc30; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10000bc04:	pacibsp	
0x10000bc08:	stp	x29, x30, [sp, #-0x10]!
0x10000bc0c:	mov	x29, sp
0x10000bc10:	cbz	x0, #0x10000bc28
0x10000bc14:	cbz	x1, #0x10000bc2c
0x10000bc18:	mov	w8, #0x1d
0x10000bc1c:	strb	w8, [x1]
0x10000bc20:	ldp	x29, x30, [sp], #0x10
0x10000bc24:	retab	
0x10000bc28:	bl	#0x10012b4c8
0x10000bc2c:	bl	#0x10012b4a0

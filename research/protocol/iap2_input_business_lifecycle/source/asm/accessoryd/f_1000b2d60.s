; accessoryd 0x1000b2d60-0x1000b2dbc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000b2d60:	pacibsp	
0x1000b2d64:	stp	x22, x21, [sp, #-0x30]!
0x1000b2d68:	stp	x20, x19, [sp, #0x10]
0x1000b2d6c:	stp	x29, x30, [sp, #0x20]
0x1000b2d70:	add	x29, sp, #0x20
0x1000b2d74:	mov	x19, x2
0x1000b2d78:	mov	x20, x1
0x1000b2d7c:	mov	x21, x0
0x1000b2d80:	adrp	x8, #0x10022a000
0x1000b2d84:	ldr	x0, [x8, #0xed8]
0x1000b2d88:	bl	#0x1001aadc0
0x1000b2d8c:	bl	#0x1001a2490
0x1000b2d90:	mov	x22, x0
0x1000b2d94:	mov	x2, x21
0x1000b2d98:	mov	x3, x20
0x1000b2d9c:	mov	x4, x19
0x1000b2da0:	bl	#0x1001a7020
0x1000b2da4:	bl	#0x1001a25a0
0x1000b2da8:	mov	w0, #1
0x1000b2dac:	ldp	x29, x30, [sp, #0x20]
0x1000b2db0:	ldp	x20, x19, [sp, #0x10]
0x1000b2db4:	ldp	x22, x21, [sp], #0x30
0x1000b2db8:	retab	

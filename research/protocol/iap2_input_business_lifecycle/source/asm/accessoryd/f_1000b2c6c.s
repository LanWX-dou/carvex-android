; accessoryd 0x1000b2c6c-0x1000b2cc8; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000b2c6c:	pacibsp	
0x1000b2c70:	stp	x22, x21, [sp, #-0x30]!
0x1000b2c74:	stp	x20, x19, [sp, #0x10]
0x1000b2c78:	stp	x29, x30, [sp, #0x20]
0x1000b2c7c:	add	x29, sp, #0x20
0x1000b2c80:	mov	x19, x2
0x1000b2c84:	mov	x20, x1
0x1000b2c88:	mov	x21, x0
0x1000b2c8c:	adrp	x8, #0x10022a000
0x1000b2c90:	ldr	x0, [x8, #0xed8]
0x1000b2c94:	bl	#0x1001aadc0
0x1000b2c98:	bl	#0x1001a2490
0x1000b2c9c:	mov	x22, x0
0x1000b2ca0:	mov	x2, x21
0x1000b2ca4:	mov	x3, x20
0x1000b2ca8:	mov	x4, x19
0x1000b2cac:	bl	#0x1001a9100
0x1000b2cb0:	bl	#0x1001a25a0
0x1000b2cb4:	mov	w0, #1
0x1000b2cb8:	ldp	x29, x30, [sp, #0x20]
0x1000b2cbc:	ldp	x20, x19, [sp, #0x10]
0x1000b2cc0:	ldp	x22, x21, [sp], #0x30
0x1000b2cc4:	retab	

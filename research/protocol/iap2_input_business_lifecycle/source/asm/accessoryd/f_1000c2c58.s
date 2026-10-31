; accessoryd 0x1000c2c58-0x1000c2d0c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000c2c58:	cbz	x0, #0x1000c2d08
0x1000c2c5c:	pacibsp	
0x1000c2c60:	sub	sp, sp, #0x50
0x1000c2c64:	stp	x20, x19, [sp, #0x30]
0x1000c2c68:	stp	x29, x30, [sp, #0x40]
0x1000c2c6c:	add	x29, sp, #0x40
0x1000c2c70:	mov	x20, x0
0x1000c2c74:	ldr	x0, [x0, #8]
0x1000c2c78:	cbz	x0, #0x1000c2cf8
0x1000c2c7c:	bl	#0x1001a1830
0x1000c2c80:	mov	x19, x0
0x1000c2c84:	ldr	x8, [x20]
0x1000c2c88:	cbz	x8, #0x1000c2ca4
0x1000c2c8c:	ldr	x8, [x8, #0x40]
0x1000c2c90:	cbz	x8, #0x1000c2ca4
0x1000c2c94:	ldr	x0, [x8, #0x10]
0x1000c2c98:	cbz	x0, #0x1000c2ca8
0x1000c2c9c:	bl	#0x1001a1830
0x1000c2ca0:	b	#0x1000c2ca8
0x1000c2ca4:	mov	x0, #0
0x1000c2ca8:	mov	x8, sp
0x1000c2cac:	adrp	x16, #0x10022b000
0x1000c2cb0:	ldr	x16, [x16, #0xb78]
0x1000c2cb4:	mov	x17, x8
0x1000c2cb8:	movk	x17, #0x6ae1, lsl #48
0x1000c2cbc:	pacda	x16, x17
0x1000c2cc0:	str	x16, [sp]
0x1000c2cc4:	adrp	x9, #0x1001b3000
0x1000c2cc8:	ldr	d0, [x9, #0x118]
0x1000c2ccc:	str	d0, [sp, #8]
0x1000c2cd0:	add	x8, x8, #0x10
0x1000c2cd4:	adrp	x9, #0x10021f000
0x1000c2cd8:	add	x9, x9, #0xb8
0x1000c2cdc:	adrp	x16, #0x1000c2000
0x1000c2ce0:	add	x16, x16, #0xd0c
0x1000c2ce4:	pacia	x16, x8
0x1000c2ce8:	stp	x16, x9, [sp, #0x10]
0x1000c2cec:	stp	x19, x0, [sp, #0x20]
0x1000c2cf0:	mov	x0, sp
0x1000c2cf4:	bl	#0x100031a20
0x1000c2cf8:	ldp	x29, x30, [sp, #0x40]
0x1000c2cfc:	ldp	x20, x19, [sp, #0x30]
0x1000c2d00:	add	sp, sp, #0x50
0x1000c2d04:	autibsp	
0x1000c2d08:	ret	

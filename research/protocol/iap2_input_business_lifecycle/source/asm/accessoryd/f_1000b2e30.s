; accessoryd 0x1000b2e30-0x1000b2ed0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000b2e30:	pacibsp	
0x1000b2e34:	stp	x22, x21, [sp, #-0x30]!
0x1000b2e38:	stp	x20, x19, [sp, #0x10]
0x1000b2e3c:	stp	x29, x30, [sp, #0x20]
0x1000b2e40:	add	x29, sp, #0x20
0x1000b2e44:	mov	x20, x2
0x1000b2e48:	mov	x21, x1
0x1000b2e4c:	mov	x22, x0
0x1000b2e50:	adrp	x2, #0x10022b000
0x1000b2e54:	ldr	x2, [x2, #0xd40]
0x1000b2e58:	adrp	x3, #0x10022b000
0x1000b2e5c:	ldr	x3, [x3, #0xd48]
0x1000b2e60:	mov	x0, #0
0x1000b2e64:	mov	x1, #0
0x1000b2e68:	bl	#0x1001a1630
0x1000b2e6c:	mov	x19, x0
0x1000b2e70:	adrp	x8, #0x10021a000
0x1000b2e74:	add	x8, x8, #0x2c0
0x1000b2e78:	ldr	x1, [x8]
0x1000b2e7c:	mov	x2, x21
0x1000b2e80:	bl	#0x1001a15e0
0x1000b2e84:	adrp	x8, #0x10021a000
0x1000b2e88:	add	x8, x8, #0x2b8
0x1000b2e8c:	ldr	x1, [x8]
0x1000b2e90:	mov	x0, x19
0x1000b2e94:	mov	x2, x20
0x1000b2e98:	bl	#0x1001a15e0
0x1000b2e9c:	mov	x0, x22
0x1000b2ea0:	mov	w1, #0x12c
0x1000b2ea4:	mov	x2, x19
0x1000b2ea8:	bl	#0x1000022a4
0x1000b2eac:	mov	x20, x0
0x1000b2eb0:	cbz	x19, #0x1000b2ebc
0x1000b2eb4:	mov	x0, x19
0x1000b2eb8:	bl	#0x1001a1820
0x1000b2ebc:	mov	x0, x20
0x1000b2ec0:	ldp	x29, x30, [sp, #0x20]
0x1000b2ec4:	ldp	x20, x19, [sp, #0x10]
0x1000b2ec8:	ldp	x22, x21, [sp], #0x30
0x1000b2ecc:	retab	

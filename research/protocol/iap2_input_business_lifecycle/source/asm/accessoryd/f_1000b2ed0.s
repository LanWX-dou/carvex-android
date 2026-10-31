; accessoryd 0x1000b2ed0-0x1000b2f94; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000b2ed0:	pacibsp	
0x1000b2ed4:	stp	x24, x23, [sp, #-0x40]!
0x1000b2ed8:	stp	x22, x21, [sp, #0x10]
0x1000b2edc:	stp	x20, x19, [sp, #0x20]
0x1000b2ee0:	stp	x29, x30, [sp, #0x30]
0x1000b2ee4:	add	x29, sp, #0x30
0x1000b2ee8:	mov	x20, x3
0x1000b2eec:	mov	x21, x2
0x1000b2ef0:	mov	x22, x1
0x1000b2ef4:	mov	x23, x0
0x1000b2ef8:	adrp	x2, #0x10022b000
0x1000b2efc:	ldr	x2, [x2, #0xd40]
0x1000b2f00:	adrp	x3, #0x10022b000
0x1000b2f04:	ldr	x3, [x3, #0xd48]
0x1000b2f08:	mov	x0, #0
0x1000b2f0c:	mov	x1, #0
0x1000b2f10:	bl	#0x1001a1630
0x1000b2f14:	mov	x19, x0
0x1000b2f18:	adrp	x8, #0x10021a000
0x1000b2f1c:	add	x8, x8, #0x2c0
0x1000b2f20:	ldr	x1, [x8]
0x1000b2f24:	mov	x2, x22
0x1000b2f28:	bl	#0x1001a15e0
0x1000b2f2c:	adrp	x8, #0x10021a000
0x1000b2f30:	add	x8, x8, #0x2c8
0x1000b2f34:	ldr	x1, [x8]
0x1000b2f38:	mov	x0, x19
0x1000b2f3c:	mov	x2, x21
0x1000b2f40:	bl	#0x1001a15e0
0x1000b2f44:	adrp	x8, #0x10021a000
0x1000b2f48:	add	x8, x8, #0x2d0
0x1000b2f4c:	ldr	x1, [x8]
0x1000b2f50:	mov	x0, x19
0x1000b2f54:	mov	x2, x20
0x1000b2f58:	bl	#0x1001a15e0
0x1000b2f5c:	mov	x0, x23
0x1000b2f60:	mov	w1, #0x12d
0x1000b2f64:	mov	x2, x19
0x1000b2f68:	bl	#0x1000022a4
0x1000b2f6c:	mov	x20, x0
0x1000b2f70:	cbz	x19, #0x1000b2f7c
0x1000b2f74:	mov	x0, x19
0x1000b2f78:	bl	#0x1001a1820
0x1000b2f7c:	mov	x0, x20
0x1000b2f80:	ldp	x29, x30, [sp, #0x30]
0x1000b2f84:	ldp	x20, x19, [sp, #0x20]
0x1000b2f88:	ldp	x22, x21, [sp, #0x10]
0x1000b2f8c:	ldp	x24, x23, [sp], #0x40
0x1000b2f90:	retab	

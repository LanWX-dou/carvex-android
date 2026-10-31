; accessoryd 0x100067c6c-0x100067ce0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100067c6c:	pacibsp	
0x100067c70:	stp	x22, x21, [sp, #-0x30]!
0x100067c74:	stp	x20, x19, [sp, #0x10]
0x100067c78:	stp	x29, x30, [sp, #0x20]
0x100067c7c:	add	x29, sp, #0x20
0x100067c80:	add	w8, w4, #4
0x100067c84:	ldp	x9, x21, [x0, #0x18]
0x100067c88:	add	x10, x21, x8
0x100067c8c:	sub	x9, x10, x9
0x100067c90:	ldr	w10, [x0, #0x10]
0x100067c94:	cmp	x9, x10
0x100067c98:	csel	x22, xzr, x21, gt
0x100067c9c:	cbz	x22, #0x100067ccc
0x100067ca0:	mov	x20, x4
0x100067ca4:	mov	x19, x3
0x100067ca8:	mov	x5, x1
0x100067cac:	and	w4, w8, #0xffff
0x100067cb0:	mov	x1, x21
0x100067cb4:	mov	w3, #9
0x100067cb8:	bl	#0x100003a68
0x100067cbc:	mov	w2, w20
0x100067cc0:	add	x0, x21, #4
0x100067cc4:	mov	x1, x19
0x100067cc8:	bl	#0x1001a23a0
0x100067ccc:	mov	x0, x22
0x100067cd0:	ldp	x29, x30, [sp, #0x20]
0x100067cd4:	ldp	x20, x19, [sp, #0x10]
0x100067cd8:	ldp	x22, x21, [sp], #0x30
0x100067cdc:	retab	

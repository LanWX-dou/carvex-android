; accessoryd 0x100037e68-0x100037ecc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100037e68:	pacibsp	
0x100037e6c:	stp	x20, x19, [sp, #-0x20]!
0x100037e70:	stp	x29, x30, [sp, #0x10]
0x100037e74:	add	x29, sp, #0x10
0x100037e78:	cbz	x0, #0x100037ea4
0x100037e7c:	mov	x20, x1
0x100037e80:	mov	x19, x0
0x100037e84:	ldr	x0, [x0, #0x140]
0x100037e88:	cbz	x0, #0x100037e90
0x100037e8c:	bl	#0x1001a1f20
0x100037e90:	cbz	x20, #0x100037eb8
0x100037e94:	mov	x0, x20
0x100037e98:	bl	#0x1001a1f00
0x100037e9c:	str	x0, [x19, #0x140]
0x100037ea0:	b	#0x100037eb8
0x100037ea4:	adrp	x0, #0x10022b000
0x100037ea8:	ldr	x0, [x0, #0xbb0]
0x100037eac:	mov	w1, #0x10
0x100037eb0:	bl	#0x1001a2830
0x100037eb4:	cbnz	w0, #0x100037ec4
0x100037eb8:	ldp	x29, x30, [sp, #0x10]
0x100037ebc:	ldp	x20, x19, [sp], #0x20
0x100037ec0:	retab	
0x100037ec4:	bl	#0x10012e384
0x100037ec8:	b	#0x100037eb8

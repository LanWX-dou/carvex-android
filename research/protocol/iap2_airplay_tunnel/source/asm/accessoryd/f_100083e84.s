; accessoryd 0x100083e84-0x100083ecc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100083e84:	pacibsp	
0x100083e88:	stp	x22, x21, [sp, #-0x30]!
0x100083e8c:	stp	x20, x19, [sp, #0x10]
0x100083e90:	stp	x29, x30, [sp, #0x20]
0x100083e94:	add	x29, sp, #0x20
0x100083e98:	mov	x19, #0
0x100083e9c:	add	x20, x0, #0xe8
0x100083ea0:	mov	w21, #3
0x100083ea4:	ldr	x8, [x20, x19, lsl #3]
0x100083ea8:	str	xzr, [x20, x19, lsl #3]
0x100083eac:	bl	#0x1001a2610
0x100083eb0:	add	x19, x19, #1
0x100083eb4:	subs	x21, x21, #1
0x100083eb8:	b.ne	#0x100083ea4
0x100083ebc:	ldp	x29, x30, [sp, #0x20]
0x100083ec0:	ldp	x20, x19, [sp, #0x10]
0x100083ec4:	ldp	x22, x21, [sp], #0x30
0x100083ec8:	retab	

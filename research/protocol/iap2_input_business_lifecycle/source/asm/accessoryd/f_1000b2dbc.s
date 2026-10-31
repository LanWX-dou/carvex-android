; accessoryd 0x1000b2dbc-0x1000b2e30; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000b2dbc:	pacibsp	
0x1000b2dc0:	stp	x24, x23, [sp, #-0x40]!
0x1000b2dc4:	stp	x22, x21, [sp, #0x10]
0x1000b2dc8:	stp	x20, x19, [sp, #0x20]
0x1000b2dcc:	stp	x29, x30, [sp, #0x30]
0x1000b2dd0:	add	x29, sp, #0x30
0x1000b2dd4:	mov	x19, x4
0x1000b2dd8:	mov	x20, x3
0x1000b2ddc:	mov	x21, x2
0x1000b2de0:	mov	x22, x1
0x1000b2de4:	mov	x23, x0
0x1000b2de8:	adrp	x8, #0x10022a000
0x1000b2dec:	ldr	x0, [x8, #0xed8]
0x1000b2df0:	bl	#0x1001aadc0
0x1000b2df4:	bl	#0x1001a2490
0x1000b2df8:	mov	x24, x0
0x1000b2dfc:	mov	x2, x23
0x1000b2e00:	mov	x3, x22
0x1000b2e04:	mov	x4, x21
0x1000b2e08:	mov	x5, x20
0x1000b2e0c:	mov	x6, x19
0x1000b2e10:	bl	#0x1001a6ba0
0x1000b2e14:	bl	#0x1001a25c0
0x1000b2e18:	mov	w0, #1
0x1000b2e1c:	ldp	x29, x30, [sp, #0x30]
0x1000b2e20:	ldp	x20, x19, [sp, #0x20]
0x1000b2e24:	ldp	x22, x21, [sp, #0x10]
0x1000b2e28:	ldp	x24, x23, [sp], #0x40
0x1000b2e2c:	retab	

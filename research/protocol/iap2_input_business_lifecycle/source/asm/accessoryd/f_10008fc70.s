; accessoryd 0x10008fc70-0x10008fcb0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008fc70:	pacibsp	
0x10008fc74:	sub	sp, sp, #0x20
0x10008fc78:	stp	x29, x30, [sp, #0x10]
0x10008fc7c:	add	x29, sp, #0x10
0x10008fc80:	bl	#0x10008f3b8
0x10008fc84:	bl	#0x1001a2490
0x10008fc88:	str	x0, [sp, #8]
0x10008fc8c:	bl	#0x1001a7080
0x10008fc90:	ldr	x0, [sp, #8]
0x10008fc94:	ldp	x29, x30, [sp, #0x10]
0x10008fc98:	add	sp, sp, #0x20
0x10008fc9c:	autibsp	
0x10008fca0:	eor	x16, x30, x30, lsl #1
0x10008fca4:	tbz	x16, #0x3e, #0x10008fcac
0x10008fca8:	brk	#0xc471
0x10008fcac:	b	#0x1001a2540

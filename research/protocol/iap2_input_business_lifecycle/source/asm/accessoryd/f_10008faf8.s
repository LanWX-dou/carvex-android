; accessoryd 0x10008faf8-0x10008fb78; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008faf8:	pacibsp	
0x10008fafc:	sub	sp, sp, #0x50
0x10008fb00:	stp	x24, x23, [sp, #0x10]
0x10008fb04:	stp	x22, x21, [sp, #0x20]
0x10008fb08:	stp	x20, x19, [sp, #0x30]
0x10008fb0c:	stp	x29, x30, [sp, #0x40]
0x10008fb10:	add	x29, sp, #0x40
0x10008fb14:	mov	x19, x4
0x10008fb18:	mov	x20, x3
0x10008fb1c:	mov	x21, x2
0x10008fb20:	mov	x22, x1
0x10008fb24:	mov	x23, x0
0x10008fb28:	bl	#0x10008f3b8
0x10008fb2c:	bl	#0x1001a2490
0x10008fb30:	str	x0, [sp, #8]
0x10008fb34:	mov	x2, x23
0x10008fb38:	mov	x3, x22
0x10008fb3c:	mov	x4, x21
0x10008fb40:	mov	x5, x20
0x10008fb44:	mov	x6, x19
0x10008fb48:	bl	#0x1001a9680
0x10008fb4c:	ldr	x0, [sp, #8]
0x10008fb50:	ldp	x29, x30, [sp, #0x40]
0x10008fb54:	ldp	x20, x19, [sp, #0x30]
0x10008fb58:	ldp	x22, x21, [sp, #0x20]
0x10008fb5c:	ldp	x24, x23, [sp, #0x10]
0x10008fb60:	add	sp, sp, #0x50
0x10008fb64:	autibsp	
0x10008fb68:	eor	x16, x30, x30, lsl #1
0x10008fb6c:	tbz	x16, #0x3e, #0x10008fb74
0x10008fb70:	brk	#0xc471
0x10008fb74:	b	#0x1001a2540

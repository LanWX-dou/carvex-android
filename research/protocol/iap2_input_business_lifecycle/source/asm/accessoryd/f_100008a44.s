; accessoryd 0x100008a44-0x100008ae8; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100008a44:	pacibsp	
0x100008a48:	stp	x24, x23, [sp, #-0x40]!
0x100008a4c:	stp	x22, x21, [sp, #0x10]
0x100008a50:	stp	x20, x19, [sp, #0x20]
0x100008a54:	stp	x29, x30, [sp, #0x30]
0x100008a58:	add	x29, sp, #0x30
0x100008a5c:	cbz	x0, #0x100008ad4
0x100008a60:	mov	x19, x1
0x100008a64:	cbz	x1, #0x100008ad4
0x100008a68:	ldr	x8, [x0, #0xb0]
0x100008a6c:	cbz	x8, #0x100008ad4
0x100008a70:	ldr	x20, [x8, #0x10]
0x100008a74:	cbz	x20, #0x100008ad4
0x100008a78:	mov	x0, x19
0x100008a7c:	bl	#0x1000088b8
0x100008a80:	mov	x21, x0
0x100008a84:	ldrh	w22, [x19, #0x36]
0x100008a88:	ldp	x0, x23, [x20]
0x100008a8c:	bl	#0x10018f0f4
0x100008a90:	mov	x1, x0
0x100008a94:	mov	x0, x23
0x100008a98:	mov	x2, x19
0x100008a9c:	mov	w3, #0
0x100008aa0:	bl	#0x1000681d8
0x100008aa4:	mov	x0, x20
0x100008aa8:	mov	x1, x21
0x100008aac:	mov	x2, x22
0x100008ab0:	ldp	x29, x30, [sp, #0x30]
0x100008ab4:	ldp	x20, x19, [sp, #0x20]
0x100008ab8:	ldp	x22, x21, [sp, #0x10]
0x100008abc:	ldp	x24, x23, [sp], #0x40
0x100008ac0:	autibsp	
0x100008ac4:	eor	x16, x30, x30, lsl #1
0x100008ac8:	tbz	x16, #0x3e, #0x100008ad0
0x100008acc:	brk	#0xc471
0x100008ad0:	b	#0x1000059a0
0x100008ad4:	ldp	x29, x30, [sp, #0x30]
0x100008ad8:	ldp	x20, x19, [sp, #0x20]
0x100008adc:	ldp	x22, x21, [sp, #0x10]
0x100008ae0:	ldp	x24, x23, [sp], #0x40
0x100008ae4:	retab	

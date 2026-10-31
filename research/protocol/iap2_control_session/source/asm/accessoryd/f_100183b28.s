; accessoryd 0x100183b28-0x100183b8c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100183b28:	cbz	x0, #0x100183b80
0x100183b2c:	ldr	x8, [x0, #0x28]
0x100183b30:	cbz	x8, #0x100183b7c
0x100183b34:	pacibsp	
0x100183b38:	stp	x20, x19, [sp, #-0x20]!
0x100183b3c:	stp	x29, x30, [sp, #0x10]
0x100183b40:	add	x29, sp, #0x10
0x100183b44:	ldr	x19, [x8, #0x18]
0x100183b48:	cbz	x19, #0x100183b84
0x100183b4c:	mov	x0, x19
0x100183b50:	mov	w1, #1
0x100183b54:	bl	#0x100005740
0x100183b58:	mov	x1, x0
0x100183b5c:	mov	x0, x19
0x100183b60:	bl	#0x100032828
0x100183b64:	cbz	x0, #0x100183b6c
0x100183b68:	ldrb	w0, [x0, #2]
0x100183b6c:	ldp	x29, x30, [sp, #0x10]
0x100183b70:	ldp	x20, x19, [sp], #0x20
0x100183b74:	autibsp	
0x100183b78:	ret	
0x100183b7c:	mov	w0, #0
0x100183b80:	ret	
0x100183b84:	mov	w0, #0
0x100183b88:	b	#0x100183b6c

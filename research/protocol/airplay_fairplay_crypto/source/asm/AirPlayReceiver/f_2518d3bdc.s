; AirPlayReceiver 0x2518d3bdc-0x2518d3c74; source SHA256 ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2518d3bdc:	pacibsp	
0x2518d3be0:	stp	x24, x23, [sp, #-0x40]!
0x2518d3be4:	stp	x22, x21, [sp, #0x10]
0x2518d3be8:	stp	x20, x19, [sp, #0x20]
0x2518d3bec:	stp	x29, x30, [sp, #0x30]
0x2518d3bf0:	add	x29, sp, #0x30
0x2518d3bf4:	mov	x19, x2
0x2518d3bf8:	mov	x21, x1
0x2518d3bfc:	mov	x20, x0
0x2518d3c00:	add	x23, x0, #0x140
0x2518d3c04:	mov	x0, x23
0x2518d3c08:	bl	#0x258109180
0x2518d3c0c:	str	xzr, [x20, #0x158]
0x2518d3c10:	mov	x0, x23
0x2518d3c14:	mov	x1, x21
0x2518d3c18:	mov	x2, x19
0x2518d3c1c:	mov	w3, #0
0x2518d3c20:	bl	#0x258109190
0x2518d3c24:	mov	x22, x0
0x2518d3c28:	cbnz	w0, #0x2518d3c58
0x2518d3c2c:	str	x23, [x20, #0x158]
0x2518d3c30:	ldr	q0, [x21]
0x2518d3c34:	str	q0, [x20, #0x160]
0x2518d3c38:	ldr	q0, [x19]
0x2518d3c3c:	str	q0, [x20, #0x170]
0x2518d3c40:	mov	x0, x22
0x2518d3c44:	ldp	x29, x30, [sp, #0x30]
0x2518d3c48:	ldp	x20, x19, [sp, #0x20]
0x2518d3c4c:	ldp	x22, x21, [sp, #0x10]
0x2518d3c50:	ldp	x24, x23, [sp], #0x40
0x2518d3c54:	retab	
0x2518d3c58:	adrp	x1, #0x251944000
0x2518d3c5c:	add	x1, x1, #0xad9
0x2518d3c60:	mov	x0, x22
0x2518d3c64:	mov	w2, #0x153f
0x2518d3c68:	mov	w3, #0
0x2518d3c6c:	bl	#0x258109a30
0x2518d3c70:	b	#0x2518d3c40

; accessoryd 0x100024cb8-0x100024d54; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100024cb8:	pacibsp	
0x100024cbc:	stp	x24, x23, [sp, #-0x40]!
0x100024cc0:	stp	x22, x21, [sp, #0x10]
0x100024cc4:	stp	x20, x19, [sp, #0x20]
0x100024cc8:	stp	x29, x30, [sp, #0x30]
0x100024ccc:	add	x29, sp, #0x30
0x100024cd0:	cmp	x3, #0
0x100024cd4:	ccmp	x4, #0, #4, ne
0x100024cd8:	ccmp	x5, #0, #4, ne
0x100024cdc:	cset	w19, ne
0x100024ce0:	b.eq	#0x100024d3c
0x100024ce4:	mov	x20, x5
0x100024ce8:	mov	x21, x2
0x100024cec:	bl	#0x1001a2740
0x100024cf0:	mov	x22, x0
0x100024cf4:	bl	#0x1001a26c0
0x100024cf8:	mov	x21, x0
0x100024cfc:	mov	x0, x20
0x100024d00:	bl	#0x1001a30a0
0x100024d04:	bl	#0x1001a2490
0x100024d08:	mov	x20, x0
0x100024d0c:	adrp	x2, #0x100218000
0x100024d10:	add	x2, x2, #0x2d8
0x100024d14:	bl	#0x1001a9220
0x100024d18:	bl	#0x1001a2490
0x100024d1c:	mov	x23, x0
0x100024d20:	mov	x2, x21
0x100024d24:	mov	x3, x22
0x100024d28:	bl	#0x1001a9040
0x100024d2c:	bl	#0x1001a25a0
0x100024d30:	bl	#0x1001a2590
0x100024d34:	bl	#0x1001a25b0
0x100024d38:	bl	#0x1001a2580
0x100024d3c:	mov	x0, x19
0x100024d40:	ldp	x29, x30, [sp, #0x30]
0x100024d44:	ldp	x20, x19, [sp, #0x20]
0x100024d48:	ldp	x22, x21, [sp, #0x10]
0x100024d4c:	ldp	x24, x23, [sp], #0x40
0x100024d50:	retab	

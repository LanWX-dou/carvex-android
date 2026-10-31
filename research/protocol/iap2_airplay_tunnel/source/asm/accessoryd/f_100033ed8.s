; accessoryd 0x100033ed8-0x100033fd0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100033ed8:	pacibsp	
0x100033edc:	stp	x24, x23, [sp, #-0x40]!
0x100033ee0:	stp	x22, x21, [sp, #0x10]
0x100033ee4:	stp	x20, x19, [sp, #0x20]
0x100033ee8:	stp	x29, x30, [sp, #0x30]
0x100033eec:	add	x29, sp, #0x30
0x100033ef0:	mov	x20, x1
0x100033ef4:	mov	x19, x0
0x100033ef8:	add	w22, w0, #2
0x100033efc:	bl	#0x10006baa4
0x100033f00:	mov	x21, x0
0x100033f04:	and	w0, w22, #0xff
0x100033f08:	bl	#0x1000ebe00
0x100033f0c:	mov	x22, x0
0x100033f10:	bl	#0x1000831a0
0x100033f14:	mov	x23, x0
0x100033f18:	mov	w0, #0
0x100033f1c:	mov	w1, #0
0x100033f20:	mov	w2, #0
0x100033f24:	bl	#0x10006a08c
0x100033f28:	cmp	w19, #0x81
0x100033f2c:	b.hs	#0x100033fcc
0x100033f30:	add	w21, w21, w22
0x100033f34:	add	w22, w23, w0
0x100033f38:	mov	w0, #1
0x100033f3c:	mov	x1, x20
0x100033f40:	mov	w2, #0x80
0x100033f44:	bl	#0x10006a08c
0x100033f48:	add	w8, w22, w0
0x100033f4c:	add	w21, w21, w8
0x100033f50:	cmp	w19, #0x7f
0x100033f54:	mov	w9, #0x7f
0x100033f58:	csel	w8, w19, w9, hi
0x100033f5c:	add	w2, w8, #1
0x100033f60:	mov	w0, #2
0x100033f64:	mov	w1, #0xffff
0x100033f68:	bl	#0x10006a08c
0x100033f6c:	mov	x20, x0
0x100033f70:	mov	x0, x19
0x100033f74:	mov	w1, #8
0x100033f78:	bl	#0x1000993f8
0x100033f7c:	add	w8, w20, w0
0x100033f80:	add	w20, w21, w8
0x100033f84:	mov	x0, x19
0x100033f88:	mov	w1, #8
0x100033f8c:	bl	#0x1000993f8
0x100033f90:	add	w8, w20, w0
0x100033f94:	add	w19, w8, #0x268
0x100033f98:	mov	w20, #5
0x100033f9c:	mov	w0, #0xff
0x100033fa0:	mov	w1, #8
0x100033fa4:	bl	#0x1000993f8
0x100033fa8:	add	w19, w0, w19
0x100033fac:	subs	w20, w20, #1
0x100033fb0:	b.ne	#0x100033f9c
0x100033fb4:	mov	x0, x19
0x100033fb8:	ldp	x29, x30, [sp, #0x30]
0x100033fbc:	ldp	x20, x19, [sp, #0x20]
0x100033fc0:	ldp	x22, x21, [sp, #0x10]
0x100033fc4:	ldp	x24, x23, [sp], #0x40
0x100033fc8:	retab	
0x100033fcc:	bl	#0x10012b9dc

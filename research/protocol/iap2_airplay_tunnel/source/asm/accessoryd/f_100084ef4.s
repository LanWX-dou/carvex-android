; accessoryd 0x100084ef4-0x100084fa4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100084ef4:	pacibsp	
0x100084ef8:	stp	x22, x21, [sp, #-0x30]!
0x100084efc:	stp	x20, x19, [sp, #0x10]
0x100084f00:	stp	x29, x30, [sp, #0x20]
0x100084f04:	add	x29, sp, #0x20
0x100084f08:	mov	x19, x0
0x100084f0c:	mov	w0, #1
0x100084f10:	cbz	x1, #0x100084f8c
0x100084f14:	cbz	x3, #0x100084f8c
0x100084f18:	mov	x21, x1
0x100084f1c:	mov	x0, x2
0x100084f20:	mov	x1, x3
0x100084f24:	mov	w2, #0
0x100084f28:	bl	#0x100022264
0x100084f2c:	cbz	x0, #0x100084f74
0x100084f30:	mov	x20, x0
0x100084f34:	mov	x0, x19
0x100084f38:	mov	x1, x21
0x100084f3c:	mov	x2, x20
0x100084f40:	bl	#0x1000858a0
0x100084f44:	mov	w8, #0x5164
0x100084f48:	strh	w8, [x19, #0x1c]
0x100084f4c:	mov	x0, x20
0x100084f50:	mov	w1, #1
0x100084f54:	bl	#0x1000088a4
0x100084f58:	ldr	x0, [x20, #0x18]
0x100084f5c:	cbz	x0, #0x100084f64
0x100084f60:	bl	#0x1001a22d0
0x100084f64:	mov	x0, x20
0x100084f68:	bl	#0x1001a22d0
0x100084f6c:	mov	w0, #0
0x100084f70:	b	#0x100084f8c
0x100084f74:	adrp	x0, #0x10022b000
0x100084f78:	ldr	x0, [x0, #0xbb0]
0x100084f7c:	mov	w1, #0x10
0x100084f80:	bl	#0x1001a2830
0x100084f84:	cbnz	w0, #0x100084f9c
0x100084f88:	mov	w0, #1
0x100084f8c:	ldp	x29, x30, [sp, #0x20]
0x100084f90:	ldp	x20, x19, [sp, #0x10]
0x100084f94:	ldp	x22, x21, [sp], #0x30
0x100084f98:	retab	
0x100084f9c:	bl	#0x10014cbdc
0x100084fa0:	b	#0x100084f88

; accessoryd 0x1000059a0-0x100005a44; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000059a0:	pacibsp	
0x1000059a4:	sub	sp, sp, #0x40
0x1000059a8:	stp	x22, x21, [sp, #0x10]
0x1000059ac:	stp	x20, x19, [sp, #0x20]
0x1000059b0:	stp	x29, x30, [sp, #0x30]
0x1000059b4:	add	x29, sp, #0x30
0x1000059b8:	cbz	x0, #0x100005a34
0x1000059bc:	mov	x21, x2
0x1000059c0:	mov	x20, x1
0x1000059c4:	mov	x19, x0
0x1000059c8:	mov	w0, #0x10
0x1000059cc:	movk	w0, #0x2b94, lsl #16
0x1000059d0:	mov	x1, #0
0x1000059d4:	mov	x2, #0
0x1000059d8:	mov	x3, #0
0x1000059dc:	mov	x4, #0
0x1000059e0:	bl	#0x1001a2320
0x1000059e4:	adrp	x8, #0x10022b000
0x1000059e8:	ldr	x8, [x8, #0xce0]
0x1000059ec:	ldr	x0, [x8]
0x1000059f0:	mov	w2, w21
0x1000059f4:	mov	x1, x20
0x1000059f8:	bl	#0x1001a1510
0x1000059fc:	mov	x20, x0
0x100005a00:	ldr	x0, [x19]
0x100005a04:	mov	x1, x20
0x100005a08:	bl	#0x1000f4e98
0x100005a0c:	mov	x19, x0
0x100005a10:	cbz	x20, #0x100005a1c
0x100005a14:	mov	x0, x20
0x100005a18:	bl	#0x1001a1820
0x100005a1c:	mov	x0, x19
0x100005a20:	ldp	x29, x30, [sp, #0x30]
0x100005a24:	ldp	x20, x19, [sp, #0x20]
0x100005a28:	ldp	x22, x21, [sp, #0x10]
0x100005a2c:	add	sp, sp, #0x40
0x100005a30:	retab	
0x100005a34:	add	x0, sp, #0xf
0x100005a38:	bl	#0x100129964
0x100005a3c:	ldrb	w19, [sp, #0xf]
0x100005a40:	b	#0x100005a1c

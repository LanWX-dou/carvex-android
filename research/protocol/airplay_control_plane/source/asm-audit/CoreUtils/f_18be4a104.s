; CoreUtils 0x18be4a104-0x18be4a1f8; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be4a104:	pacibsp	
0x18be4a108:	sub	sp, sp, #0x70
0x18be4a10c:	stp	x20, x19, [sp, #0x50]
0x18be4a110:	stp	x29, x30, [sp, #0x60]
0x18be4a114:	add	x29, sp, #0x60
0x18be4a118:	mov	x19, x0
0x18be4a11c:	adrp	x8, #0x1e016a000
0x18be4a120:	ldr	x8, [x8, #0xf28]
0x18be4a124:	ldr	x8, [x8]
0x18be4a128:	stur	x8, [x29, #-0x18]
0x18be4a12c:	adrp	x8, #0x18bf72000
0x18be4a130:	ldr	q0, [x8, #0x90]
0x18be4a134:	str	q0, [x0]
0x18be4a138:	ldr	w8, [x1]
0x18be4a13c:	str	w8, [x0, #0x10]
0x18be4a140:	ldr	w8, [x1, #4]
0x18be4a144:	str	w8, [x0, #0x14]
0x18be4a148:	ldr	w8, [x1, #8]
0x18be4a14c:	str	w8, [x0, #0x18]
0x18be4a150:	ldr	w8, [x1, #0xc]
0x18be4a154:	str	w8, [x0, #0x1c]
0x18be4a158:	ldr	w8, [x1, #0x10]
0x18be4a15c:	str	w8, [x0, #0x20]
0x18be4a160:	ldr	w8, [x1, #0x14]
0x18be4a164:	str	w8, [x0, #0x24]
0x18be4a168:	ldr	w8, [x1, #0x18]
0x18be4a16c:	str	w8, [x0, #0x28]
0x18be4a170:	ldr	w8, [x1, #0x1c]
0x18be4a174:	str	xzr, [x0, #0x30]
0x18be4a178:	str	w8, [x0, #0x2c]
0x18be4a17c:	cbz	x2, #0x18be4a190
0x18be4a180:	ldr	w8, [x2]
0x18be4a184:	str	w8, [x19, #0x38]
0x18be4a188:	ldr	w8, [x2, #4]
0x18be4a18c:	b	#0x18be4a198
0x18be4a190:	mov	w8, #0
0x18be4a194:	str	wzr, [x19, #0x38]
0x18be4a198:	str	w8, [x19, #0x3c]
0x18be4a19c:	str	xzr, [x19, #0x80]
0x18be4a1a0:	adrp	x2, #0x18bf71000
0x18be4a1a4:	add	x2, x2, #0x1b4
0x18be4a1a8:	add	x1, sp, #8
0x18be4a1ac:	mov	x0, x19
0x18be4a1b0:	mov	w3, #0x40
0x18be4a1b4:	bl	#0x18be4a808
0x18be4a1b8:	add	x0, x19, #0x88
0x18be4a1bc:	add	x1, sp, #8
0x18be4a1c0:	bl	#0x18be4a5f4
0x18be4a1c4:	stp	xzr, xzr, [x19, #0xe8]
0x18be4a1c8:	strb	wzr, [x19, #0xf8]
0x18be4a1cc:	ldur	x8, [x29, #-0x18]
0x18be4a1d0:	adrp	x9, #0x1e016a000
0x18be4a1d4:	ldr	x9, [x9, #0xf28]
0x18be4a1d8:	ldr	x9, [x9]
0x18be4a1dc:	cmp	x9, x8
0x18be4a1e0:	b.ne	#0x18be4a1f4
0x18be4a1e4:	ldp	x29, x30, [sp, #0x60]
0x18be4a1e8:	ldp	x20, x19, [sp, #0x50]
0x18be4a1ec:	add	sp, sp, #0x70
0x18be4a1f0:	retab	
0x18be4a1f4:	bl	#0x1900cc180

; CoreUtils 0x18be4d1f4-0x18be4d298; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be4d1f4:	pacibsp	
0x18be4d1f8:	stp	x22, x21, [sp, #-0x30]!
0x18be4d1fc:	stp	x20, x19, [sp, #0x10]
0x18be4d200:	stp	x29, x30, [sp, #0x20]
0x18be4d204:	add	x29, sp, #0x20
0x18be4d208:	mov	x20, x3
0x18be4d20c:	mov	x21, x2
0x18be4d210:	mov	x22, x1
0x18be4d214:	mov	x19, x0
0x18be4d218:	ldrb	w8, [x0, #0xf8]
0x18be4d21c:	cbnz	w8, #0x18be4d24c
0x18be4d220:	ldr	x8, [x19, #0xe8]
0x18be4d224:	ands	x8, x8, #0xf
0x18be4d228:	b.eq	#0x18be4d244
0x18be4d22c:	mov	w9, #0x10
0x18be4d230:	sub	x2, x9, x8
0x18be4d234:	adrp	x1, #0x18bf71000
0x18be4d238:	add	x1, x1, #0x1b4
0x18be4d23c:	add	x0, x19, #0x88
0x18be4d240:	bl	#0x18be48df8
0x18be4d244:	mov	w8, #1
0x18be4d248:	strb	w8, [x19, #0xf8]
0x18be4d24c:	mov	x0, x19
0x18be4d250:	mov	x1, x22
0x18be4d254:	mov	x2, x21
0x18be4d258:	mov	x3, x20
0x18be4d25c:	bl	#0x18be4a6e0
0x18be4d260:	mov	x21, x0
0x18be4d264:	cbz	x0, #0x18be4d284
0x18be4d268:	add	x0, x19, #0x88
0x18be4d26c:	mov	x1, x20
0x18be4d270:	mov	x2, x21
0x18be4d274:	bl	#0x18be48df8
0x18be4d278:	ldr	x8, [x19, #0xf0]
0x18be4d27c:	add	x8, x8, x21
0x18be4d280:	str	x8, [x19, #0xf0]
0x18be4d284:	mov	x0, x21
0x18be4d288:	ldp	x29, x30, [sp, #0x20]
0x18be4d28c:	ldp	x20, x19, [sp, #0x10]
0x18be4d290:	ldp	x22, x21, [sp], #0x30
0x18be4d294:	retab	

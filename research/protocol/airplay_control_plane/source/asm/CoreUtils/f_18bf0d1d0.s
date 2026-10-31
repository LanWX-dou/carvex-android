; CoreUtils 0x18bf0d1d0-0x18bf0d27c; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18bf0d1d0:	pacibsp	
0x18bf0d1d4:	stp	x24, x23, [sp, #-0x40]!
0x18bf0d1d8:	stp	x22, x21, [sp, #0x10]
0x18bf0d1dc:	stp	x20, x19, [sp, #0x20]
0x18bf0d1e0:	stp	x29, x30, [sp, #0x30]
0x18bf0d1e4:	add	x29, sp, #0x30
0x18bf0d1e8:	mov	x19, x4
0x18bf0d1ec:	mov	x20, x3
0x18bf0d1f0:	mov	x21, x2
0x18bf0d1f4:	mov	x22, x1
0x18bf0d1f8:	mov	x23, x0
0x18bf0d1fc:	ldr	x0, [x0, #0x20a8]
0x18bf0d200:	ldr	x8, [x23, #0x20b0]
0x18bf0d204:	add	x1, x0, x8
0x18bf0d208:	mov	x2, x22
0x18bf0d20c:	mov	x3, x21
0x18bf0d210:	mov	x4, x20
0x18bf0d214:	mov	x5, x19
0x18bf0d218:	mov	x6, #0
0x18bf0d21c:	bl	#0x18bf42438
0x18bf0d220:	cbz	w0, #0x18bf0d268
0x18bf0d224:	ldr	x0, [x23, #0x2148]
0x18bf0d228:	ldr	x8, [x23, #0x2150]
0x18bf0d22c:	add	x1, x0, x8
0x18bf0d230:	mov	x2, x22
0x18bf0d234:	mov	x3, x21
0x18bf0d238:	mov	x4, x20
0x18bf0d23c:	mov	x5, x19
0x18bf0d240:	mov	x6, #0
0x18bf0d244:	ldp	x29, x30, [sp, #0x30]
0x18bf0d248:	ldp	x20, x19, [sp, #0x20]
0x18bf0d24c:	ldp	x22, x21, [sp, #0x10]
0x18bf0d250:	ldp	x24, x23, [sp], #0x40
0x18bf0d254:	autibsp	
0x18bf0d258:	eor	x16, x30, x30, lsl #1
0x18bf0d25c:	tbz	x16, #0x3e, #0x18bf0d264
0x18bf0d260:	brk	#0xc471
0x18bf0d264:	b	#0x18bf42438
0x18bf0d268:	ldp	x29, x30, [sp, #0x30]
0x18bf0d26c:	ldp	x20, x19, [sp, #0x20]
0x18bf0d270:	ldp	x22, x21, [sp, #0x10]
0x18bf0d274:	ldp	x24, x23, [sp], #0x40
0x18bf0d278:	retab	

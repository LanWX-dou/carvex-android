; accessoryd 0x1000353f8-0x100035464; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000353f8:	pacibsp	
0x1000353fc:	stp	x20, x19, [sp, #-0x20]!
0x100035400:	stp	x29, x30, [sp, #0x10]
0x100035404:	add	x29, sp, #0x10
0x100035408:	ldr	x19, [x0]
0x10003540c:	ldr	x20, [x1]
0x100035410:	ldr	x8, [x19, #0x40]
0x100035414:	ldrb	w0, [x8, #5]
0x100035418:	ldr	x8, [x20, #0x40]
0x10003541c:	ldrb	w1, [x8, #5]
0x100035420:	bl	#0x1000084b8
0x100035424:	ldr	x8, [x19]
0x100035428:	ldr	x9, [x20]
0x10003542c:	cmp	x8, x9
0x100035430:	b.ne	#0x100035460
0x100035434:	mov	w9, w0
0x100035438:	cbz	w9, #0x100035450
0x10003543c:	ldrb	w8, [x8, #0x1a5]
0x100035440:	orr	x10, x9, #0xffffffffffffff00
0x100035444:	cmp	w9, w8
0x100035448:	csel	x0, x10, x9, hi
0x10003544c:	b	#0x100035454
0x100035450:	mov	x0, #0
0x100035454:	ldp	x29, x30, [sp, #0x10]
0x100035458:	ldp	x20, x19, [sp], #0x20
0x10003545c:	retab	
0x100035460:	bl	#0x10012bb7c

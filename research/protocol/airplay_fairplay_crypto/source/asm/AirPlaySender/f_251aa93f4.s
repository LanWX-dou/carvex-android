; AirPlaySender 0x251aa93f4-0x251aa9490; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251aa93f4:	pacibsp	
0x251aa93f8:	stp	x20, x19, [sp, #-0x20]!
0x251aa93fc:	stp	x29, x30, [sp, #0x10]
0x251aa9400:	add	x29, sp, #0x10
0x251aa9404:	bl	#0x25810ac50
0x251aa9408:	ldr	x19, [x0, #8]
0x251aa940c:	cbz	x19, #0x251aa9480
0x251aa9410:	mov	x0, x19
0x251aa9414:	bl	#0x258109150
0x251aa9418:	ldr	x16, [x0, #0x10]!
0x251aa941c:	mov	x17, x0
0x251aa9420:	movk	x17, #0x97e1, lsl #48
0x251aa9424:	autda	x16, x17
0x251aa9428:	ldr	x2, [x16, #8]!
0x251aa942c:	cbz	x2, #0x251aa9480
0x251aa9430:	mov	x1, x16
0x251aa9434:	movk	x1, #0xd6e6, lsl #48
0x251aa9438:	mov	x16, x2
0x251aa943c:	mov	x17, x1
0x251aa9440:	autia	x16, x17
0x251aa9444:	mov	x17, x16
0x251aa9448:	xpaci	x17
0x251aa944c:	cmp	x16, x17
0x251aa9450:	b.eq	#0x251aa9458
0x251aa9454:	brk	#0xc470
0x251aa9458:	paciza	x16
0x251aa945c:	cbz	x16, #0x251aa9480
0x251aa9460:	mov	x0, x19
0x251aa9464:	ldp	x29, x30, [sp, #0x10]
0x251aa9468:	ldp	x20, x19, [sp], #0x20
0x251aa946c:	autibsp	
0x251aa9470:	eor	x16, x30, x30, lsl #1
0x251aa9474:	tbz	x16, #0x3e, #0x251aa947c
0x251aa9478:	brk	#0xc471
0x251aa947c:	braa	x2, x1
0x251aa9480:	mov	w0, #0
0x251aa9484:	ldp	x29, x30, [sp, #0x10]
0x251aa9488:	ldp	x20, x19, [sp], #0x20
0x251aa948c:	retab	

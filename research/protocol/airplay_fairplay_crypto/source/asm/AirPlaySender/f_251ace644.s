; AirPlaySender 0x251ace644-0x251ace6c8; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251ace644:	pacibsp	
0x251ace648:	stp	x20, x19, [sp, #-0x20]!
0x251ace64c:	stp	x29, x30, [sp, #0x10]
0x251ace650:	add	x29, sp, #0x10
0x251ace654:	mov	x20, x0
0x251ace658:	bl	#0x25810ac50
0x251ace65c:	mov	x19, x0
0x251ace660:	adrp	x8, #0x27097a000
0x251ace664:	ldr	w8, [x8, #0xf80]
0x251ace668:	cmp	w8, #0x1e
0x251ace66c:	b.gt	#0x251ace690
0x251ace670:	cmn	w8, #1
0x251ace674:	b.ne	#0x251ace6bc
0x251ace678:	adrp	x0, #0x27097a000
0x251ace67c:	add	x0, x0, #0xf80
0x251ace680:	mov	w1, #0x1e
0x251ace684:	movk	w1, #0x200, lsl #16
0x251ace688:	bl	#0x258101e40
0x251ace68c:	cbnz	w0, #0x251ace6bc
0x251ace690:	ldr	x0, [x19]
0x251ace694:	cbz	x0, #0x251ace6a0
0x251ace698:	bl	#0x2519fa054
0x251ace69c:	str	xzr, [x19]
0x251ace6a0:	ldr	x0, [x19, #8]
0x251ace6a4:	cbz	x0, #0x251ace6b0
0x251ace6a8:	bl	#0x2580f5830
0x251ace6ac:	str	xzr, [x19, #8]
0x251ace6b0:	ldp	x29, x30, [sp, #0x10]
0x251ace6b4:	ldp	x20, x19, [sp], #0x20
0x251ace6b8:	retab	
0x251ace6bc:	mov	x0, x20
0x251ace6c0:	bl	#0x251ba4300
0x251ace6c4:	b	#0x251ace690

; AirPlaySender 0x251aa9668-0x251aa97a0; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251aa9668:	pacibsp	
0x251aa966c:	stp	x20, x19, [sp, #-0x20]!
0x251aa9670:	stp	x29, x30, [sp, #0x10]
0x251aa9674:	add	x29, sp, #0x10
0x251aa9678:	bl	#0x25810ac50
0x251aa967c:	ldr	x20, [x0, #8]
0x251aa9680:	cbz	x20, #0x251aa976c
0x251aa9684:	mov	x19, x0
0x251aa9688:	mov	x0, x20
0x251aa968c:	bl	#0x258109150
0x251aa9690:	ldr	x16, [x0, #0x10]!
0x251aa9694:	mov	x17, x0
0x251aa9698:	movk	x17, #0x97e1, lsl #48
0x251aa969c:	autda	x16, x17
0x251aa96a0:	ldr	x9, [x16, #8]!
0x251aa96a4:	cbz	x9, #0x251aa976c
0x251aa96a8:	mov	x8, x16
0x251aa96ac:	movk	x8, #0xd6e6, lsl #48
0x251aa96b0:	mov	x16, x9
0x251aa96b4:	mov	x17, x8
0x251aa96b8:	autia	x16, x17
0x251aa96bc:	mov	x17, x16
0x251aa96c0:	xpaci	x17
0x251aa96c4:	cmp	x16, x17
0x251aa96c8:	b.eq	#0x251aa96d0
0x251aa96cc:	brk	#0xc470
0x251aa96d0:	paciza	x16
0x251aa96d4:	cbz	x16, #0x251aa976c
0x251aa96d8:	mov	x0, x20
0x251aa96dc:	blraa	x9, x8
0x251aa96e0:	cmp	w0, #4
0x251aa96e4:	b.ne	#0x251aa976c
0x251aa96e8:	ldr	x20, [x19]
0x251aa96ec:	cbz	x20, #0x251aa976c
0x251aa96f0:	mov	x0, x20
0x251aa96f4:	bl	#0x258109150
0x251aa96f8:	ldr	x16, [x0, #0x10]!
0x251aa96fc:	mov	x17, x0
0x251aa9700:	movk	x17, #0xf7db, lsl #48
0x251aa9704:	autda	x16, x17
0x251aa9708:	ldr	x9, [x16, #8]!
0x251aa970c:	cbz	x9, #0x251aa9780
0x251aa9710:	mov	x8, x16
0x251aa9714:	movk	x8, #0x2d6f, lsl #48
0x251aa9718:	mov	x16, x9
0x251aa971c:	mov	x17, x8
0x251aa9720:	autia	x16, x17
0x251aa9724:	mov	x17, x16
0x251aa9728:	xpaci	x17
0x251aa972c:	cmp	x16, x17
0x251aa9730:	b.eq	#0x251aa9738
0x251aa9734:	brk	#0xc470
0x251aa9738:	paciza	x16
0x251aa973c:	cbz	x16, #0x251aa9780
0x251aa9740:	add	x1, x19, #0x10
0x251aa9744:	add	x6, x19, #0x10
0x251aa9748:	mov	x0, x20
0x251aa974c:	mov	w2, #0x10
0x251aa9750:	mov	x3, #0
0x251aa9754:	mov	x4, #0
0x251aa9758:	mov	w5, #0x10
0x251aa975c:	blraa	x9, x8
0x251aa9760:	mov	x19, x0
0x251aa9764:	cbz	w0, #0x251aa9770
0x251aa9768:	b	#0x251aa9784
0x251aa976c:	mov	w19, #0
0x251aa9770:	mov	x0, x19
0x251aa9774:	ldp	x29, x30, [sp, #0x10]
0x251aa9778:	ldp	x20, x19, [sp], #0x20
0x251aa977c:	retab	
0x251aa9780:	mov	w19, #-0x31ee
0x251aa9784:	adrp	x1, #0x251c18000
0x251aa9788:	add	x1, x1, #0xc07
0x251aa978c:	mov	x0, x19
0x251aa9790:	mov	w2, #0x14a
0x251aa9794:	mov	w3, #0
0x251aa9798:	bl	#0x258109a30
0x251aa979c:	b	#0x251aa9770

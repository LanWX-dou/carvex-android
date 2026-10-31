; AirPlaySender 0x251a355d0-0x251a356c8; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a355d0:	pacibsp	
0x251a355d4:	sub	sp, sp, #0x40
0x251a355d8:	stp	x22, x21, [sp, #0x10]
0x251a355dc:	stp	x20, x19, [sp, #0x20]
0x251a355e0:	stp	x29, x30, [sp, #0x30]
0x251a355e4:	add	x29, sp, #0x30
0x251a355e8:	mov	x19, x2
0x251a355ec:	mov	x21, x1
0x251a355f0:	mov	x20, x0
0x251a355f4:	str	xzr, [sp, #8]
0x251a355f8:	bl	#0x25810d720
0x251a355fc:	mov	x2, x0
0x251a35600:	adrp	x1, #0x276124000
0x251a35604:	add	x1, x1, #0xae0
0x251a35608:	add	x3, sp, #8
0x251a3560c:	mov	x0, x20
0x251a35610:	bl	#0x25810acc0
0x251a35614:	cbnz	w0, #0x251a356a0
0x251a35618:	ldr	x0, [sp, #8]
0x251a3561c:	bl	#0x25810ac50
0x251a35620:	mov	x20, x0
0x251a35624:	str	x21, [x0]
0x251a35628:	cbz	x21, #0x251a35634
0x251a3562c:	mov	x0, x21
0x251a35630:	bl	#0x2580f6a60
0x251a35634:	bl	#0x25810d150
0x251a35638:	str	x0, [x20, #8]
0x251a3563c:	cbz	x0, #0x251a356ac
0x251a35640:	adrp	x8, #0x27097a000
0x251a35644:	ldr	w8, [x8, #0xb90]
0x251a35648:	cmp	w8, #0x1e
0x251a3564c:	b.gt	#0x251a35670
0x251a35650:	cmn	w8, #1
0x251a35654:	b.ne	#0x251a35694
0x251a35658:	adrp	x0, #0x27097a000
0x251a3565c:	add	x0, x0, #0xb90
0x251a35660:	mov	w1, #0x1e
0x251a35664:	movk	w1, #0x200, lsl #16
0x251a35668:	bl	#0x258101e40
0x251a3566c:	cbnz	w0, #0x251a35694
0x251a35670:	mov	w20, #0
0x251a35674:	ldr	x8, [sp, #8]
0x251a35678:	str	x8, [x19]
0x251a3567c:	mov	x0, x20
0x251a35680:	ldp	x29, x30, [sp, #0x30]
0x251a35684:	ldp	x20, x19, [sp, #0x20]
0x251a35688:	ldp	x22, x21, [sp, #0x10]
0x251a3568c:	add	sp, sp, #0x40
0x251a35690:	retab	
0x251a35694:	add	x0, sp, #8
0x251a35698:	bl	#0x251b4c190
0x251a3569c:	b	#0x251a35670
0x251a356a0:	mov	x20, x0
0x251a356a4:	bl	#0x251b4c168
0x251a356a8:	b	#0x251a356b8
0x251a356ac:	bl	#0x251b4c1d8
0x251a356b0:	mov	w20, #0xe7d8
0x251a356b4:	movk	w20, #0xfffe, lsl #16
0x251a356b8:	ldr	x0, [sp, #8]
0x251a356bc:	cbz	x0, #0x251a3567c
0x251a356c0:	bl	#0x2580f5830
0x251a356c4:	b	#0x251a3567c

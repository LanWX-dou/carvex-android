; AirPlaySender 0x2519cc764-0x2519cc87c; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519cc764:	pacibsp	
0x2519cc768:	stp	x22, x21, [sp, #-0x30]!
0x2519cc76c:	stp	x20, x19, [sp, #0x10]
0x2519cc770:	stp	x29, x30, [sp, #0x20]
0x2519cc774:	add	x29, sp, #0x20
0x2519cc778:	mov	x19, x3
0x2519cc77c:	mov	x21, x2
0x2519cc780:	mov	x22, x1
0x2519cc784:	bl	#0x25810ac50
0x2519cc788:	mov	x20, x0
0x2519cc78c:	adrp	x1, #0x27613e000
0x2519cc790:	add	x1, x1, #0x290
0x2519cc794:	mov	x0, x22
0x2519cc798:	bl	#0x258101830
0x2519cc79c:	cbz	w0, #0x2519cc7cc
0x2519cc7a0:	ldr	x0, [x20, #8]
0x2519cc7a4:	cbz	x0, #0x2519cc864
0x2519cc7a8:	mov	x1, x19
0x2519cc7ac:	ldp	x29, x30, [sp, #0x20]
0x2519cc7b0:	ldp	x20, x19, [sp, #0x10]
0x2519cc7b4:	ldp	x22, x21, [sp], #0x30
0x2519cc7b8:	autibsp	
0x2519cc7bc:	eor	x16, x30, x30, lsl #1
0x2519cc7c0:	tbz	x16, #0x3e, #0x2519cc7c8
0x2519cc7c4:	brk	#0xc471
0x2519cc7c8:	b	#0x25810da70
0x2519cc7cc:	adrp	x8, #0x2680d4000
0x2519cc7d0:	ldr	x8, [x8, #0x870]
0x2519cc7d4:	ldr	x1, [x8]
0x2519cc7d8:	mov	x0, x22
0x2519cc7dc:	bl	#0x258101830
0x2519cc7e0:	cbz	w0, #0x2519cc804
0x2519cc7e4:	add	x2, x20, #0x10
0x2519cc7e8:	mov	x0, x21
0x2519cc7ec:	mov	w1, #3
0x2519cc7f0:	bl	#0x2580f7010
0x2519cc7f4:	str	x0, [x19]
0x2519cc7f8:	cbz	x0, #0x2519cc870
0x2519cc7fc:	mov	w0, #0
0x2519cc800:	b	#0x2519cc854
0x2519cc804:	adrp	x8, #0x2680d4000
0x2519cc808:	ldr	x8, [x8, #0x878]
0x2519cc80c:	ldr	x1, [x8]
0x2519cc810:	mov	x0, x22
0x2519cc814:	bl	#0x258101830
0x2519cc818:	cbz	w0, #0x2519cc850
0x2519cc81c:	adrp	x8, #0x2680d3000
0x2519cc820:	ldr	x8, [x8, #0x198]
0x2519cc824:	ldrb	w9, [x20, #0x70]
0x2519cc828:	adrp	x10, #0x2680d3000
0x2519cc82c:	ldr	x10, [x10, #0x188]
0x2519cc830:	cmp	w9, #0
0x2519cc834:	csel	x8, x10, x8, eq
0x2519cc838:	ldr	x0, [x8]
0x2519cc83c:	bl	#0x2580f6a60
0x2519cc840:	mov	x8, x0
0x2519cc844:	mov	w0, #0
0x2519cc848:	str	x8, [x19]
0x2519cc84c:	b	#0x2519cc854
0x2519cc850:	mov	w0, #-0x31f0
0x2519cc854:	ldp	x29, x30, [sp, #0x20]
0x2519cc858:	ldp	x20, x19, [sp, #0x10]
0x2519cc85c:	ldp	x22, x21, [sp], #0x30
0x2519cc860:	retab	
0x2519cc864:	bl	#0x2519cac10
0x2519cc868:	mov	w0, #-0x4199
0x2519cc86c:	b	#0x2519cc854
0x2519cc870:	bl	#0x251bcc310
0x2519cc874:	mov	w0, #-0x4196
0x2519cc878:	b	#0x2519cc854

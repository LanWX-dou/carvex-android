; AirPlaySender 0x251a587a0-0x251a5885c; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a587a0:	pacibsp	
0x251a587a4:	sub	sp, sp, #0x60
0x251a587a8:	stp	x22, x21, [sp, #0x30]
0x251a587ac:	stp	x20, x19, [sp, #0x40]
0x251a587b0:	stp	x29, x30, [sp, #0x50]
0x251a587b4:	add	x29, sp, #0x50
0x251a587b8:	mov	x19, x3
0x251a587bc:	mov	x20, x2
0x251a587c0:	mov	x21, x1
0x251a587c4:	mov	x22, x0
0x251a587c8:	bl	#0x25810ac50
0x251a587cc:	stp	x22, x21, [sp, #8]
0x251a587d0:	add	x8, sp, #0x28
0x251a587d4:	str	x20, [sp, #0x18]
0x251a587d8:	stp	x8, xzr, [sp, #0x20]
0x251a587dc:	ldr	w8, [x0, #0xe0]
0x251a587e0:	cmp	w8, #5
0x251a587e4:	b.ne	#0x251a58818
0x251a587e8:	ldr	x0, [x0, #0x78]
0x251a587ec:	adrp	x16, #0x2519c5000
0x251a587f0:	add	x16, x16, #0x858
0x251a587f4:	paciza	x16
0x251a587f8:	mov	x1, x16
0x251a587fc:	add	x2, sp, #8
0x251a58800:	bl	#0x25810d260
0x251a58804:	mov	x20, x0
0x251a58808:	cbnz	w0, #0x251a58834
0x251a5880c:	ldr	x8, [sp, #0x28]
0x251a58810:	str	x8, [x19]
0x251a58814:	b	#0x251a5881c
0x251a58818:	mov	w20, #0
0x251a5881c:	mov	x0, x20
0x251a58820:	ldp	x29, x30, [sp, #0x50]
0x251a58824:	ldp	x20, x19, [sp, #0x40]
0x251a58828:	ldp	x22, x21, [sp, #0x30]
0x251a5882c:	add	sp, sp, #0x60
0x251a58830:	retab	
0x251a58834:	adrp	x1, #0x251bf7000
0x251a58838:	add	x1, x1, #0x1db
0x251a5883c:	mov	x0, x20
0x251a58840:	mov	w2, #0x1027
0x251a58844:	mov	w3, #0
0x251a58848:	bl	#0x258109a30
0x251a5884c:	ldr	x0, [sp, #0x28]
0x251a58850:	cbz	x0, #0x251a5881c
0x251a58854:	bl	#0x2580f5830
0x251a58858:	b	#0x251a5881c

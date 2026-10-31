; AirPlaySender 0x251ab1780-0x251ab1830; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251ab1780:	pacibsp	
0x251ab1784:	stp	x24, x23, [sp, #-0x40]!
0x251ab1788:	stp	x22, x21, [sp, #0x10]
0x251ab178c:	stp	x20, x19, [sp, #0x20]
0x251ab1790:	stp	x29, x30, [sp, #0x30]
0x251ab1794:	add	x29, sp, #0x30
0x251ab1798:	mov	x19, x3
0x251ab179c:	cbz	w0, #0x251ab181c
0x251ab17a0:	mov	x20, x2
0x251ab17a4:	mov	x22, x1
0x251ab17a8:	mov	x23, x0
0x251ab17ac:	adrp	x8, #0x2680d3000
0x251ab17b0:	ldr	x8, [x8, #0x150]
0x251ab17b4:	ldr	x0, [x8]
0x251ab17b8:	adrp	x2, #0x2680d3000
0x251ab17bc:	ldr	x2, [x2, #0x340]
0x251ab17c0:	adrp	x3, #0x2680d3000
0x251ab17c4:	ldr	x3, [x3, #0x358]
0x251ab17c8:	mov	x1, #0
0x251ab17cc:	bl	#0x258101820
0x251ab17d0:	cbz	x0, #0x251ab1824
0x251ab17d4:	mov	x21, x0
0x251ab17d8:	mov	w2, w23
0x251ab17dc:	adrp	x1, #0x27612f000
0x251ab17e0:	add	x1, x1, #0xb30
0x251ab17e4:	bl	#0x25810a790
0x251ab17e8:	cbz	w22, #0x251ab1800
0x251ab17ec:	adrp	x1, #0x276132000
0x251ab17f0:	add	x1, x1, #0x150
0x251ab17f4:	mov	x0, x21
0x251ab17f8:	mov	x2, x20
0x251ab17fc:	bl	#0x25810a790
0x251ab1800:	mov	w0, #0
0x251ab1804:	str	x21, [x19]
0x251ab1808:	ldp	x29, x30, [sp, #0x30]
0x251ab180c:	ldp	x20, x19, [sp, #0x20]
0x251ab1810:	ldp	x22, x21, [sp, #0x10]
0x251ab1814:	ldp	x24, x23, [sp], #0x40
0x251ab1818:	retab	
0x251ab181c:	mov	x21, #0
0x251ab1820:	b	#0x251ab1800
0x251ab1824:	bl	#0x251b8a1d0
0x251ab1828:	mov	w0, #-0x1a48
0x251ab182c:	b	#0x251ab1808

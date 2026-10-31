; AirPlaySender 0x251aaf744-0x251aaf934; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251aaf744:	pacibsp	
0x251aaf748:	sub	sp, sp, #0x90
0x251aaf74c:	stp	x28, x27, [sp, #0x30]
0x251aaf750:	stp	x26, x25, [sp, #0x40]
0x251aaf754:	stp	x24, x23, [sp, #0x50]
0x251aaf758:	stp	x22, x21, [sp, #0x60]
0x251aaf75c:	stp	x20, x19, [sp, #0x70]
0x251aaf760:	stp	x29, x30, [sp, #0x80]
0x251aaf764:	add	x29, sp, #0x80
0x251aaf768:	mov	x21, x7
0x251aaf76c:	mov	x22, x6
0x251aaf770:	str	x5, [sp, #0x28]
0x251aaf774:	mov	x25, x4
0x251aaf778:	mov	x20, x3
0x251aaf77c:	mov	x27, x2
0x251aaf780:	mov	x26, x1
0x251aaf784:	mov	x19, x0
0x251aaf788:	bl	#0x25810ac50
0x251aaf78c:	mov	x23, x0
0x251aaf790:	strb	wzr, [x0, #0x3a]
0x251aaf794:	cbnz	w20, #0x251aaf7b0
0x251aaf798:	ldrb	w8, [x23, #0x39]
0x251aaf79c:	cbnz	w8, #0x251aaf7b8
0x251aaf7a0:	cmp	w27, #0
0x251aaf7a4:	mov	w8, #2
0x251aaf7a8:	csel	w20, wzr, w8, eq
0x251aaf7ac:	b	#0x251aaf7cc
0x251aaf7b0:	mov	w20, #4
0x251aaf7b4:	b	#0x251aaf7cc
0x251aaf7b8:	ldrb	w8, [x23, #0x3b]
0x251aaf7bc:	cmp	w8, #0
0x251aaf7c0:	mov	w8, #5
0x251aaf7c4:	mov	w9, #3
0x251aaf7c8:	csel	w20, w9, w8, eq
0x251aaf7cc:	ldr	x28, [x29, #0x28]
0x251aaf7d0:	mov	w24, #0xed1
0x251aaf7d4:	movk	w24, #3, lsl #16
0x251aaf7d8:	ldp	x8, x9, [x29, #0x10]
0x251aaf7dc:	cbnz	w27, #0x251aaf838
0x251aaf7e0:	ldrb	w3, [x23, #0x40]
0x251aaf7e4:	stp	x9, x28, [sp, #8]
0x251aaf7e8:	str	x8, [sp]
0x251aaf7ec:	adrp	x1, #0x276136000
0x251aaf7f0:	add	x1, x1, #0x450
0x251aaf7f4:	mov	x0, x19
0x251aaf7f8:	mov	x2, x20
0x251aaf7fc:	mov	w4, #0
0x251aaf800:	mov	x5, #0
0x251aaf804:	mov	x6, x22
0x251aaf808:	mov	x7, x21
0x251aaf80c:	bl	#0x251b88c94
0x251aaf810:	mov	x8, x0
0x251aaf814:	mov	w0, #0
0x251aaf818:	add	w9, w24, #2
0x251aaf81c:	cmp	w8, w24
0x251aaf820:	csel	w19, w9, w8, eq
0x251aaf824:	cbz	w19, #0x251aaf8d8
0x251aaf828:	mov	x0, x19
0x251aaf82c:	bl	#0x251b8992c
0x251aaf830:	mov	x0, x19
0x251aaf834:	b	#0x251aaf8d8
0x251aaf838:	ldr	x27, [x29, #0x20]
0x251aaf83c:	cbnz	x26, #0x251aaf888
0x251aaf840:	bl	#0x25810d530
0x251aaf844:	stp	xzr, x28, [sp, #0x10]
0x251aaf848:	stp	x0, x27, [sp]
0x251aaf84c:	mov	x0, x19
0x251aaf850:	mov	x1, x20
0x251aaf854:	mov	w2, #0x7374
0x251aaf858:	movk	w2, #0x7070, lsl #16
0x251aaf85c:	mov	x3, #0
0x251aaf860:	mov	x4, #0
0x251aaf864:	mov	w5, #0
0x251aaf868:	mov	w6, #0
0x251aaf86c:	mov	x7, #0
0x251aaf870:	bl	#0x251b885ec
0x251aaf874:	cmp	w0, #0
0x251aaf878:	mov	w8, #0xed1
0x251aaf87c:	movk	w8, #3, lsl #16
0x251aaf880:	csel	w0, w8, w0, eq
0x251aaf884:	b	#0x251aaf8d8
0x251aaf888:	ldrb	w3, [x23, #0x40]
0x251aaf88c:	stp	x9, x28, [sp, #8]
0x251aaf890:	str	x8, [sp]
0x251aaf894:	mov	x0, x19
0x251aaf898:	mov	x1, x26
0x251aaf89c:	mov	x2, x20
0x251aaf8a0:	mov	x4, x25
0x251aaf8a4:	ldr	x5, [sp, #0x28]
0x251aaf8a8:	mov	x6, x22
0x251aaf8ac:	mov	x7, x21
0x251aaf8b0:	bl	#0x251b88c94
0x251aaf8b4:	mov	w21, #0xed1
0x251aaf8b8:	movk	w21, #3, lsl #16
0x251aaf8bc:	cmp	w0, w21
0x251aaf8c0:	b.ne	#0x251aaf8cc
0x251aaf8c4:	ldrb	w8, [x23, #0x38]
0x251aaf8c8:	cbz	w8, #0x251aaf8f8
0x251aaf8cc:	add	w8, w21, #0x45
0x251aaf8d0:	cmp	w0, w8
0x251aaf8d4:	csel	w0, w21, w0, eq
0x251aaf8d8:	ldp	x29, x30, [sp, #0x80]
0x251aaf8dc:	ldp	x20, x19, [sp, #0x70]
0x251aaf8e0:	ldp	x22, x21, [sp, #0x60]
0x251aaf8e4:	ldp	x24, x23, [sp, #0x50]
0x251aaf8e8:	ldp	x26, x25, [sp, #0x40]
0x251aaf8ec:	ldp	x28, x27, [sp, #0x30]
0x251aaf8f0:	add	sp, sp, #0x90
0x251aaf8f4:	retab	
0x251aaf8f8:	bl	#0x25810d530
0x251aaf8fc:	stp	xzr, xzr, [sp, #0x10]
0x251aaf900:	stp	x0, x27, [sp]
0x251aaf904:	mov	x0, x19
0x251aaf908:	mov	x1, x20
0x251aaf90c:	mov	w2, #0x7374
0x251aaf910:	movk	w2, #0x7070, lsl #16
0x251aaf914:	mov	x3, #0
0x251aaf918:	mov	x4, #0
0x251aaf91c:	mov	w5, #0
0x251aaf920:	mov	w6, #0
0x251aaf924:	mov	x7, #0
0x251aaf928:	bl	#0x251b885ec
0x251aaf92c:	cmp	w0, #0
0x251aaf930:	b	#0x251aaf8d4

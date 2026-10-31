; CoreUtils 0x18bf1c798-0x18bf1c924; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18bf1c798:	pacibsp	
0x18bf1c79c:	stp	x26, x25, [sp, #-0x50]!
0x18bf1c7a0:	stp	x24, x23, [sp, #0x10]
0x18bf1c7a4:	stp	x22, x21, [sp, #0x20]
0x18bf1c7a8:	stp	x20, x19, [sp, #0x30]
0x18bf1c7ac:	stp	x29, x30, [sp, #0x40]
0x18bf1c7b0:	add	x29, sp, #0x40
0x18bf1c7b4:	mov	x19, x4
0x18bf1c7b8:	cbz	x0, #0x18bf1c900
0x18bf1c7bc:	mov	x25, x0
0x18bf1c7c0:	ldr	w8, [x0]
0x18bf1c7c4:	mov	w9, #0x6f63
0x18bf1c7c8:	movk	w9, #0x6e73, lsl #16
0x18bf1c7cc:	cmp	w8, w9
0x18bf1c7d0:	b.ne	#0x18bf1c900
0x18bf1c7d4:	ldrb	w8, [x25, #8]
0x18bf1c7d8:	cbnz	w8, #0x18bf1c90c
0x18bf1c7dc:	ldr	w8, [x25, #4]
0x18bf1c7e0:	tbnz	w8, #0x1f, #0x18bf1c918
0x18bf1c7e4:	mov	x21, x6
0x18bf1c7e8:	mov	x22, x5
0x18bf1c7ec:	mov	x26, x3
0x18bf1c7f0:	mov	x24, x2
0x18bf1c7f4:	mov	x23, x1
0x18bf1c7f8:	ldp	x1, x8, [x25, #0x40]
0x18bf1c7fc:	sub	x8, x8, x1
0x18bf1c800:	cmp	x8, #1
0x18bf1c804:	b.lt	#0x18bf1c838
0x18bf1c808:	cmp	x8, x24
0x18bf1c80c:	csel	x20, x8, x24, lt
0x18bf1c810:	mov	x0, x26
0x18bf1c814:	mov	x2, x20
0x18bf1c818:	bl	#0x1900cc480
0x18bf1c81c:	ldr	x8, [x25, #0x40]
0x18bf1c820:	add	x9, x8, x20
0x18bf1c824:	str	x9, [x25, #0x40]
0x18bf1c828:	add	x8, x26, x20
0x18bf1c82c:	sub	x24, x24, x20
0x18bf1c830:	mov	x26, x8
0x18bf1c834:	b	#0x18bf1c83c
0x18bf1c838:	mov	x20, #0
0x18bf1c83c:	cmp	x24, #1
0x18bf1c840:	b.lt	#0x18bf1c8c4
0x18bf1c844:	ldr	w0, [x25, #4]
0x18bf1c848:	mov	x1, x26
0x18bf1c84c:	mov	x2, x24
0x18bf1c850:	mov	x3, x22
0x18bf1c854:	bl	#0x1900ec940
0x18bf1c858:	cmp	x0, #1
0x18bf1c85c:	b.ge	#0x18bf1c8ac
0x18bf1c860:	cbz	x0, #0x18bf1c8cc
0x18bf1c864:	bl	#0x1900ce930
0x18bf1c868:	ldr	w8, [x0]
0x18bf1c86c:	cbz	w8, #0x18bf1c8dc
0x18bf1c870:	bl	#0x1900ce930
0x18bf1c874:	ldr	w0, [x0]
0x18bf1c878:	cmp	w0, #4
0x18bf1c87c:	b.eq	#0x18bf1c844
0x18bf1c880:	cmp	w0, #0x23
0x18bf1c884:	b.ne	#0x18bf1c8e0
0x18bf1c888:	cmp	x20, x23
0x18bf1c88c:	b.hs	#0x18bf1c8c4
0x18bf1c890:	ldr	w1, [x25, #4]
0x18bf1c894:	mov	x0, x25
0x18bf1c898:	mov	w2, #0
0x18bf1c89c:	mov	x3, x21
0x18bf1c8a0:	bl	#0x18bf1d73c
0x18bf1c8a4:	cbnz	w0, #0x18bf1c8e0
0x18bf1c8a8:	b	#0x18bf1c8bc
0x18bf1c8ac:	add	x8, x26, x0
0x18bf1c8b0:	sub	x24, x24, x0
0x18bf1c8b4:	add	x20, x0, x20
0x18bf1c8b8:	mov	x26, x8
0x18bf1c8bc:	cmp	x24, #0
0x18bf1c8c0:	b.gt	#0x18bf1c844
0x18bf1c8c4:	mov	w0, #0
0x18bf1c8c8:	b	#0x18bf1c8e0
0x18bf1c8cc:	cmp	x20, x23
0x18bf1c8d0:	mov	w8, #-0x1a61
0x18bf1c8d4:	csel	w0, w8, wzr, lo
0x18bf1c8d8:	b	#0x18bf1c8e0
0x18bf1c8dc:	mov	w0, #-0x1a2c
0x18bf1c8e0:	cbz	x19, #0x18bf1c8e8
0x18bf1c8e4:	str	x20, [x19]
0x18bf1c8e8:	ldp	x29, x30, [sp, #0x40]
0x18bf1c8ec:	ldp	x20, x19, [sp, #0x30]
0x18bf1c8f0:	ldp	x22, x21, [sp, #0x20]
0x18bf1c8f4:	ldp	x24, x23, [sp, #0x10]
0x18bf1c8f8:	ldp	x26, x25, [sp], #0x50
0x18bf1c8fc:	retab	
0x18bf1c900:	mov	x20, #0
0x18bf1c904:	mov	w0, #-0x1a54
0x18bf1c908:	b	#0x18bf1c8e0
0x18bf1c90c:	mov	x20, #0
0x18bf1c910:	mov	w0, #-0x1a43
0x18bf1c914:	b	#0x18bf1c8e0
0x18bf1c918:	mov	x20, #0
0x18bf1c91c:	mov	w0, #-0x1a59
0x18bf1c920:	b	#0x18bf1c8e0

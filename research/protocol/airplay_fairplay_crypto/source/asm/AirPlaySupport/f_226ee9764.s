; AirPlaySupport 0x226ee9764-0x226ee9854; source SHA256 d90a26393a5f761e1a8c98ce08f2acd90b9a630c4697054d07e8b3381ebf6a15; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x226ee9764:	pacibsp	
0x226ee9768:	sub	sp, sp, #0x70
0x226ee976c:	stp	x26, x25, [sp, #0x20]
0x226ee9770:	stp	x24, x23, [sp, #0x30]
0x226ee9774:	stp	x22, x21, [sp, #0x40]
0x226ee9778:	stp	x20, x19, [sp, #0x50]
0x226ee977c:	stp	x29, x30, [sp, #0x60]
0x226ee9780:	add	x29, sp, #0x60
0x226ee9784:	mov	x21, x4
0x226ee9788:	mov	x22, x3
0x226ee978c:	mov	x19, x2
0x226ee9790:	mov	x23, x1
0x226ee9794:	mov	x24, x0
0x226ee9798:	stp	xzr, xzr, [sp, #0x10]
0x226ee979c:	adrp	x8, #0x226f51000
0x226ee97a0:	add	x8, x8, #0xf63
0x226ee97a4:	stp	x8, x2, [sp]
0x226ee97a8:	adrp	x25, #0x226f51000
0x226ee97ac:	add	x25, x25, #0xf5c
0x226ee97b0:	add	x0, sp, #0x18
0x226ee97b4:	mov	x1, x25
0x226ee97b8:	bl	#0x22818b6d0
0x226ee97bc:	mov	x26, x0
0x226ee97c0:	sxtw	x20, w26
0x226ee97c4:	adrp	x8, #0x226f51000
0x226ee97c8:	add	x8, x8, #0xf74
0x226ee97cc:	stp	x8, x19, [sp]
0x226ee97d0:	add	x0, sp, #0x10
0x226ee97d4:	mov	x1, x25
0x226ee97d8:	bl	#0x22818b6d0
0x226ee97dc:	sxtw	x19, w0
0x226ee97e0:	ldp	x4, x2, [sp, #0x10]
0x226ee97e4:	mov	x0, x24
0x226ee97e8:	mov	x1, x23
0x226ee97ec:	mov	x3, x20
0x226ee97f0:	mov	x5, x19
0x226ee97f4:	mov	x6, x22
0x226ee97f8:	mov	x7, x21
0x226ee97fc:	bl	#0x226ee961c
0x226ee9800:	cbz	w26, #0x226ee9814
0x226ee9804:	ldr	x8, [sp, #0x18]
0x226ee9808:	strb	wzr, [x8], #1
0x226ee980c:	subs	x20, x20, #1
0x226ee9810:	b.ne	#0x226ee9808
0x226ee9814:	cbz	w19, #0x226ee9828
0x226ee9818:	ldr	x8, [sp, #0x10]
0x226ee981c:	strb	wzr, [x8], #1
0x226ee9820:	subs	x19, x19, #1
0x226ee9824:	b.ne	#0x226ee981c
0x226ee9828:	ldr	x0, [sp, #0x18]
0x226ee982c:	bl	#0x22813e830
0x226ee9830:	ldr	x0, [sp, #0x10]
0x226ee9834:	bl	#0x22813e830
0x226ee9838:	ldp	x29, x30, [sp, #0x60]
0x226ee983c:	ldp	x20, x19, [sp, #0x50]
0x226ee9840:	ldp	x22, x21, [sp, #0x40]
0x226ee9844:	ldp	x24, x23, [sp, #0x30]
0x226ee9848:	ldp	x26, x25, [sp, #0x20]
0x226ee984c:	add	sp, sp, #0x70
0x226ee9850:	retab	

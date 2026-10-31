; AirPlaySender 0x2519bd76c-0x2519bd800; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519bd76c:	pacibsp	
0x2519bd770:	stp	x24, x23, [sp, #-0x40]!
0x2519bd774:	stp	x22, x21, [sp, #0x10]
0x2519bd778:	stp	x20, x19, [sp, #0x20]
0x2519bd77c:	stp	x29, x30, [sp, #0x30]
0x2519bd780:	add	x29, sp, #0x30
0x2519bd784:	mov	x19, x6
0x2519bd788:	mov	x20, x5
0x2519bd78c:	mov	x21, x4
0x2519bd790:	mov	x22, x3
0x2519bd794:	mov	x23, x2
0x2519bd798:	mov	x24, x1
0x2519bd79c:	bl	#0x25810ac50
0x2519bd7a0:	ldr	x0, [x0, #8]
0x2519bd7a4:	cbz	x0, #0x2519bd7e4
0x2519bd7a8:	mov	x1, x24
0x2519bd7ac:	mov	x2, x23
0x2519bd7b0:	mov	x3, x22
0x2519bd7b4:	mov	x4, x21
0x2519bd7b8:	mov	x5, x20
0x2519bd7bc:	mov	x6, x19
0x2519bd7c0:	bl	#0x25810ba10
0x2519bd7c4:	mov	x19, x0
0x2519bd7c8:	cbnz	w0, #0x2519bd7f4
0x2519bd7cc:	mov	x0, x19
0x2519bd7d0:	ldp	x29, x30, [sp, #0x30]
0x2519bd7d4:	ldp	x20, x19, [sp, #0x20]
0x2519bd7d8:	ldp	x22, x21, [sp, #0x10]
0x2519bd7dc:	ldp	x24, x23, [sp], #0x40
0x2519bd7e0:	retab	
0x2519bd7e4:	bl	#0x251b89918
0x2519bd7e8:	mov	w19, #0xe7a4
0x2519bd7ec:	movk	w19, #0xfffe, lsl #16
0x2519bd7f0:	b	#0x2519bd7cc
0x2519bd7f4:	mov	x0, x19
0x2519bd7f8:	bl	#0x251b89908
0x2519bd7fc:	b	#0x2519bd7cc

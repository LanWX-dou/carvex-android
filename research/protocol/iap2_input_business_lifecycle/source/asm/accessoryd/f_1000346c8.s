; accessoryd 0x1000346c8-0x100034778; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000346c8:	pacibsp	
0x1000346cc:	stp	x22, x21, [sp, #-0x30]!
0x1000346d0:	stp	x20, x19, [sp, #0x10]
0x1000346d4:	stp	x29, x30, [sp, #0x20]
0x1000346d8:	add	x29, sp, #0x20
0x1000346dc:	mov	x20, x2
0x1000346e0:	mov	x21, x1
0x1000346e4:	mov	x19, x0
0x1000346e8:	bl	#0x1000345d8
0x1000346ec:	strh	wzr, [x19, #0xbe]
0x1000346f0:	ldrb	w8, [x19, #0xd4]
0x1000346f4:	and	w8, w8, #0xfffffff3
0x1000346f8:	strb	w8, [x19, #0xd4]
0x1000346fc:	ldr	x0, [x19, #0x108]
0x100034700:	bl	#0x100083130
0x100034704:	ldr	x0, [x19, #0x108]
0x100034708:	bl	#0x10008305c
0x10003470c:	str	x0, [x19, #0x108]
0x100034710:	cbz	w20, #0x10003472c
0x100034714:	str	xzr, [x19, #0x1d0]
0x100034718:	str	wzr, [x19, #0x1d8]
0x10003471c:	mov	w8, #1
0x100034720:	sturh	w8, [x19, #0xd5]
0x100034724:	add	x8, x19, #0x1ec
0x100034728:	str	xzr, [x8]
0x10003472c:	tbnz	w21, #0, #0x100034768
0x100034730:	ldr	x0, [x19, #0x120]
0x100034734:	adrp	x16, #0x100008000
0x100034738:	add	x16, x16, #0x664
0x10003473c:	paciza	x16
0x100034740:	mov	x1, x16
0x100034744:	bl	#0x100099494
0x100034748:	strh	wzr, [x19, #0xbc]
0x10003474c:	ldrb	w8, [x19, #0xd4]
0x100034750:	and	w8, w8, #0xfc
0x100034754:	strb	w8, [x19, #0xd4]
0x100034758:	cbz	w20, #0x100034768
0x10003475c:	str	wzr, [x19, #0x1cc]
0x100034760:	add	x8, x19, #0x1dc
0x100034764:	str	xzr, [x8]
0x100034768:	ldp	x29, x30, [sp, #0x20]
0x10003476c:	ldp	x20, x19, [sp, #0x10]
0x100034770:	ldp	x22, x21, [sp], #0x30
0x100034774:	retab	

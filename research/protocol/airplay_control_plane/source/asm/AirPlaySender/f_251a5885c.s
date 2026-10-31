; AirPlaySender 0x251a5885c-0x251a588c0; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a5885c:	pacibsp	
0x251a58860:	sub	sp, sp, #0x30
0x251a58864:	stp	x20, x19, [sp, #0x10]
0x251a58868:	stp	x29, x30, [sp, #0x20]
0x251a5886c:	add	x29, sp, #0x20
0x251a58870:	mov	x19, x1
0x251a58874:	mov	x20, x0
0x251a58878:	bl	#0x25810ac50
0x251a5887c:	stp	x20, x19, [sp]
0x251a58880:	ldr	w8, [x0, #0xe0]
0x251a58884:	cmp	w8, #5
0x251a58888:	b.ne	#0x251a588ac
0x251a5888c:	ldr	x0, [x0, #0x78]
0x251a58890:	adrp	x16, #0x2519c6000
0x251a58894:	add	x16, x16, #0x9f0
0x251a58898:	paciza	x16
0x251a5889c:	mov	x1, x16
0x251a588a0:	mov	x2, sp
0x251a588a4:	bl	#0x25810d260
0x251a588a8:	b	#0x251a588b0
0x251a588ac:	mov	w0, #0
0x251a588b0:	ldp	x29, x30, [sp, #0x20]
0x251a588b4:	ldp	x20, x19, [sp, #0x10]
0x251a588b8:	add	sp, sp, #0x30
0x251a588bc:	retab	

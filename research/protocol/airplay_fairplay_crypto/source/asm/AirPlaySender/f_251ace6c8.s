; AirPlaySender 0x251ace6c8-0x251ace720; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251ace6c8:	pacibsp	
0x251ace6cc:	sub	sp, sp, #0x30
0x251ace6d0:	stp	x20, x19, [sp, #0x10]
0x251ace6d4:	stp	x29, x30, [sp, #0x20]
0x251ace6d8:	add	x29, sp, #0x20
0x251ace6dc:	mov	x19, x0
0x251ace6e0:	adrp	x8, #0x2680d3000
0x251ace6e4:	ldr	x8, [x8, #0x150]
0x251ace6e8:	ldr	x0, [x8]
0x251ace6ec:	mov	x1, #0
0x251ace6f0:	bl	#0x25810aa90
0x251ace6f4:	mov	x20, x0
0x251ace6f8:	str	x19, [sp]
0x251ace6fc:	adrp	x2, #0x276139000
0x251ace700:	add	x2, x2, #0x50
0x251ace704:	mov	x1, #0
0x251ace708:	bl	#0x25810aa50
0x251ace70c:	mov	x0, x20
0x251ace710:	ldp	x29, x30, [sp, #0x20]
0x251ace714:	ldp	x20, x19, [sp, #0x10]
0x251ace718:	add	sp, sp, #0x30
0x251ace71c:	retab	

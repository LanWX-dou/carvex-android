; airplaysender 0x251a356c8-0x251a356f8; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a356c8:	pacibsp	
0x251a356cc:	sub	sp, sp, #0x20
0x251a356d0:	stp	x29, x30, [sp, #0x10]
0x251a356d4:	add	x29, sp, #0x10
0x251a356d8:	str	x1, [sp]
0x251a356dc:	adrp	x2, #0x27612c000
0x251a356e0:	add	x2, x2, #0x290
0x251a356e4:	mov	x1, #0
0x251a356e8:	bl	#0x2581026d0
0x251a356ec:	ldp	x29, x30, [sp, #0x10]
0x251a356f0:	add	sp, sp, #0x20
0x251a356f4:	retab	

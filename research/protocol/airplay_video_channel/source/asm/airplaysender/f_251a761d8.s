; airplaysender 0x251a761d8-0x251a76260; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a761d8:	pacibsp	
0x251a761dc:	sub	sp, sp, #0x50
0x251a761e0:	stp	x20, x19, [sp, #0x30]
0x251a761e4:	stp	x29, x30, [sp, #0x40]
0x251a761e8:	add	x29, sp, #0x40
0x251a761ec:	mov	x19, x1
0x251a761f0:	mov	x20, x0
0x251a761f4:	bl	#0x25810ac50
0x251a761f8:	ldr	x0, [x0]
0x251a761fc:	mov	x8, sp
0x251a76200:	adrp	x16, #0x2681b4000
0x251a76204:	ldr	x16, [x16, #0xed0]
0x251a76208:	mov	x17, x8
0x251a7620c:	movk	x17, #0x6ae1, lsl #48
0x251a76210:	pacda	x16, x17
0x251a76214:	str	x16, [sp]
0x251a76218:	adrp	x9, #0x251c6b000
0x251a7621c:	ldr	d0, [x9, #8]
0x251a76220:	str	d0, [sp, #8]
0x251a76224:	add	x8, x8, #0x10
0x251a76228:	adrp	x9, #0x2693e6000
0x251a7622c:	add	x9, x9, #0x2a0
0x251a76230:	adrp	x16, #0x251a79000
0x251a76234:	add	x16, x16, #0xffc
0x251a76238:	pacia	x16, x8
0x251a7623c:	stp	x16, x9, [sp, #0x10]
0x251a76240:	str	x20, [sp, #0x20]
0x251a76244:	strb	w19, [sp, #0x28]
0x251a76248:	mov	x1, sp
0x251a7624c:	bl	#0x2580f54f0
0x251a76250:	ldp	x29, x30, [sp, #0x40]
0x251a76254:	ldp	x20, x19, [sp, #0x30]
0x251a76258:	add	sp, sp, #0x50
0x251a7625c:	retab	

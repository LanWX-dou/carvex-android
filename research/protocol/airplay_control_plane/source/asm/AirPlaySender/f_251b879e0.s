; AirPlaySender 0x251b879e0-0x251b87acc; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251b879e0:	pacibsp	
0x251b879e4:	sub	sp, sp, #0xe0
0x251b879e8:	stp	x20, x19, [sp, #0xc0]
0x251b879ec:	stp	x29, x30, [sp, #0xd0]
0x251b879f0:	add	x29, sp, #0xd0
0x251b879f4:	mov	x19, x0
0x251b879f8:	sub	x20, x29, #0x40
0x251b879fc:	bl	#0x2519a8600
0x251b87a00:	stur	x8, [x29, #-0x18]
0x251b87a04:	bl	#0x25810ac50
0x251b87a08:	movi	v0.2d, #0000000000000000
0x251b87a0c:	stp	q0, q0, [x20]
0x251b87a10:	stp	q0, q0, [sp, #0x70]
0x251b87a14:	stp	q0, q0, [sp, #0x50]
0x251b87a18:	stp	q0, q0, [sp, #0x30]
0x251b87a1c:	stp	q0, q0, [sp, #0x10]
0x251b87a20:	str	xzr, [sp, #8]
0x251b87a24:	ldr	x0, [x0, #0x18]
0x251b87a28:	cbz	x0, #0x251b87a9c
0x251b87a2c:	add	x1, sp, #0x10
0x251b87a30:	bl	#0x25199e50c
0x251b87a34:	add	x4, sp, #8
0x251b87a38:	mov	x0, x19
0x251b87a3c:	mov	w1, #0
0x251b87a40:	mov	w2, #0
0x251b87a44:	mov	w3, #0
0x251b87a48:	bl	#0x251aaf934
0x251b87a4c:	cbnz	w0, #0x251b87aa4
0x251b87a50:	ldr	x20, [sp, #8]
0x251b87a54:	add	x1, sp, #0x10
0x251b87a58:	sub	x3, x29, #0x40
0x251b87a5c:	mov	x0, x20
0x251b87a60:	mov	x2, #-1
0x251b87a64:	bl	#0x25810fd30
0x251b87a68:	cmp	w0, #0
0x251b87a6c:	cset	w19, eq
0x251b87a70:	cbz	x20, #0x251b87a7c
0x251b87a74:	mov	x0, x20
0x251b87a78:	bl	#0x2580f5830
0x251b87a7c:	ldur	x8, [x29, #-0x18]
0x251b87a80:	bl	#0x251997d70
0x251b87a84:	b.ne	#0x251b87ac8
0x251b87a88:	mov	x0, x19
0x251b87a8c:	ldp	x29, x30, [sp, #0xd0]
0x251b87a90:	ldp	x20, x19, [sp, #0xc0]
0x251b87a94:	add	sp, sp, #0xe0
0x251b87a98:	retab	
0x251b87a9c:	mov	w19, #0
0x251b87aa0:	b	#0x251b87a7c
0x251b87aa4:	adrp	x1, #0x251c1c000
0x251b87aa8:	add	x1, x1, #0x26d
0x251b87aac:	mov	w2, #0x19f
0x251b87ab0:	mov	w3, #0
0x251b87ab4:	bl	#0x258109a30
0x251b87ab8:	mov	w19, #0
0x251b87abc:	ldr	x20, [sp, #8]
0x251b87ac0:	cbnz	x20, #0x251b87a74
0x251b87ac4:	b	#0x251b87a7c
0x251b87ac8:	bl	#0x2580f4380

; AirPlaySender 0x2519c19b4-0x2519c1a64; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519c19b4:	pacibsp	
0x2519c19b8:	stp	x22, x21, [sp, #-0x30]!
0x2519c19bc:	stp	x20, x19, [sp, #0x10]
0x2519c19c0:	stp	x29, x30, [sp, #0x20]
0x2519c19c4:	add	x29, sp, #0x20
0x2519c19c8:	mov	x21, x5
0x2519c19cc:	mov	x20, x2
0x2519c19d0:	mov	x22, x1
0x2519c19d4:	bl	#0x25810ac50
0x2519c19d8:	ldr	x1, [x0, #0x68]
0x2519c19dc:	cbz	x1, #0x2519c1a44
0x2519c19e0:	add	x8, x1, #0xc
0x2519c19e4:	cmp	x22, x8
0x2519c19e8:	b.ne	#0x2519c1a4c
0x2519c19ec:	mov	x19, x0
0x2519c19f0:	cbz	x20, #0x2519c1a28
0x2519c19f4:	ldrb	w8, [x21, #0x38]
0x2519c19f8:	tbz	w8, #0, #0x2519c1a58
0x2519c19fc:	ldr	d0, [x21]
0x2519c1a00:	fcvtzu	d0, d0
0x2519c1a04:	str	s0, [x1, #4]
0x2519c1a08:	mov	w8, w20
0x2519c1a0c:	ldr	x1, [x19, #0x68]
0x2519c1a10:	str	x8, [x1, #0x5c0]
0x2519c1a14:	ldr	x0, [x19, #8]
0x2519c1a18:	bl	#0x25810daa0
0x2519c1a1c:	mov	w0, #0
0x2519c1a20:	str	xzr, [x19, #0x68]
0x2519c1a24:	b	#0x2519c1a34
0x2519c1a28:	ldr	x0, [x19, #8]
0x2519c1a2c:	bl	#0x25810da90
0x2519c1a30:	mov	w0, #0
0x2519c1a34:	ldp	x29, x30, [sp, #0x20]
0x2519c1a38:	ldp	x20, x19, [sp, #0x10]
0x2519c1a3c:	ldp	x22, x21, [sp], #0x30
0x2519c1a40:	retab	
0x2519c1a44:	bl	#0x251bcc410
0x2519c1a48:	b	#0x2519c1a50
0x2519c1a4c:	bl	#0x251bcc3e8
0x2519c1a50:	mov	w0, #-0x4199
0x2519c1a54:	b	#0x2519c1a34
0x2519c1a58:	bl	#0x251bcc3fc
0x2519c1a5c:	mov	w0, #-0x4198
0x2519c1a60:	b	#0x2519c1a34

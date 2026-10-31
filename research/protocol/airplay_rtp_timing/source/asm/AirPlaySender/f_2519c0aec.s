; AirPlaySender 0x2519c0aec-0x2519c0b88; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519c0aec:	pacibsp	
0x2519c0af0:	sub	sp, sp, #0x40
0x2519c0af4:	stp	x22, x21, [sp, #0x10]
0x2519c0af8:	stp	x20, x19, [sp, #0x20]
0x2519c0afc:	stp	x29, x30, [sp, #0x30]
0x2519c0b00:	add	x29, sp, #0x30
0x2519c0b04:	mov	x19, x2
0x2519c0b08:	mov	x20, x1
0x2519c0b0c:	str	wzr, [sp, #0xc]
0x2519c0b10:	bl	#0x25810ac50
0x2519c0b14:	ldr	x8, [x0, #0x68]
0x2519c0b18:	cbnz	x8, #0x2519c0b60
0x2519c0b1c:	mov	x21, x0
0x2519c0b20:	ldr	x0, [x0, #8]
0x2519c0b24:	add	x1, sp, #0xc
0x2519c0b28:	bl	#0x25810dab0
0x2519c0b2c:	mov	x8, x0
0x2519c0b30:	str	x0, [x21, #0x68]
0x2519c0b34:	ldr	w0, [sp, #0xc]
0x2519c0b38:	cbnz	w0, #0x2519c0b6c
0x2519c0b3c:	add	x8, x8, #0xc
0x2519c0b40:	str	x8, [x20]
0x2519c0b44:	mov	w8, #0x5b4
0x2519c0b48:	str	x8, [x19]
0x2519c0b4c:	ldp	x29, x30, [sp, #0x30]
0x2519c0b50:	ldp	x20, x19, [sp, #0x20]
0x2519c0b54:	ldp	x22, x21, [sp, #0x10]
0x2519c0b58:	add	sp, sp, #0x40
0x2519c0b5c:	retab	
0x2519c0b60:	bl	#0x251bcc3d4
0x2519c0b64:	mov	w0, #-0x4199
0x2519c0b68:	b	#0x2519c0b4c
0x2519c0b6c:	adrp	x1, #0x251c5c000
0x2519c0b70:	add	x1, x1, #0x605
0x2519c0b74:	mov	w2, #0xdd
0x2519c0b78:	mov	w3, #0
0x2519c0b7c:	bl	#0x258109a30
0x2519c0b80:	ldr	w0, [sp, #0xc]
0x2519c0b84:	b	#0x2519c0b4c

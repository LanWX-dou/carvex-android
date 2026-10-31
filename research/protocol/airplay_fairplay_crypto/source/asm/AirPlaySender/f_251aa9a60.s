; AirPlaySender 0x251aa9a60-0x251aa9b80; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251aa9a60:	pacibsp	
0x251aa9a64:	sub	sp, sp, #0x160
0x251aa9a68:	stp	x24, x23, [sp, #0x120]
0x251aa9a6c:	stp	x22, x21, [sp, #0x130]
0x251aa9a70:	stp	x20, x19, [sp, #0x140]
0x251aa9a74:	stp	x29, x30, [sp, #0x150]
0x251aa9a78:	add	x29, sp, #0x150
0x251aa9a7c:	mov	x19, x3
0x251aa9a80:	mov	x21, x2
0x251aa9a84:	mov	x22, x1
0x251aa9a88:	adrp	x8, #0x2681b4000
0x251aa9a8c:	ldr	x8, [x8, #0xee0]
0x251aa9a90:	ldr	x8, [x8]
0x251aa9a94:	stur	x8, [x29, #-0x38]
0x251aa9a98:	bl	#0x25810ac50
0x251aa9a9c:	mov	x23, x0
0x251aa9aa0:	movi	v0.2d, #0000000000000000
0x251aa9aa4:	stp	q0, q0, [sp, #0xb0]
0x251aa9aa8:	stp	q0, q0, [sp, #0x90]
0x251aa9aac:	stp	q0, q0, [sp, #0x70]
0x251aa9ab0:	stp	q0, q0, [sp, #0x50]
0x251aa9ab4:	stp	q0, q0, [sp, #0x30]
0x251aa9ab8:	stp	q0, q0, [sp, #0x10]
0x251aa9abc:	str	q0, [sp]
0x251aa9ac0:	ldr	x0, [x0, #0x30]
0x251aa9ac4:	mov	w1, #0x10
0x251aa9ac8:	bl	#0x25810e760
0x251aa9acc:	cbz	x0, #0x251aa9b6c
0x251aa9ad0:	mov	x20, x0
0x251aa9ad4:	mov	w1, #0x10
0x251aa9ad8:	bl	#0x25810e790
0x251aa9adc:	mov	x0, sp
0x251aa9ae0:	bl	#0x25810e690
0x251aa9ae4:	mov	x0, sp
0x251aa9ae8:	mov	x1, x22
0x251aa9aec:	mov	x2, x21
0x251aa9af0:	bl	#0x25810e6a0
0x251aa9af4:	mov	x0, sp
0x251aa9af8:	add	x1, x23, #0x10
0x251aa9afc:	mov	w2, #0x10
0x251aa9b00:	bl	#0x25810e6a0
0x251aa9b04:	sub	x21, x29, #0x78
0x251aa9b08:	sub	x0, x29, #0x78
0x251aa9b0c:	mov	x1, sp
0x251aa9b10:	bl	#0x25810e680
0x251aa9b14:	mov	x0, x20
0x251aa9b18:	bl	#0x25810e780
0x251aa9b1c:	ldur	q0, [x29, #-0x78]
0x251aa9b20:	str	q0, [x0]
0x251aa9b24:	mov	x8, #-0x40
0x251aa9b28:	strb	wzr, [x21], #1
0x251aa9b2c:	adds	x8, x8, #1
0x251aa9b30:	b.lo	#0x251aa9b28
0x251aa9b34:	mov	w0, #0
0x251aa9b38:	str	x20, [x19]
0x251aa9b3c:	ldur	x8, [x29, #-0x38]
0x251aa9b40:	adrp	x9, #0x2681b4000
0x251aa9b44:	ldr	x9, [x9, #0xee0]
0x251aa9b48:	ldr	x9, [x9]
0x251aa9b4c:	cmp	x9, x8
0x251aa9b50:	b.ne	#0x251aa9b7c
0x251aa9b54:	ldp	x29, x30, [sp, #0x150]
0x251aa9b58:	ldp	x20, x19, [sp, #0x140]
0x251aa9b5c:	ldp	x22, x21, [sp, #0x130]
0x251aa9b60:	ldp	x24, x23, [sp, #0x120]
0x251aa9b64:	add	sp, sp, #0x160
0x251aa9b68:	retab	
0x251aa9b6c:	bl	#0x251b84590
0x251aa9b70:	mov	w0, #0xe7d8
0x251aa9b74:	movk	w0, #0xfffe, lsl #16
0x251aa9b78:	b	#0x251aa9b3c
0x251aa9b7c:	bl	#0x2580f4380

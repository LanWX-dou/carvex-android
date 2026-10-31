; CoreUtils 0x18be7bb64-0x18be7bc8c; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be7bb64:	pacibsp	
0x18be7bb68:	stp	x24, x23, [sp, #-0x40]!
0x18be7bb6c:	stp	x22, x21, [sp, #0x10]
0x18be7bb70:	stp	x20, x19, [sp, #0x20]
0x18be7bb74:	stp	x29, x30, [sp, #0x30]
0x18be7bb78:	add	x29, sp, #0x30
0x18be7bb7c:	mov	x19, x4
0x18be7bb80:	mov	x20, x3
0x18be7bb84:	mov	x21, x2
0x18be7bb88:	mov	x22, x1
0x18be7bb8c:	mov	x24, x0
0x18be7bb90:	adrp	x8, #0x1e43d0000
0x18be7bb94:	ldr	x8, [x8, #0xc08]
0x18be7bb98:	cmn	x8, #1
0x18be7bb9c:	b.ne	#0x18be7bc5c
0x18be7bba0:	adrp	x8, #0x1e43d0000
0x18be7bba4:	ldr	x1, [x8, #0xc00]
0x18be7bba8:	mov	x0, #0
0x18be7bbac:	mov	w2, #0x128
0x18be7bbb0:	mov	x3, #0
0x18be7bbb4:	bl	#0x1900ce6a0
0x18be7bbb8:	mov	x23, x0
0x18be7bbbc:	cbz	x0, #0x18be7bc80
0x18be7bbc0:	movi	v0.2d, #0000000000000000
0x18be7bbc4:	stur	q0, [x23, #0xf8]
0x18be7bbc8:	stur	q0, [x23, #0xe8]
0x18be7bbcc:	stur	q0, [x23, #0xd8]
0x18be7bbd0:	stur	q0, [x23, #0xc8]
0x18be7bbd4:	stur	q0, [x23, #0xb8]
0x18be7bbd8:	stur	q0, [x23, #0xa8]
0x18be7bbdc:	stur	q0, [x23, #0x98]
0x18be7bbe0:	stur	q0, [x23, #0x88]
0x18be7bbe4:	stur	q0, [x23, #0x78]
0x18be7bbe8:	stur	q0, [x23, #0x68]
0x18be7bbec:	stur	q0, [x23, #0x58]
0x18be7bbf0:	stur	q0, [x23, #0x48]
0x18be7bbf4:	stur	q0, [x23, #0x38]
0x18be7bbf8:	mov	x8, x23
0x18be7bbfc:	str	q0, [x8, #0x18]!
0x18be7bc00:	stur	q0, [x23, #0x28]
0x18be7bc04:	stp	q0, q0, [x8, #0x100]
0x18be7bc08:	str	q0, [x8, #0xf0]
0x18be7bc0c:	str	x24, [x23, #0x10]
0x18be7bc10:	ldr	x8, [x24]
0x18be7bc14:	mov	x0, x23
0x18be7bc18:	mov	x1, x22
0x18be7bc1c:	mov	x2, x21
0x18be7bc20:	mov	x3, x20
0x18be7bc24:	blraaz	x8
0x18be7bc28:	mov	x20, x0
0x18be7bc2c:	cbz	w0, #0x18be7bc3c
0x18be7bc30:	mov	x0, x23
0x18be7bc34:	bl	#0x1900caac0
0x18be7bc38:	mov	x23, #0
0x18be7bc3c:	cbz	x19, #0x18be7bc44
0x18be7bc40:	str	w20, [x19]
0x18be7bc44:	mov	x0, x23
0x18be7bc48:	ldp	x29, x30, [sp, #0x30]
0x18be7bc4c:	ldp	x20, x19, [sp, #0x20]
0x18be7bc50:	ldp	x22, x21, [sp, #0x10]
0x18be7bc54:	ldp	x24, x23, [sp], #0x40
0x18be7bc58:	retab	
0x18be7bc5c:	adrp	x0, #0x1e43d0000
0x18be7bc60:	add	x0, x0, #0xc08
0x18be7bc64:	adrp	x16, #0x18be7c000
0x18be7bc68:	add	x16, x16, #0x4ec
0x18be7bc6c:	paciza	x16
0x18be7bc70:	mov	x2, x16
0x18be7bc74:	mov	x1, #0
0x18be7bc78:	bl	#0x1900cc2c0
0x18be7bc7c:	b	#0x18be7bba0
0x18be7bc80:	mov	w20, #-0x1a48
0x18be7bc84:	cbnz	x19, #0x18be7bc40
0x18be7bc88:	b	#0x18be7bc44

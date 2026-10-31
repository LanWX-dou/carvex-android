; AirPlaySender 0x251a52a68-0x251a52b1c; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a52a68:	pacibsp	
0x251a52a6c:	stp	x22, x21, [sp, #-0x30]!
0x251a52a70:	stp	x20, x19, [sp, #0x10]
0x251a52a74:	stp	x29, x30, [sp, #0x20]
0x251a52a78:	add	x29, sp, #0x20
0x251a52a7c:	mov	x19, x3
0x251a52a80:	mov	x20, x2
0x251a52a84:	mov	x21, x1
0x251a52a88:	mov	x22, x0
0x251a52a8c:	bl	#0x258109150
0x251a52a90:	ldr	x16, [x0, #0x10]!
0x251a52a94:	mov	x17, x0
0x251a52a98:	movk	x17, #0x8354, lsl #48
0x251a52a9c:	autda	x16, x17
0x251a52aa0:	ldr	x5, [x16, #0x40]!
0x251a52aa4:	cbz	x5, #0x251a52b08
0x251a52aa8:	mov	x4, x16
0x251a52aac:	movk	x4, #0xb90f, lsl #48
0x251a52ab0:	mov	x16, x5
0x251a52ab4:	mov	x17, x4
0x251a52ab8:	autia	x16, x17
0x251a52abc:	mov	x17, x16
0x251a52ac0:	xpaci	x17
0x251a52ac4:	cmp	x16, x17
0x251a52ac8:	b.eq	#0x251a52ad0
0x251a52acc:	brk	#0xc470
0x251a52ad0:	paciza	x16
0x251a52ad4:	cbz	x16, #0x251a52b08
0x251a52ad8:	mov	x0, x22
0x251a52adc:	mov	x1, x21
0x251a52ae0:	mov	x2, x20
0x251a52ae4:	mov	x3, x19
0x251a52ae8:	ldp	x29, x30, [sp, #0x20]
0x251a52aec:	ldp	x20, x19, [sp, #0x10]
0x251a52af0:	ldp	x22, x21, [sp], #0x30
0x251a52af4:	autibsp	
0x251a52af8:	eor	x16, x30, x30, lsl #1
0x251a52afc:	tbz	x16, #0x3e, #0x251a52b04
0x251a52b00:	brk	#0xc471
0x251a52b04:	braa	x5, x4
0x251a52b08:	mov	w0, #-0x31ee
0x251a52b0c:	ldp	x29, x30, [sp, #0x20]
0x251a52b10:	ldp	x20, x19, [sp, #0x10]
0x251a52b14:	ldp	x22, x21, [sp], #0x30
0x251a52b18:	retab	

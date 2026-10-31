; AirPlaySender 0x251a89d50-0x251a89e0c; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a89d50:	pacibsp	
0x251a89d54:	stp	x22, x21, [sp, #-0x30]!
0x251a89d58:	stp	x20, x19, [sp, #0x10]
0x251a89d5c:	stp	x29, x30, [sp, #0x20]
0x251a89d60:	add	x29, sp, #0x20
0x251a89d64:	mov	x19, x3
0x251a89d68:	mov	x20, x2
0x251a89d6c:	mov	x21, x1
0x251a89d70:	mov	x22, x0
0x251a89d74:	bl	#0x258109150
0x251a89d78:	ldr	x16, [x0, #0x10]!
0x251a89d7c:	mov	x17, x0
0x251a89d80:	movk	x17, #0xa363, lsl #48
0x251a89d84:	autda	x16, x17
0x251a89d88:	ldr	x7, [x16, #0x38]!
0x251a89d8c:	cbz	x7, #0x251a89df8
0x251a89d90:	mov	x6, x16
0x251a89d94:	movk	x6, #0xe8aa, lsl #48
0x251a89d98:	mov	x16, x7
0x251a89d9c:	mov	x17, x6
0x251a89da0:	autia	x16, x17
0x251a89da4:	mov	x17, x16
0x251a89da8:	xpaci	x17
0x251a89dac:	cmp	x16, x17
0x251a89db0:	b.eq	#0x251a89db8
0x251a89db4:	brk	#0xc470
0x251a89db8:	paciza	x16
0x251a89dbc:	cbz	x16, #0x251a89df8
0x251a89dc0:	mov	x0, x22
0x251a89dc4:	mov	x1, x21
0x251a89dc8:	mov	w2, #0x20
0x251a89dcc:	mov	x3, x20
0x251a89dd0:	mov	w4, #0x20
0x251a89dd4:	mov	x5, x19
0x251a89dd8:	ldp	x29, x30, [sp, #0x20]
0x251a89ddc:	ldp	x20, x19, [sp, #0x10]
0x251a89de0:	ldp	x22, x21, [sp], #0x30
0x251a89de4:	autibsp	
0x251a89de8:	eor	x16, x30, x30, lsl #1
0x251a89dec:	tbz	x16, #0x3e, #0x251a89df4
0x251a89df0:	brk	#0xc471
0x251a89df4:	braa	x7, x6
0x251a89df8:	mov	w0, #-0x31ee
0x251a89dfc:	ldp	x29, x30, [sp, #0x20]
0x251a89e00:	ldp	x20, x19, [sp, #0x10]
0x251a89e04:	ldp	x22, x21, [sp], #0x30
0x251a89e08:	retab	

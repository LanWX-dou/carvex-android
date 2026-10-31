; AirPlaySender 0x2519dcb7c-0x2519de0e8; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519dcb7c:	pacibsp	
0x2519dcb80:	sub	sp, sp, #0x140
0x2519dcb84:	stp	x28, x27, [sp, #0xe0]
0x2519dcb88:	stp	x26, x25, [sp, #0xf0]
0x2519dcb8c:	stp	x24, x23, [sp, #0x100]
0x2519dcb90:	stp	x22, x21, [sp, #0x110]
0x2519dcb94:	stp	x20, x19, [sp, #0x120]
0x2519dcb98:	stp	x29, x30, [sp, #0x130]
0x2519dcb9c:	add	x29, sp, #0x130
0x2519dcba0:	stp	x4, x3, [sp, #0x60]
0x2519dcba4:	str	w2, [sp, #0x5c]
0x2519dcba8:	str	x1, [sp, #0x70]
0x2519dcbac:	mov	x23, x0
0x2519dcbb0:	adrp	x8, #0x2681b4000
0x2519dcbb4:	ldr	x8, [x8, #0xee0]
0x2519dcbb8:	ldr	x8, [x8]
0x2519dcbbc:	stur	x8, [x29, #-0x60]
0x2519dcbc0:	mov	x25, #0xb4fa
0x2519dcbc4:	movk	x25, #0x6d3c, lsl #16
0x2519dcbc8:	movk	x25, #0x2a54, lsl #32
0x2519dcbcc:	movk	x25, #0x375b, lsl #48
0x2519dcbd0:	mov	w24, #0x1f79
0x2519dcbd4:	movk	w24, #0xd3ef, lsl #16
0x2519dcbd8:	mov	w14, #0x9f29
0x2519dcbdc:	movk	w14, #0x6c83, lsl #16
0x2519dcbe0:	mov	w19, #0x14f8
0x2519dcbe4:	movk	w19, #0x1455, lsl #16
0x2519dcbe8:	adrp	x8, #0x26e7db000
0x2519dcbec:	ldr	w10, [x8, #0x4e8]
0x2519dcbf0:	adrp	x9, #0x26e7db000
0x2519dcbf4:	ldr	w11, [x9, #0x410]
0x2519dcbf8:	eor	w10, w10, w25
0x2519dcbfc:	eor	w10, w10, w11
0x2519dcc00:	mul	w10, w10, w24
0x2519dcc04:	adrp	x12, #0x251c70000
0x2519dcc08:	add	x12, x12, #0xc70
0x2519dcc0c:	add	x12, x12, w10, uxtb
0x2519dcc10:	ldrb	w12, [x12]
0x2519dcc14:	mov	w13, #0x69
0x2519dcc18:	eor	w12, w12, w13
0x2519dcc1c:	adrp	x13, #0x251c6d000
0x2519dcc20:	add	x13, x13, #0x90
0x2519dcc24:	ldrb	w12, [x13, w12, uxtw]
0x2519dcc28:	eor	w10, w10, w12
0x2519dcc2c:	and	w10, w10, #0xff
0x2519dcc30:	adrp	x22, #0x27612b000
0x2519dcc34:	add	x22, x22, #0x8f0
0x2519dcc38:	sub	w10, w10, #0x2b
0x2519dcc3c:	ldr	x26, [x22, w10, sxtw #3]
0x2519dcc40:	ldr	x10, [x26, #-4]!
0x2519dcc44:	sub	w11, w11, w10
0x2519dcc48:	eor	w11, w11, w25
0x2519dcc4c:	mul	w11, w11, w24
0x2519dcc50:	adrp	x12, #0x251c6f000
0x2519dcc54:	add	x12, x12, #0xa60
0x2519dcc58:	add	x12, x12, w11, uxtb
0x2519dcc5c:	ldrb	w12, [x12]
0x2519dcc60:	eor	w12, w12, #0x18
0x2519dcc64:	adrp	x13, #0x251c70000
0x2519dcc68:	add	x13, x13, #0xb70
0x2519dcc6c:	ldrb	w12, [x13, w12, uxtw]
0x2519dcc70:	eor	w11, w11, w12
0x2519dcc74:	and	w11, w11, #0xff
0x2519dcc78:	add	w11, w11, #0x69
0x2519dcc7c:	ldr	x27, [x22, w11, uxtw #3]
0x2519dcc80:	ldr	x11, [x27]
0x2519dcc84:	sub	x10, x11, x10
0x2519dcc88:	add	x11, sp, #0x98
0x2519dcc8c:	add	x10, x10, x11
0x2519dcc90:	madd	x11, x10, x24, x25
0x2519dcc94:	eor	x10, x10, x25
0x2519dcc98:	mul	x10, x10, x24
0x2519dcc9c:	str	x11, [x26]
0x2519dcca0:	str	x10, [x27]
0x2519dcca4:	sub	x10, x29, #0x90
0x2519dcca8:	mov	w11, #0x2ee
0x2519dccac:	movk	w11, #0x944b, lsl #16
0x2519dccb0:	orr	w11, w10, w11
0x2519dccb4:	mov	x12, #0xfd11
0x2519dccb8:	movk	x12, #0x6bb4, lsl #16
0x2519dccbc:	movk	x12, #0xea63, lsl #32
0x2519dccc0:	movk	x12, #0x719e, lsl #48
0x2519dccc4:	orr	w10, w10, w12
0x2519dccc8:	sub	w10, w12, w10
0x2519dcccc:	add	w10, w10, w11
0x2519dccd0:	mov	w11, #0xc787
0x2519dccd4:	movk	w11, #0xa963, lsl #16
0x2519dccd8:	eor	w10, w10, w11
0x2519dccdc:	mov	w11, #0x25fc
0x2519dcce0:	movk	w11, #0xdb53, lsl #16
0x2519dcce4:	msub	w10, w10, w14, w11
0x2519dcce8:	stur	w10, [x29, #-0x8c]
0x2519dccec:	ldr	w10, [x26]
0x2519dccf0:	ldr	w11, [x27]
0x2519dccf4:	sub	w10, w11, w10
0x2519dccf8:	eor	w10, w10, w25
0x2519dccfc:	mul	w10, w10, w24
0x2519dcd00:	ldr	x11, [x22, #0x158]
0x2519dcd04:	sub	x11, x11, #0xc
0x2519dcd08:	str	x11, [sp, #0x50]
0x2519dcd0c:	add	x11, x11, w10, uxtb
0x2519dcd10:	ldrb	w11, [x11]
0x2519dcd14:	mov	w12, #0xe4
0x2519dcd18:	eor	w11, w11, w12
0x2519dcd1c:	ldr	x12, [x22, #0x1f8]
0x2519dcd20:	sub	x20, x12, #4
0x2519dcd24:	ldrb	w11, [x20, w11, uxtw]
0x2519dcd28:	eor	w10, w11, w10
0x2519dcd2c:	and	w10, w10, #0xff
0x2519dcd30:	add	w10, w10, #0x3c8
0x2519dcd34:	ldr	w8, [x8, #0x4e8]
0x2519dcd38:	ldr	w9, [x9, #0x410]
0x2519dcd3c:	sub	w8, w9, w8
0x2519dcd40:	eor	w8, w8, w25
0x2519dcd44:	mul	w8, w8, w24
0x2519dcd48:	adrp	x9, #0x251c70000
0x2519dcd4c:	add	x9, x9, #0xd70
0x2519dcd50:	add	x9, x9, w8, uxtb
0x2519dcd54:	ldrb	w9, [x9]
0x2519dcd58:	mov	w11, #0x99
0x2519dcd5c:	eor	w9, w9, w11
0x2519dcd60:	adrp	x11, #0x251c6d000
0x2519dcd64:	add	x11, x11, #0x190
0x2519dcd68:	ldrb	w9, [x11, w9, uxtw]
0x2519dcd6c:	eor	w8, w8, w9
0x2519dcd70:	and	w8, w8, #0xff
0x2519dcd74:	sub	w8, w8, #0x9c
0x2519dcd78:	ldr	x8, [x22, w8, sxtw #3]
0x2519dcd7c:	sub	x28, x8, #0xc
0x2519dcd80:	ldr	x8, [x28, w10, uxtw #3]
0x2519dcd84:	sub	x0, x29, #0x90
0x2519dcd88:	mov	x17, #0xf9e7
0x2519dcd8c:	blraa	x8, x17
0x2519dcd90:	ldur	w21, [x29, #-0x90]
0x2519dcd94:	cmp	w21, w19
0x2519dcd98:	cset	w8, eq
0x2519dcd9c:	mov	w9, #0x4b
0x2519dcda0:	mul	w8, w8, w9
0x2519dcda4:	mov	w9, #0x8f
0x2519dcda8:	eor	w8, w8, w9
0x2519dcdac:	ldr	x8, [x28, w8, uxtw #3]
0x2519dcdb0:	mov	x17, #0xc3f2
0x2519dcdb4:	braa	x8, x17
0x2519dcdb8:	mov	w9, #0x251f
0x2519dcdbc:	movk	w9, #0xd9ec, lsl #16
0x2519dcdc0:	add	w9, w23, w9
0x2519dcdc4:	mov	w10, #0xdaed
0x2519dcdc8:	movk	w10, #0x2613, lsl #16
0x2519dcdcc:	and	w10, w9, w10
0x2519dcdd0:	mov	w9, w8
0x2519dcdd4:	mov	x11, #0x8dee
0x2519dcdd8:	movk	x11, #0xee72, lsl #16
0x2519dcddc:	movk	x11, #1, lsl #32
0x2519dcde0:	and	x11, x11, x9, lsl #1
0x2519dcde4:	add	x9, x9, x22
0x2519dcde8:	sub	x9, x9, x11
0x2519dcdec:	eor	x11, x9, x22
0x2519dcdf0:	add	x11, x24, x11
0x2519dcdf4:	ldrb	w11, [x11]
0x2519dcdf8:	cmp	w11, #0
0x2519dcdfc:	cset	w11, eq
0x2519dce00:	add	w8, w8, #1
0x2519dce04:	add	w10, w10, #0xc0
0x2519dce08:	mul	w10, w11, w10
0x2519dce0c:	eor	w10, w10, w23
0x2519dce10:	ldr	x10, [x28, w10, sxtw #3]
0x2519dce14:	mov	x17, #0xff56
0x2519dce18:	braa	x10, x17
0x2519dce1c:	ldr	x8, [sp, #0x48]
0x2519dce20:	b	#0x2519dd644
0x2519dce24:	sub	w8, w19, #0x77
0x2519dce28:	mov	w9, #0x242
0x2519dce2c:	ldr	w10, [sp, #0x130]
0x2519dce30:	add	x10, x22, x10
0x2519dce34:	ldr	x15, [sp, #0x118]
0x2519dce38:	add	x11, x15, #0xc
0x2519dce3c:	sub	x12, x29, #0x90
0x2519dce40:	mov	w13, #0xebc9
0x2519dce44:	movk	w13, #0x473, lsl #16
0x2519dce48:	orr	w13, w12, w13
0x2519dce4c:	sub	w13, w13, w12
0x2519dce50:	mov	w14, #0x1430
0x2519dce54:	movk	w14, #0xfb8c, lsl #16
0x2519dce58:	and	w12, w12, w14
0x2519dce5c:	add	w14, w19, #0x2fd
0x2519dce60:	add	w12, w13, w12
0x2519dce64:	mov	w13, #0x2ea0
0x2519dce68:	movk	w13, #0x395b, lsl #16
0x2519dce6c:	eor	w12, w12, w13
0x2519dce70:	mov	w13, #0x9f29
0x2519dce74:	movk	w13, #0x6c83, lsl #16
0x2519dce78:	mul	w12, w12, w13
0x2519dce7c:	eor	w12, w14, w12
0x2519dce80:	stur	w12, [x29, #-0x8c]
0x2519dce84:	add	x12, sp, #0x140
0x2519dce88:	str	x15, [x12, #0xc70]
0x2519dce8c:	str	x11, [x12, #0xc68]
0x2519dce90:	str	x10, [x12, #0xc80]
0x2519dce94:	add	x10, sp, #0x134
0x2519dce98:	str	x10, [x12, #0xc78]
0x2519dce9c:	ldp	x11, x10, [sp, #0xb8]
0x2519dcea0:	ldr	w10, [x10]
0x2519dcea4:	ldr	w11, [x11]
0x2519dcea8:	sub	w10, w11, w10
0x2519dceac:	mov	x11, #0xb4fa
0x2519dceb0:	movk	x11, #0x6d3c, lsl #16
0x2519dceb4:	movk	x11, #0x2a54, lsl #32
0x2519dceb8:	movk	x11, #0x375b, lsl #48
0x2519dcebc:	eor	w10, w10, w11
0x2519dcec0:	mul	w10, w10, w25
0x2519dcec4:	ldr	x11, [sp, #0x50]
0x2519dcec8:	add	x11, x11, w10, uxtb
0x2519dcecc:	ldrb	w11, [x11]
0x2519dced0:	mov	w12, #0xb4
0x2519dced4:	eor	w11, w11, w12
0x2519dced8:	ldr	x12, [sp, #0x48]
0x2519dcedc:	ldrb	w11, [x12, w11, uxtw]
0x2519dcee0:	orr	w22, w8, w9
0x2519dcee4:	eor	w8, w10, w11
0x2519dcee8:	and	w8, w8, #0xff
0x2519dceec:	add	w8, w8, #0x404
0x2519dcef0:	ldr	x8, [x16, w8, uxtw #3]
0x2519dcef4:	sub	x0, x29, #0x90
0x2519dcef8:	mov	x17, #0xc7d4
0x2519dcefc:	blraa	x8, x17
0x2519dcf00:	ldr	x16, [sp, #0x120]
0x2519dcf04:	mov	w8, #0
0x2519dcf08:	ldur	w9, [x29, #-0x90]
0x2519dcf0c:	mov	w10, #0x147f
0x2519dcf10:	movk	w10, #0x1455, lsl #16
0x2519dcf14:	add	w10, w10, #0x22b
0x2519dcf18:	eor	w10, w22, w10
0x2519dcf1c:	cmp	w9, w10
0x2519dcf20:	cset	w9, eq
0x2519dcf24:	mov	w10, #0x1ed
0x2519dcf28:	mul	w9, w9, w10
0x2519dcf2c:	eor	w9, w9, w19
0x2519dcf30:	ldr	x9, [x16, w9, uxtw #3]
0x2519dcf34:	mov	x17, #0x84de
0x2519dcf38:	braa	x9, x17
0x2519dcf3c:	and	w9, w8, #0xf0
0x2519dcf40:	orr	w8, w8, w9, lsr #4
0x2519dcf44:	and	w9, w8, #0xff
0x2519dcf48:	eor	w10, w10, #0x80
0x2519dcf4c:	lsr	w9, w9, w10
0x2519dcf50:	orr	w8, w9, w8
0x2519dcf54:	orr	w8, w8, w8, lsr #1
0x2519dcf58:	and	w8, w8, #1
0x2519dcf5c:	mov	w9, #-0xa464
0x2519dcf60:	mov	w10, #0x14f8
0x2519dcf64:	movk	w10, #0x1455, lsl #16
0x2519dcf68:	madd	w8, w8, w9, w10
0x2519dcf6c:	str	w8, [x0, #0x24]
0x2519dcf70:	ldur	x8, [x29, #-0x60]
0x2519dcf74:	adrp	x9, #0x2681b4000
0x2519dcf78:	ldr	x9, [x9, #0xee0]
0x2519dcf7c:	ldr	x9, [x9]
0x2519dcf80:	cmp	x9, x8
0x2519dcf84:	b.ne	#0x2519dcfa8
0x2519dcf88:	ldp	x29, x30, [sp, #0x1a0]
0x2519dcf8c:	ldp	x20, x19, [sp, #0x190]
0x2519dcf90:	ldp	x22, x21, [sp, #0x180]
0x2519dcf94:	ldp	x24, x23, [sp, #0x170]
0x2519dcf98:	ldp	x26, x25, [sp, #0x160]
0x2519dcf9c:	ldp	x28, x27, [sp, #0x150]
0x2519dcfa0:	add	sp, sp, #0x1b0
0x2519dcfa4:	retab	
0x2519dcfa8:	bl	#0x2580f4380
0x2519dcfac:	add	w24, w24, #1
0x2519dcfb0:	b	#0x251a19884
0x2519dcfb4:	str	w11, [sp, #0x28]
0x2519dcfb8:	add	w17, w24, #0x93
0x2519dcfbc:	ldrb	w8, [x10, #0x10]!
0x2519dcfc0:	ldrb	w9, [x14]
0x2519dcfc4:	eor	w8, w9, w8
0x2519dcfc8:	mov	x21, x14
0x2519dcfcc:	strb	w8, [x21, #0x10]!
0x2519dcfd0:	ldrb	w8, [x10, #1]
0x2519dcfd4:	ldrb	w9, [x14, #1]
0x2519dcfd8:	eor	w8, w9, w8
0x2519dcfdc:	strb	w8, [x14, #0x11]
0x2519dcfe0:	ldrb	w8, [x10, #2]
0x2519dcfe4:	ldrb	w9, [x14, #2]
0x2519dcfe8:	eor	w8, w9, w8
0x2519dcfec:	strb	w8, [x14, #0x12]
0x2519dcff0:	ldrb	w8, [x10, #3]
0x2519dcff4:	ldrb	w9, [x14, #3]
0x2519dcff8:	eor	w8, w9, w8
0x2519dcffc:	strb	w8, [x14, #0x13]
0x2519dd000:	ldrb	w8, [x10, #4]
0x2519dd004:	ldrb	w9, [x14, #4]
0x2519dd008:	eor	w8, w9, w8
0x2519dd00c:	strb	w8, [x14, #0x14]
0x2519dd010:	ldrb	w8, [x10, #5]
0x2519dd014:	ldrb	w9, [x14, #5]
0x2519dd018:	eor	w8, w9, w8
0x2519dd01c:	strb	w8, [x14, #0x15]
0x2519dd020:	ldrb	w8, [x10, #6]
0x2519dd024:	ldrb	w9, [x14, #6]
0x2519dd028:	eor	w8, w9, w8
0x2519dd02c:	strb	w8, [x14, #0x16]
0x2519dd030:	ldrb	w8, [x10, #7]
0x2519dd034:	ldrb	w9, [x14, #7]
0x2519dd038:	eor	w8, w9, w8
0x2519dd03c:	strb	w8, [x14, #0x17]
0x2519dd040:	ldrb	w8, [x10, #8]
0x2519dd044:	ldrb	w9, [x14, #8]
0x2519dd048:	eor	w8, w9, w8
0x2519dd04c:	strb	w8, [x14, #0x18]
0x2519dd050:	ldrb	w8, [x10, #9]
0x2519dd054:	ldrb	w9, [x14, #9]
0x2519dd058:	eor	w8, w9, w8
0x2519dd05c:	strb	w8, [x14, #0x19]
0x2519dd060:	ldrb	w8, [x10, #0xa]
0x2519dd064:	ldrb	w9, [x14, #0xa]
0x2519dd068:	eor	w8, w9, w8
0x2519dd06c:	strb	w8, [x14, #0x1a]
0x2519dd070:	ldrb	w8, [x10, #0xb]
0x2519dd074:	ldrb	w9, [x14, #0xb]
0x2519dd078:	eor	w8, w9, w8
0x2519dd07c:	strb	w8, [x14, #0x1b]
0x2519dd080:	ldrb	w8, [x10, #0xc]
0x2519dd084:	ldrb	w9, [x14, #0xc]
0x2519dd088:	eor	w8, w9, w8
0x2519dd08c:	strb	w8, [x14, #0x1c]
0x2519dd090:	ldrb	w8, [x10, #0xd]
0x2519dd094:	ldrb	w9, [x14, #0xd]
0x2519dd098:	eor	w8, w9, w8
0x2519dd09c:	strb	w8, [x14, #0x1d]
0x2519dd0a0:	ldrb	w8, [x10, #0xe]
0x2519dd0a4:	ldrb	w9, [x14, #0xe]
0x2519dd0a8:	eor	w8, w9, w8
0x2519dd0ac:	strb	w8, [x14, #0x1e]
0x2519dd0b0:	stp	x21, x10, [sp, #0x18]
0x2519dd0b4:	ldrb	w8, [x10, #0xf]
0x2519dd0b8:	ldrb	w9, [x14, #0xf]
0x2519dd0bc:	eor	w8, w9, w8
0x2519dd0c0:	strb	w8, [x14, #0x1f]
0x2519dd0c4:	mov	x23, #0
0x2519dd0c8:	ldr	x8, [x26, w24, sxtw #3]
0x2519dd0cc:	str	x8, [sp, #0x30]
0x2519dd0d0:	ldrb	w24, [sp, #0x152]
0x2519dd0d4:	ldrb	w30, [sp, #0x153]
0x2519dd0d8:	mov	w9, #2
0x2519dd0dc:	udiv	w8, w9, w30
0x2519dd0e0:	msub	w8, w8, w30, w9
0x2519dd0e4:	str	x8, [sp, #0xa8]
0x2519dd0e8:	ldrb	w2, [x21]
0x2519dd0ec:	ldrb	w4, [x21, #4]
0x2519dd0f0:	ldrb	w1, [x21, #8]
0x2519dd0f4:	ldrb	w7, [x21, #0xc]
0x2519dd0f8:	ldrb	w5, [x21, #1]
0x2519dd0fc:	ldrb	w3, [x21, #5]
0x2519dd100:	ldrb	w6, [x21, #9]
0x2519dd104:	ldrb	w13, [x21, #0xd]
0x2519dd108:	mov	w9, #3
0x2519dd10c:	udiv	w8, w9, w30
0x2519dd110:	msub	w8, w8, w30, w9
0x2519dd114:	str	x8, [sp, #0xa0]
0x2519dd118:	ldrb	w22, [x21, #2]
0x2519dd11c:	ldrb	w27, [x21, #0xa]
0x2519dd120:	ldrb	w15, [x21, #6]
0x2519dd124:	ldrb	w8, [x21, #0xe]
0x2519dd128:	ldrb	w16, [x21, #0xf]
0x2519dd12c:	ldrb	w0, [x21, #0xb]
0x2519dd130:	ldrb	w14, [x21, #7]
0x2519dd134:	ldrb	w20, [x21, #3]
0x2519dd138:	mov	w9, #0xd3
0x2519dd13c:	str	w17, [sp, #0xb0]
0x2519dd140:	eor	w12, w17, w9
0x2519dd144:	ldp	x10, x9, [sp, #8]
0x2519dd148:	ldur	x17, [x10, #-0x78]
0x2519dd14c:	ldrb	w28, [x17, x2]
0x2519dd150:	strb	w28, [x21]
0x2519dd154:	ldur	x17, [x10, #-0x58]
0x2519dd158:	ldrb	w2, [x17, x4]
0x2519dd15c:	strb	w2, [x21, #4]
0x2519dd160:	ldur	x17, [x10, #-0x38]
0x2519dd164:	ldrb	w1, [x17, x1]
0x2519dd168:	strb	w1, [x21, #8]
0x2519dd16c:	ldur	x17, [x10, #-0x18]
0x2519dd170:	ldrb	w17, [x17, x7]
0x2519dd174:	strb	w17, [x21, #0xc]
0x2519dd178:	ldur	x4, [x10, #-0x50]
0x2519dd17c:	ldrb	w7, [x4, x3]
0x2519dd180:	strb	w7, [x21, #1]
0x2519dd184:	ldur	x3, [x10, #-0x30]
0x2519dd188:	ldrb	w6, [x3, x6]
0x2519dd18c:	strb	w6, [x21, #5]
0x2519dd190:	ldur	x3, [x10, #-0x10]
0x2519dd194:	ldrb	w3, [x3, x13]
0x2519dd198:	strb	w3, [x21, #9]
0x2519dd19c:	ldur	x13, [x10, #-0x70]
0x2519dd1a0:	ldrb	w13, [x13, x5]
0x2519dd1a4:	strb	w13, [x21, #0xd]
0x2519dd1a8:	ldur	x4, [x10, #-0x28]
0x2519dd1ac:	ldrb	w5, [x4, x27]
0x2519dd1b0:	strb	w5, [x21, #2]
0x2519dd1b4:	ldur	x4, [x10, #-0x68]
0x2519dd1b8:	ldrb	w4, [x4, x22]
0x2519dd1bc:	strb	w4, [x21, #0xa]
0x2519dd1c0:	ldur	x22, [x10, #-8]
0x2519dd1c4:	ldrb	w22, [x22, x8]
0x2519dd1c8:	strb	w22, [x21, #6]
0x2519dd1cc:	ldur	x8, [x10, #-0x48]
0x2519dd1d0:	ldrb	w8, [x8, x15]
0x2519dd1d4:	strb	w8, [x21, #0xe]
0x2519dd1d8:	ldur	x15, [x10, #-0x20]
0x2519dd1dc:	ldrb	w15, [x15, x0]
0x2519dd1e0:	strb	w15, [x21, #0xf]
0x2519dd1e4:	ldur	x0, [x10, #-0x40]
0x2519dd1e8:	ldrb	w0, [x0, x14]
0x2519dd1ec:	strb	w0, [x21, #0xb]
0x2519dd1f0:	ldur	x14, [x10, #-0x60]
0x2519dd1f4:	ldrb	w14, [x14, x20]
0x2519dd1f8:	strb	w14, [x21, #7]
0x2519dd1fc:	ldr	x20, [x10]
0x2519dd200:	ldrb	w20, [x20, x16]
0x2519dd204:	strb	w20, [x21, #3]
0x2519dd208:	and	w16, w23, #0xff
0x2519dd20c:	udiv	w27, w16, w24
0x2519dd210:	msub	w16, w27, w24, w16
0x2519dd214:	ldr	x11, [sp, #0x98]
0x2519dd218:	add	x16, x11, x16, lsl #7
0x2519dd21c:	ldp	x27, x11, [x16]
0x2519dd220:	ldr	w27, [x27, x28, lsl #2]
0x2519dd224:	ldr	w11, [x11, x7, lsl #2]
0x2519dd228:	ldp	x7, x28, [x16, #0x10]
0x2519dd22c:	ldr	w5, [x7, x5, lsl #2]
0x2519dd230:	eor	w11, w11, w27
0x2519dd234:	ldr	w7, [x28, x20, lsl #2]
0x2519dd238:	eor	w5, w5, w7
0x2519dd23c:	eor	w28, w11, w5
0x2519dd240:	lsr	w7, w28, #0x18
0x2519dd244:	strb	w7, [x21, #3]
0x2519dd248:	lsr	w20, w28, #0x10
0x2519dd24c:	strb	w20, [x21, #2]
0x2519dd250:	lsr	w5, w28, #8
0x2519dd254:	strb	w5, [x21, #1]
0x2519dd258:	strb	w28, [x21]
0x2519dd25c:	add	x11, x16, #0x20
0x2519dd260:	cmp	w30, #1
0x2519dd264:	csel	x11, x16, x11, eq
0x2519dd268:	ldr	x11, [x11]
0x2519dd26c:	ldr	w11, [x11, x2, lsl #2]
0x2519dd270:	mov	w2, #0x28
0x2519dd274:	mov	w27, #8
0x2519dd278:	csel	x2, x27, x2, eq
0x2519dd27c:	ldr	x2, [x16, x2]
0x2519dd280:	ldr	w2, [x2, x6, lsl #2]
0x2519dd284:	mov	w6, #0x30
0x2519dd288:	mov	w27, #0x10
0x2519dd28c:	csel	x6, x27, x6, eq
0x2519dd290:	ldr	x6, [x16, x6]
0x2519dd294:	ldr	w6, [x6, x22, lsl #2]
0x2519dd298:	eor	w2, w2, w6
0x2519dd29c:	mov	w6, #0x38
0x2519dd2a0:	mov	w22, #0x18
0x2519dd2a4:	csel	x6, x22, x6, eq
0x2519dd2a8:	ldr	x6, [x16, x6]
0x2519dd2ac:	ldr	w14, [x6, x14, lsl #2]
0x2519dd2b0:	eor	w14, w2, w14
0x2519dd2b4:	eor	w14, w14, w11
0x2519dd2b8:	str	w14, [x21, #4]
0x2519dd2bc:	ldr	x11, [sp, #0xa8]
0x2519dd2c0:	add	x11, x16, x11, lsl #5
0x2519dd2c4:	ldp	x2, x6, [x11]
0x2519dd2c8:	ldr	w1, [x2, x1, lsl #2]
0x2519dd2cc:	lsl	w2, w12, #3
0x2519dd2d0:	sub	w2, w2, w12
0x2519dd2d4:	ldr	w3, [x6, x3, lsl #2]
0x2519dd2d8:	eor	w1, w3, w1
0x2519dd2dc:	ldp	x3, x11, [x11, #0x10]
0x2519dd2e0:	ldr	w3, [x3, x4, lsl #2]
0x2519dd2e4:	ldr	w11, [x11, x0, lsl #2]
0x2519dd2e8:	eor	w11, w3, w11
0x2519dd2ec:	eor	w1, w1, w11
0x2519dd2f0:	sub	w11, w2, #0x33e
0x2519dd2f4:	lsr	w0, w1, w11
0x2519dd2f8:	strb	w0, [x21, #0xb]
0x2519dd2fc:	lsr	w27, w1, #0x10
0x2519dd300:	strb	w27, [x21, #0xa]
0x2519dd304:	lsr	w6, w1, #8
0x2519dd308:	strb	w6, [x21, #9]
0x2519dd30c:	strb	w1, [x21, #8]
0x2519dd310:	ldr	x11, [sp, #0xa0]
0x2519dd314:	add	x11, x16, x11, lsl #5
0x2519dd318:	ldp	x16, x2, [x11]
0x2519dd31c:	ldr	w16, [x16, x17, lsl #2]
0x2519dd320:	ldr	w13, [x2, x13, lsl #2]
0x2519dd324:	eor	w13, w13, w16
0x2519dd328:	ldp	x16, x11, [x11, #0x10]
0x2519dd32c:	ldr	w8, [x16, x8, lsl #2]
0x2519dd330:	ldr	w11, [x11, x15, lsl #2]
0x2519dd334:	eor	w8, w8, w11
0x2519dd338:	eor	w16, w13, w8
0x2519dd33c:	str	w16, [x21, #0xc]
0x2519dd340:	ldurb	w8, [x9, #-0xf]
0x2519dd344:	eor	w8, w8, w28
0x2519dd348:	and	x2, x8, #0xff
0x2519dd34c:	strb	w8, [x21]
0x2519dd350:	ldurb	w8, [x9, #-0xe]
0x2519dd354:	eor	w8, w8, w5
0x2519dd358:	and	x5, x8, #0xff
0x2519dd35c:	strb	w8, [x21, #1]
0x2519dd360:	ldurb	w8, [x9, #-0xd]
0x2519dd364:	eor	w8, w8, w20
0x2519dd368:	and	x22, x8, #0xff
0x2519dd36c:	strb	w8, [x21, #2]
0x2519dd370:	ldurb	w8, [x9, #-0xc]
0x2519dd374:	eor	w8, w8, w7
0x2519dd378:	and	x20, x8, #0xff
0x2519dd37c:	strb	w8, [x21, #3]
0x2519dd380:	ldurb	w8, [x9, #-0xb]
0x2519dd384:	eor	w8, w8, w14
0x2519dd388:	and	x4, x8, #0xff
0x2519dd38c:	strb	w8, [x21, #4]
0x2519dd390:	ldurb	w8, [x9, #-0xa]
0x2519dd394:	eor	w8, w8, w14, lsr #8
0x2519dd398:	and	x3, x8, #0xff
0x2519dd39c:	strb	w8, [x21, #5]
0x2519dd3a0:	ldurb	w8, [x9, #-9]
0x2519dd3a4:	eor	w8, w8, w14, lsr #16
0x2519dd3a8:	and	x15, x8, #0xff
0x2519dd3ac:	strb	w8, [x21, #6]
0x2519dd3b0:	ldurb	w8, [x9, #-8]
0x2519dd3b4:	eor	w8, w8, w14, lsr #24
0x2519dd3b8:	and	x14, x8, #0xff
0x2519dd3bc:	strb	w8, [x21, #7]
0x2519dd3c0:	ldurb	w8, [x9, #-7]
0x2519dd3c4:	eor	w8, w8, w1
0x2519dd3c8:	and	x1, x8, #0xff
0x2519dd3cc:	strb	w8, [x21, #8]
0x2519dd3d0:	ldurb	w8, [x9, #-6]
0x2519dd3d4:	eor	w8, w8, w6
0x2519dd3d8:	and	x6, x8, #0xff
0x2519dd3dc:	strb	w8, [x21, #9]
0x2519dd3e0:	ldurb	w8, [x9, #-5]
0x2519dd3e4:	eor	w8, w8, w27
0x2519dd3e8:	and	x27, x8, #0xff
0x2519dd3ec:	strb	w8, [x21, #0xa]
0x2519dd3f0:	ldurb	w8, [x9, #-4]
0x2519dd3f4:	eor	w8, w8, w0
0x2519dd3f8:	and	x0, x8, #0xff
0x2519dd3fc:	strb	w8, [x21, #0xb]
0x2519dd400:	ldurb	w8, [x9, #-3]
0x2519dd404:	eor	w8, w8, w16
0x2519dd408:	and	x7, x8, #0xff
0x2519dd40c:	strb	w8, [x21, #0xc]
0x2519dd410:	ldurb	w8, [x9, #-2]
0x2519dd414:	eor	w8, w8, w16, lsr #8
0x2519dd418:	and	x13, x8, #0xff
0x2519dd41c:	strb	w8, [x21, #0xd]
0x2519dd420:	ldurb	w8, [x9, #-1]
0x2519dd424:	eor	w11, w8, w16, lsr #16
0x2519dd428:	and	x8, x11, #0xff
0x2519dd42c:	strb	w11, [x21, #0xe]
0x2519dd430:	ldrb	w11, [x9], #0x10
0x2519dd434:	eor	w11, w11, w16, lsr #24
0x2519dd438:	and	x16, x11, #0xff
0x2519dd43c:	strb	w11, [x21, #0xf]
0x2519dd440:	cmp	x23, #8
0x2519dd444:	cset	w11, eq
0x2519dd448:	mov	w17, #0x1b
0x2519dd44c:	mul	w11, w11, w17
0x2519dd450:	ldr	w17, [sp, #0xb0]
0x2519dd454:	eor	w11, w11, w17
0x2519dd458:	ldr	x11, [x26, w11, sxtw #3]
0x2519dd45c:	mov	x17, #0xe1a4
0x2519dd460:	braa	x11, x17
0x2519dd464:	add	w9, w9, #1
0x2519dd468:	mov	x13, x14
0x2519dd46c:	b	#0x251a2c528
0x2519dd470:	add	w10, w20, #0x1d2
0x2519dd474:	mov	w8, #0x56
0x2519dd478:	and	w8, w8, w27, lsl #1
0x2519dd47c:	mov	w9, #0x25
0x2519dd480:	eor	w9, w20, w9
0x2519dd484:	sub	w8, w27, w8
0x2519dd488:	str	w10, [sp, #0x38]
0x2519dd48c:	add	w8, w8, w10
0x2519dd490:	add	w8, w8, w9
0x2519dd494:	mov	w9, #0x2b
0x2519dd498:	eor	w8, w8, w9
0x2519dd49c:	ldr	x10, [sp, #0xc8]
0x2519dd4a0:	strb	w8, [x10]
0x2519dd4a4:	sub	x26, x29, #0x88
0x2519dd4a8:	mov	w8, #0x7040
0x2519dd4ac:	movk	w8, #0xbf4c, lsl #16
0x2519dd4b0:	orr	w8, w26, w8
0x2519dd4b4:	sub	w8, w8, w26
0x2519dd4b8:	mov	w9, #0x8fb8
0x2519dd4bc:	movk	w9, #0x40b3, lsl #16
0x2519dd4c0:	and	w9, w26, w9
0x2519dd4c4:	add	w8, w8, w9
0x2519dd4c8:	mov	w9, #0x459c
0x2519dd4cc:	movk	w9, #0xb3a8, lsl #16
0x2519dd4d0:	eor	w8, w8, w9
0x2519dd4d4:	mov	w9, #0x97f7
0x2519dd4d8:	movk	w9, #0xb9f0, lsl #16
0x2519dd4dc:	mul	w8, w8, w9
0x2519dd4e0:	stur	x10, [x29, #-0x70]
0x2519dd4e4:	ldr	x23, [sp, #0xd8]
0x2519dd4e8:	stur	x23, [x29, #-0x80]
0x2519dd4ec:	mov	w9, #0xb74b
0x2519dd4f0:	movk	w9, #0xdcb, lsl #16
0x2519dd4f4:	eor	w9, w8, w9
0x2519dd4f8:	stur	w9, [x29, #-0x88]
0x2519dd4fc:	add	w8, w8, w20
0x2519dd500:	add	w8, w8, #0xcf
0x2519dd504:	stur	w8, [x29, #-0x78]
0x2519dd508:	ldp	x25, x21, [sp, #0xb0]
0x2519dd50c:	ldr	w8, [x25]
0x2519dd510:	ldr	w9, [x21]
0x2519dd514:	sub	w8, w9, w8
0x2519dd518:	mov	x9, #0xb4fa
0x2519dd51c:	movk	x9, #0x6d3c, lsl #16
0x2519dd520:	movk	x9, #0x2a54, lsl #32
0x2519dd524:	movk	x9, #0x375b, lsl #48
0x2519dd528:	eor	w8, w8, w9
0x2519dd52c:	mul	w8, w8, w28
0x2519dd530:	ldr	x9, [sp, #0x98]
0x2519dd534:	add	x9, x9, w8, uxtb
0x2519dd538:	ldrb	w9, [x9]
0x2519dd53c:	mov	w10, #0x7d
0x2519dd540:	eor	w9, w9, w10
0x2519dd544:	ldr	x10, [sp, #0x88]
0x2519dd548:	ldrb	w9, [x10, w9, uxtw]
0x2519dd54c:	eor	w8, w8, w9
0x2519dd550:	and	w8, w8, #0xff
0x2519dd554:	add	w8, w8, #0x3dd
0x2519dd558:	ldr	x8, [x7, w8, uxtw #3]
0x2519dd55c:	sub	x0, x29, #0x88
0x2519dd560:	mov	x17, #0xbad3
0x2519dd564:	blraa	x8, x17
0x2519dd568:	ldr	x8, [sp, #0xd0]
0x2519dd56c:	add	x8, x8, x27, lsl #4
0x2519dd570:	mov	w9, #0x362d
0x2519dd574:	movk	w9, #0x60f0, lsl #16
0x2519dd578:	eor	w9, w26, w9
0x2519dd57c:	mov	x11, #0x7184
0x2519dd580:	movk	x11, #0xbfa6, lsl #16
0x2519dd584:	movk	x11, #0x5eb1, lsl #32
0x2519dd588:	movk	x11, #0xb0c6, lsl #48
0x2519dd58c:	and	w10, w9, w11
0x2519dd590:	add	w9, w9, w11
0x2519dd594:	sub	w9, w9, w10, lsl #1
0x2519dd598:	mov	w10, #0xabc0
0x2519dd59c:	movk	w10, #0x5274, lsl #16
0x2519dd5a0:	eor	w9, w9, w10
0x2519dd5a4:	mov	w10, #0x72f
0x2519dd5a8:	movk	w10, #0x132d, lsl #16
0x2519dd5ac:	madd	w9, w9, w10, w20
0x2519dd5b0:	sub	w9, w9, #0xdd
0x2519dd5b4:	stur	w9, [x29, #-0x78]
0x2519dd5b8:	stp	x8, x23, [x29, #-0x88]
0x2519dd5bc:	ldr	w8, [x25]
0x2519dd5c0:	ldr	w9, [x21]
0x2519dd5c4:	sub	w8, w9, w8
0x2519dd5c8:	mov	x9, #0xb4fa
0x2519dd5cc:	movk	x9, #0x6d3c, lsl #16
0x2519dd5d0:	movk	x9, #0x2a54, lsl #32
0x2519dd5d4:	movk	x9, #0x375b, lsl #48
0x2519dd5d8:	eor	w8, w8, w9
0x2519dd5dc:	mul	w8, w8, w28
0x2519dd5e0:	ldr	x9, [sp, #0xa8]
0x2519dd5e4:	add	x9, x9, w8, uxtb
0x2519dd5e8:	ldrb	w9, [x9]
0x2519dd5ec:	mov	w10, #0x6a
0x2519dd5f0:	eor	w9, w9, w10
0x2519dd5f4:	ldr	x10, [sp, #0xa0]
0x2519dd5f8:	ldrb	w9, [x10, w9, uxtw]
0x2519dd5fc:	eor	w8, w8, w9
0x2519dd600:	and	w8, w8, #0xff
0x2519dd604:	add	w8, w8, #0x36e
0x2519dd608:	ldr	x9, [sp, #0xe0]
0x2519dd60c:	ldr	x8, [x9, w8, uxtw #3]
0x2519dd610:	sub	x0, x29, #0x88
0x2519dd614:	mov	x17, #0xa98
0x2519dd618:	blraa	x8, x17
0x2519dd61c:	ldr	x7, [sp, #0xe0]
0x2519dd620:	add	x27, x27, #1
0x2519dd624:	cmp	x27, #9
0x2519dd628:	cset	w8, ne
0x2519dd62c:	lsl	w9, w8, #4
0x2519dd630:	orr	w8, w9, w8, lsl #5
0x2519dd634:	eor	w8, w20, w8
0x2519dd638:	ldr	x8, [x7, w8, uxtw #3]
0x2519dd63c:	mov	x17, #0x8a7
0x2519dd640:	braa	x8, x17
0x2519dd644:	ldr	x13, [sp, #0xe0]
0x2519dd648:	ldr	x9, [x27, w9, sxtw #3]
0x2519dd64c:	str	x9, [sp, #0x98]
0x2519dd650:	add	x9, sp, #0x220
0x2519dd654:	add	x11, x9, x13
0x2519dd658:	add	x10, x13, #0x140
0x2519dd65c:	str	x10, [sp, #0xe0]
0x2519dd660:	ldp	w16, w0, [x8, #0x48]
0x2519dd664:	ldp	w14, w10, [x8, #0x50]
0x2519dd668:	ldrb	w15, [x8, #0x60]
0x2519dd66c:	cmp	w15, #2
0x2519dd670:	b.eq	#0x2519dd7ac
0x2519dd674:	mov	w13, #0x7265
0x2519dd678:	movk	w13, #0x62b4, lsl #16
0x2519dd67c:	cmp	w15, #1
0x2519dd680:	b.eq	#0x2519dd694
0x2519dd684:	b	#0x251a1c86c
0x2519dd688:	mov	w6, #0xf99d
0x2519dd68c:	movk	w6, #0x85c9, lsl #16
0x2519dd690:	ldr	w7, [sp, #0xc4]
0x2519dd694:	add	w15, w6, w7
0x2519dd698:	add	w2, w15, #0x1a5
0x2519dd69c:	add	x15, x13, x20
0x2519dd6a0:	ldrb	w17, [x12, x15]
0x2519dd6a4:	eor	w17, w17, w19
0x2519dd6a8:	add	x1, x15, #1
0x2519dd6ac:	ldrb	w1, [x12, x1]
0x2519dd6b0:	eor	w1, w1, w19
0x2519dd6b4:	orr	w1, w17, w1, lsl #8
0x2519dd6b8:	add	x3, x15, x2
0x2519dd6bc:	sub	x3, x3, #0x1a4
0x2519dd6c0:	ldrb	w3, [x12, x3]
0x2519dd6c4:	eor	w3, w3, w19
0x2519dd6c8:	lsl	w3, w3, #0x10
0x2519dd6cc:	add	x15, x15, #3
0x2519dd6d0:	ldrb	w15, [x12, x15]
0x2519dd6d4:	eor	w15, w15, w19
0x2519dd6d8:	orr	w15, w3, w15, lsl #24
0x2519dd6dc:	orr	w15, w15, w1
0x2519dd6e0:	add	w1, w25, w15
0x2519dd6e4:	add	w3, w25, #6
0x2519dd6e8:	and	w15, w15, w3
0x2519dd6ec:	and	w17, w17, #6
0x2519dd6f0:	eor	w15, w15, w17
0x2519dd6f4:	sub	w15, w1, w15, lsl #1
0x2519dd6f8:	mov	w9, #0x19dc
0x2519dd6fc:	movk	w9, #0x61f5, lsl #16
0x2519dd700:	eor	w17, w13, w9
0x2519dd704:	mov	w9, #0x9447
0x2519dd708:	movk	w9, #0xfcbe, lsl #16
0x2519dd70c:	add	w17, w17, w9
0x2519dd710:	mov	w9, #0x2862
0x2519dd714:	movk	w9, #0xd675, lsl #16
0x2519dd718:	eor	w1, w13, w9
0x2519dd71c:	mov	w9, #0xa5f9
0x2519dd720:	movk	w9, #0x4b3e, lsl #16
0x2519dd724:	add	w1, w1, w9
0x2519dd728:	mov	w9, #0xbf20
0x2519dd72c:	movk	w9, #0x22cb, lsl #16
0x2519dd730:	eor	w3, w13, w9
0x2519dd734:	mov	w9, #0x32bb
0x2519dd738:	movk	w9, #0xbf80, lsl #16
0x2519dd73c:	add	w3, w3, w9
0x2519dd740:	mov	w9, #0xfcfa
0x2519dd744:	movk	w9, #0xf7ff, lsl #16
0x2519dd748:	eor	w4, w13, w9
0x2519dd74c:	mov	w9, #0x7162
0x2519dd750:	movk	w9, #0x6ab4, lsl #16
0x2519dd754:	add	w4, w4, w9
0x2519dd758:	eor	w17, w17, w13
0x2519dd75c:	eor	w1, w1, w3
0x2519dd760:	eor	w17, w17, w1
0x2519dd764:	eor	w17, w17, w4
0x2519dd768:	lsr	w17, w17, #2
0x2519dd76c:	mov	w9, #0x1c99
0x2519dd770:	movk	w9, #0x18ad, lsl #16
0x2519dd774:	eor	x17, x17, x9
0x2519dd778:	str	w15, [x11, x17, lsl #2]
0x2519dd77c:	add	x13, x13, #4
0x2519dd780:	add	x15, x13, x20
0x2519dd784:	cmp	x15, #0x40
0x2519dd788:	cset	w15, lo
0x2519dd78c:	mov	w9, #0x27f
0x2519dd790:	mul	w15, w15, w9
0x2519dd794:	eor	w15, w15, w2
0x2519dd798:	ldr	x15, [x27, w15, sxtw #3]
0x2519dd79c:	mov	w5, #0x7265
0x2519dd7a0:	movk	w5, #0x62b4, lsl #16
0x2519dd7a4:	mov	x17, #0x86cf
0x2519dd7a8:	braa	x15, x17
0x2519dd7ac:	add	w13, w6, w7
0x2519dd7b0:	add	w13, w13, #2
0x2519dd7b4:	mov	w9, #0x194
0x2519dd7b8:	orr	w15, w13, w9
0x2519dd7bc:	ldr	w13, [x8, #0x58]
0x2519dd7c0:	mov	w1, #0x7265
0x2519dd7c4:	movk	w1, #0x62b4, lsl #16
0x2519dd7c8:	mov	w9, #0xa8d8
0x2519dd7cc:	movk	w9, #0xe0a2, lsl #16
0x2519dd7d0:	add	x17, x1, x20
0x2519dd7d4:	ldrb	w2, [x12, x17]
0x2519dd7d8:	eor	w2, w2, w19
0x2519dd7dc:	lsl	w2, w2, #0x18
0x2519dd7e0:	add	x3, x17, #1
0x2519dd7e4:	ldrb	w3, [x12, x3]
0x2519dd7e8:	eor	w3, w3, w19
0x2519dd7ec:	orr	w2, w2, w3, lsl #16
0x2519dd7f0:	add	x3, x17, #2
0x2519dd7f4:	ldrb	w3, [x12, x3]
0x2519dd7f8:	eor	w3, w3, w19
0x2519dd7fc:	orr	w2, w2, w3, lsl #8
0x2519dd800:	add	x17, x17, #3
0x2519dd804:	ldrb	w17, [x12, x17]
0x2519dd808:	eor	w17, w17, w19
0x2519dd80c:	orr	w2, w2, w17
0x2519dd810:	add	w3, w25, #0xe
0x2519dd814:	and	w3, w2, w3
0x2519dd818:	and	w17, w17, #0xe
0x2519dd81c:	eor	w17, w3, w17
0x2519dd820:	add	w2, w2, w25
0x2519dd824:	sub	w17, w2, w17, lsl #1
0x2519dd828:	mov	w2, #0x6586
0x2519dd82c:	movk	w2, #0x5f02, lsl #16
0x2519dd830:	eor	w2, w1, w2
0x2519dd834:	mov	w3, #0x9b
0x2519dd838:	and	w3, w1, w3
0x2519dd83c:	lsl	w4, w3, #1
0x2519dd840:	mov	w22, #0xa800
0x2519dd844:	movk	w22, #0x4000, lsl #16
0x2519dd848:	orr	w5, w4, w22
0x2519dd84c:	and	w5, w5, w2
0x2519dd850:	and	w4, w4, #0x1c
0x2519dd854:	eor	w3, w4, w3
0x2519dd858:	eor	w3, w3, w5
0x2519dd85c:	lsl	w4, w2, #1
0x2519dd860:	mov	w5, #0x783a
0x2519dd864:	movk	w5, #0xc493, lsl #16
0x2519dd868:	eor	w5, w4, w5
0x2519dd86c:	and	w2, w5, w2
0x2519dd870:	mov	w30, #5
0x2519dd874:	movk	w30, #0x248, lsl #16
0x2519dd878:	add	w5, w30, #0x17
0x2519dd87c:	and	w4, w4, w5
0x2519dd880:	eor	w4, w4, w30
0x2519dd884:	eor	w2, w4, w2
0x2519dd888:	lsl	w4, w3, #2
0x2519dd88c:	eor	w5, w4, w22
0x2519dd890:	and	w5, w5, w2
0x2519dd894:	mov	w22, #0xe81c
0x2519dd898:	movk	w22, #0xc249, lsl #16
0x2519dd89c:	and	w4, w4, w22
0x2519dd8a0:	eor	w3, w4, w3
0x2519dd8a4:	eor	w3, w3, w5
0x2519dd8a8:	lsl	w4, w2, #2
0x2519dd8ac:	mov	w5, #0x874
0x2519dd8b0:	movk	w5, #0x4927, lsl #16
0x2519dd8b4:	eor	w5, w4, w5
0x2519dd8b8:	and	w2, w5, w2
0x2519dd8bc:	and	w4, w4, w22
0x2519dd8c0:	eor	w2, w2, w4
0x2519dd8c4:	mov	w4, #0x4809
0x2519dd8c8:	movk	w4, #0xc248, lsl #16
0x2519dd8cc:	eor	w4, w2, w4
0x2519dd8d0:	mov	w5, #0xa019
0x2519dd8d4:	movk	w5, #1, lsl #16
0x2519dd8d8:	eor	w2, w2, w5
0x2519dd8dc:	and	w2, w2, w3, lsl #4
0x2519dd8e0:	eor	w2, w2, w3
0x2519dd8e4:	lsl	w3, w4, #4
0x2519dd8e8:	mov	w5, #0x81d0
0x2519dd8ec:	movk	w5, #0x249e, lsl #16
0x2519dd8f0:	eor	w5, w3, w5
0x2519dd8f4:	and	w4, w5, w4
0x2519dd8f8:	sub	w5, w22, #0xc
0x2519dd8fc:	and	w3, w3, w5
0x2519dd900:	eor	w3, w4, w3
0x2519dd904:	mov	w4, #0x680d
0x2519dd908:	movk	w4, #0xc241, lsl #16
0x2519dd90c:	eor	w4, w3, w4
0x2519dd910:	mov	w5, #0x800d
0x2519dd914:	movk	w5, #8, lsl #16
0x2519dd918:	eor	w3, w3, w5
0x2519dd91c:	and	w3, w3, w2, lsl #8
0x2519dd920:	add	w5, w22, #1
0x2519dd924:	eor	w2, w2, w5
0x2519dd928:	eor	w2, w2, w3
0x2519dd92c:	lsl	w3, w4, #8
0x2519dd930:	mov	w5, #0x49e80000
0x2519dd934:	eor	w5, w3, w5
0x2519dd938:	and	w4, w5, w4
0x2519dd93c:	mov	w22, #0x42490000
0x2519dd940:	and	w3, w3, w22
0x2519dd944:	mov	w5, #0x2010000
0x2519dd948:	eor	w3, w3, w5
0x2519dd94c:	eor	w3, w3, w4
0x2519dd950:	lsl	w4, w2, #0x10
0x2519dd954:	mov	w5, #0x681d0000
0x2519dd958:	eor	w5, w4, w5
0x2519dd95c:	and	w3, w5, w3
0x2519dd960:	and	w4, w4, w22
0x2519dd964:	eor	w2, w4, w2
0x2519dd968:	eor	w2, w2, w3
0x2519dd96c:	eor	w2, w1, w2, lsl #1
0x2519dd970:	mov	w3, #0x9768
0x2519dd974:	movk	w3, #0x2672, lsl #16
0x2519dd978:	eor	w2, w3, w2, lsr #2
0x2519dd97c:	str	w17, [x11, w2, uxtw #2]
0x2519dd980:	add	x1, x1, #4
0x2519dd984:	add	x17, x1, x20
0x2519dd988:	cmp	x17, #0x40
0x2519dd98c:	cset	w17, lo
0x2519dd990:	orr	w17, w17, w17, lsl #3
0x2519dd994:	eor	w17, w17, w15
0x2519dd998:	ldr	x2, [x27, w17, sxtw #3]
0x2519dd99c:	add	x3, x24, #0x10
0x2519dd9a0:	mov	w22, #0x248a
0x2519dd9a4:	movk	w22, #0xbbba, lsl #16
0x2519dd9a8:	mov	x17, #0x6ccd
0x2519dd9ac:	braa	x2, x17
0x2519dd9b0:	str	xzr, [sp, #0x98]
0x2519dd9b4:	ldr	x13, [sp, #0x30]
0x2519dd9b8:	mov	x17, #0x672c
0x2519dd9bc:	braa	x13, x17
0x2519dd9c0:	mov	x6, x0
0x2519dd9c4:	mov	x3, x28
0x2519dd9c8:	mov	x5, x2
0x2519dd9cc:	mov	w13, #0x7a08
0x2519dd9d0:	movk	w13, #0x49d, lsl #16
0x2519dd9d4:	eor	w13, w28, w13
0x2519dd9d8:	mov	w17, #-0x68000000
0x2519dd9dc:	eor	w17, w28, w17
0x2519dd9e0:	extr	w17, w13, w17, #0x1b
0x2519dd9e4:	add	w13, w12, #0x61
0x2519dd9e8:	mov	w15, #0x1f8d
0x2519dd9ec:	movk	w15, #0xb0aa, lsl #16
0x2519dd9f0:	eor	w0, w30, w15
0x2519dd9f4:	eor	w1, w6, w25
0x2519dd9f8:	and	w0, w0, w1
0x2519dd9fc:	mov	w15, #0x638c
0x2519dda00:	movk	w15, #0x2c37, lsl #16
0x2519dda04:	add	w1, w12, w15
0x2519dda08:	and	w1, w6, w1
0x2519dda0c:	mov	w15, #0x717a
0x2519dda10:	movk	w15, #0xa527, lsl #16
0x2519dda14:	eor	w2, w2, w15
0x2519dda18:	mov	w4, #0x85f7
0x2519dda1c:	movk	w4, #0x6362, lsl #16
0x2519dda20:	eor	w4, w30, w4
0x2519dda24:	and	w2, w4, w2
0x2519dda28:	mov	w15, #0xb72
0x2519dda2c:	movk	w15, #0x39ba, lsl #16
0x2519dda30:	and	w4, w30, w15
0x2519dda34:	eor	w2, w2, w4
0x2519dda38:	eor	w0, w1, w0
0x2519dda3c:	mov	w15, #0x6a33
0x2519dda40:	movk	w15, #0xd160, lsl #16
0x2519dda44:	eor	w0, w0, w15
0x2519dda48:	mov	w15, #0xfe8d
0x2519dda4c:	movk	w15, #0xdedd, lsl #16
0x2519dda50:	eor	w1, w2, w15
0x2519dda54:	and	w0, w1, w0
0x2519dda58:	mov	w15, #0xf5cc
0x2519dda5c:	movk	w15, #0x228a, lsl #16
0x2519dda60:	and	w1, w2, w15
0x2519dda64:	mov	w15, #0xb73
0x2519dda68:	movk	w15, #0xfd77, lsl #16
0x2519dda6c:	eor	w1, w1, w15
0x2519dda70:	eor	w0, w1, w0
0x2519dda74:	mov	w15, #0xcf61
0x2519dda78:	movk	w15, #0xf956, lsl #16
0x2519dda7c:	eor	w1, w11, w15
0x2519dda80:	mov	w15, #0x309f
0x2519dda84:	movk	w15, #0x6a9, lsl #16
0x2519dda88:	add	w1, w1, w15
0x2519dda8c:	mov	w15, #0x80ea
0x2519dda90:	movk	w15, #0xc28d, lsl #16
0x2519dda94:	eor	w2, w11, w15
0x2519dda98:	mov	w15, #0x7f16
0x2519dda9c:	movk	w15, #0x3d72, lsl #16
0x2519ddaa0:	add	w2, w2, w15
0x2519ddaa4:	eor	w1, w1, w2
0x2519ddaa8:	mov	w15, #0x3583
0x2519ddaac:	movk	w15, #0xa746, lsl #16
0x2519ddab0:	eor	w11, w11, w15
0x2519ddab4:	mov	w15, #0xca7d
0x2519ddab8:	movk	w15, #0x58b9, lsl #16
0x2519ddabc:	add	w11, w11, w15
0x2519ddac0:	eor	w11, w1, w11
0x2519ddac4:	add	x1, x14, x27
0x2519ddac8:	ldr	w1, [x8, x1, lsl #2]
0x2519ddacc:	mov	w15, #0xfdb6
0x2519ddad0:	movk	w15, #0x5b5, lsl #16
0x2519ddad4:	eor	w2, w1, w15
0x2519ddad8:	mov	w15, #0x24a
0x2519ddadc:	movk	w15, #0xfa4a, lsl #16
0x2519ddae0:	add	w2, w2, w15
0x2519ddae4:	mov	w15, #0x7f6c
0x2519ddae8:	movk	w15, #0x98b2, lsl #16
0x2519ddaec:	eor	w4, w1, w15
0x2519ddaf0:	mov	w15, #0x8094
0x2519ddaf4:	movk	w15, #0x674d, lsl #16
0x2519ddaf8:	add	w4, w4, w15
0x2519ddafc:	eor	w2, w2, w4
0x2519ddb00:	mov	w15, #0x5bea
0x2519ddb04:	movk	w15, #0xab45, lsl #16
0x2519ddb08:	eor	w1, w1, w15
0x2519ddb0c:	mov	w15, #0xa416
0x2519ddb10:	movk	w15, #0x54ba, lsl #16
0x2519ddb14:	add	w1, w1, w15
0x2519ddb18:	eor	w1, w2, w1
0x2519ddb1c:	add	w11, w17, w11
0x2519ddb20:	add	w11, w11, w0
0x2519ddb24:	mov	w15, #0x1ad0
0x2519ddb28:	movk	w15, #0xe7c7, lsl #16
0x2519ddb2c:	add	w11, w11, w15
0x2519ddb30:	add	w11, w11, w1
0x2519ddb34:	mov	w15, #0xdc07
0x2519ddb38:	movk	w15, #0xf1c7, lsl #16
0x2519ddb3c:	eor	w17, w11, w15
0x2519ddb40:	mov	w15, #0x6e08
0x2519ddb44:	movk	w15, #0xb45c, lsl #16
0x2519ddb48:	add	w17, w17, w15
0x2519ddb4c:	mov	w15, #0x8ca5
0x2519ddb50:	movk	w15, #0xf624, lsl #16
0x2519ddb54:	eor	w0, w11, w15
0x2519ddb58:	mov	w15, #0x3ea6
0x2519ddb5c:	movk	w15, #0xb3bf, lsl #16
0x2519ddb60:	add	w0, w0, w15
0x2519ddb64:	mov	w15, #0xe320
0x2519ddb68:	movk	w15, #0xc278, lsl #16
0x2519ddb6c:	eor	w1, w11, w15
0x2519ddb70:	mov	w15, #0x5121
0x2519ddb74:	movk	w15, #0x87e3, lsl #16
0x2519ddb78:	add	w1, w1, w15
0x2519ddb7c:	mov	w15, #0xfe7d
0x2519ddb80:	movk	w15, #0x7fff, lsl #16
0x2519ddb84:	eor	w2, w11, w15
0x2519ddb88:	mov	w15, #0x4c7e
0x2519ddb8c:	movk	w15, #0x3a64, lsl #16
0x2519ddb90:	add	w2, w2, w15
0x2519ddb94:	eor	w11, w11, w17
0x2519ddb98:	eor	w17, w0, w1
0x2519ddb9c:	eor	w11, w11, w17
0x2519ddba0:	mov	w15, #0x37f7
0x2519ddba4:	movk	w15, #0x26f9, lsl #16
0x2519ddba8:	eor	w17, w2, w15
0x2519ddbac:	eor	w28, w11, w17
0x2519ddbb0:	eor	w0, w16, w30, ror #2
0x2519ddbb4:	add	x14, x14, #1
0x2519ddbb8:	add	x4, x19, #0x14
0x2519ddbbc:	cmp	x14, x4
0x2519ddbc0:	cset	w11, eq
0x2519ddbc4:	mov	w15, #0x39b
0x2519ddbc8:	mul	w11, w11, w15
0x2519ddbcc:	eor	w11, w11, w12
0x2519ddbd0:	ldr	x1, [x26, w11, sxtw #3]
0x2519ddbd4:	mov	x2, x6
0x2519ddbd8:	mov	x11, x5
0x2519ddbdc:	mov	x30, x3
0x2519ddbe0:	mov	x17, #0xda44
0x2519ddbe4:	braa	x1, x17
0x2519ddbe8:	b	#0x251a1e938
0x2519ddbec:	mov	w8, #0x339
0x2519ddbf0:	eor	w26, w20, w8
0x2519ddbf4:	b	#0x251a0439c
0x2519ddbf8:	add	x8, x8, #4
0x2519ddbfc:	b	#0x251a1e740
0x2519ddc00:	add	x8, sp, #0x98
0x2519ddc04:	mov	w9, #0xc4e0
0x2519ddc08:	movk	w9, #0xc9e9, lsl #16
0x2519ddc0c:	add	w9, w1, w9
0x2519ddc10:	and	w9, w9, w4
0x2519ddc14:	add	x11, x3, #0x48
0x2519ddc18:	ldr	w11, [x11, w10, uxtw]
0x2519ddc1c:	eor	w12, w10, w5
0x2519ddc20:	and	w13, w6, w10, lsl #1
0x2519ddc24:	mov	w14, #0x24
0x2519ddc28:	eor	w14, w9, w14
0x2519ddc2c:	lsr	w14, w11, w14
0x2519ddc30:	mov	w15, #-0x64
0x2519ddc34:	eor	w15, w14, w15
0x2519ddc38:	and	w16, w15, #0xfffffff7
0x2519ddc3c:	and	w14, w14, #2
0x2519ddc40:	eor	w14, w16, w14
0x2519ddc44:	sub	w14, w15, w14, lsl #1
0x2519ddc48:	add	w14, w14, #0x75
0x2519ddc4c:	mov	w15, #0x1082
0x2519ddc50:	movk	w15, #0xa814, lsl #16
0x2519ddc54:	add	w12, w12, w15
0x2519ddc58:	add	w12, w13, w12
0x2519ddc5c:	strb	w14, [x2, w12, uxtw]
0x2519ddc60:	lsr	w13, w11, #0x10
0x2519ddc64:	mov	w14, #-0x63
0x2519ddc68:	eor	w14, w13, w14
0x2519ddc6c:	and	w15, w14, #0xfffffff7
0x2519ddc70:	and	w13, w13, #2
0x2519ddc74:	eor	w13, w15, w13
0x2519ddc78:	sub	w13, w14, w13, lsl #1
0x2519ddc7c:	add	w13, w13, #0x75
0x2519ddc80:	add	w14, w12, #1
0x2519ddc84:	strb	w13, [x2, w14, uxtw]
0x2519ddc88:	mov	w13, #0x7a
0x2519ddc8c:	eor	w13, w13, w11, lsr #8
0x2519ddc90:	mov	w14, #0xea
0x2519ddc94:	and	w14, w14, w13, lsl #1
0x2519ddc98:	sub	w13, w13, w14
0x2519ddc9c:	add	w13, w13, #0x75
0x2519ddca0:	add	w14, w12, #2
0x2519ddca4:	strb	w13, [x2, w14, uxtw]
0x2519ddca8:	mov	w14, #0x86
0x2519ddcac:	mov	w13, #0x7d
0x2519ddcb0:	eor	w11, w11, w13
0x2519ddcb4:	add	w12, w12, #3
0x2519ddcb8:	strb	w11, [x2, w12, uxtw]
0x2519ddcbc:	add	w10, w10, #4
0x2519ddcc0:	ldr	w11, [x3, #0x5c]
0x2519ddcc4:	cmp	w10, w11
0x2519ddcc8:	cset	w11, lo
0x2519ddccc:	mov	w12, #0x3dd
0x2519ddcd0:	mul	w11, w11, w12
0x2519ddcd4:	eor	w11, w11, w1
0x2519ddcd8:	ldr	x11, [x19, w11, sxtw #3]
0x2519ddcdc:	mov	w12, #0x5c
0x2519ddce0:	mov	x17, #0x6ccd
0x2519ddce4:	braa	x11, x17
0x2519ddce8:	mov	w0, #-0xa427
0x2519ddcec:	ldp	x29, x30, [sp, #0x10]
0x2519ddcf0:	add	sp, sp, #0x20
0x2519ddcf4:	retab	
0x2519ddcf8:	mov	w8, #1
0x2519ddcfc:	mov	w13, #0x248a
0x2519ddd00:	movk	w13, #0x92c7, lsl #16
0x2519ddd04:	add	w9, w27, w13
0x2519ddd08:	mov	w10, #-2
0x2519ddd0c:	sub	w10, w10, w25
0x2519ddd10:	eor	w10, w10, w9
0x2519ddd14:	sub	w11, w9, w20
0x2519ddd18:	and	w10, w11, w10
0x2519ddd1c:	bic	w9, w20, w9
0x2519ddd20:	orr	w9, w10, w9
0x2519ddd24:	mvn	w9, w9
0x2519ddd28:	lsr	w9, w9, #0x1f
0x2519ddd2c:	mov	x25, x20
0x2519ddd30:	mov	w10, #0xc9a0
0x2519ddd34:	movk	w10, #0xc28, lsl #16
0x2519ddd38:	add	w10, w8, w10
0x2519ddd3c:	mov	w11, #0x1444
0x2519ddd40:	movk	w11, #0x6110, lsl #16
0x2519ddd44:	orr	w23, w10, w11
0x2519ddd48:	eor	w10, w22, w23
0x2519ddd4c:	eor	w9, w9, w10
0x2519ddd50:	add	w10, w8, w19
0x2519ddd54:	adds	w19, w10, w9
0x2519ddd58:	cset	w9, eq
0x2519ddd5c:	add	w10, w8, #0xef
0x2519ddd60:	mov	w11, #0x27b
0x2519ddd64:	mul	w9, w9, w11
0x2519ddd68:	eor	w9, w9, w10
0x2519ddd6c:	ldr	x9, [x28, w9, sxtw #3]
0x2519ddd70:	mov	x17, #0x1007
0x2519ddd74:	braa	x9, x17
0x2519ddd78:	mov	w8, #0x550
0x2519ddd7c:	movk	w8, #0x3230, lsl #16
0x2519ddd80:	add	w8, w10, w8
0x2519ddd84:	mov	w12, #0x60
0x2519ddd88:	movk	w12, #0x4806, lsl #16
0x2519ddd8c:	orr	w8, w8, w12
0x2519ddd90:	add	x12, x30, #0x48
0x2519ddd94:	ldr	w12, [x12, w9, uxtw]
0x2519ddd98:	mov	w13, #0xefe9
0x2519ddd9c:	movk	w13, #0xfd7e, lsl #16
0x2519ddda0:	eor	w13, w9, w13
0x2519ddda4:	mov	w14, #0xdfd0
0x2519ddda8:	movk	w14, #0xfafd, lsl #16
0x2519dddac:	and	w14, w14, w9, lsl #1
0x2519dddb0:	lsr	w15, w12, #0x18
0x2519dddb4:	eor	w16, w8, w15
0x2519dddb8:	eor	w16, w16, #0xfffffff8
0x2519dddbc:	and	w17, w16, #0xfffffff7
0x2519dddc0:	and	w15, w15, #2
0x2519dddc4:	eor	w15, w17, w15
0x2519dddc8:	sub	w15, w16, w15, lsl #1
0x2519dddcc:	add	w15, w15, #0x75
0x2519dddd0:	add	w13, w13, w1
0x2519dddd4:	add	w13, w14, w13
0x2519dddd8:	strb	w15, [x22, w13, uxtw]
0x2519ddddc:	lsr	w14, w12, #0x10
0x2519ddde0:	eor	w15, w14, w2
0x2519ddde4:	and	w16, w15, #0xfffffff7
0x2519ddde8:	and	w14, w14, #2
0x2519dddec:	eor	w14, w16, w14
0x2519dddf0:	sub	w14, w15, w14, lsl #1
0x2519dddf4:	add	w14, w14, #0x75
0x2519dddf8:	add	w15, w13, #1
0x2519dddfc:	strb	w14, [x22, w15, uxtw]
0x2519dde00:	eor	w14, w3, w12, lsr #8
0x2519dde04:	and	w15, w4, w14, lsl #1
0x2519dde08:	sub	w14, w14, w15
0x2519dde0c:	add	w14, w14, #0x75
0x2519dde10:	add	w15, w13, #2
0x2519dde14:	strb	w14, [x22, w15, uxtw]
0x2519dde18:	eor	w12, w12, w5
0x2519dde1c:	add	w13, w13, #3
0x2519dde20:	strb	w12, [x22, w13, uxtw]
0x2519dde24:	add	w9, w9, #4
0x2519dde28:	cmp	w9, w11
0x2519dde2c:	cset	w12, lo
0x2519dde30:	mov	w13, #0x160
0x2519dde34:	mul	w12, w12, w13
0x2519dde38:	eor	w12, w12, w10
0x2519dde3c:	ldr	x12, [x27, w12, sxtw #3]
0x2519dde40:	mov	x17, #0xc3f2
0x2519dde44:	braa	x12, x17
0x2519dde48:	cmp	x1, x12
0x2519dde4c:	cset	w17, lo
0x2519dde50:	strb	w4, [x10, x2]
0x2519dde54:	add	x2, x2, #1
0x2519dde58:	add	x0, x2, x12
0x2519dde5c:	cmp	x2, x5
0x2519dde60:	cset	w21, hi
0x2519dde64:	eor	w21, w17, w21
0x2519dde68:	cmp	x0, x1
0x2519dde6c:	cset	w0, lo
0x2519dde70:	cmp	w21, #0
0x2519dde74:	csel	w17, w17, w0, ne
0x2519dde78:	eor	w0, w14, w6
0x2519dde7c:	mul	w17, w17, w0
0x2519dde80:	eor	w17, w17, w3
0x2519dde84:	ldr	x0, [x28, w17, sxtw #3]
0x2519dde88:	mov	x17, #0x9b30
0x2519dde8c:	braa	x0, x17
0x2519dde90:	b	#0x2519f0b64
0x2519dde94:	eor	w8, w13, w4
0x2519dde98:	mov	w9, #0x3d6
0x2519dde9c:	eor	w10, w11, w9
0x2519ddea0:	subs	x8, x8, #1
0x2519ddea4:	ldrb	w13, [x0, x8]
0x2519ddea8:	add	x9, sp, #0x260
0x2519ddeac:	add	x14, x9, x8
0x2519ddeb0:	strb	w13, [x14]
0x2519ddeb4:	cset	w14, eq
0x2519ddeb8:	add	w13, w10, #0x13a
0x2519ddebc:	mul	w14, w14, w13
0x2519ddec0:	eor	w14, w14, w11
0x2519ddec4:	ldr	x14, [x26, w14, sxtw #3]
0x2519ddec8:	mov	x17, #0x2db9
0x2519ddecc:	braa	x14, x17
0x2519dded0:	mov	w11, #0
0x2519dded4:	sub	w10, w9, #0x30
0x2519dded8:	orr	w12, w10, #0x20
0x2519ddedc:	mov	w10, #0x6930
0x2519ddee0:	movk	w10, #0x2dc3, lsl #16
0x2519ddee4:	add	w10, w22, w10
0x2519ddee8:	cmp	w22, w2
0x2519ddeec:	cset	w13, eq
0x2519ddef0:	sub	w12, w12, #0x109
0x2519ddef4:	mul	w12, w12, w13
0x2519ddef8:	eor	w12, w12, w9
0x2519ddefc:	ldr	x12, [x26, w12, sxtw #3]
0x2519ddf00:	mov	x17, #0x61bd
0x2519ddf04:	braa	x12, x17
0x2519ddf08:	mov	x4, x10
0x2519ddf0c:	mov	x10, x14
0x2519ddf10:	mov	x15, x16
0x2519ddf14:	mov	w13, #0x7a08
0x2519ddf18:	movk	w13, #0x49d, lsl #16
0x2519ddf1c:	eor	w13, w16, w13
0x2519ddf20:	mov	w14, #-0x68000000
0x2519ddf24:	eor	w14, w16, w14
0x2519ddf28:	extr	w13, w13, w14, #0x1b
0x2519ddf2c:	eor	w14, w10, w21
0x2519ddf30:	eor	w16, w4, w1
0x2519ddf34:	eor	w14, w14, w16
0x2519ddf38:	eor	w16, w3, w21
0x2519ddf3c:	add	x17, x5, x20
0x2519ddf40:	ldr	w17, [x11, x17, lsl #2]
0x2519ddf44:	eor	w17, w17, w25
0x2519ddf48:	add	w13, w16, w13
0x2519ddf4c:	add	w13, w13, w14
0x2519ddf50:	mov	w14, #0xbe71
0x2519ddf54:	movk	w14, #0xeb19, lsl #16
0x2519ddf58:	add	w13, w13, w14
0x2519ddf5c:	add	w13, w13, w17
0x2519ddf60:	mov	w14, #0xe655
0x2519ddf64:	movk	w14, #0x13c3, lsl #16
0x2519ddf68:	eor	w14, w13, w14
0x2519ddf6c:	mov	w16, #0xcb7b
0x2519ddf70:	movk	w16, #0x9003, lsl #16
0x2519ddf74:	add	w14, w14, w16
0x2519ddf78:	mov	w16, #0x2af2
0x2519ddf7c:	movk	w16, #0x77b2, lsl #16
0x2519ddf80:	eor	w16, w13, w16
0x2519ddf84:	mov	w17, #0x7de
0x2519ddf88:	movk	w17, #0xf472, lsl #16
0x2519ddf8c:	add	w16, w16, w17
0x2519ddf90:	mov	w17, #0xc198
0x2519ddf94:	movk	w17, #0x66b1, lsl #16
0x2519ddf98:	eor	w17, w13, w17
0x2519ddf9c:	mov	w0, #0xecb8
0x2519ddfa0:	movk	w0, #0xe571, lsl #16
0x2519ddfa4:	add	w17, w17, w0
0x2519ddfa8:	mov	w0, #0xd59a
0x2519ddfac:	movk	w0, #0x7eff, lsl #16
0x2519ddfb0:	add	w0, w0, #0xa55
0x2519ddfb4:	eor	w0, w13, w0
0x2519ddfb8:	mov	w2, #0xf2c1
0x2519ddfbc:	movk	w2, #0xfd3f, lsl #16
0x2519ddfc0:	add	w0, w0, w2
0x2519ddfc4:	eor	w13, w13, w9
0x2519ddfc8:	eor	w13, w13, w14
0x2519ddfcc:	eor	w14, w16, w17
0x2519ddfd0:	eor	w13, w13, w14
0x2519ddfd4:	eor	w16, w13, w0
0x2519ddfd8:	eor	w14, w22, w1, ror #2
0x2519ddfdc:	add	x5, x5, #1
0x2519ddfe0:	add	x2, x24, #0x28
0x2519ddfe4:	cmp	x5, x2
0x2519ddfe8:	cset	w13, ne
0x2519ddfec:	mov	w17, #0x1d
0x2519ddff0:	mul	w13, w13, w17
0x2519ddff4:	eor	w13, w13, w12
0x2519ddff8:	ldr	x13, [x27, w13, sxtw #3]
0x2519ddffc:	mov	x3, x4
0x2519de000:	mov	x1, x15
0x2519de004:	mov	x17, #0xc042
0x2519de008:	braa	x13, x17
0x2519de00c:	mov	w9, #0x9000
0x2519de010:	str	w9, [x8]
0x2519de014:	mov	w8, #0x14f8
0x2519de018:	movk	w8, #0x1455, lsl #16
0x2519de01c:	str	w8, [x0, #0x20]
0x2519de020:	ldp	x20, x19, [sp, #0x10]
0x2519de024:	add	sp, sp, #0x20
0x2519de028:	ret	
0x2519de02c:	mov	w15, #0xa314
0x2519de030:	movk	w15, #0xff0e, lsl #16
0x2519de034:	add	w15, w0, w15
0x2519de038:	mov	w17, #0x5e37
0x2519de03c:	movk	w17, #0xf1, lsl #16
0x2519de040:	and	w17, w15, w17
0x2519de044:	ldrb	w15, [x10, w1, uxtw]
0x2519de048:	mov	w0, #0x9b
0x2519de04c:	eor	w14, w0, w14, lsl #4
0x2519de050:	add	w0, w17, #0x56
0x2519de054:	eor	w0, w0, w15
0x2519de058:	and	w14, w0, w14
0x2519de05c:	and	w15, w15, #0x3c
0x2519de060:	mov	w0, #0x8a
0x2519de064:	orr	w15, w15, w0
0x2519de068:	eor	w14, w14, w15
0x2519de06c:	strb	w14, [x10, w1, uxtw]
0x2519de070:	mov	w14, #0
0x2519de074:	add	w23, w17, #0x22
0x2519de078:	eor	w15, w23, w13
0x2519de07c:	adds	w11, w15, w11
0x2519de080:	cset	w15, eq
0x2519de084:	lsl	w0, w15, #1
0x2519de088:	orr	w15, w0, w15, lsl #3
0x2519de08c:	eor	w15, w15, w17
0x2519de090:	ldr	x15, [x28, w15, sxtw #3]
0x2519de094:	mov	w24, #1
0x2519de098:	mov	x17, #0xf7f6
0x2519de09c:	braa	x15, x17
0x2519de0a0:	ldr	w12, [sp, #0xe8]
0x2519de0a4:	sub	w8, w12, #0x176
0x2519de0a8:	ldr	w9, [x28, #0x9bc]
0x2519de0ac:	sub	w10, w21, w8
0x2519de0b0:	mvn	x11, x8
0x2519de0b4:	add	x11, x11, x25
0x2519de0b8:	eor	x10, x11, x10
0x2519de0bc:	sub	x11, x8, x25
0x2519de0c0:	sub	x10, x10, #1
0x2519de0c4:	and	x10, x10, x11
0x2519de0c8:	lsr	x10, x10, #0x3f
0x2519de0cc:	eor	w10, w10, #1
0x2519de0d0:	add	w9, w10, w9
0x2519de0d4:	str	w9, [x28]
0x2519de0d8:	mov	w9, #0x26e
0x2519de0dc:	eor	w8, w8, w9
0x2519de0e0:	mov	w21, #1
0x2519de0e4:	b	#0x2519efe3c

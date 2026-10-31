; AirPlaySender 0x2519fa054-0x2519fa410; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519fa054:	pacibsp	
0x2519fa058:	sub	sp, sp, #0x90
0x2519fa05c:	stp	x28, x27, [sp, #0x30]
0x2519fa060:	stp	x26, x25, [sp, #0x40]
0x2519fa064:	stp	x24, x23, [sp, #0x50]
0x2519fa068:	stp	x22, x21, [sp, #0x60]
0x2519fa06c:	stp	x20, x19, [sp, #0x70]
0x2519fa070:	stp	x29, x30, [sp, #0x80]
0x2519fa074:	add	x29, sp, #0x80
0x2519fa078:	mov	x19, x0
0x2519fa07c:	adrp	x8, #0x2681b4000
0x2519fa080:	ldr	x8, [x8, #0xee0]
0x2519fa084:	ldr	x8, [x8]
0x2519fa088:	str	x8, [sp, #0x28]
0x2519fa08c:	mov	x20, #0xb4fa
0x2519fa090:	movk	x20, #0x6d3c, lsl #16
0x2519fa094:	movk	x20, #0x2a54, lsl #32
0x2519fa098:	movk	x20, #0x375b, lsl #48
0x2519fa09c:	mov	w21, #0x1f79
0x2519fa0a0:	movk	w21, #0xd3ef, lsl #16
0x2519fa0a4:	adrp	x8, #0x26e7f1000
0x2519fa0a8:	ldr	w10, [x8, #0x6d8]
0x2519fa0ac:	adrp	x9, #0x26e7db000
0x2519fa0b0:	ldr	w11, [x9, #0x410]
0x2519fa0b4:	add	w10, w11, w10
0x2519fa0b8:	eor	w10, w10, w20
0x2519fa0bc:	mul	w10, w10, w21
0x2519fa0c0:	adrp	x12, #0x251c6f000
0x2519fa0c4:	add	x12, x12, #0xb60
0x2519fa0c8:	add	x12, x12, w10, uxtb
0x2519fa0cc:	ldrb	w12, [x12]
0x2519fa0d0:	mov	w13, #0x4a
0x2519fa0d4:	eor	w12, w12, w13
0x2519fa0d8:	adrp	x13, #0x251c71000
0x2519fa0dc:	add	x13, x13, #0x70
0x2519fa0e0:	ldrb	w12, [x13, w12, uxtw]
0x2519fa0e4:	eor	w10, w10, w12
0x2519fa0e8:	and	w12, w10, #0xff
0x2519fa0ec:	adrp	x10, #0x27612b000
0x2519fa0f0:	add	x10, x10, #0x8f0
0x2519fa0f4:	add	w12, w12, #0x11
0x2519fa0f8:	ldr	x22, [x10, w12, uxtw #3]
0x2519fa0fc:	ldr	x12, [x22, #-4]!
0x2519fa100:	add	w11, w11, w12
0x2519fa104:	eor	w11, w11, w20
0x2519fa108:	mul	w11, w11, w21
0x2519fa10c:	ldr	x13, [x10, #0x5c0]
0x2519fa110:	sub	x23, x13, #0xc
0x2519fa114:	add	x13, x23, w11, uxtb
0x2519fa118:	ldrb	w13, [x13]
0x2519fa11c:	eor	w13, w13, #0xfe
0x2519fa120:	ldr	x14, [x10, #0x408]
0x2519fa124:	sub	x24, x14, #4
0x2519fa128:	ldrb	w13, [x24, w13, uxtw]
0x2519fa12c:	eor	w11, w13, w11
0x2519fa130:	and	w11, w11, #0xff
0x2519fa134:	sub	w11, w11, #0x26
0x2519fa138:	ldr	x25, [x10, w11, sxtw #3]
0x2519fa13c:	ldr	x11, [x25]
0x2519fa140:	add	x13, sp, #8
0x2519fa144:	add	x12, x12, x13
0x2519fa148:	add	x11, x12, x11
0x2519fa14c:	neg	x12, x20
0x2519fa150:	madd	x12, x11, x21, x12
0x2519fa154:	eor	x11, x11, x20
0x2519fa158:	mul	x11, x11, x21
0x2519fa15c:	str	x12, [x22]
0x2519fa160:	str	x11, [x25]
0x2519fa164:	add	x11, sp, #0x10
0x2519fa168:	mov	w12, #0x409d
0x2519fa16c:	movk	w12, #0xb902, lsl #16
0x2519fa170:	eor	w11, w11, w12
0x2519fa174:	mov	w12, #0xa84c
0x2519fa178:	movk	w12, #0xa435, lsl #16
0x2519fa17c:	orr	w12, w12, w11, lsl #1
0x2519fa180:	sub	w11, w12, w11
0x2519fa184:	mov	w12, #0x2bda
0x2519fa188:	movk	w12, #0xade5, lsl #16
0x2519fa18c:	add	w11, w11, w12
0x2519fa190:	mov	w12, #0x51d2
0x2519fa194:	movk	w12, #0xd630, lsl #16
0x2519fa198:	eor	w11, w11, w12
0x2519fa19c:	mov	w12, #0x9f29
0x2519fa1a0:	movk	w12, #0x6c83, lsl #16
0x2519fa1a4:	mov	w13, #0x25fc
0x2519fa1a8:	movk	w13, #0xdb53, lsl #16
0x2519fa1ac:	msub	w11, w11, w12, w13
0x2519fa1b0:	str	w11, [sp, #0x14]
0x2519fa1b4:	ldr	w11, [x22]
0x2519fa1b8:	ldr	w12, [x25]
0x2519fa1bc:	eor	w11, w11, w20
0x2519fa1c0:	eor	w11, w11, w12
0x2519fa1c4:	mul	w11, w11, w21
0x2519fa1c8:	ldr	x12, [x10, #0x128]
0x2519fa1cc:	add	x12, x12, w11, uxtb
0x2519fa1d0:	ldurb	w12, [x12, #-8]
0x2519fa1d4:	mov	w13, #0xb9
0x2519fa1d8:	eor	w12, w12, w13
0x2519fa1dc:	ldr	x13, [x10, #0x638]
0x2519fa1e0:	add	x12, x13, x12
0x2519fa1e4:	ldurb	w12, [x12, #-4]
0x2519fa1e8:	eor	w11, w12, w11
0x2519fa1ec:	and	w11, w11, #0xff
0x2519fa1f0:	add	w11, w11, #0x3fc
0x2519fa1f4:	ldr	w8, [x8, #0x6d8]
0x2519fa1f8:	ldr	w9, [x9, #0x410]
0x2519fa1fc:	eor	w8, w8, w20
0x2519fa200:	eor	w8, w8, w9
0x2519fa204:	mul	w8, w8, w21
0x2519fa208:	adrp	x9, #0x251c6f000
0x2519fa20c:	add	x9, x9, #0xa60
0x2519fa210:	add	x9, x9, w8, uxtb
0x2519fa214:	ldrb	w9, [x9]
0x2519fa218:	eor	w9, w9, #0x18
0x2519fa21c:	adrp	x12, #0x251c70000
0x2519fa220:	add	x12, x12, #0xb70
0x2519fa224:	ldrb	w9, [x12, w9, uxtw]
0x2519fa228:	eor	w8, w8, w9
0x2519fa22c:	and	w8, w8, #0xff
0x2519fa230:	sub	w8, w8, #0x27
0x2519fa234:	ldr	x8, [x10, w8, sxtw #3]
0x2519fa238:	sub	x26, x8, #0xc
0x2519fa23c:	ldr	x8, [x26, w11, uxtw #3]
0x2519fa240:	add	x0, sp, #0x10
0x2519fa244:	mov	x17, #0xf9e7
0x2519fa248:	blraa	x8, x17
0x2519fa24c:	ldr	w27, [sp, #0x10]
0x2519fa250:	mov	w8, #0x14f8
0x2519fa254:	movk	w8, #0x1455, lsl #16
0x2519fa258:	cmp	w27, w8
0x2519fa25c:	cset	w8, eq
0x2519fa260:	mov	w9, #0x199
0x2519fa264:	mul	w8, w8, w9
0x2519fa268:	mov	w9, #0x28a
0x2519fa26c:	eor	w8, w8, w9
0x2519fa270:	ldr	x8, [x26, w8, uxtw #3]
0x2519fa274:	mov	x17, #0x761e
0x2519fa278:	braa	x8, x17
0x2519fa27c:	mov	w9, #0
0x2519fa280:	mov	w8, #0x6a
0x2519fa284:	eor	w8, w26, w8
0x2519fa288:	sub	w10, w26, #0x3c
0x2519fa28c:	mov	w11, #0x5d
0x2519fa290:	orr	w10, w10, w11
0x2519fa294:	eor	w12, w26, #0x7c
0x2519fa298:	ldr	w13, [sp, #0x6c]
0x2519fa29c:	mov	x11, x13
0x2519fa2a0:	add	w12, w12, w13
0x2519fa2a4:	ldr	w2, [sp, #0x84]
0x2519fa2a8:	cmp	w12, w2
0x2519fa2ac:	cset	w13, ls
0x2519fa2b0:	lsl	w14, w13, #7
0x2519fa2b4:	sub	w13, w14, w13
0x2519fa2b8:	add	w14, w26, #0x2e5
0x2519fa2bc:	eor	w13, w13, w14
0x2519fa2c0:	ldr	x13, [x19, w13, sxtw #3]
0x2519fa2c4:	str	w12, [sp, #0x6c]
0x2519fa2c8:	ldr	x1, [sp, #0x78]
0x2519fa2cc:	mov	x17, #0x7f6f
0x2519fa2d0:	braa	x13, x17
0x2519fa2d4:	ldr	x30, [sp, #0x48]
0x2519fa2d8:	ldrb	w9, [x30, #0x60]
0x2519fa2dc:	cmp	w9, #2
0x2519fa2e0:	b.eq	#0x2519fa34c
0x2519fa2e4:	mov	x8, x7
0x2519fa2e8:	cmp	w9, #1
0x2519fa2ec:	mov	w0, #0x480
0x2519fa2f0:	movk	w0, #0x7a36, lsl #16
0x2519fa2f4:	mov	w16, #0x2222
0x2519fa2f8:	movk	w16, #0x4080, lsl #16
0x2519fa2fc:	mov	w1, #0xea
0x2519fa300:	ldr	x4, [sp, #0x40]
0x2519fa304:	b.ne	#0x2519fa3a8
0x2519fa308:	mov	w9, #0
0x2519fa30c:	add	w8, w6, w7
0x2519fa310:	add	w10, w8, #0x63
0x2519fa314:	mov	w11, #0x11
0x2519fa318:	orr	w10, w10, w11
0x2519fa31c:	add	w8, w8, #0x74
0x2519fa320:	ldr	w11, [x30, #0x5c]
0x2519fa324:	eor	w12, w10, w19
0x2519fa328:	cmp	w11, w12
0x2519fa32c:	cset	w12, eq
0x2519fa330:	mov	w13, #0xc1
0x2519fa334:	mul	w12, w12, w13
0x2519fa338:	eor	w8, w12, w8
0x2519fa33c:	ldr	x12, [x27, w8, sxtw #3]
0x2519fa340:	mov	x8, x7
0x2519fa344:	mov	x17, #0xc3f2
0x2519fa348:	braa	x12, x17
0x2519fa34c:	mov	w9, #0
0x2519fa350:	add	w8, w6, w7
0x2519fa354:	add	w10, w8, #0x9f
0x2519fa358:	mov	w11, #0x14
0x2519fa35c:	orr	w10, w10, w11
0x2519fa360:	add	w8, w8, #0xb3
0x2519fa364:	ldr	w11, [x30, #0x5c]
0x2519fa368:	cmp	w11, #0
0x2519fa36c:	cset	w12, ne
0x2519fa370:	mov	w13, #0x1d4
0x2519fa374:	eor	w13, w10, w13
0x2519fa378:	mul	w12, w12, w13
0x2519fa37c:	eor	w8, w12, w8
0x2519fa380:	ldr	x12, [x27, w8, sxtw #3]
0x2519fa384:	mov	x8, x7
0x2519fa388:	mov	w0, #0x480
0x2519fa38c:	movk	w0, #0x7a36, lsl #16
0x2519fa390:	mov	w1, #0x1017
0x2519fa394:	movk	w1, #0x281, lsl #16
0x2519fa398:	mov	w4, #0xea
0x2519fa39c:	ldr	x22, [sp, #0x40]
0x2519fa3a0:	mov	x17, #0xc3f2
0x2519fa3a4:	braa	x12, x17
0x2519fa3a8:	add	x9, sp, #0xd8
0x2519fa3ac:	add	w8, w6, w8
0x2519fa3b0:	add	w8, w8, #0xf
0x2519fa3b4:	mov	w10, #0x82
0x2519fa3b8:	orr	w8, w8, w10
0x2519fa3bc:	mov	w10, #0x5c
0x2519fa3c0:	ldr	x14, [sp, #0x30]
0x2519fa3c4:	mov	w15, #0xba
0x2519fa3c8:	sub	w11, w8, w6
0x2519fa3cc:	sub	w11, w11, #0x91
0x2519fa3d0:	sub	x10, x10, #1
0x2519fa3d4:	str	x10, [sp, #0xd8]
0x2519fa3d8:	eor	w12, w9, w15
0x2519fa3dc:	add	w13, w9, #0x11
0x2519fa3e0:	mul	w12, w12, w13
0x2519fa3e4:	strb	w12, [x30, x10]
0x2519fa3e8:	ldr	x10, [sp, #0xd8]
0x2519fa3ec:	cmp	x10, #0
0x2519fa3f0:	cset	w12, eq
0x2519fa3f4:	add	w13, w0, #0x17b
0x2519fa3f8:	eor	w11, w11, w13
0x2519fa3fc:	mul	w11, w12, w11
0x2519fa400:	eor	w11, w11, w8
0x2519fa404:	ldr	x11, [x27, w11, sxtw #3]
0x2519fa408:	mov	x17, #0x84de
0x2519fa40c:	braa	x11, x17

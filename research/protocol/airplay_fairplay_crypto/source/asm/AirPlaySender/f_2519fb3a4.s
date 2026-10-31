; AirPlaySender 0x2519fb3a4-0x2519fb4d4; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519fb3a4:	pacibsp	
0x2519fb3a8:	sub	sp, sp, #0x20
0x2519fb3ac:	stp	x29, x30, [sp, #0x10]
0x2519fb3b0:	add	x29, sp, #0x10
0x2519fb3b4:	mov	x9, #0xb4fa
0x2519fb3b8:	movk	x9, #0x6d3c, lsl #16
0x2519fb3bc:	movk	x9, #0x2a54, lsl #32
0x2519fb3c0:	movk	x9, #0x375b, lsl #48
0x2519fb3c4:	mov	w8, #0x1f79
0x2519fb3c8:	movk	w8, #0xd3ef, lsl #16
0x2519fb3cc:	adrp	x12, #0x26e7db000
0x2519fb3d0:	ldr	w10, [x12, #0x538]
0x2519fb3d4:	adrp	x13, #0x26e7db000
0x2519fb3d8:	ldr	w11, [x13, #0x410]
0x2519fb3dc:	eor	w10, w10, w9
0x2519fb3e0:	eor	w10, w10, w11
0x2519fb3e4:	mul	w10, w10, w8
0x2519fb3e8:	adrp	x14, #0x251c6f000
0x2519fb3ec:	add	x14, x14, #0xa60
0x2519fb3f0:	add	x15, x14, w10, uxtb
0x2519fb3f4:	ldrb	w15, [x15]
0x2519fb3f8:	adrp	x16, #0x251c70000
0x2519fb3fc:	add	x16, x16, #0xb70
0x2519fb400:	eor	w15, w15, #0x18
0x2519fb404:	ldrb	w15, [x16, w15, uxtw]
0x2519fb408:	eor	w10, w10, w15
0x2519fb40c:	and	w10, w10, #0xff
0x2519fb410:	sub	w10, w10, #0x32
0x2519fb414:	adrp	x15, #0x27612b000
0x2519fb418:	add	x15, x15, #0x8f0
0x2519fb41c:	ldr	x10, [x15, w10, sxtw #3]
0x2519fb420:	ldr	x17, [x10, #-4]!
0x2519fb424:	add	w11, w11, w17
0x2519fb428:	eor	w11, w11, w9
0x2519fb42c:	mul	w11, w11, w8
0x2519fb430:	add	x1, x14, w11, uxtb
0x2519fb434:	ldrb	w1, [x1]
0x2519fb438:	mov	w2, #0xb4
0x2519fb43c:	eor	w1, w1, w2
0x2519fb440:	ldrb	w1, [x16, w1, uxtw]
0x2519fb444:	eor	w11, w11, w1
0x2519fb448:	and	w11, w11, #0xff
0x2519fb44c:	add	w11, w11, #0x42
0x2519fb450:	ldr	x11, [x15, w11, uxtw #3]
0x2519fb454:	ldr	x1, [x11]
0x2519fb458:	sub	x17, x1, x17
0x2519fb45c:	add	x1, sp, #8
0x2519fb460:	eor	x1, x1, x9
0x2519fb464:	eor	x17, x17, x1
0x2519fb468:	mul	x17, x17, x8
0x2519fb46c:	str	x17, [x10]
0x2519fb470:	str	x17, [x11]
0x2519fb474:	cmp	x0, #0
0x2519fb478:	cset	w17, ne
0x2519fb47c:	mov	w1, #0xd8
0x2519fb480:	mul	w17, w17, w1
0x2519fb484:	mov	w1, #0x249
0x2519fb488:	eor	w17, w17, w1
0x2519fb48c:	ldr	w12, [x12, #0x538]
0x2519fb490:	ldr	w13, [x13, #0x410]
0x2519fb494:	add	w12, w13, w12
0x2519fb498:	eor	w12, w12, w9
0x2519fb49c:	mul	w12, w12, w8
0x2519fb4a0:	add	x13, x14, w12, uxtb
0x2519fb4a4:	ldrb	w13, [x13]
0x2519fb4a8:	mov	w14, #0xb3
0x2519fb4ac:	eor	w13, w13, w14
0x2519fb4b0:	ldrb	w13, [x16, w13, uxtw]
0x2519fb4b4:	eor	w12, w12, w13
0x2519fb4b8:	and	w12, w12, #0xff
0x2519fb4bc:	sub	w12, w12, #0x82
0x2519fb4c0:	ldr	x12, [x15, w12, sxtw #3]
0x2519fb4c4:	sub	x12, x12, #0xc
0x2519fb4c8:	ldr	x13, [x12, w17, uxtw #3]
0x2519fb4cc:	mov	x17, #0xc5e3
0x2519fb4d0:	braa	x13, x17

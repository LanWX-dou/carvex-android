; AirPlaySender 0x2519de244-0x2519e1eec; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519de244:	pacibsp	
0x2519de248:	stp	x28, x27, [sp, #-0x60]!
0x2519de24c:	stp	x26, x25, [sp, #0x10]
0x2519de250:	stp	x24, x23, [sp, #0x20]
0x2519de254:	stp	x22, x21, [sp, #0x30]
0x2519de258:	stp	x20, x19, [sp, #0x40]
0x2519de25c:	stp	x29, x30, [sp, #0x50]
0x2519de260:	add	x29, sp, #0x50
0x2519de264:	sub	sp, sp, #0xf40
0x2519de268:	stp	x5, x7, [sp, #0x1a8]
0x2519de26c:	stp	x3, x6, [sp, #0x198]
0x2519de270:	mov	x25, x2
0x2519de274:	mov	x24, x1
0x2519de278:	str	w0, [sp, #0x190]
0x2519de27c:	adrp	x8, #0x2681b4000
0x2519de280:	ldr	x8, [x8, #0xee0]
0x2519de284:	ldr	x8, [x8]
0x2519de288:	stur	x8, [x29, #-0x68]
0x2519de28c:	mov	x26, #0xb4fa
0x2519de290:	movk	x26, #0x6d3c, lsl #16
0x2519de294:	movk	x26, #0x2a54, lsl #32
0x2519de298:	movk	x26, #0x375b, lsl #48
0x2519de29c:	mov	w27, #0x1f79
0x2519de2a0:	movk	w27, #0xd3ef, lsl #16
0x2519de2a4:	mov	w15, #0x9f29
0x2519de2a8:	movk	w15, #0x6c83, lsl #16
0x2519de2ac:	adrp	x8, #0x26e7db000
0x2519de2b0:	ldr	w10, [x8, #0x418]
0x2519de2b4:	adrp	x9, #0x26e7db000
0x2519de2b8:	ldr	w11, [x9, #0x410]
0x2519de2bc:	add	w10, w11, w10
0x2519de2c0:	eor	w10, w10, w26
0x2519de2c4:	mul	w10, w10, w27
0x2519de2c8:	adrp	x12, #0x251c6f000
0x2519de2cc:	add	x12, x12, #0xb60
0x2519de2d0:	add	x12, x12, w10, uxtb
0x2519de2d4:	ldrb	w12, [x12]
0x2519de2d8:	mov	w13, #0xcd
0x2519de2dc:	eor	w12, w12, w13
0x2519de2e0:	adrp	x14, #0x251c71000
0x2519de2e4:	add	x14, x14, #0x70
0x2519de2e8:	ldrb	w12, [x14, w12, uxtw]
0x2519de2ec:	eor	w10, w10, w12
0x2519de2f0:	and	w10, w10, #0xff
0x2519de2f4:	adrp	x22, #0x27612b000
0x2519de2f8:	add	x22, x22, #0x8f0
0x2519de2fc:	sub	w10, w10, #0x58
0x2519de300:	ldr	x20, [x22, w10, sxtw #3]
0x2519de304:	ldr	x10, [x20, #-4]!
0x2519de308:	eor	w11, w26, w11
0x2519de30c:	eor	w11, w10, w11
0x2519de310:	mul	w11, w11, w27
0x2519de314:	adrp	x12, #0x251c6f000
0x2519de318:	add	x12, x12, #0xa60
0x2519de31c:	add	x12, x12, w11, uxtb
0x2519de320:	ldrb	w12, [x12]
0x2519de324:	mov	w14, #0xb4
0x2519de328:	eor	w12, w12, w14
0x2519de32c:	adrp	x14, #0x251c70000
0x2519de330:	add	x14, x14, #0xb70
0x2519de334:	ldrb	w12, [x14, w12, uxtw]
0x2519de338:	mov	w19, #0x14f8
0x2519de33c:	movk	w19, #0x1455, lsl #16
0x2519de340:	eor	w11, w11, w12
0x2519de344:	and	w11, w11, #0xff
0x2519de348:	add	w11, w11, #0x42
0x2519de34c:	ldr	x21, [x22, w11, uxtw #3]
0x2519de350:	ldr	x11, [x21]
0x2519de354:	sub	x10, x11, x10
0x2519de358:	add	x11, sp, #0x208
0x2519de35c:	sub	x10, x10, x11
0x2519de360:	eor	x10, x10, x26
0x2519de364:	mul	x10, x10, x27
0x2519de368:	str	x10, [x20]
0x2519de36c:	str	x10, [x21]
0x2519de370:	sub	x10, x29, #0xb0
0x2519de374:	mov	w11, #0xc569
0x2519de378:	movk	w11, #0x3d28, lsl #16
0x2519de37c:	eor	w10, w10, w11
0x2519de380:	mov	w11, #0x25fc
0x2519de384:	movk	w11, #0xdb53, lsl #16
0x2519de388:	msub	w10, w10, w15, w11
0x2519de38c:	stur	w10, [x29, #-0xac]
0x2519de390:	ldr	w10, [x20]
0x2519de394:	ldr	w11, [x21]
0x2519de398:	sub	w10, w11, w10
0x2519de39c:	eor	w10, w10, w26
0x2519de3a0:	mul	w10, w10, w27
0x2519de3a4:	ldr	x11, [x22, #0x158]
0x2519de3a8:	sub	x23, x11, #0xc
0x2519de3ac:	add	x11, x23, w10, uxtb
0x2519de3b0:	ldrb	w11, [x11]
0x2519de3b4:	eor	w11, w11, w13
0x2519de3b8:	ldr	x12, [x22, #0x1f8]
0x2519de3bc:	sub	x12, x12, #4
0x2519de3c0:	str	x12, [sp, #0x188]
0x2519de3c4:	ldrb	w11, [x12, w11, uxtw]
0x2519de3c8:	eor	w10, w11, w10
0x2519de3cc:	and	w10, w10, #0xff
0x2519de3d0:	add	w10, w10, #0x387
0x2519de3d4:	ldr	w8, [x8, #0x418]
0x2519de3d8:	ldr	w9, [x9, #0x410]
0x2519de3dc:	eor	w8, w8, w26
0x2519de3e0:	eor	w8, w8, w9
0x2519de3e4:	mul	w8, w8, w27
0x2519de3e8:	adrp	x9, #0x251c70000
0x2519de3ec:	add	x9, x9, #0xe70
0x2519de3f0:	add	x9, x9, w8, uxtb
0x2519de3f4:	ldrb	w9, [x9]
0x2519de3f8:	mov	w11, #0x3b
0x2519de3fc:	eor	w9, w9, w11
0x2519de400:	adrp	x11, #0x251c6d000
0x2519de404:	add	x11, x11, #0x290
0x2519de408:	ldrb	w9, [x11, w9, uxtw]
0x2519de40c:	eor	w8, w8, w9
0x2519de410:	and	w8, w8, #0xff
0x2519de414:	sub	w8, w8, #0x75
0x2519de418:	ldr	x8, [x22, w8, sxtw #3]
0x2519de41c:	sub	x28, x8, #0xc
0x2519de420:	ldr	x8, [x28, w10, uxtw #3]
0x2519de424:	sub	x0, x29, #0xb0
0x2519de428:	mov	x17, #0xf9e7
0x2519de42c:	blraa	x8, x17
0x2519de430:	ldur	w8, [x29, #-0xb0]
0x2519de434:	cmp	w8, w19
0x2519de438:	cset	w9, ne
0x2519de43c:	mov	w10, #0x1d
0x2519de440:	mul	w9, w9, w10
0x2519de444:	mov	w10, #0x12f
0x2519de448:	eor	w9, w9, w10
0x2519de44c:	ldr	x9, [x28, w9, uxtw #3]
0x2519de450:	mov	x17, #0x707d
0x2519de454:	braa	x9, x17
0x2519de458:	ldr	w8, [sp, #0x28]
0x2519de45c:	ldr	w9, [x23]
0x2519de460:	add	w8, w9, w8
0x2519de464:	str	w8, [x23]
0x2519de468:	mov	w8, #0x14f8
0x2519de46c:	movk	w8, #0x1455, lsl #16
0x2519de470:	str	w8, [x19]
0x2519de474:	ldur	x8, [x29, #-0x58]
0x2519de478:	adrp	x9, #0x2681b4000
0x2519de47c:	ldr	x9, [x9, #0xee0]
0x2519de480:	ldr	x9, [x9]
0x2519de484:	cmp	x9, x8
0x2519de488:	b.ne	#0x2519de4ac
0x2519de48c:	ldp	x29, x30, [sp, #0xc0]
0x2519de490:	ldp	x20, x19, [sp, #0xb0]
0x2519de494:	ldp	x22, x21, [sp, #0xa0]
0x2519de498:	ldp	x24, x23, [sp, #0x90]
0x2519de49c:	ldp	x26, x25, [sp, #0x80]
0x2519de4a0:	ldp	x28, x27, [sp, #0x70]
0x2519de4a4:	add	sp, sp, #0xd0
0x2519de4a8:	retab	
0x2519de4ac:	bl	#0x2580f4380
0x2519de4b0:	add	x9, x9, #4
0x2519de4b4:	b	#0x251a1af70
0x2519de4b8:	mov	x21, x13
0x2519de4bc:	add	w22, w22, #0xe2
0x2519de4c0:	add	x8, sp, #0xd8
0x2519de4c4:	mov	w9, #0x8d
0x2519de4c8:	sub	w10, w22, #0x27f
0x2519de4cc:	mov	w11, #0xba
0x2519de4d0:	mov	w12, #0x35
0x2519de4d4:	ldp	x2, x3, [sp, #0x50]
0x2519de4d8:	eor	w13, w8, w11
0x2519de4dc:	add	w14, w8, #0x11
0x2519de4e0:	mul	w13, w13, w14
0x2519de4e4:	add	x14, x0, x9
0x2519de4e8:	strb	w13, [x14]
0x2519de4ec:	cmp	x9, #0
0x2519de4f0:	cset	w13, eq
0x2519de4f4:	mul	w13, w13, w12
0x2519de4f8:	eor	w13, w13, w10
0x2519de4fc:	ldr	x13, [x26, w13, sxtw #3]
0x2519de500:	mov	x17, #0x306
0x2519de504:	braa	x13, x17
0x2519de508:	mov	w13, #0
0x2519de50c:	mov	w8, #0xc868
0x2519de510:	movk	w8, #0x2508, lsl #16
0x2519de514:	mov	w9, #0x12a6
0x2519de518:	movk	w9, #0xf08a, lsl #16
0x2519de51c:	add	w9, w21, w9
0x2519de520:	mov	w10, #0xee7b
0x2519de524:	movk	w10, #0xf75, lsl #16
0x2519de528:	and	w11, w9, w10
0x2519de52c:	str	w13, [sp, #0x30]
0x2519de530:	and	w9, w13, #0xff
0x2519de534:	mov	w10, #0x356e
0x2519de538:	movk	w10, #0xdaf7, lsl #16
0x2519de53c:	str	w11, [sp, #0x40]
0x2519de540:	add	w10, w11, w10
0x2519de544:	eor	w10, w10, w9
0x2519de548:	eor	w11, w21, #0x38
0x2519de54c:	and	w9, w11, w9, lsl #1
0x2519de550:	add	w9, w12, w9
0x2519de554:	add	w19, w10, w9
0x2519de558:	add	w8, w19, w8
0x2519de55c:	str	w8, [sp, #0x3c]
0x2519de560:	add	w23, w8, #0x38
0x2519de564:	ldr	w8, [x26]
0x2519de568:	ldr	w9, [x27]
0x2519de56c:	sub	w8, w9, w8
0x2519de570:	eor	w8, w8, w25
0x2519de574:	mul	w8, w8, w24
0x2519de578:	adrp	x9, #0x27612b000
0x2519de57c:	add	x9, x9, #0xa18
0x2519de580:	ldr	x10, [x9]
0x2519de584:	add	x10, x10, w8, uxtb
0x2519de588:	ldurb	w10, [x10, #-8]
0x2519de58c:	mov	w11, #0xb4
0x2519de590:	eor	w10, w10, w11
0x2519de594:	ldr	x9, [x9, #0x510]
0x2519de598:	add	x9, x9, x10
0x2519de59c:	ldurb	w9, [x9, #-4]
0x2519de5a0:	eor	w8, w9, w8
0x2519de5a4:	and	w8, w8, #0xff
0x2519de5a8:	add	w8, w8, #0x3c8
0x2519de5ac:	ldr	x8, [x28, w8, uxtw #3]
0x2519de5b0:	mov	x1, #0x4924
0x2519de5b4:	movk	x1, #0x7777, lsl #16
0x2519de5b8:	movk	x1, #0x40, lsl #32
0x2519de5bc:	movk	x1, #0x100, lsl #48
0x2519de5c0:	mov	x0, x23
0x2519de5c4:	mov	x17, #0xaa22
0x2519de5c8:	blraa	x8, x17
0x2519de5cc:	ldr	x8, [sp, #0x68]
0x2519de5d0:	str	x0, [x8]
0x2519de5d4:	cmp	x0, #0
0x2519de5d8:	cset	w8, ne
0x2519de5dc:	lsl	w9, w8, #5
0x2519de5e0:	sub	w8, w9, w8
0x2519de5e4:	eor	w8, w8, w21
0x2519de5e8:	ldr	x8, [x28, w8, sxtw #3]
0x2519de5ec:	mov	w9, #0x70d1
0x2519de5f0:	movk	w9, #0x1454, lsl #16
0x2519de5f4:	sub	w21, w9, #5
0x2519de5f8:	ldr	x11, [sp, #0x48]
0x2519de5fc:	mov	x17, #0x3169
0x2519de600:	braa	x8, x17
0x2519de604:	add	x11, x11, #1
0x2519de608:	b	#0x251a024f4
0x2519de60c:	mov	w8, #0x65c0
0x2519de610:	movk	w8, #0x956a, lsl #16
0x2519de614:	add	w8, w24, w8
0x2519de618:	mov	w9, #0x9b62
0x2519de61c:	movk	w9, #0x6a95, lsl #16
0x2519de620:	and	w20, w8, w9
0x2519de624:	mov	w8, #0x142
0x2519de628:	eor	w8, w20, w8
0x2519de62c:	mov	w9, #0x117
0x2519de630:	mul	w19, w8, w9
0x2519de634:	ldr	w8, [sp, #0x10c]
0x2519de638:	ldr	w9, [sp, #0xf4]
0x2519de63c:	add	w8, w9, w8
0x2519de640:	ldr	w9, [sp, #0x108]
0x2519de644:	add	w8, w8, w9
0x2519de648:	mov	w9, #0xb236
0x2519de64c:	eor	w9, w19, w9
0x2519de650:	cmp	w8, w9
0x2519de654:	cset	w8, eq
0x2519de658:	mov	w9, #0x281
0x2519de65c:	mul	w8, w8, w9
0x2519de660:	eor	w8, w8, w24
0x2519de664:	ldr	x9, [x7, w8, uxtw #3]
0x2519de668:	mov	w8, #0x708d
0x2519de66c:	movk	w8, #0x1454, lsl #16
0x2519de670:	sub	w8, w8, #0x318
0x2519de674:	mov	x17, #0xc7a2
0x2519de678:	braa	x9, x17
0x2519de67c:	mov	w9, #0x12b
0x2519de680:	eor	w9, w11, w9
0x2519de684:	add	w9, w9, w9, lsl #3
0x2519de688:	lsl	w13, w9, #1
0x2519de68c:	mov	w9, #0xc5
0x2519de690:	ldr	w11, [sp, #0xd0]
0x2519de694:	eor	w9, w11, w9
0x2519de698:	eor	w10, w11, #0xfc
0x2519de69c:	add	w10, w10, #0xa
0x2519de6a0:	eor	w11, w11, #0x38
0x2519de6a4:	sub	w11, w11, #0x32
0x2519de6a8:	eor	w10, w11, w10
0x2519de6ac:	ldrb	w11, [x12]
0x2519de6b0:	add	w9, w9, w13
0x2519de6b4:	sub	w9, w9, #0x57
0x2519de6b8:	eor	w9, w10, w9
0x2519de6bc:	add	w9, w11, w9
0x2519de6c0:	add	w9, w9, #0xb
0x2519de6c4:	strb	w9, [x12]
0x2519de6c8:	mov	w9, #0x22a4
0x2519de6cc:	movk	w9, #0xa77d, lsl #16
0x2519de6d0:	cmp	w3, w9
0x2519de6d4:	cinc	x10, x12, ne
0x2519de6d8:	ldrb	w11, [x10]
0x2519de6dc:	add	w11, w23, w11
0x2519de6e0:	add	w11, w11, #0x58
0x2519de6e4:	strb	w11, [x10]
0x2519de6e8:	orr	w9, w9, #1
0x2519de6ec:	eor	w9, w3, w9
0x2519de6f0:	mov	w10, #2
0x2519de6f4:	udiv	w11, w10, w9
0x2519de6f8:	msub	w10, w11, w9, w10
0x2519de6fc:	mov	w11, #0x92
0x2519de700:	eor	w11, w8, w11
0x2519de704:	add	w11, w11, #0x4b
0x2519de708:	mov	w15, #0x8b
0x2519de70c:	eor	w15, w8, w15
0x2519de710:	add	w15, w15, #0x54
0x2519de714:	eor	w11, w11, w15
0x2519de718:	mov	w15, #0x62
0x2519de71c:	eor	w8, w8, w15
0x2519de720:	add	x10, x12, x10
0x2519de724:	sub	w8, w8, #0x45
0x2519de728:	eor	w8, w11, w8
0x2519de72c:	ldrb	w11, [x10]
0x2519de730:	add	w8, w8, w11
0x2519de734:	add	w8, w8, #0x5c
0x2519de738:	strb	w8, [x10]
0x2519de73c:	mov	w8, #3
0x2519de740:	udiv	w10, w8, w9
0x2519de744:	msub	w8, w10, w9, w8
0x2519de748:	add	x8, x12, x8
0x2519de74c:	ldrb	w10, [x8]
0x2519de750:	add	w10, w10, #0x5c
0x2519de754:	strb	w10, [x8]
0x2519de758:	mov	w8, #4
0x2519de75c:	udiv	w10, w8, w9
0x2519de760:	msub	w8, w10, w9, w8
0x2519de764:	ldr	w11, [sp, #0xd4]
0x2519de768:	mov	w10, #-0x17
0x2519de76c:	orn	w10, w10, w11, lsl #1
0x2519de770:	add	w10, w11, w10
0x2519de774:	sub	w10, w10, #0x74
0x2519de778:	mov	w11, #0x53
0x2519de77c:	eor	w11, w10, w11
0x2519de780:	sub	w11, w11, #0x53
0x2519de784:	mov	w15, #0xa3
0x2519de788:	eor	w15, w10, w15
0x2519de78c:	add	w15, w15, #0x5d
0x2519de790:	eor	w11, w11, w15
0x2519de794:	mov	w15, #0x7b
0x2519de798:	eor	w10, w10, w15
0x2519de79c:	add	x8, x12, x8
0x2519de7a0:	sub	w10, w10, #0x7b
0x2519de7a4:	eor	w10, w11, w10
0x2519de7a8:	ldrb	w11, [x8]
0x2519de7ac:	add	w10, w10, w11
0x2519de7b0:	sub	w10, w10, #0x75
0x2519de7b4:	strb	w10, [x8]
0x2519de7b8:	mov	w10, #5
0x2519de7bc:	udiv	w8, w10, w9
0x2519de7c0:	msub	w8, w8, w9, w10
0x2519de7c4:	add	x8, x12, x8
0x2519de7c8:	ldrb	w10, [x8]
0x2519de7cc:	add	w10, w6, w10
0x2519de7d0:	add	w10, w10, #0x39
0x2519de7d4:	strb	w10, [x8]
0x2519de7d8:	mov	w8, #6
0x2519de7dc:	udiv	w10, w8, w9
0x2519de7e0:	msub	w8, w10, w9, w8
0x2519de7e4:	mov	w10, #0x73
0x2519de7e8:	eor	w10, w14, w10
0x2519de7ec:	sub	w10, w10, #5
0x2519de7f0:	eor	w11, w14, w1
0x2519de7f4:	sub	w11, w11, #0x60
0x2519de7f8:	eor	w10, w10, w11
0x2519de7fc:	add	x8, x12, x8
0x2519de800:	eor	w11, w14, #0xfffffff1
0x2519de804:	add	w11, w11, #0x79
0x2519de808:	eor	w10, w10, w11
0x2519de80c:	ldrb	w11, [x8]
0x2519de810:	add	w10, w10, w11
0x2519de814:	mov	w0, #0x7429
0x2519de818:	movk	w0, #0x68f1, lsl #16
0x2519de81c:	sub	w10, w10, #0x1e
0x2519de820:	strb	w10, [x8]
0x2519de824:	mov	w8, #7
0x2519de828:	udiv	w10, w8, w9
0x2519de82c:	msub	w8, w10, w9, w8
0x2519de830:	add	x8, x12, x8
0x2519de834:	ldrb	w10, [x8]
0x2519de838:	add	w10, w10, w16
0x2519de83c:	mov	w15, #0x7e1e
0x2519de840:	movk	w15, #0x5575, lsl #16
0x2519de844:	strb	w10, [x8]
0x2519de848:	mov	w8, #8
0x2519de84c:	udiv	w10, w8, w9
0x2519de850:	msub	w10, w10, w9, w8
0x2519de854:	lsl	w8, w26, #1
0x2519de858:	and	w8, w8, #8
0x2519de85c:	sub	w8, w26, w8
0x2519de860:	add	w8, w8, #4
0x2519de864:	mov	w11, #0x50
0x2519de868:	eor	w11, w8, w11
0x2519de86c:	sub	w11, w11, #0x50
0x2519de870:	mov	w1, #0xa
0x2519de874:	eor	w14, w8, w1
0x2519de878:	sub	w14, w14, #0xa
0x2519de87c:	eor	w14, w11, w14
0x2519de880:	mov	w11, #0xccb7
0x2519de884:	movk	w11, #0x4c74, lsl #16
0x2519de888:	eor	w16, w8, w22
0x2519de88c:	mov	w8, #0xf885
0x2519de890:	movk	w8, #0xcd76, lsl #16
0x2519de894:	add	x17, x12, x10
0x2519de898:	sub	w10, w16, #0x5e
0x2519de89c:	eor	w10, w14, w10
0x2519de8a0:	ldrb	w14, [x17]
0x2519de8a4:	add	w14, w10, w14
0x2519de8a8:	mov	w10, #0x6ca
0x2519de8ac:	movk	w10, #0x3289, lsl #16
0x2519de8b0:	add	w14, w14, #4
0x2519de8b4:	strb	w14, [x17]
0x2519de8b8:	mov	w14, #9
0x2519de8bc:	udiv	w16, w14, w9
0x2519de8c0:	msub	w14, w16, w9, w14
0x2519de8c4:	add	x16, x12, x14
0x2519de8c8:	ldrb	w14, [x16]
0x2519de8cc:	add	w17, w14, w7
0x2519de8d0:	mov	w14, #0x6ca
0x2519de8d4:	movk	w14, #0x3289, lsl #16
0x2519de8d8:	strb	w17, [x16]
0x2519de8dc:	udiv	w16, w1, w9
0x2519de8e0:	msub	w16, w16, w9, w1
0x2519de8e4:	add	x16, x12, x16
0x2519de8e8:	ldrb	w17, [x16]
0x2519de8ec:	add	w17, w17, w5
0x2519de8f0:	strb	w17, [x16]
0x2519de8f4:	mov	w16, #0x8bd7
0x2519de8f8:	movk	w16, #0x970e, lsl #16
0x2519de8fc:	mov	x2, #-0x7429
0x2519de900:	movk	x2, #0x970e, lsl #16
0x2519de904:	mov	w3, #0x1d
0x2519de908:	mov	w5, #0x7429
0x2519de90c:	movk	w5, #0x68f1, lsl #16
0x2519de910:	add	w17, w5, w16
0x2519de914:	udiv	w1, w17, w9
0x2519de918:	msub	w17, w1, w9, w17
0x2519de91c:	add	x17, x12, x17
0x2519de920:	ldrb	w1, [x17]
0x2519de924:	add	x6, x5, x4
0x2519de928:	add	x6, x6, x2
0x2519de92c:	ldrb	w6, [x6]
0x2519de930:	eor	w1, w6, w1
0x2519de934:	strb	w1, [x17]
0x2519de938:	add	x5, x5, #1
0x2519de93c:	add	x17, x0, #0x14
0x2519de940:	cmp	x5, x17
0x2519de944:	cset	w17, ne
0x2519de948:	mul	w17, w17, w3
0x2519de94c:	eor	w17, w17, w13
0x2519de950:	ldr	x6, [x20, w17, sxtw #3]
0x2519de954:	mov	w1, #0xccb7
0x2519de958:	movk	w1, #0x4c74, lsl #16
0x2519de95c:	mov	x17, #0x15a8
0x2519de960:	braa	x6, x17
0x2519de964:	add	x12, x3, x20
0x2519de968:	lsl	x12, x12, #2
0x2519de96c:	sub	x17, x12, #0xc
0x2519de970:	ldr	w17, [x11, x17]
0x2519de974:	sub	x1, x12, #0x20
0x2519de978:	ldr	w1, [x11, x1]
0x2519de97c:	sub	x2, x12, #0x38
0x2519de980:	ldr	w4, [x11, x2]
0x2519de984:	sub	x2, x12, #0x40
0x2519de988:	ldr	w5, [x11, x2]
0x2519de98c:	mov	w30, #0x2b2
0x2519de990:	eor	w2, w15, w30
0x2519de994:	eor	w17, w17, w21
0x2519de998:	eor	w1, w1, w4
0x2519de99c:	eor	w17, w17, w1
0x2519de9a0:	eor	w17, w17, w5
0x2519de9a4:	mov	w1, #0x2d21
0x2519de9a8:	movk	w1, #0xf78, lsl #16
0x2519de9ac:	eor	w17, w1, w17, ror #31
0x2519de9b0:	str	w17, [x11, x12]
0x2519de9b4:	add	x12, x3, x2
0x2519de9b8:	sub	x3, x12, #0x324
0x2519de9bc:	add	x12, x24, #0x50
0x2519de9c0:	cmp	x3, x12
0x2519de9c4:	cset	w12, eq
0x2519de9c8:	mul	w12, w12, w30
0x2519de9cc:	eor	w12, w12, w15
0x2519de9d0:	ldr	x12, [x27, w12, sxtw #3]
0x2519de9d4:	mov	w4, #0x7265
0x2519de9d8:	movk	w4, #0x62b4, lsl #16
0x2519de9dc:	mov	x17, #0x6ccd
0x2519de9e0:	braa	x12, x17
0x2519de9e4:	add	x22, x7, #0x18
0x2519de9e8:	mov	x8, #0xabe3
0x2519de9ec:	movk	x8, #0x347, lsl #16
0x2519de9f0:	movk	x8, #0xdaac, lsl #32
0x2519de9f4:	movk	x8, #0xead3, lsl #48
0x2519de9f8:	sub	x24, x29, #0x80
0x2519de9fc:	orr	w9, w8, w24
0x2519dea00:	and	w8, w24, w8
0x2519dea04:	sub	w8, w9, w8
0x2519dea08:	mov	w9, #0x9e3f
0x2519dea0c:	movk	w9, #0xfa3, lsl #16
0x2519dea10:	eor	w8, w8, w9
0x2519dea14:	mov	w9, #0x97f7
0x2519dea18:	movk	w9, #0xb9f0, lsl #16
0x2519dea1c:	mul	w8, w8, w9
0x2519dea20:	stur	x22, [x29, #-0x78]
0x2519dea24:	mov	w9, #0x5fba
0x2519dea28:	movk	w9, #0x5dbb, lsl #16
0x2519dea2c:	sub	w9, w9, w8
0x2519dea30:	add	w8, w8, w21
0x2519dea34:	sub	w8, w8, #8
0x2519dea38:	stp	w9, w8, [x29, #-0x80]
0x2519dea3c:	ldp	x19, x23, [sp, #0x70]
0x2519dea40:	ldr	w8, [x23]
0x2519dea44:	ldr	w9, [x19]
0x2519dea48:	mov	x28, #0xb4fa
0x2519dea4c:	movk	x28, #0x6d3c, lsl #16
0x2519dea50:	movk	x28, #0x2a54, lsl #32
0x2519dea54:	movk	x28, #0x375b, lsl #48
0x2519dea58:	eor	w8, w8, w28
0x2519dea5c:	eor	w8, w8, w9
0x2519dea60:	mov	w9, #0x1f79
0x2519dea64:	movk	w9, #0xd3ef, lsl #16
0x2519dea68:	mul	w8, w8, w9
0x2519dea6c:	add	x9, x27, w8, uxtb
0x2519dea70:	ldrb	w9, [x9]
0x2519dea74:	mov	w10, #0x4a
0x2519dea78:	eor	w9, w9, w10
0x2519dea7c:	ldrb	w9, [x30, w9, uxtw]
0x2519dea80:	mov	x20, x7
0x2519dea84:	add	w10, w21, #0x83
0x2519dea88:	str	w10, [sp, #0x50]
0x2519dea8c:	eor	w8, w8, w9
0x2519dea90:	and	w8, w8, #0xff
0x2519dea94:	add	w8, w8, #0x3f1
0x2519dea98:	ldr	x8, [x25, w8, uxtw #3]
0x2519dea9c:	sub	x0, x29, #0x80
0x2519deaa0:	mov	x28, x30
0x2519deaa4:	mov	x17, #0x1799
0x2519deaa8:	blraa	x8, x17
0x2519deaac:	mov	x8, #0xbf86
0x2519deab0:	movk	x8, #0x30ea, lsl #16
0x2519deab4:	movk	x8, #0xb479, lsl #32
0x2519deab8:	movk	x8, #0x92d0, lsl #48
0x2519deabc:	and	w9, w24, w8
0x2519deac0:	add	w8, w24, w8
0x2519deac4:	sub	w8, w8, w9, lsl #1
0x2519deac8:	mov	w9, #0x7aef
0x2519deacc:	movk	w9, #0xdc2, lsl #16
0x2519dead0:	eor	w8, w8, w9
0x2519dead4:	mov	w9, #0x9f29
0x2519dead8:	movk	w9, #0x6c83, lsl #16
0x2519deadc:	stp	x20, x22, [x29, #-0x78]
0x2519deae0:	mov	w10, #0x2d71
0x2519deae4:	movk	w10, #0xdb07, lsl #16
0x2519deae8:	msub	w8, w8, w9, w10
0x2519deaec:	add	w8, w8, w21
0x2519deaf0:	add	w8, w8, #0x6e
0x2519deaf4:	stur	w8, [x29, #-0x80]
0x2519deaf8:	ldr	w8, [x23]
0x2519deafc:	ldr	w9, [x19]
0x2519deb00:	sub	w8, w9, w8
0x2519deb04:	mov	x9, #0xb4fa
0x2519deb08:	movk	x9, #0x6d3c, lsl #16
0x2519deb0c:	movk	x9, #0x2a54, lsl #32
0x2519deb10:	movk	x9, #0x375b, lsl #48
0x2519deb14:	eor	w8, w8, w9
0x2519deb18:	mov	w9, #0x1f79
0x2519deb1c:	movk	w9, #0xd3ef, lsl #16
0x2519deb20:	mul	w8, w8, w9
0x2519deb24:	add	x9, x27, w8, uxtb
0x2519deb28:	ldrb	w9, [x9]
0x2519deb2c:	mov	w10, #0x4a
0x2519deb30:	eor	w9, w9, w10
0x2519deb34:	ldrb	w9, [x28, w9, uxtw]
0x2519deb38:	eor	w8, w8, w9
0x2519deb3c:	and	w8, w8, #0xff
0x2519deb40:	add	w8, w8, #0x3d1
0x2519deb44:	ldr	x8, [x25, w8, uxtw #3]
0x2519deb48:	sub	x0, x29, #0x80
0x2519deb4c:	mov	x17, #0x88c0
0x2519deb50:	blraa	x8, x17
0x2519deb54:	mov	x8, #0xd1c0
0x2519deb58:	movk	x8, #0x6f5c, lsl #16
0x2519deb5c:	movk	x8, #0x5326, lsl #32
0x2519deb60:	movk	x8, #0xd151, lsl #48
0x2519deb64:	and	w9, w24, w8
0x2519deb68:	add	w8, w24, w8
0x2519deb6c:	sub	w8, w8, w9, lsl #1
0x2519deb70:	mov	w9, #0x47ac
0x2519deb74:	movk	w9, #0x9602, lsl #16
0x2519deb78:	eor	w8, w8, w9
0x2519deb7c:	mov	w9, #0xd21b
0x2519deb80:	movk	w9, #0xe2f9, lsl #16
0x2519deb84:	mul	w8, w8, w9
0x2519deb88:	mov	w9, #0xb53e
0x2519deb8c:	movk	w9, #0xdc14, lsl #16
0x2519deb90:	eor	w9, w8, w9
0x2519deb94:	sub	x10, x29, #0x90
0x2519deb98:	add	w11, w8, w21
0x2519deb9c:	sub	w11, w11, #0x1d6
0x2519deba0:	stp	x22, x10, [x29, #-0x80]
0x2519deba4:	mov	w10, #0x22b5
0x2519deba8:	movk	w10, #0xa77d, lsl #16
0x2519debac:	sub	w8, w10, w8
0x2519debb0:	stur	w9, [x29, #-0x70]
0x2519debb4:	stp	w8, w11, [x29, #-0x6c]
0x2519debb8:	ldr	x8, [sp, #0x68]
0x2519debbc:	ldr	x8, [x8]
0x2519debc0:	str	x8, [sp, #0xa0]
0x2519debc4:	ldr	w8, [x23]
0x2519debc8:	ldr	w9, [x19]
0x2519debcc:	sub	w8, w9, w8
0x2519debd0:	mov	x9, #0xb4fa
0x2519debd4:	movk	x9, #0x6d3c, lsl #16
0x2519debd8:	movk	x9, #0x2a54, lsl #32
0x2519debdc:	movk	x9, #0x375b, lsl #48
0x2519debe0:	eor	w8, w8, w9
0x2519debe4:	mov	w9, #0x1f79
0x2519debe8:	movk	w9, #0xd3ef, lsl #16
0x2519debec:	mul	w8, w8, w9
0x2519debf0:	adrp	x9, #0x27612b000
0x2519debf4:	add	x9, x9, #0xd08
0x2519debf8:	ldr	x10, [x9]
0x2519debfc:	add	x10, x10, w8, uxtb
0x2519dec00:	ldurb	w10, [x10, #-8]
0x2519dec04:	mov	w11, #0xc4
0x2519dec08:	eor	w10, w10, w11
0x2519dec0c:	ldr	x9, [x9, #0xe0]
0x2519dec10:	add	x9, x9, x10
0x2519dec14:	ldurb	w9, [x9, #-8]
0x2519dec18:	eor	w8, w9, w8
0x2519dec1c:	and	w8, w8, #0xff
0x2519dec20:	add	w8, w8, #0x3c6
0x2519dec24:	ldr	x8, [x25, w8, uxtw #3]
0x2519dec28:	sub	x0, x29, #0x80
0x2519dec2c:	add	x1, sp, #0xa0
0x2519dec30:	mov	x17, #0x9971
0x2519dec34:	blraa	x8, x17
0x2519dec38:	mov	x8, sp
0x2519dec3c:	ldr	x9, [sp, #0xa0]
0x2519dec40:	add	x8, x8, x9
0x2519dec44:	mov	sp, x8
0x2519dec48:	ldur	w8, [x29, #-0x90]
0x2519dec4c:	ldp	w9, w10, [x20]
0x2519dec50:	add	w8, w9, w8
0x2519dec54:	str	w8, [x20]
0x2519dec58:	ldur	w8, [x29, #-0x8c]
0x2519dec5c:	add	w8, w10, w8
0x2519dec60:	str	w8, [x20, #4]
0x2519dec64:	ldur	w8, [x29, #-0x88]
0x2519dec68:	ldp	w9, w10, [x20, #8]
0x2519dec6c:	add	w8, w9, w8
0x2519dec70:	str	w8, [x20, #8]
0x2519dec74:	ldur	w8, [x29, #-0x84]
0x2519dec78:	add	w8, w10, w8
0x2519dec7c:	str	w8, [x20, #0xc]
0x2519dec80:	ldr	x8, [sp, #0x88]
0x2519dec84:	add	x26, x26, x8
0x2519dec88:	ldr	w21, [sp, #0x94]
0x2519dec8c:	sub	w21, w21, w8
0x2519dec90:	mov	w8, #0xe1
0x2519dec94:	ldr	w11, [sp, #0x50]
0x2519dec98:	eor	w8, w11, w8
0x2519dec9c:	sub	w16, w8, #0x18c
0x2519deca0:	mov	w9, #0xc861
0x2519deca4:	movk	w9, #0xa210, lsl #16
0x2519deca8:	add	w9, w9, #0xfb
0x2519decac:	eor	w9, w16, w9
0x2519decb0:	add	w9, w9, w21
0x2519decb4:	cmn	w9, #0x40
0x2519decb8:	cset	w9, lo
0x2519decbc:	mov	w10, #0x749
0x2519decc0:	mul	w9, w9, w10
0x2519decc4:	eor	w9, w9, w11
0x2519decc8:	ldr	x9, [x25, w9, sxtw #3]
0x2519deccc:	mov	x17, #0x6ebe
0x2519decd0:	braa	x9, x17
0x2519decd4:	mov	w8, #0xd0
0x2519decd8:	eor	w8, w11, w8
0x2519decdc:	ldr	x9, [sp, #0x80]
0x2519dece0:	str	x9, [sp, #0x190]
0x2519dece4:	ldp	x27, x23, [sp, #0x178]
0x2519dece8:	ldr	w9, [x27]
0x2519decec:	ldr	w10, [x23]
0x2519decf0:	eor	w9, w9, w22
0x2519decf4:	eor	w9, w9, w10
0x2519decf8:	mov	w10, #0x1f79
0x2519decfc:	movk	w10, #0xd3ef, lsl #16
0x2519ded00:	mul	w9, w9, w10
0x2519ded04:	add	x10, x20, w9, uxtb
0x2519ded08:	ldrb	w10, [x10]
0x2519ded0c:	mov	w11, #0xb4
0x2519ded10:	eor	w10, w10, w11
0x2519ded14:	ldr	x19, [sp, #0x108]
0x2519ded18:	ldrb	w10, [x19, w10, uxtw]
0x2519ded1c:	eor	w9, w9, w10
0x2519ded20:	mov	w10, #0x19
0x2519ded24:	mul	w8, w8, w10
0x2519ded28:	str	x8, [sp, #0x138]
0x2519ded2c:	and	w8, w9, #0xff
0x2519ded30:	add	w8, w8, #0x3e4
0x2519ded34:	ldr	x8, [x28, w8, uxtw #3]
0x2519ded38:	mov	w0, #3
0x2519ded3c:	mov	x17, #0xaa22
0x2519ded40:	blraa	x8, x17
0x2519ded44:	ldr	w8, [x27]
0x2519ded48:	ldr	w9, [x23]
0x2519ded4c:	sub	w8, w9, w8
0x2519ded50:	eor	w8, w8, w22
0x2519ded54:	mov	w10, #0x1f79
0x2519ded58:	movk	w10, #0xd3ef, lsl #16
0x2519ded5c:	mul	w8, w8, w10
0x2519ded60:	add	x9, x20, w8, uxtb
0x2519ded64:	ldrb	w9, [x9]
0x2519ded68:	mov	w11, #0xb3
0x2519ded6c:	eor	w9, w9, w11
0x2519ded70:	ldrb	w9, [x19, w9, uxtw]
0x2519ded74:	eor	w8, w8, w9
0x2519ded78:	and	w8, w8, #0xff
0x2519ded7c:	sub	w8, w8, #0x30
0x2519ded80:	adrp	x19, #0x27612b000
0x2519ded84:	add	x19, x19, #0x8f0
0x2519ded88:	ldr	x8, [x19, w8, sxtw #3]
0x2519ded8c:	str	x8, [sp, #0x50]
0x2519ded90:	stur	x0, [x8, #-4]
0x2519ded94:	ldr	w8, [x27]
0x2519ded98:	ldr	w9, [x23]
0x2519ded9c:	sub	w8, w9, w8
0x2519deda0:	eor	w8, w8, w22
0x2519deda4:	mul	w8, w8, w10
0x2519deda8:	mov	w20, #0x1f79
0x2519dedac:	movk	w20, #0xd3ef, lsl #16
0x2519dedb0:	ldp	x10, x9, [sp, #0xc8]
0x2519dedb4:	add	x9, x9, w8, uxtb
0x2519dedb8:	ldrb	w9, [x9]
0x2519dedbc:	eor	w9, w9, #0xfe
0x2519dedc0:	ldrb	w9, [x10, w9, uxtw]
0x2519dedc4:	eor	w8, w8, w9
0x2519dedc8:	and	w8, w8, #0xff
0x2519dedcc:	add	w8, w8, #0x36b
0x2519dedd0:	ldr	x8, [x28, w8, uxtw #3]
0x2519dedd4:	mov	w1, #0x30
0x2519dedd8:	mov	w2, #3
0x2519deddc:	mov	x17, #0x1b49
0x2519dede0:	blraa	x8, x17
0x2519dede4:	ldr	w8, [x27]
0x2519dede8:	ldr	w9, [x23]
0x2519dedec:	add	w8, w9, w8
0x2519dedf0:	eor	w8, w8, w22
0x2519dedf4:	mul	w8, w8, w20
0x2519dedf8:	ldp	x25, x21, [sp, #0x120]
0x2519dedfc:	add	x9, x21, w8, uxtb
0x2519dee00:	ldrb	w9, [x9]
0x2519dee04:	mov	w10, #0xcd
0x2519dee08:	eor	w9, w9, w10
0x2519dee0c:	ldrb	w9, [x25, w9, uxtw]
0x2519dee10:	eor	w8, w8, w9
0x2519dee14:	and	w8, w8, #0xff
0x2519dee18:	add	w8, w8, #0x389
0x2519dee1c:	ldr	x8, [x28, w8, uxtw #3]
0x2519dee20:	mov	w0, #0xc
0x2519dee24:	mov	x17, #0xaa22
0x2519dee28:	blraa	x8, x17
0x2519dee2c:	ldr	w8, [x27]
0x2519dee30:	ldr	w9, [x23]
0x2519dee34:	add	w8, w9, w8
0x2519dee38:	eor	w8, w8, w22
0x2519dee3c:	mul	w8, w8, w20
0x2519dee40:	add	x9, x21, w8, uxtb
0x2519dee44:	ldrb	w9, [x9]
0x2519dee48:	mov	w10, #0x4a
0x2519dee4c:	eor	w9, w9, w10
0x2519dee50:	ldrb	w9, [x25, w9, uxtw]
0x2519dee54:	eor	w8, w8, w9
0x2519dee58:	and	w8, w8, #0xff
0x2519dee5c:	sub	w8, w8, #0x3b
0x2519dee60:	ldr	x21, [x19, w8, sxtw #3]
0x2519dee64:	str	x0, [x21, #-4]!
0x2519dee68:	ldr	w8, [x27]
0x2519dee6c:	ldr	w9, [x23]
0x2519dee70:	sub	w8, w9, w8
0x2519dee74:	eor	w8, w8, w22
0x2519dee78:	mul	w8, w8, w20
0x2519dee7c:	ldp	x26, x25, [sp, #0x160]
0x2519dee80:	add	x9, x25, w8, uxtb
0x2519dee84:	ldrb	w9, [x9]
0x2519dee88:	mov	w10, #0xc4
0x2519dee8c:	eor	w9, w9, w10
0x2519dee90:	ldrb	w9, [x26, w9, uxtw]
0x2519dee94:	eor	w8, w8, w9
0x2519dee98:	and	w8, w8, #0xff
0x2519dee9c:	add	w8, w8, #0x3e0
0x2519deea0:	ldr	x8, [x28, w8, uxtw #3]
0x2519deea4:	mov	w1, #0xa2
0x2519deea8:	mov	w2, #0xc
0x2519deeac:	mov	x17, #0x1b49
0x2519deeb0:	blraa	x8, x17
0x2519deeb4:	ldr	w8, [x27]
0x2519deeb8:	ldr	w9, [x23]
0x2519deebc:	eor	w8, w8, w22
0x2519deec0:	eor	w8, w8, w9
0x2519deec4:	mul	w8, w8, w20
0x2519deec8:	ldr	x9, [sp, #0x158]
0x2519deecc:	add	x9, x9, w8, uxtb
0x2519deed0:	ldrb	w9, [x9]
0x2519deed4:	mov	w10, #0x1a
0x2519deed8:	eor	w9, w9, w10
0x2519deedc:	ldr	x10, [sp, #0x150]
0x2519deee0:	ldrb	w9, [x10, w9, uxtw]
0x2519deee4:	eor	w8, w8, w9
0x2519deee8:	and	w8, w8, #0xff
0x2519deeec:	add	w8, w8, #0x362
0x2519deef0:	ldr	x8, [x28, w8, uxtw #3]
0x2519deef4:	mov	w0, #0x2c
0x2519deef8:	mov	x17, #0xaa22
0x2519deefc:	blraa	x8, x17
0x2519def00:	ldr	w8, [x27]
0x2519def04:	ldr	w9, [x23]
0x2519def08:	add	w8, w9, w8
0x2519def0c:	eor	w8, w8, w22
0x2519def10:	mov	w10, #0x1f79
0x2519def14:	movk	w10, #0xd3ef, lsl #16
0x2519def18:	mul	w8, w8, w10
0x2519def1c:	mov	x12, x25
0x2519def20:	add	x9, x25, w8, uxtb
0x2519def24:	ldrb	w9, [x9]
0x2519def28:	mov	w11, #0x69
0x2519def2c:	eor	w9, w9, w11
0x2519def30:	ldrb	w9, [x26, w9, uxtw]
0x2519def34:	eor	w8, w8, w9
0x2519def38:	and	w8, w8, #0xff
0x2519def3c:	sub	w8, w8, #0xcb
0x2519def40:	ldr	x20, [x19, w8, sxtw #3]
0x2519def44:	str	x0, [x20]
0x2519def48:	ldr	w8, [x27]
0x2519def4c:	ldr	w9, [x23]
0x2519def50:	add	w8, w9, w8
0x2519def54:	eor	w8, w8, w22
0x2519def58:	mul	w8, w8, w10
0x2519def5c:	mov	w25, #0x1f79
0x2519def60:	movk	w25, #0xd3ef, lsl #16
0x2519def64:	add	x9, x12, w8, uxtb
0x2519def68:	ldrb	w9, [x9]
0x2519def6c:	mov	w10, #0xc4
0x2519def70:	eor	w9, w9, w10
0x2519def74:	ldrb	w9, [x26, w9, uxtw]
0x2519def78:	eor	w8, w8, w9
0x2519def7c:	and	w8, w8, #0xff
0x2519def80:	add	w8, w8, #0x3e0
0x2519def84:	ldr	x8, [x28, w8, uxtw #3]
0x2519def88:	mov	w1, #0x78
0x2519def8c:	mov	w2, #0x2c
0x2519def90:	mov	x17, #0x1b49
0x2519def94:	blraa	x8, x17
0x2519def98:	str	x21, [sp, #0x110]
0x2519def9c:	ldr	x8, [x21]
0x2519defa0:	str	wzr, [x8, #8]
0x2519defa4:	ldr	x8, [x20]
0x2519defa8:	str	wzr, [x8, #8]
0x2519defac:	ldr	x9, [x21]
0x2519defb0:	ldr	x8, [sp, #0x50]
0x2519defb4:	ldur	x12, [x8, #-4]
0x2519defb8:	ldr	x0, [x20]
0x2519defbc:	mov	x21, x20
0x2519defc0:	str	x20, [sp, #0x130]
0x2519defc4:	mov	w10, #0x33
0x2519defc8:	strb	w10, [x9]
0x2519defcc:	ldr	w10, [x27]
0x2519defd0:	ldr	w11, [x23]
0x2519defd4:	add	w10, w11, w10
0x2519defd8:	eor	w10, w10, w22
0x2519defdc:	mul	w10, w10, w25
0x2519defe0:	ldp	x1, x5, [sp, #0x140]
0x2519defe4:	add	x11, x5, w10, uxtb
0x2519defe8:	ldrb	w11, [x11]
0x2519defec:	mov	w13, #0x3b
0x2519deff0:	eor	w11, w11, w13
0x2519deff4:	mov	w30, #0x3b
0x2519deff8:	ldrb	w11, [x1, w11, uxtw]
0x2519deffc:	eor	w10, w10, w11
0x2519df000:	and	w10, w10, #0xff
0x2519df004:	sub	w10, w10, #0x73
0x2519df008:	ldr	x11, [x19, w10, sxtw #3]
0x2519df00c:	str	x11, [sp, #0xf8]
0x2519df010:	mov	w10, #0xd5
0x2519df014:	strb	w10, [x11]
0x2519df018:	mov	w14, #1
0x2519df01c:	strb	w14, [x12]
0x2519df020:	ldr	w10, [x27]
0x2519df024:	ldr	w11, [x23]
0x2519df028:	eor	w10, w10, w22
0x2519df02c:	eor	w10, w10, w11
0x2519df030:	mul	w10, w10, w25
0x2519df034:	ldp	x17, x16, [sp, #0x100]
0x2519df038:	add	x11, x17, w10, uxtb
0x2519df03c:	ldrb	w11, [x11]
0x2519df040:	mov	w13, #0x7d
0x2519df044:	eor	w11, w11, w13
0x2519df048:	ldrb	w11, [x16, w11, uxtw]
0x2519df04c:	eor	w10, w10, w11
0x2519df050:	and	w10, w10, #0xff
0x2519df054:	add	w10, w10, #0x49
0x2519df058:	ldr	x10, [x19, w10, uxtw #3]
0x2519df05c:	str	x10, [sp, #0xa8]
0x2519df060:	mov	w11, #0xde
0x2519df064:	strb	w11, [x10]
0x2519df068:	ldr	w10, [x27]
0x2519df06c:	ldr	w13, [x23]
0x2519df070:	add	w10, w13, w10
0x2519df074:	eor	w10, w10, w22
0x2519df078:	mul	w10, w10, w25
0x2519df07c:	ldp	x6, x20, [sp, #0x150]
0x2519df080:	add	x13, x20, w10, uxtb
0x2519df084:	ldrb	w13, [x13]
0x2519df088:	mov	w15, #0x9f
0x2519df08c:	eor	w13, w13, w15
0x2519df090:	ldrb	w13, [x6, w13, uxtw]
0x2519df094:	eor	w10, w10, w13
0x2519df098:	and	w10, w10, #0xff
0x2519df09c:	add	w10, w10, #0x2b
0x2519df0a0:	ldr	x10, [x19, w10, uxtw #3]
0x2519df0a4:	str	x10, [sp, #0xe0]
0x2519df0a8:	strb	w14, [x10]
0x2519df0ac:	ldr	w10, [x27]
0x2519df0b0:	ldr	w13, [x23]
0x2519df0b4:	sub	w10, w13, w10
0x2519df0b8:	eor	w10, w10, w22
0x2519df0bc:	mul	w10, w10, w25
0x2519df0c0:	add	x13, x20, w10, uxtb
0x2519df0c4:	ldrb	w13, [x13]
0x2519df0c8:	eor	w13, w13, w15
0x2519df0cc:	ldrb	w13, [x6, w13, uxtw]
0x2519df0d0:	eor	w10, w10, w13
0x2519df0d4:	and	w10, w10, #0xff
0x2519df0d8:	sub	w10, w10, #0x29
0x2519df0dc:	ldr	x13, [x19, w10, sxtw #3]
0x2519df0e0:	str	x13, [sp, #0x60]
0x2519df0e4:	mov	w10, #0xbb
0x2519df0e8:	strb	w10, [x13]
0x2519df0ec:	mov	w10, #0x60
0x2519df0f0:	strb	w10, [x12, #1]
0x2519df0f4:	ldr	w10, [x27]
0x2519df0f8:	ldr	w13, [x23]
0x2519df0fc:	sub	w10, w13, w10
0x2519df100:	eor	w10, w10, w22
0x2519df104:	mul	w10, w10, w25
0x2519df108:	ldp	x7, x3, [sp, #0x120]
0x2519df10c:	add	x13, x3, w10, uxtb
0x2519df110:	ldrb	w13, [x13]
0x2519df114:	mov	w8, #0x4a
0x2519df118:	eor	w13, w13, w8
0x2519df11c:	ldrb	w13, [x7, w13, uxtw]
0x2519df120:	eor	w10, w10, w13
0x2519df124:	and	w10, w10, #0xff
0x2519df128:	add	w10, w10, #0x41
0x2519df12c:	ldr	x10, [x19, w10, uxtw #3]
0x2519df130:	str	x10, [sp, #0x88]
0x2519df134:	strb	wzr, [x10]
0x2519df138:	ldr	w10, [x27]
0x2519df13c:	ldr	w13, [x23]
0x2519df140:	sub	w10, w13, w10
0x2519df144:	eor	w10, w10, w22
0x2519df148:	mul	w10, w10, w25
0x2519df14c:	add	x13, x17, w10, uxtb
0x2519df150:	ldrb	w15, [x13]
0x2519df154:	mov	w13, #0xb9
0x2519df158:	eor	w15, w15, w13
0x2519df15c:	mov	w2, #0xb9
0x2519df160:	mov	x13, x16
0x2519df164:	ldrb	w15, [x16, w15, uxtw]
0x2519df168:	eor	w10, w10, w15
0x2519df16c:	and	w10, w10, #0xff
0x2519df170:	add	w10, w10, #0x35
0x2519df174:	ldr	x15, [x19, w10, uxtw #3]
0x2519df178:	str	x15, [sp, #0x68]
0x2519df17c:	mov	w10, #0xcf
0x2519df180:	strb	w10, [x15]
0x2519df184:	mov	w15, #0x2f
0x2519df188:	strb	w15, [x0, #0x12]
0x2519df18c:	mov	w15, #0x4f
0x2519df190:	strb	w15, [x0, #7]
0x2519df194:	mov	w15, #0xc5
0x2519df198:	strb	w15, [x9, #7]
0x2519df19c:	ldr	w15, [x27]
0x2519df1a0:	ldr	w16, [x23]
0x2519df1a4:	sub	w15, w16, w15
0x2519df1a8:	eor	w15, w15, w22
0x2519df1ac:	mul	w15, w15, w25
0x2519df1b0:	ldr	x8, [sp, #0x168]
0x2519df1b4:	add	x16, x8, w15, uxtb
0x2519df1b8:	ldrb	w16, [x16]
0x2519df1bc:	mov	w11, #0x73
0x2519df1c0:	eor	w16, w16, w11
0x2519df1c4:	ldrb	w16, [x26, w16, uxtw]
0x2519df1c8:	eor	w15, w15, w16
0x2519df1cc:	and	w15, w15, #0xff
0x2519df1d0:	sub	w15, w15, #0x2d
0x2519df1d4:	ldr	x16, [x19, w15, sxtw #3]
0x2519df1d8:	str	x16, [sp, #0xb0]
0x2519df1dc:	mov	w15, #0x32
0x2519df1e0:	strb	w15, [x16]
0x2519df1e4:	mov	w4, #0x1a
0x2519df1e8:	strb	w4, [x9, #6]
0x2519df1ec:	ldr	w15, [x27]
0x2519df1f0:	eor	w15, w15, w22
0x2519df1f4:	ldr	w16, [x23]
0x2519df1f8:	eor	w15, w15, w16
0x2519df1fc:	mul	w15, w15, w25
0x2519df200:	add	x16, x17, w15, uxtb
0x2519df204:	ldrb	w16, [x16]
0x2519df208:	mov	w10, #0xb4
0x2519df20c:	eor	w16, w16, w10
0x2519df210:	ldrb	w16, [x13, w16, uxtw]
0x2519df214:	mov	x10, x13
0x2519df218:	eor	w15, w15, w16
0x2519df21c:	and	w15, w15, #0xff
0x2519df220:	sub	w15, w15, #0x63
0x2519df224:	ldr	x15, [x19, w15, sxtw #3]
0x2519df228:	str	x15, [sp, #0x78]
0x2519df22c:	strb	w14, [x15]
0x2519df230:	mov	w14, #0x27
0x2519df234:	strb	w14, [x9, #5]
0x2519df238:	ldr	w14, [x27]
0x2519df23c:	ldr	w15, [x23]
0x2519df240:	sub	w14, w15, w14
0x2519df244:	eor	w14, w14, w22
0x2519df248:	mul	w14, w14, w25
0x2519df24c:	add	x15, x5, w14, uxtb
0x2519df250:	ldrb	w15, [x15]
0x2519df254:	eor	w15, w15, w30
0x2519df258:	ldrb	w15, [x1, w15, uxtw]
0x2519df25c:	eor	w14, w14, w15
0x2519df260:	and	w14, w14, #0xff
0x2519df264:	add	w14, w14, #0x2e
0x2519df268:	ldr	x15, [x19, w14, uxtw #3]
0x2519df26c:	str	x15, [sp, #0xd8]
0x2519df270:	mov	w14, #0x91
0x2519df274:	strb	w14, [x15]
0x2519df278:	mov	w14, #0x11
0x2519df27c:	strb	w14, [x0, #0xc]
0x2519df280:	mov	w14, #0x36
0x2519df284:	strb	w14, [x9, #2]
0x2519df288:	mov	w13, #0x66
0x2519df28c:	strb	w13, [x0, #0x22]
0x2519df290:	ldr	w14, [x27]
0x2519df294:	ldr	w15, [x23]
0x2519df298:	sub	w14, w15, w14
0x2519df29c:	eor	w14, w14, w22
0x2519df2a0:	mul	w14, w14, w25
0x2519df2a4:	add	x15, x17, w14, uxtb
0x2519df2a8:	ldrb	w15, [x15]
0x2519df2ac:	eor	w15, w15, w2
0x2519df2b0:	ldrb	w15, [x10, w15, uxtw]
0x2519df2b4:	eor	w14, w14, w15
0x2519df2b8:	and	w14, w14, #0xff
0x2519df2bc:	add	w14, w14, #0x57
0x2519df2c0:	ldr	x14, [x19, w14, uxtw #3]
0x2519df2c4:	str	x14, [sp, #0xf0]
0x2519df2c8:	mov	w13, #0xaa
0x2519df2cc:	strb	w13, [x14]
0x2519df2d0:	ldr	w14, [x27]
0x2519df2d4:	ldr	w15, [x23]
0x2519df2d8:	sub	w14, w15, w14
0x2519df2dc:	eor	w14, w14, w22
0x2519df2e0:	mul	w14, w14, w25
0x2519df2e4:	add	x15, x8, w14, uxtb
0x2519df2e8:	ldrb	w15, [x15]
0x2519df2ec:	mov	w13, #0x69
0x2519df2f0:	eor	w15, w15, w13
0x2519df2f4:	ldrb	w15, [x26, w15, uxtw]
0x2519df2f8:	eor	w14, w14, w15
0x2519df2fc:	and	w14, w14, #0xff
0x2519df300:	sub	w14, w14, #0xa5
0x2519df304:	ldr	x14, [x19, w14, sxtw #3]
0x2519df308:	str	x14, [sp, #0xc0]
0x2519df30c:	strb	w11, [x14]
0x2519df310:	mov	w14, #0xcc
0x2519df314:	strb	w14, [x0, #0x21]
0x2519df318:	ldr	w14, [x27]
0x2519df31c:	ldr	w15, [x23]
0x2519df320:	add	w14, w15, w14
0x2519df324:	eor	w14, w14, w22
0x2519df328:	mul	w14, w14, w25
0x2519df32c:	add	x15, x20, w14, uxtb
0x2519df330:	ldrb	w15, [x15]
0x2519df334:	eor	w15, w15, w4
0x2519df338:	mov	w30, #0x1a
0x2519df33c:	ldrb	w15, [x6, w15, uxtw]
0x2519df340:	eor	w14, w14, w15
0x2519df344:	and	w14, w14, #0xff
0x2519df348:	sub	w14, w14, #0x76
0x2519df34c:	ldr	x15, [x19, w14, sxtw #3]
0x2519df350:	str	x15, [sp, #0xe8]
0x2519df354:	mov	w14, #0x18
0x2519df358:	strb	w14, [x15]
0x2519df35c:	mov	w14, #0x8f
0x2519df360:	strb	w14, [x9, #1]
0x2519df364:	ldr	w14, [x27]
0x2519df368:	eor	w14, w14, w22
0x2519df36c:	ldr	w15, [x23]
0x2519df370:	eor	w14, w14, w15
0x2519df374:	mul	w14, w14, w25
0x2519df378:	add	x15, x8, w14, uxtb
0x2519df37c:	ldrb	w15, [x15]
0x2519df380:	eor	w15, w15, w11
0x2519df384:	ldrb	w15, [x26, w15, uxtw]
0x2519df388:	eor	w14, w14, w15
0x2519df38c:	and	w14, w14, #0xff
0x2519df390:	add	w14, w14, #0x9b
0x2519df394:	ldr	x14, [x19, w14, uxtw #3]
0x2519df398:	str	x14, [sp, #0x90]
0x2519df39c:	mov	w26, #0xf1
0x2519df3a0:	strb	w26, [x14]
0x2519df3a4:	ldr	w14, [x27]
0x2519df3a8:	ldr	w15, [x23]
0x2519df3ac:	sub	w14, w15, w14
0x2519df3b0:	eor	w14, w14, w22
0x2519df3b4:	mul	w14, w14, w25
0x2519df3b8:	add	x15, x3, w14, uxtb
0x2519df3bc:	mov	x16, x3
0x2519df3c0:	ldrb	w15, [x15]
0x2519df3c4:	mov	w4, #0xcd
0x2519df3c8:	eor	w15, w15, w4
0x2519df3cc:	ldrb	w15, [x7, w15, uxtw]
0x2519df3d0:	eor	w14, w14, w15
0x2519df3d4:	and	w14, w14, #0xff
0x2519df3d8:	sub	w14, w14, #0x1f
0x2519df3dc:	ldr	x15, [x19, w14, sxtw #3]
0x2519df3e0:	str	x15, [sp, #0xb8]
0x2519df3e4:	mov	w14, #0x8d
0x2519df3e8:	strb	w14, [x15]
0x2519df3ec:	mov	w13, #0x19
0x2519df3f0:	strb	w13, [x9, #3]
0x2519df3f4:	mov	w14, #0x44
0x2519df3f8:	strb	w14, [x12, #2]
0x2519df3fc:	ldr	w12, [x27]
0x2519df400:	ldr	w14, [x23]
0x2519df404:	sub	w12, w14, w12
0x2519df408:	eor	w12, w12, w22
0x2519df40c:	mul	w12, w12, w25
0x2519df410:	add	x14, x17, w12, uxtb
0x2519df414:	ldrb	w14, [x14]
0x2519df418:	eor	w14, w14, #0x18
0x2519df41c:	ldrb	w14, [x10, w14, uxtw]
0x2519df420:	eor	w12, w12, w14
0x2519df424:	and	w12, w12, #0xff
0x2519df428:	sub	w12, w12, #0x13
0x2519df42c:	ldr	x13, [x19, w12, sxtw #3]
0x2519df430:	str	x13, [sp, #0x98]
0x2519df434:	mov	w12, #0x35
0x2519df438:	strb	w12, [x13]
0x2519df43c:	ldr	w12, [x27]
0x2519df440:	eor	w12, w12, w22
0x2519df444:	ldr	w14, [x23]
0x2519df448:	eor	w12, w12, w14
0x2519df44c:	mul	w12, w12, w25
0x2519df450:	add	x14, x17, w12, uxtb
0x2519df454:	ldrb	w14, [x14]
0x2519df458:	eor	w14, w14, #0x18
0x2519df45c:	ldrb	w14, [x10, w14, uxtw]
0x2519df460:	mov	x3, x10
0x2519df464:	eor	w12, w12, w14
0x2519df468:	and	w12, w12, #0xff
0x2519df46c:	add	w12, w12, #0x6a
0x2519df470:	ldr	x14, [x19, w12, uxtw #3]
0x2519df474:	str	x14, [sp, #0x58]
0x2519df478:	mov	w12, #0x77
0x2519df47c:	strb	w12, [x14]
0x2519df480:	ldr	w12, [x27]
0x2519df484:	ldr	w14, [x23]
0x2519df488:	add	w12, w14, w12
0x2519df48c:	eor	w12, w12, w22
0x2519df490:	mul	w12, w12, w25
0x2519df494:	add	x14, x5, w12, uxtb
0x2519df498:	ldrb	w14, [x14]
0x2519df49c:	mov	w15, #0x6a
0x2519df4a0:	eor	w14, w14, w15
0x2519df4a4:	ldrb	w14, [x1, w14, uxtw]
0x2519df4a8:	eor	w12, w12, w14
0x2519df4ac:	and	w12, w12, #0xff
0x2519df4b0:	sub	w12, w12, #0x1d
0x2519df4b4:	ldr	x14, [x19, w12, sxtw #3]
0x2519df4b8:	str	x14, [sp, #0x80]
0x2519df4bc:	mov	w12, #0x15
0x2519df4c0:	strb	w12, [x14]
0x2519df4c4:	mov	w10, #0xde
0x2519df4c8:	strb	w10, [x0, #3]
0x2519df4cc:	ldr	w11, [x27]
0x2519df4d0:	eor	w11, w11, w22
0x2519df4d4:	ldr	w12, [x23]
0x2519df4d8:	eor	w11, w11, w12
0x2519df4dc:	mov	w13, #0x1f79
0x2519df4e0:	movk	w13, #0xd3ef, lsl #16
0x2519df4e4:	mul	w11, w11, w13
0x2519df4e8:	add	x12, x17, w11, uxtb
0x2519df4ec:	ldrb	w12, [x12]
0x2519df4f0:	eor	w12, w12, #0x18
0x2519df4f4:	ldrb	w12, [x3, w12, uxtw]
0x2519df4f8:	eor	w11, w11, w12
0x2519df4fc:	and	w11, w11, #0xff
0x2519df500:	add	w11, w11, #9
0x2519df504:	ldr	x12, [x19, w11, uxtw #3]
0x2519df508:	str	x12, [sp, #0xa0]
0x2519df50c:	mov	w11, #0x85
0x2519df510:	strb	w11, [x12]
0x2519df514:	ldr	w11, [x27]
0x2519df518:	ldr	w12, [x23]
0x2519df51c:	add	w11, w12, w11
0x2519df520:	eor	w11, w11, w22
0x2519df524:	mul	w11, w11, w13
0x2519df528:	mov	w13, #0x1f79
0x2519df52c:	movk	w13, #0xd3ef, lsl #16
0x2519df530:	ldp	x14, x12, [sp, #0xc8]
0x2519df534:	add	x12, x12, w11, uxtb
0x2519df538:	ldrb	w12, [x12]
0x2519df53c:	eor	w12, w12, #0xfe
0x2519df540:	ldrb	w12, [x14, w12, uxtw]
0x2519df544:	eor	w11, w11, w12
0x2519df548:	and	w11, w11, #0xff
0x2519df54c:	sub	w11, w11, #0xc7
0x2519df550:	ldr	x11, [x19, w11, sxtw #3]
0x2519df554:	str	x11, [sp, #0x70]
0x2519df558:	mov	w25, #0xa4
0x2519df55c:	strb	w25, [x11]
0x2519df560:	mov	w11, #0xb0
0x2519df564:	strb	w11, [x9, #4]
0x2519df568:	ldr	w9, [x27]
0x2519df56c:	eor	w9, w9, w22
0x2519df570:	ldr	w11, [x23]
0x2519df574:	eor	w9, w9, w11
0x2519df578:	mul	w9, w9, w13
0x2519df57c:	add	x11, x17, w9, uxtb
0x2519df580:	ldrb	w11, [x11]
0x2519df584:	mov	w8, #0xb4
0x2519df588:	eor	w11, w11, w8
0x2519df58c:	ldrb	w11, [x3, w11, uxtw]
0x2519df590:	eor	w9, w9, w11
0x2519df594:	and	w9, w9, #0xff
0x2519df598:	add	w9, w9, #0x30
0x2519df59c:	ldr	x11, [x19, w9, uxtw #3]
0x2519df5a0:	str	x11, [sp, #0xd0]
0x2519df5a4:	mov	w9, #0xbd
0x2519df5a8:	strb	w9, [x11]
0x2519df5ac:	mov	w9, #0xd4
0x2519df5b0:	strb	w9, [x0, #0x20]
0x2519df5b4:	mov	w9, #0x87
0x2519df5b8:	strb	w9, [x0, #0x19]
0x2519df5bc:	mov	w9, #0xb8
0x2519df5c0:	strb	w9, [x0, #6]
0x2519df5c4:	ldr	x8, [x21]
0x2519df5c8:	mov	w9, #0x1f
0x2519df5cc:	strb	w9, [x8, #2]
0x2519df5d0:	mov	w9, #0xa9
0x2519df5d4:	strb	w9, [x8, #0x14]
0x2519df5d8:	ldr	w9, [x27]
0x2519df5dc:	ldr	w11, [x23]
0x2519df5e0:	sub	w9, w11, w9
0x2519df5e4:	eor	w9, w9, w22
0x2519df5e8:	mul	w9, w9, w13
0x2519df5ec:	add	x11, x20, w9, uxtb
0x2519df5f0:	ldrb	w11, [x11]
0x2519df5f4:	eor	w11, w11, w30
0x2519df5f8:	ldrb	w11, [x6, w11, uxtw]
0x2519df5fc:	eor	w9, w9, w11
0x2519df600:	and	w9, w9, #0xff
0x2519df604:	sub	w9, w9, #0x44
0x2519df608:	ldr	x11, [x19, w9, sxtw #3]
0x2519df60c:	mov	w9, #0x75
0x2519df610:	str	x11, [sp, #0x40]
0x2519df614:	strb	w9, [x11]
0x2519df618:	ldr	w9, [x27]
0x2519df61c:	ldr	w11, [x23]
0x2519df620:	add	w9, w11, w9
0x2519df624:	eor	w9, w9, w22
0x2519df628:	mul	w9, w9, w13
0x2519df62c:	add	x11, x5, w9, uxtb
0x2519df630:	ldrb	w11, [x11]
0x2519df634:	mov	w15, #0x3b
0x2519df638:	eor	w11, w11, w15
0x2519df63c:	ldrb	w11, [x1, w11, uxtw]
0x2519df640:	eor	w9, w9, w11
0x2519df644:	and	w9, w9, #0xff
0x2519df648:	sub	w9, w9, #0x2e
0x2519df64c:	ldr	x9, [x19, w9, sxtw #3]
0x2519df650:	mov	w11, #0x14
0x2519df654:	str	x9, [sp, #0x48]
0x2519df658:	strb	w11, [x9]
0x2519df65c:	ldr	w9, [x27]
0x2519df660:	ldr	w11, [x23]
0x2519df664:	add	w9, w11, w9
0x2519df668:	eor	w9, w9, w22
0x2519df66c:	mul	w9, w9, w13
0x2519df670:	add	x11, x17, w9, uxtb
0x2519df674:	ldrb	w11, [x11]
0x2519df678:	mov	w10, #0xb9
0x2519df67c:	eor	w11, w11, w10
0x2519df680:	mov	w20, #0xb9
0x2519df684:	ldrb	w11, [x3, w11, uxtw]
0x2519df688:	eor	w9, w9, w11
0x2519df68c:	and	w9, w9, #0xff
0x2519df690:	add	w9, w9, #0x2e
0x2519df694:	ldr	x9, [x19, w9, uxtw #3]
0x2519df698:	mov	w11, #0x65
0x2519df69c:	str	x9, [sp, #0x38]
0x2519df6a0:	strb	w11, [x9]
0x2519df6a4:	strb	w24, [x8, #0x10]
0x2519df6a8:	mov	w9, #0x2d
0x2519df6ac:	strb	w9, [x8, #5]
0x2519df6b0:	ldr	w9, [x27]
0x2519df6b4:	eor	w9, w9, w22
0x2519df6b8:	ldr	w11, [x23]
0x2519df6bc:	eor	w9, w9, w11
0x2519df6c0:	mul	w9, w9, w13
0x2519df6c4:	add	x11, x17, w9, uxtb
0x2519df6c8:	ldrb	w11, [x11]
0x2519df6cc:	mov	w2, #0xb3
0x2519df6d0:	eor	w11, w11, w2
0x2519df6d4:	ldrb	w11, [x3, w11, uxtw]
0x2519df6d8:	eor	w9, w9, w11
0x2519df6dc:	and	w9, w9, #0xff
0x2519df6e0:	add	w9, w9, #0x13
0x2519df6e4:	ldr	x11, [x19, w9, uxtw #3]
0x2519df6e8:	mov	w14, #0x20
0x2519df6ec:	str	x11, [sp, #0x118]
0x2519df6f0:	strb	w14, [x11]
0x2519df6f4:	ldr	w11, [x27]
0x2519df6f8:	ldr	w12, [x23]
0x2519df6fc:	add	w11, w12, w11
0x2519df700:	eor	w11, w11, w22
0x2519df704:	mul	w11, w11, w13
0x2519df708:	add	x12, x17, w11, uxtb
0x2519df70c:	ldrb	w12, [x12]
0x2519df710:	eor	w12, w12, w2
0x2519df714:	mov	w9, #0xb3
0x2519df718:	ldrb	w12, [x3, w12, uxtw]
0x2519df71c:	eor	w11, w11, w12
0x2519df720:	and	w11, w11, #0xff
0x2519df724:	sub	w11, w11, #0x29
0x2519df728:	ldr	x11, [x19, w11, sxtw #3]
0x2519df72c:	str	x11, [sp, #0x28]
0x2519df730:	mov	w10, #0xcf
0x2519df734:	strb	w10, [x11]
0x2519df738:	ldr	w10, [x27]
0x2519df73c:	ldr	w11, [x23]
0x2519df740:	sub	w10, w11, w10
0x2519df744:	eor	w10, w10, w22
0x2519df748:	mul	w10, w10, w13
0x2519df74c:	add	x11, x16, w10, uxtb
0x2519df750:	mov	x6, x16
0x2519df754:	ldrb	w11, [x11]
0x2519df758:	eor	w11, w11, w4
0x2519df75c:	mov	w2, #0xcd
0x2519df760:	ldrb	w11, [x7, w11, uxtw]
0x2519df764:	eor	w10, w10, w11
0x2519df768:	and	w10, w10, #0xff
0x2519df76c:	sub	w10, w10, #0x7d
0x2519df770:	ldr	x11, [x19, w10, sxtw #3]
0x2519df774:	mov	w10, #0xfa
0x2519df778:	str	x11, [sp, #0x20]
0x2519df77c:	strb	w10, [x11]
0x2519df780:	ldr	w10, [x27]
0x2519df784:	ldr	w11, [x23]
0x2519df788:	add	w10, w11, w10
0x2519df78c:	eor	w10, w10, w22
0x2519df790:	mul	w10, w10, w13
0x2519df794:	add	x11, x5, w10, uxtb
0x2519df798:	ldrb	w11, [x11]
0x2519df79c:	eor	w11, w11, w15
0x2519df7a0:	ldrb	w11, [x1, w11, uxtw]
0x2519df7a4:	eor	w10, w10, w11
0x2519df7a8:	and	w10, w10, #0xff
0x2519df7ac:	sub	w10, w10, #0x1d
0x2519df7b0:	ldr	x11, [x19, w10, sxtw #3]
0x2519df7b4:	mov	w10, #0xdd
0x2519df7b8:	str	x11, [sp, #0x30]
0x2519df7bc:	strb	w10, [x11]
0x2519df7c0:	mov	w10, #0x4d
0x2519df7c4:	strb	w10, [x8, #4]
0x2519df7c8:	mov	w10, #0xd
0x2519df7cc:	strb	w10, [x8, #0x24]
0x2519df7d0:	mov	w24, #0xd9
0x2519df7d4:	strb	w24, [x8]
0x2519df7d8:	ldr	w10, [x27]
0x2519df7dc:	ldr	w11, [x23]
0x2519df7e0:	sub	w10, w11, w10
0x2519df7e4:	eor	w10, w10, w22
0x2519df7e8:	mul	w11, w10, w13
0x2519df7ec:	add	x10, x17, w11, uxtb
0x2519df7f0:	ldrb	w10, [x10]
0x2519df7f4:	eor	w10, w10, w9
0x2519df7f8:	ldrb	w10, [x3, w10, uxtw]
0x2519df7fc:	str	wzr, [sp, #0x170]
0x2519df800:	eor	w10, w11, w10
0x2519df804:	and	w10, w10, #0xff
0x2519df808:	sub	w10, w10, #0x6f
0x2519df80c:	ldr	x10, [x19, w10, sxtw #3]
0x2519df810:	mov	w9, #0x71
0x2519df814:	str	x10, [sp, #0x18]
0x2519df818:	strb	w9, [x10]
0x2519df81c:	mov	w10, #0xef
0x2519df820:	strb	w10, [x8, #0x13]
0x2519df824:	strb	w24, [x8, #0x1d]
0x2519df828:	mov	w10, #0x22
0x2519df82c:	strb	w10, [x8, #0xd]
0x2519df830:	mov	w10, #0x49
0x2519df834:	strb	w10, [x8, #0x1f]
0x2519df838:	strb	w14, [x8, #1]
0x2519df83c:	mov	w9, #0xf0
0x2519df840:	strb	w9, [x8, #0x25]
0x2519df844:	strb	w25, [x8, #0x1b]
0x2519df848:	strb	w26, [x8, #0x26]
0x2519df84c:	strb	w26, [x8, #0x28]
0x2519df850:	strb	w26, [x8, #0x17]
0x2519df854:	mov	w0, #0x48
0x2519df858:	strb	w0, [x8, #0x1a]
0x2519df85c:	mov	w12, #0x42
0x2519df860:	strb	w12, [x8, #0x15]
0x2519df864:	ldr	w9, [x27]
0x2519df868:	ldr	w10, [x23]
0x2519df86c:	sub	w9, w10, w9
0x2519df870:	eor	w9, w9, w22
0x2519df874:	mul	w9, w9, w13
0x2519df878:	add	x10, x17, w9, uxtb
0x2519df87c:	ldrb	w10, [x10]
0x2519df880:	eor	w10, w10, w20
0x2519df884:	ldrb	w10, [x3, w10, uxtw]
0x2519df888:	eor	w9, w9, w10
0x2519df88c:	and	w9, w9, #0xff
0x2519df890:	sub	w9, w9, #0x26
0x2519df894:	ldr	x10, [x19, w9, sxtw #3]
0x2519df898:	mov	w9, #0xf7
0x2519df89c:	str	x10, [sp, #0xc8]
0x2519df8a0:	strb	w9, [x10]
0x2519df8a4:	mov	w9, #0xdf
0x2519df8a8:	strb	w9, [x8, #0x27]
0x2519df8ac:	mov	w9, #0x69
0x2519df8b0:	strb	w9, [x8, #0x29]
0x2519df8b4:	mov	w9, #0x97
0x2519df8b8:	strb	w9, [x8, #0x2a]
0x2519df8bc:	strb	w9, [x8, #0x2b]
0x2519df8c0:	mov	w9, #0x89
0x2519df8c4:	strb	w9, [x8, #0x1e]
0x2519df8c8:	mov	w9, #0xf
0x2519df8cc:	strb	w9, [x8, #0x16]
0x2519df8d0:	mov	w9, #0xb8
0x2519df8d4:	strb	w9, [x8, #0x18]
0x2519df8d8:	mov	w9, #0x78
0x2519df8dc:	strb	w9, [x8, #0x1c]
0x2519df8e0:	mov	w9, #0x87
0x2519df8e4:	strb	w9, [x8, #0xe]
0x2519df8e8:	mov	w9, #0xaa
0x2519df8ec:	strb	w9, [x8, #0x23]
0x2519df8f0:	mov	w9, #0x4f
0x2519df8f4:	strb	w9, [x8, #0x11]
0x2519df8f8:	mov	w9, #0x3a
0x2519df8fc:	strb	w9, [x8, #0xf]
0x2519df900:	ldr	x8, [sp, #0x50]
0x2519df904:	ldur	x24, [x8, #-4]
0x2519df908:	ldrb	w8, [x24]
0x2519df90c:	lsl	x9, x8, #1
0x2519df910:	and	x9, x9, #0x1fc
0x2519df914:	sub	x8, x8, x9
0x2519df918:	mov	x9, #0x6dfe0000
0x2519df91c:	movk	x9, #0xabfa, lsl #32
0x2519df920:	movk	x9, #0x5fc, lsl #48
0x2519df924:	add	x15, x9, x8, lsl #16
0x2519df928:	mov	w8, #0x130
0x2519df92c:	ldr	x9, [sp, #0x110]
0x2519df930:	ldr	x26, [x9]
0x2519df934:	ldrb	w9, [x26]
0x2519df938:	and	x8, x8, x9, lsl #1
0x2519df93c:	sub	x8, x9, x8
0x2519df940:	mov	x9, #0x9800
0x2519df944:	movk	x9, #0x4985, lsl #16
0x2519df948:	movk	x9, #0x3add, lsl #32
0x2519df94c:	movk	x9, #0xbe11, lsl #48
0x2519df950:	add	x16, x9, x8, lsl #8
0x2519df954:	ldrb	w8, [x24, #2]
0x2519df958:	lsl	w9, w8, #1
0x2519df95c:	and	w9, w9, #0xfc
0x2519df960:	sub	w8, w8, w9
0x2519df964:	add	w8, w8, #0xa
0x2519df968:	ldr	x9, [sp, #0x138]
0x2519df96c:	orr	x8, x9, x8, lsl #56
0x2519df970:	mov	x9, #0x2d9a0000
0x2519df974:	movk	x9, #0x8082, lsl #32
0x2519df978:	movk	x9, #0xcc, lsl #48
0x2519df97c:	and	x9, x15, x9
0x2519df980:	add	x8, x8, x9
0x2519df984:	str	x8, [sp, #0x160]
0x2519df988:	mov	w8, #0x3142
0x2519df98c:	movk	w8, #0x133a, lsl #16
0x2519df990:	ldr	w30, [x26, #8]
0x2519df994:	eor	w8, w30, w8
0x2519df998:	mov	w10, #0xe203
0x2519df99c:	movk	w10, #0xe4a, lsl #16
0x2519df9a0:	add	w8, w8, w10
0x2519df9a4:	mov	w10, #0xbb72
0x2519df9a8:	movk	w10, #0xe113, lsl #16
0x2519df9ac:	eor	w10, w30, w10
0x2519df9b0:	mov	w11, #0x6833
0x2519df9b4:	movk	w11, #0xfc63, lsl #16
0x2519df9b8:	add	w10, w10, w11
0x2519df9bc:	eor	w8, w8, w10
0x2519df9c0:	mov	w10, #0xb694
0x2519df9c4:	movk	w10, #0xeb57, lsl #16
0x2519df9c8:	eor	w10, w30, w10
0x2519df9cc:	mov	w11, #0x65d5
0x2519df9d0:	movk	w11, #0xf627, lsl #16
0x2519df9d4:	add	w10, w10, w11
0x2519df9d8:	eor	w8, w8, w10
0x2519df9dc:	ldr	w10, [x27]
0x2519df9e0:	eor	w10, w10, w22
0x2519df9e4:	ldr	w11, [x23]
0x2519df9e8:	eor	w10, w10, w11
0x2519df9ec:	mul	w10, w10, w13
0x2519df9f0:	add	x11, x6, w10, uxtb
0x2519df9f4:	ldrb	w11, [x11]
0x2519df9f8:	eor	w11, w11, w2
0x2519df9fc:	ldrb	w11, [x7, w11, uxtw]
0x2519dfa00:	eor	w10, w10, w11
0x2519dfa04:	sub	w11, w8, w30
0x2519dfa08:	mov	w13, #0x6014
0x2519dfa0c:	movk	w13, #0x1ebb, lsl #16
0x2519dfa10:	add	w11, w11, w13
0x2519dfa14:	mov	w13, #0xb007
0x2519dfa18:	movk	w13, #0xdd35, lsl #16
0x2519dfa1c:	and	w13, w11, w13
0x2519dfa20:	mov	w14, #0xb386
0x2519dfa24:	movk	w14, #0xd9a1, lsl #16
0x2519dfa28:	eor	w14, w11, w14
0x2519dfa2c:	and	w14, w14, w13, lsl #1
0x2519dfa30:	eor	w13, w14, w13
0x2519dfa34:	mov	w14, #0xd388
0x2519dfa38:	movk	w14, #0x7189, lsl #16
0x2519dfa3c:	eor	w14, w11, w14
0x2519dfa40:	lsl	w1, w14, #1
0x2519dfa44:	mov	w2, #0xc71e
0x2519dfa48:	movk	w2, #0x5978, lsl #16
0x2519dfa4c:	eor	w2, w1, w2
0x2519dfa50:	and	w14, w2, w14
0x2519dfa54:	mov	w2, #0x6380
0x2519dfa58:	movk	w2, #0xacbc, lsl #16
0x2519dfa5c:	orr	w3, w2, #0xe
0x2519dfa60:	and	w1, w1, w3
0x2519dfa64:	eor	w14, w14, w1
0x2519dfa68:	mov	w1, #0x2081
0x2519dfa6c:	movk	w1, #0xa484, lsl #16
0x2519dfa70:	eor	w1, w14, w1
0x2519dfa74:	mov	w3, #0x400c
0x2519dfa78:	movk	w3, #0x838, lsl #16
0x2519dfa7c:	eor	w14, w14, w3
0x2519dfa80:	and	w14, w14, w13, lsl #2
0x2519dfa84:	eor	w13, w14, w13
0x2519dfa88:	lsl	w14, w1, #2
0x2519dfa8c:	mov	w3, #0x8e3c
0x2519dfa90:	movk	w3, #0xb2f1, lsl #16
0x2519dfa94:	eor	w3, w14, w3
0x2519dfa98:	and	w1, w3, w1
0x2519dfa9c:	orr	w3, w2, #0xc
0x2519dfaa0:	and	w14, w14, w3
0x2519dfaa4:	eor	w14, w1, w14
0x2519dfaa8:	mov	w1, #0x6183
0x2519dfaac:	movk	w1, #0xc0c, lsl #16
0x2519dfab0:	eor	w1, w14, w1
0x2519dfab4:	mov	w3, #0x200
0x2519dfab8:	movk	w3, #0xa0b0, lsl #16
0x2519dfabc:	eor	w14, w14, w3
0x2519dfac0:	and	w14, w14, w13, lsl #4
0x2519dfac4:	eor	w13, w14, w13
0x2519dfac8:	lsl	w14, w1, #4
0x2519dfacc:	mov	w3, #0x38f0
0x2519dfad0:	movk	w3, #0xcbc6, lsl #16
0x2519dfad4:	eor	w3, w14, w3
0x2519dfad8:	and	w1, w3, w1
0x2519dfadc:	and	w14, w14, w2
0x2519dfae0:	eor	w14, w1, w14
0x2519dfae4:	mov	w1, #0x430f
0x2519dfae8:	movk	w1, #0x2438, lsl #16
0x2519dfaec:	eor	w1, w14, w1
0x2519dfaf0:	mov	w3, #0x2000
0x2519dfaf4:	movk	w3, #0x8884, lsl #16
0x2519dfaf8:	eor	w14, w14, w3
0x2519dfafc:	and	w14, w14, w13, lsl #8
0x2519dfb00:	orr	w2, w2, #0xf
0x2519dfb04:	eor	w13, w13, w2
0x2519dfb08:	eor	w13, w13, w14
0x2519dfb0c:	lsl	w14, w1, #8
0x2519dfb10:	mov	w2, #0x3c630000
0x2519dfb14:	eor	w2, w14, w2
0x2519dfb18:	and	w1, w2, w1
0x2519dfb1c:	mov	w2, #0x2cbc0000
0x2519dfb20:	and	w14, w14, w2
0x2519dfb24:	mov	w3, #0x9c0000
0x2519dfb28:	eor	w14, w14, w3
0x2519dfb2c:	eor	w14, w14, w1
0x2519dfb30:	lsl	w1, w13, #0x10
0x2519dfb34:	mov	w3, #0x638f0000
0x2519dfb38:	eor	w3, w1, w3
0x2519dfb3c:	and	w14, w3, w14
0x2519dfb40:	and	w1, w1, w2
0x2519dfb44:	eor	w13, w1, w13
0x2519dfb48:	eor	w13, w13, w14
0x2519dfb4c:	eor	w13, w11, w13, lsl #1
0x2519dfb50:	mov	w9, #0x96a3
0x2519dfb54:	movk	w9, #0x77e4, lsl #16
0x2519dfb58:	sub	w11, w9, w30
0x2519dfb5c:	add	w11, w11, #1
0x2519dfb60:	mov	w1, #0xa56f
0x2519dfb64:	movk	w1, #0x4327, lsl #16
0x2519dfb68:	eor	w1, w11, w1
0x2519dfb6c:	mov	w2, #0xcc34
0x2519dfb70:	movk	w2, #0xcb3c, lsl #16
0x2519dfb74:	add	w1, w1, w2
0x2519dfb78:	mov	w2, #0x39bb
0x2519dfb7c:	movk	w2, #0xc541, lsl #16
0x2519dfb80:	eor	w2, w11, w2
0x2519dfb84:	mov	w3, #0x50e8
0x2519dfb88:	movk	w3, #0x4d5a, lsl #16
0x2519dfb8c:	add	w2, w2, w3
0x2519dfb90:	mov	w3, #0xf502
0x2519dfb94:	movk	w3, #0x6fd, lsl #16
0x2519dfb98:	eor	w3, w11, w3
0x2519dfb9c:	mov	w4, #0x9c5f
0x2519dfba0:	movk	w4, #0x8ee6, lsl #16
0x2519dfba4:	add	w3, w3, w4
0x2519dfba8:	mov	w4, #0xff75
0x2519dfbac:	movk	w4, #0xf77f, lsl #16
0x2519dfbb0:	eor	w4, w11, w4
0x2519dfbb4:	mov	w5, #0x962a
0x2519dfbb8:	movk	w5, #0x7f64, lsl #16
0x2519dfbbc:	add	w4, w4, w5
0x2519dfbc0:	eor	w11, w1, w11
0x2519dfbc4:	eor	w1, w2, w3
0x2519dfbc8:	eor	w11, w11, w1
0x2519dfbcc:	eor	w9, w11, w4
0x2519dfbd0:	str	w9, [sp, #0x168]
0x2519dfbd4:	mov	w1, #0x53e6
0x2519dfbd8:	movk	w1, #0xadbf, lsl #16
0x2519dfbdc:	eor	w1, w13, w1
0x2519dfbe0:	mov	w2, #0x1488
0x2519dfbe4:	movk	w2, #0x27c4, lsl #16
0x2519dfbe8:	add	w1, w1, w2
0x2519dfbec:	mov	w2, #0x7208
0x2519dfbf0:	movk	w2, #0xf00a, lsl #16
0x2519dfbf4:	eor	w2, w13, w2
0x2519dfbf8:	mov	w3, #0x356a
0x2519dfbfc:	movk	w3, #0x7a71, lsl #16
0x2519dfc00:	add	w2, w2, w3
0x2519dfc04:	eor	w1, w1, w2
0x2519dfc08:	mov	w2, #0xa90f
0x2519dfc0c:	movk	w2, #0x671f, lsl #16
0x2519dfc10:	eor	w13, w13, w2
0x2519dfc14:	mov	w2, #0xee6f
0x2519dfc18:	movk	w2, #0xed64, lsl #16
0x2519dfc1c:	add	w13, w13, w2
0x2519dfc20:	eor	w13, w1, w13
0x2519dfc24:	mov	w1, #0x2324
0x2519dfc28:	movk	w1, #0x6181, lsl #16
0x2519dfc2c:	add	w8, w8, w1
0x2519dfc30:	add	w25, w8, w13
0x2519dfc34:	ldrb	w13, [x26, #6]
0x2519dfc38:	mov	w1, #0xc6
0x2519dfc3c:	and	x1, x1, x13, lsl #1
0x2519dfc40:	sub	x13, x13, x1
0x2519dfc44:	mov	x1, #0x6300
0x2519dfc48:	movk	x1, #0x57e5, lsl #16
0x2519dfc4c:	movk	x1, #0x9e35, lsl #32
0x2519dfc50:	movk	x1, #0xcc3a, lsl #48
0x2519dfc54:	add	x1, x1, x13, lsl #8
0x2519dfc58:	ldrb	w13, [x26, #5]
0x2519dfc5c:	lsl	w2, w13, #1
0x2519dfc60:	and	w2, w2, #0x60
0x2519dfc64:	sub	w13, w13, w2
0x2519dfc68:	mov	w2, #0xc666
0x2519dfc6c:	movk	w2, #0x2ad7, lsl #16
0x2519dfc70:	add	w3, w13, w2
0x2519dfc74:	ldr	x8, [sp, #0xa8]
0x2519dfc78:	ldrb	w13, [x8]
0x2519dfc7c:	mov	w14, #0x36
0x2519dfc80:	eor	x2, x13, x14
0x2519dfc84:	and	w10, w10, #0xff
0x2519dfc88:	sub	w10, w10, #0x3a
0x2519dfc8c:	ldr	x11, [x19, w10, sxtw #3]
0x2519dfc90:	add	x13, x11, #0xff
0x2519dfc94:	ldrb	w2, [x13, x2]
0x2519dfc98:	mov	w8, #0x66
0x2519dfc9c:	sub	w4, w8, w2
0x2519dfca0:	mov	w5, #0x6b
0x2519dfca4:	orr	w4, w4, w5
0x2519dfca8:	sub	w2, w2, #0x67
0x2519dfcac:	mov	w5, #-0x2a
0x2519dfcb0:	and	w5, w2, w5
0x2519dfcb4:	eor	w4, w4, w5
0x2519dfcb8:	mov	w10, #0x14
0x2519dfcbc:	eor	w5, w2, w10
0x2519dfcc0:	and	w6, w5, w4, lsl #1
0x2519dfcc4:	eor	w6, w6, w4
0x2519dfcc8:	and	w6, w5, w6, lsl #1
0x2519dfccc:	eor	w6, w6, w4
0x2519dfcd0:	eor	w7, w2, #4
0x2519dfcd4:	and	w6, w7, w6, lsl #1
0x2519dfcd8:	eor	w4, w6, w4
0x2519dfcdc:	mov	w6, #0x5e
0x2519dfce0:	and	w6, w2, w6
0x2519dfce4:	mov	w8, #0x65
0x2519dfce8:	eor	w6, w6, w8
0x2519dfcec:	mov	w8, #0x28
0x2519dfcf0:	and	w7, w8, w2, lsl #1
0x2519dfcf4:	mov	w27, #0x4a
0x2519dfcf8:	eor	w7, w7, w27
0x2519dfcfc:	and	w7, w7, w2
0x2519dfd00:	eor	w7, w7, w6
0x2519dfd04:	and	w7, w5, w7, lsl #1
0x2519dfd08:	eor	w7, w7, w6
0x2519dfd0c:	and	w5, w5, w7, lsl #1
0x2519dfd10:	eor	w5, w5, w6
0x2519dfd14:	eor	w7, w2, #0x10
0x2519dfd18:	and	w5, w7, w5, lsl #1
0x2519dfd1c:	eor	w5, w5, w6
0x2519dfd20:	eor	w5, w2, w5, lsl #1
0x2519dfd24:	lsl	w4, w4, #4
0x2519dfd28:	eor	w6, w4, w2, lsl #3
0x2519dfd2c:	bfxil	w6, w5, #5, #3
0x2519dfd30:	ldr	x8, [sp, #0x98]
0x2519dfd34:	ldrb	w2, [x8]
0x2519dfd38:	eor	w0, w2, w0
0x2519dfd3c:	sub	w0, w0, #0x48
0x2519dfd40:	mov	w19, #0x74
0x2519dfd44:	eor	w4, w2, w19
0x2519dfd48:	sub	w4, w4, #0x74
0x2519dfd4c:	eor	w0, w0, w4
0x2519dfd50:	mov	w20, #-0x46
0x2519dfd54:	eor	w2, w2, w20
0x2519dfd58:	add	w2, w2, #0x46
0x2519dfd5c:	eor	w0, w0, w2
0x2519dfd60:	mov	w2, #-0x27
0x2519dfd64:	mov	w4, #-1
0x2519dfd68:	madd	w0, w0, w2, w4
0x2519dfd6c:	ldr	x8, [sp, #0x130]
0x2519dfd70:	ldr	x8, [x8]
0x2519dfd74:	ldrb	w4, [x8, #0x22]
0x2519dfd78:	mul	w5, w4, w2
0x2519dfd7c:	add	w4, w5, #0x1c
0x2519dfd80:	mov	w2, #-0x76
0x2519dfd84:	and	w2, w4, w2
0x2519dfd88:	mov	w7, #0x53
0x2519dfd8c:	eor	w7, w2, w7
0x2519dfd90:	mov	w2, #0x64
0x2519dfd94:	eor	w21, w4, w2
0x2519dfd98:	mov	w2, #0x2e
0x2519dfd9c:	and	w22, w21, w2
0x2519dfda0:	eor	w22, w22, w7
0x2519dfda4:	and	w22, w21, w22, lsl #1
0x2519dfda8:	eor	w22, w22, w7
0x2519dfdac:	and	w22, w21, w22, lsl #1
0x2519dfdb0:	eor	w22, w22, w7
0x2519dfdb4:	and	w21, w21, w22, lsl #1
0x2519dfdb8:	eor	w21, w21, w7
0x2519dfdbc:	eor	w22, w4, #0x60
0x2519dfdc0:	and	w21, w22, w21, lsl #1
0x2519dfdc4:	str	x24, [sp, #0x10]
0x2519dfdc8:	ldrb	w22, [x24, #1]
0x2519dfdcc:	mov	w9, #0xb0
0x2519dfdd0:	eor	x22, x22, x9
0x2519dfdd4:	ldrb	w22, [x13, x22]
0x2519dfdd8:	eor	w7, w21, w7
0x2519dfddc:	add	w21, w22, #0x3d
0x2519dfde0:	and	w19, w21, w19
0x2519dfde4:	eor	w19, w19, w12
0x2519dfde8:	eor	w23, w21, #0x70
0x2519dfdec:	and	w24, w23, w19, lsl #1
0x2519dfdf0:	eor	w24, w24, w19
0x2519dfdf4:	and	w24, w21, w24, lsl #1
0x2519dfdf8:	eor	w19, w24, w19
0x2519dfdfc:	mov	w24, #2
0x2519dfe00:	sub	w24, w24, w22
0x2519dfe04:	eor	w19, w24, w19, lsl #1
0x2519dfe08:	mov	w17, #0x24
0x2519dfe0c:	and	w24, w21, w17
0x2519dfe10:	eor	w20, w24, w20
0x2519dfe14:	and	w24, w21, w10
0x2519dfe18:	eor	w24, w20, w24
0x2519dfe1c:	and	w24, w23, w24, lsl #1
0x2519dfe20:	eor	w24, w24, w20
0x2519dfe24:	and	w24, w23, w24, lsl #1
0x2519dfe28:	eor	w24, w24, w20
0x2519dfe2c:	and	w23, w23, w24, lsl #1
0x2519dfe30:	eor	w23, w23, w20
0x2519dfe34:	sub	w22, w12, w22
0x2519dfe38:	and	w22, w22, w23, lsl #1
0x2519dfe3c:	eor	w20, w22, w20
0x2519dfe40:	lsl	w20, w20, #0x19
0x2519dfe44:	eor	w20, w20, w21, lsl #24
0x2519dfe48:	extr	w19, w19, w20, #0x1d
0x2519dfe4c:	mov	x20, #0xffca00000000
0x2519dfe50:	movk	x20, #0xffff, lsl #48
0x2519dfe54:	add	x20, x20, x3, lsl #32
0x2519dfe58:	ldrb	w3, [x8, #7]
0x2519dfe5c:	and	w21, w27, w3, lsl #1
0x2519dfe60:	sub	w3, w3, w21
0x2519dfe64:	mov	w21, #0xe72d
0x2519dfe68:	add	w3, w3, w21
0x2519dfe6c:	mov	x21, #-0x8000000000000
0x2519dfe70:	add	x3, x21, x3, lsl #48
0x2519dfe74:	lsl	w6, w6, #0x18
0x2519dfe78:	mov	x21, #0xf561
0x2519dfe7c:	movk	x21, #0x6c2b, lsl #16
0x2519dfe80:	movk	x21, #0xf93f, lsl #32
0x2519dfe84:	movk	x21, #0x117e, lsl #48
0x2519dfe88:	eor	x6, x6, x21
0x2519dfe8c:	mov	x21, #0xfd71
0x2519dfe90:	movk	x21, #0xff7b, lsl #16
0x2519dfe94:	movk	x21, #0x3d8f, lsl #32
0x2519dfe98:	movk	x21, #0x71a8, lsl #48
0x2519dfe9c:	eor	x21, x20, x21
0x2519dfea0:	and	x6, x6, x21
0x2519dfea4:	mov	x21, #0x6c000000000
0x2519dfea8:	movk	x21, #0x2a81, lsl #48
0x2519dfeac:	and	x20, x20, x21
0x2519dfeb0:	orr	x20, x6, x20
0x2519dfeb4:	and	w6, w19, #0xff
0x2519dfeb8:	mov	x19, #0xc727
0x2519dfebc:	movk	x19, #0xf083, lsl #16
0x2519dfec0:	movk	x19, #0xabc8, lsl #32
0x2519dfec4:	movk	x19, #0x7746, lsl #48
0x2519dfec8:	eor	x6, x19, x6, lsl #40
0x2519dfecc:	mvn	w19, w16
0x2519dfed0:	orr	x19, x19, #0xfffffffffffffdff
0x2519dfed4:	and	x6, x6, x19
0x2519dfed8:	mov	w19, #0xfd00
0x2519dfedc:	and	x19, x16, x19
0x2519dfee0:	mov	x21, #0xe56
0x2519dfee4:	movk	x21, #0x5b2a, lsl #16
0x2519dfee8:	movk	x21, #0x6968, lsl #32
0x2519dfeec:	movk	x21, #0x8d63, lsl #48
0x2519dfef0:	eor	x19, x19, x21
0x2519dfef4:	ldr	x17, [sp, #0x60]
0x2519dfef8:	ldrb	w21, [x17]
0x2519dfefc:	eor	x22, x21, #0xffffffffffffff0f
0x2519dff00:	and	x19, x22, x19
0x2519dff04:	mov	w17, #0xa9
0x2519dff08:	and	x21, x21, x17
0x2519dff0c:	orr	x19, x19, x21
0x2519dff10:	mov	x21, #0xf99e
0x2519dff14:	movk	x21, #0xa65c, lsl #16
0x2519dff18:	movk	x21, #0x68df, lsl #32
0x2519dff1c:	movk	x21, #0x80b2, lsl #48
0x2519dff20:	eor	x20, x20, x21
0x2519dff24:	mov	x21, #0x69a8
0x2519dff28:	movk	x21, #0xa455, lsl #16
0x2519dff2c:	movk	x21, #0x9697, lsl #32
0x2519dff30:	movk	x21, #0x729c, lsl #48
0x2519dff34:	eor	x19, x19, x21
0x2519dff38:	and	x19, x20, x19
0x2519dff3c:	mov	w20, #0xf100
0x2519dff40:	and	x16, x16, x20
0x2519dff44:	lsl	w7, w7, #2
0x2519dff48:	eor	w7, w7, w4, lsl #1
0x2519dff4c:	mov	w20, #0x1ec
0x2519dff50:	and	w7, w7, w20
0x2519dff54:	mov	w20, #0x493d
0x2519dff58:	movk	w20, #0xfa60, lsl #16
0x2519dff5c:	eor	w20, w7, w20
0x2519dff60:	mov	w21, #0x9af0
0x2519dff64:	movk	w21, #0x4aeb, lsl #16
0x2519dff68:	add	w20, w20, w21
0x2519dff6c:	mov	w21, #0x61d9
0x2519dff70:	movk	w21, #0x7cec, lsl #16
0x2519dff74:	eor	w21, w7, w21
0x2519dff78:	mov	w22, #0xb20c
0x2519dff7c:	movk	w22, #0xcc67, lsl #16
0x2519dff80:	add	w21, w21, w22
0x2519dff84:	eor	w20, w20, w21
0x2519dff88:	mov	w21, #0x29e0
0x2519dff8c:	movk	w21, #0x868c, lsl #16
0x2519dff90:	eor	w7, w7, w21
0x2519dff94:	mov	w21, #0xfa33
0x2519dff98:	movk	w21, #0x3607, lsl #16
0x2519dff9c:	add	w7, w7, w21
0x2519dffa0:	eor	w7, w20, w7
0x2519dffa4:	and	w5, w5, #0xff
0x2519dffa8:	cmp	w5, #0xe3
0x2519dffac:	mov	w5, #0x100
0x2519dffb0:	csel	w5, w5, wzr, hi
0x2519dffb4:	bfxil	w5, w4, #0, #8
0x2519dffb8:	sub	w4, w5, w7
0x2519dffbc:	mov	w5, #0x1e74
0x2519dffc0:	movk	w5, #0x1a1a, lsl #16
0x2519dffc4:	add	w4, w4, w5
0x2519dffc8:	mov	w5, #0x3a70
0x2519dffcc:	movk	w5, #0xcc76, lsl #16
0x2519dffd0:	eor	w5, w4, w5
0x2519dffd4:	mov	w7, #0x8f4d
0x2519dffd8:	movk	w7, #0x5a07, lsl #16
0x2519dffdc:	add	w5, w5, w7
0x2519dffe0:	mov	w7, #0x9b75
0x2519dffe4:	movk	w7, #0xfef, lsl #16
0x2519dffe8:	eor	w7, w4, w7
0x2519dffec:	mov	w20, #0x2e4a
0x2519dfff0:	movk	w20, #0x999e, lsl #16
0x2519dfff4:	add	w7, w7, w20
0x2519dfff8:	mov	w20, #0x30a1
0x2519dfffc:	movk	w20, #0x97ca, lsl #16
0x2519e0000:	eor	w20, w4, w20
0x2519e0004:	mov	w21, #0x859e
0x2519e0008:	movk	w21, #0x1bb, lsl #16
0x2519e000c:	add	w20, w20, w21
0x2519e0010:	mov	w21, #0xdb67
0x2519e0014:	movk	w21, #0x3ddd, lsl #16
0x2519e0018:	eor	w21, w4, w21
0x2519e001c:	mov	w22, #0x6e5c
0x2519e0020:	movk	w22, #0xabac, lsl #16
0x2519e0024:	add	w21, w21, w22
0x2519e0028:	eor	w4, w5, w4
0x2519e002c:	eor	w5, w7, w20
0x2519e0030:	eor	w4, w4, w5
0x2519e0034:	eor	w4, w4, w21
0x2519e0038:	mov	x5, #0x7c36
0x2519e003c:	movk	x5, #0xd9c6, lsl #16
0x2519e0040:	movk	x5, #0x3c03, lsl #32
0x2519e0044:	movk	x5, #0xba94, lsl #48
0x2519e0048:	eor	x16, x16, x5
0x2519e004c:	eor	x16, x16, x19
0x2519e0050:	mov	x5, #0x38d8
0x2519e0054:	movk	x5, #0xf7c, lsl #16
0x2519e0058:	movk	x5, #0xa537, lsl #32
0x2519e005c:	movk	x5, #0x88b9, lsl #48
0x2519e0060:	eor	x5, x6, x5
0x2519e0064:	and	x16, x5, x16
0x2519e0068:	mov	x5, #0x320
0x2519e006c:	movk	x5, #0x4000, lsl #16
0x2519e0070:	movk	x5, #0x5408, lsl #32
0x2519e0074:	movk	x5, #0x3000, lsl #48
0x2519e0078:	and	x5, x6, x5
0x2519e007c:	mov	x6, #0x4215
0x2519e0080:	movk	x6, #0xabd4, lsl #16
0x2519e0084:	movk	x6, #0xae93, lsl #32
0x2519e0088:	movk	x6, #0x82e9, lsl #48
0x2519e008c:	eor	x5, x5, x6
0x2519e0090:	eor	x16, x5, x16
0x2519e0094:	mov	x5, #-0x6dfe0001
0x2519e0098:	movk	x5, #0x5405, lsl #32
0x2519e009c:	movk	x5, #0xfa03, lsl #48
0x2519e00a0:	eor	x15, x15, x5
0x2519e00a4:	and	x5, x16, x15
0x2519e00a8:	mov	w15, #0x4a5b
0x2519e00ac:	movk	w15, #0x698e, lsl #16
0x2519e00b0:	eor	x15, x4, x15
0x2519e00b4:	mov	w16, #0x55
0x2519e00b8:	and	w16, w0, w16
0x2519e00bc:	mov	w4, #0x63
0x2519e00c0:	eor	w16, w16, w4
0x2519e00c4:	and	w2, w2, w0, lsl #1
0x2519e00c8:	eor	w2, w2, w12
0x2519e00cc:	eor	w4, w0, #6
0x2519e00d0:	and	w2, w2, w4
0x2519e00d4:	eor	w2, w2, w16
0x2519e00d8:	mov	w4, #0x16
0x2519e00dc:	eor	w4, w0, w4
0x2519e00e0:	and	w2, w4, w2, lsl #1
0x2519e00e4:	eor	w2, w2, w16
0x2519e00e8:	and	w2, w4, w2, lsl #1
0x2519e00ec:	eor	w2, w2, w16
0x2519e00f0:	and	w2, w4, w2, lsl #1
0x2519e00f4:	eor	w2, w2, w16
0x2519e00f8:	and	w2, w4, w2, lsl #1
0x2519e00fc:	eor	w2, w2, w16
0x2519e0100:	and	w2, w4, w2, lsl #1
0x2519e0104:	eor	w16, w2, w16
0x2519e0108:	eor	w0, w0, w16, lsl #1
0x2519e010c:	mov	x16, #0x90b0
0x2519e0110:	movk	x16, #0xa3fb, lsl #16
0x2519e0114:	movk	x16, #0xb089, lsl #32
0x2519e0118:	movk	x16, #0xc06, lsl #48
0x2519e011c:	eor	x16, x1, x16
0x2519e0120:	ldr	x17, [sp, #0x78]
0x2519e0124:	ldrb	w1, [x17]
0x2519e0128:	eor	x2, x1, #0xffffffffffffffef
0x2519e012c:	and	x16, x2, x16
0x2519e0130:	mov	w17, #0x4f
0x2519e0134:	and	x1, x1, x17
0x2519e0138:	sub	x10, x11, #6
0x2519e013c:	ldrb	w15, [x10, x15]
0x2519e0140:	orr	x1, x16, x1
0x2519e0144:	lsr	w16, w15, #3
0x2519e0148:	orr	w15, w16, w15, lsl #5
0x2519e014c:	mov	w16, #0x44
0x2519e0150:	and	w16, w16, w15, lsl #1
0x2519e0154:	sub	w16, w15, w16
0x2519e0158:	ldrb	w15, [x26, #1]
0x2519e015c:	and	w2, w9, w15, lsl #1
0x2519e0160:	mov	w23, #0xb0
0x2519e0164:	sub	w15, w15, w2
0x2519e0168:	add	w15, w15, #0x136, lsl #12
0x2519e016c:	add	w15, w15, #0x285
0x2519e0170:	mov	x2, #0xd30000000000
0x2519e0174:	movk	x2, #0xffff, lsl #48
0x2519e0178:	add	x15, x2, x15, lsl #40
0x2519e017c:	mov	x2, #-0x3cf
0x2519e0180:	movk	x2, #0xf3ff, lsl #48
0x2519e0184:	ldr	x9, [sp, #0x160]
0x2519e0188:	add	x9, x9, x2
0x2519e018c:	eor	x9, x9, x3
0x2519e0190:	mov	x2, #0xa1fc
0x2519e0194:	movk	x2, #0x6fff, lsl #16
0x2519e0198:	movk	x2, #0xd5fa, lsl #32
0x2519e019c:	movk	x2, #0xaad9, lsl #48
0x2519e01a0:	eor	x9, x9, x2
0x2519e01a4:	eor	x5, x9, x5
0x2519e01a8:	mov	w9, #0x1b
0x2519e01ac:	eor	w9, w0, w9
0x2519e01b0:	and	w9, w9, #0xff
0x2519e01b4:	mov	w2, #0xec5f
0x2519e01b8:	movk	w2, #0x1641, lsl #16
0x2519e01bc:	eor	w2, w9, w2
0x2519e01c0:	mov	w3, #0x13a1
0x2519e01c4:	movk	w3, #0xe9be, lsl #16
0x2519e01c8:	add	w2, w2, w3
0x2519e01cc:	mov	w3, #0xd407
0x2519e01d0:	movk	w3, #0xe8f7, lsl #16
0x2519e01d4:	eor	w3, w9, w3
0x2519e01d8:	mov	w4, #0x2bf9
0x2519e01dc:	movk	w4, #0x1708, lsl #16
0x2519e01e0:	add	w3, w3, w4
0x2519e01e4:	eor	w2, w2, w3
0x2519e01e8:	mov	w3, #0x38e0
0x2519e01ec:	movk	w3, #0xfeb6, lsl #16
0x2519e01f0:	eor	w9, w9, w3
0x2519e01f4:	mov	w3, #0xc720
0x2519e01f8:	movk	w3, #0x149, lsl #16
0x2519e01fc:	add	w9, w9, w3
0x2519e0200:	eor	w9, w2, w9
0x2519e0204:	ldrb	w3, [x8, #0x20]
0x2519e0208:	mov	w2, #0x7edb
0x2519e020c:	movk	w2, #0x7ff7, lsl #16
0x2519e0210:	eor	w2, w3, w2
0x2519e0214:	mov	w4, #0x1b6
0x2519e0218:	and	w4, w4, w3, lsl #1
0x2519e021c:	add	w2, w4, w2
0x2519e0220:	mov	w4, #0x7d01
0x2519e0224:	movk	w4, #0x4705, lsl #16
0x2519e0228:	eor	w4, w3, w4
0x2519e022c:	mov	w6, #0x8220
0x2519e0230:	movk	w6, #0xb8fa, lsl #16
0x2519e0234:	add	w4, w4, w6
0x2519e0238:	mov	w6, #0xba78
0x2519e023c:	movk	w6, #0x6216, lsl #16
0x2519e0240:	eor	w6, w3, w6
0x2519e0244:	mov	w7, #0x4567
0x2519e0248:	movk	w7, #0x9de9, lsl #16
0x2519e024c:	add	w6, w6, w7
0x2519e0250:	eor	w4, w4, w6
0x2519e0254:	mov	w6, #0xc75c
0x2519e0258:	movk	w6, #0x2513, lsl #16
0x2519e025c:	eor	w3, w3, w6
0x2519e0260:	mov	w6, #0x3843
0x2519e0264:	movk	w6, #0xdaec, lsl #16
0x2519e0268:	add	w3, w3, w6
0x2519e026c:	eor	w3, w4, w3
0x2519e0270:	sub	w3, w2, w3
0x2519e0274:	mov	w4, #0x6e27
0x2519e0278:	movk	w4, #0x8f15, lsl #16
0x2519e027c:	add	w3, w3, w4
0x2519e0280:	mov	w4, #0xd632
0x2519e0284:	movk	w4, #0xc81d, lsl #16
0x2519e0288:	eor	w4, w3, w4
0x2519e028c:	mov	w6, #0xc40c
0x2519e0290:	movk	w6, #0x38ee, lsl #16
0x2519e0294:	add	w4, w4, w6
0x2519e0298:	mov	w6, #0x6a54
0x2519e029c:	movk	w6, #0xf407, lsl #16
0x2519e02a0:	eor	w6, w3, w6
0x2519e02a4:	mov	w7, #0x786e
0x2519e02a8:	movk	w7, #0x4f4, lsl #16
0x2519e02ac:	add	w6, w6, w7
0x2519e02b0:	mov	w7, #0xa61f
0x2519e02b4:	movk	w7, #0xcceb, lsl #16
0x2519e02b8:	eor	w7, w3, w7
0x2519e02bc:	mov	w19, #0xb427
0x2519e02c0:	movk	w19, #0x3c18, lsl #16
0x2519e02c4:	add	w7, w7, w19
0x2519e02c8:	mov	w19, #0xf7bf
0x2519e02cc:	movk	w19, #0xfffd, lsl #16
0x2519e02d0:	eor	w19, w3, w19
0x2519e02d4:	mov	w20, #0xe587
0x2519e02d8:	movk	w20, #0xf0e, lsl #16
0x2519e02dc:	add	w19, w19, w20
0x2519e02e0:	eor	w3, w4, w3
0x2519e02e4:	eor	w4, w6, w7
0x2519e02e8:	eor	w3, w3, w4
0x2519e02ec:	eor	w3, w3, w19
0x2519e02f0:	mov	x4, #0xdb57
0x2519e02f4:	movk	x4, #0xe2fb, lsl #16
0x2519e02f8:	movk	x4, #0xdd68, lsl #32
0x2519e02fc:	movk	x4, #0xe6e0, lsl #48
0x2519e0300:	eor	x1, x1, x4
0x2519e0304:	ldr	x17, [sp, #0x68]
0x2519e0308:	ldrb	w4, [x17]
0x2519e030c:	lsl	x4, x4, #0x10
0x2519e0310:	mov	x6, #-0x860001
0x2519e0314:	eor	x6, x4, x6
0x2519e0318:	and	x1, x1, x6
0x2519e031c:	mov	w6, #0x1a0000
0x2519e0320:	and	x4, x4, x6
0x2519e0324:	eor	x1, x1, x4
0x2519e0328:	orr	w0, w0, #0x66666666
0x2519e032c:	mov	w4, #0x17c
0x2519e0330:	and	w0, w4, w0, lsl #1
0x2519e0334:	mov	w4, #0x54d1
0x2519e0338:	movk	w4, #0x40b2, lsl #16
0x2519e033c:	eor	w4, w3, w4
0x2519e0340:	mov	w6, #0xa560
0x2519e0344:	movk	w6, #0x1e52, lsl #16
0x2519e0348:	add	w4, w4, w6
0x2519e034c:	mov	w6, #0xa0a0
0x2519e0350:	movk	w6, #0xffae, lsl #16
0x2519e0354:	eor	w6, w3, w6
0x2519e0358:	mov	w7, #0x512f
0x2519e035c:	movk	w7, #0xa14e, lsl #16
0x2519e0360:	add	w6, w6, w7
0x2519e0364:	eor	w4, w4, w6
0x2519e0368:	mov	w6, #0xe649
0x2519e036c:	movk	w6, #0x4fef, lsl #16
0x2519e0370:	eor	w3, w3, w6
0x2519e0374:	mov	w6, #0x17c8
0x2519e0378:	movk	w6, #0x110f, lsl #16
0x2519e037c:	add	w3, w3, w6
0x2519e0380:	eor	w3, w4, w3
0x2519e0384:	mov	w4, #0xd364
0x2519e0388:	movk	w4, #0x1faa, lsl #16
0x2519e038c:	add	w2, w2, w4
0x2519e0390:	add	w2, w2, w3
0x2519e0394:	mov	w3, #0xf259
0x2519e0398:	movk	w3, #0x8785, lsl #16
0x2519e039c:	eor	w3, w2, w3
0x2519e03a0:	mov	w4, #0x3851
0x2519e03a4:	movk	w4, #0x35cc, lsl #16
0x2519e03a8:	add	w3, w3, w4
0x2519e03ac:	mov	w4, #0x51ea
0x2519e03b0:	movk	w4, #0xa6f7, lsl #16
0x2519e03b4:	eor	w4, w2, w4
0x2519e03b8:	mov	w6, #0x9be4
0x2519e03bc:	movk	w6, #0x14be, lsl #16
0x2519e03c0:	add	w4, w4, w6
0x2519e03c4:	mov	w6, #0x49b8
0x2519e03c8:	movk	w6, #0x137f, lsl #16
0x2519e03cc:	eor	w6, w2, w6
0x2519e03d0:	mov	w7, #0x83b2
0x2519e03d4:	movk	w7, #0xa136, lsl #16
0x2519e03d8:	add	w6, w6, w7
0x2519e03dc:	mov	w7, #0xdffd
0x2519e03e0:	movk	w7, #0x7fbb, lsl #16
0x2519e03e4:	eor	w7, w2, w7
0x2519e03e8:	mov	w19, #0x15f5
0x2519e03ec:	movk	w19, #0xcdf2, lsl #16
0x2519e03f0:	add	w7, w7, w19
0x2519e03f4:	mov	w19, #0xf068
0x2519e03f8:	movk	w19, #0xa153, lsl #16
0x2519e03fc:	eor	w19, w0, w19
0x2519e0400:	mov	w20, #0x9d52
0x2519e0404:	movk	w20, #0xd094, lsl #16
0x2519e0408:	add	w19, w19, w20
0x2519e040c:	mov	w20, #0x57de
0x2519e0410:	movk	w20, #0x2f71, lsl #16
0x2519e0414:	eor	w20, w0, w20
0x2519e0418:	mov	w21, #0x3ae8
0x2519e041c:	movk	w21, #0x5eb6, lsl #16
0x2519e0420:	add	w20, w20, w21
0x2519e0424:	eor	w19, w19, w20
0x2519e0428:	mov	w20, #0xa6fa
0x2519e042c:	movk	w20, #0x8e22, lsl #16
0x2519e0430:	eor	w0, w0, w20
0x2519e0434:	sub	w0, w0, #0x1a3, lsl #12
0x2519e0438:	sub	w0, w0, #0x43c
0x2519e043c:	eor	w0, w19, w0
0x2519e0440:	sub	w9, w9, w0
0x2519e0444:	mov	w0, #0x6dc6
0x2519e0448:	movk	w0, #0x71c7, lsl #16
0x2519e044c:	add	w9, w9, w0
0x2519e0450:	add	w16, w16, #0x22
0x2519e0454:	mov	w12, #0x3b
0x2519e0458:	eor	w17, w16, w12
0x2519e045c:	add	w17, w17, #0x3d
0x2519e0460:	eor	w0, w16, #0xffffffdf
0x2519e0464:	sub	w0, w0, #0x27
0x2519e0468:	eor	w17, w17, w0
0x2519e046c:	mov	w12, #0x71
0x2519e0470:	eor	w12, w16, w12
0x2519e0474:	add	w12, w12, #0x77
0x2519e0478:	eor	w12, w17, w12
0x2519e047c:	eor	w16, w2, w3
0x2519e0480:	eor	w17, w4, w6
0x2519e0484:	mov	x4, #0x8e72
0x2519e0488:	movk	x4, #0xdbe5, lsl #16
0x2519e048c:	movk	x4, #0x3632, lsl #32
0x2519e0490:	movk	x4, #0xa619, lsl #48
0x2519e0494:	eor	w16, w16, w17
0x2519e0498:	mov	w17, #0x3563
0x2519e049c:	movk	w17, #0x4db6, lsl #16
0x2519e04a0:	eor	w17, w7, w17
0x2519e04a4:	eor	w16, w16, w17
0x2519e04a8:	mov	w17, #-0x23000000
0x2519e04ac:	add	w12, w17, w12, lsl #24
0x2519e04b0:	mov	x17, #0x41c8
0x2519e04b4:	movk	x17, #0xdd8f, lsl #16
0x2519e04b8:	movk	x17, #0x415a, lsl #32
0x2519e04bc:	movk	x17, #0xce6, lsl #48
0x2519e04c0:	eor	x12, x12, x17
0x2519e04c4:	mov	x17, #0x4579
0x2519e04c8:	movk	x17, #0xe928, lsl #16
0x2519e04cc:	movk	x17, #0xa40f, lsl #32
0x2519e04d0:	movk	x17, #0x2b23, lsl #48
0x2519e04d4:	eor	x17, x1, x17
0x2519e04d8:	and	x12, x12, x17
0x2519e04dc:	mov	x17, #0xbe37
0x2519e04e0:	movk	x17, #0x2270, lsl #16
0x2519e04e4:	movk	x17, #0xbea5, lsl #32
0x2519e04e8:	movk	x17, #0xf319, lsl #48
0x2519e04ec:	and	x17, x1, x17
0x2519e04f0:	eor	x12, x12, x17
0x2519e04f4:	ldr	x17, [sp, #0x88]
0x2519e04f8:	ldrb	w17, [x17]
0x2519e04fc:	mov	x0, #0x8af9
0x2519e0500:	movk	x0, #0x1303, lsl #16
0x2519e0504:	movk	x0, #0xd8ae, lsl #32
0x2519e0508:	movk	x0, #0x462b, lsl #48
0x2519e050c:	eor	x17, x0, x17, lsl #32
0x2519e0510:	mov	x0, #0x8211
0x2519e0514:	movk	x0, #0x821, lsl #32
0x2519e0518:	movk	x0, #0x4001, lsl #48
0x2519e051c:	eor	x0, x12, x0
0x2519e0520:	and	x17, x0, x17
0x2519e0524:	mov	x0, #0x7506
0x2519e0528:	movk	x0, #0xecfc, lsl #16
0x2519e052c:	movk	x0, #0x27d7, lsl #32
0x2519e0530:	movk	x0, #0xb9d4, lsl #48
0x2519e0534:	and	x12, x12, x0
0x2519e0538:	str	x10, [sp, #8]
0x2519e053c:	ldrb	w9, [x10, w9, uxtw]
0x2519e0540:	lsr	w0, w9, #3
0x2519e0544:	orr	w0, w0, w9, lsl #5
0x2519e0548:	ldrb	w16, [x13, w16, uxtw]
0x2519e054c:	add	w9, w16, #0x2d
0x2519e0550:	mov	w7, #0x15
0x2519e0554:	eor	w1, w9, w7
0x2519e0558:	sub	w1, w9, w1
0x2519e055c:	ldr	x9, [sp, #0x58]
0x2519e0560:	ldrb	w9, [x9]
0x2519e0564:	eor	w2, w9, #0xffffffc7
0x2519e0568:	add	w2, w2, #0x39
0x2519e056c:	mov	w3, #-0x29
0x2519e0570:	eor	w3, w9, w3
0x2519e0574:	add	w3, w3, #0x29
0x2519e0578:	eor	w2, w2, w3
0x2519e057c:	mov	w3, #0x96
0x2519e0580:	eor	w9, w9, w3
0x2519e0584:	add	w9, w9, #0x6a
0x2519e0588:	eor	w9, w2, w9
0x2519e058c:	mov	w2, #0xb7
0x2519e0590:	eor	w0, w0, w2
0x2519e0594:	add	w16, w16, w1
0x2519e0598:	lsr	w1, w1, #1
0x2519e059c:	sub	w16, w16, w1, lsl #2
0x2519e05a0:	ldrb	w1, [x8, #3]
0x2519e05a4:	eor	x15, x15, x1, lsl #48
0x2519e05a8:	add	w0, w0, #0x70
0x2519e05ac:	eor	x15, x15, x0, lsl #56
0x2519e05b0:	eor	x12, x15, x12
0x2519e05b4:	eor	x12, x12, x17
0x2519e05b8:	mov	x15, #0x658d
0x2519e05bc:	movk	x15, #0x40a, lsl #16
0x2519e05c0:	movk	x15, #0x95cc, lsl #32
0x2519e05c4:	movk	x15, #0xdb84, lsl #48
0x2519e05c8:	eor	x6, x12, x15
0x2519e05cc:	add	w12, w16, #0x2b
0x2519e05d0:	ubfx	w15, w12, #5, #3
0x2519e05d4:	orr	w12, w15, w12, lsl #3
0x2519e05d8:	ldr	x15, [sp, #0xe0]
0x2519e05dc:	ldrb	w15, [x15]
0x2519e05e0:	mov	x16, #0x1a7c
0x2519e05e4:	movk	x16, #0x2f03, lsl #16
0x2519e05e8:	movk	x16, #0x7101, lsl #32
0x2519e05ec:	movk	x16, #0xb679, lsl #48
0x2519e05f0:	eor	x15, x16, x15, lsl #8
0x2519e05f4:	mvn	w16, w12
0x2519e05f8:	orr	x16, x16, #0xffffffffffffff03
0x2519e05fc:	and	x15, x16, x15
0x2519e0600:	mov	w16, #0x83
0x2519e0604:	and	x12, x12, x16
0x2519e0608:	orr	x12, x15, x12
0x2519e060c:	mov	x15, #0x1227
0x2519e0610:	movk	x15, #0x2705, lsl #16
0x2519e0614:	movk	x15, #0x39a4, lsl #32
0x2519e0618:	movk	x15, #0x3e5c, lsl #48
0x2519e061c:	eor	x12, x12, x15
0x2519e0620:	ldr	x15, [sp, #0xb0]
0x2519e0624:	ldrb	w15, [x15]
0x2519e0628:	lsl	x15, x15, #0x10
0x2519e062c:	mov	x16, #-0x590001
0x2519e0630:	movk	x16, #0xfbbf, lsl #32
0x2519e0634:	movk	x16, #0xbfff, lsl #48
0x2519e0638:	eor	x16, x15, x16
0x2519e063c:	and	x12, x12, x16
0x2519e0640:	ldr	x16, [sp, #0xd8]
0x2519e0644:	ldrb	w16, [x16]
0x2519e0648:	eor	x16, x16, x14
0x2519e064c:	ldrb	w16, [x13, x16]
0x2519e0650:	and	x13, x15, #0xfffffffffff9ffff
0x2519e0654:	mov	x15, #0xb271
0x2519e0658:	movk	x15, #0x5d5, lsl #16
0x2519e065c:	movk	x15, #0x224f, lsl #32
0x2519e0660:	movk	x15, #0x8c70, lsl #48
0x2519e0664:	eor	x13, x13, x15
0x2519e0668:	eor	x12, x13, x12
0x2519e066c:	ldr	x13, [sp, #0x90]
0x2519e0670:	ldrb	w13, [x13]
0x2519e0674:	lsl	x13, x13, #0x18
0x2519e0678:	mov	x15, #-0x86000001
0x2519e067c:	eor	x15, x13, x15
0x2519e0680:	and	x12, x12, x15
0x2519e0684:	mov	w15, #-0xe000000
0x2519e0688:	and	x13, x13, x15
0x2519e068c:	mov	x15, #0x208f
0x2519e0690:	movk	x15, #0x22cf, lsl #16
0x2519e0694:	movk	x15, #0x5c7b, lsl #32
0x2519e0698:	movk	x15, #0xa01e, lsl #48
0x2519e069c:	eor	x13, x13, x15
0x2519e06a0:	eor	x12, x13, x12
0x2519e06a4:	ldrb	w13, [x8, #0x12]
0x2519e06a8:	lsl	x13, x13, #0x20
0x2519e06ac:	bic	x12, x12, x13
0x2519e06b0:	mov	x15, #0x6e00000000
0x2519e06b4:	and	x13, x13, x15
0x2519e06b8:	orr	x13, x12, x13
0x2519e06bc:	ldr	x12, [sp, #0xf0]
0x2519e06c0:	ldrb	w12, [x12]
0x2519e06c4:	mov	x15, #0x8b0c
0x2519e06c8:	movk	x15, #0xa121, lsl #16
0x2519e06cc:	movk	x15, #0x6e63, lsl #32
0x2519e06d0:	movk	x15, #0xeb1c, lsl #48
0x2519e06d4:	eor	x12, x15, x12, lsl #8
0x2519e06d8:	ldrb	w15, [x26, #7]
0x2519e06dc:	bic	x12, x12, x15
0x2519e06e0:	and	x15, x15, #0xfffffffffffffff3
0x2519e06e4:	mov	x17, #0x2500
0x2519e06e8:	movk	x17, #0x441a, lsl #16
0x2519e06ec:	movk	x17, #0x10c, lsl #32
0x2519e06f0:	movk	x17, #0x41, lsl #48
0x2519e06f4:	orr	x15, x15, x17
0x2519e06f8:	eor	x12, x15, x12
0x2519e06fc:	mov	w15, #0x860000
0x2519e0700:	mov	x17, #0xa049
0x2519e0704:	movk	x17, #0x6b21, lsl #16
0x2519e0708:	movk	x17, #0x9a3b, lsl #32
0x2519e070c:	movk	x17, #0xa886, lsl #48
0x2519e0710:	orr	x15, x17, x15
0x2519e0714:	ldr	x0, [sp, #0x80]
0x2519e0718:	ldrb	w0, [x0]
0x2519e071c:	eor	x15, x15, x0, lsl #16
0x2519e0720:	ldrb	w0, [x8, #0x19]
0x2519e0724:	ldrb	w1, [x26, #2]
0x2519e0728:	orr	x1, x1, x0, lsl #8
0x2519e072c:	mov	x2, #0xe15b
0x2519e0730:	movk	x2, #0x6bff, lsl #16
0x2519e0734:	movk	x2, #0xfe3b, lsl #32
0x2519e0738:	movk	x2, #0xef96, lsl #48
0x2519e073c:	eor	x2, x1, x2
0x2519e0740:	and	x15, x15, x2
0x2519e0744:	mov	w2, #0x5fb6
0x2519e0748:	and	x1, x1, x2
0x2519e074c:	orr	x15, x15, x1
0x2519e0750:	eor	x15, x15, x17
0x2519e0754:	add	w16, w16, #0x2d
0x2519e0758:	eor	w17, w16, w7
0x2519e075c:	and	x0, x0, #3
0x2519e0760:	lsl	w17, w17, w0
0x2519e0764:	lsl	w1, w17, #1
0x2519e0768:	and	w1, w1, #0xffffff87
0x2519e076c:	sub	w17, w17, w1
0x2519e0770:	sub	w17, w17, #0x3d
0x2519e0774:	eor	w0, w0, #3
0x2519e0778:	eor	w17, w17, #0xffffffc3
0x2519e077c:	lsl	w17, w17, w0
0x2519e0780:	ldrb	w0, [x8, #0xc]
0x2519e0784:	lsl	x1, x0, #0x38
0x2519e0788:	lsl	x0, x0, #0x39
0x2519e078c:	and	x0, x0, #0x800000000000000
0x2519e0790:	sub	x0, x1, x0
0x2519e0794:	mov	x1, #0x93bc
0x2519e0798:	movk	x1, #0xb6a4, lsl #16
0x2519e079c:	movk	x1, #0x109c, lsl #32
0x2519e07a0:	movk	x1, #0x489, lsl #48
0x2519e07a4:	add	x0, x0, x1
0x2519e07a8:	add	w9, w9, #0xd
0x2519e07ac:	and	x9, x9, #0xff
0x2519e07b0:	mov	w10, #0x76
0x2519e07b4:	eor	x9, x9, x10
0x2519e07b8:	mov	x2, x11
0x2519e07bc:	add	x10, x11, #0x202
0x2519e07c0:	str	x10, [sp, #0x160]
0x2519e07c4:	ldrb	w9, [x10, x9]
0x2519e07c8:	ldr	x1, [sp, #0xf8]
0x2519e07cc:	ldrb	w1, [x1]
0x2519e07d0:	lsl	x1, x1, #0x28
0x2519e07d4:	sub	w9, w9, #0x43
0x2519e07d8:	mov	w10, #0x17
0x2519e07dc:	eor	w9, w9, w10
0x2519e07e0:	mov	w10, #-0x1d
0x2519e07e4:	mul	w9, w9, w10
0x2519e07e8:	and	w9, w9, #0xff
0x2519e07ec:	orr	x9, x1, x9, lsl #48
0x2519e07f0:	eor	x9, x0, x9
0x2519e07f4:	mov	x0, #0x5819
0x2519e07f8:	movk	x0, #0x1be9, lsl #16
0x2519e07fc:	movk	x0, #0xa00d, lsl #32
0x2519e0800:	movk	x0, #0xa0c2, lsl #48
0x2519e0804:	eor	x9, x9, x0
0x2519e0808:	eor	x22, x9, x13
0x2519e080c:	ldrb	w9, [x8, #6]
0x2519e0810:	mov	x13, #0x96000000
0x2519e0814:	movk	x13, #1, lsl #32
0x2519e0818:	and	x13, x13, x9, lsl #25
0x2519e081c:	lsl	x9, x9, #0x18
0x2519e0820:	sub	x9, x9, x13
0x2519e0824:	mov	x13, #0x9b98
0x2519e0828:	movk	x13, #0xcb50, lsl #16
0x2519e082c:	movk	x13, #0x8bc4, lsl #32
0x2519e0830:	movk	x13, #0x2971, lsl #48
0x2519e0834:	add	x9, x9, x13
0x2519e0838:	eor	x9, x9, x13
0x2519e083c:	add	x9, x9, x15
0x2519e0840:	mov	w13, #0x43
0x2519e0844:	eor	w13, w17, w13
0x2519e0848:	ubfx	w15, w16, #5, #3
0x2519e084c:	bic	w13, w13, w15
0x2519e0850:	and	w15, w15, #4
0x2519e0854:	orr	w15, w15, w23
0x2519e0858:	eor	w13, w13, w15
0x2519e085c:	ldr	x15, [sp, #0x70]
0x2519e0860:	ldrb	w15, [x15]
0x2519e0864:	mov	x16, #0xa39b
0x2519e0868:	movk	x16, #0x8d7e, lsl #16
0x2519e086c:	movk	x16, #0xf563, lsl #32
0x2519e0870:	movk	x16, #0x34ee, lsl #48
0x2519e0874:	eor	x15, x16, x15, lsl #16
0x2519e0878:	mov	x16, #0x93
0x2519e087c:	movk	x16, #0x8c4, lsl #16
0x2519e0880:	movk	x16, #0x9000, lsl #32
0x2519e0884:	movk	x16, #0x14a2, lsl #48
0x2519e0888:	eor	x16, x12, x16
0x2519e088c:	and	x15, x16, x15
0x2519e0890:	mov	x16, #0x5c64
0x2519e0894:	movk	x16, #0x6003, lsl #16
0x2519e0898:	movk	x16, #0xa0c, lsl #32
0x2519e089c:	movk	x16, #0x4b11, lsl #48
0x2519e08a0:	and	x12, x12, x16
0x2519e08a4:	mov	x16, #0xd03b
0x2519e08a8:	movk	x16, #0x7929, lsl #16
0x2519e08ac:	movk	x16, #0x9a7c, lsl #32
0x2519e08b0:	movk	x16, #0x7765, lsl #48
0x2519e08b4:	eor	x12, x12, x16
0x2519e08b8:	eor	x12, x12, x15
0x2519e08bc:	ldr	x15, [sp, #0xa0]
0x2519e08c0:	ldrb	w15, [x15]
0x2519e08c4:	lsl	x15, x15, #0x18
0x2519e08c8:	mov	x16, #-0x86000001
0x2519e08cc:	movk	x16, #0x7fff, lsl #48
0x2519e08d0:	eor	x16, x15, x16
0x2519e08d4:	and	x12, x12, x16
0x2519e08d8:	mov	w16, #0x6b000000
0x2519e08dc:	and	x15, x15, x16
0x2519e08e0:	mov	x16, #0x8b7a
0x2519e08e4:	movk	x16, #0xefa, lsl #16
0x2519e08e8:	movk	x16, #0x8155, lsl #32
0x2519e08ec:	movk	x16, #0xa3d3, lsl #48
0x2519e08f0:	eor	x15, x15, x16
0x2519e08f4:	eor	x12, x15, x12
0x2519e08f8:	ldr	x15, [sp, #0xb8]
0x2519e08fc:	ldrb	w15, [x15]
0x2519e0900:	lsl	x15, x15, #0x20
0x2519e0904:	mov	x16, #-0x5100000001
0x2519e0908:	eor	x16, x15, x16
0x2519e090c:	and	x12, x12, x16
0x2519e0910:	mov	x16, #0xb900000000
0x2519e0914:	and	x15, x15, x16
0x2519e0918:	ldr	x16, [sp, #0xc0]
0x2519e091c:	ldrb	w16, [x16]
0x2519e0920:	lsl	x16, x16, #0x20
0x2519e0924:	ldrb	w17, [x26, #3]
0x2519e0928:	orr	x16, x16, x17, lsl #40
0x2519e092c:	eor	x9, x16, x9
0x2519e0930:	str	x26, [sp, #0x120]
0x2519e0934:	ldrb	w16, [x26, #4]
0x2519e0938:	eor	x9, x9, x16, lsl #56
0x2519e093c:	and	w13, w13, #0xff
0x2519e0940:	eor	x9, x9, x13, lsl #48
0x2519e0944:	mov	x13, #0x7a31
0x2519e0948:	movk	x13, #0x61b9, lsl #16
0x2519e094c:	movk	x13, #0xb9e2, lsl #32
0x2519e0950:	movk	x13, #0x9af0, lsl #48
0x2519e0954:	eor	x9, x9, x13
0x2519e0958:	mov	w13, #0x8fe4
0x2519e095c:	movk	w13, #0xe6a4, lsl #16
0x2519e0960:	and	w13, w13, w30, lsl #1
0x2519e0964:	sub	w13, w30, w13
0x2519e0968:	mov	w16, #0x47f2
0x2519e096c:	movk	w16, #0xf352, lsl #16
0x2519e0970:	add	w13, w13, w16
0x2519e0974:	mov	w16, #0xd151
0x2519e0978:	movk	w16, #0x84b6, lsl #16
0x2519e097c:	eor	w13, w13, w16
0x2519e0980:	mov	w10, #0x96a3
0x2519e0984:	movk	w10, #0x77e4, lsl #16
0x2519e0988:	ldr	w11, [sp, #0x168]
0x2519e098c:	eor	w14, w11, w10
0x2519e0990:	eor	w11, w13, w11
0x2519e0994:	and	w13, w14, w30
0x2519e0998:	add	w11, w11, w13, lsl #1
0x2519e099c:	mov	w13, #0x28fd
0x2519e09a0:	movk	w13, #0x4b69, lsl #16
0x2519e09a4:	eor	w13, w25, w13
0x2519e09a8:	mov	w14, #0x3589
0x2519e09ac:	movk	w14, #0xa2f7, lsl #16
0x2519e09b0:	add	w13, w13, w14
0x2519e09b4:	mov	w14, #0x6f4e
0x2519e09b8:	movk	w14, #0x686e, lsl #16
0x2519e09bc:	eor	w14, w25, w14
0x2519e09c0:	mov	w16, #0x723c
0x2519e09c4:	movk	w16, #0x81f0, lsl #16
0x2519e09c8:	add	w14, w14, w16
0x2519e09cc:	mov	w16, #0x9acf
0x2519e09d0:	movk	w16, #0x5a89, lsl #16
0x2519e09d4:	eor	w16, w25, w16
0x2519e09d8:	mov	w17, #0x87bb
0x2519e09dc:	movk	w17, #0xb317, lsl #16
0x2519e09e0:	add	w16, w16, w17
0x2519e09e4:	mov	w17, #0x3ff6
0x2519e09e8:	movk	w17, #0x6fef, lsl #16
0x2519e09ec:	eor	w17, w25, w17
0x2519e09f0:	mov	w0, #0x2284
0x2519e09f4:	movk	w0, #0x8671, lsl #16
0x2519e09f8:	add	w17, w17, w0
0x2519e09fc:	ldr	x0, [sp, #0xe8]
0x2519e0a00:	ldrb	w0, [x0]
0x2519e0a04:	orr	x15, x15, x0, lsl #48
0x2519e0a08:	str	x8, [sp, #0x50]
0x2519e0a0c:	ldrb	w0, [x8, #0x21]
0x2519e0a10:	orr	x15, x15, x0, lsl #40
0x2519e0a14:	ldr	x0, [sp, #0xd0]
0x2519e0a18:	ldrb	w0, [x0]
0x2519e0a1c:	orr	x15, x15, x0, lsl #56
0x2519e0a20:	mov	x0, #0x292f
0x2519e0a24:	movk	x0, #0xfd41, lsl #16
0x2519e0a28:	movk	x0, #0xe2ea, lsl #32
0x2519e0a2c:	movk	x0, #0xb0c9, lsl #48
0x2519e0a30:	eor	x15, x15, x0
0x2519e0a34:	eor	x7, x15, x12
0x2519e0a38:	eor	w11, w11, w25
0x2519e0a3c:	eor	w11, w11, w14
0x2519e0a40:	eor	w12, w13, w16
0x2519e0a44:	eor	w11, w11, w12
0x2519e0a48:	mov	w12, #0xe28b
0x2519e0a4c:	movk	w12, #0x1661, lsl #16
0x2519e0a50:	eor	w13, w17, w12
0x2519e0a54:	eor	w11, w11, w13
0x2519e0a58:	lsl	x13, x11, #0x21
0x2519e0a5c:	mov	x14, #0x6c6400000000
0x2519e0a60:	movk	x14, #0x4c32, lsl #48
0x2519e0a64:	and	x14, x13, x14
0x2519e0a68:	mov	x15, #0x59fe00000000
0x2519e0a6c:	movk	x15, #0x51d6, lsl #48
0x2519e0a70:	and	x13, x13, x15
0x2519e0a74:	str	w30, [sp, #0x128]
0x2519e0a78:	sub	w8, w30, w25
0x2519e0a7c:	add	w8, w8, w12
0x2519e0a80:	lsl	x11, x11, #0x20
0x2519e0a84:	sub	x12, x11, x14
0x2519e0a88:	sub	x13, x11, x13
0x2519e0a8c:	neg	x11, x11
0x2519e0a90:	mov	x14, #0x238c
0x2519e0a94:	movk	x14, #0x40bd, lsl #16
0x2519e0a98:	movk	x14, #0x2cff, lsl #32
0x2519e0a9c:	movk	x14, #0xa8eb, lsl #48
0x2519e0aa0:	add	x13, x13, x14
0x2519e0aa4:	eor	x11, x11, x14
0x2519e0aa8:	eor	x10, x11, x13
0x2519e0aac:	str	x10, [sp, #0x158]
0x2519e0ab0:	sub	x11, x2, #8
0x2519e0ab4:	add	x10, x12, x4
0x2519e0ab8:	stp	x10, x11, [sp, #0x148]
0x2519e0abc:	cmp	w8, #1
0x2519e0ac0:	csinc	w8, w8, wzr, hi
0x2519e0ac4:	str	w8, [sp, #0x140]
0x2519e0ac8:	ldr	x8, [sp, #0x138]
0x2519e0acc:	mov	x11, x8
0x2519e0ad0:	ldr	w12, [sp, #0x19c]
0x2519e0ad4:	ldr	x13, [sp, #0x1b8]
0x2519e0ad8:	mov	w16, #0x383
0x2519e0adc:	mov	w0, #0x3328
0x2519e0ae0:	movk	w0, #0x9125, lsl #16
0x2519e0ae4:	mov	w1, #0xc9ff
0x2519e0ae8:	movk	w1, #0x6eda, lsl #16
0x2519e0aec:	mov	w26, #0xec09
0x2519e0af0:	movk	w26, #0x1e08, lsl #16
0x2519e0af4:	mov	w19, #0xdbd6
0x2519e0af8:	movk	w19, #0x3c11, lsl #16
0x2519e0afc:	mov	w21, #0x13f8
0x2519e0b00:	movk	w21, #0xe1f7, lsl #16
0x2519e0b04:	mov	w2, #0x7cc
0x2519e0b08:	mov	w3, #0x145
0x2519e0b0c:	mov	w10, #0
0x2519e0b10:	mov	w8, #0x3bec
0x2519e0b14:	movk	w8, #0x78b, lsl #16
0x2519e0b18:	add	w8, w11, w8
0x2519e0b1c:	mov	w11, #0xc377
0x2519e0b20:	movk	w11, #0xf874, lsl #16
0x2519e0b24:	and	w25, w8, w11
0x2519e0b28:	sub	w8, w25, #0x2e7
0x2519e0b2c:	ldrb	w17, [x13, w10, uxtw]
0x2519e0b30:	orr	w8, w8, w16
0x2519e0b34:	sub	w24, w8, #0x397
0x2519e0b38:	and	w24, w24, w10, lsl #3
0x2519e0b3c:	lsl	x17, x17, x24
0x2519e0b40:	eor	x5, x17, x5
0x2519e0b44:	sub	w17, w25, #0x32b
0x2519e0b48:	cmp	w10, w17
0x2519e0b4c:	cset	w17, lo
0x2519e0b50:	mov	w11, #0x73
0x2519e0b54:	mul	w17, w17, w11
0x2519e0b58:	eor	w17, w17, w25
0x2519e0b5c:	ldr	x24, [x28, w17, sxtw #3]
0x2519e0b60:	mov	x17, #0x405b
0x2519e0b64:	braa	x24, x17
0x2519e0b68:	sub	w10, w10, w11
0x2519e0b6c:	strb	wzr, [x8, xzr]
0x2519e0b70:	sub	w11, w9, #0x232
0x2519e0b74:	mov	w12, #0x148
0x2519e0b78:	eor	x12, x11, x12
0x2519e0b7c:	add	x12, x12, xzr
0x2519e0b80:	cmp	x12, x10
0x2519e0b84:	cset	w14, eq
0x2519e0b88:	mov	w13, #0xf7
0x2519e0b8c:	mul	w14, w14, w13
0x2519e0b90:	eor	w14, w14, w9
0x2519e0b94:	ldr	x14, [x26, w14, sxtw #3]
0x2519e0b98:	mov	x28, x11
0x2519e0b9c:	mov	x17, #0xbe83
0x2519e0ba0:	braa	x14, x17
0x2519e0ba4:	mov	w12, #0x7ecf
0x2519e0ba8:	movk	w12, #0x988a, lsl #16
0x2519e0bac:	mov	w8, #0x819b
0x2519e0bb0:	movk	w8, #0x6775, lsl #16
0x2519e0bb4:	add	w10, w22, #0xe3
0x2519e0bb8:	mov	w9, #0xc2f8
0x2519e0bbc:	movk	w9, #0xe775, lsl #16
0x2519e0bc0:	add	w9, w10, w9
0x2519e0bc4:	mov	w11, #0xbbdf
0x2519e0bc8:	movk	w11, #0x7fff, lsl #16
0x2519e0bcc:	and	w9, w9, w11
0x2519e0bd0:	ldr	x19, [sp, #0x68]
0x2519e0bd4:	ldr	x0, [x19]
0x2519e0bd8:	str	x23, [sp, #0x80]
0x2519e0bdc:	eor	w8, w9, w8
0x2519e0be0:	cmp	w23, w8
0x2519e0be4:	cset	w8, eq
0x2519e0be8:	sub	w11, w10, #0x29c
0x2519e0bec:	mul	w8, w8, w11
0x2519e0bf0:	eor	w8, w8, w10
0x2519e0bf4:	ldr	x8, [x28, w8, sxtw #3]
0x2519e0bf8:	mov	x17, #0x831f
0x2519e0bfc:	braa	x8, x17
0x2519e0c00:	mov	x9, #0
0x2519e0c04:	mov	w10, #0x27e
0x2519e0c08:	ldr	w8, [sp, #0x50]
0x2519e0c0c:	eor	w11, w8, w10
0x2519e0c10:	add	w20, w11, #0xf2
0x2519e0c14:	sub	w8, w8, #0x1f7
0x2519e0c18:	cmp	x9, #0x10
0x2519e0c1c:	cset	w12, lo
0x2519e0c20:	add	w14, w11, #0x22c
0x2519e0c24:	mul	w12, w12, w14
0x2519e0c28:	eor	w8, w12, w8
0x2519e0c2c:	ldr	x12, [x7, w8, sxtw #3]
0x2519e0c30:	mov	w8, #0x14f8
0x2519e0c34:	movk	w8, #0x1455, lsl #16
0x2519e0c38:	ldr	x26, [sp]
0x2519e0c3c:	mov	w28, #0x1f79
0x2519e0c40:	movk	w28, #0xd3ef, lsl #16
0x2519e0c44:	mov	x27, #0xb4fa
0x2519e0c48:	movk	x27, #0x6d3c, lsl #16
0x2519e0c4c:	movk	x27, #0x2a54, lsl #32
0x2519e0c50:	movk	x27, #0x375b, lsl #48
0x2519e0c54:	ldp	x3, x2, [sp, #0xa0]
0x2519e0c58:	ldr	x4, [sp, #0xb8]
0x2519e0c5c:	ldp	x5, x1, [sp, #0x60]
0x2519e0c60:	ldr	x15, [sp, #0x90]
0x2519e0c64:	mov	w16, #0x14f8
0x2519e0c68:	movk	w16, #0x1455, lsl #16
0x2519e0c6c:	adrp	x0, #0x27612b000
0x2519e0c70:	add	x0, x0, #0x8f0
0x2519e0c74:	mov	x17, #0xc7a2
0x2519e0c78:	braa	x12, x17
0x2519e0c7c:	add	x8, x8, #4
0x2519e0c80:	b	#0x2519f11b4
0x2519e0c84:	ldr	w10, [x10]
0x2519e0c88:	ldr	w11, [x11]
0x2519e0c8c:	add	w10, w11, w10
0x2519e0c90:	eor	w9, w10, w9
0x2519e0c94:	mul	w8, w9, w8
0x2519e0c98:	adrp	x9, #0x27612b000
0x2519e0c9c:	add	x9, x9, #0xa18
0x2519e0ca0:	ldr	x10, [x9]
0x2519e0ca4:	add	x10, x10, w8, uxtb
0x2519e0ca8:	ldurb	w10, [x10, #-8]
0x2519e0cac:	mov	w11, #0xb9
0x2519e0cb0:	eor	w10, w10, w11
0x2519e0cb4:	ldr	x9, [x9, #0x510]
0x2519e0cb8:	add	x9, x9, x10
0x2519e0cbc:	ldurb	w9, [x9, #-4]
0x2519e0cc0:	eor	w8, w9, w8
0x2519e0cc4:	and	w8, w8, #0xff
0x2519e0cc8:	add	w8, w8, #0x3d8
0x2519e0ccc:	ldr	x8, [x12, w8, uxtw #3]
0x2519e0cd0:	mov	x17, #0x6b0e
0x2519e0cd4:	blraa	x8, x17
0x2519e0cd8:	mov	w0, #0
0x2519e0cdc:	b	#0x2519ddcec
0x2519e0ce0:	mov	w10, #0x6ba0
0x2519e0ce4:	movk	w10, #0xc68b, lsl #16
0x2519e0ce8:	mov	w8, #0xc4a0
0x2519e0cec:	movk	w8, #0x582, lsl #16
0x2519e0cf0:	add	w8, w14, w8
0x2519e0cf4:	mov	w9, #0x39f9
0x2519e0cf8:	movk	w9, #0xfa7d, lsl #16
0x2519e0cfc:	and	w11, w8, w9
0x2519e0d00:	mov	w8, #0x23f0
0x2519e0d04:	movk	w8, #0xf899, lsl #16
0x2519e0d08:	add	w8, w14, w8
0x2519e0d0c:	mov	w9, #0xdbfa
0x2519e0d10:	movk	w9, #0x766, lsl #16
0x2519e0d14:	and	w8, w8, w9
0x2519e0d18:	str	w19, [x26]
0x2519e0d1c:	mov	w9, #0x26b
0x2519e0d20:	eor	w9, w8, w9
0x2519e0d24:	lsl	w9, w19, w9
0x2519e0d28:	mov	w12, #0xd740
0x2519e0d2c:	movk	w12, #0x8d16, lsl #16
0x2519e0d30:	and	w9, w9, w12
0x2519e0d34:	sub	w12, w10, #0xe7
0x2519e0d38:	eor	w12, w11, w12
0x2519e0d3c:	add	w12, w12, w19
0x2519e0d40:	sub	w12, w12, w9
0x2519e0d44:	cmp	w12, w10
0x2519e0d48:	cset	w9, eq
0x2519e0d4c:	mov	w13, #0xed
0x2519e0d50:	mul	w9, w9, w13
0x2519e0d54:	eor	w9, w9, w14
0x2519e0d58:	ldr	x9, [x20, w9, sxtw #3]
0x2519e0d5c:	ldr	x16, [sp, #0x10]
0x2519e0d60:	mov	x17, #0xc5e3
0x2519e0d64:	braa	x9, x17
0x2519e0d68:	add	w16, w16, #1
0x2519e0d6c:	add	w0, w0, #1
0x2519e0d70:	b	#0x251a0e2c4
0x2519e0d74:	mov	w8, #0xc5
0x2519e0d78:	eor	w8, w10, w8
0x2519e0d7c:	add	w28, w8, #0x3f
0x2519e0d80:	mov	w9, #0x13a
0x2519e0d84:	mul	w22, w8, w9
0x2519e0d88:	ldr	w8, [sp, #0xd0]
0x2519e0d8c:	cmp	w8, #0xc
0x2519e0d90:	cset	w8, eq
0x2519e0d94:	mov	w9, #0xd0
0x2519e0d98:	eor	w9, w28, w9
0x2519e0d9c:	add	w9, w9, w22
0x2519e0da0:	mul	w8, w9, w8
0x2519e0da4:	eor	w8, w8, w10
0x2519e0da8:	ldr	x8, [x26, w8, sxtw #3]
0x2519e0dac:	mov	w9, #0x708d
0x2519e0db0:	movk	w9, #0x1454, lsl #16
0x2519e0db4:	sub	w13, w9, #0x328
0x2519e0db8:	mov	x17, #0x306
0x2519e0dbc:	braa	x8, x17
0x2519e0dc0:	mov	w9, #0x86a7
0x2519e0dc4:	movk	w9, #0x488a, lsl #16
0x2519e0dc8:	cmp	w8, w9
0x2519e0dcc:	mov	w8, #0x70d0
0x2519e0dd0:	movk	w8, #0x1454, lsl #16
0x2519e0dd4:	mov	w9, #0x14f8
0x2519e0dd8:	movk	w9, #0x1455, lsl #16
0x2519e0ddc:	csel	w8, w9, w8, eq
0x2519e0de0:	str	w8, [x0, #0x20]
0x2519e0de4:	ldur	x8, [x29, #-0x60]
0x2519e0de8:	adrp	x9, #0x2681b4000
0x2519e0dec:	ldr	x9, [x9, #0xee0]
0x2519e0df0:	ldr	x9, [x9]
0x2519e0df4:	cmp	x9, x8
0x2519e0df8:	b.ne	#0x2519e0e1c
0x2519e0dfc:	add	sp, sp, #0x350
0x2519e0e00:	ldp	x29, x30, [sp, #0x50]
0x2519e0e04:	ldp	x20, x19, [sp, #0x40]
0x2519e0e08:	ldp	x22, x21, [sp, #0x30]
0x2519e0e0c:	ldp	x24, x23, [sp, #0x20]
0x2519e0e10:	ldp	x26, x25, [sp, #0x10]
0x2519e0e14:	ldp	x28, x27, [sp], #0x60
0x2519e0e18:	retab	
0x2519e0e1c:	bl	#0x2580f4380
0x2519e0e20:	sub	w13, w9, #0x2d3
0x2519e0e24:	orr	w13, w13, #0x380
0x2519e0e28:	mov	w14, w12
0x2519e0e2c:	add	x15, x26, x14
0x2519e0e30:	ldrb	w15, [x15]
0x2519e0e34:	add	x14, x8, x14
0x2519e0e38:	mov	w16, #0x75
0x2519e0e3c:	eor	w15, w15, w16
0x2519e0e40:	strb	w15, [x14]
0x2519e0e44:	add	w14, w12, w10
0x2519e0e48:	add	w12, w12, #1
0x2519e0e4c:	mov	w15, #0xd394
0x2519e0e50:	movk	w15, #0xf26f, lsl #16
0x2519e0e54:	add	w13, w13, w15
0x2519e0e58:	cmp	w14, w11
0x2519e0e5c:	ccmp	w12, w13, #2, lo
0x2519e0e60:	cset	w13, lo
0x2519e0e64:	lsl	w14, w13, #4
0x2519e0e68:	sub	w13, w14, w13, lsl #1
0x2519e0e6c:	eor	w13, w13, w9
0x2519e0e70:	ldr	x13, [x25, w13, sxtw #3]
0x2519e0e74:	mov	x17, #0x726e
0x2519e0e78:	braa	x13, x17
0x2519e0e7c:	ldur	x8, [x29, #-0x60]
0x2519e0e80:	adrp	x9, #0x2681b4000
0x2519e0e84:	ldr	x9, [x9, #0xee0]
0x2519e0e88:	ldr	x9, [x9]
0x2519e0e8c:	cmp	x9, x8
0x2519e0e90:	b.ne	#0x2519e0eb4
0x2519e0e94:	ldp	x29, x30, [sp, #0x140]
0x2519e0e98:	ldp	x20, x19, [sp, #0x130]
0x2519e0e9c:	ldp	x22, x21, [sp, #0x120]
0x2519e0ea0:	ldp	x24, x23, [sp, #0x110]
0x2519e0ea4:	ldp	x26, x25, [sp, #0x100]
0x2519e0ea8:	ldp	x28, x27, [sp, #0xf0]
0x2519e0eac:	add	sp, sp, #0x150
0x2519e0eb0:	retab	
0x2519e0eb4:	bl	#0x2580f4380
0x2519e0eb8:	strb	w19, [x12, x10]
0x2519e0ebc:	add	x10, x10, #1
0x2519e0ec0:	cmp	x10, #0x40
0x2519e0ec4:	cset	w11, eq
0x2519e0ec8:	eor	w11, w9, w11
0x2519e0ecc:	bic	w11, w14, w11
0x2519e0ed0:	mul	w11, w11, w15
0x2519e0ed4:	eor	w11, w11, w8
0x2519e0ed8:	ldr	x11, [x27, w11, uxtw #3]
0x2519e0edc:	mov	x17, #0x761e
0x2519e0ee0:	braa	x11, x17
0x2519e0ee4:	mov	w8, #0x6d64
0x2519e0ee8:	movk	w8, #0x1454, lsl #16
0x2519e0eec:	str	w8, [x0, #0x10]
0x2519e0ef0:	add	sp, sp, #0x10
0x2519e0ef4:	ret	
0x2519e0ef8:	mov	w30, #0x6da8
0x2519e0efc:	movk	w30, #0xc8a7, lsl #16
0x2519e0f00:	ldr	w6, [sp, #0x94]
0x2519e0f04:	ldr	x3, [sp, #0x70]
0x2519e0f08:	mov	x27, x25
0x2519e0f0c:	ldr	w25, [sp, #0x64]
0x2519e0f10:	b	#0x251a1d02c
0x2519e0f14:	add	x15, sp, #0x1bc
0x2519e0f18:	ldr	w7, [sp, #0xc4]
0x2519e0f1c:	mov	w8, #0xf99d
0x2519e0f20:	movk	w8, #0x85c9, lsl #16
0x2519e0f24:	add	w8, w8, w7
0x2519e0f28:	add	w14, w8, #0xc
0x2519e0f2c:	b	#0x251a2280c
0x2519e0f30:	mov	w9, #0xbb09
0x2519e0f34:	movk	w9, #0x78ce, lsl #16
0x2519e0f38:	cmp	w8, w9
0x2519e0f3c:	mov	w8, #0x70d0
0x2519e0f40:	movk	w8, #0x1454, lsl #16
0x2519e0f44:	mov	w9, #0x14f8
0x2519e0f48:	movk	w9, #0x1455, lsl #16
0x2519e0f4c:	csel	w8, w9, w8, eq
0x2519e0f50:	str	w8, [x0, #0x20]
0x2519e0f54:	ldur	x8, [x29, #-0x60]
0x2519e0f58:	adrp	x9, #0x2681b4000
0x2519e0f5c:	ldr	x9, [x9, #0xee0]
0x2519e0f60:	ldr	x9, [x9]
0x2519e0f64:	cmp	x9, x8
0x2519e0f68:	b.ne	#0x2519e0f8c
0x2519e0f6c:	add	sp, sp, #0x380
0x2519e0f70:	ldp	x29, x30, [sp, #0x50]
0x2519e0f74:	ldp	x20, x19, [sp, #0x40]
0x2519e0f78:	ldp	x22, x21, [sp, #0x30]
0x2519e0f7c:	ldp	x24, x23, [sp, #0x20]
0x2519e0f80:	ldp	x26, x25, [sp, #0x10]
0x2519e0f84:	ldp	x28, x27, [sp], #0x60
0x2519e0f88:	retab	
0x2519e0f8c:	bl	#0x2580f4380
0x2519e0f90:	sub	w8, w8, #0x1b
0x2519e0f94:	mov	w9, #0x248a
0x2519e0f98:	movk	w9, #0xbbba, lsl #16
0x2519e0f9c:	ldr	x0, [sp, #0x58]
0x2519e0fa0:	ldr	w1, [sp, #0x54]
0x2519e0fa4:	b	#0x2519e6d14
0x2519e0fa8:	b	#0x251a049cc
0x2519e0fac:	cmp	w13, w10
0x2519e0fb0:	cset	w15, lo
0x2519e0fb4:	add	w17, w11, #0x89
0x2519e0fb8:	mov	w0, #0xe9e0
0x2519e0fbc:	movk	w0, #0x8370, lsl #16
0x2519e0fc0:	add	w0, w9, w0
0x2519e0fc4:	mov	w2, #0xe1
0x2519e0fc8:	strb	w2, [x12, w0, uxtw]
0x2519e0fcc:	mov	w0, #0x3ca6
0x2519e0fd0:	movk	w0, #0x69ab, lsl #16
0x2519e0fd4:	add	w0, w9, w0
0x2519e0fd8:	add	w9, w9, #1
0x2519e0fdc:	cmp	w0, w10
0x2519e0fe0:	cset	w2, lo
0x2519e0fe4:	eor	w2, w15, w2
0x2519e0fe8:	cmp	w0, w13
0x2519e0fec:	cset	w0, lo
0x2519e0ff0:	cmp	w2, #0
0x2519e0ff4:	csel	w15, w15, w0, ne
0x2519e0ff8:	lsl	w0, w15, #1
0x2519e0ffc:	orr	w15, w0, w15, lsl #5
0x2519e1000:	eor	w15, w15, w17
0x2519e1004:	ldr	x15, [x20, w15, sxtw #3]
0x2519e1008:	mov	x17, #0xabe1
0x2519e100c:	braa	x15, x17
0x2519e1010:	mov	w13, #0xfa
0x2519e1014:	eor	w12, w12, w13
0x2519e1018:	mov	w13, #0x125
0x2519e101c:	mul	w12, w12, w13
0x2519e1020:	ldr	x5, [sp, #0x58]
0x2519e1024:	ldr	w13, [x5, #0x58]
0x2519e1028:	mov	w14, #0x458d
0x2519e102c:	movk	w14, #0x5fd7, lsl #16
0x2519e1030:	eor	w14, w13, w14
0x2519e1034:	mov	w15, #0xba73
0x2519e1038:	movk	w15, #0xa028, lsl #16
0x2519e103c:	add	w14, w14, w15
0x2519e1040:	mov	w15, #0x3233
0x2519e1044:	movk	w15, #0x2256, lsl #16
0x2519e1048:	eor	w17, w13, w15
0x2519e104c:	eor	w12, w17, w12
0x2519e1050:	mov	w15, #0xcea4
0x2519e1054:	movk	w15, #0xdda9, lsl #16
0x2519e1058:	add	w12, w12, w15
0x2519e105c:	mov	w15, #0xed9
0x2519e1060:	movk	w15, #0xe11c, lsl #16
0x2519e1064:	eor	w13, w13, w15
0x2519e1068:	mov	w15, #0xf127
0x2519e106c:	movk	w15, #0x1ee3, lsl #16
0x2519e1070:	add	w13, w13, w15
0x2519e1074:	eor	w13, w13, w14
0x2519e1078:	eor	w12, w13, w12
0x2519e107c:	mov	w13, #0x3e6c
0x2519e1080:	movk	w13, #0xa8ae, lsl #16
0x2519e1084:	eor	w13, w11, w13
0x2519e1088:	mov	w14, #0xc194
0x2519e108c:	movk	w14, #0x5751, lsl #16
0x2519e1090:	add	w13, w13, w14
0x2519e1094:	mov	w14, #0xafa1
0x2519e1098:	movk	w14, #0x5f4b, lsl #16
0x2519e109c:	eor	w14, w11, w14
0x2519e10a0:	mov	w15, #0x505f
0x2519e10a4:	movk	w15, #0xa0b4, lsl #16
0x2519e10a8:	add	w14, w14, w15
0x2519e10ac:	eor	w13, w13, w14
0x2519e10b0:	mov	w14, #0xebc5
0x2519e10b4:	movk	w14, #0x6b78, lsl #16
0x2519e10b8:	eor	w11, w11, w14
0x2519e10bc:	mov	w14, #0x143b
0x2519e10c0:	movk	w14, #0x9487, lsl #16
0x2519e10c4:	add	w11, w11, w14
0x2519e10c8:	eor	w11, w13, w11
0x2519e10cc:	mov	w13, #0xf4de
0x2519e10d0:	movk	w13, #0x90a1, lsl #16
0x2519e10d4:	add	w11, w11, w13
0x2519e10d8:	add	w11, w11, w12
0x2519e10dc:	mov	w12, #0xbc16
0x2519e10e0:	movk	w12, #0xec84, lsl #16
0x2519e10e4:	eor	w12, w11, w12
0x2519e10e8:	mov	w13, #0x4328
0x2519e10ec:	movk	w13, #0x441c, lsl #16
0x2519e10f0:	add	w12, w12, w13
0x2519e10f4:	mov	w13, #0xa4a4
0x2519e10f8:	movk	w13, #0x2347, lsl #16
0x2519e10fc:	eor	w13, w11, w13
0x2519e1100:	mov	w14, #0x5b96
0x2519e1104:	movk	w14, #0x8bdf, lsl #16
0x2519e1108:	add	w13, w13, w14
0x2519e110c:	mov	w14, #0xc683
0x2519e1110:	movk	w14, #0x655b, lsl #16
0x2519e1114:	eor	w14, w11, w14
0x2519e1118:	mov	w15, #0x39b3
0x2519e111c:	movk	w15, #0xcdc3, lsl #16
0x2519e1120:	add	w14, w14, w15
0x2519e1124:	mov	w15, #0xdeff
0x2519e1128:	movk	w15, #0xfdff, lsl #16
0x2519e112c:	eor	w17, w11, w15
0x2519e1130:	mov	w15, #0x21cf
0x2519e1134:	movk	w15, #0x5567, lsl #16
0x2519e1138:	add	w17, w17, w15
0x2519e113c:	eor	w11, w11, w12
0x2519e1140:	eor	w12, w13, w14
0x2519e1144:	eor	w11, w11, w12
0x2519e1148:	mov	w12, #0x7ac6
0x2519e114c:	movk	w12, #0xcbfa, lsl #16
0x2519e1150:	eor	w12, w17, w12
0x2519e1154:	eor	w11, w11, w12
0x2519e1158:	str	w11, [x5, #0x58]
0x2519e115c:	b	#0x2519eb23c
0x2519e1160:	add	x8, x19, #0x24
0x2519e1164:	sub	w9, w13, #0xc8
0x2519e1168:	sub	x11, x29, #0x90
0x2519e116c:	mov	w10, #0x944b
0x2519e1170:	movk	w10, #0xd1af, lsl #16
0x2519e1174:	eor	w10, w11, w10
0x2519e1178:	mov	w11, #0x7f8e
0x2519e117c:	movk	w11, #0x9589, lsl #16
0x2519e1180:	orr	w11, w11, w10, lsl #1
0x2519e1184:	sub	w10, w11, w10
0x2519e1188:	mov	w11, #0x4039
0x2519e118c:	movk	w11, #0xb53b, lsl #16
0x2519e1190:	add	w10, w10, w11
0x2519e1194:	mov	w11, #0x88e1
0x2519e1198:	movk	w11, #0x1400, lsl #16
0x2519e119c:	eor	w10, w10, w11
0x2519e11a0:	mov	w11, #0x8101
0x2519e11a4:	movk	w11, #0xce46, lsl #16
0x2519e11a8:	mul	w10, w10, w11
0x2519e11ac:	ldr	x21, [sp, #0x48]
0x2519e11b0:	stp	x21, x19, [x29, #-0x78]
0x2519e11b4:	eor	w9, w9, w10
0x2519e11b8:	ldr	w11, [sp, #0x14]
0x2519e11bc:	sub	w11, w11, w10
0x2519e11c0:	mov	w12, #0x94e4
0x2519e11c4:	movk	w12, #0x97c3, lsl #16
0x2519e11c8:	add	w11, w11, w12
0x2519e11cc:	stp	w9, w11, [x29, #-0x68]
0x2519e11d0:	mov	w9, #0x3c
0x2519e11d4:	sub	w9, w9, w10
0x2519e11d8:	sturb	w9, [x29, #-0x90]
0x2519e11dc:	stp	x8, x14, [x29, #-0x88]
0x2519e11e0:	ldr	w8, [x26]
0x2519e11e4:	ldr	w9, [x27]
0x2519e11e8:	add	w8, w9, w8
0x2519e11ec:	eor	w8, w8, w25
0x2519e11f0:	mul	w8, w8, w24
0x2519e11f4:	ldp	x12, x11, [sp, #0x28]
0x2519e11f8:	add	x9, x11, w8, uxtb
0x2519e11fc:	ldrb	w9, [x9]
0x2519e1200:	mov	w15, #0x99
0x2519e1204:	eor	w9, w9, w15
0x2519e1208:	ldrb	w9, [x12, w9, uxtw]
0x2519e120c:	mov	w10, #0x7ecf
0x2519e1210:	movk	w10, #0x988a, lsl #16
0x2519e1214:	sub	w10, w13, w10
0x2519e1218:	eor	w8, w8, w9
0x2519e121c:	and	w8, w8, #0xff
0x2519e1220:	sub	w8, w8, #0x61
0x2519e1224:	ldr	x8, [x22, w8, sxtw #3]
0x2519e1228:	ldur	x8, [x8, #-4]
0x2519e122c:	str	x8, [sp, #0x90]
0x2519e1230:	ldr	w8, [x26]
0x2519e1234:	ldr	w9, [x27]
0x2519e1238:	sub	w8, w9, w8
0x2519e123c:	eor	w8, w8, w25
0x2519e1240:	mul	w8, w8, w24
0x2519e1244:	add	x9, x11, w8, uxtb
0x2519e1248:	ldrb	w9, [x9]
0x2519e124c:	eor	w9, w9, w15
0x2519e1250:	ldrb	w9, [x12, w9, uxtw]
0x2519e1254:	sub	w19, w10, #0x176
0x2519e1258:	eor	w8, w8, w9
0x2519e125c:	and	w8, w8, #0xff
0x2519e1260:	add	w8, w8, #0x2f4
0x2519e1264:	ldr	x8, [x28, w8, uxtw #3]
0x2519e1268:	sub	x0, x29, #0x90
0x2519e126c:	add	x1, sp, #0x90
0x2519e1270:	mov	x22, x13
0x2519e1274:	str	x14, [sp, #0x40]
0x2519e1278:	mov	x17, #0x5a5d
0x2519e127c:	blraa	x8, x17
0x2519e1280:	mov	x8, sp
0x2519e1284:	ldr	x9, [sp, #0x90]
0x2519e1288:	add	x8, x8, x9
0x2519e128c:	mov	sp, x8
0x2519e1290:	ldrb	w8, [x21]
0x2519e1294:	lsl	x9, x8, #6
0x2519e1298:	sub	x8, x9, x8, lsl #3
0x2519e129c:	add	x9, x21, #4
0x2519e12a0:	add	x10, x9, x8
0x2519e12a4:	add	x8, x10, #4
0x2519e12a8:	mov	w9, #0xc365
0x2519e12ac:	movk	w9, #0x7fb3, lsl #16
0x2519e12b0:	add	w9, w22, w9
0x2519e12b4:	ldr	w14, [sp, #0x24]
0x2519e12b8:	eor	w9, w9, w14
0x2519e12bc:	mov	w10, #0x19a6
0x2519e12c0:	movk	w10, #0xacc7, lsl #16
0x2519e12c4:	str	w19, [sp, #0x48]
0x2519e12c8:	eor	w10, w19, w10
0x2519e12cc:	add	w9, w9, w10
0x2519e12d0:	mov	w10, #0xe4ba
0x2519e12d4:	movk	w10, #0x10ed, lsl #16
0x2519e12d8:	eor	w10, w14, w10
0x2519e12dc:	mov	w11, #0xb9c4
0x2519e12e0:	movk	w11, #0xa4ec, lsl #16
0x2519e12e4:	add	w10, w10, w11
0x2519e12e8:	mov	w11, #0x4c88
0x2519e12ec:	movk	w11, #0xdb7f, lsl #16
0x2519e12f0:	eor	w11, w14, w11
0x2519e12f4:	mov	w12, #0x11f8
0x2519e12f8:	movk	w12, #0x6f7e, lsl #16
0x2519e12fc:	add	w11, w11, w12
0x2519e1300:	mov	w12, #0xcff7
0x2519e1304:	movk	w12, #0xffdf, lsl #16
0x2519e1308:	eor	w12, w14, w12
0x2519e130c:	mov	w13, #0x928f
0x2519e1310:	movk	w13, #0x4bde, lsl #16
0x2519e1314:	add	w12, w12, w13
0x2519e1318:	eor	w10, w10, w14
0x2519e131c:	eor	w11, w11, w12
0x2519e1320:	eor	w10, w10, w11
0x2519e1324:	eor	w9, w10, w9
0x2519e1328:	and	w10, w9, #0xfffffff0
0x2519e132c:	mov	w11, #0x5fff
0x2519e1330:	movk	w11, #0xc20, lsl #16
0x2519e1334:	eor	w10, w10, w11
0x2519e1338:	mov	w11, #0xfae0
0x2519e133c:	movk	w11, #0x8fbd, lsl #16
0x2519e1340:	and	w9, w11, w9, lsl #1
0x2519e1344:	mov	w11, #0x4000
0x2519e1348:	movk	w11, #0x87bd, lsl #16
0x2519e134c:	eor	w9, w9, w11
0x2519e1350:	mov	w11, #0xe7be
0x2519e1354:	movk	w11, #0xfef7, lsl #16
0x2519e1358:	add	w10, w10, w11
0x2519e135c:	add	w9, w10, w9
0x2519e1360:	add	w10, w22, #0x213
0x2519e1364:	mov	w11, #0x9f8
0x2519e1368:	movk	w11, #0x5390, lsl #16
0x2519e136c:	sub	x12, x29, #0x90
0x2519e1370:	and	w11, w12, w11
0x2519e1374:	lsl	w11, w11, #1
0x2519e1378:	sub	w11, w11, w12
0x2519e137c:	mov	w12, #0xf604
0x2519e1380:	movk	w12, #0xac6f, lsl #16
0x2519e1384:	add	w11, w11, w12
0x2519e1388:	mov	w12, #0xd01a
0x2519e138c:	movk	w12, #0x97d0, lsl #16
0x2519e1390:	eor	w11, w11, w12
0x2519e1394:	mov	w12, #0x9c25
0x2519e1398:	movk	w12, #0x4a5e, lsl #16
0x2519e139c:	mul	w11, w11, w12
0x2519e13a0:	stur	x8, [x29, #-0x80]
0x2519e13a4:	eor	w8, w10, w11
0x2519e13a8:	ldr	x10, [sp, #0x18]
0x2519e13ac:	stur	x10, [x29, #-0x68]
0x2519e13b0:	eor	w9, w9, w11
0x2519e13b4:	stp	w9, w8, [x29, #-0x78]
0x2519e13b8:	ldr	x8, [sp, #0x40]
0x2519e13bc:	stp	x8, x8, [x29, #-0x90]
0x2519e13c0:	ldr	w8, [x26]
0x2519e13c4:	ldr	w9, [x27]
0x2519e13c8:	eor	w8, w8, w25
0x2519e13cc:	eor	w8, w8, w9
0x2519e13d0:	mul	w8, w8, w24
0x2519e13d4:	ldr	x9, [sp, #0x50]
0x2519e13d8:	add	x9, x9, w8, uxtb
0x2519e13dc:	ldrb	w9, [x9]
0x2519e13e0:	mov	w10, #0xcd
0x2519e13e4:	eor	w9, w9, w10
0x2519e13e8:	ldrb	w9, [x20, w9, uxtw]
0x2519e13ec:	eor	w8, w8, w9
0x2519e13f0:	and	w8, w8, #0xff
0x2519e13f4:	add	w8, w8, #0x3a7
0x2519e13f8:	ldr	x8, [x28, w8, uxtw #3]
0x2519e13fc:	sub	x0, x29, #0x90
0x2519e1400:	mov	x17, #0xd885
0x2519e1404:	blraa	x8, x17
0x2519e1408:	ldur	w21, [x29, #-0x70]
0x2519e140c:	mov	w8, #0x14f8
0x2519e1410:	movk	w8, #0x1455, lsl #16
0x2519e1414:	cmp	w21, w8
0x2519e1418:	cset	w8, eq
0x2519e141c:	lsl	w9, w8, #0xa
0x2519e1420:	sub	w8, w9, w8
0x2519e1424:	eor	w8, w8, w22
0x2519e1428:	ldr	x8, [x28, w8, sxtw #3]
0x2519e142c:	mov	x17, #0x691d
0x2519e1430:	braa	x8, x17
0x2519e1434:	mov	x8, sp
0x2519e1438:	mov	w9, #0x107
0x2519e143c:	mov	w10, #0x337
0x2519e1440:	eor	w10, w25, w10
0x2519e1444:	mov	w11, #0xa7
0x2519e1448:	mul	w11, w10, w11
0x2519e144c:	mov	w10, #0xba
0x2519e1450:	mov	w12, #0x343
0x2519e1454:	eor	x11, x11, x12
0x2519e1458:	eor	w12, w8, w10
0x2519e145c:	add	w13, w8, #0x11
0x2519e1460:	mul	w12, w12, w13
0x2519e1464:	add	x13, x19, x9
0x2519e1468:	strb	w12, [x13]
0x2519e146c:	cmp	x9, x11
0x2519e1470:	cset	w12, eq
0x2519e1474:	orr	w12, w25, w12, lsl #3
0x2519e1478:	ldr	x12, [x24, w12, sxtw #3]
0x2519e147c:	mov	x17, #0xa0d1
0x2519e1480:	braa	x12, x17
0x2519e1484:	mov	w8, #0x4c
0x2519e1488:	eor	w8, w11, w8
0x2519e148c:	mov	w11, #0x118
0x2519e1490:	mul	w8, w8, w11
0x2519e1494:	ldr	x11, [sp, #0x30]
0x2519e1498:	add	x11, x11, x9
0x2519e149c:	ldrb	w11, [x11]
0x2519e14a0:	ldrb	w12, [x13, x9]
0x2519e14a4:	eor	w11, w11, w12
0x2519e14a8:	eor	w11, w11, w8
0x2519e14ac:	mov	w12, #0x8e
0x2519e14b0:	eor	w11, w11, w12
0x2519e14b4:	strb	w11, [x13, x9]
0x2519e14b8:	add	x9, x9, #1
0x2519e14bc:	eor	w11, w8, w10
0x2519e14c0:	add	w20, w11, #0xf2
0x2519e14c4:	sub	w8, w8, #0x1f7
0x2519e14c8:	cmp	x9, #0x10
0x2519e14cc:	cset	w12, lo
0x2519e14d0:	add	w14, w11, #0x22c
0x2519e14d4:	mul	w12, w12, w14
0x2519e14d8:	eor	w8, w12, w8
0x2519e14dc:	ldr	x12, [x7, w8, sxtw #3]
0x2519e14e0:	mov	w8, #0x14f8
0x2519e14e4:	movk	w8, #0x1455, lsl #16
0x2519e14e8:	mov	x17, #0xc7a2
0x2519e14ec:	braa	x12, x17
0x2519e14f0:	sub	x8, x8, #1
0x2519e14f4:	ldrb	w10, [x11, x8]
0x2519e14f8:	strb	w10, [x14, x8]
0x2519e14fc:	eor	x10, x13, #0x1e0
0x2519e1500:	cmp	x8, x10
0x2519e1504:	cset	w10, eq
0x2519e1508:	mul	w10, w10, w9
0x2519e150c:	eor	w10, w10, w21
0x2519e1510:	ldr	x10, [x28, w10, uxtw #3]
0x2519e1514:	mov	x17, #0xabe1
0x2519e1518:	braa	x10, x17
0x2519e151c:	b	#0x251a1e99c
0x2519e1520:	mov	w11, #0x2cd
0x2519e1524:	eor	w23, w22, w11
0x2519e1528:	ldr	w10, [x10]
0x2519e152c:	ldr	w11, [x16]
0x2519e1530:	sub	w10, w11, w10
0x2519e1534:	eor	w9, w10, w9
0x2519e1538:	mul	w8, w9, w8
0x2519e153c:	adrp	x9, #0x27612b000
0x2519e1540:	add	x9, x9, #0xa48
0x2519e1544:	ldr	x10, [x9]
0x2519e1548:	add	x10, x10, w8, uxtb
0x2519e154c:	ldurb	w10, [x10, #-0xc]
0x2519e1550:	mov	w11, #0x4a
0x2519e1554:	eor	w10, w10, w11
0x2519e1558:	ldr	x9, [x9, #0xa0]
0x2519e155c:	add	x9, x9, x10
0x2519e1560:	ldurb	w9, [x9, #-4]
0x2519e1564:	eor	w8, w9, w8
0x2519e1568:	and	w8, w8, #0xff
0x2519e156c:	add	w8, w8, #0x3bb
0x2519e1570:	ldr	x8, [x21, w8, uxtw #3]
0x2519e1574:	mov	x1, #0x4e91
0x2519e1578:	movk	x1, #0x4592, lsl #16
0x2519e157c:	movk	x1, #0x40, lsl #32
0x2519e1580:	movk	x1, #0x101, lsl #48
0x2519e1584:	mov	w0, #0x108
0x2519e1588:	mov	x17, #0xaa22
0x2519e158c:	blraa	x8, x17
0x2519e1590:	cmp	x0, #0
0x2519e1594:	cset	w8, eq
0x2519e1598:	eor	w8, w23, w8
0x2519e159c:	and	w8, w8, #1
0x2519e15a0:	mov	w9, #0x3d1
0x2519e15a4:	eor	w9, w22, w9
0x2519e15a8:	mul	w8, w8, w9
0x2519e15ac:	eor	w8, w8, w22
0x2519e15b0:	ldr	x8, [x21, w8, sxtw #3]
0x2519e15b4:	mov	w11, #0x70cc
0x2519e15b8:	movk	w11, #0x1454, lsl #16
0x2519e15bc:	mov	x17, #0x9d21
0x2519e15c0:	braa	x8, x17
0x2519e15c4:	mov	w8, #0x59
0x2519e15c8:	strb	w8, [x11, #3]
0x2519e15cc:	mov	w8, #0x4c
0x2519e15d0:	strb	w8, [x11, #2]
0x2519e15d4:	mov	w8, #0x50
0x2519e15d8:	strb	w8, [x11, #1]
0x2519e15dc:	mov	w8, #0x46
0x2519e15e0:	strb	w8, [x11]
0x2519e15e4:	mov	w8, #0x6f
0x2519e15e8:	eor	w8, w24, w8
0x2519e15ec:	strb	w8, [x11, #4]
0x2519e15f0:	mov	w8, #1
0x2519e15f4:	strb	w8, [x11, #5]
0x2519e15f8:	mov	w8, #2
0x2519e15fc:	strb	w8, [x11, #6]
0x2519e1600:	strb	wzr, [x11, #7]
0x2519e1604:	mov	w9, #-0x7e000000
0x2519e1608:	str	w9, [x11, #8]
0x2519e160c:	strb	w8, [x11, #0xc]
0x2519e1610:	ldrb	w8, [x14, #0xe]
0x2519e1614:	strb	w8, [x11, #0xd]
0x2519e1618:	add	x10, x11, #0xe
0x2519e161c:	sub	x8, x29, #0x88
0x2519e1620:	mov	w9, #0x8068
0x2519e1624:	movk	w9, #0x4219, lsl #16
0x2519e1628:	and	w9, w8, w9
0x2519e162c:	lsl	w9, w9, #1
0x2519e1630:	sub	w8, w9, w8
0x2519e1634:	mov	w9, #0x7f94
0x2519e1638:	movk	w9, #0xbde6, lsl #16
0x2519e163c:	add	w8, w8, w9
0x2519e1640:	mov	w9, #0xd199
0x2519e1644:	movk	w9, #0x2818, lsl #16
0x2519e1648:	eor	w8, w8, w9
0x2519e164c:	mul	w8, w8, w7
0x2519e1650:	str	x10, [sp, #0x38]
0x2519e1654:	stur	x10, [x29, #-0x80]
0x2519e1658:	sub	w9, w27, w8
0x2519e165c:	add	w9, w9, #0x10c
0x2519e1660:	stur	w9, [x29, #-0x78]
0x2519e1664:	mov	w9, #0x7da6
0x2519e1668:	add	w8, w8, w9
0x2519e166c:	sturh	w8, [x29, #-0x74]
0x2519e1670:	ldr	w8, [x25]
0x2519e1674:	ldr	w9, [x3]
0x2519e1678:	add	w8, w9, w8
0x2519e167c:	eor	w8, w8, w2
0x2519e1680:	mul	w8, w8, w0
0x2519e1684:	ldr	x9, [x20, #0x418]
0x2519e1688:	sub	x21, x9, #8
0x2519e168c:	add	x9, x21, w8, uxtb
0x2519e1690:	ldrb	w9, [x9]
0x2519e1694:	mov	w10, #0x73
0x2519e1698:	eor	w9, w9, w10
0x2519e169c:	ldr	x10, [x20, #0x4f8]
0x2519e16a0:	sub	x28, x10, #8
0x2519e16a4:	ldrb	w9, [x28, w9, uxtw]
0x2519e16a8:	eor	w8, w9, w8
0x2519e16ac:	and	w8, w8, #0xff
0x2519e16b0:	add	w8, w8, #0x60
0x2519e16b4:	ldr	x8, [x20, w8, uxtw #3]
0x2519e16b8:	ldr	x8, [x8]
0x2519e16bc:	str	x8, [sp, #0xe0]
0x2519e16c0:	ldr	w8, [x25]
0x2519e16c4:	ldr	w9, [x3]
0x2519e16c8:	eor	w8, w8, w2
0x2519e16cc:	eor	w8, w8, w9
0x2519e16d0:	mul	w8, w8, w0
0x2519e16d4:	add	x9, x6, w8, uxtb
0x2519e16d8:	ldrb	w9, [x9]
0x2519e16dc:	mov	w10, #0x1a
0x2519e16e0:	eor	w9, w9, w10
0x2519e16e4:	ldrb	w9, [x5, w9, uxtw]
0x2519e16e8:	eor	w8, w8, w9
0x2519e16ec:	and	w8, w8, #0xff
0x2519e16f0:	add	w8, w8, #0x398
0x2519e16f4:	ldr	x8, [x26, w8, uxtw #3]
0x2519e16f8:	sub	x0, x29, #0x88
0x2519e16fc:	add	x1, sp, #0xe0
0x2519e1700:	str	x11, [sp, #0x40]
0x2519e1704:	mov	x17, #0x6e8
0x2519e1708:	blraa	x8, x17
0x2519e170c:	ldr	x0, [sp, #0x40]
0x2519e1710:	mov	x8, sp
0x2519e1714:	ldr	x9, [sp, #0xe0]
0x2519e1718:	add	x8, x8, x9
0x2519e171c:	mov	sp, x8
0x2519e1720:	mov	w8, #0x100
0x2519e1724:	strh	w8, [x0, #0xe]
0x2519e1728:	ldr	x8, [sp, #0x78]
0x2519e172c:	add	x9, x8, #0x103
0x2519e1730:	mov	w12, #0x8d
0x2519e1734:	mov	w8, #0x24c
0x2519e1738:	eor	w8, w27, w8
0x2519e173c:	add	x10, x0, x12
0x2519e1740:	ldrb	w11, [x10]
0x2519e1744:	mov	w10, #0xea
0x2519e1748:	and	w13, w10, w11, lsl #1
0x2519e174c:	sub	w11, w11, w13
0x2519e1750:	add	w11, w11, #0x75
0x2519e1754:	strb	w11, [x9], #0xffffffffffffffff
0x2519e1758:	cmp	x12, #0xe
0x2519e175c:	cset	w13, eq
0x2519e1760:	add	w11, w8, #0x18f
0x2519e1764:	mul	w13, w13, w11
0x2519e1768:	orr	w13, w13, w27
0x2519e176c:	ldr	x13, [x26, w13, sxtw #3]
0x2519e1770:	sub	x12, x12, #1
0x2519e1774:	mov	x17, #0x761e
0x2519e1778:	braa	x13, x17
0x2519e177c:	add	x15, sp, #0x148
0x2519e1780:	ldr	w7, [sp, #0xc4]
0x2519e1784:	mov	w8, #0xf99d
0x2519e1788:	movk	w8, #0x85c9, lsl #16
0x2519e178c:	add	w8, w8, w7
0x2519e1790:	add	w14, w8, #0x17
0x2519e1794:	mov	w16, #0x80
0x2519e1798:	mov	x9, x7
0x2519e179c:	ldr	x22, [sp, #0x20]
0x2519e17a0:	add	x1, sp, #0x148
0x2519e17a4:	b	#0x2519fd04c
0x2519e17a8:	cmp	w16, w5
0x2519e17ac:	cset	w17, eq
0x2519e17b0:	sub	w19, w21, #0xd
0x2519e17b4:	mov	w20, #0x41
0x2519e17b8:	orr	w19, w19, w20
0x2519e17bc:	sub	w20, w21, #0x136
0x2519e17c0:	add	w22, w20, w19
0x2519e17c4:	sub	w22, w22, #0x401
0x2519e17c8:	mul	w17, w22, w17
0x2519e17cc:	eor	w17, w17, w21
0x2519e17d0:	ldr	x21, [x10, w17, sxtw #3]
0x2519e17d4:	mov	x17, #0x93d0
0x2519e17d8:	braa	x21, x17
0x2519e17dc:	eor	x14, x8, x11
0x2519e17e0:	adds	x12, x14, x12
0x2519e17e4:	ldrb	w14, [x16, x12]
0x2519e17e8:	strb	w14, [x9, x12]
0x2519e17ec:	cset	w14, eq
0x2519e17f0:	mul	w14, w14, w13
0x2519e17f4:	eor	w14, w14, w10
0x2519e17f8:	ldr	x14, [x20, w14, sxtw #3]
0x2519e17fc:	mov	x17, #0x3e6a
0x2519e1800:	braa	x14, x17
0x2519e1804:	mov	w8, #0xdc
0x2519e1808:	eor	w8, w21, w8
0x2519e180c:	lsl	w22, w8, #2
0x2519e1810:	ldp	w9, w10, [sp, #0xd0]
0x2519e1814:	add	w9, w10, w9
0x2519e1818:	ldr	w10, [sp, #0xcc]
0x2519e181c:	add	w9, w9, w10
0x2519e1820:	mov	w10, #0xaf7b
0x2519e1824:	add	w10, w8, w10
0x2519e1828:	cmp	w9, w10
0x2519e182c:	cset	w9, eq
0x2519e1830:	mov	w10, #0x3b5
0x2519e1834:	eor	w10, w22, w10
0x2519e1838:	mul	w9, w9, w10
0x2519e183c:	eor	w9, w9, w21
0x2519e1840:	ldr	x9, [x26, w9, sxtw #3]
0x2519e1844:	mov	w10, #0x708d
0x2519e1848:	movk	w10, #0x1454, lsl #16
0x2519e184c:	sub	w13, w10, #0x318
0x2519e1850:	mov	x17, #0x77dd
0x2519e1854:	braa	x9, x17
0x2519e1858:	sub	w8, w24, #9
0x2519e185c:	orr	w21, w8, #0x40
0x2519e1860:	mov	w8, #0x7a75
0x2519e1864:	movk	w8, #0xa660, lsl #16
0x2519e1868:	add	w8, w24, w8
0x2519e186c:	mov	w9, #0x87f4
0x2519e1870:	movk	w9, #0x599f, lsl #16
0x2519e1874:	ldr	w10, [sp, #0xd4]
0x2519e1878:	add	x10, x27, x10
0x2519e187c:	add	x11, sp, #0xf0
0x2519e1880:	add	x11, x11, #0x5c
0x2519e1884:	mov	x12, #0xd1fa
0x2519e1888:	movk	x12, #0x6af3, lsl #16
0x2519e188c:	movk	x12, #0xf100, lsl #32
0x2519e1890:	movk	x12, #0x7978, lsl #48
0x2519e1894:	sub	x13, x29, #0x88
0x2519e1898:	orr	w14, w13, w12
0x2519e189c:	and	w12, w13, w12
0x2519e18a0:	add	w13, w24, #0x37a
0x2519e18a4:	orn	w12, w12, w14
0x2519e18a8:	mov	w14, #0xeb6c
0x2519e18ac:	movk	w14, #0xa824, lsl #16
0x2519e18b0:	eor	w12, w12, w14
0x2519e18b4:	mov	w14, #0x9f29
0x2519e18b8:	movk	w14, #0x6c83, lsl #16
0x2519e18bc:	mul	w12, w12, w14
0x2519e18c0:	eor	w12, w13, w12
0x2519e18c4:	stur	w12, [x29, #-0x84]
0x2519e18c8:	ldr	x12, [sp, #0x10]
0x2519e18cc:	stp	x11, x12, [x29, #-0x80]
0x2519e18d0:	add	x11, sp, #0xcc
0x2519e18d4:	stp	x11, x10, [x29, #-0x70]
0x2519e18d8:	ldr	w10, [x25]
0x2519e18dc:	ldr	w11, [x4]
0x2519e18e0:	eor	w10, w10, w16
0x2519e18e4:	eor	w10, w10, w11
0x2519e18e8:	mul	w10, w10, w15
0x2519e18ec:	ldr	x11, [sp, #0x58]
0x2519e18f0:	add	x11, x11, w10, uxtb
0x2519e18f4:	ldrb	w11, [x11]
0x2519e18f8:	mov	w12, #0xb4
0x2519e18fc:	eor	w11, w11, w12
0x2519e1900:	ldr	x12, [sp, #0x50]
0x2519e1904:	ldrb	w11, [x12, w11, uxtw]
0x2519e1908:	and	w22, w8, w9
0x2519e190c:	eor	w8, w10, w11
0x2519e1910:	and	w8, w8, #0xff
0x2519e1914:	add	w8, w8, #0x404
0x2519e1918:	ldr	x8, [x26, w8, uxtw #3]
0x2519e191c:	sub	x0, x29, #0x88
0x2519e1920:	mov	x17, #0xc7d4
0x2519e1924:	blraa	x8, x17
0x2519e1928:	ldr	x0, [sp, #0x40]
0x2519e192c:	ldp	x12, x4, [sp, #0x88]
0x2519e1930:	mov	x16, #0xb4fa
0x2519e1934:	movk	x16, #0x6d3c, lsl #16
0x2519e1938:	movk	x16, #0x2a54, lsl #32
0x2519e193c:	movk	x16, #0x375b, lsl #48
0x2519e1940:	mov	w15, #0x1f79
0x2519e1944:	movk	w15, #0xd3ef, lsl #16
0x2519e1948:	ldur	w13, [x29, #-0x88]
0x2519e194c:	mov	w8, #0x14f8
0x2519e1950:	movk	w8, #0x1455, lsl #16
0x2519e1954:	add	w8, w8, w22
0x2519e1958:	add	w8, w8, w21
0x2519e195c:	sub	w8, w8, #0x2b5
0x2519e1960:	cmp	w13, w8
0x2519e1964:	cset	w8, eq
0x2519e1968:	mov	w9, #0x2f5
0x2519e196c:	mul	w8, w8, w9
0x2519e1970:	orr	w8, w8, w24
0x2519e1974:	ldr	x8, [x26, w8, sxtw #3]
0x2519e1978:	mov	x17, #0x77dd
0x2519e197c:	braa	x8, x17
0x2519e1980:	ldrb	w8, [x25, #4]
0x2519e1984:	add	w9, w27, #0x33
0x2519e1988:	orr	w9, w9, #0x88888888
0x2519e198c:	mov	w10, #0x62
0x2519e1990:	eor	w10, w8, w10
0x2519e1994:	eor	w9, w10, w9
0x2519e1998:	mov	w10, #0x9c
0x2519e199c:	and	w8, w10, w8, lsl #1
0x2519e19a0:	add	w8, w9, w8
0x2519e19a4:	add	x9, sp, #0xc
0x2519e19a8:	mov	w10, #0xeb04
0x2519e19ac:	movk	w10, #0x113e, lsl #16
0x2519e19b0:	and	w10, w9, w10
0x2519e19b4:	lsl	w10, w10, #1
0x2519e19b8:	sub	w9, w10, w9
0x2519e19bc:	mov	w10, #0x14f9
0x2519e19c0:	movk	w10, #0x6ec1, lsl #16
0x2519e19c4:	add	w9, w9, w10
0x2519e19c8:	mov	w10, #0x2125
0x2519e19cc:	movk	w10, #0x6225, lsl #16
0x2519e19d0:	eor	w9, w9, w10
0x2519e19d4:	mov	w10, #0x97f7
0x2519e19d8:	movk	w10, #0xb9f0, lsl #16
0x2519e19dc:	mul	w9, w9, w10
0x2519e19e0:	eor	w8, w9, w8
0x2519e19e4:	eor	w8, w8, #0x80
0x2519e19e8:	strb	w8, [sp, #0x10]
0x2519e19ec:	sub	w8, w27, w9
0x2519e19f0:	mov	w9, #0xe066
0x2519e19f4:	movk	w9, #0x7665, lsl #16
0x2519e19f8:	add	w8, w8, w9
0x2519e19fc:	str	w8, [sp, #0xc]
0x2519e1a00:	ldr	w8, [x22]
0x2519e1a04:	ldr	w9, [x23]
0x2519e1a08:	add	w8, w9, w8
0x2519e1a0c:	eor	w8, w8, w20
0x2519e1a10:	mul	w8, w8, w21
0x2519e1a14:	adrp	x9, #0x27612b000
0x2519e1a18:	add	x9, x9, #0xa70
0x2519e1a1c:	ldr	x10, [x9]
0x2519e1a20:	add	x10, x10, w8, uxtb
0x2519e1a24:	ldurb	w10, [x10, #-8]
0x2519e1a28:	mov	w11, #0x3b
0x2519e1a2c:	eor	w10, w10, w11
0x2519e1a30:	ldr	x9, [x9, #0xb0]
0x2519e1a34:	add	x9, x9, x10
0x2519e1a38:	ldurb	w9, [x9, #-8]
0x2519e1a3c:	eor	w8, w9, w8
0x2519e1a40:	and	w8, w8, #0xff
0x2519e1a44:	add	w8, w8, #0x3ae
0x2519e1a48:	ldr	x8, [x24, w8, uxtw #3]
0x2519e1a4c:	add	x0, sp, #0xc
0x2519e1a50:	mov	x17, #0x45fc
0x2519e1a54:	blraa	x8, x17
0x2519e1a58:	ldr	w8, [sp, #0x14]
0x2519e1a5c:	str	w8, [x19, #8]
0x2519e1a60:	ldr	x8, [sp, #0x18]
0x2519e1a64:	adrp	x9, #0x2681b4000
0x2519e1a68:	ldr	x9, [x9, #0xee0]
0x2519e1a6c:	ldr	x9, [x9]
0x2519e1a70:	cmp	x9, x8
0x2519e1a74:	b.ne	#0x2519e1a98
0x2519e1a78:	ldp	x29, x30, [sp, #0x70]
0x2519e1a7c:	ldp	x20, x19, [sp, #0x60]
0x2519e1a80:	ldp	x22, x21, [sp, #0x50]
0x2519e1a84:	ldp	x24, x23, [sp, #0x40]
0x2519e1a88:	ldp	x26, x25, [sp, #0x30]
0x2519e1a8c:	ldp	x28, x27, [sp, #0x20]
0x2519e1a90:	add	sp, sp, #0x80
0x2519e1a94:	retab	
0x2519e1a98:	bl	#0x2580f4380
0x2519e1a9c:	ldp	x10, x9, [x0, #0x10]
0x2519e1aa0:	mov	w12, #0x23e
0x2519e1aa4:	eor	w11, w11, w12
0x2519e1aa8:	str	wzr, [x9]
0x2519e1aac:	str	x8, [x10, #0x918]
0x2519e1ab0:	ldr	w12, [x9]
0x2519e1ab4:	add	w12, w12, #0x100
0x2519e1ab8:	str	w12, [x9]
0x2519e1abc:	add	x12, x8, #0x100
0x2519e1ac0:	str	x12, [x10, #0x928]
0x2519e1ac4:	ldr	w12, [x9]
0x2519e1ac8:	add	w12, w12, #0x100
0x2519e1acc:	str	w12, [x9]
0x2519e1ad0:	add	x12, x8, #0x200
0x2519e1ad4:	str	x12, [x10, #0x938]
0x2519e1ad8:	ldr	w12, [x9]
0x2519e1adc:	add	w12, w12, #0x100
0x2519e1ae0:	str	w12, [x9]
0x2519e1ae4:	add	x12, x8, #0x300
0x2519e1ae8:	str	x12, [x10, #0x948]
0x2519e1aec:	ldr	w12, [x9]
0x2519e1af0:	add	w12, w12, #0x100
0x2519e1af4:	str	w12, [x9]
0x2519e1af8:	add	x12, x8, #0x400
0x2519e1afc:	str	x12, [x10, #0x958]
0x2519e1b00:	ldr	w12, [x9]
0x2519e1b04:	add	w12, w12, #0x100
0x2519e1b08:	str	w12, [x9]
0x2519e1b0c:	add	x12, x8, #0x500
0x2519e1b10:	str	x12, [x10, #0x968]
0x2519e1b14:	ldr	w12, [x9]
0x2519e1b18:	add	w12, w12, #0x100
0x2519e1b1c:	str	w12, [x9]
0x2519e1b20:	add	x12, x8, #0x600
0x2519e1b24:	str	x12, [x10, #0x978]
0x2519e1b28:	ldr	w12, [x9]
0x2519e1b2c:	add	w11, w11, w12
0x2519e1b30:	sub	w11, w11, #0x2bf
0x2519e1b34:	str	w11, [x9]
0x2519e1b38:	add	x11, x8, #0x700
0x2519e1b3c:	str	x11, [x10, #0x988]
0x2519e1b40:	ldr	w11, [x9]
0x2519e1b44:	add	w11, w11, #0x100
0x2519e1b48:	str	w11, [x9]
0x2519e1b4c:	add	x11, x8, #0x800
0x2519e1b50:	str	x11, [x10, #0x998]
0x2519e1b54:	ldr	w11, [x9]
0x2519e1b58:	add	w11, w11, #0x100
0x2519e1b5c:	str	w11, [x9]
0x2519e1b60:	add	x11, x8, #0x900
0x2519e1b64:	str	x11, [x10, #0x9a8]
0x2519e1b68:	ldr	w11, [x9]
0x2519e1b6c:	add	w11, w11, #0x100
0x2519e1b70:	str	w11, [x9]
0x2519e1b74:	add	x11, x8, #0xa00
0x2519e1b78:	str	x11, [x10, #0x9b8]
0x2519e1b7c:	ldr	w11, [x9]
0x2519e1b80:	add	w11, w11, #0x100
0x2519e1b84:	str	w11, [x9]
0x2519e1b88:	add	x11, x8, #0xb00
0x2519e1b8c:	str	x11, [x10, #0x9c8]
0x2519e1b90:	ldr	w11, [x9]
0x2519e1b94:	add	w11, w11, #0x100
0x2519e1b98:	str	w11, [x9]
0x2519e1b9c:	add	x11, x8, #0xc00
0x2519e1ba0:	str	x11, [x10, #0x9d8]
0x2519e1ba4:	ldr	w11, [x9]
0x2519e1ba8:	add	w11, w11, #0x100
0x2519e1bac:	str	w11, [x9]
0x2519e1bb0:	add	x11, x8, #0xd00
0x2519e1bb4:	str	x11, [x10, #0x9e8]
0x2519e1bb8:	ldr	w11, [x9]
0x2519e1bbc:	add	w11, w11, #0x100
0x2519e1bc0:	str	w11, [x9]
0x2519e1bc4:	add	x11, x8, #0xe00
0x2519e1bc8:	str	x11, [x10, #0x9f8]
0x2519e1bcc:	ldr	w11, [x9]
0x2519e1bd0:	add	w11, w11, #0x100
0x2519e1bd4:	str	w11, [x9]
0x2519e1bd8:	add	x8, x8, #0xf00
0x2519e1bdc:	str	x8, [x10, #0xa08]
0x2519e1be0:	ldr	w8, [x9]
0x2519e1be4:	add	w8, w8, #0x100
0x2519e1be8:	str	w8, [x9]
0x2519e1bec:	mov	w8, #0x14f8
0x2519e1bf0:	movk	w8, #0x1455, lsl #16
0x2519e1bf4:	b	#0x251a0332c
0x2519e1bf8:	add	x15, sp, #0x148
0x2519e1bfc:	ldr	w7, [sp, #0xc4]
0x2519e1c00:	mov	w8, #0xf99d
0x2519e1c04:	movk	w8, #0x85c9, lsl #16
0x2519e1c08:	add	w8, w8, w7
0x2519e1c0c:	add	w14, w8, #0x10
0x2519e1c10:	b	#0x2519fc1cc
0x2519e1c14:	sub	w8, w24, #0x26f
0x2519e1c18:	str	w21, [sp, #0x94]
0x2519e1c1c:	b	#0x2519f4520
0x2519e1c20:	mov	w8, #0x7d53
0x2519e1c24:	movk	w8, #0x872b, lsl #16
0x2519e1c28:	add	w8, w28, w8
0x2519e1c2c:	mov	w9, #0x806a
0x2519e1c30:	movk	w9, #0x78d4, lsl #16
0x2519e1c34:	and	w8, w8, w9
0x2519e1c38:	str	w8, [sp, #0x118]
0x2519e1c3c:	add	w21, w8, #0x74
0x2519e1c40:	mov	w8, #0xd0
0x2519e1c44:	and	w8, w8, w19, lsl #1
0x2519e1c48:	mov	w9, #0xb6
0x2519e1c4c:	eor	w9, w21, w9
0x2519e1c50:	sub	w8, w19, w8
0x2519e1c54:	add	w8, w8, w9
0x2519e1c58:	mov	w9, #0x68
0x2519e1c5c:	eor	w8, w8, w9
0x2519e1c60:	ldr	x10, [sp, #0x60]
0x2519e1c64:	strb	w8, [x10]
0x2519e1c68:	mov	x9, #0x8f01
0x2519e1c6c:	movk	x9, #0x8b9, lsl #16
0x2519e1c70:	movk	x9, #0x3493, lsl #32
0x2519e1c74:	movk	x9, #0x6a2f, lsl #48
0x2519e1c78:	sub	x23, x29, #0x90
0x2519e1c7c:	orr	w8, w9, w23
0x2519e1c80:	and	w9, w23, w9
0x2519e1c84:	sub	w8, w8, w9
0x2519e1c88:	mov	w9, #0xbadd
0x2519e1c8c:	movk	w9, #0x45d, lsl #16
0x2519e1c90:	eor	w8, w8, w9
0x2519e1c94:	mov	w9, #0x97f7
0x2519e1c98:	movk	w9, #0xb9f0, lsl #16
0x2519e1c9c:	mul	w8, w8, w9
0x2519e1ca0:	add	x22, sp, #0x140
0x2519e1ca4:	str	x10, [x22, #0xc78]
0x2519e1ca8:	ldr	x25, [sp, #0xe8]
0x2519e1cac:	str	x25, [x22, #0xc68]
0x2519e1cb0:	add	w9, w8, w28
0x2519e1cb4:	add	w9, w9, #0x41
0x2519e1cb8:	mov	w10, #0xb74b
0x2519e1cbc:	movk	w10, #0xdcb, lsl #16
0x2519e1cc0:	eor	w8, w8, w10
0x2519e1cc4:	stur	w9, [x29, #-0x80]
0x2519e1cc8:	stur	w8, [x29, #-0x90]
0x2519e1ccc:	ldr	w8, [x26]
0x2519e1cd0:	ldr	x20, [sp, #0xb8]
0x2519e1cd4:	ldr	w9, [x20]
0x2519e1cd8:	sub	w8, w9, w8
0x2519e1cdc:	eor	w8, w8, w27
0x2519e1ce0:	mov	w24, #0x1f79
0x2519e1ce4:	movk	w24, #0xd3ef, lsl #16
0x2519e1ce8:	mul	w8, w8, w24
0x2519e1cec:	ldr	x9, [sp, #0xa8]
0x2519e1cf0:	add	x9, x9, w8, uxtb
0x2519e1cf4:	ldrb	w9, [x9]
0x2519e1cf8:	mov	w10, #0x99
0x2519e1cfc:	eor	w9, w9, w10
0x2519e1d00:	ldr	x10, [sp, #0xb0]
0x2519e1d04:	ldrb	w9, [x10, w9, uxtw]
0x2519e1d08:	eor	w8, w8, w9
0x2519e1d0c:	and	w8, w8, #0xff
0x2519e1d10:	add	w8, w8, #0x32b
0x2519e1d14:	ldr	x8, [x16, w8, uxtw #3]
0x2519e1d18:	sub	x0, x29, #0x90
0x2519e1d1c:	mov	x17, #0xbad3
0x2519e1d20:	blraa	x8, x17
0x2519e1d24:	ldr	x8, [sp, #0x68]
0x2519e1d28:	add	x8, x8, x19, lsl #4
0x2519e1d2c:	mov	x10, #0x329f
0x2519e1d30:	movk	x10, #0x64ea, lsl #16
0x2519e1d34:	movk	x10, #0xeb7b, lsl #32
0x2519e1d38:	movk	x10, #0xb0e9, lsl #48
0x2519e1d3c:	and	w9, w23, w10
0x2519e1d40:	add	w10, w23, w10
0x2519e1d44:	sub	w9, w10, w9, lsl #1
0x2519e1d48:	mov	w10, #0xdef6
0x2519e1d4c:	movk	w10, #0xe9c8, lsl #16
0x2519e1d50:	eor	w9, w9, w10
0x2519e1d54:	mov	w10, #0x72f
0x2519e1d58:	movk	w10, #0x132d, lsl #16
0x2519e1d5c:	madd	w9, w9, w10, w28
0x2519e1d60:	sub	w9, w9, #0x16b
0x2519e1d64:	stur	w9, [x29, #-0x80]
0x2519e1d68:	str	x25, [x22, #0xc68]
0x2519e1d6c:	str	x8, [x22, #0xc60]
0x2519e1d70:	ldr	w8, [x26]
0x2519e1d74:	ldr	w9, [x20]
0x2519e1d78:	add	w8, w9, w8
0x2519e1d7c:	eor	w8, w8, w27
0x2519e1d80:	mul	w8, w8, w24
0x2519e1d84:	ldr	x9, [sp, #0x98]
0x2519e1d88:	add	x9, x9, w8, uxtb
0x2519e1d8c:	ldrb	w9, [x9]
0x2519e1d90:	mov	w10, #0x73
0x2519e1d94:	eor	w9, w9, w10
0x2519e1d98:	ldr	x10, [sp, #0x90]
0x2519e1d9c:	ldrb	w9, [x10, w9, uxtw]
0x2519e1da0:	eor	w8, w8, w9
0x2519e1da4:	and	w8, w8, #0xff
0x2519e1da8:	add	w8, w8, #0x417
0x2519e1dac:	ldr	x9, [sp, #0x120]
0x2519e1db0:	ldr	x8, [x9, w8, uxtw #3]
0x2519e1db4:	sub	x0, x29, #0x90
0x2519e1db8:	mov	x17, #0xa98
0x2519e1dbc:	blraa	x8, x17
0x2519e1dc0:	ldr	x16, [sp, #0x120]
0x2519e1dc4:	add	x19, x19, #1
0x2519e1dc8:	cmp	x19, #9
0x2519e1dcc:	cset	w8, eq
0x2519e1dd0:	mov	w9, #0x15
0x2519e1dd4:	mul	w8, w8, w9
0x2519e1dd8:	eor	w8, w28, w8
0x2519e1ddc:	ldr	x8, [x16, w8, uxtw #3]
0x2519e1de0:	mov	x17, #0x93d0
0x2519e1de4:	braa	x8, x17
0x2519e1de8:	b	#0x251a283c8
0x2519e1dec:	ldr	x11, [x0]
0x2519e1df0:	mov	w8, #0x133
0x2519e1df4:	sub	x12, x29, #0x80
0x2519e1df8:	ldr	w13, [x21]
0x2519e1dfc:	eor	w8, w9, w8
0x2519e1e00:	ldr	w14, [x27]
0x2519e1e04:	sub	w15, w14, w13
0x2519e1e08:	eor	w15, w15, w7
0x2519e1e0c:	mul	w15, w15, w25
0x2519e1e10:	and	x16, x15, #0xff
0x2519e1e14:	add	x17, x3, x16
0x2519e1e18:	ldrb	w17, [x17]
0x2519e1e1c:	eor	w17, w17, #0xfe
0x2519e1e20:	ldrb	w17, [x2, w17, uxtw]
0x2519e1e24:	mov	w1, #0xb9
0x2519e1e28:	eor	w17, w15, w17
0x2519e1e2c:	add	x16, x6, x16
0x2519e1e30:	ldrb	w16, [x16]
0x2519e1e34:	eor	w16, w16, w1
0x2519e1e38:	ldrb	w16, [x24, w16, uxtw]
0x2519e1e3c:	eor	w15, w15, w16
0x2519e1e40:	and	w15, w15, #0xff
0x2519e1e44:	sub	w15, w15, #0x1e
0x2519e1e48:	ldr	x15, [x20, w15, sxtw #3]
0x2519e1e4c:	add	x15, x15, x10
0x2519e1e50:	subs	x10, x10, #1
0x2519e1e54:	and	w16, w17, #0xff
0x2519e1e58:	sub	w16, w16, #0x42
0x2519e1e5c:	ldr	x16, [x20, w16, sxtw #3]
0x2519e1e60:	ldrb	w11, [x11, x10]
0x2519e1e64:	add	x12, x12, x10
0x2519e1e68:	eor	w13, w13, w7
0x2519e1e6c:	eor	w13, w13, w14
0x2519e1e70:	mul	w13, w13, w25
0x2519e1e74:	add	x14, x6, w13, uxtb
0x2519e1e78:	add	x16, x16, x10
0x2519e1e7c:	ldrb	w14, [x14]
0x2519e1e80:	eor	w14, w14, w1
0x2519e1e84:	ldrb	w14, [x24, w14, uxtw]
0x2519e1e88:	eor	w13, w13, w14
0x2519e1e8c:	ldurb	w14, [x16, #-8]
0x2519e1e90:	and	w13, w13, #0xff
0x2519e1e94:	sub	w13, w13, #0x42
0x2519e1e98:	ldr	x13, [x20, w13, sxtw #3]
0x2519e1e9c:	add	x13, x13, x10
0x2519e1ea0:	ldurb	w13, [x13, #-0xc]
0x2519e1ea4:	ldurb	w15, [x15, #-7]
0x2519e1ea8:	mov	w16, #-0x6b
0x2519e1eac:	mul	w16, w10, w16
0x2519e1eb0:	eor	w16, w8, w16
0x2519e1eb4:	eor	w11, w16, w11
0x2519e1eb8:	eor	w11, w11, w14
0x2519e1ebc:	eor	w13, w13, w15
0x2519e1ec0:	eor	w11, w11, w13
0x2519e1ec4:	mov	w13, #0x89
0x2519e1ec8:	cset	w14, eq
0x2519e1ecc:	mov	w15, #0x3af
0x2519e1ed0:	eor	w11, w11, w13
0x2519e1ed4:	mul	w13, w14, w15
0x2519e1ed8:	eor	w13, w13, w9
0x2519e1edc:	ldr	x13, [x28, w13, uxtw #3]
0x2519e1ee0:	strb	w11, [x12]
0x2519e1ee4:	mov	x17, #0x958f
0x2519e1ee8:	braa	x13, x17

; AirPlaySender 0x2519fa410-0x2519fb3a4; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519fa410:	pacibsp	
0x2519fa414:	sub	sp, sp, #0xa0
0x2519fa418:	stp	x28, x27, [sp, #0x40]
0x2519fa41c:	stp	x26, x25, [sp, #0x50]
0x2519fa420:	stp	x24, x23, [sp, #0x60]
0x2519fa424:	stp	x22, x21, [sp, #0x70]
0x2519fa428:	stp	x20, x19, [sp, #0x80]
0x2519fa42c:	stp	x29, x30, [sp, #0x90]
0x2519fa430:	add	x29, sp, #0x90
0x2519fa434:	mov	x20, x1
0x2519fa438:	str	x0, [sp, #8]
0x2519fa43c:	adrp	x8, #0x2681b4000
0x2519fa440:	ldr	x8, [x8, #0xee0]
0x2519fa444:	ldr	x8, [x8]
0x2519fa448:	str	x8, [sp, #0x38]
0x2519fa44c:	mov	x22, #0xb4fa
0x2519fa450:	movk	x22, #0x6d3c, lsl #16
0x2519fa454:	movk	x22, #0x2a54, lsl #32
0x2519fa458:	movk	x22, #0x375b, lsl #48
0x2519fa45c:	mov	w21, #0x1f79
0x2519fa460:	movk	w21, #0xd3ef, lsl #16
0x2519fa464:	adrp	x8, #0x26e7db000
0x2519fa468:	ldr	w10, [x8, #0x508]
0x2519fa46c:	adrp	x9, #0x26e7db000
0x2519fa470:	ldr	w11, [x9, #0x410]
0x2519fa474:	eor	w10, w10, w22
0x2519fa478:	eor	w10, w10, w11
0x2519fa47c:	adrp	x12, #0x251c70000
0x2519fa480:	add	x12, x12, #0xd70
0x2519fa484:	mul	w10, w10, w21
0x2519fa488:	add	x12, x12, w10, uxtb
0x2519fa48c:	ldrb	w12, [x12]
0x2519fa490:	mov	w13, #0x99
0x2519fa494:	adrp	x14, #0x251c6d000
0x2519fa498:	add	x14, x14, #0x190
0x2519fa49c:	eor	w12, w12, w13
0x2519fa4a0:	ldrb	w12, [x14, w12, uxtw]
0x2519fa4a4:	eor	w10, w10, w12
0x2519fa4a8:	and	w10, w10, #0xff
0x2519fa4ac:	sub	w12, w10, #0x98
0x2519fa4b0:	adrp	x10, #0x27612b000
0x2519fa4b4:	add	x10, x10, #0x8f0
0x2519fa4b8:	ldr	x24, [x10, w12, sxtw #3]
0x2519fa4bc:	ldr	x12, [x24, #-4]!
0x2519fa4c0:	mov	w19, #0x14f8
0x2519fa4c4:	movk	w19, #0x1455, lsl #16
0x2519fa4c8:	eor	w11, w22, w11
0x2519fa4cc:	eor	w11, w12, w11
0x2519fa4d0:	mul	w11, w11, w21
0x2519fa4d4:	ldr	x13, [x10, #0x2b0]
0x2519fa4d8:	add	x13, x13, w11, uxtb
0x2519fa4dc:	ldurb	w13, [x13, #-8]
0x2519fa4e0:	mov	w14, #0x1a
0x2519fa4e4:	eor	w13, w13, w14
0x2519fa4e8:	ldr	x14, [x10, #0x510]
0x2519fa4ec:	ldrb	w13, [x14, w13, uxtw]
0x2519fa4f0:	eor	w11, w13, w11
0x2519fa4f4:	and	w11, w11, #0xff
0x2519fa4f8:	sub	w11, w11, #0x40
0x2519fa4fc:	ldr	x25, [x10, w11, sxtw #3]
0x2519fa500:	ldr	x11, [x25]
0x2519fa504:	sub	x11, x11, x12
0x2519fa508:	add	x12, sp, #0x10
0x2519fa50c:	sub	x11, x11, x12
0x2519fa510:	mul	x12, x22, x21
0x2519fa514:	madd	x12, x11, x21, x12
0x2519fa518:	eor	x11, x11, x22
0x2519fa51c:	mul	x11, x11, x21
0x2519fa520:	str	x12, [x24]
0x2519fa524:	str	x11, [x25]
0x2519fa528:	add	x11, sp, #0x18
0x2519fa52c:	mov	w12, #0x8bdf
0x2519fa530:	movk	w12, #0x84, lsl #16
0x2519fa534:	orr	w12, w11, w12
0x2519fa538:	sub	w12, w12, w11
0x2519fa53c:	mov	w13, #0x7420
0x2519fa540:	movk	w13, #0xff7b, lsl #16
0x2519fa544:	and	w11, w11, w13
0x2519fa548:	add	w11, w12, w11
0x2519fa54c:	mov	w12, #0x4eb6
0x2519fa550:	movk	w12, #0x3dac, lsl #16
0x2519fa554:	eor	w11, w11, w12
0x2519fa558:	mov	w12, #0x9f29
0x2519fa55c:	movk	w12, #0x6c83, lsl #16
0x2519fa560:	mov	w13, #0x25fc
0x2519fa564:	movk	w13, #0xdb53, lsl #16
0x2519fa568:	msub	w11, w11, w12, w13
0x2519fa56c:	str	w11, [sp, #0x1c]
0x2519fa570:	ldr	w11, [x24]
0x2519fa574:	ldr	w12, [x25]
0x2519fa578:	add	w11, w12, w11
0x2519fa57c:	eor	w11, w11, w22
0x2519fa580:	mul	w11, w11, w21
0x2519fa584:	ldr	x12, [x10, #0x180]
0x2519fa588:	add	x12, x12, w11, uxtb
0x2519fa58c:	ldurb	w12, [x12, #-8]
0x2519fa590:	mov	w13, #0x3b
0x2519fa594:	eor	w12, w12, w13
0x2519fa598:	ldr	x14, [x10, #0x230]
0x2519fa59c:	add	x12, x14, x12
0x2519fa5a0:	ldurb	w12, [x12, #-8]
0x2519fa5a4:	eor	w11, w12, w11
0x2519fa5a8:	and	w11, w11, #0xff
0x2519fa5ac:	add	w11, w11, #0x3bb
0x2519fa5b0:	ldr	w8, [x8, #0x508]
0x2519fa5b4:	ldr	w9, [x9, #0x410]
0x2519fa5b8:	sub	w8, w9, w8
0x2519fa5bc:	eor	w8, w8, w22
0x2519fa5c0:	mul	w8, w8, w21
0x2519fa5c4:	adrp	x9, #0x251c70000
0x2519fa5c8:	add	x9, x9, #0xe70
0x2519fa5cc:	add	x9, x9, w8, uxtb
0x2519fa5d0:	ldrb	w9, [x9]
0x2519fa5d4:	eor	w9, w9, w13
0x2519fa5d8:	adrp	x12, #0x251c6d000
0x2519fa5dc:	add	x12, x12, #0x290
0x2519fa5e0:	ldrb	w9, [x12, w9, uxtw]
0x2519fa5e4:	eor	w8, w8, w9
0x2519fa5e8:	and	w8, w8, #0xff
0x2519fa5ec:	sub	w8, w8, #0x75
0x2519fa5f0:	ldr	x8, [x10, w8, sxtw #3]
0x2519fa5f4:	sub	x26, x8, #0xc
0x2519fa5f8:	ldr	x8, [x26, w11, uxtw #3]
0x2519fa5fc:	add	x0, sp, #0x18
0x2519fa600:	mov	x17, #0xf9e7
0x2519fa604:	blraa	x8, x17
0x2519fa608:	ldr	w8, [sp, #0x18]
0x2519fa60c:	cmp	w8, w19
0x2519fa610:	cset	w9, eq
0x2519fa614:	mov	w10, #0x3d1
0x2519fa618:	mul	w9, w9, w10
0x2519fa61c:	mov	w10, #0x172
0x2519fa620:	eor	w9, w9, w10
0x2519fa624:	ldr	x9, [x26, w9, uxtw #3]
0x2519fa628:	mov	x17, #0xbc92
0x2519fa62c:	braa	x9, x17
0x2519fa630:	add	x11, x26, x10
0x2519fa634:	ldrb	w11, [x11]
0x2519fa638:	add	x12, x19, x10
0x2519fa63c:	eor	w11, w11, w20
0x2519fa640:	strb	w11, [x12]
0x2519fa644:	cmp	x10, #0x3f
0x2519fa648:	add	x10, x10, #1
0x2519fa64c:	cset	w11, eq
0x2519fa650:	mul	w11, w11, w9
0x2519fa654:	eor	w11, w11, w8
0x2519fa658:	ldr	x11, [x25, w11, sxtw #3]
0x2519fa65c:	mov	x17, #0x91df
0x2519fa660:	braa	x11, x17
0x2519fa664:	mov	w9, #0x20c
0x2519fa668:	eor	w8, w8, w9
0x2519fa66c:	mov	w9, #0x53
0x2519fa670:	mul	w8, w8, w9
0x2519fa674:	mov	w9, w13
0x2519fa678:	sub	w10, w8, #0x19f
0x2519fa67c:	orr	w11, w10, #0x3c
0x2519fa680:	add	x10, x9, #1
0x2519fa684:	strb	w21, [x3, x9]
0x2519fa688:	cmp	x10, #0x38
0x2519fa68c:	cset	w12, ne
0x2519fa690:	add	w9, w11, #0x35a
0x2519fa694:	mul	w11, w12, w9
0x2519fa698:	eor	w11, w11, w8
0x2519fa69c:	ldr	x11, [x19, w11, sxtw #3]
0x2519fa6a0:	mov	x17, #0xc993
0x2519fa6a4:	braa	x11, x17
0x2519fa6a8:	stp	x27, x19, [sp, #0x80]
0x2519fa6ac:	stur	w12, [x29, #-0xe4]
0x2519fa6b0:	stur	x7, [x29, #-0x98]
0x2519fa6b4:	str	x0, [sp, #0x70]
0x2519fa6b8:	mov	w8, #0xf3
0x2519fa6bc:	eor	w8, w14, w8
0x2519fa6c0:	stur	w8, [x29, #-0xc0]
0x2519fa6c4:	mov	w8, #0x1c9
0x2519fa6c8:	eor	w8, w14, w8
0x2519fa6cc:	ldr	w9, [x26]
0x2519fa6d0:	ldr	w10, [x28]
0x2519fa6d4:	eor	w9, w9, w24
0x2519fa6d8:	eor	w9, w9, w10
0x2519fa6dc:	mul	w9, w9, w25
0x2519fa6e0:	str	x30, [sp, #0x78]
0x2519fa6e4:	add	x10, x30, w9, uxtb
0x2519fa6e8:	ldrb	w10, [x10]
0x2519fa6ec:	mov	w11, #0xb4
0x2519fa6f0:	eor	w10, w10, w11
0x2519fa6f4:	ldr	x11, [sp, #0x98]
0x2519fa6f8:	ldrb	w10, [x11, w10, uxtw]
0x2519fa6fc:	add	w19, w8, w8, lsl #4
0x2519fa700:	eor	w8, w9, w10
0x2519fa704:	and	w8, w8, #0xff
0x2519fa708:	add	w8, w8, #0x3e4
0x2519fa70c:	ldr	x8, [x21, w8, uxtw #3]
0x2519fa710:	mov	w0, #0x404
0x2519fa714:	mov	x20, x3
0x2519fa718:	mov	x23, x4
0x2519fa71c:	stur	w14, [x29, #-0x90]
0x2519fa720:	mov	x17, #0xaa22
0x2519fa724:	blraa	x8, x17
0x2519fa728:	mov	x27, x0
0x2519fa72c:	ldr	w8, [x26]
0x2519fa730:	ldr	w9, [x28]
0x2519fa734:	add	w8, w9, w8
0x2519fa738:	eor	w8, w8, w24
0x2519fa73c:	mul	w8, w8, w25
0x2519fa740:	str	x20, [sp, #0x208]
0x2519fa744:	add	x9, x20, w8, uxtb
0x2519fa748:	ldrb	w9, [x9]
0x2519fa74c:	mov	w10, #0x69
0x2519fa750:	eor	w9, w9, w10
0x2519fa754:	str	x23, [sp, #0x200]
0x2519fa758:	ldrb	w9, [x23, w9, uxtw]
0x2519fa75c:	eor	w8, w8, w9
0x2519fa760:	and	w8, w8, #0xff
0x2519fa764:	add	w8, w8, #0x355
0x2519fa768:	ldr	x8, [x21, w8, uxtw #3]
0x2519fa76c:	mov	w0, #0x404
0x2519fa770:	mov	x17, #0xaa22
0x2519fa774:	blraa	x8, x17
0x2519fa778:	ldur	w10, [x29, #-0xc0]
0x2519fa77c:	stp	x27, x0, [x29, #-0xa8]
0x2519fa780:	cmp	x27, #0
0x2519fa784:	ccmp	x0, #0, #4, ne
0x2519fa788:	cset	w8, eq
0x2519fa78c:	mov	w9, #0x311
0x2519fa790:	eor	w9, w10, w9
0x2519fa794:	str	w19, [sp, #0x1f8]
0x2519fa798:	eor	w9, w9, w19
0x2519fa79c:	mul	w8, w8, w9
0x2519fa7a0:	ldur	w9, [x29, #-0x90]
0x2519fa7a4:	eor	w8, w8, w9
0x2519fa7a8:	stur	x21, [x29, #-0x90]
0x2519fa7ac:	ldr	x8, [x21, w8, sxtw #3]
0x2519fa7b0:	mov	w9, #-0xa785
0x2519fa7b4:	str	w9, [sp, #0x1fc]
0x2519fa7b8:	mov	x17, #0x3aba
0x2519fa7bc:	braa	x8, x17
0x2519fa7c0:	mov	w13, w12
0x2519fa7c4:	mov	w11, w10
0x2519fa7c8:	mov	w10, w16
0x2519fa7cc:	mov	w9, #0x480
0x2519fa7d0:	movk	w9, #0x7a36, lsl #16
0x2519fa7d4:	add	w9, w9, w8
0x2519fa7d8:	add	w9, w9, #0xb6
0x2519fa7dc:	add	x12, x11, #1
0x2519fa7e0:	add	x11, x22, x11
0x2519fa7e4:	ldrb	w14, [x11]
0x2519fa7e8:	eor	x11, x9, x4
0x2519fa7ec:	add	x11, x11, x13
0x2519fa7f0:	strb	w14, [x15, x13]
0x2519fa7f4:	cmp	x12, x10
0x2519fa7f8:	cset	w13, eq
0x2519fa7fc:	mul	w13, w13, w0
0x2519fa800:	eor	w13, w13, w8
0x2519fa804:	ldr	x13, [x27, w13, sxtw #3]
0x2519fa808:	mov	x17, #0xc042
0x2519fa80c:	braa	x13, x17
0x2519fa810:	add	x12, sp, #0x1bc
0x2519fa814:	ldr	w7, [sp, #0xc4]
0x2519fa818:	mov	w8, #0xf99d
0x2519fa81c:	movk	w8, #0x85c9, lsl #16
0x2519fa820:	add	w8, w8, w7
0x2519fa824:	add	w8, w8, #0xa
0x2519fa828:	ldr	x11, [sp, #0x30]
0x2519fa82c:	ldrb	w9, [x11]
0x2519fa830:	lsl	x10, x9, #6
0x2519fa834:	sub	x9, x10, x9, lsl #3
0x2519fa838:	add	x10, x11, #4
0x2519fa83c:	add	x11, x10, x9
0x2519fa840:	add	x9, x11, #0x14
0x2519fa844:	str	x9, [sp, #0x40]
0x2519fa848:	b	#0x251a1e614
0x2519fa84c:	mov	w9, #1
0x2519fa850:	add	w10, w20, #1
0x2519fa854:	mov	w8, #0x248a
0x2519fa858:	movk	w8, #0x92c7, lsl #16
0x2519fa85c:	add	w8, w8, w27
0x2519fa860:	sub	w8, w8, #0x26e
0x2519fa864:	mov	w11, #0x13fe
0x2519fa868:	orr	w11, w8, w11
0x2519fa86c:	cmp	w11, w20
0x2519fa870:	cset	w11, lo
0x2519fa874:	sub	w11, w8, w11
0x2519fa878:	ldr	x15, [sp, #0xf0]
0x2519fa87c:	add	w8, w27, w9
0x2519fa880:	sub	w8, w8, #1
0x2519fa884:	str	w10, [x23]
0x2519fa888:	eor	w10, w19, w19, lsr #11
0x2519fa88c:	mov	w12, #0xdde2
0x2519fa890:	movk	w12, #0x6d38, lsl #16
0x2519fa894:	eor	w12, w8, w12
0x2519fa898:	lsl	w12, w10, w12
0x2519fa89c:	mov	w13, #0x5680
0x2519fa8a0:	movk	w13, #0x9d2c, lsl #16
0x2519fa8a4:	and	w12, w12, w13
0x2519fa8a8:	eor	w10, w12, w10
0x2519fa8ac:	mov	w12, #-0x103a0000
0x2519fa8b0:	and	w12, w12, w10, lsl #15
0x2519fa8b4:	eor	w10, w12, w10
0x2519fa8b8:	ldr	x12, [sp, #0xf8]
0x2519fa8bc:	sub	x12, x12, w9, uxtw
0x2519fa8c0:	ldr	x13, [sp, #0xd8]
0x2519fa8c4:	ldr	x13, [x13]
0x2519fa8c8:	ldr	w14, [x13, x15]
0x2519fa8cc:	add	x11, x12, x11
0x2519fa8d0:	str	x11, [sp, #0xf8]
0x2519fa8d4:	eor	w11, w10, w14
0x2519fa8d8:	eor	w10, w11, w10, lsr #18
0x2519fa8dc:	str	w10, [x13, x15]
0x2519fa8e0:	cmp	x15, #0x1fc
0x2519fa8e4:	cset	w10, lo
0x2519fa8e8:	mov	w11, #0x315
0x2519fa8ec:	eor	w9, w9, w11
0x2519fa8f0:	orr	w10, w10, w10, lsl #3
0x2519fa8f4:	orr	w9, w9, w10
0x2519fa8f8:	ldr	x9, [x28, w9, uxtw #3]
0x2519fa8fc:	mov	w16, #0x91cb
0x2519fa900:	movk	w16, #0x73c7, lsl #16
0x2519fa904:	mov	x17, #0x147
0x2519fa908:	braa	x9, x17
0x2519fa90c:	ldrb	w13, [x1, x12]
0x2519fa910:	add	x12, x12, #1
0x2519fa914:	strb	w13, [x3, x9]
0x2519fa918:	add	x9, x9, #1
0x2519fa91c:	cmp	x12, x14
0x2519fa920:	cset	w13, eq
0x2519fa924:	mul	w13, w13, w11
0x2519fa928:	orr	w13, w13, w10
0x2519fa92c:	ldr	x13, [x19, w13, sxtw #3]
0x2519fa930:	mov	x17, #0xc57
0x2519fa934:	braa	x13, x17
0x2519fa938:	add	x10, x23, x9
0x2519fa93c:	ldrb	w10, [x10]
0x2519fa940:	add	x11, x21, x9
0x2519fa944:	strb	w10, [x11]
0x2519fa948:	sub	x10, x9, #0x17
0x2519fa94c:	eor	x11, x22, x19
0x2519fa950:	cmp	x10, x11
0x2519fa954:	cset	w10, ne
0x2519fa958:	eor	w10, w8, w10, lsl #4
0x2519fa95c:	ldr	x10, [x15, w10, sxtw #3]
0x2519fa960:	add	x9, x9, #1
0x2519fa964:	mov	x17, #0x2468
0x2519fa968:	braa	x10, x17
0x2519fa96c:	mov	x6, x10
0x2519fa970:	mov	x5, x13
0x2519fa974:	mov	x4, x12
0x2519fa978:	add	w2, w3, #0x4e
0x2519fa97c:	mov	w8, #0xc9f3
0x2519fa980:	movk	w8, #0x6ce0, lsl #16
0x2519fa984:	eor	w10, w10, w8
0x2519fa988:	add	w12, w26, w2
0x2519fa98c:	sub	w12, w12, #0x37c
0x2519fa990:	eor	w12, w13, w12
0x2519fa994:	mov	w8, #0xb3fb
0x2519fa998:	movk	w8, #0xf07d, lsl #16
0x2519fa99c:	and	w13, w13, w8
0x2519fa9a0:	mov	w8, #0x3208
0x2519fa9a4:	movk	w8, #0x901d, lsl #16
0x2519fa9a8:	eor	w13, w13, w8
0x2519fa9ac:	and	w10, w10, w12
0x2519fa9b0:	mov	w8, #0x6ca9
0x2519fa9b4:	movk	w8, #0xa19, lsl #16
0x2519fa9b8:	eor	w12, w4, w8
0x2519fa9bc:	mov	w8, #0x85f7
0x2519fa9c0:	movk	w8, #0x6362, lsl #16
0x2519fa9c4:	eor	w14, w6, w8
0x2519fa9c8:	and	w12, w14, w12
0x2519fa9cc:	mov	w8, #0x16a1
0x2519fa9d0:	movk	w8, #0x9684, lsl #16
0x2519fa9d4:	and	w14, w6, w8
0x2519fa9d8:	mov	w8, #0x4a1
0x2519fa9dc:	movk	w8, #0x200, lsl #16
0x2519fa9e0:	eor	w14, w14, w8
0x2519fa9e4:	eor	w10, w13, w10
0x2519fa9e8:	eor	w12, w14, w12
0x2519fa9ec:	ldp	x8, x9, [sp, #0x80]
0x2519fa9f0:	ldr	w13, [x9]
0x2519fa9f4:	ldr	w14, [x8]
0x2519fa9f8:	add	w16, w14, w13
0x2519fa9fc:	mov	x8, #0xb4fa
0x2519faa00:	movk	x8, #0x6d3c, lsl #16
0x2519faa04:	movk	x8, #0x2a54, lsl #32
0x2519faa08:	movk	x8, #0x375b, lsl #48
0x2519faa0c:	eor	w16, w16, w8
0x2519faa10:	orr	w12, w12, w10
0x2519faa14:	mov	w0, #0x1f79
0x2519faa18:	movk	w0, #0xd3ef, lsl #16
0x2519faa1c:	mul	w10, w16, w0
0x2519faa20:	ldr	x9, [sp, #0xb0]
0x2519faa24:	add	x16, x9, w10, uxtb
0x2519faa28:	ldrb	w16, [x16]
0x2519faa2c:	mov	w9, #0x7d
0x2519faa30:	eor	w16, w16, w9
0x2519faa34:	ldr	x9, [sp, #0xa8]
0x2519faa38:	ldrb	w16, [x9, w16, uxtw]
0x2519faa3c:	eor	w15, w15, w26
0x2519faa40:	eor	w10, w10, w16
0x2519faa44:	and	w10, w10, #0xff
0x2519faa48:	add	w10, w10, #0x50
0x2519faa4c:	adrp	x9, #0x27612b000
0x2519faa50:	add	x9, x9, #0x8f0
0x2519faa54:	ldr	x16, [x9, w10, uxtw #3]
0x2519faa58:	add	x10, x7, x19
0x2519faa5c:	ldrb	w17, [x16, x10]
0x2519faa60:	sub	w13, w14, w13
0x2519faa64:	eor	w13, w13, w8
0x2519faa68:	lsl	w17, w17, #2
0x2519faa6c:	mov	w28, #0x1f79
0x2519faa70:	movk	w28, #0xd3ef, lsl #16
0x2519faa74:	mul	w13, w13, w0
0x2519faa78:	ldr	x0, [x9, #0x180]
0x2519faa7c:	and	x14, x13, #0xff
0x2519faa80:	add	x0, x0, x14
0x2519faa84:	ldurb	w0, [x0, #-8]
0x2519faa88:	sub	w17, w17, #0xf4
0x2519faa8c:	mov	w8, #0x6a
0x2519faa90:	eor	w0, w0, w8
0x2519faa94:	ldr	x1, [x9, #0x230]
0x2519faa98:	add	x0, x1, x0
0x2519faa9c:	ldurb	w0, [x0, #-8]
0x2519faaa0:	eor	w0, w0, w13
0x2519faaa4:	and	x17, x17, #0x3fc
0x2519faaa8:	and	w0, w0, #0xff
0x2519faaac:	sub	w0, w0, #0x8c
0x2519faab0:	ldr	x0, [x9, w0, sxtw #3]
0x2519faab4:	ldr	w17, [x11, x17]
0x2519faab8:	add	w12, w12, w15
0x2519faabc:	sub	x0, x0, #0xc
0x2519faac0:	ldr	w15, [x0, x10, lsl #2]
0x2519faac4:	add	w12, w12, w15
0x2519faac8:	eor	w15, w17, w23
0x2519faacc:	add	w12, w12, w15
0x2519faad0:	mov	w8, #0x8b3b
0x2519faad4:	movk	w8, #0x1186, lsl #16
0x2519faad8:	eor	w15, w12, w8
0x2519faadc:	mov	w8, #0x11fa
0x2519faae0:	movk	w8, #0x888b, lsl #16
0x2519faae4:	and	w17, w12, w8
0x2519faae8:	mov	w8, #0x89fb
0x2519faaec:	movk	w8, #0x82, lsl #16
0x2519faaf0:	eor	w1, w12, w8
0x2519faaf4:	and	w1, w1, w17, lsl #1
0x2519faaf8:	eor	w17, w1, w17
0x2519faafc:	lsl	w1, w15, #1
0x2519fab00:	mov	w8, #0x3582
0x2519fab04:	movk	w8, #0x321b, lsl #16
0x2519fab08:	eor	w30, w1, w8
0x2519fab0c:	and	w15, w30, w15
0x2519fab10:	mov	w8, #0x9ac0
0x2519fab14:	movk	w8, #0x990d, lsl #16
0x2519fab18:	and	w1, w1, w8
0x2519fab1c:	eor	w15, w15, w1
0x2519fab20:	mov	w1, #0x8a41
0x2519fab24:	movk	w1, #0x8904, lsl #16
0x2519fab28:	eor	w1, w15, w1
0x2519fab2c:	mov	w30, #0x80
0x2519fab30:	movk	w30, #8, lsl #16
0x2519fab34:	eor	w15, w15, w30
0x2519fab38:	and	w15, w15, w17, lsl #2
0x2519fab3c:	eor	w15, w15, w17
0x2519fab40:	lsl	w17, w1, #2
0x2519fab44:	mov	w30, #0x6b04
0x2519fab48:	movk	w30, #0x6436, lsl #16
0x2519fab4c:	eor	w30, w17, w30
0x2519fab50:	and	w1, w30, w1
0x2519fab54:	and	w17, w17, w8
0x2519fab58:	eor	w17, w1, w17
0x2519fab5c:	mov	w1, #0x90c1
0x2519fab60:	movk	w1, #0x9909, lsl #16
0x2519fab64:	eor	w1, w17, w1
0x2519fab68:	mov	w30, #0xa00
0x2519fab6c:	movk	w30, #4, lsl #16
0x2519fab70:	eor	w17, w17, w30
0x2519fab74:	and	w17, w17, w15, lsl #4
0x2519fab78:	eor	w15, w17, w15
0x2519fab7c:	lsl	w17, w1, #4
0x2519fab80:	mov	w30, #0xac10
0x2519fab84:	movk	w30, #0x90d9, lsl #16
0x2519fab88:	eor	w30, w17, w30
0x2519fab8c:	and	w1, w30, w1
0x2519fab90:	and	w17, w17, w8
0x2519fab94:	eor	w17, w1, w17
0x2519fab98:	mov	w1, #0x12c1
0x2519fab9c:	movk	w1, #0x904, lsl #16
0x2519faba0:	eor	w1, w17, w1
0x2519faba4:	mov	w30, #0x8800
0x2519faba8:	movk	w30, #0x9009, lsl #16
0x2519fabac:	eor	w17, w17, w30
0x2519fabb0:	and	w17, w17, w15, lsl #8
0x2519fabb4:	add	w30, w8, #1
0x2519fabb8:	eor	w15, w15, w30
0x2519fabbc:	lsl	w30, w1, #8
0x2519fabc0:	eor	w15, w15, w17
0x2519fabc4:	mov	w8, #0xd9a0000
0x2519fabc8:	eor	w17, w30, w8
0x2519fabcc:	and	w17, w17, w1
0x2519fabd0:	mov	w27, #0x190d0000
0x2519fabd4:	and	w1, w30, w27
0x2519fabd8:	mov	w8, #0x10050000
0x2519fabdc:	eor	w1, w1, w8
0x2519fabe0:	eor	w17, w1, w17
0x2519fabe4:	lsl	w1, w15, #0x10
0x2519fabe8:	ldr	x8, [sp, #0x98]
0x2519fabec:	add	x14, x8, x14
0x2519fabf0:	ldrb	w14, [x14]
0x2519fabf4:	mov	w8, #0x99
0x2519fabf8:	eor	w14, w14, w8
0x2519fabfc:	ldr	x8, [sp, #0xa0]
0x2519fac00:	ldrb	w14, [x8, w14, uxtw]
0x2519fac04:	mov	w8, #0x1ac10000
0x2519fac08:	eor	w30, w1, w8
0x2519fac0c:	eor	w13, w13, w14
0x2519fac10:	and	w13, w13, #0xff
0x2519fac14:	sub	w13, w13, #0x83
0x2519fac18:	ldr	x13, [x9, w13, sxtw #3]
0x2519fac1c:	and	w14, w30, w17
0x2519fac20:	and	w17, w1, w27
0x2519fac24:	mov	w27, #0x6d
0x2519fac28:	sub	x1, x13, #8
0x2519fac2c:	ldrb	w10, [x1, x10]
0x2519fac30:	mov	w8, #0x2d31
0x2519fac34:	movk	w8, #0x4680, lsl #16
0x2519fac38:	add	w13, w10, w8
0x2519fac3c:	eor	w15, w17, w15
0x2519fac40:	eor	w17, w13, #0xfffffff9
0x2519fac44:	add	w17, w17, #0x19
0x2519fac48:	mov	w8, #0xd
0x2519fac4c:	sub	w30, w8, w10
0x2519fac50:	eor	w30, w13, w30
0x2519fac54:	eor	w17, w30, w17
0x2519fac58:	eor	w30, w13, w8
0x2519fac5c:	add	w30, w30, #0xd
0x2519fac60:	eor	w13, w13, #0x55555555
0x2519fac64:	add	w13, w13, #0x15
0x2519fac68:	eor	w13, w30, w13
0x2519fac6c:	eor	w13, w17, w13
0x2519fac70:	eor	w14, w15, w14
0x2519fac74:	eor	w12, w12, w14, lsl #1
0x2519fac78:	mov	w8, #0x2478
0x2519fac7c:	movk	w8, #0x8a92, lsl #16
0x2519fac80:	eor	w12, w12, w8
0x2519fac84:	and	w13, w13, #0x1f
0x2519fac88:	eor	w13, w13, #0x1e
0x2519fac8c:	sub	w10, w27, w10
0x2519fac90:	lsl	w13, w12, w13
0x2519fac94:	mov	w8, #0x42d
0x2519fac98:	movk	w8, #0x4494, lsl #16
0x2519fac9c:	eor	w14, w6, w8
0x2519faca0:	mov	w8, #0xfbd3
0x2519faca4:	movk	w8, #0xbb6b, lsl #16
0x2519faca8:	add	w14, w14, w8
0x2519facac:	mov	w8, #0x9cb0
0x2519facb0:	movk	w8, #0x9a92, lsl #16
0x2519facb4:	eor	w15, w6, w8
0x2519facb8:	mov	w8, #0x6350
0x2519facbc:	movk	w8, #0x656d, lsl #16
0x2519facc0:	add	w15, w15, w8
0x2519facc4:	eor	w14, w14, w15
0x2519facc8:	lsr	w10, w12, w10
0x2519faccc:	mov	w8, #0xe295
0x2519facd0:	movk	w8, #0x429b, lsl #16
0x2519facd4:	eor	w12, w6, w8
0x2519facd8:	mov	w8, #0x1d6b
0x2519facdc:	movk	w8, #0xbd64, lsl #16
0x2519face0:	add	w12, w12, w8
0x2519face4:	eor	w12, w14, w12
0x2519face8:	add	w10, w12, w10
0x2519facec:	mov	w8, #0xdd37
0x2519facf0:	movk	w8, #0xf68c, lsl #16
0x2519facf4:	add	w12, w13, w8
0x2519facf8:	add	w10, w10, w12
0x2519facfc:	mov	w8, #0xd78d
0x2519fad00:	movk	w8, #0xf877, lsl #16
0x2519fad04:	eor	w12, w10, w8
0x2519fad08:	mov	w8, #0x4b5e
0x2519fad0c:	movk	w8, #0x5e67, lsl #16
0x2519fad10:	add	w12, w12, w8
0x2519fad14:	mov	w8, #0x671c
0x2519fad18:	movk	w8, #0x7f86, lsl #16
0x2519fad1c:	eor	w13, w10, w8
0x2519fad20:	mov	w8, #0xfbcd
0x2519fad24:	movk	w8, #0xd996, lsl #16
0x2519fad28:	add	w13, w13, w8
0x2519fad2c:	mov	w8, #0xc45
0x2519fad30:	movk	w8, #0x81e1, lsl #16
0x2519fad34:	eor	w14, w10, w8
0x2519fad38:	mov	w8, #0x9096
0x2519fad3c:	movk	w8, #0x27f1, lsl #16
0x2519fad40:	add	w14, w14, w8
0x2519fad44:	mov	w8, #0xdffb
0x2519fad48:	movk	w8, #0x5fff, lsl #16
0x2519fad4c:	eor	w15, w10, w8
0x2519fad50:	mov	w8, #0x432c
0x2519fad54:	movk	w8, #0xf9ef, lsl #16
0x2519fad58:	add	w15, w15, w8
0x2519fad5c:	eor	w10, w10, w12
0x2519fad60:	eor	w12, w13, w14
0x2519fad64:	mov	w8, #0x1927
0x2519fad68:	movk	w8, #0xc572, lsl #16
0x2519fad6c:	eor	w13, w15, w8
0x2519fad70:	eor	w10, w10, w12
0x2519fad74:	add	x7, x7, #1
0x2519fad78:	add	x30, x24, #0x10
0x2519fad7c:	cmp	x7, x30
0x2519fad80:	cset	w12, eq
0x2519fad84:	mov	w8, #0x52
0x2519fad88:	mul	w12, w12, w8
0x2519fad8c:	eor	w10, w10, w13
0x2519fad90:	eor	w12, w12, w3
0x2519fad94:	ldr	x14, [x20, w12, sxtw #3]
0x2519fad98:	mov	x15, x4
0x2519fad9c:	mov	x12, x5
0x2519fada0:	mov	x13, x6
0x2519fada4:	mov	x17, #0x7f6f
0x2519fada8:	braa	x14, x17
0x2519fadac:	sub	w9, w11, #0x1e2
0x2519fadb0:	sub	w10, w11, #0x207
0x2519fadb4:	mov	w11, #0x340
0x2519fadb8:	orr	w15, w10, w11
0x2519fadbc:	ldr	x9, [x7, w9, sxtw #3]
0x2519fadc0:	str	x9, [sp, #0x38]
0x2519fadc4:	ldrb	w6, [sp, #0x1f2]
0x2519fadc8:	ldrb	w14, [sp, #0x1f3]
0x2519fadcc:	mov	w10, #2
0x2519fadd0:	udiv	w9, w10, w14
0x2519fadd4:	msub	w9, w9, w14, w10
0x2519fadd8:	str	x9, [sp, #0xd0]
0x2519faddc:	ldrb	w10, [x13]
0x2519fade0:	ldurb	w24, [x8, #-0xc]
0x2519fade4:	ldurb	w26, [x8, #-8]
0x2519fade8:	ldurb	w9, [x8, #-4]
0x2519fadec:	ldurb	w16, [x8, #-3]
0x2519fadf0:	ldurb	w27, [x8, #-7]
0x2519fadf4:	mov	w12, #3
0x2519fadf8:	udiv	w11, w12, w14
0x2519fadfc:	str	w14, [sp, #0xd8]
0x2519fae00:	msub	w11, w11, w14, w12
0x2519fae04:	str	x11, [sp, #0xc8]
0x2519fae08:	ldurb	w25, [x8, #-0xb]
0x2519fae0c:	ldurb	w17, [x8, #-0xf]
0x2519fae10:	ldurb	w0, [x8, #-0xe]
0x2519fae14:	ldurb	w22, [x8, #-6]
0x2519fae18:	ldurb	w20, [x8, #-0xa]
0x2519fae1c:	ldurb	w1, [x8, #-2]
0x2519fae20:	ldurb	w3, [x8, #-0xd]
0x2519fae24:	ldurb	w12, [x8, #-9]
0x2519fae28:	ldurb	w21, [x8, #-5]
0x2519fae2c:	eor	x11, x10, x5
0x2519fae30:	eor	x19, x17, x5
0x2519fae34:	eor	w10, w15, w16
0x2519fae38:	and	x10, x10, #0xff
0x2519fae3c:	eor	x2, x10, #0x1c
0x2519fae40:	eor	x17, x0, x5
0x2519fae44:	eor	x10, x1, x5
0x2519fae48:	ldurb	w23, [x8, #-1]
0x2519fae4c:	eor	x4, x3, x5
0x2519fae50:	ldp	x16, x0, [sp, #0x10]
0x2519fae54:	mov	w3, #8
0x2519fae58:	ldp	x1, x30, [x0, #-0x78]
0x2519fae5c:	ldrb	w11, [x1, x11]
0x2519fae60:	ldurb	w1, [x16, #-0xf]
0x2519fae64:	eor	w1, w1, w11
0x2519fae68:	add	w11, w15, #0xc
0x2519fae6c:	eor	w11, w1, w11
0x2519fae70:	strb	w11, [x13]
0x2519fae74:	and	x11, x24, #0xff
0x2519fae78:	eor	x11, x11, x5
0x2519fae7c:	ldp	x24, x14, [x0, #-0x58]
0x2519fae80:	ldrb	w11, [x24, x11]
0x2519fae84:	ldurb	w24, [x16, #-0xb]
0x2519fae88:	eor	w24, w24, w11
0x2519fae8c:	eor	w11, w24, w5
0x2519fae90:	sturb	w11, [x8, #-0xc]
0x2519fae94:	and	x11, x26, #0xff
0x2519fae98:	eor	x11, x11, x5
0x2519fae9c:	ldp	x26, x7, [x0, #-0x38]
0x2519faea0:	ldrb	w11, [x26, x11]
0x2519faea4:	ldurb	w26, [x16, #-7]
0x2519faea8:	eor	w26, w26, w11
0x2519faeac:	eor	w11, w26, w5
0x2519faeb0:	sturb	w11, [x8, #-8]
0x2519faeb4:	and	x9, x9, #0xff
0x2519faeb8:	eor	x9, x9, x5
0x2519faebc:	ldp	x11, x28, [x0, #-0x18]
0x2519faec0:	ldrb	w9, [x11, x9]
0x2519faec4:	ldurb	w11, [x16, #-3]
0x2519faec8:	eor	w9, w11, w9
0x2519faecc:	eor	w11, w9, w5
0x2519faed0:	sturb	w11, [x8, #-4]
0x2519faed4:	and	x11, x27, #0xff
0x2519faed8:	eor	x11, x11, x5
0x2519faedc:	ldrb	w11, [x28, x11]
0x2519faee0:	ldurb	w27, [x16, #-2]
0x2519faee4:	eor	w11, w27, w11
0x2519faee8:	eor	w27, w11, w5
0x2519faeec:	sturb	w27, [x8, #-3]
0x2519faef0:	and	x25, x25, #0xff
0x2519faef4:	eor	x25, x25, x5
0x2519faef8:	ldrb	w7, [x7, x25]
0x2519faefc:	ldurb	w25, [x16, #-6]
0x2519faf00:	eor	w27, w25, w7
0x2519faf04:	eor	w7, w27, w5
0x2519faf08:	sturb	w7, [x8, #-7]
0x2519faf0c:	ldrb	w14, [x14, x19]
0x2519faf10:	ldurb	w7, [x16, #-0xa]
0x2519faf14:	eor	w19, w7, w14
0x2519faf18:	eor	w14, w19, w5
0x2519faf1c:	sturb	w14, [x8, #-0xb]
0x2519faf20:	ldrb	w14, [x30, x2]
0x2519faf24:	ldurb	w2, [x16, #-0xe]
0x2519faf28:	eor	w25, w2, w14
0x2519faf2c:	eor	w14, w25, w5
0x2519faf30:	sturb	w14, [x8, #-0xf]
0x2519faf34:	and	x14, x22, #0xff
0x2519faf38:	eor	x14, x14, x5
0x2519faf3c:	ldp	x7, x2, [x0, #-0x68]
0x2519faf40:	ldrb	w14, [x7, x14]
0x2519faf44:	ldurb	w7, [x16, #-0xd]
0x2519faf48:	eor	w30, w7, w14
0x2519faf4c:	eor	w14, w30, w5
0x2519faf50:	sturb	w14, [x8, #-0xe]
0x2519faf54:	ldp	x14, x7, [x0, #-0x28]
0x2519faf58:	ldrb	w14, [x14, x17]
0x2519faf5c:	ldurb	w17, [x16, #-5]
0x2519faf60:	eor	w17, w17, w14
0x2519faf64:	eor	w14, w17, w5
0x2519faf68:	sturb	w14, [x8, #-6]
0x2519faf6c:	ldp	x14, x28, [x0, #-0x48]
0x2519faf70:	ldrb	w10, [x14, x10]
0x2519faf74:	ldurb	w14, [x16, #-9]
0x2519faf78:	eor	w22, w14, w10
0x2519faf7c:	eor	w10, w22, w5
0x2519faf80:	sturb	w10, [x8, #-0xa]
0x2519faf84:	and	x10, x20, #0xff
0x2519faf88:	eor	x10, x10, x5
0x2519faf8c:	ldp	x14, x20, [x0, #-8]
0x2519faf90:	ldrb	w10, [x14, x10]
0x2519faf94:	ldurb	w14, [x16, #-1]
0x2519faf98:	eor	w10, w14, w10
0x2519faf9c:	eor	w14, w10, w5
0x2519fafa0:	sturb	w14, [x8, #-2]
0x2519fafa4:	and	x12, x12, #0xff
0x2519fafa8:	eor	x12, x12, x5
0x2519fafac:	ldrb	w12, [x2, x12]
0x2519fafb0:	ldurb	w14, [x16, #-0xc]
0x2519fafb4:	eor	w14, w14, w12
0x2519fafb8:	eor	w12, w14, w5
0x2519fafbc:	sturb	w12, [x8, #-0xd]
0x2519fafc0:	and	x12, x21, #0xff
0x2519fafc4:	eor	x12, x12, x5
0x2519fafc8:	ldrb	w12, [x28, x12]
0x2519fafcc:	ldurb	w2, [x16, #-8]
0x2519fafd0:	eor	w12, w2, w12
0x2519fafd4:	eor	w2, w12, w5
0x2519fafd8:	sturb	w2, [x8, #-9]
0x2519fafdc:	and	x2, x23, #0xff
0x2519fafe0:	eor	x2, x2, x5
0x2519fafe4:	ldrb	w2, [x7, x2]
0x2519fafe8:	ldurb	w7, [x16, #-4]
0x2519fafec:	eor	w21, w7, w2
0x2519faff0:	eor	w2, w21, w5
0x2519faff4:	sturb	w2, [x8, #-5]
0x2519faff8:	ldrb	w2, [x20, x4]
0x2519faffc:	ldrb	w4, [x16]
0x2519fb000:	eor	w2, w4, w2
0x2519fb004:	eor	w4, w2, w5
0x2519fb008:	sturb	w4, [x8, #-1]
0x2519fb00c:	udiv	w4, w3, w6
0x2519fb010:	msub	w4, w4, w6, w3
0x2519fb014:	ldr	x7, [sp, #0xc0]
0x2519fb018:	add	x23, x7, x4, lsl #7
0x2519fb01c:	ubfiz	x1, x1, #2, #8
0x2519fb020:	ldp	x4, x7, [x23]
0x2519fb024:	ldr	w1, [x4, x1]
0x2519fb028:	ubfiz	x4, x25, #2, #8
0x2519fb02c:	ldr	w4, [x7, x4]
0x2519fb030:	eor	w1, w4, w1
0x2519fb034:	ubfiz	x4, x30, #2, #8
0x2519fb038:	ldp	x7, x20, [x23, #0x10]
0x2519fb03c:	ldr	w4, [x7, x4]
0x2519fb040:	ubfiz	x14, x14, #2, #8
0x2519fb044:	ldr	w14, [x20, x14]
0x2519fb048:	eor	w14, w4, w14
0x2519fb04c:	eor	w1, w1, w14
0x2519fb050:	lsr	w4, w1, #0x18
0x2519fb054:	eor	w14, w4, w5
0x2519fb058:	sturb	w14, [x8, #-0xd]
0x2519fb05c:	eor	w14, w5, w1, lsr #16
0x2519fb060:	sturb	w14, [x8, #-0xe]
0x2519fb064:	eor	w14, w5, w1, lsr #8
0x2519fb068:	sturb	w14, [x8, #-0xf]
0x2519fb06c:	eor	w14, w1, w5
0x2519fb070:	strb	w14, [x13]
0x2519fb074:	add	x14, x23, #0x20
0x2519fb078:	ldr	w7, [sp, #0xd8]
0x2519fb07c:	cmp	w7, #1
0x2519fb080:	csel	x14, x23, x14, eq
0x2519fb084:	ldr	x14, [x14]
0x2519fb088:	ubfiz	x7, x24, #2, #8
0x2519fb08c:	ldr	w14, [x14, x7]
0x2519fb090:	mov	w7, #8
0x2519fb094:	mov	w20, #0x28
0x2519fb098:	csel	x7, x7, x20, eq
0x2519fb09c:	ldr	x7, [x23, x7]
0x2519fb0a0:	ubfiz	x19, x19, #2, #8
0x2519fb0a4:	ldr	w7, [x7, x19]
0x2519fb0a8:	mov	w19, #0x30
0x2519fb0ac:	mov	w20, #0x10
0x2519fb0b0:	csel	x19, x20, x19, eq
0x2519fb0b4:	ldr	x19, [x23, x19]
0x2519fb0b8:	ubfiz	x20, x22, #2, #8
0x2519fb0bc:	ldr	w19, [x19, x20]
0x2519fb0c0:	mov	w20, #0x38
0x2519fb0c4:	mov	w22, #0x18
0x2519fb0c8:	csel	x20, x22, x20, eq
0x2519fb0cc:	ldr	x20, [x23, x20]
0x2519fb0d0:	eor	w7, w7, w19
0x2519fb0d4:	ubfiz	x12, x12, #2, #8
0x2519fb0d8:	ldr	w12, [x20, x12]
0x2519fb0dc:	eor	w12, w7, w12
0x2519fb0e0:	eor	w14, w12, w14
0x2519fb0e4:	lsr	w12, w14, #0x18
0x2519fb0e8:	mov	w30, #0x1ea
0x2519fb0ec:	and	w7, w30, w14, lsr #23
0x2519fb0f0:	sub	w12, w12, w7
0x2519fb0f4:	add	w12, w12, #0x75
0x2519fb0f8:	sturb	w12, [x8, #-9]
0x2519fb0fc:	mov	w28, #0x15
0x2519fb100:	orn	w7, w28, w14, lsr #15
0x2519fb104:	add	w7, w7, w14, lsr #16
0x2519fb108:	add	w20, w7, #0x76
0x2519fb10c:	sturb	w20, [x8, #-0xa]
0x2519fb110:	lsr	w7, w14, #8
0x2519fb114:	mov	w19, #0xffea
0x2519fb118:	movk	w19, #0x1ff, lsl #16
0x2519fb11c:	and	w19, w19, w14, lsr #7
0x2519fb120:	sub	w7, w7, w19
0x2519fb124:	add	w25, w7, #0x75
0x2519fb128:	sturb	w25, [x8, #-0xb]
0x2519fb12c:	orn	w7, w28, w14, lsl #1
0x2519fb130:	add	w14, w14, w7
0x2519fb134:	add	w24, w14, #0x76
0x2519fb138:	sturb	w24, [x8, #-0xc]
0x2519fb13c:	ldr	x14, [sp, #0xd0]
0x2519fb140:	add	x14, x23, x14, lsl #5
0x2519fb144:	ubfiz	x7, x26, #2, #8
0x2519fb148:	ldp	x19, x22, [x14]
0x2519fb14c:	ldr	w7, [x19, x7]
0x2519fb150:	ubfiz	x19, x27, #2, #8
0x2519fb154:	ldr	w19, [x22, x19]
0x2519fb158:	ubfiz	x17, x17, #2, #8
0x2519fb15c:	ldp	x22, x14, [x14, #0x10]
0x2519fb160:	ldr	w17, [x22, x17]
0x2519fb164:	ubfiz	x21, x21, #2, #8
0x2519fb168:	ldr	w14, [x14, x21]
0x2519fb16c:	eor	w7, w19, w7
0x2519fb170:	eor	w14, w17, w14
0x2519fb174:	eor	w14, w7, w14
0x2519fb178:	lsr	w17, w14, #0x18
0x2519fb17c:	and	w7, w30, w14, lsr #23
0x2519fb180:	sub	w17, w17, w7
0x2519fb184:	add	w21, w17, #0x75
0x2519fb188:	sturb	w21, [x8, #-5]
0x2519fb18c:	lsr	w17, w14, #0x10
0x2519fb190:	mov	w7, #0xffea
0x2519fb194:	movk	w7, #1, lsl #16
0x2519fb198:	and	w7, w7, w14, lsr #15
0x2519fb19c:	sub	w17, w17, w7
0x2519fb1a0:	add	w22, w17, #0x75
0x2519fb1a4:	sturb	w22, [x8, #-6]
0x2519fb1a8:	mov	w19, #0x15
0x2519fb1ac:	orn	w17, w28, w14, lsr #7
0x2519fb1b0:	add	w17, w17, w14, lsr #8
0x2519fb1b4:	add	w27, w17, #0x76
0x2519fb1b8:	sturb	w27, [x8, #-7]
0x2519fb1bc:	mov	w28, #-0x16
0x2519fb1c0:	and	w17, w28, w14, lsl #1
0x2519fb1c4:	sub	w14, w14, w17
0x2519fb1c8:	add	w26, w14, #0x75
0x2519fb1cc:	sturb	w26, [x8, #-8]
0x2519fb1d0:	ldr	x14, [sp, #0xc8]
0x2519fb1d4:	add	x14, x23, x14, lsl #5
0x2519fb1d8:	ubfiz	x9, x9, #2, #8
0x2519fb1dc:	ldp	x17, x7, [x14]
0x2519fb1e0:	ldr	w9, [x17, x9]
0x2519fb1e4:	ubfiz	x11, x11, #2, #8
0x2519fb1e8:	ldr	w11, [x7, x11]
0x2519fb1ec:	eor	w9, w11, w9
0x2519fb1f0:	ubfiz	x10, x10, #2, #8
0x2519fb1f4:	ldp	x11, x14, [x14, #0x10]
0x2519fb1f8:	ldr	w10, [x11, x10]
0x2519fb1fc:	ubfiz	x11, x2, #2, #8
0x2519fb200:	ldr	w11, [x14, x11]
0x2519fb204:	eor	w10, w10, w11
0x2519fb208:	eor	w2, w9, w10
0x2519fb20c:	lsr	w9, w2, #0x18
0x2519fb210:	and	w10, w30, w2, lsr #23
0x2519fb214:	sub	w9, w9, w10
0x2519fb218:	add	w23, w9, #0x75
0x2519fb21c:	sturb	w23, [x8, #-1]
0x2519fb220:	eor	w9, w5, w2, lsr #16
0x2519fb224:	sturb	w9, [x8, #-2]
0x2519fb228:	eor	w9, w5, w2, lsr #8
0x2519fb22c:	sturb	w9, [x8, #-3]
0x2519fb230:	and	w9, w28, w2, lsl #1
0x2519fb234:	sub	w9, w2, w9
0x2519fb238:	add	w9, w9, #0x75
0x2519fb23c:	sturb	w9, [x8, #-4]
0x2519fb240:	cmp	x3, #0
0x2519fb244:	cset	w10, eq
0x2519fb248:	mov	w11, #0x774
0x2519fb24c:	mul	w10, w10, w11
0x2519fb250:	eor	w10, w10, w15
0x2519fb254:	ldr	x7, [sp, #0xe0]
0x2519fb258:	ldr	x10, [x7, w10, sxtw #3]
0x2519fb25c:	mov	x17, #0xdfe5
0x2519fb260:	braa	x10, x17
0x2519fb264:	mov	x13, x15
0x2519fb268:	add	x15, x15, #1
0x2519fb26c:	add	x13, x8, x13
0x2519fb270:	strb	w11, [x13]
0x2519fb274:	cmp	x15, x12
0x2519fb278:	cset	w13, eq
0x2519fb27c:	mul	w13, w13, w14
0x2519fb280:	eor	w13, w13, w10
0x2519fb284:	ldr	x13, [x26, w13, sxtw #3]
0x2519fb288:	mov	x17, #0x1ef9
0x2519fb28c:	braa	x13, x17
0x2519fb290:	mov	w8, #0xd098
0x2519fb294:	movk	w8, #0x26bd, lsl #16
0x2519fb298:	add	w8, w11, w8
0x2519fb29c:	mov	w9, #0x2e3e
0x2519fb2a0:	movk	w9, #0xd942, lsl #16
0x2519fb2a4:	and	w9, w8, w9
0x2519fb2a8:	eor	w8, w9, #0x3e
0x2519fb2ac:	lsr	w8, w10, w8
0x2519fb2b0:	add	x12, x3, #0x48
0x2519fb2b4:	ldr	w12, [x12, w8, uxtw #2]
0x2519fb2b8:	mov	w8, #0xdff7
0x2519fb2bc:	movk	w8, #0x153f, lsl #16
0x2519fb2c0:	eor	w8, w10, w8
0x2519fb2c4:	mov	w13, #0xbfe8
0x2519fb2c8:	movk	w13, #0x2a7f, lsl #16
0x2519fb2cc:	and	w13, w13, w10, lsl #1
0x2519fb2d0:	mov	w14, #0x7d
0x2519fb2d4:	eor	w14, w12, w14
0x2519fb2d8:	add	w8, w8, w15
0x2519fb2dc:	add	w13, w13, w8
0x2519fb2e0:	strb	w14, [x16, w13, uxtw]
0x2519fb2e4:	mov	w8, #0x7a
0x2519fb2e8:	eor	w8, w8, w12, lsr #8
0x2519fb2ec:	mov	w17, #0xea
0x2519fb2f0:	and	w14, w17, w8, lsl #1
0x2519fb2f4:	sub	w8, w8, w14
0x2519fb2f8:	add	w8, w8, #0x75
0x2519fb2fc:	add	w14, w13, #1
0x2519fb300:	strb	w8, [x16, w14, uxtw]
0x2519fb304:	mov	w8, #-0x63
0x2519fb308:	eor	w8, w8, w12, lsr #16
0x2519fb30c:	and	w14, w17, w8, lsl #1
0x2519fb310:	sub	w8, w8, w14
0x2519fb314:	add	w8, w8, #0x75
0x2519fb318:	add	w14, w13, #2
0x2519fb31c:	strb	w8, [x16, w14, uxtw]
0x2519fb320:	add	x8, sp, #0x98
0x2519fb324:	mov	w14, #-0x64
0x2519fb328:	eor	w12, w14, w12, lsr #24
0x2519fb32c:	and	w14, w17, w12, lsl #1
0x2519fb330:	sub	w12, w12, w14
0x2519fb334:	mov	w14, #0x86
0x2519fb338:	add	w12, w12, #0x75
0x2519fb33c:	add	w13, w13, #3
0x2519fb340:	strb	w12, [x16, w13, uxtw]
0x2519fb344:	add	w10, w10, #4
0x2519fb348:	ldr	w12, [x3, #0x5c]
0x2519fb34c:	cmp	w10, w12
0x2519fb350:	cset	w12, hs
0x2519fb354:	lsl	w13, w12, #8
0x2519fb358:	sub	w12, w13, w12, lsl #3
0x2519fb35c:	eor	w12, w12, w11
0x2519fb360:	ldr	x13, [x19, w12, sxtw #3]
0x2519fb364:	mov	w12, #0x5c
0x2519fb368:	mov	x17, #0x6ccd
0x2519fb36c:	braa	x13, x17
0x2519fb370:	add	x8, x8, #1
0x2519fb374:	sub	x9, x9, #1
0x2519fb378:	eor	w12, w8, w10
0x2519fb37c:	add	w13, w8, #0x11
0x2519fb380:	mul	w12, w12, w13
0x2519fb384:	add	x13, x19, x9
0x2519fb388:	strb	w12, [x13]
0x2519fb38c:	cmp	x9, x11
0x2519fb390:	cset	w12, eq
0x2519fb394:	orr	w12, w25, w12, lsl #3
0x2519fb398:	ldr	x12, [x24, w12, sxtw #3]
0x2519fb39c:	mov	x17, #0xa0d1
0x2519fb3a0:	braa	x12, x17

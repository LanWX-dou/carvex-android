; AirPlaySender 0x2519f2904-0x2519f4564; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519f2904:	pacibsp	
0x2519f2908:	sub	sp, sp, #0xa0
0x2519f290c:	stp	x28, x27, [sp, #0x40]
0x2519f2910:	stp	x26, x25, [sp, #0x50]
0x2519f2914:	stp	x24, x23, [sp, #0x60]
0x2519f2918:	stp	x22, x21, [sp, #0x70]
0x2519f291c:	stp	x20, x19, [sp, #0x80]
0x2519f2920:	stp	x29, x30, [sp, #0x90]
0x2519f2924:	add	x29, sp, #0x90
0x2519f2928:	adrp	x8, #0x2681b4000
0x2519f292c:	ldr	x8, [x8, #0xee0]
0x2519f2930:	ldr	x8, [x8]
0x2519f2934:	str	x8, [sp, #0x38]
0x2519f2938:	mov	x10, #0xb4fa
0x2519f293c:	movk	x10, #0x6d3c, lsl #16
0x2519f2940:	movk	x10, #0x2a54, lsl #32
0x2519f2944:	movk	x10, #0x375b, lsl #48
0x2519f2948:	mov	w9, #0x1f79
0x2519f294c:	movk	w9, #0xd3ef, lsl #16
0x2519f2950:	adrp	x8, #0x26e7e6000
0x2519f2954:	ldr	w11, [x8, #0x5e0]
0x2519f2958:	adrp	x13, #0x26e7db000
0x2519f295c:	ldr	w12, [x13, #0x410]
0x2519f2960:	eor	w11, w11, w10
0x2519f2964:	eor	w11, w11, w12
0x2519f2968:	mul	w11, w11, w9
0x2519f296c:	adrp	x14, #0x251c70000
0x2519f2970:	add	x14, x14, #0xe70
0x2519f2974:	add	x14, x14, w11, uxtb
0x2519f2978:	ldrb	w14, [x14]
0x2519f297c:	mov	w15, #0x3b
0x2519f2980:	eor	w14, w14, w15
0x2519f2984:	adrp	x16, #0x251c6d000
0x2519f2988:	add	x16, x16, #0x290
0x2519f298c:	ldrb	w14, [x16, w14, uxtw]
0x2519f2990:	eor	w11, w11, w14
0x2519f2994:	and	w11, w11, #0xff
0x2519f2998:	add	w11, w11, #4
0x2519f299c:	adrp	x14, #0x27612b000
0x2519f29a0:	add	x14, x14, #0x8f0
0x2519f29a4:	ldr	x11, [x14, w11, uxtw #3]
0x2519f29a8:	ldr	x16, [x11]
0x2519f29ac:	eor	w12, w10, w12
0x2519f29b0:	eor	w12, w16, w12
0x2519f29b4:	mul	w12, w12, w9
0x2519f29b8:	ldr	x17, [x14, #0x5c0]
0x2519f29bc:	add	x17, x17, w12, uxtb
0x2519f29c0:	ldurb	w17, [x17, #-0xc]
0x2519f29c4:	eor	w17, w17, #0xfe
0x2519f29c8:	ldr	x3, [x14, #0x408]
0x2519f29cc:	add	x17, x3, x17
0x2519f29d0:	ldurb	w17, [x17, #-4]
0x2519f29d4:	eor	w12, w17, w12
0x2519f29d8:	and	w12, w12, #0xff
0x2519f29dc:	sub	w12, w12, #0x26
0x2519f29e0:	ldr	x12, [x14, w12, sxtw #3]
0x2519f29e4:	ldr	x17, [x12]
0x2519f29e8:	add	x16, x17, x16
0x2519f29ec:	add	x17, sp, #0x20
0x2519f29f0:	eor	x16, x16, x17
0x2519f29f4:	mul	x17, x10, x9
0x2519f29f8:	madd	x17, x16, x9, x17
0x2519f29fc:	eor	x16, x16, x10
0x2519f2a00:	mul	x16, x16, x9
0x2519f2a04:	str	x17, [x11]
0x2519f2a08:	str	x16, [x12]
0x2519f2a0c:	cmp	x2, #0
0x2519f2a10:	cset	w16, ne
0x2519f2a14:	mul	w15, w16, w15
0x2519f2a18:	mov	w16, #0x29e
0x2519f2a1c:	eor	w15, w15, w16
0x2519f2a20:	ldr	w8, [x8, #0x5e0]
0x2519f2a24:	ldr	w13, [x13, #0x410]
0x2519f2a28:	eor	w8, w8, w10
0x2519f2a2c:	eor	w8, w8, w13
0x2519f2a30:	adrp	x13, #0x251c70000
0x2519f2a34:	add	x13, x13, #0xd70
0x2519f2a38:	mul	w8, w8, w9
0x2519f2a3c:	add	x13, x13, w8, uxtb
0x2519f2a40:	ldrb	w13, [x13]
0x2519f2a44:	mov	w16, #0x9f
0x2519f2a48:	adrp	x17, #0x251c6d000
0x2519f2a4c:	add	x17, x17, #0x190
0x2519f2a50:	eor	w13, w13, w16
0x2519f2a54:	ldrb	w13, [x17, w13, uxtw]
0x2519f2a58:	eor	w8, w8, w13
0x2519f2a5c:	and	w8, w8, #0xff
0x2519f2a60:	sub	w8, w8, #0x8f
0x2519f2a64:	ldr	x8, [x14, w8, sxtw #3]
0x2519f2a68:	sub	x19, x8, #0xc
0x2519f2a6c:	ldr	x13, [x19, w15, uxtw #3]
0x2519f2a70:	mov	w8, #-0xa427
0x2519f2a74:	mov	x17, #0x54bc
0x2519f2a78:	braa	x13, x17
0x2519f2a7c:	sub	w9, w20, #0x3a
0x2519f2a80:	orr	w9, w9, #0x38
0x2519f2a84:	mov	w10, #0x4296
0x2519f2a88:	movk	w10, #0xcfda, lsl #16
0x2519f2a8c:	add	w10, w20, w10
0x2519f2a90:	mov	w11, #0xbffb
0x2519f2a94:	movk	w11, #0x3025, lsl #16
0x2519f2a98:	and	w10, w10, w11
0x2519f2a9c:	add	w11, w16, #0xce
0x2519f2aa0:	eor	w11, w9, w11
0x2519f2aa4:	cmp	w8, w11
0x2519f2aa8:	cset	w11, eq
0x2519f2aac:	mov	w12, #0x687
0x2519f2ab0:	eor	w12, w10, w12
0x2519f2ab4:	mul	w11, w11, w12
0x2519f2ab8:	eor	w11, w11, w20
0x2519f2abc:	ldr	x12, [x7, w11, sxtw #3]
0x2519f2ac0:	mov	w11, #0x80
0x2519f2ac4:	mov	x20, x8
0x2519f2ac8:	ldr	x24, [sp, #0xb0]
0x2519f2acc:	ldr	x19, [sp, #0x80]
0x2519f2ad0:	ldr	x21, [sp, #0x58]
0x2519f2ad4:	ldr	w22, [sp, #0x54]
0x2519f2ad8:	mov	x17, #0x5fcc
0x2519f2adc:	braa	x12, x17
0x2519f2ae0:	str	xzr, [sp, #0xd8]
0x2519f2ae4:	ldr	w8, [x25]
0x2519f2ae8:	ldr	w9, [x4]
0x2519f2aec:	add	w8, w9, w8
0x2519f2af0:	eor	w8, w8, w16
0x2519f2af4:	mul	w8, w8, w15
0x2519f2af8:	add	x9, x3, w8, uxtb
0x2519f2afc:	ldrb	w9, [x9]
0x2519f2b00:	mov	w10, #0xb9
0x2519f2b04:	eor	w9, w9, w10
0x2519f2b08:	ldrb	w9, [x2, w9, uxtw]
0x2519f2b0c:	eor	w8, w8, w9
0x2519f2b10:	and	w8, w8, #0xff
0x2519f2b14:	add	w8, w8, #0x3d8
0x2519f2b18:	ldr	x8, [x26, w8, uxtw #3]
0x2519f2b1c:	mov	x17, #0x6b0e
0x2519f2b20:	blraa	x8, x17
0x2519f2b24:	ldp	x4, x3, [sp, #0x88]
0x2519f2b28:	mov	x2, #0xb4fa
0x2519f2b2c:	movk	x2, #0x6d3c, lsl #16
0x2519f2b30:	movk	x2, #0x2a54, lsl #32
0x2519f2b34:	movk	x2, #0x375b, lsl #48
0x2519f2b38:	mov	w0, #0x1f79
0x2519f2b3c:	movk	w0, #0xd3ef, lsl #16
0x2519f2b40:	ldp	x5, x1, [sp, #0x68]
0x2519f2b44:	ldr	x6, [sp, #0x60]
0x2519f2b48:	ldr	x14, [sp, #0x80]
0x2519f2b4c:	mov	w7, #0xaecf
0x2519f2b50:	movk	w7, #0x2636, lsl #16
0x2519f2b54:	ldrb	w8, [x14, #4]
0x2519f2b58:	ldrb	w9, [x14, #5]
0x2519f2b5c:	ldrb	w10, [x14, #6]
0x2519f2b60:	add	w10, w10, #1
0x2519f2b64:	eor	w11, w8, #0xfffffffb
0x2519f2b68:	lsl	w8, w8, #1
0x2519f2b6c:	and	w8, w8, #0xfffffff7
0x2519f2b70:	mov	w12, #0xb8
0x2519f2b74:	and	w12, w12, w9, lsl #1
0x2519f2b78:	eor	w13, w10, #0xfc
0x2519f2b7c:	lsl	w10, w10, #1
0x2519f2b80:	and	w10, w10, #0xf8
0x2519f2b84:	add	w10, w10, w13
0x2519f2b88:	eor	w10, w10, #0x80
0x2519f2b8c:	mov	w13, #0x38df
0x2519f2b90:	movk	w13, #0x5618, lsl #16
0x2519f2b94:	eor	w13, w21, w13
0x2519f2b98:	mov	w14, #0xd3d9
0x2519f2b9c:	movk	w14, #0xbdb2, lsl #16
0x2519f2ba0:	add	w13, w13, w14
0x2519f2ba4:	mov	w14, #0xc160
0x2519f2ba8:	movk	w14, #0x69d6, lsl #16
0x2519f2bac:	eor	w14, w21, w14
0x2519f2bb0:	mov	w15, #0x2a68
0x2519f2bb4:	movk	w15, #0x827c, lsl #16
0x2519f2bb8:	add	w14, w14, w15
0x2519f2bbc:	mov	w15, #0x238
0x2519f2bc0:	movk	w15, #0x5474, lsl #16
0x2519f2bc4:	eor	w15, w21, w15
0x2519f2bc8:	mov	w16, #0xe940
0x2519f2bcc:	movk	w16, #0xbfde, lsl #16
0x2519f2bd0:	add	w15, w15, w16
0x2519f2bd4:	mov	w16, #0xef7f
0x2519f2bd8:	movk	w16, #0x7fef, lsl #16
0x2519f2bdc:	eor	w16, w21, w16
0x2519f2be0:	mov	w17, #0x479
0x2519f2be4:	movk	w17, #0x9445, lsl #16
0x2519f2be8:	add	w16, w16, w17
0x2519f2bec:	eor	w13, w21, w13
0x2519f2bf0:	eor	w14, w14, w15
0x2519f2bf4:	eor	w13, w13, w14
0x2519f2bf8:	mov	w14, #0x6ff
0x2519f2bfc:	movk	w14, #0x10a4, lsl #16
0x2519f2c00:	eor	w14, w16, w14
0x2519f2c04:	eor	w13, w13, w14
0x2519f2c08:	mov	x14, #0x2749
0x2519f2c0c:	movk	x14, #0x4ef, lsl #16
0x2519f2c10:	movk	x14, #0x9332, lsl #32
0x2519f2c14:	movk	x14, #0x235d, lsl #48
0x2519f2c18:	sub	x15, x29, #0x88
0x2519f2c1c:	and	w16, w15, w14
0x2519f2c20:	sub	w15, w15, w16, lsl #1
0x2519f2c24:	add	w14, w15, w14
0x2519f2c28:	mov	w15, #0x8944
0x2519f2c2c:	movk	w15, #0x9111, lsl #16
0x2519f2c30:	eor	w14, w14, w15
0x2519f2c34:	mul	w14, w14, w7
0x2519f2c38:	add	w8, w11, w8
0x2519f2c3c:	add	w8, w14, w8
0x2519f2c40:	add	w8, w8, #0x57
0x2519f2c44:	sturb	w8, [x29, #-0x7b]
0x2519f2c48:	sub	w8, w22, w14
0x2519f2c4c:	add	w8, w8, #0xc5
0x2519f2c50:	sub	w10, w10, w14
0x2519f2c54:	sturb	w10, [x29, #-0x88]
0x2519f2c58:	sub	w9, w9, w14
0x2519f2c5c:	sub	w9, w9, w12
0x2519f2c60:	sub	w9, w9, #0x24
0x2519f2c64:	sturb	w9, [x29, #-0x7c]
0x2519f2c68:	sub	w9, w13, w14
0x2519f2c6c:	stp	w9, w8, [x29, #-0x84]
0x2519f2c70:	stp	x1, x4, [x29, #-0x78]
0x2519f2c74:	ldr	w8, [x25]
0x2519f2c78:	ldr	w9, [x3]
0x2519f2c7c:	sub	w8, w9, w8
0x2519f2c80:	eor	w8, w8, w2
0x2519f2c84:	mul	w8, w8, w0
0x2519f2c88:	add	x9, x6, w8, uxtb
0x2519f2c8c:	ldrb	w9, [x9]
0x2519f2c90:	mov	w10, #0x1a
0x2519f2c94:	eor	w9, w9, w10
0x2519f2c98:	ldrb	w9, [x5, w9, uxtw]
0x2519f2c9c:	eor	w8, w8, w9
0x2519f2ca0:	and	w8, w8, #0xff
0x2519f2ca4:	add	w8, w8, #0x395
0x2519f2ca8:	ldr	x8, [x26, w8, uxtw #3]
0x2519f2cac:	sub	x0, x29, #0x88
0x2519f2cb0:	mov	x17, #0x6e8
0x2519f2cb4:	blraa	x8, x17
0x2519f2cb8:	mov	w8, #0xff
0x2519f2cbc:	ldr	x9, [sp, #0xb8]
0x2519f2cc0:	strb	w8, [x9]
0x2519f2cc4:	str	w21, [x19, #8]
0x2519f2cc8:	ldur	x8, [x29, #-0x60]
0x2519f2ccc:	adrp	x9, #0x2681b4000
0x2519f2cd0:	ldr	x9, [x9, #0xee0]
0x2519f2cd4:	ldr	x9, [x9]
0x2519f2cd8:	cmp	x9, x8
0x2519f2cdc:	b.ne	#0x2519f2d00
0x2519f2ce0:	add	sp, sp, #0xd30
0x2519f2ce4:	ldp	x29, x30, [sp, #0x50]
0x2519f2ce8:	ldp	x20, x19, [sp, #0x40]
0x2519f2cec:	ldp	x22, x21, [sp, #0x30]
0x2519f2cf0:	ldp	x24, x23, [sp, #0x20]
0x2519f2cf4:	ldp	x26, x25, [sp, #0x10]
0x2519f2cf8:	ldp	x28, x27, [sp], #0x60
0x2519f2cfc:	retab	
0x2519f2d00:	bl	#0x2580f4380
0x2519f2d04:	mov	x14, x0
0x2519f2d08:	mov	x16, x10
0x2519f2d0c:	mov	w9, #0xd50f
0x2519f2d10:	movk	w9, #0x7a3e, lsl #16
0x2519f2d14:	add	w9, w1, w9
0x2519f2d18:	mov	w10, #0x2e74
0x2519f2d1c:	movk	w10, #0xfff7, lsl #16
0x2519f2d20:	and	w9, w9, w10
0x2519f2d24:	mov	w10, #0x90d6
0x2519f2d28:	movk	w10, #0xb189, lsl #16
0x2519f2d2c:	eor	w10, w0, w10
0x2519f2d30:	eor	w17, w16, w21
0x2519f2d34:	and	w10, w10, w17
0x2519f2d38:	mov	w17, #0x1521
0x2519f2d3c:	movk	w17, #0xd2eb, lsl #16
0x2519f2d40:	and	w17, w16, w17
0x2519f2d44:	mov	w0, #0xefff
0x2519f2d48:	movk	w0, #0x6f76, lsl #16
0x2519f2d4c:	eor	w17, w17, w0
0x2519f2d50:	eor	w10, w17, w10
0x2519f2d54:	mov	w17, #0xf274
0x2519f2d58:	movk	w17, #0x430c, lsl #16
0x2519f2d5c:	eor	w9, w9, w17
0x2519f2d60:	and	w9, w9, w10, lsl #1
0x2519f2d64:	add	w10, w10, w21
0x2519f2d68:	sub	w9, w10, w9
0x2519f2d6c:	mov	w10, #0xc129
0x2519f2d70:	movk	w10, #0x2d69, lsl #16
0x2519f2d74:	eor	w10, w3, w10
0x2519f2d78:	mov	w17, #0x3ed7
0x2519f2d7c:	movk	w17, #0xd296, lsl #16
0x2519f2d80:	add	w10, w10, w17
0x2519f2d84:	mov	w17, #0xc15c
0x2519f2d88:	movk	w17, #0x4004, lsl #16
0x2519f2d8c:	eor	w17, w3, w17
0x2519f2d90:	mov	w0, #0x3ea4
0x2519f2d94:	movk	w0, #0xbffb, lsl #16
0x2519f2d98:	add	w17, w17, w0
0x2519f2d9c:	eor	w10, w10, w17
0x2519f2da0:	mov	w17, #0x7a7d
0x2519f2da4:	movk	w17, #0xf1f0, lsl #16
0x2519f2da8:	eor	w17, w3, w17
0x2519f2dac:	mov	w0, #0x8583
0x2519f2db0:	movk	w0, #0xe0f, lsl #16
0x2519f2db4:	add	w17, w17, w0
0x2519f2db8:	eor	w17, w10, w17
0x2519f2dbc:	add	x0, x4, x20
0x2519f2dc0:	ldrb	w10, [x12, x0]
0x2519f2dc4:	lsl	w10, w10, #2
0x2519f2dc8:	sub	w10, w10, #0xf4
0x2519f2dcc:	and	x10, x10, #0x3fc
0x2519f2dd0:	ldr	w3, [x11, x10]
0x2519f2dd4:	mov	w10, #0xc892
0x2519f2dd8:	movk	w10, #0x91d5, lsl #16
0x2519f2ddc:	eor	w10, w3, w10
0x2519f2de0:	mov	w5, #0x376e
0x2519f2de4:	movk	w5, #0x6e2a, lsl #16
0x2519f2de8:	add	w10, w10, w5
0x2519f2dec:	mov	w5, #0x51b9
0x2519f2df0:	movk	w5, #0xd1b7, lsl #16
0x2519f2df4:	eor	w5, w3, w5
0x2519f2df8:	mov	w6, #0xae47
0x2519f2dfc:	movk	w6, #0x2e48, lsl #16
0x2519f2e00:	add	w5, w5, w6
0x2519f2e04:	eor	w5, w10, w5
0x2519f2e08:	mov	x10, x2
0x2519f2e0c:	eor	w9, w9, w2
0x2519f2e10:	mov	w2, #0x401b
0x2519f2e14:	movk	w2, #0x7620, lsl #16
0x2519f2e18:	eor	w2, w3, w2
0x2519f2e1c:	mov	w3, #0xbfe5
0x2519f2e20:	movk	w3, #0x89df, lsl #16
0x2519f2e24:	add	w2, w2, w3
0x2519f2e28:	eor	w2, w5, w2
0x2519f2e2c:	ldr	w3, [x13, x0, lsl #2]
0x2519f2e30:	add	w17, w17, w3
0x2519f2e34:	add	w9, w17, w9
0x2519f2e38:	mov	w17, #0x4e86
0x2519f2e3c:	movk	w17, #0xf6a5, lsl #16
0x2519f2e40:	add	w9, w9, w17
0x2519f2e44:	add	w9, w9, w2
0x2519f2e48:	ldrb	w17, [x15, x0]
0x2519f2e4c:	mov	w0, #0xc01a
0x2519f2e50:	movk	w0, #0x2dd7, lsl #16
0x2519f2e54:	add	w0, w17, w0
0x2519f2e58:	mov	w2, #0xe607
0x2519f2e5c:	movk	w2, #0xc615, lsl #16
0x2519f2e60:	eor	w2, w0, w2
0x2519f2e64:	mov	w3, #0xd9a0
0x2519f2e68:	movk	w3, #0x143d, lsl #16
0x2519f2e6c:	add	w2, w2, w3
0x2519f2e70:	mov	w3, #0xf967
0x2519f2e74:	movk	w3, #0x2eec, lsl #16
0x2519f2e78:	eor	w3, w0, w3
0x2519f2e7c:	mov	w5, #0xc700
0x2519f2e80:	movk	w5, #0xfcc4, lsl #16
0x2519f2e84:	add	w3, w3, w5
0x2519f2e88:	eor	w2, w2, w3
0x2519f2e8c:	mov	w3, #0x20e8
0x2519f2e90:	movk	w3, #0xbad1, lsl #16
0x2519f2e94:	eor	w3, w0, w3
0x2519f2e98:	mov	w5, #0x1f71
0x2519f2e9c:	movk	w5, #0x68f9, lsl #16
0x2519f2ea0:	add	w3, w3, w5
0x2519f2ea4:	eor	w3, w0, w3
0x2519f2ea8:	eor	w2, w3, w2
0x2519f2eac:	mov	w3, #0x3805
0x2519f2eb0:	movk	w3, #0x6b52, lsl #16
0x2519f2eb4:	eor	w3, w9, w3
0x2519f2eb8:	mov	w5, #0x2eaf
0x2519f2ebc:	movk	w5, #0xf94, lsl #16
0x2519f2ec0:	add	w3, w3, w5
0x2519f2ec4:	mov	w5, #0xffef
0x2519f2ec8:	movk	w5, #0x7fff, lsl #16
0x2519f2ecc:	eor	w0, w0, w5
0x2519f2ed0:	mov	w5, #0xc078
0x2519f2ed4:	movk	w5, #0xadd7, lsl #16
0x2519f2ed8:	add	w0, w0, w5
0x2519f2edc:	mov	w5, #0x9e15
0x2519f2ee0:	movk	w5, #0x1b8f, lsl #16
0x2519f2ee4:	eor	w0, w0, w5
0x2519f2ee8:	eor	w0, w2, w0
0x2519f2eec:	mov	w2, #0x7e37
0x2519f2ef0:	movk	w2, #0xe205, lsl #16
0x2519f2ef4:	eor	w2, w9, w2
0x2519f2ef8:	mov	w5, #0x689d
0x2519f2efc:	movk	w5, #0x86c3, lsl #16
0x2519f2f00:	add	w2, w2, w5
0x2519f2f04:	eor	w2, w3, w2
0x2519f2f08:	mov	w3, #0x50b9
0x2519f2f0c:	movk	w3, #0xed93, lsl #16
0x2519f2f10:	eor	w3, w9, w3
0x2519f2f14:	mov	w5, #0x4613
0x2519f2f18:	movk	w5, #0x8955, lsl #16
0x2519f2f1c:	add	w3, w3, w5
0x2519f2f20:	eor	w3, w9, w3
0x2519f2f24:	mov	w5, #0xffdf
0x2519f2f28:	movk	w5, #0xfffd, lsl #16
0x2519f2f2c:	eor	w9, w9, w5
0x2519f2f30:	mov	w5, #0xe975
0x2519f2f34:	movk	w5, #0x9b3b, lsl #16
0x2519f2f38:	add	w9, w9, w5
0x2519f2f3c:	eor	w2, w3, w2
0x2519f2f40:	mov	w3, #0xe954
0x2519f2f44:	movk	w3, #0x9b39, lsl #16
0x2519f2f48:	eor	w9, w9, w3
0x2519f2f4c:	eor	w9, w2, w9
0x2519f2f50:	mov	w2, #0x16
0x2519f2f54:	and	w2, w0, w2
0x2519f2f58:	mov	w3, #0x12
0x2519f2f5c:	eor	w2, w2, w3
0x2519f2f60:	mov	w3, #9
0x2519f2f64:	and	w0, w0, w3
0x2519f2f68:	lsl	w2, w9, w2
0x2519f2f6c:	lsl	w0, w2, w0
0x2519f2f70:	sub	w17, w22, w17
0x2519f2f74:	lsr	w9, w9, w17
0x2519f2f78:	mov	w17, #0x560b
0x2519f2f7c:	movk	w17, #0x785e, lsl #16
0x2519f2f80:	eor	w17, w14, w17
0x2519f2f84:	mov	w2, #0xa9f5
0x2519f2f88:	movk	w2, #0x87a1, lsl #16
0x2519f2f8c:	add	w17, w17, w2
0x2519f2f90:	mov	w2, #0xcf9e
0x2519f2f94:	movk	w2, #0x6079, lsl #16
0x2519f2f98:	eor	w2, w14, w2
0x2519f2f9c:	mov	w3, #0x3062
0x2519f2fa0:	movk	w3, #0x9f86, lsl #16
0x2519f2fa4:	add	w2, w2, w3
0x2519f2fa8:	eor	w17, w17, w2
0x2519f2fac:	mov	w2, #0xe39d
0x2519f2fb0:	movk	w2, #0x84ba, lsl #16
0x2519f2fb4:	eor	w2, w14, w2
0x2519f2fb8:	mov	w3, #0x1c63
0x2519f2fbc:	movk	w3, #0x7b45, lsl #16
0x2519f2fc0:	add	w2, w2, w3
0x2519f2fc4:	eor	w17, w17, w2
0x2519f2fc8:	add	w9, w17, w9
0x2519f2fcc:	add	w9, w9, w0
0x2519f2fd0:	mov	w17, #0x898f
0x2519f2fd4:	movk	w17, #0x65, lsl #16
0x2519f2fd8:	add	w9, w9, w17
0x2519f2fdc:	mov	w17, #0xe739
0x2519f2fe0:	movk	w17, #0xc202, lsl #16
0x2519f2fe4:	eor	w17, w9, w17
0x2519f2fe8:	mov	w0, #0xf079
0x2519f2fec:	movk	w0, #0x9c37, lsl #16
0x2519f2ff0:	and	w0, w9, w0
0x2519f2ff4:	mov	w2, #0xe779
0x2519f2ff8:	movk	w2, #0xda27, lsl #16
0x2519f2ffc:	eor	w2, w9, w2
0x2519f3000:	and	w2, w2, w0, lsl #1
0x2519f3004:	eor	w0, w2, w0
0x2519f3008:	lsl	w2, w17, #1
0x2519f300c:	mov	w3, #0x2e80
0x2519f3010:	movk	w3, #0xbc6a, lsl #16
0x2519f3014:	eor	w3, w2, w3
0x2519f3018:	and	w17, w3, w17
0x2519f301c:	and	w2, w2, w28
0x2519f3020:	eor	w17, w17, w2
0x2519f3024:	mov	w2, #0x1140
0x2519f3028:	movk	w2, #0x4215, lsl #16
0x2519f302c:	eor	w2, w17, w2
0x2519f3030:	mov	w3, #0x200
0x2519f3034:	movk	w3, #0x1020, lsl #16
0x2519f3038:	eor	w17, w17, w3
0x2519f303c:	and	w17, w17, w0, lsl #2
0x2519f3040:	eor	w17, w17, w0
0x2519f3044:	lsl	w0, w2, #2
0x2519f3048:	mov	w3, #0x5d00
0x2519f304c:	movk	w3, #0x78d4, lsl #16
0x2519f3050:	eor	w3, w0, w3
0x2519f3054:	and	w2, w3, w2
0x2519f3058:	and	w0, w0, w28
0x2519f305c:	eor	w0, w2, w0
0x2519f3060:	mov	w2, #0x240
0x2519f3064:	movk	w2, #0x621, lsl #16
0x2519f3068:	eor	w2, w0, w2
0x2519f306c:	mov	w3, #0x1500
0x2519f3070:	movk	w3, #0x5814, lsl #16
0x2519f3074:	eor	w0, w0, w3
0x2519f3078:	and	w0, w0, w17, lsl #4
0x2519f307c:	eor	w17, w17, w28
0x2519f3080:	eor	w17, w17, w0
0x2519f3084:	lsl	w0, w2, #4
0x2519f3088:	mov	w3, #0x7400
0x2519f308c:	movk	w3, #0xe351, lsl #16
0x2519f3090:	eor	w3, w0, w3
0x2519f3094:	and	w2, w3, w2
0x2519f3098:	and	w0, w0, w28
0x2519f309c:	mov	w3, #0x340
0x2519f30a0:	movk	w3, #0x1c24, lsl #16
0x2519f30a4:	eor	w0, w0, w3
0x2519f30a8:	eor	w0, w0, w2
0x2519f30ac:	lsl	w2, w17, #8
0x2519f30b0:	sub	w3, w28, #0x40
0x2519f30b4:	and	w3, w2, w3
0x2519f30b8:	mov	w5, #0x4000
0x2519f30bc:	movk	w5, #0x3517, lsl #16
0x2519f30c0:	eor	w2, w2, w5
0x2519f30c4:	and	w2, w2, w0
0x2519f30c8:	eor	w17, w3, w17
0x2519f30cc:	eor	w17, w17, w2
0x2519f30d0:	lsl	w2, w0, #8
0x2519f30d4:	mov	w3, #0x35170000
0x2519f30d8:	eor	w3, w2, w3
0x2519f30dc:	and	w0, w3, w0
0x2519f30e0:	mov	w5, #0x5e350000
0x2519f30e4:	and	w2, w2, w5
0x2519f30e8:	mov	w3, #0x4a200000
0x2519f30ec:	eor	w2, w2, w3
0x2519f30f0:	eor	w0, w2, w0
0x2519f30f4:	lsl	w2, w17, #0x10
0x2519f30f8:	mov	w3, #0x17400000
0x2519f30fc:	eor	w3, w2, w3
0x2519f3100:	and	w0, w3, w0
0x2519f3104:	and	w2, w2, w5
0x2519f3108:	eor	w17, w2, w17
0x2519f310c:	eor	w17, w17, w0
0x2519f3110:	eor	w9, w9, w17, lsl #1
0x2519f3114:	mov	w17, #0xa4f1
0x2519f3118:	movk	w17, #0xb8ea, lsl #16
0x2519f311c:	eor	w0, w9, w17
0x2519f3120:	add	x4, x4, #1
0x2519f3124:	add	x9, x24, #0x40
0x2519f3128:	cmp	x4, x9
0x2519f312c:	cset	w9, eq
0x2519f3130:	mov	w17, #0x1eb
0x2519f3134:	mul	w9, w9, w17
0x2519f3138:	eor	w9, w9, w1
0x2519f313c:	ldr	x9, [x27, w9, sxtw #3]
0x2519f3140:	mov	x3, x16
0x2519f3144:	mov	x2, x14
0x2519f3148:	mov	x17, #0x86cf
0x2519f314c:	braa	x9, x17
0x2519f3150:	mov	w9, #0xcb7d
0x2519f3154:	movk	w9, #0x4828, lsl #16
0x2519f3158:	add	w8, w8, w9
0x2519f315c:	mov	w9, #0x10c1
0x2519f3160:	movk	w9, #0x2510, lsl #16
0x2519f3164:	orr	w9, w8, w9
0x2519f3168:	str	wzr, [sp, #0x18c]
0x2519f316c:	mov	w14, #0x1f79
0x2519f3170:	movk	w14, #0xd3ef, lsl #16
0x2519f3174:	mov	w8, #0x61c6
0x2519f3178:	movk	w8, #0x6c05, lsl #16
0x2519f317c:	add	w8, w9, w8
0x2519f3180:	ldr	w10, [sp, #0x18c]
0x2519f3184:	add	w11, w10, #1
0x2519f3188:	str	w11, [sp, #0x18c]
0x2519f318c:	ldr	w19, [x26, x10, lsl #2]
0x2519f3190:	ldr	x10, [sp, #0xe0]
0x2519f3194:	str	w11, [x10]
0x2519f3198:	mov	x23, x4
0x2519f319c:	ldr	w20, [x4]
0x2519f31a0:	mov	w10, #0xd
0x2519f31a4:	eor	w10, w8, w10
0x2519f31a8:	sub	x11, x29, #0x98
0x2519f31ac:	eor	x11, x11, x5
0x2519f31b0:	mov	w12, #0x9f29
0x2519f31b4:	movk	w12, #0x6c83, lsl #16
0x2519f31b8:	mul	x11, x11, x12
0x2519f31bc:	eor	w8, w8, w11
0x2519f31c0:	eor	x12, x20, x11
0x2519f31c4:	sub	x13, x29, #0x98
0x2519f31c8:	str	x12, [x13, #0x20]
0x2519f31cc:	add	w10, w10, w11
0x2519f31d0:	stur	w10, [x29, #-0x80]
0x2519f31d4:	stp	w8, w11, [x29, #-0x90]
0x2519f31d8:	mov	w10, #0x68
0x2519f31dc:	eor	w10, w8, w10
0x2519f31e0:	stur	w10, [x29, #-0x7c]
0x2519f31e4:	mov	w10, #0x13ff
0x2519f31e8:	add	x10, x11, x10
0x2519f31ec:	str	x10, [x13, #0x10]
0x2519f31f0:	mov	w10, #0x754a
0x2519f31f4:	movk	w10, #0xbaee, lsl #16
0x2519f31f8:	sub	w10, w10, w11
0x2519f31fc:	add	w9, w10, w9
0x2519f3200:	stur	w9, [x29, #-0x98]
0x2519f3204:	ldr	x8, [sp, #0x178]
0x2519f3208:	ldr	w8, [x8]
0x2519f320c:	ldr	w9, [x24]
0x2519f3210:	add	w8, w9, w8
0x2519f3214:	eor	w8, w8, w22
0x2519f3218:	mul	w8, w8, w14
0x2519f321c:	ldr	x9, [sp, #0x158]
0x2519f3220:	add	x9, x9, w8, uxtb
0x2519f3224:	ldrb	w9, [x9]
0x2519f3228:	mov	w10, #0x1a
0x2519f322c:	eor	w9, w9, w10
0x2519f3230:	ldr	x10, [sp, #0x150]
0x2519f3234:	ldrb	w9, [x10, w9, uxtw]
0x2519f3238:	eor	w8, w8, w9
0x2519f323c:	and	w8, w8, #0xff
0x2519f3240:	add	w8, w8, #0x333
0x2519f3244:	ldr	x8, [x28, w8, uxtw #3]
0x2519f3248:	sub	x0, x29, #0x98
0x2519f324c:	mov	x17, #0x6b0e
0x2519f3250:	blraa	x8, x17
0x2519f3254:	ldursw	x8, [x29, #-0x94]
0x2519f3258:	add	x8, x28, x8, lsl #3
0x2519f325c:	ldr	x8, [x8]
0x2519f3260:	mov	x17, #0x6b6
0x2519f3264:	braa	x8, x17
0x2519f3268:	ldr	x8, [x0, #0x30]
0x2519f326c:	stp	x8, x16, [sp, #0x20]
0x2519f3270:	ldr	x8, [x0, #0x18]
0x2519f3274:	ldrb	w9, [x8], #4
0x2519f3278:	lsl	x10, x9, #6
0x2519f327c:	sub	x9, x10, x9, lsl #3
0x2519f3280:	add	x10, x8, x9
0x2519f3284:	add	x8, x10, #0x14
0x2519f3288:	sub	x10, x29, #0x80
0x2519f328c:	mov	w9, #0x2c50
0x2519f3290:	movk	w9, #0x64f7, lsl #16
0x2519f3294:	and	w9, w10, w9
0x2519f3298:	lsl	w9, w9, #1
0x2519f329c:	sub	w9, w9, w10
0x2519f32a0:	mov	w10, #0xd3a8
0x2519f32a4:	movk	w10, #0x1b08, lsl #16
0x2519f32a8:	add	w9, w9, w10
0x2519f32ac:	mov	w10, #0x3fc1
0x2519f32b0:	movk	w10, #0x962a, lsl #16
0x2519f32b4:	eor	w9, w9, w10
0x2519f32b8:	mov	w10, #0x72f
0x2519f32bc:	movk	w10, #0x132d, lsl #16
0x2519f32c0:	mul	w9, w9, w10
0x2519f32c4:	add	x10, sp, #0x68
0x2519f32c8:	stur	x10, [x29, #-0x80]
0x2519f32cc:	add	x19, sp, #0x68
0x2519f32d0:	mov	w10, #0xeb00
0x2519f32d4:	movk	w10, #0x3d36, lsl #16
0x2519f32d8:	sub	w10, w10, w9
0x2519f32dc:	stur	x8, [x29, #-0x70]
0x2519f32e0:	add	w8, w9, w26
0x2519f32e4:	add	w8, w8, #0x1ba
0x2519f32e8:	stp	w10, w8, [x29, #-0x78]
0x2519f32ec:	mov	w8, #0xddd
0x2519f32f0:	eor	w8, w9, w8
0x2519f32f4:	sturh	w8, [x29, #-0x68]
0x2519f32f8:	ldr	w8, [x21]
0x2519f32fc:	ldr	w9, [x25]
0x2519f3300:	sub	w8, w9, w8
0x2519f3304:	eor	w8, w8, w20
0x2519f3308:	mul	w8, w8, w2
0x2519f330c:	ldr	x9, [x22, #0x128]
0x2519f3310:	sub	x11, x9, #8
0x2519f3314:	add	x9, x11, w8, uxtb
0x2519f3318:	ldrb	w9, [x9]
0x2519f331c:	eor	w9, w9, #0x18
0x2519f3320:	ldr	x10, [x22, #0x638]
0x2519f3324:	sub	x12, x10, #4
0x2519f3328:	ldrb	w9, [x12, w9, uxtw]
0x2519f332c:	str	x12, [sp, #0x10]
0x2519f3330:	eor	w8, w9, w8
0x2519f3334:	and	w8, w8, #0xff
0x2519f3338:	add	w8, w8, #0x66
0x2519f333c:	ldr	x8, [x22, w8, uxtw #3]
0x2519f3340:	ldr	x8, [x8]
0x2519f3344:	stp	x11, x8, [sp, #0x38]
0x2519f3348:	ldr	w8, [x21]
0x2519f334c:	ldr	w9, [x25]
0x2519f3350:	eor	w8, w8, w20
0x2519f3354:	eor	w8, w8, w9
0x2519f3358:	mul	w8, w8, w2
0x2519f335c:	add	x9, x11, w8, uxtb
0x2519f3360:	ldrb	w9, [x9]
0x2519f3364:	mov	w10, #0xb3
0x2519f3368:	eor	w9, w9, w10
0x2519f336c:	ldrb	w9, [x12, w9, uxtw]
0x2519f3370:	eor	w8, w8, w9
0x2519f3374:	and	w8, w8, #0xff
0x2519f3378:	add	w8, w8, #0x3ab
0x2519f337c:	ldr	x8, [x23, w8, uxtw #3]
0x2519f3380:	str	x0, [sp, #0x30]
0x2519f3384:	sub	x0, x29, #0x80
0x2519f3388:	add	x1, sp, #0x40
0x2519f338c:	str	w13, [sp, #0x1c]
0x2519f3390:	mov	x17, #0x284a
0x2519f3394:	blraa	x8, x17
0x2519f3398:	mov	x8, sp
0x2519f339c:	ldr	x9, [sp, #0x40]
0x2519f33a0:	add	x8, x8, x9
0x2519f33a4:	mov	sp, x8
0x2519f33a8:	add	w10, w26, #0x1cc
0x2519f33ac:	str	w10, [sp, #0xc]
0x2519f33b0:	mov	w8, #0xabd0
0x2519f33b4:	movk	w8, #0x7923, lsl #16
0x2519f33b8:	sub	x9, x29, #0x80
0x2519f33bc:	and	w8, w9, w8
0x2519f33c0:	lsl	w8, w8, #1
0x2519f33c4:	sub	w8, w8, w9
0x2519f33c8:	mov	w9, #0x542b
0x2519f33cc:	movk	w9, #0x86dc, lsl #16
0x2519f33d0:	add	w8, w8, w9
0x2519f33d4:	mov	w9, #0xb842
0x2519f33d8:	movk	w9, #0xbfe, lsl #16
0x2519f33dc:	eor	w8, w8, w9
0x2519f33e0:	mov	w9, #0x72f
0x2519f33e4:	movk	w9, #0x132d, lsl #16
0x2519f33e8:	mul	w8, w8, w9
0x2519f33ec:	mov	w9, #0xb21c
0x2519f33f0:	movk	w9, #0x583a, lsl #16
0x2519f33f4:	eor	w9, w8, w9
0x2519f33f8:	sub	w8, w10, w8
0x2519f33fc:	stp	w8, w9, [x29, #-0x70]
0x2519f3400:	ldr	x8, [sp, #0x20]
0x2519f3404:	stp	x19, x8, [x29, #-0x80]
0x2519f3408:	ldr	w8, [x21]
0x2519f340c:	ldr	w9, [x25]
0x2519f3410:	sub	w8, w9, w8
0x2519f3414:	eor	w8, w8, w20
0x2519f3418:	mov	w11, #0x1f79
0x2519f341c:	movk	w11, #0xd3ef, lsl #16
0x2519f3420:	mul	w8, w8, w11
0x2519f3424:	add	x9, x28, w8, uxtb
0x2519f3428:	ldrb	w9, [x9]
0x2519f342c:	mov	w10, #0x69
0x2519f3430:	eor	w9, w9, w10
0x2519f3434:	ldrb	w9, [x27, w9, uxtw]
0x2519f3438:	eor	w8, w8, w9
0x2519f343c:	and	w8, w8, #0xff
0x2519f3440:	sub	w8, w8, #0xb2
0x2519f3444:	ldr	x27, [x22, w8, sxtw #3]
0x2519f3448:	ldr	x8, [x27]
0x2519f344c:	str	x8, [sp, #0x58]
0x2519f3450:	ldr	w8, [x21]
0x2519f3454:	ldr	w9, [x25]
0x2519f3458:	eor	w8, w8, w20
0x2519f345c:	eor	w8, w8, w9
0x2519f3460:	mul	w8, w8, w11
0x2519f3464:	ldr	x28, [sp, #0x38]
0x2519f3468:	add	x9, x28, w8, uxtb
0x2519f346c:	ldrb	w9, [x9]
0x2519f3470:	eor	w9, w9, #0x18
0x2519f3474:	ldr	x19, [sp, #0x10]
0x2519f3478:	ldrb	w9, [x19, w9, uxtw]
0x2519f347c:	eor	w8, w8, w9
0x2519f3480:	and	w8, w8, #0xff
0x2519f3484:	add	w8, w8, #0x418
0x2519f3488:	ldr	x8, [x23, w8, uxtw #3]
0x2519f348c:	sub	x0, x29, #0x80
0x2519f3490:	add	x1, sp, #0x58
0x2519f3494:	mov	x17, #0xe936
0x2519f3498:	blraa	x8, x17
0x2519f349c:	mov	x8, sp
0x2519f34a0:	ldr	x9, [sp, #0x58]
0x2519f34a4:	add	x8, x8, x9
0x2519f34a8:	mov	sp, x8
0x2519f34ac:	mov	w8, #0x7c7c
0x2519f34b0:	movk	w8, #0x2be6, lsl #16
0x2519f34b4:	ldr	w9, [sp, #0x1c]
0x2519f34b8:	add	w8, w9, w8
0x2519f34bc:	mov	w9, #0xec69
0x2519f34c0:	movk	w9, #0x8d22, lsl #16
0x2519f34c4:	sub	x10, x29, #0x80
0x2519f34c8:	eor	w9, w10, w9
0x2519f34cc:	mov	w10, #0x72f
0x2519f34d0:	movk	w10, #0x132d, lsl #16
0x2519f34d4:	mul	w9, w9, w10
0x2519f34d8:	ldr	w10, [sp, #0xc]
0x2519f34dc:	sub	w10, w10, w9
0x2519f34e0:	eor	w8, w8, w9
0x2519f34e4:	stp	w10, w8, [x29, #-0x70]
0x2519f34e8:	ldr	x9, [sp, #0x28]
0x2519f34ec:	add	x8, sp, #0x68
0x2519f34f0:	stp	x8, x9, [x29, #-0x80]
0x2519f34f4:	ldr	x8, [x27]
0x2519f34f8:	str	x8, [sp, #0x50]
0x2519f34fc:	ldr	w8, [x21]
0x2519f3500:	ldr	w9, [x25]
0x2519f3504:	eor	w8, w8, w20
0x2519f3508:	eor	w8, w8, w9
0x2519f350c:	mov	w9, #0x1f79
0x2519f3510:	movk	w9, #0xd3ef, lsl #16
0x2519f3514:	mul	w8, w8, w9
0x2519f3518:	add	x9, x28, w8, uxtb
0x2519f351c:	ldrb	w9, [x9]
0x2519f3520:	mov	w10, #0x7d
0x2519f3524:	eor	w9, w9, w10
0x2519f3528:	ldrb	w9, [x19, w9, uxtw]
0x2519f352c:	eor	w8, w8, w9
0x2519f3530:	and	w8, w8, #0xff
0x2519f3534:	add	w8, w8, #0x455
0x2519f3538:	ldr	x8, [x23, w8, uxtw #3]
0x2519f353c:	sub	x0, x29, #0x80
0x2519f3540:	add	x1, sp, #0x50
0x2519f3544:	mov	x17, #0xe936
0x2519f3548:	blraa	x8, x17
0x2519f354c:	mov	x8, sp
0x2519f3550:	ldr	x9, [sp, #0x50]
0x2519f3554:	add	x8, x8, x9
0x2519f3558:	mov	sp, x8
0x2519f355c:	mov	x8, #0x1448
0x2519f3560:	movk	x8, #0xb53e, lsl #16
0x2519f3564:	movk	x8, #0xbb6d, lsl #32
0x2519f3568:	movk	x8, #0x8598, lsl #48
0x2519f356c:	sub	x10, x29, #0x80
0x2519f3570:	orr	w9, w8, w10
0x2519f3574:	and	w8, w10, w8
0x2519f3578:	sub	w8, w9, w8
0x2519f357c:	mov	w9, #0x3256
0x2519f3580:	movk	w9, #0x8e81, lsl #16
0x2519f3584:	eor	w8, w8, w9
0x2519f3588:	mov	w9, #0x9c25
0x2519f358c:	movk	w9, #0x4a5e, lsl #16
0x2519f3590:	add	x10, sp, #0x68
0x2519f3594:	stur	x10, [x29, #-0x80]
0x2519f3598:	msub	w8, w8, w9, w26
0x2519f359c:	sub	w8, w8, #0x179
0x2519f35a0:	stur	w8, [x29, #-0x78]
0x2519f35a4:	sub	x27, x29, #0x94
0x2519f35a8:	stur	x27, [x29, #-0x70]
0x2519f35ac:	ldr	w8, [x21]
0x2519f35b0:	ldr	w9, [x25]
0x2519f35b4:	eor	w8, w8, w20
0x2519f35b8:	eor	w8, w8, w9
0x2519f35bc:	mov	w11, #0x1f79
0x2519f35c0:	movk	w11, #0xd3ef, lsl #16
0x2519f35c4:	mul	w8, w8, w11
0x2519f35c8:	ldr	x9, [x22, #0x180]
0x2519f35cc:	add	x9, x9, w8, uxtb
0x2519f35d0:	ldurb	w9, [x9, #-8]
0x2519f35d4:	mov	w10, #0x3b
0x2519f35d8:	eor	w9, w9, w10
0x2519f35dc:	ldr	x10, [x22, #0x230]
0x2519f35e0:	add	x9, x10, x9
0x2519f35e4:	ldurb	w9, [x9, #-8]
0x2519f35e8:	eor	w8, w9, w8
0x2519f35ec:	and	w8, w8, #0xff
0x2519f35f0:	add	w8, w8, #0xb
0x2519f35f4:	ldr	x8, [x22, w8, uxtw #3]
0x2519f35f8:	ldur	x8, [x8, #-4]
0x2519f35fc:	str	x8, [sp, #0x48]
0x2519f3600:	ldr	w8, [x21]
0x2519f3604:	ldr	w9, [x25]
0x2519f3608:	eor	w8, w8, w20
0x2519f360c:	eor	w8, w8, w9
0x2519f3610:	mul	w8, w8, w11
0x2519f3614:	ldr	x9, [sp, #0x38]
0x2519f3618:	add	x9, x9, w8, uxtb
0x2519f361c:	ldrb	w9, [x9]
0x2519f3620:	mov	w10, #0x7d
0x2519f3624:	eor	w9, w9, w10
0x2519f3628:	ldrb	w9, [x19, w9, uxtw]
0x2519f362c:	eor	w8, w8, w9
0x2519f3630:	and	w8, w8, #0xff
0x2519f3634:	add	w8, w8, #0x47f
0x2519f3638:	ldr	x8, [x23, w8, uxtw #3]
0x2519f363c:	sub	x0, x29, #0x80
0x2519f3640:	add	x1, sp, #0x48
0x2519f3644:	mov	x17, #0xa672
0x2519f3648:	blraa	x8, x17
0x2519f364c:	ldr	x0, [sp, #0x30]
0x2519f3650:	mov	x8, sp
0x2519f3654:	ldr	x9, [sp, #0x48]
0x2519f3658:	add	x8, x8, x9
0x2519f365c:	mov	sp, x8
0x2519f3660:	mov	x9, #0
0x2519f3664:	mov	w8, #0
0x2519f3668:	mov	w10, #0x1ce6
0x2519f366c:	movk	w10, #0x24ea, lsl #16
0x2519f3670:	add	w10, w26, w10
0x2519f3674:	mov	w11, #0xe1e6
0x2519f3678:	movk	w11, #0xdb15, lsl #16
0x2519f367c:	and	w10, w10, w11
0x2519f3680:	mov	w11, #0x224
0x2519f3684:	add	x12, x27, x9
0x2519f3688:	ldrb	w12, [x12]
0x2519f368c:	add	x13, x24, x9
0x2519f3690:	ldrb	w13, [x13]
0x2519f3694:	add	w14, w10, #0x68
0x2519f3698:	and	w14, w14, w13, lsl #1
0x2519f369c:	sub	w13, w13, w14
0x2519f36a0:	add	w13, w13, #0x75
0x2519f36a4:	eor	w12, w13, w12
0x2519f36a8:	orr	w8, w12, w8
0x2519f36ac:	cmp	x9, #0x13
0x2519f36b0:	cset	w12, eq
0x2519f36b4:	mul	w12, w12, w11
0x2519f36b8:	eor	w12, w12, w26
0x2519f36bc:	ldr	x12, [x23, w12, sxtw #3]
0x2519f36c0:	mov	x17, #0x691d
0x2519f36c4:	braa	x12, x17
0x2519f36c8:	add	w9, w0, w9
0x2519f36cc:	mov	w10, w8
0x2519f36d0:	add	x11, x2, x10
0x2519f36d4:	ldrb	w11, [x11]
0x2519f36d8:	ldrb	w12, [x15]
0x2519f36dc:	lsl	x13, x12, #6
0x2519f36e0:	sub	x12, x13, x12, lsl #3
0x2519f36e4:	add	x13, x15, #4
0x2519f36e8:	add	x14, x13, x12
0x2519f36ec:	add	w9, w9, #0x1b3
0x2519f36f0:	add	x12, x14, #4
0x2519f36f4:	add	x10, x12, x10
0x2519f36f8:	strb	w11, [x10]
0x2519f36fc:	add	w8, w8, w6
0x2519f3700:	add	w8, w8, w9
0x2519f3704:	add	w10, w6, w9
0x2519f3708:	add	w13, w10, #0xd
0x2519f370c:	orr	w9, w10, #0x30
0x2519f3710:	add	w11, w10, #0x14d
0x2519f3714:	cmp	w8, #0x10
0x2519f3718:	cset	w12, lo
0x2519f371c:	eor	w10, w12, w10
0x2519f3720:	and	w10, w10, #1
0x2519f3724:	mul	w10, w10, w1
0x2519f3728:	eor	w10, w10, w11
0x2519f372c:	ldr	x10, [x27, w10, sxtw #3]
0x2519f3730:	mov	x17, #0x4f1b
0x2519f3734:	braa	x10, x17
0x2519f3738:	mov	w11, w9
0x2519f373c:	mov	w9, w1
0x2519f3740:	sub	w12, w8, #0xfd
0x2519f3744:	eor	x13, x12, x15
0x2519f3748:	add	x13, x13, x11
0x2519f374c:	ldrb	w14, [x0, x11]
0x2519f3750:	add	w11, w10, #1
0x2519f3754:	strb	w14, [x3, w10, uxtw]
0x2519f3758:	cmp	x13, x9
0x2519f375c:	cset	w10, eq
0x2519f3760:	mul	w10, w10, w16
0x2519f3764:	eor	w10, w10, w8
0x2519f3768:	ldr	x10, [x20, w10, sxtw #3]
0x2519f376c:	mov	x17, #0xff56
0x2519f3770:	braa	x10, x17
0x2519f3774:	ldr	w9, [x8, #0x40]
0x2519f3778:	add	w9, w9, #1
0x2519f377c:	str	w9, [x8, #0x40]
0x2519f3780:	add	sp, sp, #0x10
0x2519f3784:	ret	
0x2519f3788:	mov	x19, x0
0x2519f378c:	mov	x12, x22
0x2519f3790:	mov	x8, x30
0x2519f3794:	lsl	w9, w25, #1
0x2519f3798:	eor	w17, w0, w22
0x2519f379c:	mov	w0, #0xf410
0x2519f37a0:	movk	w0, #0x393a, lsl #16
0x2519f37a4:	and	w0, w0, w17, lsl #1
0x2519f37a8:	add	w17, w17, w23
0x2519f37ac:	mov	w2, #0x1bfa
0x2519f37b0:	movk	w2, #0x5a7e, lsl #16
0x2519f37b4:	eor	w2, w6, w2
0x2519f37b8:	mov	w22, #0xe7d0
0x2519f37bc:	movk	w22, #0xa581, lsl #16
0x2519f37c0:	eor	w22, w9, w22
0x2519f37c4:	add	w2, w2, w22
0x2519f37c8:	mov	w22, #0x8f15
0x2519f37cc:	movk	w22, #0x3ab8, lsl #16
0x2519f37d0:	eor	w22, w6, w22
0x2519f37d4:	mov	w26, #0x70eb
0x2519f37d8:	movk	w26, #0xc547, lsl #16
0x2519f37dc:	add	w22, w22, w26
0x2519f37e0:	eor	w2, w2, w22
0x2519f37e4:	mov	w22, #0xeee7
0x2519f37e8:	movk	w22, #0xfc5b, lsl #16
0x2519f37ec:	eor	w6, w6, w22
0x2519f37f0:	mov	w22, #0x1119
0x2519f37f4:	movk	w22, #0x3a4, lsl #16
0x2519f37f8:	add	w6, w6, w22
0x2519f37fc:	sub	w17, w17, w0
0x2519f3800:	eor	w2, w2, w6
0x2519f3804:	add	x0, x10, x4
0x2519f3808:	ldrb	w6, [x7, x0]
0x2519f380c:	sub	w6, w6, #0x3d
0x2519f3810:	eor	w17, w17, w30
0x2519f3814:	add	x6, x11, w6, uxtb #2
0x2519f3818:	ldr	w6, [x6]
0x2519f381c:	mov	w22, #0xaa56
0x2519f3820:	movk	w22, #0x8dc9, lsl #16
0x2519f3824:	eor	w22, w6, w22
0x2519f3828:	mov	w26, #0x55aa
0x2519f382c:	movk	w26, #0x7236, lsl #16
0x2519f3830:	add	w22, w22, w26
0x2519f3834:	mov	w26, #0x6cca
0x2519f3838:	movk	w26, #0x5cc6, lsl #16
0x2519f383c:	eor	w26, w6, w26
0x2519f3840:	mov	w27, #0x9336
0x2519f3844:	movk	w27, #0xa339, lsl #16
0x2519f3848:	add	w26, w26, w27
0x2519f384c:	eor	w22, w22, w26
0x2519f3850:	mov	w26, #0x1fac
0x2519f3854:	movk	w26, #0xe74d, lsl #16
0x2519f3858:	eor	w6, w6, w26
0x2519f385c:	mov	w26, #0xe054
0x2519f3860:	movk	w26, #0x18b2, lsl #16
0x2519f3864:	add	w6, w6, w26
0x2519f3868:	ldr	w26, [x21, x0, lsl #2]
0x2519f386c:	eor	w6, w22, w6
0x2519f3870:	add	w17, w2, w17
0x2519f3874:	add	w17, w17, w26
0x2519f3878:	mov	w2, #0x38f5
0x2519f387c:	movk	w2, #0x22b1, lsl #16
0x2519f3880:	add	w17, w17, w2
0x2519f3884:	add	w17, w17, w6
0x2519f3888:	mov	w2, #0x25f7
0x2519f388c:	movk	w2, #0x3559, lsl #16
0x2519f3890:	eor	w2, w17, w2
0x2519f3894:	mov	w6, #0x2c3d
0x2519f3898:	movk	w6, #0x38ba, lsl #16
0x2519f389c:	and	w6, w17, w6
0x2519f38a0:	mov	w22, #0x2dbd
0x2519f38a4:	movk	w22, #0x3439, lsl #16
0x2519f38a8:	eor	w22, w17, w22
0x2519f38ac:	and	w22, w22, w6, lsl #1
0x2519f38b0:	eor	w6, w22, w6
0x2519f38b4:	lsl	w22, w2, #1
0x2519f38b8:	mov	w26, #0x1394
0x2519f38bc:	movk	w26, #0x1bc6, lsl #16
0x2519f38c0:	eor	w26, w22, w26
0x2519f38c4:	and	w2, w26, w2
0x2519f38c8:	mov	w30, #0x9ca
0x2519f38cc:	movk	w30, #0xde3, lsl #16
0x2519f38d0:	and	w22, w22, w30
0x2519f38d4:	eor	w2, w2, w22
0x2519f38d8:	mov	w22, #0x84a
0x2519f38dc:	movk	w22, #0x421, lsl #16
0x2519f38e0:	eor	w22, w2, w22
0x2519f38e4:	mov	w26, #0x180
0x2519f38e8:	movk	w26, #0x1c0, lsl #16
0x2519f38ec:	eor	w2, w2, w26
0x2519f38f0:	lsl	w26, w22, #2
0x2519f38f4:	and	w2, w2, w6, lsl #2
0x2519f38f8:	mov	w27, #0x2728
0x2519f38fc:	movk	w27, #0x378c, lsl #16
0x2519f3900:	eor	w27, w26, w27
0x2519f3904:	and	w22, w27, w22
0x2519f3908:	sub	w27, w30, #2
0x2519f390c:	and	w26, w26, w27
0x2519f3910:	eor	w22, w22, w26
0x2519f3914:	eor	w2, w2, w6
0x2519f3918:	mov	w6, #0x8c2
0x2519f391c:	movk	w6, #0x863, lsl #16
0x2519f3920:	eor	w6, w22, w6
0x2519f3924:	mov	w26, #0x100
0x2519f3928:	movk	w26, #0x580, lsl #16
0x2519f392c:	eor	w22, w22, w26
0x2519f3930:	and	w22, w22, w2, lsl #4
0x2519f3934:	lsl	w26, w6, #4
0x2519f3938:	mov	w27, #0x9ca0
0x2519f393c:	movk	w27, #0xde30, lsl #16
0x2519f3940:	eor	w27, w26, w27
0x2519f3944:	eor	w2, w22, w2
0x2519f3948:	and	w6, w27, w6
0x2519f394c:	sub	w22, w30, #0xa
0x2519f3950:	and	w22, w26, w22
0x2519f3954:	eor	w6, w6, w22
0x2519f3958:	mov	w22, #0x14a
0x2519f395c:	movk	w22, #0x1c3, lsl #16
0x2519f3960:	eor	w22, w6, w22
0x2519f3964:	mov	w26, #0x800
0x2519f3968:	movk	w26, #0xc20, lsl #16
0x2519f396c:	eor	w6, w6, w26
0x2519f3970:	and	w6, w6, w2, lsl #8
0x2519f3974:	eor	w2, w2, w30
0x2519f3978:	lsl	w26, w22, #8
0x2519f397c:	mov	w27, #-0x1d080000
0x2519f3980:	add	w27, w27, #0x110, lsl #12
0x2519f3984:	eor	w27, w26, w27
0x2519f3988:	eor	w2, w2, w6
0x2519f398c:	and	w6, w27, w22
0x2519f3990:	mov	w27, #0xde30000
0x2519f3994:	and	w22, w26, w27
0x2519f3998:	mov	w26, #0xce20000
0x2519f399c:	eor	w22, w22, w26
0x2519f39a0:	eor	w6, w22, w6
0x2519f39a4:	lsl	w22, w2, #0x10
0x2519f39a8:	mov	w26, #0x9ca0000
0x2519f39ac:	eor	w26, w22, w26
0x2519f39b0:	and	w6, w26, w6
0x2519f39b4:	and	w22, w22, w27
0x2519f39b8:	ldrb	w0, [x24, x0]
0x2519f39bc:	mov	w26, #0x7c4d
0x2519f39c0:	movk	w26, #0x3222, lsl #16
0x2519f39c4:	add	w26, w0, w26
0x2519f39c8:	eor	w2, w22, w2
0x2519f39cc:	mov	w22, #0x9fbe
0x2519f39d0:	movk	w22, #0x894c, lsl #16
0x2519f39d4:	eor	w22, w26, w22
0x2519f39d8:	mov	w27, #0x1cdc
0x2519f39dc:	movk	w27, #0x4491, lsl #16
0x2519f39e0:	add	w22, w22, w27
0x2519f39e4:	mov	w27, #0x7c3c
0x2519f39e8:	movk	w27, #0xb4d7, lsl #16
0x2519f39ec:	eor	w27, w26, w27
0x2519f39f0:	mov	w30, #0xff5a
0x2519f39f4:	movk	w30, #0x790a, lsl #16
0x2519f39f8:	add	w27, w27, w30
0x2519f39fc:	eor	w22, w22, w27
0x2519f3a00:	eor	w2, w2, w6
0x2519f3a04:	mov	w6, #0xe0e7
0x2519f3a08:	movk	w6, #0xf04c, lsl #16
0x2519f3a0c:	eor	w6, w26, w6
0x2519f3a10:	mov	w27, #0x6383
0x2519f3a14:	movk	w27, #0x3d91, lsl #16
0x2519f3a18:	add	w6, w6, w27
0x2519f3a1c:	eor	w6, w26, w6
0x2519f3a20:	mov	w27, #0x7fff
0x2519f3a24:	movk	w27, #0xfff5, lsl #16
0x2519f3a28:	eor	w26, w26, w27
0x2519f3a2c:	mov	w27, #0xfc9b
0x2519f3a30:	movk	w27, #0x3228, lsl #16
0x2519f3a34:	add	w26, w26, w27
0x2519f3a38:	eor	w6, w6, w22
0x2519f3a3c:	mov	w22, #0xc68e
0x2519f3a40:	movk	w22, #0x6331, lsl #16
0x2519f3a44:	eor	w22, w26, w22
0x2519f3a48:	eor	w6, w6, w22
0x2519f3a4c:	eor	w17, w17, w2, lsl #1
0x2519f3a50:	and	w2, w6, #2
0x2519f3a54:	mov	w22, #0x1d
0x2519f3a58:	and	w6, w6, w22
0x2519f3a5c:	mov	w22, #0x3fa9
0x2519f3a60:	movk	w22, #0x30f8, lsl #16
0x2519f3a64:	eor	w17, w17, w22
0x2519f3a68:	mov	w22, #0x14
0x2519f3a6c:	eor	w6, w6, w22
0x2519f3a70:	lsl	w2, w17, w2
0x2519f3a74:	sub	w0, w14, w0
0x2519f3a78:	mov	w22, #0x7958
0x2519f3a7c:	movk	w22, #0x123a, lsl #16
0x2519f3a80:	eor	w22, w19, w22
0x2519f3a84:	mov	w26, #0x86a8
0x2519f3a88:	movk	w26, #0xedc5, lsl #16
0x2519f3a8c:	add	w22, w22, w26
0x2519f3a90:	lsr	w17, w17, w0
0x2519f3a94:	mov	w0, #0x4783
0x2519f3a98:	movk	w0, #0xaa7, lsl #16
0x2519f3a9c:	eor	w0, w19, w0
0x2519f3aa0:	mov	w26, #0xb87d
0x2519f3aa4:	movk	w26, #0xf558, lsl #16
0x2519f3aa8:	add	w0, w0, w26
0x2519f3aac:	eor	w0, w22, w0
0x2519f3ab0:	mov	w22, #0x44d3
0x2519f3ab4:	movk	w22, #0x8400, lsl #16
0x2519f3ab8:	eor	w22, w19, w22
0x2519f3abc:	mov	w26, #0xbb2d
0x2519f3ac0:	movk	w26, #0x7bff, lsl #16
0x2519f3ac4:	add	w22, w22, w26
0x2519f3ac8:	lsl	w2, w2, w6
0x2519f3acc:	eor	w0, w0, w22
0x2519f3ad0:	add	w17, w0, w17
0x2519f3ad4:	add	w17, w17, w2
0x2519f3ad8:	mov	w0, #0x7778
0x2519f3adc:	movk	w0, #0xfc83, lsl #16
0x2519f3ae0:	add	w17, w17, w0
0x2519f3ae4:	mov	w0, #0x4918
0x2519f3ae8:	movk	w0, #0x75b6, lsl #16
0x2519f3aec:	eor	w0, w17, w0
0x2519f3af0:	mov	w2, #0x108
0x2519f3af4:	eor	w26, w9, w2
0x2519f3af8:	mov	w9, #0x290
0x2519f3afc:	movk	w9, #0xa01a, lsl #16
0x2519f3b00:	and	w9, w17, w9
0x2519f3b04:	lsl	w2, w9, #1
0x2519f3b08:	and	w6, w2, w0
0x2519f3b0c:	mov	w22, #0x100
0x2519f3b10:	movk	w22, #0x4024, lsl #16
0x2519f3b14:	and	w2, w2, w22
0x2519f3b18:	lsl	w22, w0, #1
0x2519f3b1c:	orr	w9, w2, w9
0x2519f3b20:	mov	w2, #0x9710
0x2519f3b24:	movk	w2, #0xab58, lsl #16
0x2519f3b28:	eor	w2, w22, w2
0x2519f3b2c:	and	w0, w2, w0
0x2519f3b30:	mov	w27, #0x4b88
0x2519f3b34:	movk	w27, #0xd5ac, lsl #16
0x2519f3b38:	and	w2, w22, w27
0x2519f3b3c:	eor	w0, w0, w2
0x2519f3b40:	mov	w2, #0x4888
0x2519f3b44:	movk	w2, #0x54a4, lsl #16
0x2519f3b48:	eor	w2, w0, w2
0x2519f3b4c:	eor	w9, w9, w6
0x2519f3b50:	mov	w6, #0x4208
0x2519f3b54:	movk	w6, #0xd40c, lsl #16
0x2519f3b58:	eor	w0, w0, w6
0x2519f3b5c:	and	w0, w0, w9, lsl #2
0x2519f3b60:	eor	w9, w0, w9
0x2519f3b64:	lsl	w0, w2, #2
0x2519f3b68:	mov	w6, #0x2e20
0x2519f3b6c:	movk	w6, #0x56b1, lsl #16
0x2519f3b70:	eor	w6, w0, w6
0x2519f3b74:	and	w2, w6, w2
0x2519f3b78:	and	w0, w0, w27
0x2519f3b7c:	eor	w0, w2, w0
0x2519f3b80:	mov	w2, #0x4188
0x2519f3b84:	movk	w2, #0x810c, lsl #16
0x2519f3b88:	eor	w2, w0, w2
0x2519f3b8c:	mov	w6, #0xa00
0x2519f3b90:	movk	w6, #0x54a0, lsl #16
0x2519f3b94:	eor	w0, w0, w6
0x2519f3b98:	and	w0, w0, w9, lsl #4
0x2519f3b9c:	eor	w9, w0, w9
0x2519f3ba0:	lsl	w0, w2, #4
0x2519f3ba4:	mov	w6, #0xb880
0x2519f3ba8:	movk	w6, #0x5ac4, lsl #16
0x2519f3bac:	eor	w6, w0, w6
0x2519f3bb0:	and	w2, w6, w2
0x2519f3bb4:	sub	w6, w27, #8
0x2519f3bb8:	and	w0, w0, w6
0x2519f3bbc:	eor	w0, w2, w0
0x2519f3bc0:	mov	w2, #0x4308
0x2519f3bc4:	movk	w2, #0x8528, lsl #16
0x2519f3bc8:	eor	w2, w0, w2
0x2519f3bcc:	mov	w6, #0x800
0x2519f3bd0:	movk	w6, #0x5084, lsl #16
0x2519f3bd4:	eor	w0, w0, w6
0x2519f3bd8:	and	w0, w0, w9, lsl #8
0x2519f3bdc:	eor	w9, w9, w27
0x2519f3be0:	lsl	w6, w2, #8
0x2519f3be4:	eor	w9, w9, w0
0x2519f3be8:	mov	w0, #0x2c4b0000
0x2519f3bec:	eor	w0, w6, w0
0x2519f3bf0:	and	w0, w0, w2
0x2519f3bf4:	mov	w22, #0x55ac0000
0x2519f3bf8:	and	w2, w6, w22
0x2519f3bfc:	mov	w6, #0x51a40000
0x2519f3c00:	eor	w2, w2, w6
0x2519f3c04:	eor	w0, w2, w0
0x2519f3c08:	lsl	w2, w9, #0x10
0x2519f3c0c:	mov	w6, #0x4b880000
0x2519f3c10:	eor	w6, w2, w6
0x2519f3c14:	and	w0, w6, w0
0x2519f3c18:	and	w2, w2, w22
0x2519f3c1c:	eor	w9, w2, w9
0x2519f3c20:	add	x10, x10, #1
0x2519f3c24:	eor	w9, w9, w0
0x2519f3c28:	add	x27, x5, #0x30
0x2519f3c2c:	cmp	x10, x27
0x2519f3c30:	cset	w0, eq
0x2519f3c34:	mov	w2, #0x289
0x2519f3c38:	mul	w0, w0, w2
0x2519f3c3c:	eor	w0, w0, w25
0x2519f3c40:	eor	w9, w17, w9, lsl #1
0x2519f3c44:	ldr	x2, [x13, w0, sxtw #3]
0x2519f3c48:	mov	x6, x8
0x2519f3c4c:	mov	x30, x12
0x2519f3c50:	mov	x22, x19
0x2519f3c54:	mov	w17, #0xef88
0x2519f3c58:	movk	w17, #0x14cf, lsl #16
0x2519f3c5c:	eor	w0, w9, w17
0x2519f3c60:	mov	x17, #0x8a7f
0x2519f3c64:	braa	x2, x17
0x2519f3c68:	ldr	w10, [sp, #0x94]
0x2519f3c6c:	b	#0x2519fc22c
0x2519f3c70:	mov	w8, #0
0x2519f3c74:	mov	x0, #0
0x2519f3c78:	sub	x15, x29, #0x98
0x2519f3c7c:	add	x9, sp, #0x100
0x2519f3c80:	add	x9, x9, #0x40
0x2519f3c84:	str	x9, [sp, #0x38]
0x2519f3c88:	mov	w9, #0x1a0
0x2519f3c8c:	orr	w9, w13, w9
0x2519f3c90:	mov	x1, #0x426e
0x2519f3c94:	movk	x1, #0x67a9, lsl #16
0x2519f3c98:	movk	x1, #0xb764, lsl #32
0x2519f3c9c:	movk	x1, #0xe612, lsl #48
0x2519f3ca0:	mov	x2, #0xb53e
0x2519f3ca4:	movk	x2, #0x49eb, lsl #16
0x2519f3ca8:	movk	x2, #0x3bc4, lsl #32
0x2519f3cac:	movk	x2, #0x9560, lsl #48
0x2519f3cb0:	mov	w10, #0xb1ce
0x2519f3cb4:	movk	w10, #0x27a4, lsl #16
0x2519f3cb8:	add	w9, w9, w10
0x2519f3cbc:	mov	w10, #0x4cee
0x2519f3cc0:	movk	w10, #0xd85b, lsl #16
0x2519f3cc4:	and	w10, w9, w10
0x2519f3cc8:	mov	w9, #0xa17a
0x2519f3ccc:	eor	w9, w10, w9
0x2519f3cd0:	add	w9, w9, w12
0x2519f3cd4:	and	w3, w9, #0xffff
0x2519f3cd8:	mov	x9, #0x7c8b
0x2519f3cdc:	movk	x9, #0xdd6, lsl #16
0x2519f3ce0:	movk	x9, #0xc8a6, lsl #32
0x2519f3ce4:	movk	x9, #0xdd67, lsl #48
0x2519f3ce8:	add	x11, sp, #0xec
0x2519f3cec:	umulh	x9, x11, x9
0x2519f3cf0:	lsr	x9, x9, #5
0x2519f3cf4:	mov	w12, #0x25
0x2519f3cf8:	msub	x9, x9, x12, x11
0x2519f3cfc:	str	x9, [sp, #0x10]
0x2519f3d00:	mov	w9, #0x20
0x2519f3d04:	mov	w4, #0x3b49
0x2519f3d08:	movk	w4, #0x5189, lsl #16
0x2519f3d0c:	mov	w5, #0xc7ed
0x2519f3d10:	movk	w5, #0xae76, lsl #16
0x2519f3d14:	mov	w6, #0x75
0x2519f3d18:	mov	w7, #0xb9
0x2519f3d1c:	mov	x11, #0x240
0x2519f3d20:	movk	x11, #0x5751, lsl #16
0x2519f3d24:	movk	x11, #0x73e9, lsl #32
0x2519f3d28:	movk	x11, #0x434d, lsl #48
0x2519f3d2c:	and	x11, x15, x11
0x2519f3d30:	lsl	x11, x11, #1
0x2519f3d34:	sub	x11, x11, x15
0x2519f3d38:	mov	x12, #0xfdbf
0x2519f3d3c:	movk	x12, #0xa8ae, lsl #16
0x2519f3d40:	movk	x12, #0x8c16, lsl #32
0x2519f3d44:	movk	x12, #0xbcb2, lsl #48
0x2519f3d48:	add	x11, x11, x12
0x2519f3d4c:	mov	x12, #0x38a6
0x2519f3d50:	movk	x12, #0x301d, lsl #16
0x2519f3d54:	movk	x12, #0x1db4, lsl #32
0x2519f3d58:	movk	x12, #0x2af9, lsl #48
0x2519f3d5c:	eor	x11, x11, x12
0x2519f3d60:	mov	w12, #0xdd99
0x2519f3d64:	movk	w12, #0xf0e1, lsl #16
0x2519f3d68:	mul	x11, x11, x12
0x2519f3d6c:	str	x11, [sp, #0x30]
0x2519f3d70:	mov	x11, #0x9411
0x2519f3d74:	movk	x11, #0x90f0, lsl #16
0x2519f3d78:	movk	x11, #0x5a47, lsl #32
0x2519f3d7c:	movk	x11, #0x87e3, lsl #48
0x2519f3d80:	eor	x11, x15, x11
0x2519f3d84:	mov	x12, #0x80a8
0x2519f3d88:	movk	x12, #0x71a1, lsl #16
0x2519f3d8c:	movk	x12, #0x16f5, lsl #32
0x2519f3d90:	movk	x12, #0x57dc, lsl #48
0x2519f3d94:	and	x12, x11, x12
0x2519f3d98:	lsl	x12, x12, #1
0x2519f3d9c:	sub	x11, x12, x11
0x2519f3da0:	mov	x12, #0x7f53
0x2519f3da4:	movk	x12, #0x8e5e, lsl #16
0x2519f3da8:	movk	x12, #0xe90a, lsl #32
0x2519f3dac:	movk	x12, #0x2823, lsl #48
0x2519f3db0:	add	x11, x11, x12
0x2519f3db4:	mov	x12, #0x2e2b
0x2519f3db8:	movk	x12, #0x2386, lsl #16
0x2519f3dbc:	movk	x12, #0x21b2, lsl #32
0x2519f3dc0:	movk	x12, #0xb5b3, lsl #48
0x2519f3dc4:	eor	x11, x11, x12
0x2519f3dc8:	mov	w13, #0x9f29
0x2519f3dcc:	movk	w13, #0x6c83, lsl #16
0x2519f3dd0:	mul	x11, x11, x13
0x2519f3dd4:	str	x11, [sp, #0xa0]
0x2519f3dd8:	mov	x11, #0x50ba
0x2519f3ddc:	movk	x11, #0xa654, lsl #16
0x2519f3de0:	movk	x11, #0x2f22, lsl #32
0x2519f3de4:	movk	x11, #0x1f5b, lsl #48
0x2519f3de8:	eor	x11, x15, x11
0x2519f3dec:	str	x11, [sp, #0x98]
0x2519f3df0:	mov	x11, #0xd610
0x2519f3df4:	movk	x11, #0x111f, lsl #16
0x2519f3df8:	movk	x11, #0x9602, lsl #32
0x2519f3dfc:	movk	x11, #0x6d39, lsl #48
0x2519f3e00:	and	x11, x15, x11
0x2519f3e04:	lsl	x11, x11, #1
0x2519f3e08:	sub	x11, x11, x15
0x2519f3e0c:	mov	x12, #0x29ea
0x2519f3e10:	movk	x12, #0xeee0, lsl #16
0x2519f3e14:	movk	x12, #0x69fd, lsl #32
0x2519f3e18:	movk	x12, #0x12c6, lsl #48
0x2519f3e1c:	add	x11, x11, x12
0x2519f3e20:	mov	x12, #0xec83
0x2519f3e24:	movk	x12, #0xd3c8, lsl #16
0x2519f3e28:	movk	x12, #0xfb02, lsl #32
0x2519f3e2c:	movk	x12, #0x8b5, lsl #48
0x2519f3e30:	eor	x11, x11, x12
0x2519f3e34:	mul	x11, x11, x13
0x2519f3e38:	str	x11, [sp, #0x90]
0x2519f3e3c:	mov	w11, #0xab90
0x2519f3e40:	movk	w11, #0x18e0, lsl #16
0x2519f3e44:	ldr	w14, [sp, #0xe8]
0x2519f3e48:	eor	w11, w14, w11
0x2519f3e4c:	str	w11, [sp, #0x7c]
0x2519f3e50:	mov	x11, #0x6510
0x2519f3e54:	movk	x11, #0xde16, lsl #16
0x2519f3e58:	movk	x11, #0x48f5, lsl #32
0x2519f3e5c:	movk	x11, #0x27ad, lsl #48
0x2519f3e60:	and	x11, x15, x11
0x2519f3e64:	lsl	x11, x11, #1
0x2519f3e68:	sub	x11, x11, x15
0x2519f3e6c:	mov	x12, #0x9ae8
0x2519f3e70:	movk	x12, #0x21e9, lsl #16
0x2519f3e74:	movk	x12, #0xb70a, lsl #32
0x2519f3e78:	movk	x12, #0x5852, lsl #48
0x2519f3e7c:	add	x11, x11, x12
0x2519f3e80:	mov	x12, #0x5f81
0x2519f3e84:	movk	x12, #0x1cc1, lsl #16
0x2519f3e88:	movk	x12, #0x25f5, lsl #32
0x2519f3e8c:	movk	x12, #0x4221, lsl #48
0x2519f3e90:	eor	x11, x11, x12
0x2519f3e94:	mul	x12, x11, x13
0x2519f3e98:	mov	w11, #0x13ff
0x2519f3e9c:	add	x11, x12, x11
0x2519f3ea0:	stp	x11, x12, [sp, #0x20]
0x2519f3ea4:	mov	w11, #0x3e4
0x2519f3ea8:	eor	w11, w14, w11
0x2519f3eac:	str	w11, [sp, #0xc]
0x2519f3eb0:	mov	w11, #0x101a
0x2519f3eb4:	add	w11, w14, w11
0x2519f3eb8:	str	w11, [sp, #8]
0x2519f3ebc:	mov	w19, #0x160
0x2519f3ec0:	mov	w20, #0xbdcd
0x2519f3ec4:	movk	w20, #0xaaca, lsl #16
0x2519f3ec8:	mov	w28, #0x40ef
0x2519f3ecc:	movk	w28, #0x5535, lsl #16
0x2519f3ed0:	mov	w30, #0x8f04
0x2519f3ed4:	movk	w30, #0x650a, lsl #16
0x2519f3ed8:	add	w11, w10, w4
0x2519f3edc:	and	w12, w11, w5
0x2519f3ee0:	add	w11, w10, #0x143
0x2519f3ee4:	add	w13, w11, w12
0x2519f3ee8:	sub	w13, w13, #0x5b6
0x2519f3eec:	cmp	w9, w13
0x2519f3ef0:	cset	w13, eq
0x2519f3ef4:	mul	w13, w13, w6
0x2519f3ef8:	eor	w10, w13, w10
0x2519f3efc:	ldr	x10, [x27, w10, sxtw #3]
0x2519f3f00:	ldr	w13, [x26]
0x2519f3f04:	ldr	w14, [x23]
0x2519f3f08:	eor	w15, w13, w21
0x2519f3f0c:	eor	w15, w15, w14
0x2519f3f10:	mul	w15, w15, w25
0x2519f3f14:	ldr	x16, [x22, #0x128]
0x2519f3f18:	sub	x24, x16, #8
0x2519f3f1c:	add	x16, x24, w15, uxtb
0x2519f3f20:	ldrb	w16, [x16]
0x2519f3f24:	eor	w16, w16, #0x18
0x2519f3f28:	ldr	x17, [x22, #0x638]
0x2519f3f2c:	sub	x17, x17, #4
0x2519f3f30:	ldrb	w16, [x17, w16, uxtw]
0x2519f3f34:	eor	w15, w16, w15
0x2519f3f38:	and	w15, w15, #0xff
0x2519f3f3c:	sub	w15, w15, #0x2f
0x2519f3f40:	ldr	x15, [x22, w15, sxtw #3]
0x2519f3f44:	str	x15, [sp, #0x88]
0x2519f3f48:	mov	x15, x24
0x2519f3f4c:	mov	x24, x17
0x2519f3f50:	add	w13, w14, w13
0x2519f3f54:	eor	w13, w13, w21
0x2519f3f58:	mul	w13, w13, w25
0x2519f3f5c:	add	x14, x15, w13, uxtb
0x2519f3f60:	ldrb	w14, [x14]
0x2519f3f64:	eor	w14, w14, w7
0x2519f3f68:	ldrb	w14, [x17, w14, uxtw]
0x2519f3f6c:	eor	w13, w13, w14
0x2519f3f70:	and	w13, w13, #0xff
0x2519f3f74:	add	w13, w13, #0x6c
0x2519f3f78:	ldr	x13, [x22, w13, uxtw #3]
0x2519f3f7c:	str	x13, [sp, #0x80]
0x2519f3f80:	mov	x17, #0xb341
0x2519f3f84:	braa	x10, x17
0x2519f3f88:	sub	w9, w12, #0x27
0x2519f3f8c:	sub	x8, x29, #0x70
0x2519f3f90:	add	x8, x8, x11
0x2519f3f94:	ldrb	w8, [x8]
0x2519f3f98:	add	w17, w7, #0x187
0x2519f3f9c:	eor	w17, w9, w17
0x2519f3fa0:	mul	w8, w8, w17
0x2519f3fa4:	eor	w17, w8, w6
0x2519f3fa8:	add	w17, w17, w11
0x2519f3fac:	sub	w17, w17, w17, lsr #16
0x2519f3fb0:	add	w17, w17, w17, lsr #8
0x2519f3fb4:	eor	w14, w17, w14
0x2519f3fb8:	add	w0, w17, w16
0x2519f3fbc:	eor	w13, w0, w13
0x2519f3fc0:	add	w17, w17, w4
0x2519f3fc4:	eor	w0, w17, w2
0x2519f3fc8:	eor	w8, w17, w8
0x2519f3fcc:	add	w8, w8, w11
0x2519f3fd0:	sub	w8, w8, w8, lsr #16
0x2519f3fd4:	add	w8, w8, w8, lsr #8
0x2519f3fd8:	eor	w14, w14, w8
0x2519f3fdc:	add	w17, w8, w16
0x2519f3fe0:	eor	w13, w13, w17
0x2519f3fe4:	add	x11, x11, #1
0x2519f3fe8:	add	w6, w8, w4
0x2519f3fec:	eor	w2, w0, w6
0x2519f3ff0:	cmp	x11, #0x10
0x2519f3ff4:	cset	w17, eq
0x2519f3ff8:	mov	w0, #0x1d9
0x2519f3ffc:	mul	w17, w17, w0
0x2519f4000:	eor	w17, w17, w12
0x2519f4004:	ldr	x0, [x22, w17, sxtw #3]
0x2519f4008:	mov	x17, #0xa0d1
0x2519f400c:	braa	x0, x17
0x2519f4010:	add	w8, w27, #0x632
0x2519f4014:	mov	x9, #0x527b
0x2519f4018:	movk	x9, #0xf055, lsl #16
0x2519f401c:	movk	x9, #0xda9a, lsl #32
0x2519f4020:	movk	x9, #0x14e2, lsl #48
0x2519f4024:	add	x20, x0, x9
0x2519f4028:	str	wzr, [x0]
0x2519f402c:	str	xzr, [x0, #8]
0x2519f4030:	str	wzr, [x0, #0x10]
0x2519f4034:	str	xzr, [x0, #0x20]
0x2519f4038:	str	xzr, [x0, #0x18]!
0x2519f403c:	eor	w23, w28, w8
0x2519f4040:	add	x8, sp, #0x18
0x2519f4044:	mov	w9, #0xdd64
0x2519f4048:	movk	w9, #0xc416, lsl #16
0x2519f404c:	orr	w9, w8, w9
0x2519f4050:	eor	w9, w9, #0xfffffffe
0x2519f4054:	mov	w10, #0x229b
0x2519f4058:	movk	w10, #0x3be9, lsl #16
0x2519f405c:	orn	w8, w10, w8
0x2519f4060:	sub	w8, w9, w8
0x2519f4064:	mov	w9, #0xfc89
0x2519f4068:	movk	w9, #0xb8d5, lsl #16
0x2519f406c:	eor	w8, w8, w9
0x2519f4070:	mov	w9, #0xfdbf
0x2519f4074:	movk	w9, #0x192a, lsl #16
0x2519f4078:	msub	w8, w8, w9, w28
0x2519f407c:	sub	w8, w8, #0x2a8
0x2519f4080:	str	w8, [sp, #0x28]
0x2519f4084:	str	x0, [sp, #0x30]
0x2519f4088:	str	x19, [sp, #0x20]
0x2519f408c:	ldr	w8, [x24]
0x2519f4090:	ldr	w9, [x25]
0x2519f4094:	sub	w8, w9, w8
0x2519f4098:	eor	w8, w8, w22
0x2519f409c:	mul	w8, w8, w21
0x2519f40a0:	adrp	x9, #0x27612b000
0x2519f40a4:	add	x9, x9, #0xd08
0x2519f40a8:	ldr	x10, [x9]
0x2519f40ac:	add	x10, x10, w8, uxtb
0x2519f40b0:	ldurb	w10, [x10, #-8]
0x2519f40b4:	mov	w11, #0xc4
0x2519f40b8:	eor	w10, w10, w11
0x2519f40bc:	ldr	x9, [x9, #0xe0]
0x2519f40c0:	add	x9, x9, x10
0x2519f40c4:	ldurb	w9, [x9, #-8]
0x2519f40c8:	eor	w8, w9, w8
0x2519f40cc:	and	w8, w8, #0xff
0x2519f40d0:	add	w8, w8, #0x421
0x2519f40d4:	ldr	x8, [x26, w8, uxtw #3]
0x2519f40d8:	add	x0, sp, #0x18
0x2519f40dc:	mov	x17, #0x56ad
0x2519f40e0:	blraa	x8, x17
0x2519f40e4:	ldr	w8, [sp, #0x18]
0x2519f40e8:	mov	x9, #0x3635
0x2519f40ec:	movk	x9, #0xdc36, lsl #16
0x2519f40f0:	movk	x9, #0xda9a, lsl #32
0x2519f40f4:	movk	x9, #0x14e2, lsl #48
0x2519f40f8:	add	x9, x23, x9
0x2519f40fc:	eor	x9, x9, x20
0x2519f4100:	mov	w10, #0x14f8
0x2519f4104:	movk	w10, #0x1455, lsl #16
0x2519f4108:	cmp	w8, w10
0x2519f410c:	csel	x9, x9, xzr, eq
0x2519f4110:	ldr	x10, [sp, #8]
0x2519f4114:	str	x9, [x10]
0x2519f4118:	ldr	x9, [sp, #0x38]
0x2519f411c:	adrp	x10, #0x2681b4000
0x2519f4120:	ldr	x10, [x10, #0xee0]
0x2519f4124:	ldr	x10, [x10]
0x2519f4128:	cmp	x10, x9
0x2519f412c:	b.ne	#0x2519f415c
0x2519f4130:	mov	w9, #0xeb08
0x2519f4134:	movk	w9, #0xebaa, lsl #16
0x2519f4138:	add	w0, w8, w9
0x2519f413c:	ldp	x29, x30, [sp, #0x90]
0x2519f4140:	ldp	x20, x19, [sp, #0x80]
0x2519f4144:	ldp	x22, x21, [sp, #0x70]
0x2519f4148:	ldp	x24, x23, [sp, #0x60]
0x2519f414c:	ldp	x26, x25, [sp, #0x50]
0x2519f4150:	ldp	x28, x27, [sp, #0x40]
0x2519f4154:	add	sp, sp, #0xa0
0x2519f4158:	retab	
0x2519f415c:	bl	#0x2580f4380
0x2519f4160:	ldr	x9, [x25]
0x2519f4164:	eor	w12, w12, w10
0x2519f4168:	add	w8, w11, #0x151
0x2519f416c:	add	w10, w11, #0x1d
0x2519f4170:	mov	x11, #-0x26b
0x2519f4174:	eor	x13, x8, x11
0x2519f4178:	adds	x12, x13, x12
0x2519f417c:	ldrb	w13, [x16, x12]
0x2519f4180:	strb	w13, [x9, x12]
0x2519f4184:	cset	w14, eq
0x2519f4188:	mov	w13, #0x207
0x2519f418c:	mul	w14, w14, w13
0x2519f4190:	eor	w14, w14, w10
0x2519f4194:	ldr	x14, [x20, w14, sxtw #3]
0x2519f4198:	mov	x17, #0x3e6a
0x2519f419c:	braa	x14, x17
0x2519f41a0:	mov	w26, #0x14f8
0x2519f41a4:	movk	w26, #0x1455, lsl #16
0x2519f41a8:	sub	w28, w27, #0x29
0x2519f41ac:	ldrb	w8, [x25, #7]
0x2519f41b0:	add	w10, w27, #0xb
0x2519f41b4:	mov	w11, #0xaf
0x2519f41b8:	and	w10, w10, w11
0x2519f41bc:	eor	w10, w8, w10
0x2519f41c0:	eor	w10, w10, #3
0x2519f41c4:	mov	w11, #0x5e
0x2519f41c8:	and	w8, w11, w8, lsl #1
0x2519f41cc:	mov	x11, #0x6b18
0x2519f41d0:	movk	x11, #0x9666, lsl #16
0x2519f41d4:	movk	x11, #0x92a6, lsl #32
0x2519f41d8:	movk	x11, #0xcfa9, lsl #48
0x2519f41dc:	add	x12, sp, #0xc
0x2519f41e0:	and	w13, w12, w11
0x2519f41e4:	sub	w12, w12, w13, lsl #1
0x2519f41e8:	add	w11, w12, w11
0x2519f41ec:	mov	w12, #0xae01
0x2519f41f0:	movk	w12, #0xed5, lsl #16
0x2519f41f4:	eor	w11, w11, w12
0x2519f41f8:	mul	w9, w11, w9
0x2519f41fc:	add	w11, w9, w27
0x2519f4200:	sub	w11, w11, #0x64
0x2519f4204:	str	w11, [sp, #0x10]
0x2519f4208:	add	w8, w9, w8
0x2519f420c:	add	w8, w8, w28
0x2519f4210:	add	w8, w8, w10
0x2519f4214:	sub	w8, w8, #0x72
0x2519f4218:	strb	w8, [sp, #0xc]
0x2519f421c:	ldr	w8, [x22]
0x2519f4220:	ldr	w9, [x23]
0x2519f4224:	sub	w8, w9, w8
0x2519f4228:	eor	w8, w8, w20
0x2519f422c:	mul	w8, w8, w21
0x2519f4230:	adrp	x9, #0x27612b000
0x2519f4234:	add	x9, x9, #0xa18
0x2519f4238:	ldr	x10, [x9]
0x2519f423c:	add	x10, x10, w8, uxtb
0x2519f4240:	ldurb	w10, [x10, #-8]
0x2519f4244:	mov	w11, #0x7d
0x2519f4248:	eor	w10, w10, w11
0x2519f424c:	ldr	x9, [x9, #0x510]
0x2519f4250:	add	x9, x9, x10
0x2519f4254:	ldurb	w9, [x9, #-4]
0x2519f4258:	eor	w8, w9, w8
0x2519f425c:	and	w8, w8, #0xff
0x2519f4260:	add	w8, w8, #0x449
0x2519f4264:	ldr	x8, [x24, w8, uxtw #3]
0x2519f4268:	add	x0, sp, #0xc
0x2519f426c:	mov	x17, #0x49ac
0x2519f4270:	blraa	x8, x17
0x2519f4274:	ldr	w8, [sp, #0x14]
0x2519f4278:	cmp	w8, w26
0x2519f427c:	cset	w9, eq
0x2519f4280:	lsl	w10, w9, #0xa
0x2519f4284:	sub	w9, w10, w9, lsl #5
0x2519f4288:	eor	w9, w9, w27
0x2519f428c:	ldr	x9, [x24, w9, sxtw #3]
0x2519f4290:	mov	x17, #0xf255
0x2519f4294:	braa	x9, x17
0x2519f4298:	add	x8, sp, #0x1c0
0x2519f429c:	add	x9, x9, x10
0x2519f42a0:	add	x9, x9, x19
0x2519f42a4:	mov	w10, #0xba
0x2519f42a8:	mov	w11, #0x7a6
0x2519f42ac:	ldr	x15, [sp, #0x198]
0x2519f42b0:	mov	w16, #0x1a16
0x2519f42b4:	movk	w16, #0x4769, lsl #16
0x2519f42b8:	ldr	w0, [sp, #0x180]
0x2519f42bc:	add	w12, w16, w0
0x2519f42c0:	add	w12, w12, #0x381
0x2519f42c4:	add	w13, w8, #0x11
0x2519f42c8:	eor	w14, w8, w10
0x2519f42cc:	mul	w13, w14, w13
0x2519f42d0:	add	x14, x15, x9
0x2519f42d4:	strb	w13, [x14]
0x2519f42d8:	cmp	x9, #0
0x2519f42dc:	cset	w13, eq
0x2519f42e0:	mul	w13, w13, w11
0x2519f42e4:	eor	w12, w13, w12
0x2519f42e8:	ldr	x12, [x28, w12, sxtw #3]
0x2519f42ec:	mov	x17, #0xbe83
0x2519f42f0:	braa	x12, x17
0x2519f42f4:	add	w12, w10, #0x172
0x2519f42f8:	sub	x9, x29, #0x70
0x2519f42fc:	add	x9, x9, x8
0x2519f4300:	ldrb	w9, [x9]
0x2519f4304:	mul	w9, w9, w21
0x2519f4308:	eor	w11, w9, w0
0x2519f430c:	add	w11, w11, w8
0x2519f4310:	mov	w16, #0x209
0x2519f4314:	eor	w16, w12, w16
0x2519f4318:	lsr	w16, w11, w16
0x2519f431c:	add	w11, w16, w11
0x2519f4320:	add	w11, w11, w11, lsr #8
0x2519f4324:	eor	w14, w11, w14
0x2519f4328:	add	w16, w11, w4
0x2519f432c:	eor	w13, w16, w13
0x2519f4330:	add	w11, w11, w3
0x2519f4334:	eor	w17, w11, w1
0x2519f4338:	eor	w9, w11, w9
0x2519f433c:	add	w9, w9, w8
0x2519f4340:	add	w9, w9, w9, lsr #16
0x2519f4344:	add	w16, w9, w9, lsr #8
0x2519f4348:	eor	w14, w14, w16
0x2519f434c:	add	x8, x8, #1
0x2519f4350:	add	w9, w16, w4
0x2519f4354:	eor	w13, w13, w9
0x2519f4358:	add	w0, w16, w3
0x2519f435c:	eor	w1, w17, w0
0x2519f4360:	cmp	x8, #0x10
0x2519f4364:	cset	w9, eq
0x2519f4368:	mov	w11, #0x142
0x2519f436c:	mul	w9, w9, w11
0x2519f4370:	eor	w9, w9, w10
0x2519f4374:	ldr	x9, [x20, w9, sxtw #3]
0x2519f4378:	mov	x17, #0x3519
0x2519f437c:	braa	x9, x17
0x2519f4380:	mov	x26, #0xb4fa
0x2519f4384:	movk	x26, #0x6d3c, lsl #16
0x2519f4388:	movk	x26, #0x2a54, lsl #32
0x2519f438c:	movk	x26, #0x375b, lsl #48
0x2519f4390:	b	#0x251a2c1c8
0x2519f4394:	mov	w9, #0x1eeb
0x2519f4398:	movk	w9, #0x225b, lsl #16
0x2519f439c:	ldr	w10, [sp, #0x248]
0x2519f43a0:	add	w9, w10, w9
0x2519f43a4:	mov	w10, #0xdfef
0x2519f43a8:	movk	w10, #0xdda4, lsl #16
0x2519f43ac:	and	w10, w9, w10
0x2519f43b0:	mov	w9, #0x57f0
0x2519f43b4:	movk	w9, #0xc461, lsl #16
0x2519f43b8:	add	w9, w10, w9
0x2519f43bc:	eor	w30, w9, w8
0x2519f43c0:	mov	w8, #0x4135
0x2519f43c4:	movk	w8, #0x59ea, lsl #16
0x2519f43c8:	eor	w23, w11, w8
0x2519f43cc:	mov	w8, #0x165e
0x2519f43d0:	movk	w8, #0x74ed, lsl #16
0x2519f43d4:	ldr	w9, [sp, #0x238]
0x2519f43d8:	eor	w8, w9, w8
0x2519f43dc:	str	w8, [sp, #0x2c8]
0x2519f43e0:	mov	w8, #0xafcd
0x2519f43e4:	movk	w8, #0xa183, lsl #16
0x2519f43e8:	ldr	w9, [sp, #0x23c]
0x2519f43ec:	eor	w8, w9, w8
0x2519f43f0:	str	w8, [sp, #0x2c4]
0x2519f43f4:	mov	w8, #0x3081
0x2519f43f8:	movk	w8, #0xeec2, lsl #16
0x2519f43fc:	ldr	w9, [sp, #0x240]
0x2519f4400:	eor	w8, w9, w8
0x2519f4404:	stur	w8, [x29, #-0x100]
0x2519f4408:	b	#0x2519f8800
0x2519f440c:	mov	w9, #0xd21b
0x2519f4410:	movk	w9, #0xe2f9, lsl #16
0x2519f4414:	mov	w10, #0x97f7
0x2519f4418:	movk	w10, #0xb9f0, lsl #16
0x2519f441c:	mov	w11, #0x9f29
0x2519f4420:	movk	w11, #0x6c83, lsl #16
0x2519f4424:	mov	w12, #0xb53e
0x2519f4428:	movk	w12, #0xdc14, lsl #16
0x2519f442c:	mov	w13, #0x2d71
0x2519f4430:	movk	w13, #0xdb07, lsl #16
0x2519f4434:	mov	w14, #0x22b5
0x2519f4438:	movk	w14, #0xa77d, lsl #16
0x2519f443c:	mov	w15, #0x5fba
0x2519f4440:	movk	w15, #0x5dbb, lsl #16
0x2519f4444:	sub	w8, w8, #0x309
0x2519f4448:	mov	w16, #0x64
0x2519f444c:	orr	w8, w8, w16
0x2519f4450:	ldr	x16, [sp, #0x80]
0x2519f4454:	add	x17, x16, #0x18
0x2519f4458:	stp	x17, xzr, [sp, #0x48]
0x2519f445c:	add	x19, x16, #0x18
0x2519f4460:	mov	w20, #0x75
0x2519f4464:	sub	x16, x29, #0x80
0x2519f4468:	mov	w17, #0xdab0
0x2519f446c:	movk	w17, #0x27a0, lsl #16
0x2519f4470:	and	w17, w16, w17
0x2519f4474:	lsl	w17, w17, #1
0x2519f4478:	sub	w17, w17, w16
0x2519f447c:	mov	w0, #0x254c
0x2519f4480:	movk	w0, #0xd85f, lsl #16
0x2519f4484:	add	w17, w17, w0
0x2519f4488:	mov	w0, #0x1090
0x2519f448c:	movk	w0, #0xd4bb, lsl #16
0x2519f4490:	eor	w17, w17, w0
0x2519f4494:	mul	w17, w17, w10
0x2519f4498:	adrp	x10, #0x27612b000
0x2519f449c:	add	x10, x10, #0xa70
0x2519f44a0:	sub	w15, w15, w17
0x2519f44a4:	stp	w15, w17, [sp, #0x40]
0x2519f44a8:	ldr	x15, [x10]
0x2519f44ac:	str	x15, [sp, #0x38]
0x2519f44b0:	ldr	x15, [x10, #0xb0]
0x2519f44b4:	str	x15, [sp, #0x30]
0x2519f44b8:	mov	w15, #0xc569
0x2519f44bc:	movk	w15, #0x3d28, lsl #16
0x2519f44c0:	eor	w15, w16, w15
0x2519f44c4:	msub	w11, w15, w11, w13
0x2519f44c8:	str	w11, [sp, #0x2c]
0x2519f44cc:	ldr	x11, [x10, #0x440]
0x2519f44d0:	ldr	x10, [x10, #0x288]
0x2519f44d4:	stp	x10, x11, [sp, #0x18]
0x2519f44d8:	mov	w10, #0x3308
0x2519f44dc:	movk	w10, #0x6763, lsl #16
0x2519f44e0:	and	w10, w16, w10
0x2519f44e4:	lsl	w10, w10, #1
0x2519f44e8:	sub	w10, w10, w16
0x2519f44ec:	mov	w11, #0xccf2
0x2519f44f0:	movk	w11, #0x989c, lsl #16
0x2519f44f4:	add	w10, w10, w11
0x2519f44f8:	mov	w11, #0x5a9e
0x2519f44fc:	movk	w11, #0x61c2, lsl #16
0x2519f4500:	eor	w10, w10, w11
0x2519f4504:	mul	w9, w10, w9
0x2519f4508:	sub	w10, w14, w9
0x2519f450c:	stp	w10, w9, [sp, #0x10]
0x2519f4510:	eor	w9, w9, w12
0x2519f4514:	str	w9, [sp, #0xc]
0x2519f4518:	str	w21, [sp, #0x94]
0x2519f451c:	ldp	x28, x27, [sp, #0x78]
0x2519f4520:	add	w24, w8, #0x26f
0x2519f4524:	ldr	x11, [sp, #0x50]
0x2519f4528:	add	x9, x26, x11
0x2519f452c:	ldrb	w9, [x9]
0x2519f4530:	add	x10, x19, x11
0x2519f4534:	eor	w9, w9, w20
0x2519f4538:	strb	w9, [x10]
0x2519f453c:	add	x10, x11, #1
0x2519f4540:	cmp	x11, #0x3f
0x2519f4544:	cset	w11, eq
0x2519f4548:	mov	w9, #0x2f5
0x2519f454c:	eor	w9, w24, w9
0x2519f4550:	mul	w11, w11, w9
0x2519f4554:	eor	w11, w11, w8
0x2519f4558:	ldr	x11, [x25, w11, sxtw #3]
0x2519f455c:	mov	x17, #0x91df
0x2519f4560:	braa	x11, x17

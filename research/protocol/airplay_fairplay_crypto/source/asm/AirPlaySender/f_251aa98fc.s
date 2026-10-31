; AirPlaySender 0x251aa98fc-0x251aa9a60; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251aa98fc:	pacibsp	
0x251aa9900:	stp	x28, x27, [sp, #-0x60]!
0x251aa9904:	stp	x26, x25, [sp, #0x10]
0x251aa9908:	stp	x24, x23, [sp, #0x20]
0x251aa990c:	stp	x22, x21, [sp, #0x30]
0x251aa9910:	stp	x20, x19, [sp, #0x40]
0x251aa9914:	stp	x29, x30, [sp, #0x50]
0x251aa9918:	add	x29, sp, #0x50
0x251aa991c:	mov	x20, x6
0x251aa9920:	mov	x21, x5
0x251aa9924:	mov	x22, x4
0x251aa9928:	mov	x23, x3
0x251aa992c:	mov	x24, x2
0x251aa9930:	mov	x25, x1
0x251aa9934:	bl	#0x25810ac50
0x251aa9938:	mov	x26, x0
0x251aa993c:	ldr	x0, [x0, #0x30]
0x251aa9940:	mov	x1, x21
0x251aa9944:	bl	#0x25810e760
0x251aa9948:	cbz	x0, #0x251aa9a34
0x251aa994c:	mov	x19, x0
0x251aa9950:	mov	x1, x21
0x251aa9954:	bl	#0x25810e790
0x251aa9958:	ldr	x26, [x26]
0x251aa995c:	cbz	x26, #0x251aa9a48
0x251aa9960:	mov	x0, x19
0x251aa9964:	bl	#0x25810e780
0x251aa9968:	mov	x27, x0
0x251aa996c:	mov	x0, x26
0x251aa9970:	bl	#0x258109150
0x251aa9974:	ldr	x16, [x0, #0x10]!
0x251aa9978:	mov	x17, x0
0x251aa997c:	movk	x17, #0xf7db, lsl #48
0x251aa9980:	autda	x16, x17
0x251aa9984:	ldr	x9, [x16, #8]!
0x251aa9988:	cbz	x9, #0x251aa99f0
0x251aa998c:	mov	x8, x16
0x251aa9990:	movk	x8, #0x2d6f, lsl #48
0x251aa9994:	mov	x16, x9
0x251aa9998:	mov	x17, x8
0x251aa999c:	autia	x16, x17
0x251aa99a0:	mov	x17, x16
0x251aa99a4:	xpaci	x17
0x251aa99a8:	cmp	x16, x17
0x251aa99ac:	b.eq	#0x251aa99b4
0x251aa99b0:	brk	#0xc470
0x251aa99b4:	paciza	x16
0x251aa99b8:	cbz	x16, #0x251aa99f0
0x251aa99bc:	mov	x0, x26
0x251aa99c0:	mov	x1, x25
0x251aa99c4:	mov	x2, x24
0x251aa99c8:	mov	x3, x23
0x251aa99cc:	mov	x4, x22
0x251aa99d0:	mov	x5, x21
0x251aa99d4:	mov	x6, x27
0x251aa99d8:	blraa	x9, x8
0x251aa99dc:	cbnz	w0, #0x251aa9a58
0x251aa99e0:	mov	w21, #0
0x251aa99e4:	cbz	x20, #0x251aa9a0c
0x251aa99e8:	str	x19, [x20]
0x251aa99ec:	b	#0x251aa9a14
0x251aa99f0:	mov	w21, #-0x31ee
0x251aa99f4:	adrp	x1, #0x251c18000
0x251aa99f8:	add	x1, x1, #0xcb6
0x251aa99fc:	mov	x0, x21
0x251aa9a00:	mov	w2, #0x167
0x251aa9a04:	mov	w3, #0
0x251aa9a08:	bl	#0x258109a30
0x251aa9a0c:	mov	x0, x19
0x251aa9a10:	bl	#0x2580f5830
0x251aa9a14:	mov	x0, x21
0x251aa9a18:	ldp	x29, x30, [sp, #0x50]
0x251aa9a1c:	ldp	x20, x19, [sp, #0x40]
0x251aa9a20:	ldp	x22, x21, [sp, #0x30]
0x251aa9a24:	ldp	x24, x23, [sp, #0x20]
0x251aa9a28:	ldp	x26, x25, [sp, #0x10]
0x251aa9a2c:	ldp	x28, x27, [sp], #0x60
0x251aa9a30:	retab	
0x251aa9a34:	bl	#0x251b8457c
0x251aa9a38:	mov	w8, #0xe7d7
0x251aa9a3c:	movk	w8, #0xfffe, lsl #16
0x251aa9a40:	add	w21, w8, #1
0x251aa9a44:	b	#0x251aa9a14
0x251aa9a48:	mov	w21, #0xe7d7
0x251aa9a4c:	movk	w21, #0xfffe, lsl #16
0x251aa9a50:	bl	#0x251b84568
0x251aa9a54:	b	#0x251aa9a0c
0x251aa9a58:	mov	x21, x0
0x251aa9a5c:	b	#0x251aa99f4

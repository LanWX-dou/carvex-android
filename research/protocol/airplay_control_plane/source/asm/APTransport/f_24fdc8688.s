; APTransport 0x24fdc8688-0x24fdc8738; source SHA256 e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x24fdc8688:	pacibsp	
0x24fdc868c:	sub	sp, sp, #0x50
0x24fdc8690:	stp	x22, x21, [sp, #0x20]
0x24fdc8694:	stp	x20, x19, [sp, #0x30]
0x24fdc8698:	stp	x29, x30, [sp, #0x40]
0x24fdc869c:	add	x29, sp, #0x40
0x24fdc86a0:	mov	x19, x2
0x24fdc86a4:	mov	x21, x1
0x24fdc86a8:	mov	x22, x0
0x24fdc86ac:	bl	#0x2500e5a60
0x24fdc86b0:	stp	x22, x21, [sp, #8]
0x24fdc86b4:	str	x19, [sp, #0x18]
0x24fdc86b8:	cbz	x21, #0x24fdc8718
0x24fdc86bc:	cbz	x19, #0x24fdc8728
0x24fdc86c0:	mov	x20, x0
0x24fdc86c4:	mov	x0, x22
0x24fdc86c8:	bl	#0x2500903e0
0x24fdc86cc:	mov	x0, x21
0x24fdc86d0:	bl	#0x2500903e0
0x24fdc86d4:	mov	x0, x19
0x24fdc86d8:	bl	#0x2500903e0
0x24fdc86dc:	ldr	x0, [x20, #8]
0x24fdc86e0:	adrp	x16, #0x24fdca000
0x24fdc86e4:	add	x16, x16, #0x290
0x24fdc86e8:	paciza	x16
0x24fdc86ec:	mov	x1, x16
0x24fdc86f0:	add	x2, sp, #8
0x24fdc86f4:	mov	w3, #0x18
0x24fdc86f8:	bl	#0x2500edec0
0x24fdc86fc:	mov	w19, #0
0x24fdc8700:	mov	x0, x19
0x24fdc8704:	ldp	x29, x30, [sp, #0x40]
0x24fdc8708:	ldp	x20, x19, [sp, #0x30]
0x24fdc870c:	ldp	x22, x21, [sp, #0x20]
0x24fdc8710:	add	sp, sp, #0x50
0x24fdc8714:	retab	
0x24fdc8718:	mov	w19, #0xe57e
0x24fdc871c:	movk	w19, #0xfffe, lsl #16
0x24fdc8720:	bl	#0x24fe17de8
0x24fdc8724:	b	#0x24fdc8700
0x24fdc8728:	mov	w19, #0xe57e
0x24fdc872c:	movk	w19, #0xfffe, lsl #16
0x24fdc8730:	bl	#0x24fe17dd4
0x24fdc8734:	b	#0x24fdc8700

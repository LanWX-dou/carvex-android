; accessoryd 0x10017b680-0x10017b6a8; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10017b680:	cbz	x0, #0x10017b69c
0x10017b684:	str	wzr, [x0]
0x10017b688:	strh	wzr, [x0, #4]
0x10017b68c:	strb	wzr, [x0, #6]
0x10017b690:	str	xzr, [x0, #8]
0x10017b694:	strh	wzr, [x0, #0x10]
0x10017b698:	strb	wzr, [x0, #0x12]
0x10017b69c:	cmp	x0, #0
0x10017b6a0:	cset	w0, ne
0x10017b6a4:	ret	

; accessoryd 0x10003f740-0x10003f768; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10003f740:	sub	w8, w0, #1
0x10003f744:	cmp	w8, #7
0x10003f748:	b.hi	#0x10003f75c
0x10003f74c:	adrp	x9, #0x100219000
0x10003f750:	add	x9, x9, #0xfc8
0x10003f754:	ldr	x0, [x9, w8, uxtw #3]
0x10003f758:	ret	
0x10003f75c:	adrp	x0, #0x1001cd000
0x10003f760:	add	x0, x0, #0x604
0x10003f764:	ret	

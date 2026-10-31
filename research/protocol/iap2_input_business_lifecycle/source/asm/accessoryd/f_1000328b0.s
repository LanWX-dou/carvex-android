; accessoryd 0x1000328b0-0x1000328dc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000328b0:	cbz	x0, #0x1000328d8
0x1000328b4:	mov	w8, #0x3e8ffff
0x1000328b8:	str	w8, [x0, #4]
0x1000328bc:	mov	w8, #0xa
0x1000328c0:	strh	w8, [x0, #8]
0x1000328c4:	adrp	x8, #0x1001b3000
0x1000328c8:	ldr	d0, [x8, #0x348]
0x1000328cc:	str	s0, [x0]
0x1000328d0:	mov	w8, #-0xff00
0x1000328d4:	stur	w8, [x0, #0xa]
0x1000328d8:	ret	

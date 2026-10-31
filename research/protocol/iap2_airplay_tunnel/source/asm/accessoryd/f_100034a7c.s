; accessoryd 0x100034a7c-0x100034abc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100034a7c:	cbz	x0, #0x100034ab8
0x100034a80:	add	x8, x0, #0x19a
0x100034a84:	add	x9, x0, #0x19e
0x100034a88:	mov	w10, #0x3e8ffff
0x100034a8c:	str	w10, [x9]
0x100034a90:	mov	w9, #0xa
0x100034a94:	strh	w9, [x0, #0x1a2]
0x100034a98:	adrp	x9, #0x1001b3000
0x100034a9c:	ldr	d0, [x9, #0x348]
0x100034aa0:	str	s0, [x8]
0x100034aa4:	mov	w8, #-0xff00
0x100034aa8:	str	w8, [x0, #0x1a4]
0x100034aac:	ldr	x0, [x0, #8]
0x100034ab0:	mov	w1, #1
0x100034ab4:	b	#0x10000639c
0x100034ab8:	ret	

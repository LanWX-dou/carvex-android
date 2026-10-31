; accessoryd 0x1000349e8-0x100034a28; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000349e8:	cbz	x0, #0x100034a24
0x1000349ec:	ldrh	w8, [x0, #0x1a6]
0x1000349f0:	ldrh	w9, [x0, #0xc0]
0x1000349f4:	cmp	w8, w9
0x1000349f8:	csel	w8, w8, w9, lo
0x1000349fc:	cbz	x1, #0x100034a0c
0x100034a00:	ldr	w9, [x1, #0x28]
0x100034a04:	cmp	w9, w8
0x100034a08:	csel	w8, w9, w8, lo
0x100034a0c:	ldrb	w9, [x0, #0xd5]
0x100034a10:	cmp	w9, #2
0x100034a14:	mov	w9, #-0xa
0x100034a18:	mov	w10, #-0xc
0x100034a1c:	csel	w9, w10, w9, eq
0x100034a20:	add	w0, w9, w8
0x100034a24:	ret	

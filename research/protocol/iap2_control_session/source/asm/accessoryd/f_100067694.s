; accessoryd 0x100067694-0x1000676c4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100067694:	cbz	x0, #0x1000676b8
0x100067698:	ldr	x8, [x0, #0x18]
0x10006769c:	cbz	x8, #0x1000676bc
0x1000676a0:	ldr	w9, [x0, #0x10]
0x1000676a4:	cmp	w9, #6
0x1000676a8:	b.lo	#0x1000676b8
0x1000676ac:	ldrh	w8, [x8]
0x1000676b0:	rev16	w8, w8
0x1000676b4:	b	#0x1000676bc
0x1000676b8:	mov	w8, #0
0x1000676bc:	and	w0, w8, #0xffff
0x1000676c0:	ret	

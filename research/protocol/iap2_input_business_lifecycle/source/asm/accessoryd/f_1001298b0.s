; accessoryd 0x1001298b0-0x1001298e0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1001298b0:	cbz	x0, #0x1001298dc
0x1001298b4:	ldrb	w8, [x0, #0x68]
0x1001298b8:	cmp	w8, #1
0x1001298bc:	b.ne	#0x1001298d8
0x1001298c0:	ldr	x8, [x0, #0x28]
0x1001298c4:	cbz	x8, #0x1001298d8
0x1001298c8:	ldr	x8, [x8, #0x18]
0x1001298cc:	cbz	x8, #0x1001298d8
0x1001298d0:	ldrb	w0, [x8, #0x16b]
0x1001298d4:	ret	
0x1001298d8:	mov	w0, #0
0x1001298dc:	ret	

; accessoryd 0x10012961c-0x100129634; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10012961c:	cbz	x0, #0x10012962c
0x100129620:	ldrb	w8, [x0, #0x1c0]
0x100129624:	and	w0, w8, #1
0x100129628:	ret	
0x10012962c:	mov	w8, #0
0x100129630:	b	#0x100129624

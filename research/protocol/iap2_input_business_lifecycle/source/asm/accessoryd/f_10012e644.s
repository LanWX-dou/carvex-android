; accessoryd 0x10012e644-0x10012e660; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10012e644:	mov	x8, x0
0x10012e648:	adrp	x9, #0x10023e000
0x10012e64c:	ldr	x0, [x9, #0x5c8]
0x10012e650:	cbz	x0, #0x10012e65c
0x10012e654:	mov	w1, w8
0x10012e658:	b	#0x1001a1690
0x10012e65c:	ret	

; accessoryd 0x1000caef4-0x1000caf0c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000caef4:	cbz	x0, #0x1000caf08
0x1000caef8:	mov	w8, #1
0x1000caefc:	strb	w8, [x0, #0x2c]
0x1000caf00:	ldr	x0, [x0, #0x18]
0x1000caf04:	b	#0x100034778
0x1000caf08:	ret	

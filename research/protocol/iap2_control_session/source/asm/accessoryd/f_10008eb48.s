; accessoryd 0x10008eb48-0x10008eb64; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10008eb48:	strh	wzr, [x1]
0x10008eb4c:	strh	w0, [x1, #2]
0x10008eb50:	add	x8, x1, #0x20
0x10008eb54:	stp	x8, x2, [x1, #8]
0x10008eb58:	strh	w3, [x1, #0x18]
0x10008eb5c:	mov	x0, x1
0x10008eb60:	ret	

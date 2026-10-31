; accessoryd 0x10013ed5c-0x10013ed74; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10013ed5c:	cbz	x0, #0x10013ed70
0x10013ed60:	mov	w8, #0x1d
0x10013ed64:	strb	w8, [x0]
0x10013ed68:	adrp	x0, #0x10021b000
0x10013ed6c:	add	x0, x0, #0x550
0x10013ed70:	ret	

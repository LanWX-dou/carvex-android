; accessoryd 0x10000ad88-0x10000ada0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10000ad88:	cbz	x0, #0x10000ad9c
0x10000ad8c:	ldurh	w8, [x0, #0x3d]
0x10000ad90:	and	w8, w8, #0xfe
0x10000ad94:	cmp	w8, #0x11
0x10000ad98:	cset	w0, hi
0x10000ad9c:	ret	

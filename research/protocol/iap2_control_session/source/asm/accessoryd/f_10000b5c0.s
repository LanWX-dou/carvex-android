; accessoryd 0x10000b5c0-0x10000b5d0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10000b5c0:	sub	w8, w1, w0
0x10000b5c4:	cmp	w2, w8, uxtb
0x10000b5c8:	cset	w0, hs
0x10000b5cc:	ret	

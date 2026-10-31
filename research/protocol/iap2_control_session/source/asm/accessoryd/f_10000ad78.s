; accessoryd 0x10000ad78-0x10000ad88; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10000ad78:	cmp	x0, #0
0x10000ad7c:	mov	w8, #0xffff
0x10000ad80:	csel	w0, wzr, w8, eq
0x10000ad84:	ret	

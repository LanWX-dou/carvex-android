; accessoryd 0x100005f4c-0x100005f60; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100005f4c:	ldrb	w8, [x0, #0xd5]
0x100005f50:	cmp	w8, #2
0x100005f54:	mov	w8, #9
0x100005f58:	cinc	w0, w8, eq
0x100005f5c:	ret	

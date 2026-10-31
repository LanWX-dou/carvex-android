; accessoryd 0x100004b44-0x100004b74; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100004b44:	cbz	x0, #0x100004b68
0x100004b48:	ldr	x8, [x0, #0x18]
0x100004b4c:	cbz	x8, #0x100004b6c
0x100004b50:	ldr	w9, [x0, #0x10]
0x100004b54:	cmp	w9, #6
0x100004b58:	b.lo	#0x100004b68
0x100004b5c:	ldrh	w8, [x8, #4]
0x100004b60:	rev16	w8, w8
0x100004b64:	b	#0x100004b6c
0x100004b68:	mov	w8, #0
0x100004b6c:	and	w0, w8, #0xffff
0x100004b70:	ret	

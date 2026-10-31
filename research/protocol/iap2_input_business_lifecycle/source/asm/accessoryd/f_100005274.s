; accessoryd 0x100005274-0x1000052a4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100005274:	cbz	x0, #0x100005298
0x100005278:	ldr	x8, [x0, #0x18]
0x10000527c:	cbz	x8, #0x10000529c
0x100005280:	ldr	w9, [x0, #0x10]
0x100005284:	cmp	w9, #6
0x100005288:	b.lo	#0x100005298
0x10000528c:	ldrh	w8, [x8, #2]
0x100005290:	rev16	w8, w8
0x100005294:	b	#0x10000529c
0x100005298:	mov	w8, #0
0x10000529c:	and	w0, w8, #0xffff
0x1000052a0:	ret	

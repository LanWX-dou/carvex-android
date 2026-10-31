; accessoryd 0x100129738-0x100129784; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100129738:	cbz	x0, #0x100129774
0x10012973c:	ldrb	w8, [x0, #0x68]
0x100129740:	cmp	w8, #1
0x100129744:	b.ne	#0x10012977c
0x100129748:	ldr	x8, [x0, #0x28]
0x10012974c:	cbz	x8, #0x10012977c
0x100129750:	ldr	x0, [x8, #0x18]
0x100129754:	cbz	x0, #0x100129774
0x100129758:	pacibsp	
0x10012975c:	stp	x29, x30, [sp, #-0x10]!
0x100129760:	mov	x29, sp
0x100129764:	mov	x1, #0
0x100129768:	bl	#0x1000349e8
0x10012976c:	ldp	x29, x30, [sp], #0x10
0x100129770:	autibsp	
0x100129774:	and	w0, w0, #0xffff
0x100129778:	ret	
0x10012977c:	mov	w0, #0
0x100129780:	b	#0x100129774

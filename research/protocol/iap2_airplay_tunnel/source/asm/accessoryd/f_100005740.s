; accessoryd 0x100005740-0x100005788; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100005740:	cbz	x0, #0x10000577c
0x100005744:	ldrb	w8, [x0, #0x1a4]
0x100005748:	cbz	x8, #0x10000577c
0x10000574c:	mov	x10, #0
0x100005750:	mov	w9, #0
0x100005754:	add	x11, x0, #0x1b8
0x100005758:	add	x12, x11, x10, lsl #2
0x10000575c:	ldrb	w13, [x12, #1]
0x100005760:	cmp	w1, w13
0x100005764:	b.ne	#0x10000576c
0x100005768:	ldrb	w9, [x12]
0x10000576c:	add	x10, x10, #1
0x100005770:	subs	x8, x8, #1
0x100005774:	b.ne	#0x100005758
0x100005778:	b	#0x100005780
0x10000577c:	mov	w9, #0
0x100005780:	and	w0, w9, #0xff
0x100005784:	ret	

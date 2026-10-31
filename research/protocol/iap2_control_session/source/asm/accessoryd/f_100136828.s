; accessoryd 0x100136828-0x1001368ac; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100136828:	pacibsp	
0x10013682c:	stp	x22, x21, [sp, #-0x30]!
0x100136830:	stp	x20, x19, [sp, #0x10]
0x100136834:	stp	x29, x30, [sp, #0x20]
0x100136838:	add	x29, sp, #0x20
0x10013683c:	cbz	x0, #0x100136898
0x100136840:	mov	x20, x1
0x100136844:	cbz	x1, #0x100136898
0x100136848:	mov	x19, x2
0x10013684c:	ldr	x21, [x0, #0x1c8]
0x100136850:	ldr	x8, [x21, #0x10]
0x100136854:	cbnz	x8, #0x10013686c
0x100136858:	mov	w0, #0xffff
0x10013685c:	mov	w1, #0x428a
0x100136860:	movk	w1, #0xd38c, lsl #16
0x100136864:	bl	#0x1001a2370
0x100136868:	str	x0, [x21, #0x10]
0x10013686c:	mov	x0, x20
0x100136870:	mov	x1, x19
0x100136874:	mov	x2, x21
0x100136878:	ldp	x29, x30, [sp, #0x20]
0x10013687c:	ldp	x20, x19, [sp, #0x10]
0x100136880:	ldp	x22, x21, [sp], #0x30
0x100136884:	autibsp	
0x100136888:	eor	x16, x30, x30, lsl #1
0x10013688c:	tbz	x16, #0x3e, #0x100136894
0x100136890:	brk	#0xc471
0x100136894:	b	#0x10004a580
0x100136898:	mov	w0, #0
0x10013689c:	ldp	x29, x30, [sp, #0x20]
0x1001368a0:	ldp	x20, x19, [sp, #0x10]
0x1001368a4:	ldp	x22, x21, [sp], #0x30
0x1001368a8:	retab	

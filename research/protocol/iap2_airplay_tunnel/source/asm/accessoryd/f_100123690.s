; accessoryd 0x100123690-0x1001236dc; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100123690:	pacibsp	
0x100123694:	stp	x20, x19, [sp, #-0x20]!
0x100123698:	stp	x29, x30, [sp, #0x10]
0x10012369c:	add	x29, sp, #0x10
0x1001236a0:	mov	x19, x0
0x1001236a4:	mov	w0, #0
0x1001236a8:	cbz	x19, #0x1001236d0
0x1001236ac:	cbz	x1, #0x1001236d0
0x1001236b0:	mov	x0, x19
0x1001236b4:	mov	w1, #7
0x1001236b8:	bl	#0x100003360
0x1001236bc:	cbz	x0, #0x1001236d0
0x1001236c0:	mov	x0, x19
0x1001236c4:	mov	w1, #2
0x1001236c8:	bl	#0x1001235c0
0x1001236cc:	mov	w0, #1
0x1001236d0:	ldp	x29, x30, [sp, #0x10]
0x1001236d4:	ldp	x20, x19, [sp], #0x20
0x1001236d8:	retab	

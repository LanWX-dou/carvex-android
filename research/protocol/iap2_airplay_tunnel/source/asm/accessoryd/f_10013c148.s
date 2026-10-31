; accessoryd 0x10013c148-0x10013c1a0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10013c148:	cbz	x0, #0x10013c198
0x10013c14c:	pacibsp	
0x10013c150:	stp	x29, x30, [sp, #-0x10]!
0x10013c154:	mov	x29, sp
0x10013c158:	mov	w1, #1
0x10013c15c:	bl	#0x100003360
0x10013c160:	cbz	x0, #0x10013c190
0x10013c164:	bl	#0x100001b04
0x10013c168:	b.ne	#0x10013c190
0x10013c16c:	ldr	x8, [x0, #8]
0x10013c170:	cbz	x8, #0x10013c180
0x10013c174:	ldr	x9, [x8, #0x70]
0x10013c178:	cbz	x9, #0x10013c190
0x10013c17c:	ldrb	w8, [x8, #0x80]
0x10013c180:	ldp	x29, x30, [sp], #0x10
0x10013c184:	autibsp	
0x10013c188:	and	w0, w8, #1
0x10013c18c:	ret	
0x10013c190:	mov	w8, #0
0x10013c194:	b	#0x10013c180
0x10013c198:	mov	w8, #0
0x10013c19c:	b	#0x10013c188

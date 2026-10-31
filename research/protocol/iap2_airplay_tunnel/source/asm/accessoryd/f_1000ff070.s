; accessoryd 0x1000ff070-0x1000ff1d0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000ff070:	pacibsp	
0x1000ff074:	sub	sp, sp, #0x40
0x1000ff078:	stp	x22, x21, [sp, #0x10]
0x1000ff07c:	stp	x20, x19, [sp, #0x20]
0x1000ff080:	stp	x29, x30, [sp, #0x30]
0x1000ff084:	add	x29, sp, #0x30
0x1000ff088:	cbz	x0, #0x1000ff0b8
0x1000ff08c:	mov	x20, x0
0x1000ff090:	ldrb	w8, [x0, #0x1e]
0x1000ff094:	cmp	w8, #1
0x1000ff098:	b.ne	#0x1000ff0d4
0x1000ff09c:	adrp	x0, #0x10022b000
0x1000ff0a0:	ldr	x0, [x0, #0xbb0]
0x1000ff0a4:	mov	w1, #0x10
0x1000ff0a8:	bl	#0x1001a2830
0x1000ff0ac:	cbz	w0, #0x1000ff1bc
0x1000ff0b0:	bl	#0x100197a3c
0x1000ff0b4:	b	#0x1000ff1b8
0x1000ff0b8:	adrp	x0, #0x10022b000
0x1000ff0bc:	ldr	x0, [x0, #0xbb0]
0x1000ff0c0:	mov	w1, #0x10
0x1000ff0c4:	bl	#0x1001a2830
0x1000ff0c8:	cbz	w0, #0x1000ff1bc
0x1000ff0cc:	bl	#0x100197a88
0x1000ff0d0:	b	#0x1000ff1b8
0x1000ff0d4:	mov	x19, x1
0x1000ff0d8:	cbz	x1, #0x1000ff1a0
0x1000ff0dc:	ldr	x21, [x20, #0x128]
0x1000ff0e0:	cbz	x21, #0x1000ff120
0x1000ff0e4:	ldr	x22, [x20]
0x1000ff0e8:	mov	x0, x19
0x1000ff0ec:	bl	#0x100067694
0x1000ff0f0:	mov	x2, x0
0x1000ff0f4:	mov	x8, x21
0x1000ff0f8:	ldr	x9, [x8, #0x10]!
0x1000ff0fc:	stp	xzr, xzr, [sp]
0x1000ff100:	mov	x0, x21
0x1000ff104:	mov	x1, x22
0x1000ff108:	mov	x3, x19
0x1000ff10c:	mov	w4, #0
0x1000ff110:	mov	w5, #0
0x1000ff114:	mov	x6, #0
0x1000ff118:	mov	x7, #0
0x1000ff11c:	blraa	x9, x8
0x1000ff120:	mov	x0, x20
0x1000ff124:	mov	x1, x19
0x1000ff128:	bl	#0x1001327d0
0x1000ff12c:	cbz	w0, #0x1000ff1bc
0x1000ff130:	bl	#0x100022760
0x1000ff134:	cbz	w0, #0x1000ff17c
0x1000ff138:	ldr	x21, [x20, #0x128]
0x1000ff13c:	cbz	x21, #0x1000ff17c
0x1000ff140:	ldr	x22, [x20]
0x1000ff144:	mov	x0, x19
0x1000ff148:	bl	#0x100067694
0x1000ff14c:	mov	x2, x0
0x1000ff150:	mov	x8, x21
0x1000ff154:	ldr	x9, [x8, #0x10]!
0x1000ff158:	stp	xzr, xzr, [sp]
0x1000ff15c:	mov	x0, x21
0x1000ff160:	mov	x1, x22
0x1000ff164:	mov	x3, x19
0x1000ff168:	mov	w4, #0
0x1000ff16c:	mov	w5, #1
0x1000ff170:	mov	x6, #0
0x1000ff174:	mov	x7, #0
0x1000ff178:	blraa	x9, x8
0x1000ff17c:	ldr	x0, [x20, #0x100]
0x1000ff180:	cbz	x0, #0x1000ff198
0x1000ff184:	ldr	x1, [x20]
0x1000ff188:	mov	x8, x0
0x1000ff18c:	ldr	x9, [x8, #0x10]!
0x1000ff190:	mov	x2, x19
0x1000ff194:	blraa	x9, x8
0x1000ff198:	mov	w0, #1
0x1000ff19c:	b	#0x1000ff1bc
0x1000ff1a0:	adrp	x0, #0x10022b000
0x1000ff1a4:	ldr	x0, [x0, #0xbb0]
0x1000ff1a8:	mov	w1, #0x10
0x1000ff1ac:	bl	#0x1001a2830
0x1000ff1b0:	cbz	w0, #0x1000ff1bc
0x1000ff1b4:	bl	#0x1001979f0
0x1000ff1b8:	mov	w0, #0
0x1000ff1bc:	ldp	x29, x30, [sp, #0x30]
0x1000ff1c0:	ldp	x20, x19, [sp, #0x20]
0x1000ff1c4:	ldp	x22, x21, [sp, #0x10]
0x1000ff1c8:	add	sp, sp, #0x40
0x1000ff1cc:	retab	

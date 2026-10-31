; accessoryd 0x1000dd9e8-0x1000dda90; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000dd9e8:	pacibsp	
0x1000dd9ec:	sub	sp, sp, #0x30
0x1000dd9f0:	stp	x20, x19, [sp, #0x10]
0x1000dd9f4:	stp	x29, x30, [sp, #0x20]
0x1000dd9f8:	add	x29, sp, #0x20
0x1000dd9fc:	adrp	x20, #0x10022a000
0x1000dda00:	ldr	x0, [x20, #0xef8]
0x1000dda04:	bl	#0x1001aadc0
0x1000dda08:	bl	#0x1001a2490
0x1000dda0c:	mov	x19, x0
0x1000dda10:	bl	#0x1001a7080
0x1000dda14:	bl	#0x1001a2560
0x1000dda18:	ldr	x0, [x20, #0xef8]
0x1000dda1c:	bl	#0x1001aadc0
0x1000dda20:	bl	#0x1001a2490
0x1000dda24:	mov	x19, x0
0x1000dda28:	bl	#0x1001a67a0
0x1000dda2c:	mov	x20, x0
0x1000dda30:	bl	#0x1001a2560
0x1000dda34:	cmp	x20, #1
0x1000dda38:	b.ne	#0x1000dda80
0x1000dda3c:	adrp	x8, #0x10022a000
0x1000dda40:	ldr	x0, [x8, #0xed0]
0x1000dda44:	bl	#0x1001aad80
0x1000dda48:	bl	#0x1001a2490
0x1000dda4c:	str	x0, [sp, #8]
0x1000dda50:	adrp	x2, #0x10022a000
0x1000dda54:	add	x2, x2, #0xd8
0x1000dda58:	bl	#0x1001ab1c0
0x1000dda5c:	ldr	x0, [sp, #8]
0x1000dda60:	ldp	x29, x30, [sp, #0x20]
0x1000dda64:	ldp	x20, x19, [sp, #0x10]
0x1000dda68:	add	sp, sp, #0x30
0x1000dda6c:	autibsp	
0x1000dda70:	eor	x16, x30, x30, lsl #1
0x1000dda74:	tbz	x16, #0x3e, #0x1000dda7c
0x1000dda78:	brk	#0xc471
0x1000dda7c:	b	#0x1001a2540
0x1000dda80:	ldp	x29, x30, [sp, #0x20]
0x1000dda84:	ldp	x20, x19, [sp, #0x10]
0x1000dda88:	add	sp, sp, #0x30
0x1000dda8c:	retab	

; accessoryd 0x1000dd2f8-0x1000dd364; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000dd2f8:	pacibsp	
0x1000dd2fc:	sub	sp, sp, #0x30
0x1000dd300:	stp	x20, x19, [sp, #0x10]
0x1000dd304:	stp	x29, x30, [sp, #0x20]
0x1000dd308:	add	x29, sp, #0x20
0x1000dd30c:	strh	w1, [sp, #0xe]
0x1000dd310:	cbz	x0, #0x1000dd354
0x1000dd314:	mov	x19, x0
0x1000dd318:	adrp	x8, #0x10022b000
0x1000dd31c:	ldr	x8, [x8, #0xce0]
0x1000dd320:	ldr	x0, [x8]
0x1000dd324:	add	x2, sp, #0xe
0x1000dd328:	mov	w1, #2
0x1000dd32c:	bl	#0x1001a17a0
0x1000dd330:	mov	x20, x0
0x1000dd334:	adrp	x8, #0x10023d000
0x1000dd338:	add	x8, x8, #0xbb8
0x1000dd33c:	ldr	x1, [x8]
0x1000dd340:	mov	x0, x19
0x1000dd344:	mov	x2, x20
0x1000dd348:	bl	#0x1001a16d0
0x1000dd34c:	mov	x0, x20
0x1000dd350:	bl	#0x1001a1820
0x1000dd354:	ldp	x29, x30, [sp, #0x20]
0x1000dd358:	ldp	x20, x19, [sp, #0x10]
0x1000dd35c:	add	sp, sp, #0x30
0x1000dd360:	retab	

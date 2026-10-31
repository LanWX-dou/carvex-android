; accessoryd 0x100034424-0x100034464; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100034424:	pacibsp	
0x100034428:	stp	x20, x19, [sp, #-0x20]!
0x10003442c:	stp	x29, x30, [sp, #0x10]
0x100034430:	add	x29, sp, #0x10
0x100034434:	ldrb	w8, [x0, #0xd4]
0x100034438:	tbnz	w8, #2, #0x100034444
0x10003443c:	bl	#0x1000024e4
0x100034440:	b	#0x100034454
0x100034444:	ldrb	w8, [x0, #0xbe]
0x100034448:	add	w19, w8, #0x47
0x10003444c:	bl	#0x1000024e4
0x100034450:	and	w0, w19, w0
0x100034454:	and	w0, w0, #0xff
0x100034458:	ldp	x29, x30, [sp, #0x10]
0x10003445c:	ldp	x20, x19, [sp], #0x20
0x100034460:	retab	

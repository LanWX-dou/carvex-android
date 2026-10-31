; accessoryd 0x10002a934-0x10002a980; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x10002a934:	pacibsp	
0x10002a938:	stp	x20, x19, [sp, #-0x20]!
0x10002a93c:	stp	x29, x30, [sp, #0x10]
0x10002a940:	add	x29, sp, #0x10
0x10002a944:	mov	x19, x0
0x10002a948:	ldr	x0, [x0, #0x20]
0x10002a94c:	bl	#0x10007dadc
0x10002a950:	ldr	x0, [x19, #0x20]
0x10002a954:	cbz	x0, #0x10002a974
0x10002a958:	ldp	x29, x30, [sp, #0x10]
0x10002a95c:	ldp	x20, x19, [sp], #0x20
0x10002a960:	autibsp	
0x10002a964:	eor	x16, x30, x30, lsl #1
0x10002a968:	tbz	x16, #0x3e, #0x10002a970
0x10002a96c:	brk	#0xc471
0x10002a970:	b	#0x1001a1820
0x10002a974:	ldp	x29, x30, [sp, #0x10]
0x10002a978:	ldp	x20, x19, [sp], #0x20
0x10002a97c:	retab	

; CoreUtils 0x18be48ef0-0x18be48f28; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be48ef0:	pacibsp	
0x18be48ef4:	stp	x20, x19, [sp, #-0x20]!
0x18be48ef8:	stp	x29, x30, [sp, #0x10]
0x18be48efc:	add	x29, sp, #0x10
0x18be48f00:	mov	x19, x2
0x18be48f04:	mov	x20, x0
0x18be48f08:	add	x0, x0, #0x88
0x18be48f0c:	bl	#0x18be48df8
0x18be48f10:	ldr	x8, [x20, #0xe8]
0x18be48f14:	add	x8, x8, x19
0x18be48f18:	str	x8, [x20, #0xe8]
0x18be48f1c:	ldp	x29, x30, [sp, #0x10]
0x18be48f20:	ldp	x20, x19, [sp], #0x20
0x18be48f24:	retab	

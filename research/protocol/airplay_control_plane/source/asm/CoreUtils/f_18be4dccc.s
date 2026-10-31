; CoreUtils 0x18be4dccc-0x18be4dcf8; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be4dccc:	pacibsp	
0x18be4dcd0:	sub	sp, sp, #0x20
0x18be4dcd4:	stp	x29, x30, [sp, #0x10]
0x18be4dcd8:	add	x29, sp, #0x10
0x18be4dcdc:	add	x8, x29, #0x10
0x18be4dce0:	str	x8, [sp, #8]
0x18be4dce4:	add	x4, x29, #0x10
0x18be4dce8:	bl	#0x18be4dc0c
0x18be4dcec:	ldp	x29, x30, [sp, #0x10]
0x18be4dcf0:	add	sp, sp, #0x20
0x18be4dcf4:	retab	

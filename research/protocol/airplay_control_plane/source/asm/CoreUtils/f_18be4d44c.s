; CoreUtils 0x18be4d44c-0x18be4d478; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be4d44c:	pacibsp	
0x18be4d450:	sub	sp, sp, #0x20
0x18be4d454:	stp	x29, x30, [sp, #0x10]
0x18be4d458:	add	x29, sp, #0x10
0x18be4d45c:	add	x8, x29, #0x10
0x18be4d460:	str	x8, [sp, #8]
0x18be4d464:	add	x3, x29, #0x10
0x18be4d468:	bl	#0x18be4d298
0x18be4d46c:	ldp	x29, x30, [sp, #0x10]
0x18be4d470:	add	sp, sp, #0x20
0x18be4d474:	retab	

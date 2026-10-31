; CoreUtils 0x18be4dcf8-0x18be4dd34; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18be4dcf8:	pacibsp	
0x18be4dcfc:	sub	sp, sp, #0x20
0x18be4dd00:	stp	x29, x30, [sp, #0x10]
0x18be4dd04:	add	x29, sp, #0x10
0x18be4dd08:	mov	x9, x3
0x18be4dd0c:	mov	x8, x1
0x18be4dd10:	str	x2, [sp]
0x18be4dd14:	adrp	x3, #0x18bf70000
0x18be4dd18:	add	x3, x3, #0x51e
0x18be4dd1c:	mov	x1, x9
0x18be4dd20:	mov	x2, x8
0x18be4dd24:	bl	#0x18be4dccc
0x18be4dd28:	ldp	x29, x30, [sp, #0x10]
0x18be4dd2c:	add	sp, sp, #0x20
0x18be4dd30:	retab	

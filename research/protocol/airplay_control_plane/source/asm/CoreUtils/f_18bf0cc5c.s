; CoreUtils 0x18bf0cc5c-0x18bf0cc8c; source SHA256 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x18bf0cc5c:	pacibsp	
0x18bf0cc60:	sub	sp, sp, #0x20
0x18bf0cc64:	stp	x29, x30, [sp, #0x10]
0x18bf0cc68:	add	x29, sp, #0x10
0x18bf0cc6c:	add	x8, x29, #0x10
0x18bf0cc70:	str	x8, [sp, #8]
0x18bf0cc74:	add	x0, x0, #0x18
0x18bf0cc78:	add	x4, x29, #0x10
0x18bf0cc7c:	bl	#0x18be4dc0c
0x18bf0cc80:	ldp	x29, x30, [sp, #0x10]
0x18bf0cc84:	add	sp, sp, #0x20
0x18bf0cc88:	retab	

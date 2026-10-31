; accessoryd 0x100008e80-0x100008e94; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100008e80:	ldr	x8, [x0, #0x40]
0x100008e84:	ldurh	w9, [x0, #0x3d]
0x100008e88:	ubfx	w1, w9, #0xc, #2
0x100008e8c:	add	x0, x8, #8
0x100008e90:	b	#0x100008e94

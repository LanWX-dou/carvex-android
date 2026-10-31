; accessoryd 0x100003360-0x100003370; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100003360:	cbz	x0, #0x10000336c
0x100003364:	add	x8, x0, #0xd0
0x100003368:	ldr	x0, [x8, w1, uxtw #3]
0x10000336c:	ret	

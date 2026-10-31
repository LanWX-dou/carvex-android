; accessoryd 0x100067688-0x100067694; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100067688:	cbz	x0, #0x100067690
0x10006768c:	str	x1, [x0, #0x40]
0x100067690:	ret	

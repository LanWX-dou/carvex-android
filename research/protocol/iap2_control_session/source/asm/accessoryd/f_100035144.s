; accessoryd 0x100035144-0x100035154; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100035144:	ldrb	w8, [x0, #0xd4]
0x100035148:	orr	w8, w8, #0x10
0x10003514c:	strb	w8, [x0, #0xd4]
0x100035150:	ret	

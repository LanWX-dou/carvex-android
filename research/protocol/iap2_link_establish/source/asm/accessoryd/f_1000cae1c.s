; accessoryd 0x1000cae1c-0x1000cae38; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000cae1c:	pacibsp	
0x1000cae20:	stp	x29, x30, [sp, #-0x10]!
0x1000cae24:	mov	x29, sp
0x1000cae28:	bl	#0x100033ed8
0x1000cae2c:	add	w0, w0, #0x60
0x1000cae30:	ldp	x29, x30, [sp], #0x10
0x1000cae34:	retab	

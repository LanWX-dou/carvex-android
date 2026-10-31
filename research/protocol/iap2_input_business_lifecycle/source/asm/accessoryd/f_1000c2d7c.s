; accessoryd 0x1000c2d7c-0x1000c2db4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000c2d7c:	cbz	x0, #0x1000c2dac
0x1000c2d80:	ldr	x0, [x0, #0x28]
0x1000c2d84:	cbz	x0, #0x1000c2dac
0x1000c2d88:	pacibsp	
0x1000c2d8c:	stp	x29, x30, [sp, #-0x10]!
0x1000c2d90:	mov	x29, sp
0x1000c2d94:	bl	#0x1000cb1f0
0x1000c2d98:	mov	w0, #0x86a0
0x1000c2d9c:	movk	w0, #1, lsl #16
0x1000c2da0:	bl	#0x1001a2a40
0x1000c2da4:	ldp	x29, x30, [sp], #0x10
0x1000c2da8:	autibsp	
0x1000c2dac:	mov	w0, #1
0x1000c2db0:	ret	

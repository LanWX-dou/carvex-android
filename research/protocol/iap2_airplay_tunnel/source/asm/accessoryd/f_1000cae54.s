; accessoryd 0x1000cae54-0x1000caef4; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000cae54:	pacibsp	
0x1000cae58:	stp	x22, x21, [sp, #-0x30]!
0x1000cae5c:	stp	x20, x19, [sp, #0x10]
0x1000cae60:	stp	x29, x30, [sp, #0x20]
0x1000cae64:	add	x29, sp, #0x20
0x1000cae68:	cbz	x7, #0x1000caeec
0x1000cae6c:	mov	x19, x7
0x1000cae70:	mov	x20, x6
0x1000cae74:	mov	x21, x5
0x1000cae78:	movi	v0.2d, #0000000000000000
0x1000cae7c:	stp	q0, q0, [x7]
0x1000cae80:	stp	q0, q0, [x7, #0x40]
0x1000cae84:	stp	q0, q0, [x7, #0x20]
0x1000cae88:	str	x7, [x7]
0x1000cae8c:	add	x22, x7, #0x60
0x1000cae90:	str	x1, [x7, #0x10]
0x1000cae94:	mov	x1, x7
0x1000cae98:	mov	x7, x22
0x1000cae9c:	bl	#0x100033fd0
0x1000caea0:	str	x0, [x19, #0x18]
0x1000caea4:	mov	x0, x21
0x1000caea8:	mov	x1, x20
0x1000caeac:	bl	#0x100033ed8
0x1000caeb0:	mov	x8, x0
0x1000caeb4:	ldr	x0, [x19, #0x18]
0x1000caeb8:	cbz	x0, #0x1000caef0
0x1000caebc:	add	x8, x22, w8, uxtw
0x1000caec0:	str	x8, [x19, #8]
0x1000caec4:	bl	#0x100035144
0x1000caec8:	ldr	x0, [x19, #0x18]
0x1000caecc:	bl	#0x100034a70
0x1000caed0:	mov	x0, x19
0x1000caed4:	bl	#0x100103954
0x1000caed8:	mov	x0, x19
0x1000caedc:	ldp	x29, x30, [sp, #0x20]
0x1000caee0:	ldp	x20, x19, [sp, #0x10]
0x1000caee4:	ldp	x22, x21, [sp], #0x30
0x1000caee8:	retab	
0x1000caeec:	bl	#0x10017ab74
0x1000caef0:	bl	#0x10017ab48

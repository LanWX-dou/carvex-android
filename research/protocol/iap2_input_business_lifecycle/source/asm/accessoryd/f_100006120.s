; accessoryd 0x100006120-0x100006174; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100006120:	pacibsp	
0x100006124:	stp	x22, x21, [sp, #-0x30]!
0x100006128:	stp	x20, x19, [sp, #0x10]
0x10000612c:	stp	x29, x30, [sp, #0x20]
0x100006130:	add	x29, sp, #0x20
0x100006134:	mov	x19, x0
0x100006138:	ldr	x20, [x0]
0x10000613c:	mov	x0, x20
0x100006140:	bl	#0x100005f4c
0x100006144:	mov	x21, x0
0x100006148:	mov	x0, x20
0x10000614c:	bl	#0x100005f38
0x100006150:	ldrh	w8, [x19, #0x36]
0x100006154:	add	w9, w0, w21
0x100006158:	subs	w8, w8, w9
0x10000615c:	csel	w8, w8, wzr, hi
0x100006160:	and	w0, w8, #0xffff
0x100006164:	ldp	x29, x30, [sp, #0x20]
0x100006168:	ldp	x20, x19, [sp, #0x10]
0x10000616c:	ldp	x22, x21, [sp], #0x30
0x100006170:	retab	

; APTransport 0x24fda858c-0x24fda863c; source SHA256 e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x24fda858c:	pacibsp	
0x24fda8590:	sub	sp, sp, #0x60
0x24fda8594:	stp	x24, x23, [sp, #0x20]
0x24fda8598:	stp	x22, x21, [sp, #0x30]
0x24fda859c:	stp	x20, x19, [sp, #0x40]
0x24fda85a0:	stp	x29, x30, [sp, #0x50]
0x24fda85a4:	add	x29, sp, #0x50
0x24fda85a8:	mov	x21, x3
0x24fda85ac:	mov	x22, x2
0x24fda85b0:	mov	x20, x1
0x24fda85b4:	mov	x23, x0
0x24fda85b8:	bl	#0x2500e5a60
0x24fda85bc:	mov	x19, x0
0x24fda85c0:	stp	x23, x20, [sp]
0x24fda85c4:	stp	x22, x21, [sp, #0x10]
0x24fda85c8:	mov	x0, x20
0x24fda85cc:	bl	#0x24fda863c
0x24fda85d0:	cbz	x0, #0x24fda8608
0x24fda85d4:	mov	x0, x20
0x24fda85d8:	mov	w1, #3
0x24fda85dc:	bl	#0x24fdfad78
0x24fda85e0:	mov	x20, x0
0x24fda85e4:	str	x0, [sp, #8]
0x24fda85e8:	bl	#0x24fddfe94
0x24fda85ec:	cbnz	w0, #0x24fda8608
0x24fda85f0:	ldr	w8, [x19, #0xb4]
0x24fda85f4:	add	w1, w8, #1
0x24fda85f8:	str	w1, [x19, #0xb4]
0x24fda85fc:	mov	x0, x20
0x24fda8600:	bl	#0x24fdfad84
0x24fda8604:	str	x0, [sp, #8]
0x24fda8608:	ldr	x0, [x19, #0x18]
0x24fda860c:	adrp	x16, #0x24fda8000
0x24fda8610:	add	x16, x16, #0x644
0x24fda8614:	paciza	x16
0x24fda8618:	mov	x1, x16
0x24fda861c:	mov	x2, sp
0x24fda8620:	bl	#0x2500edf10
0x24fda8624:	ldp	x29, x30, [sp, #0x50]
0x24fda8628:	ldp	x20, x19, [sp, #0x40]
0x24fda862c:	ldp	x22, x21, [sp, #0x30]
0x24fda8630:	ldp	x24, x23, [sp, #0x20]
0x24fda8634:	add	sp, sp, #0x60
0x24fda8638:	retab	

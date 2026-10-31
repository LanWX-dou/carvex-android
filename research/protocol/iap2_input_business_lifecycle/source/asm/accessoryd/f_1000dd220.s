; accessoryd 0x1000dd220-0x1000dd28c; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000dd220:	pacibsp	
0x1000dd224:	sub	sp, sp, #0x30
0x1000dd228:	stp	x20, x19, [sp, #0x10]
0x1000dd22c:	stp	x29, x30, [sp, #0x20]
0x1000dd230:	add	x29, sp, #0x20
0x1000dd234:	strh	w1, [sp, #0xe]
0x1000dd238:	cbz	x0, #0x1000dd27c
0x1000dd23c:	mov	x19, x0
0x1000dd240:	adrp	x8, #0x10022b000
0x1000dd244:	ldr	x8, [x8, #0xce0]
0x1000dd248:	ldr	x0, [x8]
0x1000dd24c:	add	x2, sp, #0xe
0x1000dd250:	mov	w1, #2
0x1000dd254:	bl	#0x1001a17a0
0x1000dd258:	mov	x20, x0
0x1000dd25c:	adrp	x8, #0x10023d000
0x1000dd260:	add	x8, x8, #0xba8
0x1000dd264:	ldr	x1, [x8]
0x1000dd268:	mov	x0, x19
0x1000dd26c:	mov	x2, x20
0x1000dd270:	bl	#0x1001a16d0
0x1000dd274:	mov	x0, x20
0x1000dd278:	bl	#0x1001a1820
0x1000dd27c:	ldp	x29, x30, [sp, #0x20]
0x1000dd280:	ldp	x20, x19, [sp, #0x10]
0x1000dd284:	add	sp, sp, #0x30
0x1000dd288:	retab	

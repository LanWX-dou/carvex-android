; airplaysender 0x251a77178-0x251a77208; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a77178:	pacibsp	
0x251a7717c:	sub	sp, sp, #0x40
0x251a77180:	stp	d9, d8, [sp, #0x10]
0x251a77184:	stp	x20, x19, [sp, #0x20]
0x251a77188:	stp	x29, x30, [sp, #0x30]
0x251a7718c:	add	x29, sp, #0x30
0x251a77190:	mov	x19, x4
0x251a77194:	mov	x20, x3
0x251a77198:	ldr	q0, [x2]
0x251a7719c:	fcvtzu	v0.2d, v0.2d
0x251a771a0:	ucvtf	v0.2d, v0.2d
0x251a771a4:	str	q0, [sp]
0x251a771a8:	bl	#0x25810d280
0x251a771ac:	mov	v2.16b, v0.16b
0x251a771b0:	mov	v3.16b, v1.16b
0x251a771b4:	ldr	q0, [sp]
0x251a771b8:	mov	d1, v0.d[1]
0x251a771bc:	bl	#0x25810c320
0x251a771c0:	mov	v8.16b, v1.16b
0x251a771c4:	fcvtzs	w1, d0
0x251a771c8:	adrp	x0, #0x276131000
0x251a771cc:	add	x0, x0, #0x590
0x251a771d0:	bl	#0x258109e20
0x251a771d4:	sxtw	x8, w0
0x251a771d8:	str	x8, [x20]
0x251a771dc:	fcvtzs	w1, d8
0x251a771e0:	adrp	x0, #0x276131000
0x251a771e4:	add	x0, x0, #0x5b0
0x251a771e8:	bl	#0x258109e20
0x251a771ec:	sxtw	x8, w0
0x251a771f0:	str	x8, [x19]
0x251a771f4:	ldp	x29, x30, [sp, #0x30]
0x251a771f8:	ldp	x20, x19, [sp, #0x20]
0x251a771fc:	ldp	d9, d8, [sp, #0x10]
0x251a77200:	add	sp, sp, #0x40
0x251a77204:	retab	

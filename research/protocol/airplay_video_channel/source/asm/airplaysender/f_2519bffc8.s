; airplaysender 0x2519bffc8-0x2519c0148; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519bffc8:	pacibsp	
0x2519bffcc:	stp	x28, x27, [sp, #-0x60]!
0x2519bffd0:	stp	x26, x25, [sp, #0x10]
0x2519bffd4:	stp	x24, x23, [sp, #0x20]
0x2519bffd8:	stp	x22, x21, [sp, #0x30]
0x2519bffdc:	stp	x20, x19, [sp, #0x40]
0x2519bffe0:	stp	x29, x30, [sp, #0x50]
0x2519bffe4:	add	x29, sp, #0x50
0x2519bffe8:	mov	x20, x6
0x2519bffec:	mov	x21, x5
0x2519bfff0:	mov	x22, x4
0x2519bfff4:	mov	x23, x3
0x2519bfff8:	mov	x24, x2
0x2519bfffc:	mov	x25, x1
0x2519c0000:	bl	#0x25810ac50
0x2519c0004:	cbz	x21, #0x2519c0108
0x2519c0008:	mov	x26, x0
0x2519c000c:	ldr	x8, [x0]
0x2519c0010:	cbz	x8, #0x2519c011c
0x2519c0014:	ldr	x0, [x26, #8]
0x2519c0018:	mov	x1, x21
0x2519c001c:	bl	#0x25810e760
0x2519c0020:	cbz	x0, #0x2519c012c
0x2519c0024:	mov	x19, x0
0x2519c0028:	mov	x1, x21
0x2519c002c:	bl	#0x25810e790
0x2519c0030:	ldr	x27, [x26]
0x2519c0034:	mov	x0, x19
0x2519c0038:	bl	#0x25810e780
0x2519c003c:	mov	x26, x0
0x2519c0040:	mov	x0, x27
0x2519c0044:	bl	#0x258109150
0x2519c0048:	ldr	x16, [x0, #0x10]!
0x2519c004c:	mov	x17, x0
0x2519c0050:	movk	x17, #0xf7db, lsl #48
0x2519c0054:	autda	x16, x17
0x2519c0058:	ldr	x9, [x16, #8]!
0x2519c005c:	cbz	x9, #0x2519c00c4
0x2519c0060:	mov	x8, x16
0x2519c0064:	movk	x8, #0x2d6f, lsl #48
0x2519c0068:	mov	x16, x9
0x2519c006c:	mov	x17, x8
0x2519c0070:	autia	x16, x17
0x2519c0074:	mov	x17, x16
0x2519c0078:	xpaci	x17
0x2519c007c:	cmp	x16, x17
0x2519c0080:	b.eq	#0x2519c0088
0x2519c0084:	brk	#0xc470
0x2519c0088:	paciza	x16
0x2519c008c:	cbz	x16, #0x2519c00c4
0x2519c0090:	mov	x0, x27
0x2519c0094:	mov	x1, x25
0x2519c0098:	mov	x2, x24
0x2519c009c:	mov	x3, x23
0x2519c00a0:	mov	x4, x22
0x2519c00a4:	mov	x5, x21
0x2519c00a8:	mov	x6, x26
0x2519c00ac:	blraa	x9, x8
0x2519c00b0:	cbnz	w0, #0x2519c0140
0x2519c00b4:	mov	w21, #0
0x2519c00b8:	cbz	x20, #0x2519c00e0
0x2519c00bc:	str	x19, [x20]
0x2519c00c0:	b	#0x2519c00e8
0x2519c00c4:	mov	w21, #-0x31ee
0x2519c00c8:	adrp	x1, #0x251bdf000
0x2519c00cc:	add	x1, x1, #0x61d
0x2519c00d0:	mov	x0, x21
0x2519c00d4:	mov	w2, #0x109
0x2519c00d8:	mov	w3, #0
0x2519c00dc:	bl	#0x258109a30
0x2519c00e0:	mov	x0, x19
0x2519c00e4:	bl	#0x2580f5830
0x2519c00e8:	mov	x0, x21
0x2519c00ec:	ldp	x29, x30, [sp, #0x50]
0x2519c00f0:	ldp	x20, x19, [sp, #0x40]
0x2519c00f4:	ldp	x22, x21, [sp, #0x30]
0x2519c00f8:	ldp	x24, x23, [sp, #0x20]
0x2519c00fc:	ldp	x26, x25, [sp, #0x10]
0x2519c0100:	ldp	x28, x27, [sp], #0x60
0x2519c0104:	retab	
0x2519c0108:	bl	#0x251b4c2b4
0x2519c010c:	mov	w8, #0xe7d6
0x2519c0110:	movk	w8, #0xfffe, lsl #16
0x2519c0114:	orr	w21, w8, #1
0x2519c0118:	b	#0x2519c00e8
0x2519c011c:	mov	w21, #0xe7d6
0x2519c0120:	movk	w21, #0xfffe, lsl #16
0x2519c0124:	bl	#0x251b4c2a0
0x2519c0128:	b	#0x2519c00e8
0x2519c012c:	bl	#0x251b4c28c
0x2519c0130:	mov	w8, #0xe7d6
0x2519c0134:	movk	w8, #0xfffe, lsl #16
0x2519c0138:	add	w21, w8, #2
0x2519c013c:	b	#0x2519c00e8
0x2519c0140:	mov	x21, x0
0x2519c0144:	b	#0x2519c00c8

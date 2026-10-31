; AirPlaySender 0x251a58098-0x251a581a4; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a58098:	pacibsp	
0x251a5809c:	sub	sp, sp, #0x40
0x251a580a0:	stp	x22, x21, [sp, #0x10]
0x251a580a4:	stp	x20, x19, [sp, #0x20]
0x251a580a8:	stp	x29, x30, [sp, #0x30]
0x251a580ac:	add	x29, sp, #0x30
0x251a580b0:	mov	x20, x2
0x251a580b4:	mov	x21, x1
0x251a580b8:	mov	x19, x0
0x251a580bc:	bl	#0x25810ac50
0x251a580c0:	ldrb	w8, [x0]
0x251a580c4:	cbnz	w8, #0x251a58184
0x251a580c8:	mov	x1, sp
0x251a580cc:	mov	x0, x19
0x251a580d0:	bl	#0x2519c8d58
0x251a580d4:	ldr	x19, [sp]
0x251a580d8:	cbz	x19, #0x251a58194
0x251a580dc:	mov	x0, x19
0x251a580e0:	bl	#0x258109150
0x251a580e4:	ldr	x16, [x0, #0x10]!
0x251a580e8:	mov	x17, x0
0x251a580ec:	movk	x17, #0x5584, lsl #48
0x251a580f0:	autda	x16, x17
0x251a580f4:	ldr	x9, [x16, #0x18]!
0x251a580f8:	cbz	x9, #0x251a58148
0x251a580fc:	mov	x8, x16
0x251a58100:	movk	x8, #0x3564, lsl #48
0x251a58104:	mov	x16, x9
0x251a58108:	mov	x17, x8
0x251a5810c:	autia	x16, x17
0x251a58110:	mov	x17, x16
0x251a58114:	xpaci	x17
0x251a58118:	cmp	x16, x17
0x251a5811c:	b.eq	#0x251a58124
0x251a58120:	brk	#0xc470
0x251a58124:	paciza	x16
0x251a58128:	cbz	x16, #0x251a58148
0x251a5812c:	mov	x0, x19
0x251a58130:	mov	x1, x21
0x251a58134:	mov	x2, x20
0x251a58138:	blraa	x9, x8
0x251a5813c:	mov	x20, x0
0x251a58140:	cbnz	w0, #0x251a5814c
0x251a58144:	b	#0x251a58164
0x251a58148:	mov	w20, #-0x31ee
0x251a5814c:	adrp	x1, #0x251bf6000
0x251a58150:	add	x1, x1, #0xb3d
0x251a58154:	mov	x0, x20
0x251a58158:	mov	w2, #0x215a
0x251a5815c:	mov	w3, #0
0x251a58160:	bl	#0x258109a30
0x251a58164:	mov	x0, x19
0x251a58168:	bl	#0x2580f5830
0x251a5816c:	mov	x0, x20
0x251a58170:	ldp	x29, x30, [sp, #0x30]
0x251a58174:	ldp	x20, x19, [sp, #0x20]
0x251a58178:	ldp	x22, x21, [sp, #0x10]
0x251a5817c:	add	sp, sp, #0x40
0x251a58180:	retab	
0x251a58184:	add	x0, sp, #0xc
0x251a58188:	bl	#0x251b5ff10
0x251a5818c:	ldr	w20, [sp, #0xc]
0x251a58190:	b	#0x251a5816c
0x251a58194:	bl	#0x251b5ff50
0x251a58198:	mov	w20, #0xe76b
0x251a5819c:	movk	w20, #0xfffe, lsl #16
0x251a581a0:	b	#0x251a5816c

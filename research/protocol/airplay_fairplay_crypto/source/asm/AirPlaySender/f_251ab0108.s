; AirPlaySender 0x251ab0108-0x251ab019c; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251ab0108:	pacibsp	
0x251ab010c:	stp	x22, x21, [sp, #-0x30]!
0x251ab0110:	stp	x20, x19, [sp, #0x10]
0x251ab0114:	stp	x29, x30, [sp, #0x20]
0x251ab0118:	add	x29, sp, #0x20
0x251ab011c:	mov	x19, x2
0x251ab0120:	mov	x20, x1
0x251ab0124:	bl	#0x25810ac50
0x251ab0128:	mov	x22, x0
0x251ab012c:	ldr	x0, [x0, #0x28]
0x251ab0130:	add	x1, x22, #8
0x251ab0134:	mov	w2, #0x10
0x251ab0138:	bl	#0x2580f6ff0
0x251ab013c:	cbz	x0, #0x251ab0178
0x251ab0140:	mov	x21, x0
0x251ab0144:	ldr	x0, [x22, #0x28]
0x251ab0148:	add	x1, x22, #0x18
0x251ab014c:	mov	w2, #0x10
0x251ab0150:	bl	#0x2580f6ff0
0x251ab0154:	cbz	x0, #0x251ab0188
0x251ab0158:	mov	w22, #0
0x251ab015c:	str	x21, [x20]
0x251ab0160:	str	x0, [x19]
0x251ab0164:	mov	x0, x22
0x251ab0168:	ldp	x29, x30, [sp, #0x20]
0x251ab016c:	ldp	x20, x19, [sp, #0x10]
0x251ab0170:	ldp	x22, x21, [sp], #0x30
0x251ab0174:	retab	
0x251ab0178:	mov	w22, #0xe7d8
0x251ab017c:	movk	w22, #0xfffe, lsl #16
0x251ab0180:	bl	#0x251b89c1c
0x251ab0184:	b	#0x251ab0164
0x251ab0188:	mov	w22, #0xe7d8
0x251ab018c:	movk	w22, #0xfffe, lsl #16
0x251ab0190:	mov	x0, x21
0x251ab0194:	bl	#0x251b89bd0
0x251ab0198:	b	#0x251ab0164

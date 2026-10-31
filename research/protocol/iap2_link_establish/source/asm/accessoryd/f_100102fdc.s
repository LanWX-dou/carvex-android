; accessoryd 0x100102fdc-0x1001031d0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100102fdc:	pacibsp	
0x100102fe0:	stp	x28, x27, [sp, #-0x50]!
0x100102fe4:	stp	x24, x23, [sp, #0x10]
0x100102fe8:	stp	x22, x21, [sp, #0x20]
0x100102fec:	stp	x20, x19, [sp, #0x30]
0x100102ff0:	stp	x29, x30, [sp, #0x40]
0x100102ff4:	add	x29, sp, #0x40
0x100102ff8:	mov	w9, #0x10
0x100102ffc:	movk	w9, #1, lsl #16
0x100103000:	adrp	x17, #0x10022b000
0x100103004:	add	x17, x17, #0xe18
0x100103008:	ldr	x16, [x17]
0x10010300c:	blraa	x16, x17
0x100103010:	sub	sp, sp, #0x10, lsl #12
0x100103014:	sub	sp, sp, #0x10
0x100103018:	mov	x22, x3
0x10010301c:	mov	x21, x2
0x100103020:	mov	x19, x1
0x100103024:	mov	x20, x0
0x100103028:	adrp	x8, #0x10022b000
0x10010302c:	ldr	x8, [x8, #0xb80]
0x100103030:	ldr	x8, [x8]
0x100103034:	stur	x8, [x29, #-0x48]
0x100103038:	add	x8, sp, #9
0x10010303c:	add	x0, x8, #0xa
0x100103040:	mov	w1, #0xaa
0x100103044:	mov	w2, #0xfff5
0x100103048:	bl	#0x1001a23c0
0x10010304c:	ldrb	w8, [x22]
0x100103050:	ldrb	w9, [x22, #1]
0x100103054:	ldrh	w10, [x22, #4]
0x100103058:	ldrh	w11, [x22, #6]
0x10010305c:	ldrh	w12, [x22, #8]
0x100103060:	ldrh	w13, [x22, #2]
0x100103064:	ldrb	w23, [x22, #0x18]
0x100103068:	ldrb	w24, [x22, #0xa]
0x10010306c:	strb	w8, [sp, #9]
0x100103070:	strb	w9, [sp, #0xa]
0x100103074:	lsr	w9, w10, #8
0x100103078:	strb	w9, [sp, #0xb]
0x10010307c:	strb	w10, [sp, #0xc]
0x100103080:	lsr	w9, w11, #8
0x100103084:	strb	w9, [sp, #0xd]
0x100103088:	strb	w11, [sp, #0xe]
0x10010308c:	lsr	w9, w12, #8
0x100103090:	strb	w9, [sp, #0xf]
0x100103094:	strb	w12, [sp, #0x10]
0x100103098:	sturh	w13, [sp, #0x11]
0x10010309c:	cbz	w8, #0x1001030b0
0x1001030a0:	cmp	w8, #1
0x1001030a4:	b.ne	#0x1001030bc
0x1001030a8:	mov	w9, #0xa
0x1001030ac:	b	#0x1001030b4
0x1001030b0:	mov	x9, #0
0x1001030b4:	mov	w8, #0xa
0x1001030b8:	b	#0x1001030fc
0x1001030bc:	strb	w23, [sp, #0x13]
0x1001030c0:	cbz	w23, #0x1001030e0
0x1001030c4:	add	x8, sp, #9
0x1001030c8:	add	x0, x8, #0xb
0x1001030cc:	add	x1, x22, #0x19
0x1001030d0:	mov	x2, x23
0x1001030d4:	bl	#0x1001a23a0
0x1001030d8:	add	w8, w23, #0xb
0x1001030dc:	b	#0x1001030e4
0x1001030e0:	mov	w8, #0xb
0x1001030e4:	add	w9, w23, #0xc
0x1001030e8:	add	x10, sp, #9
0x1001030ec:	add	x10, x10, w8, uxtb
0x1001030f0:	strb	w24, [x10]
0x1001030f4:	add	w8, w8, #1
0x1001030f8:	and	x9, x9, #0xff
0x1001030fc:	cmp	w24, #5
0x100103100:	mov	w11, #5
0x100103104:	csel	w10, w24, w11, lo
0x100103108:	cbz	w24, #0x100103160
0x10010310c:	mov	x11, #0
0x100103110:	add	x12, x22, #0x1e
0x100103114:	add	x13, sp, #9
0x100103118:	mov	x14, x10
0x10010311c:	add	x15, x12, x11, lsl #2
0x100103120:	ldrb	w16, [x15]
0x100103124:	strb	w16, [x13, x9]
0x100103128:	ldrb	w16, [x15, #1]
0x10010312c:	add	x17, x9, #1
0x100103130:	ldrb	w0, [x15, #3]
0x100103134:	orr	w16, w16, w0, lsl #7
0x100103138:	strb	w16, [x13, x17]
0x10010313c:	add	x16, x9, #2
0x100103140:	ldrb	w15, [x15, #2]
0x100103144:	strb	w15, [x13, x16]
0x100103148:	add	x11, x11, #1
0x10010314c:	add	x9, x9, #3
0x100103150:	subs	x14, x14, #1
0x100103154:	b.ne	#0x10010311c
0x100103158:	add	w9, w10, w10, lsl #1
0x10010315c:	add	w8, w8, w9
0x100103160:	cbz	x21, #0x100103170
0x100103164:	ldrb	w3, [x21]
0x100103168:	mov	w1, #0xc0
0x10010316c:	b	#0x100103178
0x100103170:	mov	w3, #0
0x100103174:	mov	w1, #0x80
0x100103178:	add	x4, sp, #9
0x10010317c:	and	w5, w8, #0xff
0x100103180:	mov	x0, x20
0x100103184:	mov	x2, x19
0x100103188:	mov	w6, #0
0x10010318c:	mov	w7, #1
0x100103190:	bl	#0x100006e24
0x100103194:	ldur	x8, [x29, #-0x48]
0x100103198:	adrp	x9, #0x10022b000
0x10010319c:	ldr	x9, [x9, #0xb80]
0x1001031a0:	ldr	x9, [x9]
0x1001031a4:	cmp	x9, x8
0x1001031a8:	b.ne	#0x1001031cc
0x1001031ac:	add	sp, sp, #0x10, lsl #12
0x1001031b0:	add	sp, sp, #0x10
0x1001031b4:	ldp	x29, x30, [sp, #0x40]
0x1001031b8:	ldp	x20, x19, [sp, #0x30]
0x1001031bc:	ldp	x22, x21, [sp, #0x20]
0x1001031c0:	ldp	x24, x23, [sp, #0x10]
0x1001031c4:	ldp	x28, x27, [sp], #0x50
0x1001031c8:	retab	
0x1001031cc:	bl	#0x1001a1f90

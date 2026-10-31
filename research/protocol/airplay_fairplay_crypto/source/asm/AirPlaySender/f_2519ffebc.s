; AirPlaySender 0x2519ffebc-0x251a0019c; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519ffebc:	pacibsp	
0x2519ffec0:	sub	sp, sp, #0xa0
0x2519ffec4:	stp	x28, x27, [sp, #0x40]
0x2519ffec8:	stp	x26, x25, [sp, #0x50]
0x2519ffecc:	stp	x24, x23, [sp, #0x60]
0x2519ffed0:	stp	x22, x21, [sp, #0x70]
0x2519ffed4:	stp	x20, x19, [sp, #0x80]
0x2519ffed8:	stp	x29, x30, [sp, #0x90]
0x2519ffedc:	add	x29, sp, #0x90
0x2519ffee0:	mov	x21, x4
0x2519ffee4:	mov	x20, x3
0x2519ffee8:	mov	x22, x2
0x2519ffeec:	mov	x19, x1
0x2519ffef0:	mov	x23, x0
0x2519ffef4:	adrp	x8, #0x2681b4000
0x2519ffef8:	ldr	x8, [x8, #0xee0]
0x2519ffefc:	ldr	x8, [x8]
0x2519fff00:	str	x8, [sp, #0x38]
0x2519fff04:	mov	x25, #0xb4fa
0x2519fff08:	movk	x25, #0x6d3c, lsl #16
0x2519fff0c:	movk	x25, #0x2a54, lsl #32
0x2519fff10:	movk	x25, #0x375b, lsl #48
0x2519fff14:	mov	w24, #0x1f79
0x2519fff18:	movk	w24, #0xd3ef, lsl #16
0x2519fff1c:	adrp	x8, #0x26e7e6000
0x2519fff20:	ldr	w10, [x8, #0x5c0]
0x2519fff24:	adrp	x9, #0x26e7db000
0x2519fff28:	ldr	w11, [x9, #0x410]
0x2519fff2c:	sub	w10, w11, w10
0x2519fff30:	eor	w10, w10, w25
0x2519fff34:	mul	w10, w10, w24
0x2519fff38:	adrp	x12, #0x251c6f000
0x2519fff3c:	add	x12, x12, #0xa60
0x2519fff40:	add	x12, x12, w10, uxtb
0x2519fff44:	ldrb	w12, [x12]
0x2519fff48:	adrp	x13, #0x251c70000
0x2519fff4c:	add	x13, x13, #0xb70
0x2519fff50:	eor	w12, w12, #0x18
0x2519fff54:	ldrb	w12, [x13, w12, uxtw]
0x2519fff58:	eor	w10, w10, w12
0x2519fff5c:	and	w10, w10, #0xff
0x2519fff60:	sub	w12, w10, #0x20
0x2519fff64:	adrp	x10, #0x27612b000
0x2519fff68:	add	x10, x10, #0x8f0
0x2519fff6c:	ldr	x26, [x10, w12, sxtw #3]
0x2519fff70:	ldr	x12, [x26, #-4]!
0x2519fff74:	add	w11, w11, w12
0x2519fff78:	eor	w11, w11, w25
0x2519fff7c:	mul	w11, w11, w24
0x2519fff80:	ldr	x13, [x10, #0x158]
0x2519fff84:	add	x13, x13, w11, uxtb
0x2519fff88:	ldurb	w13, [x13, #-0xc]
0x2519fff8c:	mov	w14, #0xcd
0x2519fff90:	eor	w13, w13, w14
0x2519fff94:	ldr	x14, [x10, #0x1f8]
0x2519fff98:	add	x13, x14, x13
0x2519fff9c:	ldurb	w13, [x13, #-4]
0x2519fffa0:	eor	w11, w13, w11
0x2519fffa4:	and	w11, w11, #0xff
0x2519fffa8:	sub	w11, w11, #0x19
0x2519fffac:	ldr	x27, [x10, w11, sxtw #3]
0x2519fffb0:	ldr	x11, [x27]
0x2519fffb4:	eor	x11, x11, x12
0x2519fffb8:	mov	x12, sp
0x2519fffbc:	add	x11, x11, x12
0x2519fffc0:	sub	x12, x11, x25
0x2519fffc4:	mul	x12, x12, x24
0x2519fffc8:	eor	x11, x11, x25
0x2519fffcc:	mul	x11, x11, x24
0x2519fffd0:	str	x12, [x26]
0x2519fffd4:	str	x11, [x27]
0x2519fffd8:	add	x11, sp, #8
0x2519fffdc:	mov	w12, #0x27f1
0x2519fffe0:	movk	w12, #0x609e, lsl #16
0x2519fffe4:	orr	w12, w11, w12
0x2519fffe8:	sub	w12, w12, w11
0x2519fffec:	mov	w13, #0xd808
0x2519ffff0:	movk	w13, #0x9f61, lsl #16
0x2519ffff4:	and	w11, w11, w13
0x2519ffff8:	add	w11, w12, w11
0x2519ffffc:	mov	w12, #0xe298
0x251a00000:	movk	w12, #0x5db6, lsl #16
0x251a00004:	eor	w11, w11, w12
0x251a00008:	mov	w12, #0x9f29
0x251a0000c:	movk	w12, #0x6c83, lsl #16
0x251a00010:	mov	w13, #0x25fc
0x251a00014:	movk	w13, #0xdb53, lsl #16
0x251a00018:	msub	w11, w11, w12, w13
0x251a0001c:	str	w11, [sp, #0xc]
0x251a00020:	ldr	w11, [x26]
0x251a00024:	ldr	w12, [x27]
0x251a00028:	sub	w11, w12, w11
0x251a0002c:	eor	w11, w11, w25
0x251a00030:	mul	w11, w11, w24
0x251a00034:	ldr	x12, [x10, #0x128]
0x251a00038:	add	x12, x12, w11, uxtb
0x251a0003c:	ldurb	w12, [x12, #-8]
0x251a00040:	mov	w13, #0xb9
0x251a00044:	eor	w12, w12, w13
0x251a00048:	ldr	x13, [x10, #0x638]
0x251a0004c:	add	x12, x13, x12
0x251a00050:	ldurb	w12, [x12, #-4]
0x251a00054:	eor	w11, w12, w11
0x251a00058:	and	w11, w11, #0xff
0x251a0005c:	add	w11, w11, #0x3fc
0x251a00060:	ldr	w8, [x8, #0x5c0]
0x251a00064:	ldr	w9, [x9, #0x410]
0x251a00068:	eor	w8, w8, w25
0x251a0006c:	eor	w8, w8, w9
0x251a00070:	mul	w8, w8, w24
0x251a00074:	adrp	x9, #0x251c70000
0x251a00078:	add	x9, x9, #0xc70
0x251a0007c:	add	x9, x9, w8, uxtb
0x251a00080:	ldrb	w9, [x9]
0x251a00084:	mov	w12, #0x69
0x251a00088:	eor	w9, w9, w12
0x251a0008c:	adrp	x12, #0x251c6d000
0x251a00090:	add	x12, x12, #0x90
0x251a00094:	ldrb	w9, [x12, w9, uxtw]
0x251a00098:	eor	w8, w8, w9
0x251a0009c:	and	w8, w8, #0xff
0x251a000a0:	sub	w8, w8, #0xdd
0x251a000a4:	ldr	x8, [x10, w8, sxtw #3]
0x251a000a8:	sub	x28, x8, #0xc
0x251a000ac:	ldr	x8, [x28, w11, uxtw #3]
0x251a000b0:	add	x0, sp, #8
0x251a000b4:	mov	x17, #0xf9e7
0x251a000b8:	blraa	x8, x17
0x251a000bc:	ldr	w8, [sp, #8]
0x251a000c0:	mov	w9, #0x14f8
0x251a000c4:	movk	w9, #0x1455, lsl #16
0x251a000c8:	cmp	w8, w9
0x251a000cc:	cset	w9, eq
0x251a000d0:	mov	w10, #0x26
0x251a000d4:	mul	w9, w9, w10
0x251a000d8:	mov	w10, #0x1de
0x251a000dc:	eor	w9, w9, w10
0x251a000e0:	ldr	x9, [x28, w9, uxtw #3]
0x251a000e4:	mov	x17, #0x3aba
0x251a000e8:	braa	x9, x17
0x251a000ec:	add	w8, w10, #0x1e2
0x251a000f0:	ldrb	w9, [x15, #0xc]
0x251a000f4:	and	w11, w8, #0xff
0x251a000f8:	mov	w12, #0xaa
0x251a000fc:	eor	w11, w11, w12
0x251a00100:	cmp	w9, w11
0x251a00104:	cset	w9, hi
0x251a00108:	add	w11, w10, #0x20c
0x251a0010c:	mul	w9, w9, w11
0x251a00110:	eor	w9, w9, w10
0x251a00114:	ldr	x10, [x20, w9, sxtw #3]
0x251a00118:	mov	w9, #0x7097
0x251a0011c:	movk	w9, #0x1454, lsl #16
0x251a00120:	mov	x17, #0xb8e2
0x251a00124:	braa	x10, x17
0x251a00128:	add	x30, x30, #1
0x251a0012c:	add	x11, x11, #0x80
0x251a00130:	b	#0x2519ec3bc
0x251a00134:	ldr	w9, [sp, #0x8c]
0x251a00138:	sub	w8, w9, #0xcd
0x251a0013c:	sub	w9, w9, #0x363
0x251a00140:	sub	x10, x29, #0xf0
0x251a00144:	str	x10, [sp, #0x18]
0x251a00148:	ldur	w10, [x29, #-0x98]
0x251a0014c:	mov	w11, #0x29d
0x251a00150:	eor	w11, w8, w11
0x251a00154:	and	x11, x11, x10
0x251a00158:	add	w13, w11, #1
0x251a0015c:	sub	x10, x29, #0xdc
0x251a00160:	add	x10, x10, x11
0x251a00164:	mov	w12, #0xf5
0x251a00168:	strb	w12, [x10]
0x251a0016c:	cmp	w11, #0x37
0x251a00170:	cset	w10, hi
0x251a00174:	mov	w12, #0x3c5
0x251a00178:	mul	w10, w10, w12
0x251a0017c:	eor	w9, w10, w9
0x251a00180:	ldr	x9, [x26, w9, sxtw #3]
0x251a00184:	mov	x17, #0xd853
0x251a00188:	braa	x9, x17
0x251a0018c:	ldr	x14, [sp, #0x170]
0x251a00190:	ldr	x19, [sp, #0x160]
0x251a00194:	ldr	w23, [sp, #0x190]
0x251a00198:	b	#0x251a0e91c

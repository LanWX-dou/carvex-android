; accessoryd 0x1000b2f94-0x1000b3068; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x1000b2f94:	pacibsp	
0x1000b2f98:	sub	sp, sp, #0x40
0x1000b2f9c:	stp	x22, x21, [sp, #0x10]
0x1000b2fa0:	stp	x20, x19, [sp, #0x20]
0x1000b2fa4:	stp	x29, x30, [sp, #0x30]
0x1000b2fa8:	add	x29, sp, #0x30
0x1000b2fac:	mov	x21, x1
0x1000b2fb0:	mov	x22, x0
0x1000b2fb4:	strb	w2, [sp, #0xf]
0x1000b2fb8:	adrp	x2, #0x10022b000
0x1000b2fbc:	ldr	x2, [x2, #0xd40]
0x1000b2fc0:	adrp	x3, #0x10022b000
0x1000b2fc4:	ldr	x3, [x3, #0xd48]
0x1000b2fc8:	mov	x0, #0
0x1000b2fcc:	mov	x1, #0
0x1000b2fd0:	bl	#0x1001a1630
0x1000b2fd4:	mov	x19, x0
0x1000b2fd8:	adrp	x8, #0x10022b000
0x1000b2fdc:	ldr	x8, [x8, #0xce0]
0x1000b2fe0:	ldr	x0, [x8]
0x1000b2fe4:	add	x2, sp, #0xf
0x1000b2fe8:	mov	w1, #7
0x1000b2fec:	bl	#0x1001a17a0
0x1000b2ff0:	mov	x20, x0
0x1000b2ff4:	adrp	x8, #0x10021a000
0x1000b2ff8:	add	x8, x8, #0x2c0
0x1000b2ffc:	ldr	x1, [x8]
0x1000b3000:	mov	x0, x19
0x1000b3004:	mov	x2, x21
0x1000b3008:	bl	#0x1001a15e0
0x1000b300c:	adrp	x8, #0x10021a000
0x1000b3010:	add	x8, x8, #0x2d8
0x1000b3014:	ldr	x1, [x8]
0x1000b3018:	mov	x0, x19
0x1000b301c:	mov	x2, x20
0x1000b3020:	bl	#0x1001a15e0
0x1000b3024:	mov	x0, x22
0x1000b3028:	mov	w1, #0x12e
0x1000b302c:	mov	x2, x19
0x1000b3030:	bl	#0x1000022a4
0x1000b3034:	mov	x21, x0
0x1000b3038:	cbz	x20, #0x1000b3044
0x1000b303c:	mov	x0, x20
0x1000b3040:	bl	#0x1001a1820
0x1000b3044:	cbz	x19, #0x1000b3050
0x1000b3048:	mov	x0, x19
0x1000b304c:	bl	#0x1001a1820
0x1000b3050:	mov	x0, x21
0x1000b3054:	ldp	x29, x30, [sp, #0x30]
0x1000b3058:	ldp	x20, x19, [sp, #0x20]
0x1000b305c:	ldp	x22, x21, [sp, #0x10]
0x1000b3060:	add	sp, sp, #0x40
0x1000b3064:	retab	

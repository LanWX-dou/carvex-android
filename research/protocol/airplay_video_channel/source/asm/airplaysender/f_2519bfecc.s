; airplaysender 0x2519bfecc-0x2519bffc8; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519bfecc:	pacibsp	
0x2519bfed0:	sub	sp, sp, #0x60
0x2519bfed4:	stp	x24, x23, [sp, #0x20]
0x2519bfed8:	stp	x22, x21, [sp, #0x30]
0x2519bfedc:	stp	x20, x19, [sp, #0x40]
0x2519bfee0:	stp	x29, x30, [sp, #0x50]
0x2519bfee4:	add	x29, sp, #0x50
0x2519bfee8:	mov	x21, x5
0x2519bfeec:	mov	x22, x4
0x2519bfef0:	mov	x20, x3
0x2519bfef4:	mov	x24, x2
0x2519bfef8:	mov	x23, x0
0x2519bfefc:	str	xzr, [sp, #0x18]
0x2519bff00:	adrp	x8, #0x251bdf000
0x2519bff04:	add	x8, x8, #0x648
0x2519bff08:	stp	x8, x1, [sp]
0x2519bff0c:	adrp	x1, #0x251bdf000
0x2519bff10:	add	x1, x1, #0x641
0x2519bff14:	add	x0, sp, #0x18
0x2519bff18:	bl	#0x25810a1a0
0x2519bff1c:	sxtw	x19, w0
0x2519bff20:	ldr	x1, [sp, #0x18]
0x2519bff24:	adrp	x3, #0x251bdf000
0x2519bff28:	add	x3, x3, #0x658
0x2519bff2c:	mov	x0, x23
0x2519bff30:	mov	x2, x19
0x2519bff34:	mov	w4, #0x1f
0x2519bff38:	mov	x5, x24
0x2519bff3c:	mov	x6, x20
0x2519bff40:	bl	#0x2519bffc8
0x2519bff44:	cbnz	w0, #0x2519bffb0
0x2519bff48:	ldr	x1, [sp, #0x18]
0x2519bff4c:	adrp	x3, #0x251bdf000
0x2519bff50:	add	x3, x3, #0x6a9
0x2519bff54:	mov	x0, x23
0x2519bff58:	mov	x2, x19
0x2519bff5c:	mov	w4, #0x20
0x2519bff60:	mov	x5, x22
0x2519bff64:	mov	x6, x21
0x2519bff68:	bl	#0x2519bffc8
0x2519bff6c:	mov	x20, x0
0x2519bff70:	cbnz	w0, #0x2519bffbc
0x2519bff74:	ldr	x0, [sp, #0x18]
0x2519bff78:	cbz	w19, #0x2519bff8c
0x2519bff7c:	strb	wzr, [x0], #1
0x2519bff80:	subs	x19, x19, #1
0x2519bff84:	b.ne	#0x2519bff7c
0x2519bff88:	ldr	x0, [sp, #0x18]
0x2519bff8c:	cbz	x0, #0x2519bff94
0x2519bff90:	bl	#0x2580f4d30
0x2519bff94:	mov	x0, x20
0x2519bff98:	ldp	x29, x30, [sp, #0x50]
0x2519bff9c:	ldp	x20, x19, [sp, #0x40]
0x2519bffa0:	ldp	x22, x21, [sp, #0x30]
0x2519bffa4:	ldp	x24, x23, [sp, #0x20]
0x2519bffa8:	add	sp, sp, #0x60
0x2519bffac:	retab	
0x2519bffb0:	mov	x20, x0
0x2519bffb4:	bl	#0x251b4c2c8
0x2519bffb8:	b	#0x2519bff74
0x2519bffbc:	mov	x0, x20
0x2519bffc0:	bl	#0x251b4c2f0
0x2519bffc4:	b	#0x2519bff74

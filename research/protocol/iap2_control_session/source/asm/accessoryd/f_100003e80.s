; accessoryd 0x100003e80-0x100003ee0; source SHA256 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x100003e80:	pacibsp	
0x100003e84:	stp	x22, x21, [sp, #-0x30]!
0x100003e88:	stp	x20, x19, [sp, #0x10]
0x100003e8c:	stp	x29, x30, [sp, #0x20]
0x100003e90:	add	x29, sp, #0x20
0x100003e94:	ldp	x8, x20, [x0, #0x18]
0x100003e98:	sub	x8, x20, x8
0x100003e9c:	add	x8, x8, #5
0x100003ea0:	ldr	w9, [x0, #0x10]
0x100003ea4:	cmp	x8, x9
0x100003ea8:	csel	x21, xzr, x20, gt
0x100003eac:	cbz	x21, #0x100003ecc
0x100003eb0:	mov	x19, x3
0x100003eb4:	mov	x5, x1
0x100003eb8:	mov	x1, x20
0x100003ebc:	mov	w3, #3
0x100003ec0:	mov	w4, #5
0x100003ec4:	bl	#0x100003a68
0x100003ec8:	strb	w19, [x20, #4]
0x100003ecc:	mov	x0, x21
0x100003ed0:	ldp	x29, x30, [sp, #0x20]
0x100003ed4:	ldp	x20, x19, [sp, #0x10]
0x100003ed8:	ldp	x22, x21, [sp], #0x30
0x100003edc:	retab	

; APTransport 0x24fda6c70-0x24fda6cdc; source SHA256 e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x24fda6c70:	pacibsp	
0x24fda6c74:	stp	x22, x21, [sp, #-0x30]!
0x24fda6c78:	stp	x20, x19, [sp, #0x10]
0x24fda6c7c:	stp	x29, x30, [sp, #0x20]
0x24fda6c80:	add	x29, sp, #0x20
0x24fda6c84:	mov	x19, x1
0x24fda6c88:	bl	#0x2500e5a60
0x24fda6c8c:	mov	x21, x0
0x24fda6c90:	ldr	x20, [x0]
0x24fda6c94:	cbz	x19, #0x24fda6ca0
0x24fda6c98:	mov	x0, x19
0x24fda6c9c:	bl	#0x2500903e0
0x24fda6ca0:	str	x19, [x21]
0x24fda6ca4:	cbz	x20, #0x24fda6ccc
0x24fda6ca8:	mov	x0, x20
0x24fda6cac:	ldp	x29, x30, [sp, #0x20]
0x24fda6cb0:	ldp	x20, x19, [sp, #0x10]
0x24fda6cb4:	ldp	x22, x21, [sp], #0x30
0x24fda6cb8:	autibsp	
0x24fda6cbc:	eor	x16, x30, x30, lsl #1
0x24fda6cc0:	tbz	x16, #0x3e, #0x24fda6cc8
0x24fda6cc4:	brk	#0xc471
0x24fda6cc8:	b	#0x2500903d0
0x24fda6ccc:	ldp	x29, x30, [sp, #0x20]
0x24fda6cd0:	ldp	x20, x19, [sp, #0x10]
0x24fda6cd4:	ldp	x22, x21, [sp], #0x30
0x24fda6cd8:	retab	

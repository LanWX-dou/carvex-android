; airplaysender 0x251a779d8-0x251a779f0; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a779d8:	cmp	w2, #0
0x251a779dc:	mov	w8, #0x28
0x251a779e0:	mov	w9, #0x20
0x251a779e4:	csel	x8, x9, x8, eq
0x251a779e8:	ldr	x0, [x0, x8]
0x251a779ec:	b	#0x258030ce0

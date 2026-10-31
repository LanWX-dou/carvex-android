; AirPlaySender 0x251a57ffc-0x251a5804c; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x251a57ffc:	pacibsp	
0x251a58000:	sub	sp, sp, #0x30
0x251a58004:	stp	x20, x19, [sp, #0x10]
0x251a58008:	stp	x29, x30, [sp, #0x20]
0x251a5800c:	add	x29, sp, #0x20
0x251a58010:	mov	x19, x1
0x251a58014:	mov	x20, x0
0x251a58018:	bl	#0x25810ac50
0x251a5801c:	stp	x20, x19, [sp]
0x251a58020:	ldr	x0, [x0, #0x78]
0x251a58024:	adrp	x16, #0x2519c4000
0x251a58028:	add	x16, x16, #0x688
0x251a5802c:	paciza	x16
0x251a58030:	mov	x1, x16
0x251a58034:	mov	x2, sp
0x251a58038:	bl	#0x25810d260
0x251a5803c:	ldp	x29, x30, [sp, #0x20]
0x251a58040:	ldp	x20, x19, [sp, #0x10]
0x251a58044:	add	sp, sp, #0x30
0x251a58048:	retab	

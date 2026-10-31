; AirPlaySender 0x2519c1b94-0x2519c1bb8; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519c1b94:	add	x8, x0, #0x18
0x2519c1b98:	add	x9, x0, #0x98
0x2519c1b9c:	ldsetal	wzr, w9, [x9]
0x2519c1ba0:	add	x10, x8, x9, lsl #6
0x2519c1ba4:	ldp	q0, q1, [x10]
0x2519c1ba8:	ldp	q2, q3, [x10, #0x20]
0x2519c1bac:	stp	q2, q3, [x1, #0x20]
0x2519c1bb0:	stp	q0, q1, [x1]
0x2519c1bb4:	ret	

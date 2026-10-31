; APTransport 0x24fdfad5c-0x24fdfad70; source SHA256 e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x24fdfad5c:	lsl	x8, x1, #0x20
0x24fdfad60:	orr	x8, x8, x0, lsl #48
0x24fdfad64:	mov	w9, w2
0x24fdfad68:	orr	x0, x8, x9
0x24fdfad6c:	ret	

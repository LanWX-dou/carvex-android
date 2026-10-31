; AirPlaySender 0x2519c18f0-0x2519c19b4; source SHA256 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x2519c18f0:	pacibsp	
0x2519c18f4:	stp	x26, x25, [sp, #-0x50]!
0x2519c18f8:	stp	x24, x23, [sp, #0x10]
0x2519c18fc:	stp	x22, x21, [sp, #0x20]
0x2519c1900:	stp	x20, x19, [sp, #0x30]
0x2519c1904:	stp	x29, x30, [sp, #0x40]
0x2519c1908:	add	x29, sp, #0x40
0x2519c190c:	mov	x19, x7
0x2519c1910:	mov	x21, x6
0x2519c1914:	mov	x20, x5
0x2519c1918:	mov	x23, x4
0x2519c191c:	mov	x25, x3
0x2519c1920:	mov	x22, x2
0x2519c1924:	mov	x24, x1
0x2519c1928:	bl	#0x25810ac50
0x2519c192c:	ldrb	w8, [x24, #0x88]
0x2519c1930:	tbz	w8, #0, #0x2519c198c
0x2519c1934:	cbnz	x23, #0x2519c1994
0x2519c1938:	ldr	w8, [x0, #0x50]
0x2519c193c:	mul	w23, w8, w20
0x2519c1940:	cmp	x25, x23
0x2519c1944:	b.lo	#0x2519c199c
0x2519c1948:	ldr	d0, [x24, #0x50]
0x2519c194c:	fcvtzu	x1, d0
0x2519c1950:	ldr	x0, [x0, #8]
0x2519c1954:	mov	x2, x22
0x2519c1958:	mov	x3, x23
0x2519c195c:	bl	#0x25810dac0
0x2519c1960:	mov	x22, x0
0x2519c1964:	cbnz	w0, #0x2519c19a8
0x2519c1968:	str	x23, [x21]
0x2519c196c:	str	w20, [x19]
0x2519c1970:	mov	x0, x22
0x2519c1974:	ldp	x29, x30, [sp, #0x40]
0x2519c1978:	ldp	x20, x19, [sp, #0x30]
0x2519c197c:	ldp	x22, x21, [sp, #0x20]
0x2519c1980:	ldp	x24, x23, [sp, #0x10]
0x2519c1984:	ldp	x26, x25, [sp], #0x50
0x2519c1988:	retab	
0x2519c198c:	bl	#0x251bcc45c
0x2519c1990:	b	#0x2519c19a0
0x2519c1994:	bl	#0x251bcc424
0x2519c1998:	b	#0x2519c19a0
0x2519c199c:	bl	#0x251bcc448
0x2519c19a0:	mov	w22, #-0x4198
0x2519c19a4:	b	#0x2519c1970
0x2519c19a8:	mov	x0, x22
0x2519c19ac:	bl	#0x251bcc438
0x2519c19b0:	b	#0x2519c1970

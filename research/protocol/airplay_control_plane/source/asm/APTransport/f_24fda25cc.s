; APTransport 0x24fda25cc-0x24fda2688; source SHA256 e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d; original firmware bytes
; disassembly: Capstone 5.0.7 CS_ARCH_ARM64; no rewriting
; unreviewed: 未人工确认（机器输出，字节为固件原始值）
0x24fda25cc:	pacibsp	
0x24fda25d0:	stp	x26, x25, [sp, #-0x50]!
0x24fda25d4:	stp	x24, x23, [sp, #0x10]
0x24fda25d8:	stp	x22, x21, [sp, #0x20]
0x24fda25dc:	stp	x20, x19, [sp, #0x30]
0x24fda25e0:	stp	x29, x30, [sp, #0x40]
0x24fda25e4:	add	x29, sp, #0x40
0x24fda25e8:	mov	x19, x5
0x24fda25ec:	mov	x22, x4
0x24fda25f0:	mov	x23, x3
0x24fda25f4:	mov	x20, x2
0x24fda25f8:	mov	x21, x1
0x24fda25fc:	mov	x24, x0
0x24fda2600:	bl	#0x2500efc20
0x24fda2604:	mov	x25, x0
0x24fda2608:	mov	x0, x24
0x24fda260c:	mov	x1, x21
0x24fda2610:	mov	x2, x20
0x24fda2614:	bl	#0x2500efc10
0x24fda2618:	mov	x20, x0
0x24fda261c:	mov	x0, x23
0x24fda2620:	mov	x1, x22
0x24fda2624:	mov	x2, x19
0x24fda2628:	bl	#0x2500efc20
0x24fda262c:	mov	x21, x0
0x24fda2630:	mov	x0, x23
0x24fda2634:	mov	x1, x22
0x24fda2638:	mov	x2, x19
0x24fda263c:	bl	#0x2500efc10
0x24fda2640:	cbz	w25, #0x24fda2650
0x24fda2644:	cbz	w20, #0x24fda2664
0x24fda2648:	mov	w0, #0
0x24fda264c:	b	#0x24fda2670
0x24fda2650:	cmp	w21, #0
0x24fda2654:	ccmp	w0, #0, #4, ne
0x24fda2658:	cset	w0, eq
0x24fda265c:	b.eq	#0x24fda2670
0x24fda2660:	cbnz	w20, #0x24fda2670
0x24fda2664:	ldrb	w8, [x19]
0x24fda2668:	cmp	w8, #0
0x24fda266c:	cset	w0, eq
0x24fda2670:	ldp	x29, x30, [sp, #0x40]
0x24fda2674:	ldp	x20, x19, [sp, #0x30]
0x24fda2678:	ldp	x22, x21, [sp, #0x20]
0x24fda267c:	ldp	x24, x23, [sp, #0x10]
0x24fda2680:	ldp	x26, x25, [sp], #0x50
0x24fda2684:	retab	

	TTL Bitoperators
	AREA program, CODE, READONLY
	ENTRY
	
	
	LDR r0, =0x20000000
	LDR r1, =0x80000000 ;negtif sayi(isaret biti dolu)
	ADDS r2, r0,r1
	END
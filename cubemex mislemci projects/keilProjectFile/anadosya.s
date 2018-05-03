	TTL Bitoperators
	AREA program, CODE, READONLY
	ENTRY
	
	
	LDR r0, =0xC0000000
	LDR r1, =0x80000000
	ADDS r2, r0,r1
	END
	
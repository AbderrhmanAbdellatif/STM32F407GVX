	TTL ders6
	AREA program, CODE,READONLY
	ENTRY
	
	LDR r0,=0xCDAB1E9B
	LDR r3,=0x6A289924 ; Bic maskesi
	BIC r0,r0,r3

	END
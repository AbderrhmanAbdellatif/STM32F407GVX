	TTL Ders7
	AREA Program, CODE, READONLY
	ENTRY

	LDR r1,=4	;x=4
	LDR r2,=5	;y=5
	MOV r0,#1	;result
	
	MOVS r2,r2	;r2=0 (x^0) ise Z=1 -> BEQ true -> sonagit
	
basadon	
   	BEQ sonagit
	MUL r0,r1,r0	;result *=x
	SUBS r2,r2,#1	;y--
	B basadon
sonagit	
	END


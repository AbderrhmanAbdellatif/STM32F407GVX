	TTL Ders7
	AREA Program, CODE ,READONLY
	ENTRY
	
	MOV r0,#9	;N! sayisi 	
	MOV r1,#1	;result 
	MOV r2,r0	;temp =N
basagit	
	CMP r2,#1	;while(temp>1)
	BGT wh1		;eger r0 greater than 1 -> go to wh1
	B son		;degilse ->  cik

wh1
	MUL r1,r2,r1 ; result= result*temp
	SUB r2,r2,#1 ;temp--	
	B basagit
son
	END
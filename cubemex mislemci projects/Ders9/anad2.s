	TTL ders9
	AREA  PROGRAM, CODE	
	ENTRY
	
	;byte [] b=new b[20];
	;// b array i için memory adresi 0x10000000
	;for (int i=0; i<b.length;i++){
		;b[i]=(byte)(i+1);
	;}
	
	LDR R1,=0X00000001 ; base adress of byte array
	;MOV r2,#1				;count
;loop	
	;CMP r2,#21
	;BGE cik 				;greater or equal
	;STRB r2,[r1],#1 	;birer birer artar ç. byte
	;ADD r2,r2,#1
	;B loop
;cik	
	MOV r2,#1
	MOV r3,#2
	MOV r4,#0
loop	
	CMP r2,#10
	BGE exit
	;STRH r3,[R1],#2
	;MUL r3,r2,r2
	LDRB r4,[R1],#1
	ADD r4,r4
	ADD r2,r2,#1
	B loop
exit	
	END
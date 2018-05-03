	TTL ders9
	AREA  PROGRAM, CODE	
	ENTRY
	
	;byte [] b=new b[20];
	;// b array i için memory adresi 0x10000000
	;for (int i=0; i<b.length;i++){
		;b[i]=(byte)(i+1);
	;}
	
	LDR R1,=0X10000000 ; base adress of byte array
	MOV r2,#1				;count
loop	
	CMP r2,#21
	BGE cik 				;greater or equal
	STRB r2,[r1],#1 	;birer birer artar ç. byte
	ADD r2,r2,#1
	B loop
cik	
	
	
	END
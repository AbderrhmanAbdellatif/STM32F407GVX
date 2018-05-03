	TTL Ders7
	AREA Program,CODE , READONLY
	ENTRY

	;int sayi =150;
	;if(sayi< 50){
	;  sayi+=10;
	;}else if(sayi ==40){
	;  sayi-=40;
	;}else{
	;  sayi*=90
	;}
	; >> sayi =13500 = 0x34BC
	MOV r0,#150
	MOV r1,#90

	CMP r0,#50
	BGE elseif
	ADD r0,r0,#10
	B end_if  ; yazmazsam diger else e girer
elseif	
	CMP r0,#40
	BNE _else
	SUB r0,r0,#40 ; yada ,#-40
	B end_if
_else
	MUL r0,r1,r0
end_if	
	
	END
	TTL ders
	AREA Program, CODE, READONLY
	ENTRY

 	MOV r9,#2_01011010  ; comment:sayi1
	MOV r10,#0xB4 ; immid. data tasimada 255 den fazla tasiyamaz
	MOV r11,#15
	MOV r8,#56
	MOV r7,#0	; toplam degiskeni
	ADD r5,r5,r9
	ADD r5,r5,r10
	ADD r5,r5,r11
	ADD r5,r5,r8
stop B stop	
	END
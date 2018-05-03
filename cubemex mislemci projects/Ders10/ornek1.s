	TTL	Ders8AdressingMode
	AREA	Program, CODE
	ENTRY	

	;short array[] = new short[15];
        ;int i;
        ;for (i = 0; i < 15; i++) {
            ;array[i] = (short) (i + 1);
            ;System.out.printf("%d ", array[i]);
        ;}
        ;System.out.println("\n ");
		
		;ornek 1: bir byte yazmak : 01 00 02 00..
	;LDR r1, =0x10000000		; based address of array
	;MOV r2,#1	; counter
;devam
	;CMP r2,#15
	;BHI cik  ; higher 
	;STRH r2,[r1],#2
	;ADD r2,r2,#1
	;B devam
;cik

;ornek2: 2byte yazmak :
	
	LDR r1, =0x10000000		; based address of array
	MOV r2,#1	; counter
	LDR r4,=0xBFA ;short u asmaz ç. short 2 byte(16 bit)(half word)(0x0BFA) bu da hatta 12 bit

devam
	CMP r2,#15
	BHI cik  ; higher 
	STRH r4,[r1],#2
	;ADD r2,r2,#1
	ADD r4,r4,#5
	
	B devam
cik

;ornek 3: arrayin o ndaki elemanina k ekle: -------
;int k = 34;



	LDR r1, =0x00001000	; based address of array


	END
	TTL Ders7
	AREA Program, CODE, READONLY
	ENTRY

	LDR r0,=0xAAAAAAA	;MOV 1 byteten daha tasiyamaz
	MOV r1,#0		;counter
basagit	
	CMP r1,#20	;while(counter <20)	
	BGE bitir	;{ bigger or eq 
	LSRS r0,r0,#1 ;S flag guncellensin
	ADD r1,r1,#1
	B basagit
bitir	
	
	END
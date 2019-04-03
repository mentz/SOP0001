!  testa divisibilidade em Assembly as88
!
!  (c) rro, 2015-02-25
!
!  para montar o programa:
!    $ ./as88 diviserr.s readnum.s

#include "../syscalnr.h"              

.SECT .TEXT

start:
	MOV	BP,SP		
	PUSH	pr1		
	PUSH	_PRINTF		
	SYS			

	CALL	readnum		
	MOV	(x),AX		

	PUSH	pr2		
	PUSH	_PRINTF		
	SYS			

	CALL	readnum		
	MOV	(y),AX		

	MOV	CX,(x)		
	MOV	DX,0		
	MOV	AX,(y)		
        IDIV    CX              
        CMP     DX,0		
        JNZ     divisivel       

ndivisivel:
	MOV	BX,str_ndiv	
        JMP     imprime
	
divisivel: 
	MOV    	BX,str_div	
	
imprime:
	PUSH	pr3		
	PUSH	(x)		
	PUSH	BX		
	PUSH	(y)		
	PUSH	_PRINTF
	SYS

encerra:    
	MOV	SP,BP		
	PUSH	0		
	PUSH	_EXIT		
	SYS			
fim:
	
.SECT	.DATA
pr1:		.ASCIZ	'Entre o 1o numero: '
pr2:		.ASCIZ	'Entre o 2o numero: '
str_div:	.ASCIZ	'eh'
str_ndiv:	.ASCIZ	'nao eh'
pr3:		.ASCIZ	'\n%d %s divisivel por %d\n'
x:		.WORD	0
y:		.WORD	0

.SECT	.BSS

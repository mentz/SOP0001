!  testa divisibilidade em Assembly as88
!
!  (c) rro, 2015-02-25
!
!  para montar o programa:
!    $ ./as88 divis.s readnum.s

#include "../syscalnr.h"              

.SECT .TEXT

start:
	MOV	BP,SP		! salva SP
	PUSH	pr1		! endereco da string
	PUSH	_PRINTF		! no. da syscall
	SYS			! executa syscall 

	CALL	readnum		! le string e converte para numero
	MOV	(x),AX		! armazena o numero lido em 'x'

	PUSH	pr2		! endereco da string
	PUSH	_PRINTF		! no. da syscall
	SYS			! executa syscall 

	CALL	readnum		! le string e converte para numero
	MOV	(y),AX		! armazena o numero lido em 'y'

	MOV	CX,AX		! divisor em CX (y)
	MOV	DX,0		! dividendo=DX:AX - DX=0, AX=x
	MOV	AX,(x)		! 
        IDIV    CX              ! quociente em AX, resto em DX
        CMP     DX,0		! compara DX com 0
        JZ      divisivel       ! se for igual, e' divisivel

ndivisivel:
	MOV	BX,str_ndiv	! BX=end de "nao eh"
        JMP     imprime
	
divisivel: 
	MOV    	BX,str_div	! BX=end de "eh"
	
imprime:
	PUSH	(y)		! valor de y
	PUSH	BX		! endereco da string
	PUSH	(x)		! valor de x
	PUSH	pr3		! 1o argumento de printf() e' pr3
	PUSH	_PRINTF
	SYS

encerra:    
	MOV	SP,BP		! limpa pilha
	PUSH	0		! codigo de retorno=0
	PUSH	_EXIT		
	SYS			! encerra o programa
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

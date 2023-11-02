.section .text
.globl lab02d

lab02d:
	ADD X0, X0, #1000 //adding 1000 to the passed in value
	ADRP X2, myvalue
	ADD X2, X2, :lo12:myvalue
	STUR X0,[X2,0]
	ORR X0, XZR, X2
	BR X30

 .section       	.data
  	myvalue:	.word 
        

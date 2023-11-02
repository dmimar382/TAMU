.globl lab03b

lab03b:
    ADRP X0, UIN
    ADD X0, X0, :lo12:UIN //loads in the address of UIN into X0
    LDUR X1, [X0,0] //load the value of UIN into X1
    ORR X3, XZR, XZR //i = 0 = X3
    ADD X4, X3, #10 // X4 = 10
    
loop:
    SUB X5, X4, X3 // 10 - i and store in X5
    CBZ X5, finish // if X5 = 0, finish     
    SUB X1, X1, #1 //else, subtract 1 from UIN    
    ADD X3, X3, #1 //i++         
    B loop //loop back 

finish:
    STUR X1, [X0,0] //storing the result in X0
    LDUR X0, [X0,0] //loading the value of X0 into X0         
    BR X30

.section .data
UIN: .word 38 //UIN: 927009911




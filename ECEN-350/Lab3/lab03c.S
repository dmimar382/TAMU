.globl lab03c

lab03c:
    ADRP X0, my_array
    ADD X0, X0, :lo12:my_array //loads in the address of my_array into X0
    //LDUR X1, [X0,0] //load the value of UIN into X1
    ORR X3, XZR, XZR //i = 0 = X3
    ADD X4, X3, #9 // j = 9
    
loop:
    CMP X3, #10 //compares i and 10
    B.GE finish // if i > 10, go to finish
    STUR X4, [X0,0] //Storing j in my_array[i]
    ADD X4, X4, #1 //increment j by 1  
    ADD X3, X3, #1 //increment i by 1 bytes   
    ADD X0, X0, #4 //increment address by 4 bytes to place the next j value          
    B loop //loop back 

finish:    
    BR X30

.section .data
my_array: .space 40 //allocating space for an array of size 10, filling the aray with the default value 0




`timescale 1ns/ 1ps
`default_nettype none

module adder_2bit(
    output wire Carry,
    output wire [1:0] Sum, 
    input wire [1:0] A,B
    );

    //define interrnal nets
    wire Cin;

    full_adder add0(Sum[0],Cin,A[0],B[0], 1'b0);//calls full adder function
    full_adder add1(Sum[1],Carry,A[1],B[1],Cin);

endmodule //designate end of module    
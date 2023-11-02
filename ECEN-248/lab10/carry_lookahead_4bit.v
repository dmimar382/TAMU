`timescale 1ns/1ps
`default_nettype none
 //This is the top-level module 
module carry_lookahead_4bit(Cout, S, X, Y, Cin);

    output wire Cout; //C_4 for a 4-bit adder
    output wire [3:0] S; //final 4-bit sum vector
    input wire [3:0] X, Y; //4-bit addends
    input wire Cin; //input carry in 

    wire [3:0] G, P;
    wire [4:0] C;

    assign C[0] = Cin;
    
    //instantiate previous modules 
    generate_propagate_unit gpu(G, P, X, Y);
    carry_lookahead_unit clu(C[4:1], G, P, C[0]);
    summation_unit sum(S, P, C[3:0]);
    
    assign Cout= C[4];

endmodule //designate end of module
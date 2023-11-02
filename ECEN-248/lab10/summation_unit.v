`timescale 1ns/1ps
`default_nettype none

module summation_unit(S, P, C);

    output wire [15:0] S; //sum vector 
    input wire [15:0] P, C; //propogate and carry vectors

    assign #2 S = P ^ C;

endmodule //designate end of module 
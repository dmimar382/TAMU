//This module describes the generate propogate unit 
`timescale 1ns/1ps
`default_nettype none

module generate_propagate_unit(G, P, X, Y);

    //ports are wires as we will use dataflow
    output wire [3:0] G, P;
    input wire [3:0] X, Y;
    
    //define internal nets
    assign G = X & Y;
    assign P = X ^ Y;

endmodule //designate end of module
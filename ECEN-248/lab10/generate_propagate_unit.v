`timescale 1ns/1ps
`default_nettype none

//This module describes the generate propogate unit 
module generate_propagate_unit(G, P, X, Y);

    //ports are wires as we will use dataflow
    output wire [15:0] G, P;
    input wire [15:0] X, Y;
    
    //define internal nets
    assign #2 G = X & Y;
    assign #2 P = X ^ Y;

endmodule //designate end of module
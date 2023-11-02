//this module describes the carry look ahead unit 
`timescale 1ns/1ps
`default_nettype none

module carry_lookahead_unit(C, G, P, C0);

    output wire [4:1] C; //C4,C3,C2,C1
    input wire [3:0] G, P; //generates and propogates 
    input wire C0; //input carry in
    
    //define internal nets 
    assign #4  C[1] = G[0] | (P[0] & C0);
    assign #4  C[2] = G[1] | (G[0] & P[1]) | (C0 & P[0] & P[1]);
    assign #4  C[3] = G[2] | (G[1] & P[2]) | (G[0] & P[1] & P[2]) | (C0 & P[0] & P[1] & P[2]);
    assign #4  C[4] = G[3] | (G[2] & P[3]) | (G[1] & P[2] & P[3]) | (G[0] & P[1] & P[2] & P[3]) | (C0 & P[0] & P[1] & P[2] & P[3]);

endmodule //designate end of module 
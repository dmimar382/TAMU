`timescale 1ns/1ps
`default_nettype none

//This module describes the block carry-lookahead unit
// for a 2-level carry lookahead adder

module block_carry_lookahead_unit(G_star, P_star, C, G, P, C0);

    //ports are wires because we will use dataflow
    output wire G_star, P_star; //block generate and propagate
    output wire [3:1] C; //C3,C2,C1
    input wire [3:0] G,P; //generates and propagates
    input wire C0; //input carry
    
    //define internal nets 
    assign #4 C[1] = G[0] | ( P[0] & C0 );
    assign #4 C[2] = G[1] | ( G[0] & P[1]) | ( P[1] & P[0] & C0 );
    assign #4 C[3] = G[2] | ( G[1] & P[2]) | ( G[0] & P[1] & P[2]) | ( P[2] & P[1] & P[0] & C0 );
    
    assign #4 G_star = G[3] | ( G[2] & P[3]) | ( G[1] & P[2] & P[3]) | ( P[1] & P[2] & P[3] & G[0]);
    assign #2 P_star = P[3] & P[2] & P[1] & P[0];

endmodule //designate end of module
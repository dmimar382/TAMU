`timescale 1ns/1ps //delay unit is 1ns

module d_flip_flop_behavioral(
output reg Q, //described in behavioral statement
output wire notQ, //described in a dataflow statement 
input wire D, 
input wire Clk //clock signal 
);

//describe behavior of D flip-flop
//posedge means positive(rising) edge
always@(posedge Clk) //trigger when rising edge of Clk
Q<=D;   //non-block assignemnt statement 

assign notQ = ~Q;

endmodule //designate end of module
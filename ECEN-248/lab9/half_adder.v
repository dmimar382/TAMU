`timescale 1ns/1ps
`default_nettype none

//demonstrates the workings of a half adder using dataflow verilog
module half_adder(S,Cout,A,B);

//declare input and output ports
input wire A,B;
output wire S, Cout;
//declare internal nets
wire andAB;

//assign values 
assign S = A^B;
assign andAB = A&B;
assign Cout = andAB;

endmodule //designate end of module 
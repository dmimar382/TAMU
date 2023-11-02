`timescale 1ns / 1ps
`default_nettype none

/*This simple module will demonstrate the concept of clock frequency *
* division using a simple counter. We will use behavioral Verilog *
* for our circuit description. */

module clock_divider(ClkOut, ClkIn);

/*output port needs to be a reg because we will drive it with a behavioral statement*/
output wire [3:0] ClkOut;
input wire ClkIn; // wires can drive regs

//this is a keyword we have not seen yet
//as the name implies, it is a parameter that is changed at compile time
parameter n = 25; //make count 6 bits for now

reg [n:0] Count; //count bit width is based on n. 

//simple behavioral construct to describe a counter
always@(posedge ClkIn)
Count <= Count +1; //thats it

//now we need to wire up our ClkOut which is a 4-bit wire
//Wire up most significant bits 
assign ClkOut [3:0] = Count[n:n-3];

endmodule //designate end of module
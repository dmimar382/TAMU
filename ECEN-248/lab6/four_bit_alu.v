`timescale 1ns/ 1ps
`default_nettype none

module four_bit_alu(
output wire [3:0] Result, //4 bit output
output wire Overflow, //1 bit signal for overflow
input wire [3:0] opA, opB, //4 bit operands
input wire [1:0] ctrl //2-bit operation select
);


//define internal nets 
wire [3:0] andAB; // 4-bit operation

//assign values to internal net wires 
assign andAB[0] = opA[0] & opB[0];
assign andAB[1] = opA[1] & opB[1];
assign andAB[2] = opA[2] & opB[2];
assign andAB[3] = opA[3] & opB[3];

wire [3:0] Sum; // add_sub Sum result
wire ADDSUBOF; //add_sub overflow wire

add_sub addsub(Sum, ADDSUBOF, opA, opB, ctrl[1]); /* calls back to add_sub program, sets*
* outputs as Sum and ADDSUBOF, and inputs as opA, opB and ctrl[1]*/

four_bit_mux mux(Result, andAB, Sum, ctrl[0]); // ouputs the result from the MUX
 
assign Overflow = ADDSUBOF & ctrl[0]; /*The overflow is equal to the *
*output of the add_sub unit AND operation selected*/ 

endmodule // designate end of module 
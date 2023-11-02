`timescale 1ns/1ps //specify 1ns for each delay unit


//This module describes a simple 3-bit up-counter
//using half-adder modules built in the previous step

module up_counter(Count,Carry2, En, Clk, Rst);

//Count output needs to be a reg
output reg [2:0] Count;
output wire Carry2;
//inputs are wires
input wire En,Clk,Rst;
//intermediate nets
wire [2:0] Carry,Sum;

//Lets create and instantiate a wrapper for the 3-bit counter first 
Threebit_counter UC1(Sum,Carry2,Count, En);

//Describe positive endge triggered flip-flops for count
//Including "posedge Rst" in the sensitivity list
//implies an asynchronous reset!

always@(posedge Clk or posedge Rst)
if (Rst) //if Rst ==1'b1
Count <= 0; //resent Count
else //otherwise, latch sum 
Count <= Sum;

endmodule //designate end of module 


module Threebit_counter(Sum,Carry2,Count,En);
//first we declare the variables
input wire En;
input wire [2:0] Count;
output wire [2:0] Sum;
output wire Carry2;
wire [2:0] Carry;

//instantiate and wire up half-adders
half_adder BitCount0(Sum[0], Carry[0], En, Count[0]);
half_adder BitCount1(Sum[1], Carry[1], Carry[0], Count[1]);
half_adder BitCount2(Sum[2], Carry[2], Carry[1], Count[2]);

assign Carry2=Carry[2];

endmodule //designate end of module

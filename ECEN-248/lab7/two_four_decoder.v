`timescale 1ns/1ps
`default_nettype none
/*This module describes a 2:4 decoder using behavioral constructs in Verilog HDL*/

//module interface for the 2:4 decoder
module two_four_decoder(
input wire [1:0] W,
input wire En, 
output reg [3:0] Y //Y is a 4-bit output of type reg
);

always@(En or W) //trigger when En or W changes 
begin 
    if (En ==1'b1)
    case(W) //selection based on W
        2'b00: Y= 4'b0001; //4'b signifies a 4-bit binary value 
        2'b01: Y= 4'b0010;// light up y[1]
        2'b10: Y= 4'b0100;// light up y[2]
        2'b11: Y= 4'b1000;// light up y[3]
    endcase // desigates end of case statement 
    else //if not Enable 
    Y = 4'b0000; //diable all outputs
    end
endmodule //designates end of module  
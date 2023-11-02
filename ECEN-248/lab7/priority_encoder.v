`timescale 1ns/1ps 
`default_nettype none
//This module describes a 4:2 priorty encoder using behavioral constructs in Verilog HDL

//module enterface for the 4:2 prority encoder
module priority_encoder(
input wire [3:0] W, // W is a 4-bit wire
output wire zero,
output reg [1:0] Y // Y is a 2-bit output of type reg 
);

//can mix levels of abstraction 
assign zero = (W ==4'b0000); //a zero test, == is used for comparison 

//behavioral portion 
always @(W)
    begin
        casex (W) //selection based on W
        4'b0001: Y = 2'b00; //2'b signifies a 2-bit binary value 
        4'b001X: Y = 2'b01; //w[1] is lit up
        4'b01XX: Y = 2'b10; //w[2] is lit up
        4'b1XXX: Y = 2'b11; //w[3] is lit up
        default: Y = 2'bXX; //default covers cases not listed
                            // 2'bXX means 2-bits of don't cares
        endcase //designates end of a case statement 
     end 
endmodule //designates end of module 
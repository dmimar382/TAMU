`timescale 1ns/1ps
`default_nettype none
/*this module describes a 1-bit wide multiplexor using behavioral constructs*
*in Verilog HDL*/

module four_bit_mux(Y,A,B,S); //define the module name and its interrface 

//declare output and input ports
output reg [3:0] Y; //output is a 4-bit wide reg
input wire [3:0] A,B; //A and B are 4-bit wide wires
input wire S; //select is still 1 bit wide 

always@(A or B or S) //always block which triggers whenever A,B or S changes
begin //block constructs together
/*1'b0 represents a 1-bit binary value of 0*/
if (S == 1'b0) //double equals are used for comparisons 
    Y = A; //drive Y with A
else 
Y=B; //instead drive Y with B

end

endmodule //designate end of module
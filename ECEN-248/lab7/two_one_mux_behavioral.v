`timescale 1ns/1ps
`default_nettype none
/*this module describes a 1-bit wide multiplexor using behavioral constructs*
*in Verilog HDL*/

module two_one_mux(Y,A,B,S); //define the module name and its interrface 

//declare output and input ports
output reg Y; //declare output of type reg since it will be modified in an always block
input wire A,B,S; //declare inputs of type wire
// wires can drive regs in behavioral statements 

always@(A or B or S) //always block which triggers whenever A,B or S changes
begin //block constructs together
/*1'b0 represents a 1-bit binary value of 0*/
if (S == 1'b0) //double equals are used for comparisons 
    Y = A; //drive Y with A
else 
Y=B; //instead drive Y with B

end

endmodule //designate end of module
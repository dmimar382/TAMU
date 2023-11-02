`timescale 1ns/1ps //delay unit is 1ns

module adder_synchronous(Carry_reg,Sum_reg,Clk, A,B);
//output ports should be regs
//because they need to hold states 

output reg Carry_reg;
output reg [1:0] Sum_reg;
input wire Clk;
input wire [1:0] A,B;

//intermediate nets
reg [1:0] A_reg, B_reg; // 2-bit registers
wire Carry;
wire [1:0] Sum;

//instantiate 2-bit adder 
adder_2bit sync1(Carry,Sum,A_reg,B_reg);

//this behavioral block describes two 2-bit registers
//registers are nothing more than grouped flip-flops
always@(posedge Clk)
begin   //if more than 2 staements we need a begin/end block
    A_reg <= A; //we use non-blocking assignemnt 
    B_reg <= B; //because they happen concurrently
    //registers to store the results 
    Carry_reg <= Carry; //wires can drive regs
    Sum_reg <= Sum;     //both are 2-bit
end
//we could group these all into one block 
endmodule //designate end of module 
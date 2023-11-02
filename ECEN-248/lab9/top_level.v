`timescale 1ns/1ps
`default_nettype none

// This is the tip level module which wires all 
//of our synchronous components together. This module 
//does not include syncronizers for the inputs(we
//will discuss them shortly) so just dont use this in 
//real application
module top_level(LEDs,SWs,BTNs, FastClk);
output wire [3:0] LEDs;
input wire FastClk;
input wire [1:0] SWs;
wire Carry2;
input wire [1:0] BTNs;

//all ports will be wires because we will use structural Verilog to wire everything up

//intermediate nets
wire [3:0] Clocks;
reg SlowClk; //will use an always block for mux

//behavioral description of a mux which 
//selects between the four avaliable clock signals 
always@(*) //combinational logic
case(SWs) // SW is a 2-bit bus
    2'b00: SlowClk = Clocks[0]; //use blocking statement for combinational logic 
    2'b01: SlowClk = Clocks[1];
    2'b10: SlowClk = Clocks[2];
    2'b11: SlowClk = Clocks[3];
endcase

//instantiate your up_counterr here
up_counter counter(LEDs[2:0],LEDs[3],BTNs[0],SlowClk,BTNs[1]);//LEDs[3] is the Carry value

//instantiate the clock divider
clock_divider clk_div0(
.ClkOut(Clocks),
.ClkIn(FastClk)
);

endmodule //designate end of module
`timescale 1ns / 1ps
`default_nettype none

/*This module describes a counter that is triggered off of*
 *the rising-edge of an signal that has not been debounced*
 *in order to demonstrate the effects of switch bounce    */
module noDebounce(LEDs, BTN, Clk);

    /*The output LEDs are of type reg because they are*
     *modified using behavioral Verilog               */
    output reg [3:0] LEDs;
    input wire BTN, Clk;

    /*intermediate nets*/
    reg edge_detect0, edge_detect1;
    wire rising_edge;//asserted when an edge is detected
    /*This is just for simulation*/
    initial
       LEDs=0;    
    /*describe an edge-detector circuit which detects*
     *a rising-edge of an asynchronous signal. The   *
     *usage of two flip-flops may seem redundant but *
     *is necessary for synchronization purposes!     */
    always@(posedge Clk)
      begin
        edge_detect0 <= BTN;//input signal
        edge_detect1 <= edge_detect0;
      end
    /*when older value is 0 and new value is 1, a   *
     *rising edge has occurred                      */
    assign rising_edge = ~edge_detect1 & edge_detect0;

    /*describe a counter that increments each time a*
     *rising-edge of input signal is detected       */
    always@(posedge Clk)
        if(rising_edge)
            LEDs <= LEDs + 1;

endmodule


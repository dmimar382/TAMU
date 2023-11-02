`default_nettype none

/*This module describes the top level traffic
light controller module discussed in lab11 */

module tlc_controller(
    output wire [1:0] highwaySignal, farmSignal, //connected to LEDs
    /*Let's output state for debugging!*/
    output wire [3:0] JB,
    input wire Clk,
    input wire farmSensor,
    /*the buttons provide input to our top level circuit*/
    input wire Rst //use as reset
);

//intermediate nets
wire RstSync;
wire RstCount;
wire SensorSync;
reg [30:0] Count;

assign JB[3] = RstCount;

/*synchronize button inputs*/
synchronizer syncRst(RstSync, Rst, Clk);
synchronizer syncSensor(SensorSync, farmSensor, Clk);

//instantiate FSM
tlc_fsm FSM(
    .state(JB[2:0]), //wire state up to JB
    .RstCount,       // RstCount(JB[3]) redundant?
    .highwaySignal,
    .farmSignal,
    .Count,  
    .Rst(RstSync),
    .farmSensor(SensorSync),
    .Clk
);

//describe counter with a syncrhonous reset 
always@ (posedge Clk)
    if (RstCount)
        Count <= 0;
    else
    begin 
    if (Count > 1500000000 == 0)
        Count <= Count + 1;
    end
        
endmodule //designate end of module  
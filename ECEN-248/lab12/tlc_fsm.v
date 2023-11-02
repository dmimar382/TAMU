`timescale 1ns / 1ps
`default_nettype none

`define seconds1 50000000 //sec1 = 50000000 clock cycles
`define seconds3 150000000 //sec3 = 150000000 clock cycles
`define seconds15 750000000 //sec15 = 750000000 clock cycles
`define seconds30 1500000000 //sec30 = 1500000000 clock cycles 

module tlc_fsm(
    output reg [2:0] state, // output for debugging
    output reg RstCount, // use an always block
    output reg [1:0] highwaySignal, farmSignal,
    input wire [30:0] Count, // use n computed earlier
    input wire Clk, Rst, // clock and reset
    input wire farmSensor
);
    
    /* declare different states */
    parameter S0 = 3'b000;
    parameter S1 = 3'b001;
    parameter S2 = 3'b010;
    parameter S3 = 3'b011;
    parameter S4 = 3'b100;
    parameter S5 = 3'b101;

    parameter green = 2'b11;
    parameter yellow = 2'b10;
    parameter red = 2'b01;
    
    reg [2:0] nextState;

    always@ (state or Count)
        case (state)
            // state 0
            S0: begin
                if (Count == `seconds1 || (Rst ==1) ) // if we reached 1 second
                begin
                    highwaySignal = red; // results of state 0
                    farmSignal = red;
                    RstCount = 1;
                    nextState = S1; //transition to S1
                end
                
                else
                begin
                    highwaySignal = red; // otherwise, stay at S0
                    farmSignal = red;
                    RstCount = 0;
                    nextState = S0;
                end
            end
            
            // state 1
            S1: begin
                if ((Count >= `seconds30) && (farmSensor))	// if reached 30 seconds
                begin
                    highwaySignal = green; // results of state 1
                    farmSignal = red;       
                    RstCount = 1;
                    nextState = S2; //transition to S2
                end
                
                else
                begin
                    highwaySignal = green; // otherwise, stay at S1
                    farmSignal = red;
                    RstCount = 0;
                    nextState = S1;
                end
                
            end
            
           // state 2
           S2: begin
                if(Count == `seconds3)	 // if reached 3 seconds
                begin
                    highwaySignal = yellow; // results of state 2
                    farmSignal = red;  
                    RstCount = 1;
                    nextState = S3; //transition to S3
                end
                else
                begin
                    highwaySignal = yellow; // otherwise, stay at S2
                    farmSignal = red;
                    RstCount = 0;
                    nextState = S2;
                end
            end
            
            //state 3
            S3: begin
                if(Count == `seconds1)	//if reached 1 second
                begin
                    highwaySignal = red; //results of state 3
                    farmSignal = red;  
                    RstCount = 1;
                    nextState = S4; //transition to S4
                end
                else
                begin
                    highwaySignal = red; //otherwise stay at S3
                    farmSignal = red;
                    RstCount = 0;
                    nextState = S3;
                end
            end
            
            //state 4
            S4: begin
                if (((Count >= `seconds3) && (!farmSensor)) || (Count >= `seconds15) )//if reached 15 seconds
                begin
                    highwaySignal = red; //results of S4
                    farmSignal = green;  
                    RstCount = 1;
                    nextState = S5; //transition to S5
                end
                else
                begin
                    highwaySignal = red; //otherwise stay at S4
                    farmSignal = green;
                    RstCount = 0;
                    nextState = S4;
                end
            end
            
            //state 5
            S5: begin
                if(Count == `seconds3)	//if reached 3 seconds
                begin
                    highwaySignal = red; //results of S5
                    farmSignal = yellow;  
                    RstCount = 1;
                    nextState = S0; //transition to S0
                end
                else
                begin
                    highwaySignal = red; //otherrwise stay at S5
                    farmSignal = yellow;
                    RstCount = 0;
                    nextState = S5;
                end
            end
        endcase

    always@ (posedge Clk)
        if(Rst)
            state <= S0;
        else
            state <= nextState;
         
endmodule //designate end of module 
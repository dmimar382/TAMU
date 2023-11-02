// Code your testbench here
// or browse Examples
//`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   10:02:47 03/05/2009
// Design Name:   ALU
// Module Name:   E:/350/Lab8/ALU/ALUTest.v
// Project Name:  ALU
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: ALU
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////
//`timescale 1ns / 1ps
`define STRLEN 32
module ALUTest_v;

	task passTest;
		input [64:0] actualOut, expectedOut;
		input [`STRLEN*8:0] testType;
		inout [7:0] passed;
	
		if(actualOut == expectedOut) begin $display ("%s passed", testType); passed = passed + 1; end
		else $display ("%s failed: %x should be %x", testType, actualOut, expectedOut);
	endtask
	
	task allPassed;
		input [7:0] passed;
		input [7:0] numTests;
		
		if(passed == numTests) $display ("All tests passed");
		else $display("Some tests failed");
	endtask

	// Inputs
	reg [63:0] BusA;
	reg [63:0] BusB;
	reg [3:0] ALUCtrl;
	reg [7:0] passed;

	// Outputs
	wire [63:0] BusW;
	wire Zero;

	// Instantiate the Unit Under Test (UUT)
	ALU uut (
		.BusW(BusW), 
		.Zero(Zero), 
		.BusA(BusA), 
		.BusB(BusB), 
		.ALUCtrl(ALUCtrl)
	);

	initial begin
      $dumpfile("test.vcd");
      $dumpvars(0,ALUTest_v);
      
		// Initialize Inputs
		BusA = 0;
		BusB = 0;
		ALUCtrl = 0;
		passed = 0;

                // Here is one example test vector, testing the ADD instruction:
      //{BusA, BusB, ALUCtrl} = {64'h1234, 64'hABCD0000, 4'h2}; #40; passTest({Zero, BusW}, 65'h0ABCD1234, "ADD 0x1234,0xABCD0000", passed);
		//Reformate and add your test vectors from the prelab here following the example of the testvector above.	
      
      {BusA, BusB, ALUCtrl} = {64'h1, 64'h8, 4'h0}; #40; passTest({Zero, BusW}, 65'h10000000000000000, "AND 0x1,0x8", passed);
      {BusA, BusB, ALUCtrl} = {64'h2, 64'h3, 4'h0}; #40; passTest({Zero, BusW}, 65'h2, "AND 0x2,0x3", passed);
      {BusA, BusB, ALUCtrl} = {64'h5, 64'h1, 4'h0}; #40; passTest({Zero, BusW}, 65'h1, "AND 0x5,0x1", passed);
      
      {BusA, BusB, ALUCtrl} = {64'h4, 64'h6, 4'h1}; #40; passTest({Zero, BusW}, 65'h6, "OR 0x4,0x6", passed);
      {BusA, BusB, ALUCtrl} = {64'h7, 64'h3, 4'h1}; #40; passTest({Zero, BusW}, 65'h7, "OR 0x7,0x3", passed);
      {BusA, BusB, ALUCtrl} = {64'h3, 64'h8, 4'h1}; #40; passTest({Zero, BusW}, 65'hB, "OR 0x3,0x8", passed);
      
      {BusA, BusB, ALUCtrl} = {64'h1, 64'h9, 4'h2}; #40; passTest({Zero, BusW}, 65'hA, "ADD 0x1,0x9", passed);
      {BusA, BusB, ALUCtrl} = {64'h0, 64'h0, 4'h2}; #40; passTest({Zero, BusW}, 65'h10000000000000000, "ADD 0x0,0x0", passed);
      {BusA, BusB, ALUCtrl} = {64'h7, 64'h1, 4'h2}; #40; passTest({Zero, BusW}, 65'h8, "ADD 0x7,0x1", passed);
      
      {BusA, BusB, ALUCtrl} = {64'hA, 64'h3, 4'h6}; #40; passTest({Zero, BusW}, 65'h7, "SUB 0xA,0x3", passed);
      {BusA, BusB, ALUCtrl} = {64'hB, 64'h2, 4'h6}; #40; passTest({Zero, BusW}, 65'h9, "SUB 0xB,0x2", passed);
      {BusA, BusB, ALUCtrl} = {64'h4, 64'h0, 4'h6}; #40; passTest({Zero, BusW}, 65'h4, "SUB 0x4,0x0", passed);
      
      {BusA, BusB, ALUCtrl} = {64'h1, 64'h6, 4'h7}; #40; passTest({Zero, BusW}, 65'h6, "PASSB 0x1,0x6", passed);
      {BusA, BusB, ALUCtrl} = {64'h2, 64'h6, 4'h7}; #40; passTest({Zero, BusW}, 65'h6, "PASSB 0x1,0x6", passed);
      {BusA, BusB, ALUCtrl} = {64'h3, 64'h6, 4'h7}; #40; passTest({Zero, BusW}, 65'h6, "PASSB 0x1,0x6", passed);
      
      


      allPassed(passed, 15);//22
	end
      
endmodule


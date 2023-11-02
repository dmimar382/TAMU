`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   10:13:28 03/03/2009
// Design Name:   RegisterFile
// Module Name:   E:/350/Lab7/RegisterFile/RegisterFileTest.v
// Project Name:  RegisterFile
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: RegisterFile
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

`define STRLEN 32
module RegisterFileTest_v;


	task passTest;
		input [63:0] actualOut, expectedOut;
		input [`STRLEN*8:0] testType;
		inout [7:0] passed;
	
		if(actualOut == expectedOut) begin $display ("%s passed", testType); passed = passed + 1; end
		else $display ("%s failed: %d should be %d", testType, actualOut, expectedOut);
	endtask
	
	task allPassed;
		input [7:0] passed;
		input [7:0] numTests;
		
		if(passed == numTests) $display ("All tests passed");
		else $display("Some tests failed");
	endtask

	// Inputs
	reg [63:0] BusW;
	reg [4:0] RA;
	reg [4:0] RB;
	reg [4:0] RW;
	reg RegWr;
	reg Clk;
	reg [7:0] passed;

	// Outputs
	wire [63:0] BusA;
	wire [63:0] BusB;

	// Instantiate the Unit Under Test (UUT)
	RegisterFile uut (
		.BusA(BusA), 
		.BusB(BusB), 
		.BusW(BusW), 
		.RA(RA), 
		.RB(RB), 
		.RW(RW), 
		.RegWr(RegWr), 
		.Clk(Clk)
	);

	initial begin
      	$dumpfile("dump.vcd"); $dumpvars;
      	$dumpvars(0, RegisterFileTest_v);
		// Initialize Inputs
		BusW = 0;
		RA = 0;
		RB = 0;
		RW = 0;
		RegWr = 0;
		Clk = 1;
		passed = 0;
		
		#10;

		// Add stimulus here
		{RA, RB, RW, BusW, RegWr} = {5'd31, 5'd31, 5'd31, 64'h0, 1'b0};
		#10
		passTest(BusA, 64'd0, "Initial $0 Check 1", passed);
		passTest(BusB, 64'd0, "Initial $0 Check 2", passed);
		#10; Clk = 0; #10; Clk = 1;
		
		{RA, RB, RW, BusW, RegWr} = {5'd31, 5'd31, 5'd31, 64'h12345678, 1'b1};
		passTest(BusA, 64'd0, "Initial $0 Check 3", passed);
		passTest(BusB, 64'd0, "Initial $0 Check 4", passed);
		#10; Clk = 0; #10; Clk = 1;
		passTest(BusA, 64'd0, "$0 Stays 0 Check 1", passed);
		passTest(BusB, 64'd0, "$0 Stays 0 Check 2", passed);
		
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd0, 64'h0, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd1, 64'h1, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd2, 64'h2, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd3, 64'h3, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd4, 64'h4, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd5, 64'h5, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd6, 64'h6, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd7, 64'h7, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd8, 64'h8, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd9, 64'h9, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd10, 64'd10, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd11, 64'd11, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd12, 64'd12, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd13, 64'd13, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd14, 64'd14, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd15, 64'd15, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd16, 64'd16, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd17, 64'd17, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd18, 64'd18, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd19, 64'd19, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd20, 64'd20, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd21, 64'd21, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd22, 64'd22, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd23, 64'd23, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd24, 64'd24, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd25, 64'd25, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd26, 64'd26, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd27, 64'd27, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd28, 64'd28, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd29, 64'd29, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd30, 64'd30, 1'b1};#10; Clk = 0; #10; Clk = 1;
		{RA, RB, RW, BusW, RegWr} = {5'd0, 5'd0, 5'd31, 64'd31, 1'b1};#10; Clk = 0; #10; Clk = 1;
      

       //Test #1
      {RA, RB, RW, BusW, RegWr} = {5'd0, 5'd1, 5'd0, 64'd0, 1'b0};
      //initial bus test
      #4;
      passTest(BusA, 64'h0, "Initial BusA: Check 0", passed);
      passTest(BusB, 64'h1, "Initial BusB: Check 1", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h0, "BusA: Value not updated 1", passed);
      passTest(BusB, 64'h1, "BusB: Value not updated 1", passed);
      
       //Test #2
      {RA, RB, RW, BusW, RegWr} = {5'd2, 5'd3, 5'd1, 64'd1000, 1'b0};
      #4;
      passTest(BusA, 64'h2, "Initial BusA: Check 2", passed);
      passTest(BusB, 64'h3, "Initial BusB: Check 3", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h2, "BusA: Value not updated 2", passed);
      passTest(BusB, 64'h3, "BusB: Value not updated 2", passed);
      
      //Test #3 - writing 0x1000 to Register 0
      {RA, RB, RW, BusW, RegWr} = {5'd4, 5'd5, 5'd0, 64'h1000, 1'b1};
      #4;
      passTest(BusA, 64'h4, "Initial BusA: Check 4", passed);
      passTest(BusB, 64'h5, "Initial BusB: Check 5", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h4, "BusA: Value not updated 3", passed);
      passTest(BusB, 64'h5, "BusB: Value not updated 3", passed);
      
      //Test #4 - writing 0x1010 to Register 10
      {RA, RB, RW, BusW, RegWr} = {5'd6, 5'd7, 5'hA, 64'h1010, 1'b1};
      #4;
      passTest(BusA, 64'h6, "Initial BusA: Check 6", passed);
      passTest(BusB, 64'h7, "Initial BusB: Check 7", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h6, "BusA: Value not updated 4", passed);
      passTest(BusB, 64'h7, "BusB: Value not updated 4", passed);
      
      //Test #5 - writing 0x103000 to Register 11 
      {RA, RB, RW, BusW, RegWr} = {5'd8, 5'd9, 5'hB, 64'h103000, 1'b1};
      #4;
      passTest(BusA, 64'h8, "Initial BusA: Check 8", passed);
      passTest(BusB, 64'h9, "Initial BusB: Check 9", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h8, "BusA: Value not updated 5", passed);
      passTest(BusB, 64'h9, "BusB: Value not updated 5", passed);
      
      //Test #6  
      {RA, RB, RW, BusW, RegWr} = {5'hA, 5'hB, 5'hC, 64'd0, 1'b0};
      #4;
      passTest(BusA, 64'h1010, "Initial BusA: Check 10", passed);
      passTest(BusB, 64'h103000, "Initial BusB: Check 11", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h1010, "BusA: Value stayed the same 6", passed);
      passTest(BusB, 64'h103000, "BusB: Value stayed the same 6", passed);
      
      //Test #7 - writing 0xABCD to Register 13
      {RA, RB, RW, BusW, RegWr} = {5'hC, 5'hD, 5'hD, 64'hABCD, 1'b1};
      #4;
      passTest(BusA, 64'hC, "Initial BusA: Check 12", passed);
      passTest(BusB, 64'hD, "Initial BusB: Check 13", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'hC, "BusA: Value not updated 7", passed);
      passTest(BusB, 64'hABCD, "BusB: Value updated 7", passed);
      
      //Test #8
      {RA, RB, RW, BusW, RegWr} = {5'hE, 5'hF, 5'hE, 64'h9080009, 1'b0};
      #4;
      passTest(BusA, 64'hE, "Initial BusA: Check 14", passed);
      passTest(BusB, 64'hF, "Initial BusB: Check 15", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'hE, "BusA: Value not updated 8", passed);
      passTest(BusB, 64'hF, "BusB: Value not updated 8", passed);

      allPassed(passed, 38);
	end
      
endmodule
`timescale 1ns / 1ps
`define STRLEN 32
module RegisterFile_tb_v;

  task passTest;
		input [63:0] actualOut, expectedOut; //declared inputs
		input [`STRLEN*8:0] testType; //declared outputs
		inout [7:0] passed; //declared inout passed
	
		if(actualOut == expectedOut) begin $display ("%s passed", testType); passed = passed + 1; end //if actual value equals expected then test passed
		else $display ("%s failed: %d should be %d", testType, actualOut, expectedOut); //if not test failed
	endtask
	
	task allPassed;
		input [7:0] passed; //declared inputs
		input [7:0] numTests; //declared inputs
		
		if(passed == numTests) $display ("All tests passed"); //if test passed equals numtests passed
		else $display("Some tests failed");
	endtask

	// declaring reg wires (inputs)
	reg [63:0] BusW;
	reg [4:0] RA;
	reg [4:0] RB;
	reg [4:0] RW;
	reg RegWr;
	reg Clk;
	reg [7:0] passed;

	// declaring reg wires (Outputs)
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
      $dumpvars(0, RegisterFile_tb_v);
		// Initialize Inputs
		BusW = 0;
		RA = 0;
		RB = 0;
		RW = 0;
		RegWr = 0;
		Clk = 1;
		passed = 0;
		
		#10;


		
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

      
      {RA, RB, RW, BusW, RegWr} = {5'd0, 5'd1, 5'd0, 64'd0, 1'b0};
      #4;
      passTest(BusA, 64'h0, "Initial A Check 0", passed);
      passTest(BusB, 64'h1, "Initial B Check 1", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h0, "A Value not updated 1", passed);
      passTest(BusB, 64'h1, "B Value not updated 1", passed);
      
      {RA, RB, RW, BusW, RegWr} = {5'd2, 5'd3, 5'd1, 64'd1000, 1'b0};
      #4;
      passTest(BusA, 64'h2, "Initial A Check 2", passed);
      passTest(BusB, 64'h3, "Initial B Check 3", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h2, "A Value not updated 2", passed);
      passTest(BusB, 64'h3, "B Value not updated 2", passed);
      
      
      {RA, RB, RW, BusW, RegWr} = {5'd4, 5'd5, 5'd0, 64'h1000, 1'b1};//test3
      #4;
      passTest(BusA, 64'h4, "Initial A Check 4", passed);
      passTest(BusB, 64'h5, "Initial B Check 5", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h4, "A Value not updated 3", passed);
      passTest(BusB, 64'h5, "B Value not updated 3", passed);
      
 
      {RA, RB, RW, BusW, RegWr} = {5'd6, 5'd7, 5'hA, 64'h1010, 1'b1};//test4
      #4;
      passTest(BusA, 64'h6, "Initial A Check 6", passed);
      passTest(BusB, 64'h7, "Initial B Check 7", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h6, "A Value not updated 4", passed);
      passTest(BusB, 64'h7, "B Value not updated 4", passed);
      

      {RA, RB, RW, BusW, RegWr} = {5'd8, 5'd9, 5'hB, 64'h103000, 1'b1};//test5
      #4;
      passTest(BusA, 64'h8, "Initial A Check 8", passed);
      passTest(BusB, 64'h9, "Initial B Check 9", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h8, "A Value not updated 5", passed);
      passTest(BusB, 64'h9, "B Value not updated 5", passed);
      
       
      {RA, RB, RW, BusW, RegWr} = {5'hA, 5'hB, 5'hC, 64'd0, 1'b0};//test6
      #4;
      passTest(BusA, 64'h1010, "Initial A Check 10", passed);
      passTest(BusB, 64'h103000, "Initial B Check 11", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'h1010, "A Value stayed the same 6", passed);
      passTest(BusB, 64'h103000, "B Value stayed the same 6", passed);
      
    
      {RA, RB, RW, BusW, RegWr} = {5'hC, 5'hD, 5'hD, 64'hABCD, 1'b1};//test 7
      #4;
      passTest(BusA, 64'hC, "Initial A Check 12", passed);
      passTest(BusB, 64'hD, "Initial B Check 13", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'hC, "A Value not updated 7", passed);
      passTest(BusB, 64'hABCD, "B Value updated 7", passed);
  
      {RA, RB, RW, BusW, RegWr} = {5'hE, 5'hF, 5'hE, 64'h9080009, 1'b0};//test 8
      #4;
      passTest(BusA, 64'hE, "Initial A Check 14", passed);
      passTest(BusB, 64'hF, "Initial B Check 15", passed);
      #6; Clk = 0; #10; Clk = 1;
      passTest(BusA, 64'hE, "A Value not updated 8", passed);
      passTest(BusB, 64'hF, "B Value not updated 8", passed);

      allPassed(passed, 32);
      
	end
      
endmodule
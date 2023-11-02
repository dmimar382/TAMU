`timescale 1ns / 1ps
`define NUM_TESTS 1024
`define STRLEN 64
`define TEST_DELAY 16

module cla_16bit_tb;

   /*A task is similar to a procedure in the traditional programming language*/
   /*This particular task simply checks the output of our circuit against a 
     known answer and prints a message based on the outcome. Additionally, 
     this task increments the variable we are using to keep track of the 
     number of tests successfully passed.*/
   task passTest;
		input [16:0] actualOut, expectedOut;
		input [`STRLEN*8:0] testType;
		inout [7:0] passed;
	
		if(actualOut == expectedOut) begin $display ("%s passed", testType); passed = passed + 1; end
		else $display ("%s failed: %x should be %x", testType, actualOut, expectedOut);
	endtask
	
    /*this task simply informs the user of the final outcome of the test*/
	task allPassed;
		input [7:0] passed;
		input [7:0] numTests;
		
		if(passed == numTests) $display ("All tests passed");
		else $display("Some tests failed");
	endtask
	
	// Inputs
	reg [15:0] X;
	reg [15:0] Y;
	reg Cin;

	// Outputs
	wire Cout;
	wire [15:0] S;
	
	//test bench nets
	reg [16:0] Result;
	reg [7:0] passed;

	// Instantiate the Unit Under Test (UUT)
	carry_lookahead_16bit uut (
		.Cout(Cout), 
		.S(S), 
		.X(X), 
		.Y(Y), 
		.Cin(Cin)
	);

	initial begin
		// Initialize Inputs
		X = 0;
		Y = 0;
		Cin = 0;
		passed = 0;
		 repeat(`NUM_TESTS)
    	 begin
    		#(`TEST_DELAY);
    		Result = X + Y + Cin;
    		passTest({Cout, S}, {Result}, "16-bit Carry-lookahead Adder Unit Test", passed);
    		X = $random;
    		Y = $random;
			Cin = $random;
    	 end
		/*check to see if all tests passed*/
      allPassed(passed,`NUM_TESTS);
      $stop; //hault simulation cause we are done!
	end
      
endmodule


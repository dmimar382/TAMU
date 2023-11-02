`timescale 1ns / 1ps
`define STRLEN 32

module cla_4bit_tb;

   /*A task is similar to a procedure in the traditional programming language*/
   /*This particular task simply checks the output of our circuit against a 
     known answer and prints a message based on the outcome. Additionally, 
     this task increments the variable we are using to keep track of the 
     number of tests successfully passed.*/
   task passTest;
		input [4:0] actualOut, expectedOut;
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
	reg [3:0] X;
	reg [3:0] Y;
	reg Cin;

	// Outputs
	wire Cout;
	wire [3:0] S;
	
	//test bench nets
	reg [4:0] Result;
	reg [7:0] passed;

	// Instantiate the Unit Under Test (UUT)
	carry_lookahead_4bit uut (
		.Cout(Cout), 
		.S(S), 
		.X(X), 
		.Y(Y), 
		.Cin(Cin)
	);

	integer i, j;	

	initial begin
		// Initialize Inputs
		X = 0;
		Y = 0;
		Cin = 0;
		passed = 0;
		
		for(i = 0; i < 5; i = i + 1)
			for(j = 0; j < 5; j = j + 1)
			 begin
			   /*no carry*/
				#10;
				Result = X + Y;
				passTest({Cout, S}, {Result}, "Carry-lookahead Adder Unit Test", passed);
			   /*carry*/
				Cin = 1;
				#10;
				Result = X + Y + 1;
				passTest({Cout, S}, {Result}, "Carry-lookahead Adder Unit Test", passed);
				X = i;
				Y = j;
				Cin = 0;
			 end
		/*check to see if all tests passed*/
      allPassed(passed, 2*i*j);
      $stop; //hault simulation cause we are done!
	end
      
endmodule


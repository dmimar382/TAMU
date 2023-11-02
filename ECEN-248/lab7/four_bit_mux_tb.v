`timescale 1ns / 1ps //time unit is 1 nano second and the simulation steps are in peco seconds
`define STRLEN 32

/*This test bench is full of non-synthesizable constructs, which basically means it is
 *restricted to simulation only!*/
module four_bit_mux_tb;

   /*A task is similar to a procedure in the traditional programming language*/
   /*This particular task simply checks the output of our circuit against a 
     known answer and prints a message based on the outcome. Additionally, 
     this task increments the variable we are using to keep track of the 
     number of tests successfully passed.*/
   task passTest;
		input [3:0] actualOut, expectedOut;
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
	reg [3:0] A;
	reg [3:0] B;
	reg S;
    reg [7:0] passed;

	// Outputs
	wire [3:0] Y;

	// Instantiate the Unit Under Test (UUT)
	four_bit_mux uut (
		.Y(Y), 
		.A(A), 
		.B(B), 
		.S(S)
	);

	initial begin
		// Initialize Inputs
		A = 0;
		B = 0;
		S = 0;
        passed = 0;
    
        // Add stimulus here	
        /*perform a walking one's test on inputs*/	
        /*wait 10 time units*/
        /*check output against known answer*/
        {A, B, S} = {4'b0000, 4'b0000, 1'b0}; #10; passTest(Y, 4'b0000, "4-bit Mux Test 1", passed);
        {A, B, S} = {4'b0001, 4'b0000, 1'b0}; #10; passTest(Y, 4'b0001, "4-bit Mux Test 2", passed);
        {A, B, S} = {4'b0010, 4'b0000, 1'b0}; #10; passTest(Y, 4'b0010, "4-bit Mux Test 3", passed);
        {A, B, S} = {4'b0100, 4'b0000, 1'b0}; #10; passTest(Y, 4'b0100, "4-bit Mux Test 4", passed);
        {A, B, S} = {4'b1000, 4'b0000, 1'b0}; #10; passTest(Y, 4'b1000, "4-bit Mux Test 5", passed);
        {A, B, S} = {4'b1111, 4'b0000, 1'b0}; #10; passTest(Y, 4'b1111, "4-bit Mux Test 6", passed);
        {A, B, S} = {4'b1111, 4'b0000, 1'b1}; #10; passTest(Y, 4'b0000, "4-bit Mux Test 7", passed);
        {A, B, S} = {4'b0000, 4'b0001, 1'b1}; #10; passTest(Y, 4'b0001, "4-bit Mux Test 8", passed);
        {A, B, S} = {4'b0000, 4'b0010, 1'b1}; #10; passTest(Y, 4'b0010, "4-bit Mux Test 9", passed);
        {A, B, S} = {4'b0000, 4'b0100, 1'b1}; #10; passTest(Y, 4'b0100, "4-bit Mux Test 10", passed);
        {A, B, S} = {4'b0000, 4'b1000, 1'b1}; #10; passTest(Y, 4'b1000, "4-bit Mux Test 11", passed);
        {A, B, S} = {4'b0000, 4'b1111, 1'b0}; #10; passTest(Y, 4'b0000, "4-bit Mux Test 12", passed);
        {A, B, S} = {4'b0000, 4'b1111, 1'b1}; #10; passTest(Y, 4'b1111, "4-bit Mux Test 13", passed);
        {A, B, S} = {4'b1010, 4'b1111, 1'b0}; #10; passTest(Y, 4'b1010, "4-bit Mux Test 14", passed);
        {A, B, S} = {4'b1010, 4'b1111, 1'b1}; #10; passTest(Y, 4'b1111, "4-bit Mux Test 15", passed);
        {A, B, S} = {4'b1111, 4'b1111, 1'b0}; #10; passTest(Y, 4'b1111, "4-bit Mux Test 16", passed);
        allPassed(passed, 16);//did all the tests pass???
        $stop;//that's all folks!
	end
      
endmodule


`timescale 1ns / 1ps//time unit is 1 nano second and the simulation steps are in peco seconds
`define STRLEN 32

/*This test bench is full of non-synthesizable constructs, which basically means it is
 *restricted to simulation only!*/
module two_one_mux_tb;

   /*A task is similar to a procedure in the traditional programming language*/
   /*This particular task simply checks the output of our circuit against a 
     known answer and prints a message based on the outcome. Additionally, 
     this task increments the variable we are using to keep track of the 
     number of tests successfully passed.*/
   task passTest;
		input actualOut, expectedOut;
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
	reg A;
	reg B;
	reg S;
    reg [7:0] passed;

	// Outputs
	wire Y;

	// Instantiate the Unit Under Test (UUT)
	two_one_mux uut (
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
        // Add stimulus here
        /*set input (i.e. stimulus)*/	
        /*wait 10 time units*/
        /*check output against known answer*/
        {A, B, S} = {3'b000}; #10; passTest(Y, 1'b0, "Mux Test 1", passed);
        {A, B, S} = {3'b001}; #10; passTest(Y, 1'b0, "Mux Test 2", passed);
        {A, B, S} = {3'b010}; #10; passTest(Y, 1'b0, "Mux Test 3", passed);
        {A, B, S} = {3'b011}; #10; passTest(Y, 1'b1, "Mux Test 4", passed);
        {A, B, S} = {3'b100}; #10; passTest(Y, 1'b1, "Mux Test 5", passed);
        {A, B, S} = {3'b101}; #10; passTest(Y, 1'b0, "Mux Test 6", passed);
        {A, B, S} = {3'b110}; #10; passTest(Y, 1'b1, "Mux Test 7", passed);
        {A, B, S} = {3'b111}; #10; passTest(Y, 1'b1, "Mux Test 8", passed);
        allPassed(passed, 8);//did all the tests pass???
        $stop;//that's all folks!
	end
      
endmodule


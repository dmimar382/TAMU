`timescale 1ns / 1ps//time unit is 1 nano second and the simulation steps are in peco seconds
`define STRLEN 32

/*This test bench is full of non-synthesizable constructs, which basically means it is
 *restricted to simulation only!*/
module priority_encoder_tb;

   /*A task is similar to a procedure in the traditional programming language*/
   /*This particular task simply checks the output of our circuit against a 
     known answer and prints a message based on the outcome. Additionally, 
     this task increments the variable we are using to keep track of the 
     number of tests successfully passed.*/
   task passTest;
		input [2:0] actualOut, expectedOut;
		input [`STRLEN*8:0] testType;
		inout [7:0] passed;
	
		if(actualOut === expectedOut) begin $display ("%s passed", testType); passed = passed + 1; end
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
	reg [3:0] W;
	
    reg [7:0] passed;

	// Outputs
	wire [1:0] Y;
    wire zero;

	// Instantiate the Unit Under Test (UUT)
	priority_encoder uut (
		.Y(Y), 
		.W(W), 
		.zero(zero)
	);

	initial begin
		// Initialize Inputs
	    W = 0;

        passed = 0;
    
        // Add stimulus here
        /*set input (i.e. stimulus)*/	
        /*wait 10 time units*/
        /*check output against known answer*/
        {W} = {4'b0000}; #10; passTest({Y, zero}, 3'bXX1, "Encoder Test 1", passed);
        {W} = {4'b0001}; #10; passTest({Y, zero}, 3'b000, "Encoder Test 2", passed);
        {W} = {4'b0010}; #10; passTest({Y, zero}, 3'b010, "Encoder Test 3", passed);
        {W} = {4'b0011}; #10; passTest({Y, zero}, 3'b010, "Encoder Test 4", passed);
        {W} = {4'b0100}; #10; passTest({Y, zero}, 3'b100, "Encoder Test 5", passed);
        {W} = {4'b0101}; #10; passTest({Y, zero}, 3'b100, "Encoder Test 6", passed);
        {W} = {4'b0110}; #10; passTest({Y, zero}, 3'b100, "Encoder Test 7", passed);
        {W} = {4'b0111}; #10; passTest({Y, zero}, 3'b100, "Encoder Test 8", passed);
        {W} = {4'b1000}; #10; passTest({Y, zero}, 3'b110, "Encoder Test 9", passed);
        {W} = {4'b1001}; #10; passTest({Y, zero}, 3'b110, "Encoder Test 10", passed);
        {W} = {4'b1010}; #10; passTest({Y, zero}, 3'b110, "Encoder Test 11", passed);
        {W} = {4'b1011}; #10; passTest({Y, zero}, 3'b110, "Encoder Test 12", passed);
        {W} = {4'b1100}; #10; passTest({Y, zero}, 3'b110, "Encoder Test 13", passed);
        {W} = {4'b1101}; #10; passTest({Y, zero}, 3'b110, "Encoder Test 14", passed);
        {W} = {4'b1110}; #10; passTest({Y, zero}, 3'b110, "Encoder Test 15", passed);
        {W} = {4'b1111}; #10; passTest({Y, zero}, 3'b110, "Encoder Test 16", passed);
        allPassed(passed, 16);//did all the tests pass???
        $stop;//that's all folks!
	end
      
endmodule


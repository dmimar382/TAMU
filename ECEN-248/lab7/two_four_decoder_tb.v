`timescale 1ns / 1ps//time unit is 1 nano second and the simulation steps are in peco seconds
`define STRLEN 32

/*This test bench is full of non-synthesizable constructs, which basically means it is
 *restricted to simulation only!*/
module two_four_decoder_tb;

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
	reg [1:0] W;
	reg En;
	
    reg [7:0] passed;

	// Outputs
	wire [3:0] Y;

	// Instantiate the Unit Under Test (UUT)
	two_four_decoder uut (
		.Y(Y), 
		.W(W), 
		.En(En) 
	);

	initial begin
		// Initialize Inputs
	    W = 0;
		En = 0;

        passed = 0;
    
        // Add stimulus here
        /*set input (i.e. stimulus)*/	
        /*wait 10 time units*/
        /*check output against known answer*/
        {En, W} = {3'b000}; #10; passTest(Y, 4'b0000, "Decoder Test 1", passed);
        {En, W} = {3'b001}; #10; passTest(Y, 4'b0000, "Decoder Test 2", passed);
        {En, W} = {3'b010}; #10; passTest(Y, 4'b0000, "Decoder Test 3", passed);
        {En, W} = {3'b011}; #10; passTest(Y, 4'b0000, "Decoder Test 4", passed);
        {En, W} = {3'b100}; #10; passTest(Y, 4'b0001, "Decoder Test 5", passed);
        {En, W} = {3'b101}; #10; passTest(Y, 4'b0010, "Decoder Test 6", passed);
        {En, W} = {3'b110}; #10; passTest(Y, 4'b0100, "Decoder Test 7", passed);
        {En, W} = {3'b111}; #10; passTest(Y, 4'b1000, "Decoder Test 8", passed);
        allPassed(passed, 8);//did all the tests pass???
        $stop;//that's all folks!
	end
      
endmodule


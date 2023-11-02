`timescale 1ns / 1ps
`define STRLEN 32

module d_latch_behavioral_tb;

   /*A task is similar to a procedure in the traditional programming language*/
   /*This particular task simply checks the output of our circuit against a 
     known answer and prints a message based on the outcome. Additionally, 
     this task increments the variable we are using to keep track of the 
     number of tests successfully passed.*/
   task passTest;
		input [1:0] actualOut, expectedOut;
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
	reg En;
	reg D;

	// Outputs
	wire Q;
	wire notQ;

    reg [7:0] passed;
	// Instantiate the Unit Under Test (UUT)
	d_latch_behavioral uut (
		.Q(Q), 
		.notQ(notQ), 
		.En(En), 
		.D(D)
	);

	initial begin

        passed = 0;

        /*Test the function of the D latch based on the function table in the lab manual*/
		  /*Simulate input, wait 10 ns, then check outputs*/
        /*test for transparency*/
        {En, D} = {2'b10}; #10; passTest({Q, notQ}, 2'b01, "D-latch Enable Test 1", passed);
        {En, D} = {2'b11}; #10; passTest({Q, notQ}, 2'b10, "D-latch Enable Test 2", passed);
        /*test for latching 1*/
        {En, D} = {2'b00}; #10; passTest({Q, notQ}, 2'b10, "D-latch Hold Test 1", passed);
        {En, D} = {2'b01}; #10; passTest({Q, notQ}, 2'b10, "D-latch Hold Test 2", passed);
        {En, D} = {2'b10}; #10; //reset latch
        {En, D} = {2'b00}; #10; passTest({Q, notQ}, 2'b01, "D-latch Hold Test 3", passed);
        {En, D} = {2'b01}; #10; passTest({Q, notQ}, 2'b01, "D-latch Hold Test 4", passed);
       
        allPassed(passed, 6);//did all the tests pass???
        $stop;//that's all folks!

	end
      
endmodule


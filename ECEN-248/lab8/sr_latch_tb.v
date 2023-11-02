`timescale 1ns / 1ps
`define STRLEN 32

module sr_latch_tb;

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
	reg S;
	reg R;

	// Outputs
	wire Q;
	wire notQ;

    reg [7:0] passed;
	// Instantiate the Unit Under Test (UUT)
	sr_latch uut (
		.Q(Q), 
		.notQ(notQ), 
		.En(En), 
		.S(S), 
		.R(R)
	);

	initial begin

        passed = 0;

        /*Test the function of the SR latch based on the function table in the lab manual*/
		  /*Simulate input, wait 10 ns, then check outputs*/
        /*perform an initial Reset of the SR-latch*/
        {En, S, R} = {3'b101}; #10; passTest({Q, notQ}, 2'b01, "SR-latch Reset Test", passed);
        /*Test hold 0*/
        {En, S, R} = {3'b100}; #10; passTest({Q, notQ}, 2'b01, "SR-latch Hold 0 Test", passed);
        /*Test the Set operation*/
        {En, S, R} = {3'b110}; #10; passTest({Q, notQ}, 2'b10, "SR-latch Set Test", passed);
        /*Test hold 1*/
        {En, S, R} = {3'b100}; #10; passTest({Q, notQ}, 2'b10, "SR-latch Hold 1 Test", passed);
        /*Test Reset from Set*/
        {En, S, R} = {3'b101}; #10; passTest({Q, notQ}, 2'b01, "SR-latch Reset from Set Test", passed);
        /*Test Enable hold 0*/
        {En, S, R} = {3'b001}; #10; passTest({Q, notQ}, 2'b01, "SR-latch Enable Hold Test 1", passed);
        {En, S, R} = {3'b010}; #10; passTest({Q, notQ}, 2'b01, "SR-latch Enable Hold Test 2", passed);
        {En, S, R} = {3'b110}; #10; //set latch
        {En, S, R} = {3'b001}; #10; passTest({Q, notQ}, 2'b10, "SR-latch Enable Hold Test 3", passed);
        {En, S, R} = {3'b010}; #10; passTest({Q, notQ}, 2'b10, "SR-latch Enable Hold Test 4", passed);
        
        allPassed(passed, 9);//did all the tests pass???
        $stop;//that's all folks!

	end
      
endmodule


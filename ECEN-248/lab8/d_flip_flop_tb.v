`timescale 1ns / 1ps
`define STRLEN 32

module d_flip_flop_tb;

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
	reg D;
	reg Clk;

	// Outputs
	wire Q;
	wire notQ;

    reg [7:0] passed;
	// Instantiate the Unit Under Test (UUT)
	d_flip_flop uut (
		.Q(Q), 
		.notQ(notQ), 
		.Clk(Clk), 
		.D(D)
	);

    /*generate clock signal*/
    always
        #40 Clk <= ~Clk;
		  
	initial begin

        passed = 0;
        Clk = 0;//initialize clock
    
        D = 0;
        @(posedge Clk) #11; //allow for internal delay in flip-flop
        passTest({Q, notQ}, 2'b01, "D flip-flop Store 0 Test", passed);
        D = 1;
        #5;
        passTest({Q, notQ}, 2'b01, "D flip-flop Hold 0 Test", passed);
        @(posedge Clk) #11; //allow for internal delay in flip-flop
        passTest({Q, notQ}, 2'b10, "D flip-flop Store 1", passed);
        D = 0;
        #1;
        passTest({Q, notQ}, 2'b10, "D flip-flop Hold 1 Test", passed);
		  #5
        @(posedge Clk) #11; //allow for internal delay in flip-flop
        passTest({Q, notQ}, 2'b01, "D flip-flop Store 0 Test Again...", passed);
        
        allPassed(passed, 5);//did all the tests pass???
        $stop;//that's all folks!

	end
      
endmodule


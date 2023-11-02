`timescale 1ns / 1ps //time unit is 1 nano second and the simuation steps are in peco seconds
`define STRLEN 32
`define NUM_TESTS 64


/*This test bench is full of non-synthesizable constructs, which basically means it is
 *restricted to simulation only!*/
module four_bit_alu_tb;

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
	reg [3:0] opA;
	reg [3:0] opB;
	reg [1:0] ctrl;

    /*known answer signals*/
    reg [3:0] Result_check;
    reg Overflow_check;
    reg [7:0] passed;

	// Outputs
	wire [3:0] Result;
    wire Overflow;


	// Instantiate the Unit Under Test (UUT)
	four_bit_alu uut (
		.Result(Result), 
        .Overflow(Overflow),
		.opA(opA), 
		.opB(opB), 
		.ctrl(ctrl)
	);

	initial begin
		// Initialize Inputs
        passed = 0;
    
        // Add stimulus here		
        /*specifically ensure overflow will not be triggered during an AND operation*/
        opA = 4'b0110;
        opB = 4'b0110; //will cause overflow in the case of an add (i.e. ctrl[1] = 0)
        ctrl = 2'b00;
    
        repeat(`NUM_TESTS)//do `NUM_TESTS times over...
          begin
            /*compute expected result*/
            if(ctrl[0] == 1'b0)//if bit-wise AND
              begin
                Result_check = opA & opB;
                Overflow_check = 1'b0;//should always be 0
              end
            else if(ctrl == 2'b01)//if add
              begin
                Result_check = opA + opB;
                Overflow_check = ((opA[3] & opB[3] & ~Result_check[3]) | (~opA[3] & ~opB[3] & Result_check[3]));
              end
            else if(ctrl == 2'b11) //if subtract
              begin
                Result_check = opA - opB;
                Overflow_check = ((opA[3] & ~opB[3] & ~Result_check[3]) | (~opA[3] & opB[3] & Result_check[3]));
              end
            else
              begin
                Result_check = 4'bXXXX;
                Overflow_check = 1'bX;
              end 
            #10; //delay!  basically wait 10 time units
            /*perform a known answer test*/
            passTest({Overflow, Result}, {Overflow_check, Result_check}, "Arithmetic Logic Unit Test", passed);
            /*generate a new random set of inputs  sort of a Monte Carlo simulation!*/
            opA = $random;
            opB = $random;
            ctrl = $random;
          end
        /*check to see if all tests passed*/
        allPassed(passed, `NUM_TESTS);
        $stop; //halt simulation cause we are done!
	end
      
endmodule


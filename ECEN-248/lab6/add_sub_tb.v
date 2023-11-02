`timescale 1ns / 1ps //time unit is 1 nano second the time step is 1 peco second
`define STRLEN 32
`define NUM_TESTS 32

/*This test bench is full of non-synthesizable constructs, which basically means it is
 *restricted to simulation only!*/
module add_sub_tb;

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
	reg opSel;
    
    /*known answer signals*/
    reg [3:0] Result_check;
    reg Overflow_check;
    reg [7:0] passed;

	// Outputs
	wire [3:0] Sum;
    wire Overflow;


	// Instantiate the Unit Under Test (UUT)
	add_sub uut (
		.Sum(Sum), 
        .Overflow(Overflow),
		.opA(opA), 
		.opB(opB), 
		.opSel(opSel)
	);

	initial begin
		// Initialize Inputs
		opA = 0;
		opB = 0;
		opSel = 0;
        passed = 0;
    
        // Add stimulus here		
        repeat(`NUM_TESTS)//do `NUM_TESTS times over...
          begin
            /*compute expected result*/
            if(opSel) //if subtract
              begin
                Result_check = opA - opB;
                Overflow_check = ((opA[3] & ~opB[3] & ~Result_check[3]) | (~opA[3] & opB[3] & Result_check[3]));
              end
            else //if add
              begin
                Result_check = opA + opB;
                Overflow_check = ((opA[3] & opB[3] & ~Result_check[3]) | (~opA[3] & ~opB[3] & Result_check[3]));
              end
            
            #10; //delay! basically wait 10 time units
            /*perform a known answer test*/ 
            passTest({Overflow, Sum}, {Overflow_check, Result_check}, "Addition/Subtraction Unit Test", passed);
            /*generate a new random set of inputs  sort of a Monte Carlo simulation!*/
            opA = $random;
            opB = $random;
            opSel = $random;
          end
        /*check to see if all tests passed*/
        allPassed(passed, `NUM_TESTS);
        $stop; //hault simulation cause we are done!
	end
      
endmodule


// Code your testbench here
// or browse Examples
// Code your testbench here
// or browse Examples
`timescale 1ns / 1ps
`define STRLEN 32
module NextPClogicTest;


task passTest;
          input [63:0] actualValue, expectedValue; //will use these to compare what output is obtained and what output should have been obtained
        input [`STRLEN*8:0] testType;
          inout [7:0] passed; //number of passed tests

        
        if(actualValue == expectedValue) 
            begin
              $display("%s passed\n", testType); //display what test passed
                passed = passed + 1; // increment the passed count by 1

        end
        else
          $display("%s failed: %b should be %b", testType, actualValue, expectedValue);//if the test does not passed, then display what we should have gotten
    endtask
    
    task allPassed;//set all passed test
        input [13:0] passed; //input passed is 14 bits
        input [13:0] numTests; //input numtests is 14 bits
        
        if(passed == numTests) 
          $display("All tests passed"); //if all tests passed, print 
        else
          $display("Some test failed"); //if some tests failed, print
    endtask


	// Inputs
	reg [63:0] CurrentPC, SignExtImm64;
	reg Branch, ALUZero, Uncondbranch;
	reg [7:0] passed;
	reg [7:0] numTests;
	// Outputs
	wire [63:0] NextPC;

	reg[63:0] expectedNextPC;
	// Instantiate the Unit Under Test (UUT)
	NextPClogic uut(
		.CurrentPC(CurrentPC),
		.SignExtImm64(SignExtImm64),
		.Branch(Branch),
		.ALUZero(ALUZero),
		.Uncondbranch(Uncondbranch),
		.NextPC(NextPC));

	initial begin
      $dumpfile("dump.vcd"); $dumpvars;
      $dumpvars(0, NextPClogicTest);
		// Initialize Inputs
		CurrentPC = 64'b0;
		SignExtImm64 = 64'b0;
		Branch = 1'b0;
		ALUZero = 1'b0;
		Uncondbranch = 1'b0;
		passed = 7'b0;
		numTests = 7'b0;
		
		
		CurrentPC = 64'h10;
		SignExtImm64 = 64'b0;
		Branch = 1'b0;
		ALUZero = 1'b0;
		Uncondbranch = 1'b0;
		expectedNextPC = 64'h14;
		#10;
      
      $display("Current PC: %h, SignExtImm64: %h, Branch: %b, ALUZero: %b, Unconditoinalbranch: %b, expectedNextPC: %h",CurrentPC,SignExtImm64, Branch, ALUZero, Uncondbranch, expectedNextPC);
		passTest(NextPC, expectedNextPC, "PC+4 Test", passed);

      
      
		
      
		CurrentPC = 64'h10;
		SignExtImm64 = 64'h2;
		Branch = 1'b1;
		ALUZero = 1'b1;
		Uncondbranch = 1'b0;
		expectedNextPC = 64'h18;
		#10;
      
      
        $display("Current PC: %h, SignExtImm64: %h, Branch: %b, ALUZero: %b, Unconditoinalbranch: %b, expectedNextPC: %h",CurrentPC,SignExtImm64, Branch, ALUZero, Uncondbranch, expectedNextPC);
      passTest(NextPC, expectedNextPC, "Conditional - Take Branch Test", passed);

      
      
      

		CurrentPC = 64'h10;
		SignExtImm64 = 64'h3;
		Branch = 1'b1;
		ALUZero = 1'b0;
		Uncondbranch = 1'b0;
		expectedNextPC = 64'h14;
		#10;
      
      
        $display("Current PC: %h, SignExtImm64: %h, Branch: %b, ALUZero: %b, Unconditoinalbranch: %b, expectedNextPC: %h",CurrentPC,SignExtImm64, Branch, ALUZero, Uncondbranch, expectedNextPC);
		passTest(NextPC, expectedNextPC, "Conditional - Don't Take Branch Test", passed);

		
      
      
		CurrentPC = 64'h10;
		SignExtImm64 = 64'h4;
		Branch = 1'b0;
		ALUZero = 1'b0;
		Uncondbranch = 1'b1;
		expectedNextPC = 64'h20;
		#10;
      
      
        $display("Current PC: %h, SignExtImm64: %h, Branch: %b, ALUZero: %b, Unconditoinalbranch: %b, expectedNextPC: %h",CurrentPC,SignExtImm64, Branch, ALUZero, Uncondbranch, expectedNextPC);
		passTest(NextPC, expectedNextPC, "Unconditional Branch Test", passed);

      
      allPassed(passed, 4);

		$finish;
	end
      
endmodule
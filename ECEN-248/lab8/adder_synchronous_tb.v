`timescale 1ns / 1ps
`define STRLEN 32
`define CLOCK_PERIOD 20

module adder_synchronous_tb;

   /*A task is similar to a procedure in the traditional programming language*/
   /*This particular task simply checks the output of our circuit against a 
     known answer and prints a message based on the outcome. Additionally, 
     this task increments the variable we are using to keep track of the 
     number of tests successfully passed.*/
   task passTest;
		input [4:0] actualOut, expectedOut;
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
	reg [1:0] A, B;
	reg Clk;

	// Outputs
	wire Carry_reg;
	wire [1:0] Sum_reg;

    //internal test regs
    reg [1:0] A_reg, B_reg;
    reg [2:0] KnownAnswer;

    reg [7:0] passed;
	// Instantiate the Unit Under Test (UUT)
	adder_synchronous
	 uut (
		.A(A),
		.B(B),
		.Clk(Clk), 
		.Carry_reg(Carry_reg),
        .Sum_reg(Sum_reg)
	);

    /*generate clock signal*/
    always
        #(`CLOCK_PERIOD/2) Clk <= ~Clk;
		  
    /*compute known answer*/
    always@(posedge Clk)
      begin
      B_reg <= B;
        A_reg <= A;
        KnownAnswer <= A_reg + B_reg;
      end

	initial begin
        A = 0;
        B = 0;
        passed = 0;
        Clk = 0;//initialize clock

        @(posedge Clk); //wait for data to get clocked into adder    
        {A, B} = 0;
        repeat(16)@(posedge Clk)  //wait for clock period
          begin
            #(`CLOCK_PERIOD/2) {A, B} = {A, B} + 1;
            passTest({Carry_reg, Sum_reg}, KnownAnswer, "Synchronous Adder Test", passed);
          end
        allPassed(passed, 16);//did all the tests pass???
        $stop;//that's all folks!

	end
      
endmodule


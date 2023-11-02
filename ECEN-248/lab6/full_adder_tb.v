`timescale 1ns / 1ps
`define STRLEN 32

module full_adder_tb;

   task passTest;
		input [1:0] actualOut, expectedOut;
		input [`STRLEN*8:0] testType;
		inout [7:0] passed;
	
		if(actualOut == expectedOut) begin $display ("%s passed", testType); passed = passed + 1; end
		else $display ("%s failed: %x should be %x", testType, actualOut, expectedOut);
	endtask
	
	task allPassed;
		input [7:0] passed;
		input [7:0] numTests;
		
		if(passed == numTests) $display ("All tests passed");
		else $display("Some tests failed");
	endtask

	// Inputs
	reg A;
	reg B;
    reg Cin;
    
    reg [7:0] passed;

	// Outputs
	wire S, Cout;

	// Instantiate the Unit Under Test (UUT)
	full_adder uut (
		.Cin(Cin), 
		.A(A), 
		.B(B), 
		.S(S),
        .Cout(Cout)
	);

	initial begin
		// Initialize Inputs
		A = 0;
		B = 0;
		Cin = 0;
        passed = 0;
    
        // Add stimulus here		
        {A, B, Cin} = {3'b000}; #10; passTest({Cout, S}, 2'b00, "Full Adder Test 1", passed);
        {A, B, Cin} = {3'b001}; #10; passTest({Cout, S}, 2'b01, "Full Adder Test 2", passed);
        {A, B, Cin} = {3'b010}; #10; passTest({Cout, S}, 2'b01, "Full Adder Test 3", passed);
        {A, B, Cin} = {3'b011}; #10; passTest({Cout, S}, 2'b10, "Full Adder Test 4", passed);
        {A, B, Cin} = {3'b100}; #10; passTest({Cout, S}, 2'b01, "Full Adder Test 5", passed);
        {A, B, Cin} = {3'b101}; #10; passTest({Cout, S}, 2'b10, "Full Adder Test 6", passed);
        {A, B, Cin} = {3'b110}; #10; passTest({Cout, S}, 2'b10, "Full Adder Test 7", passed);
        {A, B, Cin} = {3'b111}; #10; passTest({Cout, S}, 2'b11, "Full Adder Test 8", passed);
        allPassed(passed, 8);
        $stop;
	end
      
endmodule


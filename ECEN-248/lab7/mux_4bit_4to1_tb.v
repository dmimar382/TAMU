`timescale 1ns / 1ps //time unit is 1 nano second and the simulation steps are in peco seconds
`define STRLEN 32
`define NUM_TESTS 32

/*This test bench is full of non-synthesizable constructs, which basically means it is
 *restricted to simulation only!*/
module mux_4bit_4to1_tb;

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
    reg [3:0] A, B, C, D;
    reg [1:0] S;

    //test regs
    reg [3:0] Out;
    reg [7:0] passed;

    // Outputs
    wire [3:0] Y;

    // Instantiate the Unit Under Test (UUT)
    mux_4bit_4to1 uut (
        .Y(Y), 
        .A(A), 
        .B(B),
        .C(C),
        .D(D), 
        .S(S)
    );

    initial begin
        // Initialize Inputs
        A = 0;
        B = 0;
        C = 0;
        D = 0;
        S = 0;
        passed = 0;
   
        repeat(`NUM_TESTS) //do `NUM_TESTS times over...
          begin
            if(S == 2'b00)
                Out = A;
            else if(S == 2'b01)
                Out = B;
            else if(S == 2'b10)
                Out = C;
            else //only one option left!
                Out = D;
            #10;
            passTest(Y, Out, "4-bit 4:1 MUX Test", passed);
            /*generate a new random set of inputs  sort of a Monte Carlo simulation!*/
            A = $random;
            B = $random;
            C = $random;
            D = $random;
            S = $random;
          end
        allPassed(passed, `NUM_TESTS);//did all the tests pass???
        $stop;//that's all folks!
    end
      
endmodule


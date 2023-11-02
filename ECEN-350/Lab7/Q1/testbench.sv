// Code your testbench here
// or browse Examples
`timescale 1ns / 1ps
`define STRLEN 15
module SignExtender_tb(); //defining the module 
    
        task passTest;
          input [63:0] actualValue, expectedValue; //will use these to compare what output is obtained and what output should have been obtained
        input [`STRLEN*8:0] testType;
          inout [7:0] passed; //number of passed tests

        
        if(actualValue == expectedValue) 
            begin
              $display("%s passed", testType); //display what test passed
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
    
  //defining inputs and outputs
    reg [31:0] Imm32; 
  	reg Ctrl;
    reg [7:0] passed; 
    wire [63:0] BusImm; 
  
  //instantiating module
  SignExtender UUT(.BusImm(BusImm), .Ctrl(Ctrl), .Imm32(Imm32)); 
    
    initial begin
      
            
      $dumpfile("test.vcd");
      $dumpvars(0,SignExtender_tb);
      
        Imm32 = 0; 
        passed = 0;
        
      #90; Imm32[31:26] = 6'b000101; Ctrl = 1; Imm32[25:0] = 1; #10; passTest(BusImm, 1, "B", passed); //expected output is 1
      #90; Imm32[31:26] = 6'b000101; Ctrl = 0; Imm32[25:0] = -1; #10; passTest(BusImm, -1, "B", passed); //expected output is -1
      
      #90; Imm32[31:24] = 8'b10110100;  Ctrl = 1; Imm32[23:5] = 1; #10; passTest(BusImm, 1, "CBZ", passed); //expected output is 1
      #90; Imm32[31:24] = 8'b10110100; Ctrl = 0; Imm32[23:5] = -1; #10; passTest(BusImm, -1, "CBZ", passed); //expected output is -1
      
      #90; Imm32[31:21] = 11'b11111000010; Ctrl = 1; Imm32[20:12] = 1; #10; passTest(BusImm, 1, "LDUR", passed); //expected output is 1
      #90; Imm32[31:21] = 11'b11111000010; Ctrl = 0; Imm32[20:12] = -1; #10; passTest(BusImm, -1, "LDUR", passed); //expected output is -1
      
      #90; Imm32[31:21] = 11'b11111000000; Ctrl = 1; Imm32[20:12] = 1; #10; passTest(BusImm, 1, "STUR", passed); //expected output is 1
      #90; Imm32[31:21] = 11'b11111000000; Ctrl = 0; Imm32[20:12] = -1; #10; passTest(BusImm, -1, "STUR", passed); //expected output is -1
      
      #90; Imm32[31:22] = 10'b1001000100; Ctrl = 0; Imm32[21:10] = -1; #10; passTest(BusImm, -1, "ADDI", passed); //expected output is -1
      #90; Imm32[31:22] = 10'b1001000100; Ctrl = 1; Imm32[21:10] = 1; #10; passTest(BusImm, 1, "ADDI", passed); //expected output is 1
      
      
      #90; Imm32[31:22] = 10'b1101000100; Ctrl = 0; Imm32[21:10] = -1; #10; passTest(BusImm, -1, "SUBI", passed); //expected output is -1
      #90; Imm32[31:22] = 10'b1101000100; Ctrl = 1; Imm32[21:10] = 1; #10; passTest(BusImm, 1, "SUBI", passed); //expected output is 1
      
       
      #90 allPassed(passed, 12); // all passed if 16 passed
    end
        
endmodule

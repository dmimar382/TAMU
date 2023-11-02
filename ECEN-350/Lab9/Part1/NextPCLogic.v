`timescale 1ns / 1ps

module NextPClogic(NextPC, CurrentPC, SignExtImm64, Branch, ALUZero, Uncondbranch); 
       	input [63:0] CurrentPC, SignExtImm64; 
       	input Branch, ALUZero, Uncondbranch; 
       	output reg [63:0] NextPC; 

    always @(*) begin
   	
      if(Uncondbranch || (Branch && ALUZero)) begin
          NextPC  <= CurrentPC + (SignExtImm64 << 2); // jumps to address
       	end

      else begin // branch and Uncondbranch are false
          NextPC <= CurrentPC + 4;
       	end
   	end

endmodule
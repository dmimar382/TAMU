// Code your design here

module SignExtender(BusImm, Imm32, Ctrl); 
  output  reg [63:0] BusImm; 
  input [31:0] Imm32; 
  input Ctrl; 

  reg extBit;
  //need I, B, D and CBZ instruction support
  
  always@(*) begin
  
  if (Imm32[31:26] == 6'b000101 || 
      Imm32[31:26] == 6'b100101) //This is a B type instruction
    begin  
      assign  extBit = (Ctrl ? 1'b0 : Imm32[25]);
      #1 assign BusImm = {{38{extBit}}, Imm32[25:0]};
    end
    
    else if (Imm32[31:24] ==8'b10110100 || 
             Imm32[31:24] ==8'b01010100 || 
             Imm32[31:24] ==8'b10110101 ) //This is a CB instruction
      begin
        assign extBit = (Ctrl ? 1'b0 : Imm32[23]); 
        #1 assign BusImm = {{45{extBit}}, Imm32[23:5]};
      end 
    
    else if (Imm32[31:21] == 11'b00111000000 ||
             Imm32[31:21] == 11'b00111000010 ||
             Imm32[31:21] == 11'b01111000000 || 
             Imm32[31:21] == 11'b01111000010 ||
             Imm32[31:21] == 11'b10111000000 ||
             Imm32[31:21] == 11'b10111000100 || 
			 Imm32[31:21] == 11'b11001000000 || 
			 Imm32[31:21] == 11'b11001000010 ||
			 Imm32[31:21] == 11'b11111000000 || 
        	 Imm32[31:21] == 11'b11111000010) //This is a D type instruction
      begin
        assign extBit = (Ctrl ? 1'b0 : Imm32[20]); 
        #1 assign BusImm = {{55{extBit}}, Imm32[20:12]};
      end
    
    else if(Imm32[31:22] == 10'b1001000100 ||
            Imm32[31:22] == 10'b1001001000 ||
            Imm32[31:22] == 10'b1011000100 ||
            Imm32[31:22] == 10'b1011001000 ||
            Imm32[31:22] == 10'b1101000100 ||
            Imm32[31:22] == 10'b1101001000 ||
            Imm32[31:22] == 10'b1111000100 ||
            Imm32[31:22] == 10'b1111001000) //This is an I type instruction
      begin
        assign extBit = (Ctrl ? 1'b0 : Imm32[21]); 
        #1 assign BusImm = {{52{extBit}}, Imm32[21:10]};
      end
        
    end
endmodule
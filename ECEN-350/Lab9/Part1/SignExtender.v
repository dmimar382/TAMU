`define Btype 2'b00
`define Itype 2'b01
`define Dtype 2'b10
`define CBZtype 2'b11


module SignExtender(BusImm, Imm26, Ctrl); 
  output  reg [63:0] BusImm; 
  input [25:0] Imm26; 
  input [1:0] Ctrl; 

  reg extBit;
  //need I, B, D and CBZ instruction support
  
  always@(Imm26 or Ctrl) begin
    case(Ctrl)
      `Btype: begin
        extBit = Imm26[25];
        BusImm = {{38{extBit}},Imm26};
      end
      `Itype: begin
        //extBit = Imm26[21];
        BusImm = {{52{1'b0}},Imm26[21:10]};
      end
      `Dtype: begin
        extBit = Imm26[20];
        BusImm = {{55{extBit}},Imm26[20:12]};
      end
      `CBZtype: begin
        extBit = Imm26[23];
        BusImm = {{45{extBit}},Imm26[23:5]};        
      end
    endcase        
  end
  
endmodule
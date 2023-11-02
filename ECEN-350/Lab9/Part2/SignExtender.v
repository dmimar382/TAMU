`define Btype 3'b000
`define Itype 3'b001
`define Dtype 3'b010
`define CBZtype 3'b011
`define MOVZtype 3'b100


module SignExtender(BusImm, Imm26, Ctrl); 
  output  reg [63:0] BusImm; 
  input [25:0] Imm26; 
  input [2:0] Ctrl; 

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
     `MOVZtype: begin
        if(Imm26[22:21] == 2'b00)
          BusImm = {{48{1'b0}},Imm26[20:5]};//0    
        else if(Imm26[22:21] == 2'b01)
          BusImm = {{32'b0},Imm26[20:5],{16'b0}}; //16
        else if(Imm26[22:21] == 2'b10)
          BusImm = {{16'b0},Imm26[20:5],{32'b0}};  //32
        else
          BusImm = {Imm26[20:5],{48'b0}};//48    
      end
      
    endcase        
  end
  
endmodule
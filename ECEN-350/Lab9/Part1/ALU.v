// Code your design here
`timescale 1ns / 1ps

module ALU(BusW, Zero , BusA , BusB , ALUCtrl );
  
  //declare inputs and outputs
  input [63:0] BusA, BusB;
  input [3:0] ALUCtrl;
  output [63:0] BusW;
  output Zero;
  
  reg [63:0] BusW;
  reg Zero;
  
  always@(ALUCtrl or BusA or BusB)
    begin
      case(ALUCtrl)
        4'b0000: //AND
          BusW <= BusA & BusB;
        4'b0001: //OR
          BusW <= BusA | BusB;
        4'b0010: //ADD
          BusW <=  BusA + BusB;
        4'b0110: //SUB
          BusW <=  BusA - BusB;
         4'b0111: //PASSB
          BusW <=  BusB;
      endcase
     end
        
 always@(BusW)
   begin
     if(BusW == 0) 
          Zero <= 1;
     else
          Zero <= 0;
       
    end
     
        
endmodule
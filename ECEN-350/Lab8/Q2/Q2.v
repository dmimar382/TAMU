
module RegisterFile(BusA, BusB, BusW, RA, RB, RW, RegWr, Clk);
    output [63:0] BusA;
    output [63:0] BusB;
    input [63:0] BusW;
    input [4:0] RW, RA, RB;//input registers
    input RegWr;
    input Clk;
  	reg [63:0] registers [31:0];
     
  assign #2 BusA = (RA==31)? 64'b0 : registers[RA];//register A gets passed to BusA
  assign #2 BusB = (RB==31)? 64'b0:registers[RB];
  
     
    /*initial begin
      for(int i = 0; i < 32; i = i + 1) begin //initialize all of the register values to 0
            registers[i] <= 0;
        end
    end*/
  
    always @ (negedge Clk) begin
      registers[31]<= #3 0;  //always have register 31 as 0
      if(RegWr) begin
        if(RW !=31) begin //if not the 31st register, then assign RW with the value of BusW 
            registers[RW] <= #3 BusW;
        end
      end
    end
endmodule
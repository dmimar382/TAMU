module Mux21(out, in, sel);

//declare inputs and outputs
  input [1:0] in;
  input sel;
  output out;
  
//declare intermediate wires
  wire O1, O2, O3;//intermediate wires
  
//connection logic
  nand n0(O1, sel, sel);
  nand n1(O2, in[1],sel);
  nand n2(O3, O1, in[0]);
  nand n3(out, O2,O3);

  
endmodule//designte end of module
module HalfAdd(Cout, Sum, A,B);

//declaring inputs, outputs and intermediate wires
  input A,B;
  output Sum, Cout;
  wire O1, O2, O3;//intermediate wires
  
//connection wiring 
  nand n0(O1, A,B);
  nand n1(O2, O1, A);
  nand n2(O3, O1, B);
  nand n3(Sum, O2,O3);
  nand n4(Cout, O1, O1);
  
endmodule //designate end of module
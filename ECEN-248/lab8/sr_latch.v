`timescale 1ns/1ps //delay unit is 1ns 

module sr_latch(Q, notQ, En, S, R);

//declare all ports
output wire Q, notQ;
input wire En, S, R;

//intermediate nets
//nandSEN is the output of NAND(S,EN)
//nandREN is the output of NAND(R,EN)

wire nandSEN, nandREN;
//delay of nand0 is 2ns

nand #4 nand1(Q,nandSEN,notQ);
nand #4 nand2(nandSEN, S, En);
nand #4 nand3(nandREN, R,En);
nand #4 nand4(notQ, nandREN, Q);

endmodule //designate end of module 
`timescale 1ns/1ps 

module d_latch(Q,notQ,En, D, notD);

//declare all ports
output wire Q, notQ;
input wire En,D,notD;

//define internal nets
not #2 not0(notD, D);
wire nandDEN, nandnotDEN;

//define each nand gate in d-latch
nand #2 nand1(nandDEN,En,D);            //delay of each nand gate is 2ns
nand #2 nand2(nandnotDEN, En, notD);
nand #2 nand3(Q,nandDEN,notQ);
nand #2 nand4(notQ, nandnotDEN, Q);

endmodule //designate end of module 

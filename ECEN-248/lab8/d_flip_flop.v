`timescale 1ns/1ps //delay unit is 1ns
module d_flip_flop(Q,notQ,Clk,D);
//declare all ports
output wire Q,notQ; //outputs of slave
input wire Clk,D;

//intermediate nets 
wire notClk;
wire notnotClk;
wire Qm; //output of master
//not Qm is used in instantiation
//but left unconnected 

wire notQm;
not #2 not1(notClk,Clk);        //instantiate not gate
not #2 not2(notnotClk,notClk);  //instantiate not gate

//instantiate the D-latches
d_latch flip1(Qm,notQm,notClk,D);
d_latch flip2(Q, notQ,notnotClk,Qm);

endmodule //designate end of module
`timescale 1ns / 1ps
`default_nettype none
module up_counter_tb;

	/* Inputs */
	reg En;
	reg Clk;
	reg Rst;

	/* Outputs */
	wire [2:0] Count;
	wire Carry2;

	/* Instantiate the Unit Under Test (UUT) */
	up_counter uut (
		.Count(Count), 
		.Carry2(Carry2), 
		.En(En), 
		.Clk(Clk), 
		.Rst(Rst)
	);

	/*generate Clk signal*/
	always
		#10 Clk <= ~Clk;
	
	initial begin
		/* Initialize Inputs */
		En = 0;
		Clk = 0;
		Rst = 1; //Reset is active HIGH

		// Wait 20 ns for global reset to finish
		#20;
        
		Rst = 0;
		
		#20; //test hold when En is low...
		En = 1;//let it count away...

	end
      
endmodule


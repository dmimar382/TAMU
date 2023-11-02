`timescale 1ns / 1ps
`default_nettype none
module bounce_tb;

	/* Inputs */
	reg Clk;
	reg Bounced_BTN;

	/* Outputs */
	wire [3:0] LEDs;
	reg Is_BTN_Pressed;

	/* Instantiate the Unit Under Test (UUT) */
	noDebounce uut (
		.LEDs(LEDs), 
		.Clk(Clk), 
		.BTN(Bounced_BTN)
	);

	/*generate Clk signal*/
	always
		#4 Clk <= ~Clk;
	
	initial begin
		/* Initialize Inputs */
		Clk = 0;
		Bounced_BTN=0;
		Is_BTN_Pressed=0;
        /*first time the BTN is pressed*/
		#200;
		Bounced_BTN=1;
        Is_BTN_Pressed=1;
        #10;
		Bounced_BTN=0;
		#20;
		Bounced_BTN=1;
		#15;
        Bounced_BTN=0;
        #5;
        Bounced_BTN=1;
		#200; 
        Bounced_BTN=0;
        Is_BTN_Pressed=0;
        /*2nd time the BTN is pressed*/
        #200;
        Bounced_BTN=1;
        Is_BTN_Pressed=1;
        #5;
        Bounced_BTN=0;
        #25;
        Bounced_BTN=1;
        #5;
        Bounced_BTN=0;
        #5;
        Bounced_BTN=1;
        #200; 
        Bounced_BTN=0;
        Is_BTN_Pressed=0;
         /*3rd time the BTN is pressed*/
        #200;
        Bounced_BTN=1;
        Is_BTN_Pressed=1;
        #8;
        Bounced_BTN=0;
        #10;
        Bounced_BTN=1;
        #5;
        Bounced_BTN=0;
        #5;
        Bounced_BTN=1;
        #200;
        Bounced_BTN=0;
        Is_BTN_Pressed=0;
        /*4th time the BTN is pressed*/
       #200;
       Bounced_BTN=1;
       Is_BTN_Pressed=1;
       #10;
       Bounced_BTN=0;
       #12;
       Bounced_BTN=1;
       #8;
       Bounced_BTN=0;
       #5;
       Bounced_BTN=1;
       #200; 
       Bounced_BTN=0;
       Is_BTN_Pressed=0;
      /*5th time the BTN is pressed*/
      #300;
      Bounced_BTN=1;
      Is_BTN_Pressed=1;
      #200; 
      Bounced_BTN=0;
      Is_BTN_Pressed=0;
      /*6th time the BTN is pressed*/
      #200;
      Bounced_BTN=1;
      Is_BTN_Pressed=1;
      #10;
      Bounced_BTN=0;
      #14;
      Bounced_BTN=1;
      #18;
      Bounced_BTN=0;
      #15;
      Bounced_BTN=1;
      #200; 
      Bounced_BTN=0;
      Is_BTN_Pressed=0;
	end
      
endmodule

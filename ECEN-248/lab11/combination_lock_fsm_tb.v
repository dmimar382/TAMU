`timescale 1ns / 1ps

module combination_lock_fsm_tb;

  parameter     S0 = 2'b00,                   //assigning each state to a binary number 
                    S1 = 2'b01, 
                    S2 = 2'b10, 
                    S3 = 2'b11; 

	// Inputs
	reg Key1,Key2;	
	reg Clk;
	reg Reset;
	reg [3:0] Password;

	// Outputs
	wire [3:0]Lock;
	wire [1:0] state;
	
	reg passed;

	// Instantiate the Unit Under Test (UUT)
	combination_lock_fsm uut (
		.Lock(Lock), 
		.state(state), 
		.Clk(Clk), 
		.Key1(Key1),
		.Key2(Key2),
		.Reset(Reset), 
		.Password(Password)
	);

	/*generate clock signal*/
	always
		#5 Clk <= ~Clk;


	initial begin
		// Initialize Inputs
        Key1 = 0; 
        Key2=0;
		Clk = 1;
		Reset = 1;
		Password = 0;
		passed = 1;//innocent until proven otherwise!

		/*hold reset for a couple clocks*/
		#20 Reset = 0;
		#10;
		
		/*Ensure we remain in S0*/
		//Left = 1;
		#10; 
		if(state != S0)
		  begin
			$display("Error with S0!");
			passed = 0; //signal failure!
			$stop;
		  end
        if(Lock != 0)
		  begin
			$display("Error with Lock signal in S0!");
			passed = 0; //signal failure!
			$stop;
		  end

		#5;
		/*attempt to transition to S1*/
		Key1= 1;
		Password = 4'b1101; 
		#10;
		if(state !=S1)
		  begin
			$display("Failed to transition to S1!");
			passed = 0; //signal failure!
			$stop;
		  end
        if(Lock != 0)
		  begin
			$display("Error with Locked signal in S1!");
			passed = 0; //signal failure!
			$stop;
		  end
		/*test hold in S1*/
		Key1=0;
		#10;
		if(state !=S1)
		  begin
			$display("Failed to stay in S1!");
			passed = 0; //signal failure!
			$stop;
		  end		
		  /*test wrong Password*/
		 Key2=1;
		 Password = 1; 
         #10;
         if(state !=S0)
          begin
          $display("Failed to go back to S0!");
            passed = 0; //signal failure!
          $stop;
         end    
         /*attempt to transition to S1*/
                 Key1 = 1;
                 Key2 = 0;
                 Password = 4'b1101; 
                 #10;
                 if(state !=S1)
                   begin
                     $display("Failed to transition to S1!");
                     passed = 0; //signal failure!
                     $stop;
                   end
                 if(Lock != 0)
                   begin
                     $display("Error with Locked signal in S1!");
                     passed = 0; //signal failure!
                     $stop;
                   end
		/*attempt to transition to S2*/
		Key2 = 1;
		Key1 = 0;
        Password = 7; 
        #10
        Key2=0;
		#10;
		if(state !=S2)
		  begin
			$display("Failed to transition to S2!");
			passed = 0; //signal failure!
			$stop;
		  end
        if(Lock != 0)
		  begin
			$display("Error with Locked signal in S2!");
			passed = 0; //signal failure!
			$stop;
		  end

		/*test hold in S2*/
		#10;
		if(state !=S2)
		  begin
			$display("Failed to stay in S2!");
			passed = 0; //signal failure!
			$stop;
		  end
		/*okay put in the rest of the combination*/
		Key1 = 1;
		Key2 = 0;
        Password = 9;
        #10
        Key1=0; 
		#10;
		if(state !=S3)
		  begin
			$display("Failed to transition to S3!");
			passed = 0; //signal failure!
			$stop;
		  end	
        if(Lock != 4'b1111)
		  begin
			$display("Error with Locked signal in S3!");
			passed = 0; //signal failure!
			$stop;
		  end

		/*test reset*/
		Reset = 1; 
		#10;
		if(state !=S0)
		  begin
			$display("Failed to reset!");
			passed = 0; //signal failure!
			$stop;
		  end
			
		#10;	
		if(passed)
			$display("All Tests Passed!!!");
	   $stop;
	end
      
endmodule


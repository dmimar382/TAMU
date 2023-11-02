
//module interface for the 2:4 decoder
module Decode24(out, in);

input wire [1:0] in;
output reg [3:0] out; //out is a 4-bit output of type reg

always@(in) //trigger when in changes 
begin 
    case(in) //selection based on in
        2'b00: out= 4'b0001; //4'b signifies a 4-bit binary value 
        2'b01: out= 4'b0010;// input is 1, output is 2
        2'b10: out= 4'b0100;// input is 2, output is 4
        2'b11: out= 4'b1000;// input is 3, output is 8
    endcase // desigates end of case statement 
 
end
endmodule //designates end of module
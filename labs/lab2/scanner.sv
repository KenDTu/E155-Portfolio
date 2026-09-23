// Author: Ken TU 
// Email: ktu@g.hmc.edu
// Date of Creation: 09/22/2026
// Scanner module for the scanning section for lab 2

module scanner(input  logic       clk, // when instantiating pass int_osc
			   input  logic       reset,
			   input  logic       enable,
			   input  logic [3:0] column, // when instantiating pass off-board switchRight
			   output logic [3:0] row
);
	logic [22:0] counter; // this logic must toggle at 2Hz
	logic [1:0]  rowNum;  // R0 - 00, R1 - 01, R2 - 10, or R3 - 11

	counter #(.max(5_999_999)) counterScanner(.clk(clk), .reset(reset), .enable(enable), .counter(counter));
	
	// asserting each row every 2Hz
	always_ff @(posedge clk, negedge reset)
		begin
			if(reset == 0) 
					 rowNum <= 2'b00;
			else if (enable == 1 && counter == 5_999_999) rowNum <= rowNum + 1;
		end
		
	// Checking the assertion of the row
	always_comb 
		case (rowNum) // checking which row is asserted
			2'b00:    row = 4'b0001; // R0
			2'b01:    row = 4'b0010; // R1
			2'b10:    row = 4'b0100; // R2
			2'b11:    row = 4'b1000; // R3
			default:  row = 4'b0001; // R0
		endcase
	
	
	
endmodule

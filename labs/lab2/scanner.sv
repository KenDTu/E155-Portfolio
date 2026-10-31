// Author: Ken TU 
// Email: ktu@g.hmc.edu
// Date of Creation: 09/22/2026
// Scanner module for the scanning section for lab 2
`timescale 1 ns/1 ps
module scanner #(parameter counterWidth = 25, parameter max = 8_999_999)
			  (input  logic       clk, // when instantiating pass int_osc
			   input  logic       reset,
			   input  logic       enable,
			   // input  logic [3:0] column, // when instantiating pass off-board switchRight
			   output logic [3:0] switchRight   // drives the 4 NPN gates and performs the row scanning AKA row
			   // output logic [3:0] keyLead // off-board LED shows the pressed column
);
	logic [counterWidth-1:0] counter; // this logic must toggle at 2Hz

	counter #(.counterWidth(counterWidth), .max(max)) counterScanner(.clk(clk), .reset(reset), .enable(enable), .counter(counter));
	
	always_ff @(posedge clk) // , negedge reset
		begin
			// if (counter == 999_999) rowNum <= rowNum + 1; // 
			if (counter < max/4) 
				switchRight = 4'b0001; // R0
			else if (max/4 < counter && counter < max/2) 
				switchRight = 4'b0010; // R1
			else if (max/2 < counter && counter < 3*max/4) 
				switchRight = 4'b0100; // R1
			else if (3*max/4 < counter && counter < max) 
				switchRight = 4'b1000; // R2
			else 
				switchRight = 4'b1111;
		end
		
endmodule

// Author: Ken TU
// Email: ktu@g.hmc.edu
// Date of Creation: 09/20/2026
// Counter divider to divide the 24MHz int_osc
`timescale 1 ns/1 ps
// counterWidth = 2^19 = 524,288 ≥ 400,000, 18
// clock math is 24MHz / 400,000 = 60Hz , 5_999_999 | 249999
module counter #(parameter counterWidth = 25, parameter max = 5_999_999) // TODO: adjust the counterWidth and max to have correct clock divider
				 (input logic       clk,
				  input logic       reset,
				  input logic       enable,
				  output logic [counterWidth-1:0] counter
);

	always_ff @(posedge clk, negedge reset)
		begin
			if(reset == 0)                counter <= 0;
			else if (counter == max)      counter <= 0;
			else if (enable == 1)         counter <= counter + 1;
			//else 
				//counter <= counter + 1;
		end
endmodule

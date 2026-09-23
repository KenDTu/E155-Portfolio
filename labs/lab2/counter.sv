// Author: Ken TU
// Email: ktu@g.hmc.edu
// Date of Creation: 09/20/2026
// Counter divider to divide the 24MHz int_osc

// counterWidth = 2^19 = 524,288 ≥ 400,000
// clock math is 24MHz / 400,000 = 60Hz
module counter #(parameter counterWidth = 18, parameter max = 249999) // TODO: adjust the counterWidth and max to have correct clock divider
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
		end
endmodule

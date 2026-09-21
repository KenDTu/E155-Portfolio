// Author: Ken TU
// Email: ktu@g.hmc.edu
// Date of Creation: 09/20/2026
// Counter divider to divide the 24MHz int_osc

// counterWidth = 2^19 = 524,288 ≥ 400,000
// clock math is 24MHz / 400,000 = 60Hz
module counter #(parameter counterWidth = 19, parameter max = 399,999) // TODO: adjust the counterWidth and max to have correct clock divider
				 (input logic      int_osc,
				  input logic      reset,
				  input logic      enable,
				  output logic     leftHex,
			      output logic     ledLast
);
	logic [counterWidth-1:0] counter;

	always_ff @(posedge int_osc, negedge reset)  // TODO: use the enable and verify your logic
		begin
			if(reset == 0)                counter <= 0;
			else if (counter == max)      counter <= 0;
			else if (enable == 1)         counter <= counter + 1;
		end


	// output of the last led light from the counter
	assign ledLast = counter[23];

	// output of the leftHex to be on or off using logical assignment
	assign leftHex = (count > max/2);

endmodule
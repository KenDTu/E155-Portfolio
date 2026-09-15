// Author: Ken TU
// Email: ktu@g.hmc.edu
// Date of Creation: 09/07/2026
// Counter module for the 2.4Hz flashing LED

module counter #(parameter N = 8, parameter max = 24000000)
				 (input logic      int_osc,
				  input logic      reset,
				  input logic      enable,
			      output logic     ledLast
);
	logic [24:0] counter;

	always_ff @(posedge int_osc, negedge reset) 
		begin
			if(reset == 0)                counter <= 0;
			else if (counter == max)      counter <= 0;
			// else if (enable == 1) counter <= counter + 1;
			else                counter <= counter + 1;
		end


	// output of the last led light from the counter
	assign ledLast = counter[23];

endmodule

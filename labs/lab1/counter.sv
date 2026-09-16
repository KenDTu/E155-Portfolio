// Author: Ken TU
// Email: ktu@g.hmc.edu
// Date of Creation: 09/07/2026
// Counter module for the 2.4Hz flashing LED

module counter #(parameter N = 24, parameter max = 24000000)
				 (input logic      int_osc,
				  input logic      reset,
				  input logic      enable,
			      output logic     ledLast
);
	logic [counterWidth:0] counter;

	always_ff @(posedge int_osc, negedge reset)  // TODO: use the enable and verify your logic
		begin
			if(reset == 0)                counter <= 0;
			else if (counter == max)      counter <= 0;
			else                counter <= counter + 1;
		end


	// output of the last led light from the counter
	assign ledLast = counter[23];

endmodule
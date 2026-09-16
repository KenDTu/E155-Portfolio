// Author: Ken Tu
// Email: ktu@g.hmc.edu
// Date of Creation: 09/07/2026
// Top Module to instantiate HSOSC, counter, and Seven Segment Decoder.

module lab1_ktu(
		input logic [3:0] s,     // the four DIP switches (on the board, SW6)
		input logic reset, // switch for reset on the board
		input logic enable, // switch for enable on the board
		output logic [2:0] led,   // 3 LEDs (you may use the on-board LEDs)
		output logic [6:0] seg   // the segments of a common-anode 7-segment display
);

	logic int_osc;

	// Internal high-speed oscillator
	HSOSC #(.CLKHF_DIV(2'b01))
		hf_osc (.CLKHFPU(1'b1), .CLKHFEN(1'b1), .CLKHF(int_osc));

   
	// Instantiating Seven Segement displayer decoder
	sevenseg sevensegData(.s(s), .segments(seg));

	// Instantiating Counter to oscillate led 3
	counter counter1(.int_osc(int_osc), .reset(reset), .enable(enable), .ledLast(led[2]));

    //  Assign LED output
	assign led[0] = s[1] ^ s[0];
	assign led[1] = s[3] && s[2];


endmodule
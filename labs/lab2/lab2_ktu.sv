// Author: Ken Tu
// Email: ktu@g.hmc.edu
// Date of Creation: 09/20/2026
// Top Module to instantiate HSOSC, counter, and Seven Segment Decoder.

module lab2_ktu(
		input logic [3:0] switchLeft, // the four DIP switches (on the board, SW6)
		input logic [3:0] switchRight, // the off board DIP switch
		input logic reset, // switch for reset on the board
		input logic enable, // switch for enable on the board
		output logic [2:0] led,   // 3 LEDs (you may use the on-board LEDs)
		output logic [6:0] seg   // the segments of a common-anode 7-segment display
);

	logic int_osc;
	logic leftHex; // to toggle the left seven segment power
	logic rightHex; // to toggle the right seven segment power
	
	// Internal high-speed oscillator
	HSOSC #(.CLKHF_DIV(2'b01))
		hf_osc (.CLKHFPU(1'b1), .CLKHFEN(1'b1), .CLKHF(int_osc));

   
	// Instantiating Seven Segement displayer decoder
	sevenseg sevensegData(.s(s), .segments(seg));

	// Instantiating Counter to oscillate led 3
	counter counter1(.int_osc(int_osc), .reset(reset), .enable(enable), .ledLast(led[2]));
	
	assign leftHex = led[2]; // this is the on or off for the power for the side of the seven seg
	assign rightHex = ~leftHex; // if rightHex is on then leftHex should be off
	
	// TODO: pin assignments according to lab 2.
	
	// switchRight[3] - P4, switchRight[2] - P48, switchRight[1] - P47, switchRight[0] - P2
	
	// pin assignments from lab 1 to verify
    //  Assign LED output
	assign led[0] = switchLeft[1] ^ switchLeft[0];
	assign led[1] = switchLeft[3] && switchLeft[2];


endmodule
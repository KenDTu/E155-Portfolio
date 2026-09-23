// Author: Ken Tu
// Email: ktu@g.hmc.edu
// Date of Creation: 09/20/2026
// Top Module to instantiate HSOSC, counter, and Seven Segment Decoder.

/* ======= PIN ASSIGNMENTS ==========
leftHex = P46
rightHex = P45

LEFT SEGEMENT SWTICH
switchLeft[3], switchLeft[2], switchLeft[1], switchLeft[0]
P4, P48, P47, P2

RIGHT SEGEMENT SWITCH
switchRight[3], switchRight[2], switchRight[1], switchRight[0]
P32, P35, P31, P37

OUTPUT SEG
seg[6], seg[5], seg[4], seg[3], seg[2], seg[1], seg[0]
see iPad
*/

module lab2_ktu #(parameter max = 249999)
	   (input logic [3:0] switchLeft, // the four DIP switches (on the board, SW6)
		input logic [3:0] switchRight, // the off board DIP switch
		input logic reset, // switch for reset on the board
		input logic enable, // switch for enable on the board
		output logic [2:0] led,   // 3 LEDs (you may use the on-board LEDs)
		output logic [6:0] seg,   // the segments of a common-anode 7-segment display
		output leftHex, // to toggle the left seven segment power
		output rightHex // to toggle the right seven segment power
);
	logic [3:0] s;
	logic int_osc;
	logic [17:0] counter;

	// Internal high-speed oscillator
	HSOSC #(.CLKHF_DIV(2'b01))
		hf_osc (.CLKHFPU(1'b1), .CLKHFEN(1'b1), .CLKHF(int_osc));
	
	// Instantiating Counter to oscillate the l
	counter counter1(.int_osc(int_osc), .reset(reset), .enable(enable), .counter(counter));
	sevenseg sevensegData(.s(s), .segments(seg));
	
	// assign leftHex = (counter > max/2);
	assign leftHex = (counter < max/2);
	assign rightHex = ~leftHex; // if rightHex is on then leftHex should be off
	
	assign s = leftHex ? switchLeft : switchRight;
	
	// switchRight[3] - P4, switchRight[2] - P48, switchRight[1] - P47, switchRight[0] - P2
	
	// pin assignments from lab 1 to verify
    //  Assign LED output
	assign led[0] = switchLeft[1] ^ switchLeft[0];
	assign led[1] = switchLeft[3] && switchLeft[2];
	assign led[2] = (counter < max/2);
endmodule

// Author: Ken Tu
// Email: ktu@g.hmc.edu
// Date of Creation: 09/07/2026
// Seven segment display decoder module

module sevenseg(
				input logic [3:0] s,
				output logic [6:0] segments
);
	always_comb
		case(s) // driving each segment but pulling its cathode low?
			//               abc_defg
			4'b0000: segments = 7'b100_0000; // 0
			4'b0001: segments = 7'b111_1001; // 1
			4'b0010: segments = 7'b010_0100; // 2
			4'b0011: segments = 7'b011_0000; // 3
			4'b0100: segments = 7'b001_1001; // 4
			4'b0101: segments = 7'b001_0010; // 5
			4'b0110: segments = 7'b000_0010; // 6
			4'b0111: segments = 7'b111_1000; // 7
			4'b1000: segments = 7'b000_0000; // 8
			4'b1001: segments = 7'b001_1000; // 9
			4'b1010: segments = 7'b000_1000; // A
			4'b1011: segments = 7'b000_0011; // B
			4'b1100: segments = 7'b100_0110; // C
			4'b1101: segments = 7'b010_0001; // D
			4'b1110: segments = 7'b000_0110; // E
			4'b1111: segments = 7'b000_1110; // F
			default: segments = 7'b000_0000;
		endcase
		
		// for active low
		// assign segments = ~segments;
 endmodule
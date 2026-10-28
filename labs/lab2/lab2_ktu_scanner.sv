// Author: Ken TU 
// Email: ktu@g.hmc.edu
// Date of Creation: 09/22/2026
// Scanner module for the scanning section for lab 2

module scanner(input  logic       clk, // when instantiating pass int_osc
			   input  logic       reset,
			   input  logic       enable,
			   input  logic [3:0] column, // when instantiating pass off-board switchRight
			   output logic [3:0] switchRight,   // dirves the 4 NPN gates and performs the row scanning AKA row
			   output logic [3:0] keyLead // off-board LED shows the pressed column
);
	logic [22:0] counter; // this logic must toggle at 2Hz
	logic [1:0]  rowNum;  // R0 - 00, R1 - 01, R2 - 10, or R3 - 11

	counter #(.max(999_999)) counterScanner(.clk(clk), .reset(reset), .enable(enable), .counter(counter));
	
	// asserting each row every 2Hz
	always_ff @(posedge clk) // negedge reset
		begin
			//if(reset == 0) 
					 //rowNum <= 2'b00;
			if (counter == 999_997) rowNum <= rowNum + 1; // enable == 1 && 
		end
		
	// Assert each row
	always_comb 
		case (rowNum) // checking which row is asserted
			2'b00:    switchRight = 4'b0001; // R0
			2'b01:    switchRight = 4'b0010; // R1
			2'b10:    switchRight = 4'b0100; // R2
			2'b11:    switchRight = 4'b1000; // R3
			default:  switchRight = 4'b1111; // R0
		endcase
		
	assign keyLead = ~column;
	// column voltage should be determined by circuit
	//always_comb 
		//case (column) // checking which row is asserted
			
			//4'b1110:    keyLead = 4'b0001; // col0
			//4'b1101:    keyLead = 4'b0010; // col1
			//4'b1011:    keyLead = 4'b0100; // col2
			//4'b0111:    keyLead = 4'b1000; // col3
			//default:  keyLead = 4'b0000; // no column
		//endcase
	
	
	
endmodule
